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
#include "bsp_lcd.h"
#include "bsp_ram.h"
// app
#include "app_string.h"
// measure
#include "measure_sensor.h"
#include "measure_calc.h"
#include "measure_gain.h"
// image
#include "image_meas_a2.h"
// output
#include "output_current.h"
// display
#include "disp_color.h"
// disp - screen
#include "dp_screen_echo.h"
// self
#include "dbg_main.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
U08 lDbg_idx_curr_1 = 0, lDbg_idx_curr_2 = 0;
U08 lDbg_idx_scr = 0,    lDbg_idx_range = 0;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
void Dbg_InitDelay(void)
{
	U16 i = 300;

	while((i > 0) && (DMX_GetIo(DMX_INP_MBR_ENTER) &
					  DMX_GetIo(DMX_INP_MBR_RIGHT) &
					  DMX_GetIo(DMX_INP_MBR_LEFT_) &
					  DMX_GetIo(DMX_INP_MBR_BACK_)))
	{
		HAL_Delay(1);
		i--;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void DBG_InitVari(void)
{
	LCD_FlipFrame();
	LCD_ClearScrn(_cSD_BLACK);

	//LCD_DrawBitmap_2(0, 0, 800, 480, (uint8_t *)_gimg_meas_a2);
	//LCD_FlipFrame();
}

void DBG_LoopMain(void)
{
#if 0
#if 0
	INPU_ProcMain();

	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_DisplayStringAt(0, 24*0, (U08 *)"screen 2", DP_ALIGN_CENTER);

	LCD_SetTextColor(LCD_COLOR_WHITE);
	switch(INPU_GetKeyIdx())
	{
		case KEY_IDX_MENU:	LCD_DisplayStringAt(136, 24*1, (U08 *)"BACK", DP_ALIGN_LEFT);	break;
		case KEY_IDX_PREV:	LCD_DisplayStringAt(136, 24*1, (U08 *)"LEFT", DP_ALIGN_LEFT);	break;
		case KEY_IDX_NEXT:	LCD_DisplayStringAt(136, 24*1, (U08 *)"RIGHT", DP_ALIGN_LEFT);	break;
		case KEY_IDX_ENTER:	LCD_DisplayStringAt(136, 24*1, (U08 *)"ENTER", DP_ALIGN_LEFT);	break;
		default:			LCD_DisplayStringAt(136, 24*1, (U08 *)" ", DP_ALIGN_LEFT);		break;
	}

	LCD_SetTextColor(LCD_COLOR_WHITE);
	switch(INPU_GetKeyEvt())
	{
		case KEY_EVT_PUSH:		LCD_DisplayStringAt(136, 24*2, (U08 *)"S PRESS", DP_ALIGN_LEFT);	break;
		case KEY_EVT_DTT_L:		LCD_DisplayStringAt(136, 24*2, (U08 *)"L PRESS", DP_ALIGN_LEFT);	break;
		case KEY_EVT_SHORT:		LCD_DisplayStringAt(136, 24*2, (U08 *)"S CLICK", DP_ALIGN_LEFT);	break;
		case KEY_EVT_LONG:		LCD_DisplayStringAt(136, 24*2, (U08 *)"L CLICK", DP_ALIGN_LEFT);	break;
		default:				LCD_DisplayStringAt(136, 24*2, (U08 *)" ", DP_ALIGN_LEFT);			break;
	}

	INPU_ClrKeyEvt();

	LCD_FlipFrame();
	LCD_ClearScrn(LCD_COLOR_BLACK);

#else

#if 1
	// Measure - Sensor Tx PWM & Rx ADC
	MsSEN_ProcMain(ADC_CH_SS0);
	// Timer Enable
	TMR_HalEnable(_F_T, _F_T);
	// Measure - Calculation
	MsCAL_Proc3Stp(ADC_CH_SS0);
#else
	MsSEN_ProcMain(ADC_CH_SS0);
#endif

	Dbg_InitDelay();

	if((DMX_GetIo(DMX_INP_MBR_ENTER)) == 0)
	{
		lDbg_idx_scr++;
		lDbg_idx_scr %= 3;
	}
	else if((DMX_GetIo(DMX_INP_MBR_RIGHT)) == 0)	{	}
	else if((DMX_GetIo(DMX_INP_MBR_LEFT_)) == 0)
	{
		lDbg_idx_curr_2++;
		lDbg_idx_curr_2 %= 3;
		
		lDbg_idx_range++;
		lDbg_idx_range %= 2;
	}
	else if((DMX_GetIo(DMX_INP_MBR_BACK_)) == 0)
	{
		lDbg_idx_curr_1++;
		lDbg_idx_curr_1 %= 3;
	}
	
	if(lDbg_idx_scr == 0)
	{
		LCD_DrawBitmap_2(0, 0, 800, 480, (U08 *)_gimg_meas_a2);
		
		LCD_FlipFrame();
		LCD_ClearScrn(_cSD_BLACK);
	}
	else if(lDbg_idx_scr == 1)
	{
		LCD_SetTextColor(_cSD_WHITE);
		LCD_DisplayStringAt(0, 24*0, (U08 *)"screen 1", DP_ALIGN_CENTER);
	
		DpEC0_FncStdBy(lDbg_idx_range);
		
		LCD_SetTextColor(_cSD_WHITE);
		LCD_DisplayStringAt(550, 380, (U08 *)STR_Num2Str((lDbg_idx_range+1)*500, 4, 2, 0), DP_ALIGN_LEFT);
		LCD_DisplayStringAt(550+90, 380, (U08 *)"m", DP_ALIGN_LEFT);

		LCD_DisplayStringAt(0,   24*1, (U08 *)STR_Num2Str(ADC_GetTprtVlt(0), 4, 3, 0), DP_ALIGN_LEFT);
		LCD_DisplayStringAt(100, 24*1, (U08 *)STR_Num2Str(ADC_GetTprtVlt(1), 4, 3, 0), DP_ALIGN_LEFT);
			
		LCD_DisplayStringAt(100*0, 24*2, (U08 *)STR_Num2Str(ADC_GetEchoVal(0, 0), 5, 0, 0), DP_ALIGN_LEFT);
		LCD_DisplayStringAt(100*1, 24*2, (U08 *)STR_Num2Str(ADC_GetEchoVal(0, 1), 5, 0, 0), DP_ALIGN_LEFT);
		LCD_DisplayStringAt(100*2, 24*2, (U08 *)STR_Num2Str(ADC_GetEchoVal(0, 2), 5, 0, 0), DP_ALIGN_LEFT);
		LCD_DisplayStringAt(100*3, 24*2, (U08 *)STR_Num2Str(ADC_GetEchoVal(0, 3), 5, 0, 0), DP_ALIGN_LEFT);
		LCD_DisplayStringAt(100*4, 24*2, (U08 *)STR_Num2Str(ADC_GetEchoVal(0, 4), 5, 0, 0), DP_ALIGN_LEFT);
		LCD_DisplayStringAt(100*5, 24*2, (U08 *)STR_Num2Str(ADC_GetEchoVal(0, 5), 5, 0, 0), DP_ALIGN_LEFT);
		LCD_DisplayStringAt(100*6, 24*2, (U08 *)STR_Num2Str(ADC_GetEchoVal(0, 6), 5, 0, 0), DP_ALIGN_LEFT);
		LCD_DisplayStringAt(100*7, 24*2, (U08 *)STR_Num2Str(ADC_GetEchoVal(0, 7), 5, 0, 0), DP_ALIGN_LEFT);
		
		LCD_FlipFrame();
		LCD_ClearScrn(_cSD_BLACK);
	}
	else if(lDbg_idx_scr == 2)
	{
		LCD_SetTextColor(_cSD_WHITE);
		LCD_DisplayStringAt(0, 24*0, (U08 *)"screen 2", DP_ALIGN_CENTER);
		
		LCD_SetTextColor(_cSD_WHITE);
		LCD_DisplayStringAt(136, 24*1, (U08 *)"CH 1", DP_ALIGN_LEFT);
		LCD_DisplayStringAt(308, 24*1, (U08 *)"CH 2", DP_ALIGN_LEFT);
		
		switch(lDbg_idx_curr_1)
		{
			case 0:
				OuCUR_WrDac(MsSEN_C0_CH1, 10481);

				LCD_DisplayStringAt(136, 24*2, (U08 *)" 4mA", DP_ALIGN_LEFT);
				break;
			case 1:
				OuCUR_WrDac(MsSEN_C0_CH1, 31401);

				LCD_DisplayStringAt(136, 24*2, (U08 *)"12mA", DP_ALIGN_LEFT);
				break;
			case 2:
				OuCUR_WrDac(MsSEN_C0_CH1, 52320);
				
				LCD_DisplayStringAt(136, 24*2, (U08 *)"20mA", DP_ALIGN_LEFT);
				break;
		}
		
		switch(lDbg_idx_curr_2)
		{
			case 0:
				OuCUR_WrDac(MsSEN_C1_CH2, 10481);

				LCD_DisplayStringAt(308, 24*2, (U08 *)" 4mA", DP_ALIGN_LEFT);
				break;
			case 1:
				OuCUR_WrDac(MsSEN_C1_CH2, 31401);

				LCD_DisplayStringAt(308, 24*2, (U08 *)"12mA", DP_ALIGN_LEFT);
				break;
			case 2:
				OuCUR_WrDac(MsSEN_C1_CH2, 52320);
				
				LCD_DisplayStringAt(308, 24*2, (U08 *)"20mA", DP_ALIGN_LEFT);
				break;
		}
		
		LCD_DisplayStringAt(0, 24*4, (U08 *)STR_Num2Str(MRM_RdByte(1), 6, 0, 0), DP_ALIGN_CENTER);
		LCD_DisplayStringAt(0, 24*5, (U08 *)STR_Num2Str(MRM_RdByte(2), 6, 0, 0), DP_ALIGN_CENTER);
		LCD_DisplayStringAt(0, 24*6, (U08 *)STR_Num2Str(MRM_RdByte(3), 6, 0, 0), DP_ALIGN_CENTER);

		LCD_FlipFrame();
		LCD_ClearScrn(_cSD_BLACK);
	}

	while(!(DMX_GetIo(DMX_INP_MBR_ENTER) & DMX_GetIo(DMX_INP_MBR_RIGHT) & DMX_GetIo(DMX_INP_MBR_LEFT_) & DMX_GetIo(DMX_INP_MBR_BACK_)));
#endif
#endif
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

