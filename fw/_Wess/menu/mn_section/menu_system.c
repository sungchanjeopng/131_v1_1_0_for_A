//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
// bsp
#include "bsp_ram.h"
#include "bsp_ota.h"
// app
#include "app_main.h"
// menu
#include "menu_main.h"
#include "menu_lyr0_section.h"
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
#include "menu_lyr4_addition.h"
#include "disp_string.h"
#include "disp_popup.h"
// function
#include "bsp_usb.h"
#include "input_main.h"
#include "input_key.h"
#include <string.h>
// self
#include "menu_system.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnSYS_LS lMnSys;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


#define MnSYS_FWB_ROWS		(7)		// file-list rows per page (content window between top/bottom bars)

static void MnSYS_FwBrowserDoUpdate(const I08 *path)
{
	U16 ret;

	DpPOP_DrwOtaStart();
	DpPOP_DrwOtaStatus((I08*)"Reading file...");
	ret = ota_usb_program_file(path);
	DpPOP_DrwOtaResult(ret);
	HAL_Delay(1500);
	DpPOP_DrwOtaEnd();

	if(ret == OTA_RESULT_OK)
		__NVIC_SystemReset();		// success -> reboot, bootloader applies the image
}

// Restore the menu screen after the full-screen browser closes (the browser
// overwrote the whole LCD, and the persistent framebuffer keeps the last image).
static void MnSYS_FwBrowserClose(void)
{
	MENU_ReDrawAll();		// repaint top title bar (it was overwritten)
	MnLY3_GotoLyr2();		// clear + repaint menu window: section box + item list + buttons (layer L2)
}

