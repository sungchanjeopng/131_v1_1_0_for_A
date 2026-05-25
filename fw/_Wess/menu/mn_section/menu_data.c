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
#include "bsp_uart.h"
#include "bsp_usb.h"
// app
#include "app_main.h"
// menu
#include "menu_main.h"
#include "menu_lyr0_section.h"
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
#include "menu_lyr4_addition.h"
// self
#include "menu_data.h"
#include "disp_popup.h"
// function
#include "data_save.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnDAT_LS lMnDat;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
void DatComPr_BaudInit(U08 val)
{
	switch(val)
	{
		case MnDS1_BAUDRATE_9600:	URT_InitMain(URT_IDX_2, 9600);		break;
		case MnDS1_BAUDRATE_19200:	URT_InitMain(URT_IDX_2, 19200); 	break;
		case MnDS1_BAUDRATE_115200:	URT_InitMain(URT_IDX_2, 115200);	break;
		default:
			break;
	}
}


static void DatSave_ExportUsb(void)
{
	I08 filename[BspUsb_FILENAME_MAX] = {0, };
	I08 msg[64] = {0, };
	U08 ret;

	DpPOP_DrwUsbExportMsg((I08*)"Exporting trend data...", (I08*)"Please wait");
	ret = DaSAV_UsbExportCsv(filename, sizeof(filename));

	switch(ret)
	{
		case BspUsb_FILE_OK:
			DpPOP_DrwUsbExportMsg((I08*)"Saved to USB memory.", filename);
			break;
		case BspUsb_FILE_NO_USB:
			DpPOP_DrwUsbExportMsg((I08*)"Insert USB memory.", (I08*)"No USB");
			break;
		case BspUsb_FILE_DISK_FULL:
			DpPOP_DrwUsbExportMsg((I08*)"Insufficient disk space.", (I08*)"Check USB memory");
			break;
		case BspUsb_FILE_OPEN_FAIL:
			DpPOP_DrwUsbExportMsg((I08*)"File open failed.", (I08*)"Format USB as FAT32");
			break;
		case BspUsb_FILE_WRITE_FAIL:
			DpPOP_DrwUsbExportMsg((I08*)"File write failed.", (I08*)"Do not remove USB");
			break;
		case BspUsb_FILE_CLOSE_FAIL:
			DpPOP_DrwUsbExportMsg((I08*)"File close failed.", (I08*)"Try again");
			break;
		default:
			_SPRINTF(msg, "Error code: %u", ret);
			DpPOP_DrwUsbExportMsg((I08*)"Export failed.", msg);
			break;
	}

	HAL_Delay(1800);
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
S32 MnDAT_SavPrGet_Value(U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iIt)
	{
		case MnDS0_OPT_INTERVAL:		val = lMnDat.mSavPr.intv;			break;
		case MnDS0_OPT_EXPORT_USB:	val = 0;						break;
		case MnDS0_OPT_DOWNLOAD:		val = MnDS0_DOWN_CH1_LIGHT;			break;
		case MnDS0_OPT_DELETE:			val = MnDS0_DELETE_NO;				break;
		case MnDS0_OPT_DISPLAY_TERM:	val = lMnDat.mSavPr.display_term;	break;
		default:				break;
	}

	return val;
}

