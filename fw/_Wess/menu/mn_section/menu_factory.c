//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2022-01-20 12:00:00 +0900 $ (From 2020-07-13)
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
// bsp
#include "bsp_ram.h"
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
#include "menu_factory.h"
#include "menu_output.h"
#include "menu_engineer.h"
// function
#include "output_current.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnFTR_LS lMnFtr;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameter - Get
//------------------------------------------------------------------------------------------------------------------------------
U08 MnFTR_PrGet_SsChn(void)		{	return lMnFtr.mPr.chnl;		}

/* RF Module Version 저장 (A: menu 옵션 없으므로 RAM에만 유지) */
static U08 lMnFtr_rf_version = MnFTR_RF_VER_DEF;
U08  MnFTR_PrGet_RfVersion(void)		{	return lMnFtr_rf_version;		}
void MnFTR_PrSet_RfVersion(U08 ver)		{	if (ver < MnFTR_RF_VER_NUM) lMnFtr_rf_version = ver;	}

S32 MnFTR_PrGet_Value(U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iIt)
	{
		case MnFTR_I00_SS_CH:			val = lMnFtr.mPr.chnl;						break;
		case MnFTR_I01_CH0_04mA:		val = lMnFtr.mPr.cfg_4mA[MnFTR_CH_0];		break;
		case MnFTR_I02_CH0_20mA:   	 	val = lMnFtr.mPr.cfg_20mA[MnFTR_CH_0];		break;	
		case MnFTR_I03_CH1_04mA:		val = lMnFtr.mPr.cfg_4mA[MnFTR_CH_1];		break;	
		case MnFTR_I04_CH1_20mA:  	  	val = lMnFtr.mPr.cfg_20mA[MnFTR_CH_1];		break;	
		case MnFTR_I05_CH1_TRIM_12MA:	val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH1_TRM_12mA);	break;
		case MnFTR_I06_CH1_TRIM_20MA:	val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH1_TRM_20mA);	break;
		case MnFTR_I07_CH1_OUTPUT_4MA:	break;
		case MnFTR_I08_CH2_TRIM_12MA:	val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH2_TRM_12mA);	break;
		case MnFTR_I09_CH2_TRIM_20MA:	val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH2_TRM_20mA);	break;
		case MnFTR_I10_CH2_OUTPUT_4MA:	break;
		case MnFTR_I11_RELAY_TEST:		val = 0;
		case MnFTR_I12_LANG:			val = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);	break;
		case MnFTR_I13_TIME:			break;
		case MnFTR_I14_VERSION:			break;
		case MnFTR_I15_CLEAN_TEST:		val =0;	break;
		default:						break;
	}
	
	return val;
}

