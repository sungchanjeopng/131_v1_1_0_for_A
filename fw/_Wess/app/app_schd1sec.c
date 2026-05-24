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
// input
#include "input_key.h"
// measure
#include "measure_calc.h"
#include "measure_cal1_field0.h"
// menu
#include "menu_main.h"
#include "menu_system.h"
#include "menu_measure.h"
#include "menu_factory.h"
#include "menu_engineer.h"
#include "menu_test.h"
// screen
#include "screen_echo.h"
#include "screen_main.h"
#include "screen_calib.h"
// app
#include "app_main.h"
#include "app_status.h"
//
#include "output_pcd.h"
// self
#include "app_schd1sec.h"

#include "data_commu.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ApSC1_LS lApSc1;

//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
void Scd1Sec_ScrnRtnTime(void)
{
#if 0

	U16 cKey_std;
	if(InKEY_GetFgNone())		lApSc1.cKey_none++;
	else						lApSc1.cKey_none = 0;

	switch(MnSYS_PrGetBase_Item(MnSYS_I01_RTN_TIM))
	{
		case MnSYS_RTN_TIM_MIN_05:		cKey_std = 10;			break;
		case MnSYS_RTN_TIM_MIN_10:		cKey_std = 30;			break;
		case MnSYS_RTN_TIM_MIN_30:		cKey_std = 60;			break;
		case MnSYS_RTN_TIM_DISABLE:
		default:						cKey_std = 0xffff;		break;
	}

	if(APP_GetMode() == APP_MD1_MENU)
	{
		if(lApSc1.cKey_none > cKey_std)
		{
			MENU_ExitMain();
			MENU_InitMain();
			lApSc1.cKey_none = 0;
		}
	}
#endif
}

void Scd1Sec_FieldAProf(U08 iCh)
{
	U16 prof = MnEGN_PrGet_CH_Item(iCh, MnEGN_OPT_SINGLE_PROFILE);


	switch(MsCAL_Get_Stt(iCh))
	{
		case ApSTT_TPR_NG:	
		case ApSTT_MSR_NG:		return;
		case ApSTT_MSR_OK:
		case ApSTT_MSR_TRAC:
		case ApSTT_MSR_IDLE:
		case ApSTT_MSR_WEAK:	break;
		default:				return;
	}

	if(MsCAL1_GetfDp_dtt(APP_CH_1)==TRUE)
		lApSc1.Save_flag[iCh] = TRUE;


	if(lApSc1.cPrf[iCh] >= prof)
	{
		lApSc1.cPrf[iCh] = prof;
		lApSc1.cPrf_full[iCh] = TRUE;
	}
	else
		lApSc1.cPrf_full[iCh] = FALSE;

	MsCAL_FieldAProf(iCh, lApSc1.cPrf[iCh]);


#if 0

	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR) == MnEGN_MSR_ON)
	{
		if(iCh == APP_CH_1)
		{
			if(lApSc1.Save_flag[iCh]==FALSE)
			{
				if(lApSc1.cSave_real[iCh] >=400)
					lApSc1.cSave_real[iCh] = 400;
			}

			if(lApSc1.Save_flag[iCh]==TRUE)
			{
				if(lApSc1.cSave_real[iCh] >=800)
					lApSc1.cSave_real[iCh] = 800;
			}	
			
			if(lApSc1.cSave_real[iCh] <800)
			{
				MsCAL_ProcRealSave160(lApSc1.cSave_real[iCh]);
			}
		}
	}
#endif
}



void Scd1Sec_ProcProf(U08 iCh)
{
	U16 prof = MnEGN_PrGet_CH_Item(iCh, MnEGN_OPT_SINGLE_PROFILE);
	switch(MsCAL_Get_Stt(iCh))
	{
		case ApSTT_TPR_NG:	
		case ApSTT_MSR_NG:		return;
		case ApSTT_MSR_OK:
		case ApSTT_MSR_TRAC:
		case ApSTT_MSR_IDLE:
		case ApSTT_MSR_WEAK:	break;
		default:				return;
	}

	if(MsCAL1_GetfDp_dtt(APP_CH_1)==TRUE)
		lApSc1.Save_flag[iCh] = TRUE;


	if(++lApSc1.cPrf[iCh] >= prof)
	{
		lApSc1.cPrf[iCh] = prof;
		lApSc1.cPrf_full[iCh] = TRUE;
	}
	else
		lApSc1.cPrf_full[iCh] = FALSE;

	MsCAL_ProcProf(iCh, lApSc1.cPrf[iCh]);

#if 0
	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR) == MnEGN_MSR_ON)
	{
		if(iCh == APP_CH_1)
		{
			if(lApSc1.Save_flag[iCh]==FALSE)
			{
				if(++lApSc1.cSave_real[iCh] >=400)
					lApSc1.cSave_real[iCh] = 400;
			}

			if(lApSc1.Save_flag[iCh]==TRUE)
			{
				if(++lApSc1.cSave_real[iCh] >=800)
					lApSc1.cSave_real[iCh] = 800;
			}	
			
			if(lApSc1.cSave_real[iCh] <800)
			{
				MsCAL_ProcRealSave380(lApSc1.cSave_real[iCh]);
			}
		}
	}