S32 MnDAT_ComPrGet_Value(U08 iIt)
{
	S32 val = MENU_VAL_INVALID;


	if(lMnDat.mComPr.type == MnDS1_TYPE_MDB)
	{
		switch(iIt)
		{
			case MnDS1_OPT_TYPE:	val = lMnDat.mComPr.type;		break;
			case MnDS1_OPT_BAUD:	val = lMnDat.mComPr.baud;		break;
			case MnDS1_OPT_ADDR:	val = lMnDat.mComPr.addr;		break;
			default:				break;
		}
	}
	else if(lMnDat.mComPr.type == MnDS1_TYPE_RF)
	{
		switch(iIt)
		{
			case MnDS1_OPT_RF_TYPE:			val = lMnDat.mComPr.type;					break;
			case MnDS1_OPT_RF_CH1_ASSIGN:	val = lMnDat.mComPr.rf_assign[APP_CH_1];	break;
			case MnDS1_OPT_RF_CH1_ADDRESS:	val = lMnDat.mComPr.rf_addr[APP_CH_1];		break;
			case MnDS1_OPT_RF_CH2_ASSIGN:	val = lMnDat.mComPr.rf_assign[APP_CH_2];	break;
			case MnDS1_OPT_RF_CH2_ADDRESS:	val = lMnDat.mComPr.rf_addr[APP_CH_2];		break;
			default:				break;
		}
	}
	
	return val;
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
void MnDAT_SavPrSet_Value(U08 iIt, S32 val)
{
	switch(iIt)
	{
		case MnDS0_OPT_INTERVAL:
			if(lMnDat.mSavPr.intv!= val)
				DaSAV_DeleteData();
			lMnDat.mSavPr.intv 	 = val;			
			MnLY3_GotoLyr2();			
			break;
		case MnDS0_OPT_EXPORT_USB:
			DatSave_ExportUsb();
			MnLY3_GotoLyr2();
			break;
		case MnDS0_OPT_DOWNLOAD:
			DaSAV_DumpInit();
			lMnDat.f_save = FALSE;
			
			MnLy3Act_GotoLyr4();
			break;
		case MnDS0_OPT_DELETE:		
			switch(val)
			{
				case MnDS0_DELETE_YES:
					DaSAV_DeleteData();	
					MnLY3_GotoLyr2();
					break;
				case MnDS0_DELETE_NO:
					MnLY3_GotoLyr2();			
					break;
				default:
					break;
			}
			break;
		case MnDS0_OPT_DISPLAY_TERM:	lMnDat.mSavPr.display_term  = val;		MnLY3_GotoLyr2();	break;
	}

	switch(iIt)
	{
		case MnDS0_OPT_INTERVAL:		MRM_WrByte(_mSAVE_INTV, lMnDat.mSavPr.intv);				break;
		case MnDS0_OPT_DISPLAY_TERM:	MRM_WrByte(_mDISPLAY_TERM, lMnDat.mSavPr.display_term);		break;
		default:						break;
	}
}

void MnDAT_ComPrSet_Value(U08 iIt, S32 val)
{
	if(lMnDat.mComPr.type == MnDS1_TYPE_MDB)
	{
		switch(iIt)
		{
			case MnDS1_OPT_TYPE:	lMnDat.mComPr.type = val;														break;
			case MnDS1_OPT_BAUD:	lMnDat.mComPr.baud = val;		DatComPr_BaudInit(lMnDat.mComPr.baud);			break;
			case MnDS1_OPT_ADDR:	lMnDat.mComPr.addr = val;														break;
		}

		switch(iIt)
		{
			case MnDS1_OPT_TYPE:	MRM_WrByte(_mDATA_Protocol, lMnDat.mComPr.type);		break;
			case MnDS1_OPT_BAUD:	MRM_WrByte(_mDATA_BAUD, lMnDat.mComPr.baud);			break;
			case MnDS1_OPT_ADDR:	MRM_WrWord(_mDATA_ADDRESS_L, lMnDat.mComPr.addr);		break;
		}
	}
	else if(lMnDat.mComPr.type == MnDS1_TYPE_RF)
	{
		switch(iIt)
		{
			case MnDS1_OPT_RF_TYPE:			lMnDat.mComPr.type = val;						break;
			case MnDS1_OPT_RF_CH1_ASSIGN:	lMnDat.mComPr.rf_assign[APP_CH_1] = val;		break;
			case MnDS1_OPT_RF_CH1_ADDRESS:	lMnDat.mComPr.rf_addr[APP_CH_1] = val;			break;
			case MnDS1_OPT_RF_CH2_ASSIGN:	lMnDat.mComPr.rf_assign[APP_CH_2] = val;		break;
			case MnDS1_OPT_RF_CH2_ADDRESS:	lMnDat.mComPr.rf_addr[APP_CH_2] = val;			break;
		}
		
		switch(iIt)
		{
			case MnDS1_OPT_RF_TYPE:			MRM_WrByte(_mDATA_Protocol, lMnDat.mComPr.type);					break;
			case MnDS1_OPT_RF_CH1_ASSIGN:	MRM_WrByte(_mRF_CH1_ASSIGN, lMnDat.mComPr.rf_assign[APP_CH_1]);		break;
			case MnDS1_OPT_RF_CH1_ADDRESS:	MRM_WrWord(_mRF_CH1_ADDR_L, lMnDat.mComPr.rf_addr[APP_CH_1]);		break;
			case MnDS1_OPT_RF_CH2_ASSIGN:	MRM_WrByte(_mRF_CH2_ASSIGN, lMnDat.mComPr.rf_assign[APP_CH_2]);		break;
			case MnDS1_OPT_RF_CH2_ADDRESS:	MRM_WrWord(_mRF_CH2_ADDR_L, lMnDat.mComPr.rf_addr[APP_CH_2]);		break;
		}
	}
}
#if 0
void MnDAT_PrSet_Value(S32 val)
{
	U08 iL1 = MnLY1_GetSection();

	switch(iL1)
	{
		case MnDAT_S00_SAVE:	DatSave_PrSet_Value(val);	break;
		case MnDAT_S01_COMM:	DatComm_PrSet_Value(val);	break;
	}
}
#endif
void MnDAT_PrRst_Factory(void)
{
	// Sub-Section #0 (Current)
	MRM_WrByte(_mSAVE_INTV,  	MnDS0_INTV_DEF);
	MRM_WrByte(_mDISPLAY_TERM,  MnDS0_DISPLAY_TERM_DEF);
	// Sub-Section #1 (Communication)
	MRM_WrByte(_mDATA_Protocol,  	MnDS1_TYPE_MDB);
	MRM_WrByte(_mDATA_BAUD,  		MnDS1_BAUDRATE_DEF);
	MRM_WrWord(_mDATA_ADDRESS_L, 	MnDS1_ADDRESS_DEF);

	MRM_WrByte(_mRF_CH1_ASSIGN,  	MnDS1_ASSIGN_DEF);
	MRM_WrByte(_mRF_CH2_ASSIGN,  	MnDS1_ASSIGN_DEF);	
	MRM_WrWord(_mRF_CH1_ADDR_L, 	1);	
	MRM_WrWord(_mRF_CH2_ADDR_L, 	2);	
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 MnDAT_GetLayer(void)			{	return lMnDat.lyr;		}
// Set
void MnDAT_SetLayer(U08 lyr)		{	lMnDat.lyr = lyr;		}
void MnDAT_Set_f_save(U08 sel)	{	lMnDat.f_save=sel;			}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void MnDAT_PrInitMain(void)
{
	// Read Parameters
	// Sub-Section #0 (Current)
	lMnDat.mSavPr.intv	= MRM_RdByte(_mSAVE_INTV);
	lMnDat.mSavPr.display_term 		= MRM_RdByte(_mDISPLAY_TERM);
	lMnDat.f_save      		= FALSE;
	// Sub-Section #1 (Communication)
	lMnDat.mComPr.type 		= MRM_RdByte(_mDATA_Protocol);
	lMnDat.mComPr.baud 		= MRM_RdByte(_mDATA_BAUD);
	lMnDat.mComPr.addr 		= MRM_RdWord(_mDATA_ADDRESS_L);
	lMnDat.mComPr.rf_assign[APP_CH_1]	= MRM_RdByte(_mRF_CH1_ASSIGN);
	lMnDat.mComPr.rf_assign[APP_CH_2]	= MRM_RdByte(_mRF_CH2_ASSIGN);
	lMnDat.mComPr.rf_addr[APP_CH_1]	= MRM_RdWord(_mRF_CH1_ADDR_L);
	lMnDat.mComPr.rf_addr[APP_CH_2]	= MRM_RdWord(_mRF_CH2_ADDR_L);

	if(lMnDat.mSavPr.intv > MnDS0_INTV_MAX)	lMnDat.mSavPr.intv = MnDS0_INTV_DEF;
	if(lMnDat.mSavPr.display_term > MnDS0_DISPLAY_TERM_MAX)	lMnDat.mSavPr.display_term = MnDS0_DISPLAY_TERM_DEF;
	if(lMnDat.mComPr.type > MnDS1_TYPE_MAX) lMnDat.mComPr.type = MnDS1_TYPE_DEF;
	if(lMnDat.mComPr.baud > MnDS1_BAUDRATE_MAX) lMnDat.mComPr.baud = MnDS1_BAUDRATE_DEF;
	if(lMnDat.mComPr.addr > MnDS1_ADDRESS_MAX) lMnDat.mComPr.addr = MnDS1_ADDRESS_DEF;

	if(lMnDat.mComPr.rf_assign[APP_CH_1] > MnDS1_ASSIGN_MAX)	lMnDat.mComPr.rf_assign[APP_CH_1] = MnDS1_ASSIGN_DEF;
	if(lMnDat.mComPr.rf_assign[APP_CH_2] > MnDS1_ASSIGN_MAX)	lMnDat.mComPr.rf_assign[APP_CH_2] = MnDS1_ASSIGN_DEF;

	if(lMnDat.mComPr.rf_addr[APP_CH_1] < MnDS1_RF_ADDRESS_MIN)	lMnDat.mComPr.rf_addr[APP_CH_1] = 1;
	if(lMnDat.mComPr.rf_addr[APP_CH_2] < MnDS1_RF_ADDRESS_MIN)	lMnDat.mComPr.rf_addr[APP_CH_2] = 2;

	if(lMnDat.mComPr.rf_addr[APP_CH_1] > MnDS1_RF_ADDRESS_MAX)	lMnDat.mComPr.rf_addr[APP_CH_1] = 1;
	if(lMnDat.mComPr.rf_addr[APP_CH_2] > MnDS1_RF_ADDRESS_MAX)	lMnDat.mComPr.rf_addr[APP_CH_2] = 2;	
}

void MnDAT_InitMain(void)
{
	lMnDat.lyr = MENU_L0_SECTION;

	MnLY0_InitSection();
	MnLY1_InitSubSct();
	MnLY2_InitItem();
	MnLY3_InitValue();
	MnLY4_InitAddition();

	MnDAT_PrInitMain();
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