S32 MnFTR_PrGet_CH_Value(U08 ch,U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iIt)
	{
		case MnFTR_OPT_SINGLE_SS_CH:		val = lMnFtr.mPr.chnl;				break;
		case MnFTR_OPT_SINGLE_04mA:			val = lMnFtr.mPr.cfg_4mA[ch];		break;
		case MnFTR_OPT_SINGLE_20mA:   		val = lMnFtr.mPr.cfg_20mA[ch];		break;	
		case MnFTR_OPT_SINGLE_TRIM_12MA:	val = MnOUT_CurPrGet_CH_Value(ch,MnOS0_OPT_SINGLE_TRM_12mA);	break;
		case MnFTR_OPT_SINGLE_TRIM_20MA:	val = MnOUT_CurPrGet_CH_Value(ch,MnOS0_OPT_SINGLE_TRM_20mA);	break;
		case MnFTR_OPT_SINGLE_OUTPUT_4MA:	break;		
		case MnFTR_OPT_SINGLE_RELAY_TEST:	val = 0;
		case MnFTR_OPT_SINGLE_LANG:			val =MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);	break;
		case MnFTR_OPT_SINGLE_TIME:			break;
		case MnFTR_OPT_SINGLE_VERSION:		break;
		case MnFTR_OPT_SINGLE_CLEAN_TEST:	val =0;	break;		

		default:							break;
	}
	
	return val;
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
void MnFTR_PrSet_Value(S32 val)
{
	switch(MnLY2_GetIdxItem())
	{
		case MnFTR_I00_SS_CH:			lMnFtr.mPr.chnl = val;						break;
		case MnFTR_I01_CH0_04mA:		lMnFtr.mPr.cfg_4mA[MnFTR_CH_0] = val;		break;
		case MnFTR_I02_CH0_20mA:		lMnFtr.mPr.cfg_20mA[MnFTR_CH_0] = val;		break;
		case MnFTR_I03_CH1_04mA:		lMnFtr.mPr.cfg_4mA[MnFTR_CH_1] = val;		break;
		case MnFTR_I04_CH1_20mA:		lMnFtr.mPr.cfg_20mA[MnFTR_CH_1] = val;		break;
		case MnFTR_I05_CH1_TRIM_12MA:	MnOUT_CurPrSet_Value(MnOS0_OPT_CH1_TRM_12mA,val);	break;
		case MnFTR_I06_CH1_TRIM_20MA:	MnOUT_CurPrSet_Value(MnOS0_OPT_CH1_TRM_20mA,val);	break;
		case MnFTR_I07_CH1_OUTPUT_4MA:	break;
		case MnFTR_I08_CH2_TRIM_12MA:	MnOUT_CurPrSet_Value(MnOS0_OPT_CH2_TRM_12mA,val);	break;
		case MnFTR_I09_CH2_TRIM_20MA:	MnOUT_CurPrSet_Value(MnOS0_OPT_CH2_TRM_20mA,val);	break;
		case MnFTR_I10_CH2_OUTPUT_4MA:	break;
		case MnFTR_I11_RELAY_TEST:		break;
		case MnFTR_I12_LANG:			MnSYS_PrSetBase_Value(MnSYS_OPT_LANG, val);		break;
		case MnFTR_I13_TIME:			break;
		case MnFTR_I14_VERSION:			break;
		case MnFTR_I15_CLEAN_TEST:		break;
	}

	if(MnLY2_GetIdxItem()==MnFTR_I00_SS_CH)
	{
		if(lMnFtr.mPr.chnl==MnFTR_SS_SINGLE)
			MnEGN_PrSet_Value(MnEGN_OPT_MSR,MnEGN_MSR_OFF);
	}

	switch(MnLY2_GetIdxItem())
	{
		case MnFTR_I00_SS_CH:		MRM_WrByte(_mSENSOR_DUAL_SINGLE, 		lMnFtr.mPr.chnl);			break;
		case MnFTR_I01_CH0_04mA:	MRM_WrWord(_mDAC_CH1_04MA_L, 	lMnFtr.mPr.cfg_4mA[MnFTR_CH_0]);	break;
		case MnFTR_I02_CH0_20mA:	MRM_WrWord(_mDAC_CH1_20MA_L, 	lMnFtr.mPr.cfg_20mA[MnFTR_CH_0]);	break;
		case MnFTR_I03_CH1_04mA:	MRM_WrWord(_mDAC_CH2_04MA_L, 	lMnFtr.mPr.cfg_4mA[MnFTR_CH_1]);	break;
		case MnFTR_I04_CH1_20mA:	MRM_WrWord(_mDAC_CH2_20MA_L, 	lMnFtr.mPr.cfg_20mA[MnFTR_CH_1]);	break;
	}
}

void MnFTR_PrSet_CH_Value(U08 ch,S32 val)
{
	switch(MnLY2_GetIdxItem())
	{
		case MnFTR_OPT_SINGLE_SS_CH:		lMnFtr.mPr.chnl = val;						break;
		case MnFTR_OPT_SINGLE_04mA:			lMnFtr.mPr.cfg_4mA[MnFTR_CH_0] = val;		break;
		case MnFTR_OPT_SINGLE_20mA:			lMnFtr.mPr.cfg_20mA[MnFTR_CH_0] = val;		break;
		case MnFTR_OPT_SINGLE_TRIM_12MA:	MnOUT_CurPrSet_Value(MnOS0_OPT_CH1_TRM_12mA,val);	break;
		case MnFTR_OPT_SINGLE_TRIM_20MA:	MnOUT_CurPrSet_Value(MnOS0_OPT_CH1_TRM_20mA,val);	break;
		case MnFTR_OPT_SINGLE_OUTPUT_4MA:	break;
		case MnFTR_OPT_SINGLE_RELAY_TEST:	break;
		case MnFTR_OPT_SINGLE_LANG:			MnSYS_PrSetBase_Value(MnSYS_OPT_LANG, val);		break;
		case MnFTR_OPT_SINGLE_TIME:			break;
		case MnFTR_OPT_SINGLE_VERSION:		break;
		case MnFTR_OPT_SINGLE_CLEAN_TEST:	break;
	}


	if(MnLY2_GetIdxItem()==MnFTR_OPT_SINGLE_SS_CH)
	{
		if(lMnFtr.mPr.chnl==MnFTR_SS_SINGLE)
			MnEGN_PrSet_Value(MnEGN_OPT_MSR,MnEGN_MSR_OFF);
	}


	switch(MnLY2_GetIdxItem())
	{
		case MnFTR_OPT_SINGLE_SS_CH:MRM_WrByte(_mSENSOR_DUAL_SINGLE, 		lMnFtr.mPr.chnl);	break;
		case MnFTR_OPT_SINGLE_04mA:	MRM_WrWord(_mDAC_CH1_04MA_L, 	lMnFtr.mPr.cfg_4mA[MnFTR_CH_0]);	break;
		case MnFTR_OPT_SINGLE_20mA:	MRM_WrWord(_mDAC_CH1_20MA_L, 	lMnFtr.mPr.cfg_20mA[MnFTR_CH_0]);	break;
	}
}


