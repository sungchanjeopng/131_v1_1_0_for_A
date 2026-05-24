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
// app
#include "app_main.h"
#include "app_status.h"
// measure
#include "measure_calc.h"
// menu
#include "menu_factory.h"
#include "menu_output.h"
// screen
#include "screen_hybrid.h"
// self
#include "output_error.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
OuERR_LS lOuErr;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------


void OuERR_InitMain(void)
{
	lOuErr.f_run = FALSE;
	lOuErr.c_sec = 0;

}




#if 0
void OuERR_ProcMain(void)
{
	U08 stt_0 = ApSTT_GetStatus(ApSTT_CH_S0);
	U08 stt_1 = ApSTT_GetStatus(ApSTT_CH_S1);
	U08 err_hold = MnOUT_ErrPrGet_Value(MnOS3_I00_ERR_HOLD);


	switch(stt_0)
	{
		case ApSTT_MSR_OK:
			switch(lOuErr.f_run)
			{
				case ERROR_ON:		lOuErr.f_run = ERROR_OFF;	break;
				case ERROR_OFF:		
				default:										break;
			}
			break;	
		case ApSTT_MSR_NG:
			switch(lOuErr.f_run)
			{
				case ERROR_OFF:
					lOuErr.c_sec++;
					if(lOuErr.c_sec>=err_hold)
					{
						lOuErr.f_run = ERROR_ON;
						lOuErr.c_sec = 0;
					}							
					break;
				case ERROR_ON:		
				default:			break;
			}
			break;					
		case ApSTT_MSR_WEAK:		 
		case ApSTT_MSR_STOP:		 
		default:					break;
	}

	switch(stt_1)
	{
		case ApSTT_MSR_OK:
			switch(lOuErr.f_run)
			{
				case ERROR_ON:		lOuErr.f_run = ERROR_OFF;	break;
				case ERROR_OFF:		
				default:										break;
			}
			break;	
		case ApSTT_MSR_NG:
			switch(lOuErr.f_run)
			{
				case ERROR_OFF:
					lOuErr.c_sec++;
					if(lOuErr.c_sec>=err_hold)
					{
						lOuErr.f_run = ERROR_ON;
						lOuErr.c_sec = 0;
					}							
					break;
				case ERROR_ON:		
				default:			break;
			}
			break;					
		case ApSTT_MSR_WEAK:		 
		case ApSTT_MSR_STOP:		 
		default:					break;
	}

}
#endif

//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

