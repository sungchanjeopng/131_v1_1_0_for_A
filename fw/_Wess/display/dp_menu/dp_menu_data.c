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
// display
#include "disp_main.h"
#include "disp_color.h"
#include "disp_string.h"
#include "disp_figure.h"
#include "disp_titlebar.h"
#include "disp_button.h"
#include "disp_popup.h"
// menu
#include "menu_main.h"
#include "menu_data.h"
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
#include "menu_lyr4_addition.h"
// disp - screen
#include "dp_screen_main.h"
// disp - menu
#include "dp_menu_main.h"
// data
#include "data_save.h"
// self
#include "dp_menu_data.h"

#include "menu_factory.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
DpDAT_LS lDpDat;

#define DpDAT_KOR_USB_U		(53)
#define DpDAT_KOR_USB_S		(51)
#define DpDAT_KOR_USB_B		(34)
#define DpDAT_KOR_ASC_LP	(191)
#define DpDAT_KOR_ASC_RP	(192)
#define DpDAT_KOR_ASC_U		(193)
#define DpDAT_KOR_ASC_S		(194)
#define DpDAT_KOR_ASC_B		(195)
#define DpDAT_KOR_ASC_R		(196)
#define DpDAT_KOR_RS_4		(5)
#define DpDAT_KOR_RS_8		(9)
#define DpDAT_KOR_RS_5		(6)
#define DpDAT_KOR_SPACE		(173)

static void DpDAT_CopyKorText(I08 *pDst, const U08 *pSrc)
{
	U08 i;

	for(i=0; i<16; i++)	pDst[i] = 0;
	for(i=0; (i<15) && (pSrc[i] != 0); i++)	pDst[i] = (I08)pSrc[i];
}

static void DpDAT_SetKorExportLabels(void)
{
	static const U08 sDownloadUsb[] = {35, 113, 52, 45, DpDAT_KOR_SPACE, DpDAT_KOR_ASC_LP, DpDAT_KOR_ASC_U, DpDAT_KOR_ASC_S, DpDAT_KOR_ASC_B, DpDAT_KOR_ASC_RP, 0};
	static const U08 sDownloadRs[] = {35, 113, 52, 45, DpDAT_KOR_SPACE, DpDAT_KOR_ASC_LP, DpDAT_KOR_ASC_R, DpDAT_KOR_ASC_S, DpDAT_KOR_RS_4, DpDAT_KOR_RS_8, DpDAT_KOR_RS_5, DpDAT_KOR_ASC_RP, 0};

	DpDAT_CopyKorText(lDpDat.sIt0[MnDS0_OPT_EXPORT_USB], sDownloadUsb);
	DpDAT_CopyKorText(lDpDat.sIt0[MnDS0_OPT_DOWNLOAD], sDownloadRs);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Common
//------------------------------------------------------------------------------------------------------------------------------
void DpDatSav_PopIntro(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnDAT_SavPrGet_Value(iIt);
	I08 pSt0[32] = {0, };
	U08 fDp = _F_T;
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			_SPRINTF(pSt0, lDpDat.sIt0[iIt]);
			break;
		case MnSYS_LANG_ENG:
			switch(iIt)
			{
				case MnDS0_OPT_INTERVAL:			_SPRINTF(pSt0, _sSAV_Intv);			break;
				case MnDS0_OPT_EXPORT_USB:		_SPRINTF(pSt0, "Export (USB)");		break;
				case MnDS0_OPT_DOWNLOAD:			_SPRINTF(pSt0, "Export (RS485)");	break;
				case MnDS0_OPT_DELETE:				_SPRINTF(pSt0, _sSAV_Del);			break;
				case MnDS0_OPT_DISPLAY_TERM:		_SPRINTF(pSt0, _sDisplay_term);		break;
				default:							_SPRINTF(pSt0, _sNG);				break;
			}			
			break;
	}

	DpPOP_UdtTitle(pSt0);

	// Old Value
	switch(iIt)
	{
		case MnDS0_OPT_INTERVAL:
			switch(val)
			{
				case MnDS0_INTV_01S:		_SPRINTF(pSt0, _sTim_1Sec);					break;
				case MnDS0_INTV_10S:		_SPRINTF(pSt0, _sTim_10Sec);				break;
				case MnDS0_INTV_01M:		_SPRINTF(pSt0, _sTim_1Min);					break;
				case MnDS0_INTV_10M:		_SPRINTF(pSt0, _sTim_10Min);				break;
				case MnDS0_INTV_01H:		_SPRINTF(pSt0, _sTim_1Hrs);					break;
				default:					_SPRINTF(pSt0, _sNG);						break;
			}
			break;
		case MnDS0_OPT_EXPORT_USB:			fDp = _F_F;									break;
		case MnDS0_OPT_DOWNLOAD:			_SPRINTF(pSt0, "%d", (U16)DaSav_GetCnt());	break;
		case MnDS0_OPT_DELETE:				fDp = _F_F;									break;
		case MnDS0_OPT_DISPLAY_TERM:	
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_INTERVAL))
			{
				case MnDS0_INTV_01S:
					switch(val)
					{
						case MnDS0_DISPLAY_TERM_1:	_SPRINTF(pSt0, "12 min");			break;
						case MnDS0_DISPLAY_TERM_2:	_SPRINTF(pSt0, "24 min");			break;
					}
					break;
				case MnDS0_INTV_10S:
					switch(val)
					{
						case MnDS0_DISPLAY_TERM_1:	_SPRINTF(pSt0, "2 hour");			break;
						case MnDS0_DISPLAY_TERM_2:	_SPRINTF(pSt0, "4 hour");			break;
					}
					break;					
				case MnDS0_INTV_01M:
					switch(val)
					{
						case MnDS0_DISPLAY_TERM_1:	_SPRINTF(pSt0, _sTim_12Hrs);			break;
						case MnDS0_DISPLAY_TERM_2:	_SPRINTF(pSt0, _sTim_24Hrs);			break;
					}
					break;					
				case MnDS0_INTV_10M:
					switch(val)
					{
						case MnDS0_DISPLAY_TERM_1:	_SPRINTF(pSt0, _sTim_5Day);			break;
						case MnDS0_DISPLAY_TERM_2:	_SPRINTF(pSt0, _sTim_10Day);			break;
					}
					break;					
				case MnDS0_INTV_01H:
					switch(val)
					{
						case MnDS0_DISPLAY_TERM_1:	_SPRINTF(pSt0, _sTim_30Day);			break;
						case MnDS0_DISPLAY_TERM_2:	_SPRINTF(pSt0, _sTim_60Day);			break;
					}
					break;					
				default:					
					_SPRINTF(pSt0, _sNG);						
					break;
			}
			break;
		default:									_SPRINTF(pSt0, _sNG);					break;
	}	
	if(fDp)	DpPOP_UdtOldVl(pSt0);
	fDp = _F_T;