#endif
}

void Scd1Sec_ProcDamp(U08 iCh)
{
	U16 damp;

	switch(MsCAL_Get_Stt(iCh))
	{
		case ApSTT_MSR_OK:		break;
		case ApSTT_TPR_NG:	
		case ApSTT_MSR_NG:		
		case ApSTT_MSR_TRAC:
		case ApSTT_MSR_IDLE:
		case ApSTT_MSR_WEAK:	return;
		default:				return;
	}

	damp = MnMSR_CalGet_Ch_Value(iCh, MnMS1_OPT_SINGLE_DAMPING);
	
	if(++lApSc1.cDmp[iCh] >= damp)
		lApSc1.cDmp[iCh] = damp;
	MsCAL_ProcDamp(iCh, lApSc1.cDmp[iCh]);





}

void Scd1Sec_ProcCycle(U08 iCh)
{

}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 ApSCD_GetVl_Prof_Full(U08 iCh)			{  return lApSc1.cPrf_full[iCh];		} 
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void ApSCD_Init1Sec(U08 ch)
{
	lApSc1.cKey_none = 0;
	
	lApSc1.cTxW = 0;

	lApSc1.cPrf[ch] = 0;
	lApSc1.cPrf_full[ch] = FALSE;
	lApSc1.cDmp[ch] = 0;
	lApSc1.cCyc[ch] = 0;
	lApSc1.cInterval[ch] = 0;
	lApSc1.cSave_real[ch] = 0;
	lApSc1.Save_flag[ch] = FALSE;

}

void ApSCD_ProcFieldA1Sec(U08 iCh)
{
	switch(OuCUR_GetPCD_fRun())
	{
		case PCD_OFF:	break;
		case PCD_ON:	
		case PCD_TEST:	return;
		default:
			return;	
	}

	MsCal_fieldReal(iCh);
	Scd1Sec_FieldAProf(iCh);
}


void ApSCD_Intv(U08 iCh)
{

	if(lApSc1.cInterval[iCh]>=MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_MEASURE_CYCLE))
		lApSc1.cInterval[iCh]=0;

	lApSc1.cInterval[iCh]++;

}

void ApSCD_Proc1Sec(U08 iCh)
{
	U16 hold_light = MnTST_PrGet_CH_Value(iCh, MnTST_OPT_SINGLE_LIGHT_HOLD);
	U16 hold_heavy = MnTST_PrGet_CH_Value(iCh, MnTST_OPT_SINGLE_HEAVY_HOLD);
	U16 empty =MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_EMPTY);

	switch(OuCUR_GetPCD_fRun())
	{
		case PCD_OFF:	break;
		case PCD_ON:	
		case PCD_TEST:	return;
		default:
			return;	
	}

	if(ScECH_GetLayer() == SCRN_L2_VALU)
		MsCAL_ProcReal(iCh);
	else if(lApSc1.cInterval[iCh] >= MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_MEASURE_CYCLE))
		MsCAL_ProcReal(iCh);

	
	if((ScECH_GetLayer() == SCRN_L2_VALU) || (ScCLB_GetLayer() == SCRN_L2_VALU) || (MENU_GetLayer() >= MENU_L3_VALUE)) 
		return;

	if(lApSc1.cInterval[iCh] >= MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_MEASURE_CYCLE))
	{ 
		Scd1Sec_ProcProf(iCh); 
		DaMdb_ProcMain();
		MsCAL_ProcSmooth(iCh);
		MsCAL_Proc3Stp(iCh);

	}
	

	if(lApSc1.cInterval[iCh] >= MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_MEASURE_CYCLE))
	{
		Scd1Sec_ProcDamp(iCh);
	}	


#if 0
	if(gTmr.c.timer1[iCh]>600)
	{
		gTmr.c.timer1[iCh] = 0;
		MsCAL_ProcAvgSave(iCh);
	}
#endif
}

//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