//  USB firmware update: browse files on the USB drive, pick one, then program it.
//  Self-contained blocking loop (matches the original blocking OTA style); the
//  normal scheduler resumes once this returns. Called directly on the item ENTER
//  (see menu_lyr2_item.c) so it opens with a single press.
//
//  Key handling note: we scan keys ourselves while the scheduler is blocked, and
//  InKEY only produces KEY_EVT_PUSH here (its long/repeat counters are cleared each
//  tick by ClrEvt), so we edge-detect on the pressed index instead of waiting for
//  SHORT/REPEAT events: PREV/NEXT repeat while held, MENU/ENTER fire once per press.
void MnSYS_FirmwareUpdateUsb(void)
{
	static OTA_USB_FILE list[OTA_USB_LIST_MAX];
	I08  curDir[OTA_USB_PATH_MAX];
	U08  count;
	U08  cursor  = 0;
	U08  pageTop = 0;
	U08  done    = 0;
	U08  lastKey = KEY_IDX_ENTER;		// pre-arm: ignore the ENTER that opened this until released

	if(BspUsb_IsMounted() == FALSE)
	{
		DpPOP_DrwOtaStart();
		DpPOP_DrwOtaStatus((I08*)"No USB memory.");
		HAL_Delay(1500);
		MnSYS_FwBrowserClose();
		return;
	}

	strcpy((char*)curDir, "0:/");
	count = ota_usb_browse(curDir, list, OTA_USB_LIST_MAX);

	DpPOP_DrwFileList(curDir, list, count, cursor, pageTop, MnSYS_FWB_ROWS);	// show immediately on entry
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	while(done == 0)
	{
		U08 key;
		U08 fresh;
		U08 dirty = 0;					// redraw only when something actually changed

		INPU_ProcMain();				// scheduler is blocked here, so scan keys ourselves

		key = INPU_GetKeyIdx();
		if(INPU_GetKeyEvt() == KEY_EVT_NONE)
			key = KEY_IDX_NONE;			// no key currently pressed

		if(key == KEY_IDX_NONE)
		{
			lastKey = KEY_IDX_NONE;		// released -> re-arm discrete keys
		}
		else
		{
			fresh = (U08)(key != lastKey);	// first frame of a new press
			lastKey = key;
			if(fresh)
				dirty = 1;				// new press -> redraw once to wipe native button feedback

			switch(key)
			{
				case KEY_IDX_PREV:		// repeat while held; mark dirty only when it moves
					if(count > 0 && cursor > 0)
					{
						cursor--;
						if(cursor < pageTop) pageTop = cursor;
						dirty = 1;
					}
					break;

				case KEY_IDX_NEXT:
					if(count > 0 && (U08)(cursor + 1) < count)
					{
						cursor++;
						if(cursor >= (U08)(pageTop + MnSYS_FWB_ROWS))
							pageTop = (U08)(cursor - MnSYS_FWB_ROWS + 1);
						dirty = 1;
					}
					break;

				case KEY_IDX_MENU:		// one action per press
					if(fresh)
					{
						if(strcmp((char*)curDir, "0:/") == 0 || strcmp((char*)curDir, "0:") == 0)
						{
							done = 1;							// leave browser -> back to menu
						}
						else
						{
							I08 *slash = strrchr((char*)curDir, '/');
							if(slash != 0)
							{
								if(slash == curDir + 2)  *(slash + 1) = 0;	// "0:/abc" -> "0:/"
								else                     *slash       = 0;	// "0:/a/b" -> "0:/a"
							}
							count   = ota_usb_browse(curDir, list, OTA_USB_LIST_MAX);
							cursor  = 0;
							pageTop = 0;
							dirty   = 1;
						}
					}
					break;

				case KEY_IDX_ENTER:		// one action per press
					if(fresh && count > 0)
					{
						if(list[cursor].isDir != 0)
						{
							strncpy((char*)curDir, (char*)list[cursor].path, OTA_USB_PATH_MAX - 1);
							curDir[OTA_USB_PATH_MAX - 1] = 0;
							count   = ota_usb_browse(curDir, list, OTA_USB_LIST_MAX);
							cursor  = 0;
							pageTop = 0;
							dirty   = 1;
						}
						else
						{
							MnSYS_FwBrowserDoUpdate(list[cursor].path);
							done = 1;						// only here if update failed (success reboots)
						}
					}
					break;
			}
		}

		INPU_ClrKeyEvt(KEY_EVT_NONE);

		// Redraw ONLY when something changed. Idle = no redraw = no flicker.
		if(done == 0 && dirty)
			DpPOP_DrwFileList(curDir, list, count, cursor, pageTop, MnSYS_FWB_ROWS);

		HAL_Delay(50);
	}

	MnSYS_FwBrowserClose();			// restore the menu screen (browser took over the whole LCD)
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
// Get
RTC_TM MnSYS_PrGet_Rtc(void)			{	return lMnSys.rtc;				}
S32 MnSYS_PrGet_site_name_hi(U08 ch)	{	return lMnSys.mPr.site_name_HI[ch];	}
S32 MnSYS_PrGet_site_name_lo(U08 ch)	{	return lMnSys.mPr.site_name_LO[ch];	}
S32 MnSYS_PrGet_site_name(U08 ch)	{	return lMnSys.mPr.site_name[ch];	}


S32 MnSYS_PrGetBase_Item(U08 itm)
{
	switch(itm)
	{
		case MnSYS_OPT_PASSCODE:		return lMnSys.mPr.passcode;
		case MnSYS_OPT_LANG:			return lMnSys.mPr.lang;			
		case MnSYS_OPT_TIME:			break;
		case MnSYS_OPT_RTN_TIM:			return lMnSys.mPr.rtn_tim;
		case MnSYS_OPT_CH1_SITE_NAME:
		case MnSYS_OPT_CH2_SITE_NAME:	break;
		case MnSYS_OPT_FTR_RST:
		case MnSYS_OPT_FW_UPDATE_USB:	break;	
		default:						break;
	}

	return MENU_VAL_INVALID;
}

S32 MnSYS_PrGetBase_Ch_Item(U08 itm)
{
	switch(itm)
	{
		case MnSYS_OPT_SINGLE_PASSCODE:		return lMnSys.mPr.passcode;
		case MnSYS_OPT_SINGLE_LANG:			return lMnSys.mPr.lang;			
		case MnSYS_OPT_SINGLE_TIME:			break;
		case MnSYS_OPT_SINGLE_RTN_TIM:		return lMnSys.mPr.rtn_tim;
		case MnSYS_OPT_SINGLE_SITE_NAME:
		case MnSYS_OPT_SINGLE_FTR_RST:
		case MnSYS_OPT_SINGLE_FW_UPDATE_USB:	break;	
		default:							break;
	}

	return MENU_VAL_INVALID;
}

S32 MnSYS_PrGetAlarm_Item(U08 itm)
{
	switch(itm)
	{
		case MnSYS_OPT_ALARM_TIMER:		return lMnSys.mPr.alarm_timer;
		case MnSYS_OPT_ALARM_RESET:		return MnSYS_ALARM_RESET_OFF;			
		default:						break;
	}

	return MENU_VAL_INVALID;
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Set & Save
//------------------------------------------------------------------------------------------------------------------------------
void MnSYS_PrSet_Time(RTC_TM rtc)
{
	lMnSys.rtc = rtc;

	APP_RtcSetTime(lMnSys.rtc);	
}

void MnSYS_PrSetBase_Value(U08 iIt,S32 val)
{
	switch(iIt)
	{
		case MnSYS_OPT_PASSCODE:		lMnSys.mPr.passcode = val;		break;
		case MnSYS_OPT_LANG:			lMnSys.mPr.lang = val;			DpSTR_InitMain();	break;
		case MnSYS_OPT_TIME:			break;
		case MnSYS_OPT_RTN_TIM:			lMnSys.mPr.rtn_tim = val;		break;
		case MnSYS_OPT_CH1_SITE_NAME:	lMnSys.mPr.site_name[APP_CH_1] =  val;	break;
		case MnSYS_OPT_CH2_SITE_NAME:	lMnSys.mPr.site_name[APP_CH_2] =  val;	break;			
		case MnSYS_OPT_FW_UPDATE_USB:	MnSYS_FirmwareUpdateUsb();			break;
		default:
			break;
	}

	switch(iIt)
	{
		case MnSYS_OPT_PASSCODE:		MRM_WrWord(_mPASSCODE_L, lMnSys.mPr.passcode);		break;
		case MnSYS_OPT_LANG:			MRM_WrByte(_mLANG, lMnSys.mPr.lang);				break;
		case MnSYS_OPT_TIME:			break;
		case MnSYS_OPT_RTN_TIM:			MRM_WrByte(_mRTN_TIM, lMnSys.mPr.rtn_tim);			break;
		case MnSYS_OPT_CH1_SITE_NAME:	MRM_WrWord(_mCH1_SITE_NAME_L,  lMnSys.mPr.site_name[APP_CH_1]);	break;
		case MnSYS_OPT_CH2_SITE_NAME:	MRM_WrWord(_mCH2_SITE_NAME_L,  lMnSys.mPr.site_name[APP_CH_2]);	break;
	}
}

void MnSYS_PrSetBase_Ch_Value(U08 iIt,S32 val)
{
	switch(iIt)
	{
		case MnSYS_OPT_SINGLE_PASSCODE:		lMnSys.mPr.passcode = val;		break;
		case MnSYS_OPT_SINGLE_LANG:			lMnSys.mPr.lang = val;			break;
		case MnSYS_OPT_SINGLE_TIME:			break;
		case MnSYS_OPT_SINGLE_RTN_TIM:			lMnSys.mPr.rtn_tim = val;		break;
		case MnSYS_OPT_SINGLE_SITE_NAME:	lMnSys.mPr.site_name[APP_CH_1] =  val;	break;		
		case MnSYS_OPT_SINGLE_FW_UPDATE_USB:	MnSYS_FirmwareUpdateUsb();		break;
		default:
			break;
	}

	switch(iIt)
	{
		case MnSYS_OPT_SINGLE_PASSCODE:		MRM_WrWord(_mPASSCODE_L, lMnSys.mPr.passcode);		break;
		case MnSYS_OPT_SINGLE_LANG:			MRM_WrByte(_mLANG, lMnSys.mPr.lang);				break;
		case MnSYS_OPT_SINGLE_TIME:			break;
		case MnSYS_OPT_SINGLE_RTN_TIM:		MRM_WrByte(_mRTN_TIM, lMnSys.mPr.rtn_tim);			break;
		case MnSYS_OPT_SINGLE_SITE_NAME:	MRM_WrWord(_mCH1_SITE_NAME_L,  lMnSys.mPr.site_name[APP_CH_1]);	break;	
	}
}

void MnSYS_PrSetAlarm_Value(S32 val)
{
	U08 iIt = MnLY2_GetIdxItem();

	switch(iIt)
	{
		case MnSYS_OPT_ALARM_TIMER:		lMnSys.mPr.alarm_timer = val;		break;
		case MnSYS_OPT_ALARM_RESET:		lMnSys.mPr.alarm_reset = MnSYS_ALARM_RESET_ON;		break;		
		default:
			break;
	}

	switch(iIt)
	{
		case MnSYS_OPT_ALARM_TIMER:		MRM_WrByte(_mALARM_TIMER, lMnSys.mPr.alarm_timer);		break;
		case MnSYS_OPT_ALARM_RESET:		break;
	}
}

void MnSYS_PrRst_Factory(void)
{
	MRM_WrWord(_mPASSCODE_L, MnSYS_PASSCODE_DEF);
	MRM_WrByte(_mLANG, MnSYS_LANG_DEF);

	MRM_WrByte(_mRTN_TIM, MnSYS_RTN_TIM_DEF);
	MRM_WrWord(_mCH1_SITE_NAME_L, MnSYS_SITE_NAME_DEF);	
	MRM_WrWord(_mCH2_SITE_NAME_L, MnSYS_SITE_NAME_DEF);	

	MRM_WrByte(_mALARM_TIMER, MnSYS_ALARM_TIMER_DEF);


}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 MnSYS_GetLayer(void)			{	return lMnSys.lyr;		}
// Set
void MnSYS_SetLayer(U08 lyr)		{	lMnSys.lyr = lyr;		}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void MnSYS_PrInitMain(void)
{
	lMnSys.mPr.passcode = MRM_RdWord(_mPASSCODE_L);
	lMnSys.mPr.lang = MRM_RdByte(_mLANG);
	lMnSys.mPr.rtn_tim = MRM_RdByte(_mRTN_TIM);
	lMnSys.mPr.site_name[APP_CH_1] = MRM_RdWord(_mCH1_SITE_NAME_L);
	lMnSys.mPr.site_name[APP_CH_2] = MRM_RdWord(_mCH2_SITE_NAME_L);	

	lMnSys.rtc = APP_RtcGetTime();
	lMnSys.mPr.alarm_timer = MRM_RdByte(_mALARM_TIMER);

	// Check Parameters
	if(lMnSys.mPr.passcode > MnSYS_PASSCODE_MAX)						lMnSys.mPr.passcode = MnSYS_PASSCODE_DEF;
	if(lMnSys.mPr.lang > MnSYS_LANG_MAX)								lMnSys.mPr.lang = MnSYS_LANG_DEF;
	if(lMnSys.mPr.rtn_tim > MnSYS_RTN_TIM_MAX)							lMnSys.mPr.rtn_tim = MnSYS_RTN_TIM_DEF;
	if(lMnSys.mPr.site_name[APP_CH_1] < MnSYS_SITE_NAME_MIN)			lMnSys.mPr.site_name[APP_CH_1] = MnSYS_SITE_NAME_DEF;
	if(lMnSys.mPr.site_name[APP_CH_2] < MnSYS_SITE_NAME_MIN)			lMnSys.mPr.site_name[APP_CH_2] = MnSYS_SITE_NAME_DEF;
	if(lMnSys.mPr.site_name[APP_CH_1] > MnSYS_SITE_NAME_MAX)			lMnSys.mPr.site_name[APP_CH_1] = MnSYS_SITE_NAME_DEF;
	if(lMnSys.mPr.site_name[APP_CH_2] > MnSYS_SITE_NAME_MAX)			lMnSys.mPr.site_name[APP_CH_2] = MnSYS_SITE_NAME_DEF;

	if(lMnSys.mPr.alarm_timer > MnSYS_ALARM_TIMER_MAX)					lMnSys.mPr.alarm_timer= MnSYS_ALARM_TIMER_DEF;


	DpSTR_InitMain();

}

void MnSYS_InitMain(void)
{
	lMnSys.lyr = MENU_L0_SECTION;

	MnLY0_InitSection();
	MnLY1_InitSubSct();
	MnLY2_InitItem();
	MnLY3_InitValue();
	MnLY4_InitAddition();

	MnSYS_PrInitMain();
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