#if 0
	// Range (Min. / Max.)
	switch(iIt)
	{
		case MnDS0_OPT_INTERVAL:		min = MnDS0_INTV_MIN;			max = MnDS0_INTV_MAX;				break;
		case MnDS0_OPT_DOWNLOAD:
		case MnDS0_OPT_DELETE:			fDp = _F_F;															break;
		case MnDS0_OPT_DISPLAY_TERM:	min = MnDS0_DISPLAY_TERM_MIN;	max = MnDS0_DISPLAY_TERM_MAX;		break;
		default:						break;
	}
	
	switch(iIt)
	{
		case MnDS0_OPT_INTERVAL:
			switch(min)
			{
				case MnDS0_INTV_01S:		_SPRINTF(pSt0, _sTim_1Sec);					break;
				case MnDS0_INTV_10S:		_SPRINTF(pSt0, _sTim_10Sec);				break;
				case MnDS0_INTV_01M:		_SPRINTF(pSt0, _sTim_1Min);					break;
				case MnDS0_INTV_10M:		_SPRINTF(pSt0, _sTim_10Min);				break;
				case MnDS0_INTV_01H:		_SPRINTF(pSt0, _sTim_1Hrs);					break;
				default:					_SPRINTF(pSt0, _sNG);						break;
			}
			break;
		case MnDS0_OPT_DOWNLOAD:
		case MnDS0_OPT_DELETE:				fDp = _F_F;						break;
		case MnDS0_OPT_DISPLAY_TERM:
			switch(min)
			{
				case MnDS0_DISPLAY_TERM_12H:		_SPRINTF(pSt0, _sTim_12Hrs);			break;
				case MnDS0_DISPLAY_TERM_24H:		_SPRINTF(pSt0, _sTim_24Hrs);			break;
				case MnDS0_DISPLAY_TERM_01D:		_SPRINTF(pSt0, _sTim_5Day);				break;
				case MnDS0_DISPLAY_TERM_07D:		_SPRINTF(pSt0, _sTim_10Day);				break;
				case MnDS0_DISPLAY_TERM_14D:		_SPRINTF(pSt0, _sTim_30Day);			break;
				case MnDS0_DISPLAY_TERM_30D:		_SPRINTF(pSt0, _sTim_30Day);			break;
				default:							_SPRINTF(pSt0, _sNG);					break;
			}
			break;			
		default:						break;
	}
	
	if(fDp)	DpPOP_UdtRangeMin(pSt0);
	fDp = _F_T;
	
	switch(iIt)
	{
		case MnDS0_OPT_INTERVAL:
			switch(max)
			{
				case MnDS0_INTV_01S:		_SPRINTF(pSt0, _sTim_1Sec);					break;
				case MnDS0_INTV_10S:		_SPRINTF(pSt0, _sTim_10Sec);				break;
				case MnDS0_INTV_01M:		_SPRINTF(pSt0, _sTim_1Min);					break;
				case MnDS0_INTV_10M:		_SPRINTF(pSt0, _sTim_10Min);				break;
				case MnDS0_INTV_01H:		_SPRINTF(pSt0, _sTim_1Hrs);					break;
				default:					_SPRINTF(pSt0, _sNG);						break;
			}
			break;
		case MnDS0_OPT_DOWNLOAD:
		case MnDS0_OPT_DELETE:				fDp = _F_F;						break;
		case MnDS0_OPT_DISPLAY_TERM:
			switch(max)
			{
				case MnDS0_DISPLAY_TERM_12H:		_SPRINTF(pSt0, _sTim_12Hrs);			break;
				case MnDS0_DISPLAY_TERM_24H:		_SPRINTF(pSt0, _sTim_24Hrs);			break;
				case MnDS0_DISPLAY_TERM_01D:		_SPRINTF(pSt0, _sTim_5Day);				break;
				case MnDS0_DISPLAY_TERM_07D:		_SPRINTF(pSt0, _sTim_10Day);				break;
				case MnDS0_DISPLAY_TERM_14D:		_SPRINTF(pSt0, _sTim_30Day);			break;
				case MnDS0_DISPLAY_TERM_30D:		_SPRINTF(pSt0, _sTim_30Day);			break;
				default:							_SPRINTF(pSt0, _sNG);					break;
			}
			break;			
		default:						break;
	}

	
	if(fDp)	DpPOP_UdtRangeMax(pSt0);
	fDp = _F_T;
	// Explanation
	switch(iIt)
	{
		case MnDS0_OPT_INTERVAL:		_SPRINTF(pSt0, _sSel_PsSet);	break;	
		case MnDS0_OPT_DOWNLOAD:		fDp = _F_F;						break;
		case MnDS0_OPT_DELETE:			fDp = _F_F;	
		case MnDS0_OPT_DISPLAY_TERM:	_SPRINTF(pSt0, _sSel_PsSet);	break;
		default:						_SPRINTF(pSt0, _sNG);			break;
	}
	DpPOP_UdtExpla(pSt0);	
#endif
}