void MnFTR_PrRst_Factory(void)
{
	MRM_WrByte(_mSENSOR_DUAL_SINGLE, 		MnFTR_CH_DEF);
	MRM_WrWord(_mDAC_CH1_04MA_L, 	MnFTR_CFG_04mA_DEF);
	MRM_WrWord(_mDAC_CH1_20MA_L, 	MnFTR_CFG_20mA_DEF);
	MRM_WrWord(_mDAC_CH2_04MA_L, 	MnFTR_CFG_04mA_DEF);
	MRM_WrWord(_mDAC_CH2_20MA_L, 	MnFTR_CFG_20mA_DEF);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 MnFTR_GetLayer(void)			{	return lMnFtr.lyr;		}
// Set
void MnFTR_SetLayer(U08 lyr)		{	lMnFtr.lyr = lyr;		}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void MnFTR_PrInitMain(void)
{
	U08 i=0;

	// Read Parameters
	lMnFtr.mPr.chnl 	= MRM_RdByte(_mSENSOR_DUAL_SINGLE);
	lMnFtr.mPr.cfg_4mA [MnFTR_CH_0]	= MRM_RdWord(_mDAC_CH1_04MA_L);
	lMnFtr.mPr.cfg_20mA[MnFTR_CH_0] = MRM_RdWord(_mDAC_CH1_20MA_L);
	lMnFtr.mPr.cfg_4mA [MnFTR_CH_1]	= MRM_RdWord(_mDAC_CH2_04MA_L);
	lMnFtr.mPr.cfg_20mA[MnFTR_CH_1] = MRM_RdWord(_mDAC_CH2_20MA_L);
	// Check Parameters
	if(lMnFtr.mPr.chnl >= MnFTR_SS_NUM)				lMnFtr.mPr.chnl 	= MnFTR_CH_DEF;

	for(i=0; i<MnFTR_CH_NUM; i++)
	{
		if(lMnFtr.mPr.cfg_4mA[i]  < MnFTR_CFG_04mA_MIN)		lMnFtr.mPr.cfg_4mA[i] 	= MnFTR_CFG_04mA_DEF;
		if(lMnFtr.mPr.cfg_4mA[i]  > MnFTR_CFG_04mA_MAX)		lMnFtr.mPr.cfg_4mA[i]	= MnFTR_CFG_04mA_DEF;
		if(lMnFtr.mPr.cfg_20mA[i] < MnFTR_CFG_20mA_MIN)		lMnFtr.mPr.cfg_20mA[i] 	= MnFTR_CFG_20mA_DEF;
		if(lMnFtr.mPr.cfg_20mA[i] > MnFTR_CFG_20mA_MAX)		lMnFtr.mPr.cfg_20mA[i] 	= MnFTR_CFG_20mA_DEF;		
	}

}


void MnFTR_InitMain(void)
{	
	lMnFtr.lyr = MENU_L0_SECTION;

	MnLY0_InitSection();
	MnLY1_InitSubSct();
	MnLY2_InitItem();
	MnLY3_InitValue();
	MnLY4_InitAddition();

	MnFTR_PrInitMain();
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

