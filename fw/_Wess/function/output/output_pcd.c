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
#include "bsp_gpio.h"
#include "bsp_demux.h"
// self
#include "output_pcd.h"
// menu
#include "menu_output.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
OuPCD_LS lOuPcd;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 OuCUR_GetPCD_fRun(void)			  {	return lOuPcd.f_run;	}

// Set
void OuCUR_SetPCD_fRun(U08 sel)	{ lOuPcd.f_run = sel;			}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void OuPCD_SetOper(U08 f_opr)
{
	if	(f_opr>0)				DMX_SetIo(DMX_OUT_CLEAN, GIO_LV_HI);
	else if(f_opr==PCD_OFF)		DMX_SetIo(DMX_OUT_CLEAN, GIO_LV_LO);
}

void OuPCD_InitMain(void)
{
	lOuPcd.f_run = PCD_OFF;
	lOuPcd.old_run = PCD_OFF;
	lOuPcd.c_sec = 0;
	lOuPcd.r_sec = 0;
	OuPCD_SetOper(PCD_OFF);
}


void OuPCD_ProcMain(void)
{
	U16 pcd_intv=MnOUT_PcdPrGet_Value(MnOS2_OPT_INTV);
	U16 pcd_oper=MnOUT_PcdPrGet_Value(MnOS2_OPT_TERM);


	if(lOuPcd.f_run!=PCD_TEST)
	{
		switch(lOuPcd.f_run)
		{
			case PCD_OFF:	
				lOuPcd.c_sec++;
				if(lOuPcd.c_sec >= pcd_intv)
				{
					lOuPcd.f_run = PCD_ON;
					lOuPcd.c_sec = 0;
				}
				break;
			case PCD_ON:
				if(lOuPcd.r_sec>pcd_oper+1)
				{
					lOuPcd.f_run = PCD_OFF;
					lOuPcd.r_sec = 0;
				}
				else if(lOuPcd.r_sec >= pcd_oper)
				{
					OuPCD_SetOper(PCD_OFF);
					lOuPcd.r_sec++;
					return;
				}
				lOuPcd.r_sec++;
				break;
			default:		
				return;
		}
	}

	if(lOuPcd.f_run!=lOuPcd.old_run)
		OuPCD_SetOper(lOuPcd.f_run);

	lOuPcd.old_run = lOuPcd.f_run;
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