void DpDatSav_PopUpdat(void)
{
	U16 x0 = DpPOP_CT1_X0;
	U16 y0 = DpPOP_CT1_Y0;
	U32 cBg = _cPOP_BG_WND;
	I08 pSt0[16] = {0, };

	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnLY3_GetValue();

	switch(iIt)
	{
		case MnDS0_OPT_INTERVAL:
			switch(val)
			{
				case MnDS0_INTV_01S:		_SPRINTF(pSt0, _sTim_1Sec);					break;
				case MnDS0_INTV_10S:		_SPRINTF(pSt0, _sTim_10Sec);				break;
				case MnDS0_INTV_01M:		_SPRINTF(pSt0, _sTim_1Min);					break;
				case MnDS0_INTV_10M:		_SPRINTF(pSt0, _sTim_10Min);				break;
				case MnDS0_INTV_01H:		_SPRINTF(pSt0, _sTim_1Hrs);					break;
				default:					_SPRINTF(pSt0, _sNG);						break;
			}
			break;
		case MnDS0_OPT_EXPORT_USB:		DpPOP_UdtValue(0,   _F_F, gDpStr.sYnN[0]);
										DpPOP_UdtValue(1,   _F_F, gDpStr.sYnN[1]);
										DpPOP_UdtValue(val, _F_T, gDpStr.sYnN[val]);	return;	// NO / YES selector
		case MnDS0_OPT_DOWNLOAD:
			if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
			{
				if(MnSYS_PrGetBase_Item(MnSYS_OPT_LANG)==MnSYS_LANG_ENG)
				{
					switch(val)
					{
						case MnDS0_DOWN_CH1_LIGHT:		_SPRINTF(pSt0, _sCH1_Light); 				break;
						case MnDS0_DOWN_CH1_HEAVY:		_SPRINTF(pSt0, _sCH1_Heavy);				break;
						case MnDS0_DOWN_CH2_LIGHT:		_SPRINTF(pSt0, _sCH2_Light); 				break;
						case MnDS0_DOWN_CH2_HEAVY:		_SPRINTF(pSt0, _sCH2_Heavy);				break;
						default:						_SPRINTF(pSt0, _sNG);						break;
					}
				}
				else if(MnSYS_PrGetBase_Item(MnSYS_OPT_LANG)==MnSYS_LANG_KOR)
				{
					switch(val)
					{
						case MnDS0_DOWN_CH1_LIGHT:		DpSTR_GuiList(TEXT_LIST_CH1_LIGHT);				break;
						case MnDS0_DOWN_CH1_HEAVY:		DpSTR_GuiList(TEXT_LIST_CH1_HEAVY);				break;
						case MnDS0_DOWN_CH2_LIGHT:		DpSTR_GuiList(TEXT_LIST_CH2_LIGHT);				break;
						case MnDS0_DOWN_CH2_HEAVY:		DpSTR_GuiList(TEXT_LIST_CH2_HEAVY);				break;
					}


					DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
					DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
					return;
				}
			}
			else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
			{
				if(MnSYS_PrGetBase_Item(MnSYS_OPT_LANG)==MnSYS_LANG_ENG)
				{
					switch(val)
					{
						case MnDS0_DOWN_CH1_LIGHT:		_SPRINTF(pSt0, _sLight);				break;
						case MnDS0_DOWN_CH1_HEAVY:		_SPRINTF(pSt0, _sHeavy);				break;
						default:						_SPRINTF(pSt0, _sNG);					break;
					}
				}
				else if(MnSYS_PrGetBase_Item(MnSYS_OPT_LANG)==MnSYS_LANG_KOR)
				{
					switch(val)
					{
						case MnDS0_DOWN_CH1_LIGHT:		DpSTR_GuiList(TEXT_LIST_LIGHT);				break;
						case MnDS0_DOWN_CH1_HEAVY:		DpSTR_GuiList(TEXT_LIST_HEAVY);				break;
					}

					DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
					DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
					return;
				}
			}
			break;
		case MnDS0_OPT_DELETE:			DpPOP_UdtValue(0,   _F_F, gDpStr.sYnN[0]);
										DpPOP_UdtValue(1,   _F_F, gDpStr.sYnN[1]);
										DpPOP_UdtValue(val, _F_T, gDpStr.sYnN[val]);	return;
		case MnDS0_OPT_DISPLAY_TERM:
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_INTERVAL))
			{
				case MnDS0_INTV_01S:
					switch(val)
					{
						case MnDS0_DISPLAY_TERM_1:	_SPRINTF(pSt0, "12 min");			break;
						case MnDS0_DISPLAY_TERM_2:	_SPRINTF(pSt0, "24 min");			break;
					}
					break;
				case MnDS0_INTV_10S:
					switch(val)
					{
						case MnDS0_DISPLAY_TERM_1:	_SPRINTF(pSt0, "2 hour");			break;
						case MnDS0_DISPLAY_TERM_2:	_SPRINTF(pSt0, "4 hour");			break;
					}
					break;					
				case MnDS0_INTV_01M:
					switch(val)
					{
						case MnDS0_DISPLAY_TERM_1:	_SPRINTF(pSt0, _sTim_12Hrs);			break;
						case MnDS0_DISPLAY_TERM_2:	_SPRINTF(pSt0, _sTim_24Hrs);			break;
					}
					break;					
				case MnDS0_INTV_10M:
					switch(val)
					{
						case MnDS0_DISPLAY_TERM_1:	_SPRINTF(pSt0, _sTim_5Day);			break;
						case MnDS0_DISPLAY_TERM_2:	_SPRINTF(pSt0, _sTim_10Day);			break;
					}
					break;					
				case MnDS0_INTV_01H:
					switch(val)
					{
						case MnDS0_DISPLAY_TERM_1:	_SPRINTF(pSt0, _sTim_30Day);			break;
						case MnDS0_DISPLAY_TERM_2:	_SPRINTF(pSt0, _sTim_60Day);			break;
					}
					break;					
				default:					
					_SPRINTF(pSt0, _sNG);						
					break;
			}
			break;		
		default:						_SPRINTF(pSt0, _sNG);							break;
	}
	
	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpSTR_GuiLeft(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsB, pSt0);
}

void DpDatCom_PopIntro(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnDAT_ComPrGet_Value(iIt);
	S32 min = -1, max = -1;
	I08 pSt0[32] = {0, };
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);
	U08 fDp = _F_T;

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			_SPRINTF(pSt0, lDpDat.sIt1[iIt]);
			break;
		case MnSYS_LANG_ENG:
			_SPRINTF(pSt0, lDpDat.sIt1[iIt]);
			break;
	}


	DpPOP_UdtTitle(pSt0);

	// Old Value
	if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_MDB)
	{
		switch(iIt)
		{
			case MnDS1_OPT_TYPE:
				switch(val)
				{
					case MnDS1_TYPE_MDB:		_SPRINTF(pSt0, _sCOM_Mdb);	break;
					case MnDS1_TYPE_RF:			_SPRINTF(pSt0, "RF");	break;
					default:					_SPRINTF(pSt0, _sNG);		break;
				}
				break;
			case MnDS1_OPT_BAUD:
				switch(val)
				{
					case MnDS1_BAUDRATE_9600:	_SPRINTF(pSt0, _sCOM_Br9600);	break;
					case MnDS1_BAUDRATE_19200:	_SPRINTF(pSt0, _sCOM_Br19200);	break;
					case MnDS1_BAUDRATE_115200:	_SPRINTF(pSt0, _sCOM_Br115200);	break;
					default:					_SPRINTF(pSt0, _sNG);			break;
				}
				break;
			case MnDS1_OPT_ADDR:			_SPRINTF(pSt0, "%d", val);		break;
			default:						_SPRINTF(pSt0, _sNG);			break;
		}	
		DpPOP_UdtOldVl(pSt0);
	}

	if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_RF)
	{
		switch(iIt)
		{
			case MnDS1_OPT_TYPE:
				switch(val)
				{
					case MnDS1_TYPE_MDB:		_SPRINTF(pSt0, _sCOM_Mdb);	break;
					case MnDS1_TYPE_RF: 		_SPRINTF(pSt0, "RF");	break;
					default:					_SPRINTF(pSt0, _sNG);		break;
				}
				DpPOP_UdtOldVl(pSt0);
				break;
			case MnDS1_OPT_RF_CH1_ASSIGN:
			case MnDS1_OPT_RF_CH2_ASSIGN:
				if(lang==MnSYS_LANG_KOR)
				{
					switch(val)
					{
						case MnDS1_ASSIGN_LIGHT: 	 DpSTR_GuiList(TEXT_LIST_LIGHT);									break;
						case MnDS1_ASSIGN_HEAVY:	 DpSTR_GuiList(TEXT_LIST_HEAVY);									break;
						default:					break;
					}																			
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE17HsBKOR,  gDpStr.Text_list);
					break;
				}
				else
				{
					switch(val)
					{
						case MnDS1_ASSIGN_LIGHT:	_SPRINTF(pSt0, _sLight);	break;
						case MnDS1_ASSIGN_HEAVY:	_SPRINTF(pSt0, _sHeavy);	break;
						default:					_SPRINTF(pSt0, _sNG);		break;
					}
					DpPOP_UdtOldVl(pSt0);
				}
				break;
			case MnDS1_OPT_RF_CH1_ADDRESS:	
			case MnDS1_OPT_RF_CH2_ADDRESS:		
				_SPRINTF(pSt0, "%d", val);		
				DpPOP_UdtOldVl(pSt0);
				break;
			default:						_SPRINTF(pSt0, _sNG);			break;
		}	
	}

	

	// Range (Min. / Max.)
	if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_MDB)
	{	
		switch(iIt)
		{
			case MnDS1_OPT_TYPE:		min = MnDS1_TYPE_MIN;		max = MnDS1_TYPE_MAX;		fDp = _F_F;	break;
			case MnDS1_OPT_BAUD:		min = MnDS1_BAUDRATE_MIN;	max = MnDS1_BAUDRATE_MAX;					break;
			case MnDS1_OPT_ADDR:		min = MnDS1_ADDRESS_MIN;	max = MnDS1_ADDRESS_MAX;					break;
			default:					break;
		}

		switch(iIt)
		{
			case MnDS1_OPT_TYPE:
				switch(min)
				{
					case MnDS1_TYPE_MDB:	_SPRINTF(pSt0, _sCOM_Mdb);		break;
					default:				_SPRINTF(pSt0, _sNG);			break;
				}
				break;
			case MnDS1_OPT_BAUD:
				switch(min)
				{
					case MnDS1_BAUDRATE_9600:	_SPRINTF(pSt0, _sCOM_Br9600);	break;
					case MnDS1_BAUDRATE_19200:	_SPRINTF(pSt0, _sCOM_Br19200);	break;
					case MnDS1_BAUDRATE_115200:	_SPRINTF(pSt0, _sCOM_Br115200);	break;
					default:					_SPRINTF(pSt0, _sNG);			break;
				}
				break;
			case MnDS1_OPT_ADDR:		_SPRINTF(pSt0, "%d", min);		break;
			default:					break;
		}
		if(fDp) DpPOP_UdtRangeMin(pSt0);

		switch(iIt)
		{
			case MnDS1_OPT_TYPE:
				switch(max)
				{
					case MnDS1_TYPE_MDB:	_SPRINTF(pSt0, _sCOM_Mdb);		break;
					default:				_SPRINTF(pSt0, _sNG);			break;
				}
				break;
			case MnDS1_OPT_BAUD:
				switch(max)
				{
					case MnDS1_BAUDRATE_9600:	_SPRINTF(pSt0, _sCOM_Br9600);	break;
					case MnDS1_BAUDRATE_19200:	_SPRINTF(pSt0, _sCOM_Br19200);	break;
					case MnDS1_BAUDRATE_115200:	_SPRINTF(pSt0, _sCOM_Br115200);	break;
					default:					_SPRINTF(pSt0, _sNG);			break;
				}
				break;
			case MnDS1_OPT_ADDR:		_SPRINTF(pSt0, "%d", max);		break;
			default:					break;
		}

		if(fDp) DpPOP_UdtRangeMax(pSt0);
	}

	if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_RF)
	{
		switch(iIt)
		{
			case MnDS1_OPT_TYPE:
			case MnDS1_OPT_RF_CH1_ASSIGN:
			case MnDS1_OPT_RF_CH2_ASSIGN:
				fDp = _F_F;
				break;
			case MnDS1_OPT_RF_CH1_ADDRESS:
			case MnDS1_OPT_RF_CH2_ADDRESS:
				min = MnDS1_RF_ADDRESS_MIN;	max = MnDS1_RF_ADDRESS_MAX;				
				break;
			default:					break;
		}


		if(iIt==MnDS1_OPT_RF_CH1_ADDRESS)
			_SPRINTF(pSt0, "%d", min);
		if(iIt==MnDS1_OPT_RF_CH2_ADDRESS)
			_SPRINTF(pSt0, "%d", min);

		if(fDp) DpPOP_UdtRangeMin(pSt0);
		
		if(iIt==MnDS1_OPT_RF_CH1_ADDRESS)
			_SPRINTF(pSt0, "%d", max);
		if(iIt==MnDS1_OPT_RF_CH2_ADDRESS)
			_SPRINTF(pSt0, "%d", max);

		
		if(fDp) DpPOP_UdtRangeMax(pSt0);
	}

	// Explanation
	_SPRINTF(pSt0, _sSel_PsSet);

	DpPOP_UdtExpla(pSt0);	
}

void DpDatCom_PopUpdat(void)
{
	U16 x0 = DpPOP_CT1_X0;
	U16 y0 = DpPOP_CT1_Y0;
	U32 cBg = _cPOP_BG_WND;
	I08 pSt0[16] = {0, };
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnLY3_GetValue();

	if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_MDB)
	{
		switch(iIt)
		{
			case MnDS1_OPT_TYPE:
				switch(val)
				{
					case MnDS1_TYPE_MDB:	_SPRINTF(pSt0, _sCOM_Mdb);		break;
					case MnDS1_TYPE_RF:		_SPRINTF(pSt0, "RF");		break;	
					default:				_SPRINTF(pSt0, _sNG);			break;
				}
				break;
			case MnDS1_OPT_BAUD:
				switch(val)
				{
					case MnDS1_BAUDRATE_9600:	_SPRINTF(pSt0, _sCOM_Br9600);	break;
					case MnDS1_BAUDRATE_19200:	_SPRINTF(pSt0, _sCOM_Br19200);	break;
					case MnDS1_BAUDRATE_115200:	_SPRINTF(pSt0, _sCOM_Br115200);	break;
					default:					_SPRINTF(pSt0, _sNG);			break;
				}
				break;
				break;
			case MnDS1_OPT_ADDR:		_SPRINTF(pSt0, "%d", val);			break;
			default:					return;
		}
		DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
		DpSTR_GuiLeft(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsB, pSt0);		
	}
	if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_RF)
	{
		switch(iIt)
		{
			case MnDS1_OPT_TYPE:
				switch(val)
				{
					case MnDS1_TYPE_MDB:	_SPRINTF(pSt0, _sCOM_Mdb);		break;
					case MnDS1_TYPE_RF: 	_SPRINTF(pSt0, "RF");			break;	
					default:				_SPRINTF(pSt0, _sNG);			break;
				}
				DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
				DpSTR_GuiLeft(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsB, pSt0);

				break;
			case MnDS1_OPT_RF_CH1_ASSIGN:
			case MnDS1_OPT_RF_CH2_ASSIGN:
				if(lang==MnSYS_LANG_KOR)
				{
					switch(val)
					{
						case MnDS1_ASSIGN_LIGHT:	 DpSTR_GuiList(TEXT_LIST_LIGHT);									break;
						case MnDS1_ASSIGN_HEAVY:	 DpSTR_GuiList(TEXT_LIST_HEAVY);									break;
						default:					break;
					}														
					DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
					DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE17HsBKOR, gDpStr.Text_list);
					break;
				}
				else
				{
					switch(val)
					{
						case MnDS1_ASSIGN_LIGHT:	_SPRINTF(pSt0, _sLight);	break;
						case MnDS1_ASSIGN_HEAVY:	_SPRINTF(pSt0, _sHeavy);	break;
						default:					_SPRINTF(pSt0, _sNG);		break;
					}
					DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
					DpSTR_GuiLeft(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsB, pSt0);
				}
				break;
			case MnDS1_OPT_RF_CH1_ADDRESS:		
			case MnDS1_OPT_RF_CH2_ADDRESS:
				_SPRINTF(pSt0, "%d", val);	
				DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
				DpSTR_GuiLeft(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsB, pSt0);
				break;
			default:					return;
		}
	}

}
//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get (Set)
I08* DpDAT_GetAddrSct(U08 idx)		{	return lDpDat.sSct[idx];			}
I08* DpDAT_GetAddrIt0(U08 idx)		{	return lDpDat.sIt0[idx];			}
I08* DpDAT_GetAddrVl0(U08 idx)		{	return lDpDat.sVl0[idx];			}
I08* DpDAT_GetAddrIt1(U08 idx)		{	return lDpDat.sIt1[idx];			}
I08* DpDAT_GetAddrVl1(U08 idx)		{	return lDpDat.sVl1[idx];			}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Additional
//------------------------------------------------------------------------------------------------------------------------------
void DpDAT_AddUpdat(void)
{	
	U16 x0 = DpPOP_CT1_X0;
	U16 y0 = DpPOP_CT1_Y0;
	U32 cBg = _cPOP_BG_WND;
	I08 pSt0[16] = {0, };

	DpFIG_DrwRect(DpPOP_CT1_X0-5,	DpPOP_CT2_Y0, 200, 40, _cPOP_BG_WND, DpFIG_FILL);		// Clear
	_SPRINTF(pSt0, "Loading...");	
	//_SPRINTF(pSt0, "%d %%", MnLy4_GetPercent());	
	DpFIG_DrwRect(DpPOP_EXP_X0-5,	DpPOP_EXP_Y0, 400, 20,_cPOP_BG_WND, DpFIG_FILL);		// Clear
	DpPOP_UdtExpla(_sExit_Prskey);

	#if 1
	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpSTR_GuiLeft(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsB, pSt0);
	#endif

}

void DpDAT_AddIntro(void)
{
	DpDAT_PopIntro();
	DpDAT_AddUpdat();
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Pop-Up
//------------------------------------------------------------------------------------------------------------------------------
#if 1
void DpDAT_PopUpdat(void)
{
	U08 iSb = MnLY1_GetSection();

	switch(iSb)
	{
		case MnDAT_SUB_SAVE:	DpDatSav_PopUpdat();	break;
		case MnDAT_SUB_COMM:	DpDatCom_PopUpdat();	break;
		// Not Yet
		default:
			break;		
	}
}

void DpDAT_PopIntro(void)
{
	#if 1
	U08 iSb = MnLY1_GetSection();

	switch(iSb)
	{
		case MnDAT_SUB_SAVE:	DpDatSav_PopIntro();	break;
		case MnDAT_SUB_COMM:	DpDatCom_PopIntro();	break;
		// Not Yet
		default:
			break;		
	}
	#else
	U08 iSb = MnLY1_GetSection();
	U08 iIt = MnLY2_GetIdxItem();

	switch(iSb)
	{
		case MnDAT_S00_SAVE:
			switch(iIt)
			{
				case MnDS0_I00_fEN:		_SPRINTF(lDpDat.pStr, _sSAV_En);		break;
				case MnDS0_I01_INTV:	_SPRINTF(lDpDat.pStr, _sSAV_Intv);		break;
				case MnDS0_I02_DOWN:	_SPRINTF(lDpDat.pStr, _sSAV_Down);		break;
				case MnDS0_I03_DEL:		_SPRINTF(lDpDat.pStr, _sSAV_Del);		break;
				default:				_SPRINTF(lDpDat.pStr, _sNG);			break;
			}
			break;
		case MnDAT_S01_COMM:
			switch(iIt)
			{
				case MnDS1_I00_TYPE:	_SPRINTF(lDpDat.pStr, _sCOM_Type);		break;
				case MnDS1_I01_BAUD:	_SPRINTF(lDpDat.pStr, _sCOM_Baud);		break;
				case MnDS1_I02_ADDR:	_SPRINTF(lDpDat.pStr, _sCOM_Addr);		break;
				default:				_SPRINTF(lDpDat.pStr, _sNG);			break;
			}
			break;
		// Not Yet
		default:							break;		
	}
	#endif
	// Update API
	DpDAT_PopUpdat();
}

#else
void DpDAT_PopUpdat(void)
{

}

void DpDAT_PopIntro(void)
{
	// Title
	switch(MnLY2_GetIdxItem())
	{
		case MnDAT_I00_fSAV:		_SPRINTF(lDpDat.sTtl, _sSAVE);			break;
		case MnDAT_I01_INTV:		_SPRINTF(lDpDat.sTtl, _sINTV);			break;
		default:					_SPRINTF(lDpDat.sTtl, _sNG);			break;;
	}

	DpPOP_UdtTitle(lDpDat.sTtl);
}
#endif

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void DpDAT_InitVari(void)
{
	//U08 i;
	S32 val = 0;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			DpSTR_GuiList(TEXT_LIST_SAVE);
			_SPRINTF(lDpDat.sSct[MnDAT_SUB_SAVE], 	 gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_COMM);
			_SPRINTF(lDpDat.sSct[MnDAT_SUB_COMM], 	 gDpStr.Text_list);
			// Item (S0 - Save)
			DpSTR_GuiList(TEXT_LIST_INTV);
			_SPRINTF(lDpDat.sIt0[MnDS0_OPT_INTERVAL], 	 	gDpStr.Text_list);
			DpDAT_SetKorExportLabels();
			DpSTR_GuiList(TEXT_LIST_DELETE);
			_SPRINTF(lDpDat.sIt0[MnDS0_OPT_DELETE],  	 	gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_DISPLAY_TERM);
			_SPRINTF(lDpDat.sIt0[MnDS0_OPT_DISPLAY_TERM],  	gDpStr.Text_list);
			// Item (S1 - Communication)
			DpSTR_GuiList(TEXT_LIST_PROTOCL);
			_SPRINTF(lDpDat.sIt1[MnDS1_OPT_TYPE], 	 gDpStr.Text_list);
			if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_MDB)
			{
				DpSTR_GuiList(TEXT_LIST_BAUDRATE);
				_SPRINTF(lDpDat.sIt1[MnDS1_OPT_BAUD], 	 gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_ADDRESS);
				_SPRINTF(lDpDat.sIt1[MnDS1_OPT_ADDR], 	 gDpStr.Text_list);			
			}
			else if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_RF)
			{
				if(MnFTR_PrGet_SsChn()== MnFTR_SS_DUAL)
				{
					DpSTR_GuiList(TEXT_LIST_CH1_ASSIGN);
					_SPRINTF(lDpDat.sIt1[MnDS1_OPT_RF_CH1_ASSIGN],	 gDpStr.Text_list);
					DpSTR_GuiList(TEXT_LIST_CH1_ADDRESS);
					_SPRINTF(lDpDat.sIt1[MnDS1_OPT_RF_CH1_ADDRESS],	 gDpStr.Text_list); 	
					DpSTR_GuiList(TEXT_LIST_CH2_ASSIGN);
					_SPRINTF(lDpDat.sIt1[MnDS1_OPT_RF_CH2_ASSIGN],	 gDpStr.Text_list);
					DpSTR_GuiList(TEXT_LIST_CH2_ADDRESS);
					_SPRINTF(lDpDat.sIt1[MnDS1_OPT_RF_CH2_ADDRESS],  gDpStr.Text_list); 
				}
				else if(MnFTR_PrGet_SsChn()== MnFTR_SS_SINGLE)
				{
					DpSTR_GuiList(TEXT_LIST_ASSIGN);
					_SPRINTF(lDpDat.sIt1[MnDS1_OPT_RF_CH1_ASSIGN],	 gDpStr.Text_list);
					DpSTR_GuiList(TEXT_LIST_ADDRESS);
					_SPRINTF(lDpDat.sIt1[MnDS1_OPT_RF_CH1_ADDRESS],  gDpStr.Text_list); 	
				}
			}
			break;			
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpDat.sSct[MnDAT_SUB_SAVE], 	 _sSave);
			_SPRINTF(lDpDat.sSct[MnDAT_SUB_COMM], 	 _sCmnctn);
			// Item (S0 - Save)
			_SPRINTF(lDpDat.sIt0[MnDS0_OPT_INTERVAL], 	 	_sSAV_Intv);
			_SPRINTF(lDpDat.sIt0[MnDS0_OPT_EXPORT_USB], 	"Export (USB)");
			_SPRINTF(lDpDat.sIt0[MnDS0_OPT_DOWNLOAD], 	 	"Export (RS485)");
			_SPRINTF(lDpDat.sIt0[MnDS0_OPT_DELETE],  	 	_sSAV_Del);
			_SPRINTF(lDpDat.sIt0[MnDS0_OPT_DISPLAY_TERM],  	_sDisplay_term);
			// Item (S1 - Communication)
			_SPRINTF(lDpDat.sIt1[MnDS1_OPT_TYPE], 	 _sCOM_Protocol);
			if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_MDB)
			{ 
				_SPRINTF(lDpDat.sIt1[MnDS1_OPT_BAUD], 	 _sCOM_Baud);
				_SPRINTF(lDpDat.sIt1[MnDS1_OPT_ADDR], 	 _sCOM_Addr);			
			}
			else if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_RF)
			{
				if(MnFTR_PrGet_SsChn()== MnFTR_SS_DUAL)
				{
					_SPRINTF(lDpDat.sIt1[MnDS1_OPT_RF_CH1_ASSIGN],	 _sCH1_Assign);
					_SPRINTF(lDpDat.sIt1[MnDS1_OPT_RF_CH2_ASSIGN],	 _sCH2_Assign);
					_SPRINTF(lDpDat.sIt1[MnDS1_OPT_RF_CH1_ADDRESS],	 _sCH1_Address);
					_SPRINTF(lDpDat.sIt1[MnDS1_OPT_RF_CH2_ADDRESS],	 _sCH2_Address);
				}
				else if(MnFTR_PrGet_SsChn()== MnFTR_SS_SINGLE)
				{
					_SPRINTF(lDpDat.sIt1[MnDS1_OPT_RF_CH1_ASSIGN],	 _sAssign);
					_SPRINTF(lDpDat.sIt1[MnDS1_OPT_RF_CH1_ADDRESS],  _sAddress);
				}
			}
			break;
		default:
			break;
	}

	switch(MnDAT_SavPrGet_Value(MnDS0_OPT_INTERVAL))
	{
		case MnDS0_INTV_01S:		_SPRINTF(lDpDat.sVl0[MnDS0_OPT_INTERVAL], _sTim_1Sec);				break;
		case MnDS0_INTV_10S:		_SPRINTF(lDpDat.sVl0[MnDS0_OPT_INTERVAL], _sTim_10Sec);				break;
		case MnDS0_INTV_01M:		_SPRINTF(lDpDat.sVl0[MnDS0_OPT_INTERVAL], _sTim_1Min);				break;
		case MnDS0_INTV_10M:		_SPRINTF(lDpDat.sVl0[MnDS0_OPT_INTERVAL], _sTim_10Min);				break;
		case MnDS0_INTV_01H:		_SPRINTF(lDpDat.sVl0[MnDS0_OPT_INTERVAL], _sTim_1Hrs);				break;
		default:					_SPRINTF(lDpDat.sVl0[MnDS0_OPT_INTERVAL], _sNG);					break;
	}


	switch(MnDAT_SavPrGet_Value(MnDS0_OPT_INTERVAL))
	{
		case MnDS0_INTV_01S:
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_DISPLAY_TERM))
			{
				case MnDS0_DISPLAY_TERM_1:	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DISPLAY_TERM], "12 min");			break;
				case MnDS0_DISPLAY_TERM_2:	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DISPLAY_TERM], "24 min");			break;
			}
			break;
		case MnDS0_INTV_10S:
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_DISPLAY_TERM))
			{
				case MnDS0_DISPLAY_TERM_1:	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DISPLAY_TERM], "2 hour");			break;
				case MnDS0_DISPLAY_TERM_2:	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DISPLAY_TERM], "4 hour");			break;
			}
			break;					
		case MnDS0_INTV_01M:
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_DISPLAY_TERM))
			{
				case MnDS0_DISPLAY_TERM_1:	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DISPLAY_TERM], _sTim_12Hrs);			break;
				case MnDS0_DISPLAY_TERM_2:	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DISPLAY_TERM], _sTim_24Hrs);			break;
			}
			break;					
		case MnDS0_INTV_10M:
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_DISPLAY_TERM))
			{
				case MnDS0_DISPLAY_TERM_1:	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DISPLAY_TERM], _sTim_5Day); 		break;
				case MnDS0_DISPLAY_TERM_2:	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DISPLAY_TERM], _sTim_10Day); 		break;
			}
			break;					
		case MnDS0_INTV_01H:
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_DISPLAY_TERM))
			{
				case MnDS0_DISPLAY_TERM_1:	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DISPLAY_TERM], _sTim_30Day);			break;
				case MnDS0_DISPLAY_TERM_2:	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DISPLAY_TERM], _sTim_60Day);			break;
			}
			break;					
		default:					
			_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DISPLAY_TERM], _sNG);						
			break;
	}
	
	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_EXPORT_USB], 	"-");
	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DOWNLOAD], 	"-");
	_SPRINTF(lDpDat.sVl0[MnDS0_OPT_DELETE], 	"-");
	// Value (S1 - Communication)


	switch(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE))
	{
		case MnDS1_TYPE_MDB:		_SPRINTF(lDpDat.sVl1[MnDS1_OPT_TYPE], _sCOM_Mdb);	break;
		case MnDS1_TYPE_RF: 		_SPRINTF(lDpDat.sVl1[MnDS1_OPT_TYPE], "RF");		break;
		default:					_SPRINTF(lDpDat.sVl1[MnDS1_OPT_TYPE], _sNG);			break;
	}


	if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_MDB)
	{
		switch(MnDAT_ComPrGet_Value(MnDS1_OPT_BAUD))
		{
			case MnDS1_BAUDRATE_9600:	_SPRINTF(lDpDat.sVl1[MnDS1_OPT_BAUD], _sCOM_Br9600);	break;
			case MnDS1_BAUDRATE_19200:	_SPRINTF(lDpDat.sVl1[MnDS1_OPT_BAUD], _sCOM_Br19200);	break;
			case MnDS1_BAUDRATE_115200:	_SPRINTF(lDpDat.sVl1[MnDS1_OPT_BAUD], _sCOM_Br115200);	break;
			default:					_SPRINTF(lDpDat.sVl1[MnDS1_OPT_BAUD], _sNG);			break;
		}
		val = MnDAT_ComPrGet_Value(MnDS1_OPT_ADDR);	_SPRINTF(lDpDat.sVl1[MnDS1_OPT_ADDR], " %d", (U16)val);
	}
	else if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_RF)
	{
		if(MnDAT_ComPrGet_Value(MnDS1_OPT_RF_CH1_ASSIGN)==MnDS1_ASSIGN_LIGHT)
		{
			if(lang==MnSYS_LANG_KOR)
			{
				DpSTR_GuiList(TEXT_LIST_LIGHT);
				_SPRINTF(lDpDat.sVl1[MnDS1_OPT_RF_CH1_ASSIGN],  	gDpStr.Text_list);	
			}
			else
				_SPRINTF(lDpDat.sVl1[MnDS1_OPT_RF_CH1_ASSIGN], _sLight);
		}
		if(MnDAT_ComPrGet_Value(MnDS1_OPT_RF_CH1_ASSIGN)==MnDS1_ASSIGN_HEAVY)
		{
			if(lang==MnSYS_LANG_KOR)
			{
				DpSTR_GuiList(TEXT_LIST_HEAVY);
				_SPRINTF(lDpDat.sVl1[MnDS1_OPT_RF_CH1_ASSIGN],  	gDpStr.Text_list);	
			}
			else
				_SPRINTF(lDpDat.sVl1[MnDS1_OPT_RF_CH1_ASSIGN], _sHeavy);
		}	

		if(MnDAT_ComPrGet_Value(MnDS1_OPT_RF_CH2_ASSIGN)==MnDS1_ASSIGN_LIGHT)
		{
			if(lang==MnSYS_LANG_KOR)
			{
				DpSTR_GuiList(TEXT_LIST_LIGHT);
				_SPRINTF(lDpDat.sVl1[MnDS1_OPT_RF_CH2_ASSIGN],  	gDpStr.Text_list);	
			}
			else
				_SPRINTF(lDpDat.sVl1[MnDS1_OPT_RF_CH2_ASSIGN], _sLight);
		}
		if(MnDAT_ComPrGet_Value(MnDS1_OPT_RF_CH2_ASSIGN)==MnDS1_ASSIGN_HEAVY)
		{
			if(lang==MnSYS_LANG_KOR)
			{
				DpSTR_GuiList(TEXT_LIST_HEAVY);
				_SPRINTF(lDpDat.sVl1[MnDS1_OPT_RF_CH2_ASSIGN],  	gDpStr.Text_list);	
			}
			else
				_SPRINTF(lDpDat.sVl1[MnDS1_OPT_RF_CH2_ASSIGN], _sHeavy);
		}	

		val = MnDAT_ComPrGet_Value(MnDS1_OPT_RF_CH1_ADDRESS); _SPRINTF(lDpDat.sVl1[MnDS1_OPT_RF_CH1_ADDRESS], " %d", (U16)val);
		val = MnDAT_ComPrGet_Value(MnDS1_OPT_RF_CH2_ADDRESS); _SPRINTF(lDpDat.sVl1[MnDS1_OPT_RF_CH2_ADDRESS], " %d", (U16)val);
	}

	_MEMSET(lDpDat.pStr, 0, sizeof(lDpDat.pStr));
}

void DpDT1_StrSbSct(void)
{
	U08 i=0;
	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			for(i=0; i<MnDAT_SUB_NUM; i++)
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, lDpDat.sSct[i]);
			break;			
		case MnSYS_LANG_ENG:
			for(i=0; i<MnDAT_SUB_NUM; i++)
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, lDpDat.sSct[i]);
			break;

	}
}

void DpDAT_StrCntts(U08 idx)
{
	U08 i, n = 0;
	I08 *pItm, *pVal;
	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 box_val_x0 = DpMNU_STR_X0_VAL;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 iIt = MnLY2_GetIdxItem();
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);	
	U08 sel;
	U64 back_color = _cMNU_BOX_BG;
	U64 text_color = _cMNU_STR_IDLE;

	switch(idx)
	{
		case MnDAT_SUB_SAVE:		n = MnDS0_OPT_NUM;			break;
		case MnDAT_SUB_COMM:		
			if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_MDB)
				n = MnDS1_OPT_NUM;			
			else if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_RF)
			{
				if(MnFTR_PrGet_SsChn()== MnFTR_SS_DUAL)
					n = MnDS1_OPT_RF_NUM;	
				else if(MnFTR_PrGet_SsChn()== MnFTR_SS_SINGLE)
					n = MnDS1_OPT_RF_SINGLE_MAX+1;
			}
			break;
		default:					return;
	}
	sel = (iIt%DpMNU_ITM_PAGE);

	for(i=0; i<n; i++)
	{
		switch(idx)
		{
			case MnDAT_SUB_SAVE: 	pItm = lDpDat.sIt0[i];		pVal = lDpDat.sVl0[i];	break;
			case MnDAT_SUB_COMM:	pItm = lDpDat.sIt1[i];		pVal = lDpDat.sVl1[i];	break;
			default:				return;
		}

		DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, str_y0+(str_yg*i)+15, DpMNU_BOX_WID-30-60, 37, _cMNU_BOX_BG, DpFIG_FILL);

		if(MENU_GetLayer()>=MENU_L2_ITEM)
		{
			if(i==sel)
			{
				back_color = _cMNU_SEL_ITM;
				text_color = _cSD_DARKGRAY;
			}
			else
			{
				back_color = _cMNU_BOX_BG;
				text_color = _cMNU_STR_IDLE;
		
			}
		}

		switch(lang)
		{
			case MnSYS_LANG_KOR:
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, pItm);
				if(idx==MnDAT_SUB_COMM)
				{
					if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_MDB)	
						DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
					if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_RF)
					{
						if((i==MnDS1_OPT_RF_CH1_ASSIGN) || (i==MnDS1_OPT_RF_CH2_ASSIGN))
							DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, pVal);
						else
							DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
					}
				}
				break;				
			case MnSYS_LANG_ENG:
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsB, pItm);
				DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
				break;
		}

	}
}

//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

