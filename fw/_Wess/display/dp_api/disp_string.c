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
// app
#include "app_main.h"
// screen
#include "screen_main.h"
// menu
#include "menu_system.h"
#include "menu_engineer.h"
#include "menu_measure.h"
// display
#include "disp_main.h"
#include "disp_color.h"
#include "disp_figure.h"
// self
#include "disp_string.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------
DpSTR_LS gDpStr;


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation - Initial
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation - Live
//------------------------------------------------------------------------------------------------------------------------------
void DpSTR_LiveLft(U16 x0, U16 y0, U32 col_fw, U32 col_bg, sFONT ft, I08 *pStr)
{
	if(LCD_GetLayer() == LCD_FRM_0)		LCD_SetLayer(LCD_FRM_1);
	else								LCD_SetLayer(LCD_FRM_0);

	LCD_SetFont(&ft);
	LCD_SetTextColor(col_fw);
	LCD_SetBackColor(col_bg);
	LCD_DisplayStringAt(x0, y0, (U08*)pStr, DP_ALIGN_LEFT);

	if(LCD_GetLayer() == LCD_FRM_0)		LCD_SetLayer(LCD_FRM_1);
	else								LCD_SetLayer(LCD_FRM_0);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Draw for Flip
//------------------------------------------------------------------------------------------------------------------------------
void DpSTR_TitleBar_KOR(I08* pStr, U16 x0, U32 col)
{
#if 0
	if((APP_GetMode() == APP_MD0_SCRN) && ((SCRN_GetPage() == SCRN_P1_HYBRID) || (SCRN_GetPage() == SCRN_P0_FRONT)))
	{
		LCD_SetFont(&_fE22HsB);
		LCD_SetTextColor(_cTTB_ST_PRDT);
		LCD_SetBackColor(_cTTB_BG_MID);
		LCD_DisplayStringAt(70, 13, (U08*)pStr, DP_ALIGN_LEFT);
	}
	else
	{
		LCD_SetFont(&_fE22HsB);
		LCD_SetTextColor(_cTTB_ST_PRDT);
		LCD_SetBackColor(_cTTB_BG_MID);
		LCD_DisplayStringAt(70, 13, (U08*)"S L M", DP_ALIGN_LEFT);

		LCD_SetFont(&_fE22HsB);
		LCD_SetTextColor(col);
		LCD_SetBackColor(_cTTB_BG_MID);
		LCD_DisplayStringAt(x0, 13, (U08*)pStr, DP_ALIGN_LEFT);
	}
#endif
	LCD_SetFont(&_fE22HsBKOR);
	LCD_SetTextColor(_cTTB_ST_PRDT);
	LCD_SetBackColor(_cTTB_BG_MID);
	LCD_DisplayStringAt_KOR(70, 13, (U08*)pStr, DP_ALIGN_LEFT);

}



void DpSTR_TitleBar(I08* pStr, U16 x0, U32 col)
{
#if 0
	if((APP_GetMode() == APP_MD0_SCRN) && ((SCRN_GetPage() == SCRN_P1_HYBRID) || (SCRN_GetPage() == SCRN_P0_FRONT)))
	{
		LCD_SetFont(&_fE22HsB);
		LCD_SetTextColor(_cTTB_ST_PRDT);
		LCD_SetBackColor(_cTTB_BG_MID);
		LCD_DisplayStringAt(70, 13, (U08*)pStr, DP_ALIGN_LEFT);
	}
	else
	{
		LCD_SetFont(&_fE22HsB);
		LCD_SetTextColor(_cTTB_ST_PRDT);
		LCD_SetBackColor(_cTTB_BG_MID);
		LCD_DisplayStringAt(70, 13, (U08*)"S L M", DP_ALIGN_LEFT);

		LCD_SetFont(&_fE22HsB);
		LCD_SetTextColor(col);
		LCD_SetBackColor(_cTTB_BG_MID);
		LCD_DisplayStringAt(x0, 13, (U08*)pStr, DP_ALIGN_LEFT);
	}
#endif
	LCD_SetFont(&_fE22HsB);
	LCD_SetTextColor(_cTTB_ST_PRDT);
	LCD_SetBackColor(_cTTB_BG_MID);
	LCD_DisplayStringAt(70, 13, (U08*)pStr, DP_ALIGN_LEFT);

}


void DpSTR_GuiList(U08 iIt)
{
	for(U08 i=0; i<16; i++)
		gDpStr.Text_list[i] = 0;

	switch(iIt)
	{
		case TEXT_LIST_ECHO_AMP:	
			gDpStr.Text_list[0] = 90; gDpStr.Text_list[1] = 95; gDpStr.Text_list[2] = 13; gDpStr.Text_list[3] =42; gDpStr.Text_list[4] = 0; gDpStr.Text_list[5] = 0;
			break;
		case TEXT_LIST_THR_LIGHT:
#if 0
			gDpStr.Text_list[0] = 126;	gDpStr.Text_list[1] = 31; gDpStr.Text_list[2] = 42; gDpStr.Text_list[3] = 173; gDpStr.Text_list[4] = 64; gDpStr.Text_list[5] = 153; 
			gDpStr.Text_list[6] = 127; gDpStr.Text_list[7]=99; gDpStr.Text_list[8] = 0;
#else
			gDpStr.Text_list[0] = 183;	gDpStr.Text_list[1] = 184; gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 185;  gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 64; gDpStr.Text_list[6] = 153; 
			gDpStr.Text_list[7] = 127; gDpStr.Text_list[8]=99;

#endif
			break;
		case TEXT_LIST_THR_HEAVY:
#if 0
			gDpStr.Text_list[0] = 19;	gDpStr.Text_list[1] = 31; gDpStr.Text_list[2] = 42; gDpStr.Text_list[3] = 173; gDpStr.Text_list[4] = 64; gDpStr.Text_list[5] = 153; 
			gDpStr.Text_list[6] = 127; gDpStr.Text_list[7]=99; gDpStr.Text_list[8] = 0;
#else
			gDpStr.Text_list[0] = 137;	gDpStr.Text_list[1] = 181; gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 185;  gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 64; gDpStr.Text_list[6] = 153; 
			gDpStr.Text_list[7] = 127; gDpStr.Text_list[8]=99;

#endif
			break;		
		case TEXT_LIST_OFFSET:
			gDpStr.Text_list[0] = 66;	gDpStr.Text_list[1] = 84; gDpStr.Text_list[2] = 120; gDpStr.Text_list[3] = 43; gDpStr.Text_list[4] = 0;
			break;
		case TEXT_LIST_FREQ:
			gDpStr.Text_list[0] = 133;	gDpStr.Text_list[1] = 157; gDpStr.Text_list[2] = 90; gDpStr.Text_list[3] = 0;
			break;			
		case TEXT_LIST_DAMPING:
			gDpStr.Text_list[0] = 40;	gDpStr.Text_list[1] = 162; gDpStr.Text_list[2] = 0;
			break;			
		case TEXT_LIST_HEAVY_LEVEL:
#if 0
			gDpStr.Text_list[0] = 19;	gDpStr.Text_list[1] = 31; gDpStr.Text_list[2] = 42; gDpStr.Text_list[3] = 173; gDpStr.Text_list[4] = 49;
			gDpStr.Text_list[5] = 72;   gDpStr.Text_list[6] = 0;
#else
			gDpStr.Text_list[0] = 137;	gDpStr.Text_list[1] = 181; gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 185; gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 49;   gDpStr.Text_list[6] = 72;
#endif
			break;
		case TEXT_LIST_LIGHT_LEVEL:
#if 0
			gDpStr.Text_list[0] = 126;	gDpStr.Text_list[1] = 31; gDpStr.Text_list[2] = 42; gDpStr.Text_list[3] = 173; gDpStr.Text_list[4] = 49;
			gDpStr.Text_list[5] = 72;   gDpStr.Text_list[6] = 0;
#else
			gDpStr.Text_list[0] = 183;	gDpStr.Text_list[1] = 184; gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 185; gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 49;   gDpStr.Text_list[6] = 72;
#endif
			break;
		case TEXT_LIST_MAX_VALUE:
			gDpStr.Text_list[0] = 143; gDpStr.Text_list[1] = 39; gDpStr.Text_list[2] = 14;	gDpStr.Text_list[3] = 0;	
			break;
		case TEXT_LIST_MIN_VALUE:
			gDpStr.Text_list[0] = 143; gDpStr.Text_list[1] = 87; gDpStr.Text_list[2] = 14;	gDpStr.Text_list[3] = 0;	
			break;
		case TEXT_LIST_TIME:
			gDpStr.Text_list[0] = 93; gDpStr.Text_list[1] = 12; gDpStr.Text_list[2] = 0;
			break;
		case TEXT_LIST_CH_1:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;	gDpStr.Text_list[2] = 173;	gDpStr.Text_list[3] = 2;
			break;
		case TEXT_LIST_CH_2:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;	gDpStr.Text_list[2] = 173;	gDpStr.Text_list[3] = 3;
			break;
		case TEXT_LIST_SLUDGE_LEVEL_METER:
			gDpStr.Text_list[0] = 92; gDpStr.Text_list[1] = 48; gDpStr.Text_list[2] = 136; gDpStr.Text_list[3] = 173; 
			gDpStr.Text_list[4] = 18; gDpStr.Text_list[5] = 61; gDpStr.Text_list[6] = 18; gDpStr.Text_list[7] = 0;
			break;
		case TEXT_LIST_CURRENT:
			gDpStr.Text_list[0] = 127;	gDpStr.Text_list[1] = 54; gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 144; gDpStr.Text_list[4] = 51;
			gDpStr.Text_list[5] = 0;			
			break;
		case TEXT_LIST_CH1_CURRENT:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;	gDpStr.Text_list[2] = 173;	gDpStr.Text_list[3] = 2;
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 127;	gDpStr.Text_list[6] = 54; gDpStr.Text_list[7] = 173; gDpStr.Text_list[8] = 144; gDpStr.Text_list[9] = 51;
			gDpStr.Text_list[10] = 0;			
			break;
		case TEXT_LIST_CH2_CURRENT:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;	gDpStr.Text_list[2] = 173;	gDpStr.Text_list[3] = 3;
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 127;	gDpStr.Text_list[6] = 54; gDpStr.Text_list[7] = 173; gDpStr.Text_list[8] = 144; gDpStr.Text_list[9] = 51;
			gDpStr.Text_list[10] = 0;			
			break;
		case TEXT_LIST_EMPTY:
			gDpStr.Text_list[0] = 145;	gDpStr.Text_list[1] = 130; gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 71; gDpStr.Text_list[4] = 115;
			gDpStr.Text_list[5] = 0;			
			break;			
		case TEXT_LIST_TANK_SCREEN:
			gDpStr.Text_list[0] = 151;	gDpStr.Text_list[1] = 148; 
			//gDpStr.Text_list[2] = 150; gDpStr.Text_list[3] = 147; gDpStr.Text_list[4] = 44;
			gDpStr.Text_list[5] = 0;	
			break;
		case TEXT_LIST_AVG_ECHO_SCREEN:
			gDpStr.Text_list[0] = 159;	gDpStr.Text_list[1] = 23; gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 157; gDpStr.Text_list[4] = 168;
			gDpStr.Text_list[5] = 0;	
			//gDpStr.Text_list[6] = 150; gDpStr.Text_list[7] = 147; gDpStr.Text_list[8] = 44;	 
			gDpStr.Text_list[9] = 0;	
			break;
		case TEXT_LIST_REAL_ECHO_SCREEN:
			gDpStr.Text_list[0] = 96;	gDpStr.Text_list[1] = 93; gDpStr.Text_list[2] = 12; gDpStr.Text_list[3] = 173; gDpStr.Text_list[4] = 157;
			gDpStr.Text_list[5] = 168;	
			//gDpStr.Text_list[6] = 150; gDpStr.Text_list[7] = 147; gDpStr.Text_list[8] = 44;	 
			gDpStr.Text_list[9] = 0;	
			break;	
		case TEXT_LIST_PARAMETER_SCREEN:
			gDpStr.Text_list[0] = 157;	gDpStr.Text_list[1] = 47; gDpStr.Text_list[2] = 66; gDpStr.Text_list[3] = 152;
			//gDpStr.Text_list[4] = 150;	
			//gDpStr.Text_list[5] = 147; gDpStr.Text_list[6] = 44;	 
			gDpStr.Text_list[7] = 0;	
			break;	
		case TEXT_LIST_DATA_TREND_SCREEN:
			gDpStr.Text_list[0] = 41;	gDpStr.Text_list[1] = 120; gDpStr.Text_list[2] = 152; 
			gDpStr.Text_list[3] = 173;
		    gDpStr.Text_list[4] = 17;	gDpStr.Text_list[5] = 165; 
			gDpStr.Text_list[6] = 0;
			break;				
		case TEXT_LIST_MENU:
			gDpStr.Text_list[0] = 60;	gDpStr.Text_list[1] = 33; gDpStr.Text_list[2] = 0; 
			break;
		case TEXT_LIST_EXIT:
			gDpStr.Text_list[0] = 28;	gDpStr.Text_list[1] = 11; gDpStr.Text_list[2] = 25; gDpStr.Text_list[3] = 0; 
			break;			
		case TEXT_LIST_BACK:
			gDpStr.Text_list[0] = 120;	gDpStr.Text_list[1] = 127; gDpStr.Text_list[2] = 0; gDpStr.Text_list[3] = 0; 
			break;				
		case TEXT_LIST_SAVE:
			gDpStr.Text_list[0] = 126;	gDpStr.Text_list[1] = 124; gDpStr.Text_list[2] = 0; gDpStr.Text_list[3] = 0; 
			break;				
		case TEXT_LIST_SET:
			gDpStr.Text_list[0] = 83;	gDpStr.Text_list[1] = 130; gDpStr.Text_list[2] = 0; gDpStr.Text_list[3] = 0; 
			break;	
		case TEXT_LIST_SLUDGE_COLLECTOR:
			gDpStr.Text_list[0] = 117; gDpStr.Text_list[1] = 43; gDpStr.Text_list[2] = 21; gDpStr.Text_list[3] = 132; 
			gDpStr.Text_list[4] = 65; gDpStr.Text_list[5] = 0; gDpStr.Text_list[6] = 0; gDpStr.Text_list[7] = 0;
			break;	
		case TEXT_LIST_SLUDGE_COLLECTOR_DETECT:
			gDpStr.Text_list[0] = 117; gDpStr.Text_list[1] = 43; gDpStr.Text_list[2] = 21; gDpStr.Text_list[3] = 132; 
			gDpStr.Text_list[4] = 65; gDpStr.Text_list[5] = 173; gDpStr.Text_list[6] = 121; gDpStr.Text_list[7] = 94;
			gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0; gDpStr.Text_list[10] = 0;
			break;	
		case TEXT_LIST_POSITION:
			gDpStr.Text_list[0] = 115;	gDpStr.Text_list[1] = 146; gDpStr.Text_list[2] = 0; gDpStr.Text_list[3] = 0; 
			break;	
		case TEXT_LIST_DIRECTION:
			gDpStr.Text_list[0] = 68;	gDpStr.Text_list[1] = 165; gDpStr.Text_list[2] = 0; gDpStr.Text_list[3] = 0; 
			break;
		case TEXT_LIST_VELOCITY:
			gDpStr.Text_list[0] = 88;	gDpStr.Text_list[1] = 42; gDpStr.Text_list[2] = 0; gDpStr.Text_list[3] = 0; 
			break;		
		case TEXT_LIST_UNIT:
			gDpStr.Text_list[0] = 36;	gDpStr.Text_list[1] = 115; gDpStr.Text_list[2] = 0; gDpStr.Text_list[3] = 0; 
			break;	
		case TEXT_LIST_CH1_OPERATION:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 92;  gDpStr.Text_list[6] = 48; gDpStr.Text_list[7] = 136;
			gDpStr.Text_list[8] = 174;	gDpStr.Text_list[9] = 80;  gDpStr.Text_list[10] = 139; gDpStr.Text_list[11] = 90;
			gDpStr.Text_list[12] = 0;
			break;	
		case TEXT_LIST_CH1_EMPTY:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 145; gDpStr.Text_list[6] = 130; gDpStr.Text_list[7] = 173; 
			gDpStr.Text_list[8] = 71; 	gDpStr.Text_list[9] = 115;	gDpStr.Text_list[10] = 0;			
			break;			
		case TEXT_LIST_CH1_DEADZONE:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;  gDpStr.Text_list[5] = 76;	gDpStr.Text_list[6] = 13; gDpStr.Text_list[7] = 39; 
			gDpStr.Text_list[8] = 173; 	gDpStr.Text_list[9] = 108;	gDpStr.Text_list[10] = 105;	gDpStr.Text_list[11] = 0;			
			break;			
		case TEXT_LIST_CH1_MSR_CYC:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 145;	gDpStr.Text_list[6] = 130; gDpStr.Text_list[7] = 173; 
			gDpStr.Text_list[8] = 133;	gDpStr.Text_list[9] = 25;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;			
			break;			
		case TEXT_LIST_CH1_MSR_RST:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 145;	gDpStr.Text_list[6] = 130; gDpStr.Text_list[7] = 173; 
			gDpStr.Text_list[8] = 56;	gDpStr.Text_list[9] = 86;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;			
			break;
		case TEXT_LIST_CH2_OPERATION:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 92;  gDpStr.Text_list[6] = 48; gDpStr.Text_list[7] = 136;
			gDpStr.Text_list[8] = 174;	gDpStr.Text_list[9] = 80;  gDpStr.Text_list[10] = 139; gDpStr.Text_list[11] = 90;
			gDpStr.Text_list[12] = 0;
			break;	
		case TEXT_LIST_CH2_EMPTY:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 145; gDpStr.Text_list[6] = 130; gDpStr.Text_list[7] = 173; 
			gDpStr.Text_list[8] = 71;	gDpStr.Text_list[9] = 115;	gDpStr.Text_list[10] = 0;			
			break;			
		case TEXT_LIST_CH2_DEADZONE:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 76;	gDpStr.Text_list[6] = 13; gDpStr.Text_list[7] = 39; 
			gDpStr.Text_list[8] = 173;	gDpStr.Text_list[9] = 108;	gDpStr.Text_list[10] = 105; gDpStr.Text_list[11] = 0;			
			break;			
		case TEXT_LIST_CH2_MSR_CYC:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 145;	gDpStr.Text_list[6] = 130; gDpStr.Text_list[7] = 173; 
			gDpStr.Text_list[8] = 133;	gDpStr.Text_list[9] = 25;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0; 		
			break;			
		case TEXT_LIST_CH2_MSR_RST:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 145;	gDpStr.Text_list[6] = 130; gDpStr.Text_list[7] = 173; 
			gDpStr.Text_list[8] = 56;	gDpStr.Text_list[9] = 86;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0; 		
			break;

		case TEXT_LIST_OPERATION:
			gDpStr.Text_list[0] = 92;  gDpStr.Text_list[1] = 48; gDpStr.Text_list[2] = 136;
			gDpStr.Text_list[3] = 174;	gDpStr.Text_list[4] = 80;  gDpStr.Text_list[5] = 139; gDpStr.Text_list[6] = 90;
			gDpStr.Text_list[7] = 0;
			break;	
		case TEXT_LIST_DEADZONE:
			gDpStr.Text_list[0] = 76;  gDpStr.Text_list[1] = 13; gDpStr.Text_list[2] = 39; 
			gDpStr.Text_list[3] = 173;  gDpStr.Text_list[4] = 108;  gDpStr.Text_list[5] = 105; gDpStr.Text_list[6] = 0;		   
			break;		   
		case TEXT_LIST_MSR_CYC:
			gDpStr.Text_list[0] = 145;	gDpStr.Text_list[1] = 130; gDpStr.Text_list[2] = 173; 
			gDpStr.Text_list[3] = 133;	gDpStr.Text_list[4] = 25;	gDpStr.Text_list[5] = 0; gDpStr.Text_list[6] = 0; 		
			break;			
		case TEXT_LIST_MSR_RST:
			gDpStr.Text_list[0] = 145;	gDpStr.Text_list[1] = 130; gDpStr.Text_list[2] = 173; 
			gDpStr.Text_list[3] = 56;	gDpStr.Text_list[4] = 86;	gDpStr.Text_list[5] = 0; gDpStr.Text_list[6] = 0; 		
			break;
		case TEXT_LIST_CH1_FREQ:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 133;	gDpStr.Text_list[5] = 157; gDpStr.Text_list[6] = 90; gDpStr.Text_list[7] = 0;
			gDpStr.Text_list[8] = 0;	gDpStr.Text_list[9] = 0;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;			
			break;			
		case TEXT_LIST_CH1_ECHO_AMP:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 90; gDpStr.Text_list[5] = 95; gDpStr.Text_list[6] = 13; gDpStr.Text_list[7] =42; 
			gDpStr.Text_list[8] = 0;	gDpStr.Text_list[9] = 0;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;			
			break;					
		case TEXT_LIST_CH1_THR_HEAVY:
#if 0
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 19;	gDpStr.Text_list[6] = 31; gDpStr.Text_list[7] = 42; gDpStr.Text_list[8] = 173; 
			gDpStr.Text_list[9] = 64;	gDpStr.Text_list[10] = 153; 
			gDpStr.Text_list[11] = 127; gDpStr.Text_list[12]=99; gDpStr.Text_list[13] = 0;
#else
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 137;
			gDpStr.Text_list[6] = 181;	gDpStr.Text_list[7] = 173; gDpStr.Text_list[8] = 185; gDpStr.Text_list[9] = 173; 
			gDpStr.Text_list[10] = 64;	gDpStr.Text_list[11] = 153; 
			gDpStr.Text_list[12] = 127; gDpStr.Text_list[13]=99; gDpStr.Text_list[14] = 0;

#endif
			break;			
		case TEXT_LIST_CH1_LIGHT:
#if 0
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 126;	gDpStr.Text_list[6] = 31; gDpStr.Text_list[7] = 42; gDpStr.Text_list[8] = 0; 
#else
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 183;	gDpStr.Text_list[6] = 184; gDpStr.Text_list[7] = 173; gDpStr.Text_list[8] = 185; 
#endif
			break;		
		case TEXT_LIST_CH1_HEAVY:
#if 0
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 19;	gDpStr.Text_list[6] = 31; gDpStr.Text_list[7] = 42; gDpStr.Text_list[8] = 0; 
#else
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 137;	gDpStr.Text_list[6] = 181; gDpStr.Text_list[7] = 173; gDpStr.Text_list[8] = 185; 

#endif
			break;			
		case TEXT_LIST_CH1_THR_LIGHT:
#if 0
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 126;	gDpStr.Text_list[6] = 31; gDpStr.Text_list[7] = 42; gDpStr.Text_list[8] = 173; 
			gDpStr.Text_list[9] = 64;	gDpStr.Text_list[10] = 153; 
			gDpStr.Text_list[11] = 127; gDpStr.Text_list[12]=99; gDpStr.Text_list[13] = 0;
#else
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 183;
			gDpStr.Text_list[6] = 184;	gDpStr.Text_list[7] = 173; gDpStr.Text_list[8] = 185; gDpStr.Text_list[9] = 173; 
			gDpStr.Text_list[10] = 64;	gDpStr.Text_list[11] = 153; 
			gDpStr.Text_list[12] = 127; gDpStr.Text_list[13]=99; 
			
#endif
			break;					
		case TEXT_LIST_CH1_ASF_VALUE:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 0;	gDpStr.Text_list[5] = 0; gDpStr.Text_list[6] = 0; gDpStr.Text_list[7] = 0; 
			gDpStr.Text_list[8] = 0; 	gDpStr.Text_list[9] = 0; 
			gDpStr.Text_list[10] = 0; gDpStr.Text_list[11]=0; gDpStr.Text_list[12] = 0;
			break;				
		case TEXT_LIST_CH1_DAMP:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173; gDpStr.Text_list[5] = 40;	gDpStr.Text_list[6] = 162; gDpStr.Text_list[7] = 0;
			break;							
		case TEXT_LIST_CH1_OFFSET:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;  gDpStr.Text_list[5] = 66;	gDpStr.Text_list[6] = 84; 
			gDpStr.Text_list[7] = 120; gDpStr.Text_list[8] = 43; gDpStr.Text_list[9] = 0;
			break;
		case TEXT_LIST_CH2_FREQ:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 133;	gDpStr.Text_list[5] = 157; gDpStr.Text_list[6] = 90; gDpStr.Text_list[7] = 0;
			gDpStr.Text_list[8] = 0;	gDpStr.Text_list[9] = 0;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0; 		
			break;			
		case TEXT_LIST_CH2_ECHO_AMP:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 90; gDpStr.Text_list[5] = 95; gDpStr.Text_list[6] = 13; gDpStr.Text_list[7] =42; 
			gDpStr.Text_list[8] = 0;	gDpStr.Text_list[9] = 0;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0; 		
			break;					
		case TEXT_LIST_CH2_THR_HEAVY:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 137;	gDpStr.Text_list[6] = 181; gDpStr.Text_list[7] = 173; gDpStr.Text_list[8] = 185;
			gDpStr.Text_list[9] = 173;  gDpStr.Text_list[10] = 64;	gDpStr.Text_list[11] = 153; 
			gDpStr.Text_list[12] = 127; gDpStr.Text_list[13]=99; gDpStr.Text_list[14] = 0;
			break;			
		case TEXT_LIST_CH2_THR_LIGHT:
#if 0
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 126;	gDpStr.Text_list[6] = 31; gDpStr.Text_list[7] = 42; gDpStr.Text_list[8] = 173; 
			gDpStr.Text_list[9] = 64;	gDpStr.Text_list[10] = 153; 
			gDpStr.Text_list[11] = 127; gDpStr.Text_list[12]=99; gDpStr.Text_list[13] = 0;
#else
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 183;
			gDpStr.Text_list[6] = 184;	gDpStr.Text_list[7] = 173; gDpStr.Text_list[8] = 185; gDpStr.Text_list[9] = 173; 
			gDpStr.Text_list[10] = 64;	gDpStr.Text_list[11] = 153; 
			gDpStr.Text_list[12] = 127; gDpStr.Text_list[13]=99; gDpStr.Text_list[14] = 0;
						

#endif
			break;		
		case TEXT_LIST_CH2_LIGHT:
#if 0
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 126;	gDpStr.Text_list[6] = 31; gDpStr.Text_list[7] = 42; gDpStr.Text_list[8] = 0; 
#else
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 183;	gDpStr.Text_list[6] = 184; gDpStr.Text_list[7] = 173; gDpStr.Text_list[8] = 185; 
#endif
			break;		
		case TEXT_LIST_CH2_HEAVY:
#if 0
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 19;	gDpStr.Text_list[6] = 31; gDpStr.Text_list[7] = 42; gDpStr.Text_list[8] = 0;
#else
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 137;	gDpStr.Text_list[6] = 181; gDpStr.Text_list[7] = 173; gDpStr.Text_list[8] = 185; 
#endif
			break;						
		case TEXT_LIST_CH2_ASF_VALUE:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 0;	gDpStr.Text_list[5] = 0; gDpStr.Text_list[6] = 0; gDpStr.Text_list[7] = 0; 
			gDpStr.Text_list[8] = 0;	gDpStr.Text_list[9] = 0; 
			gDpStr.Text_list[10] = 0; gDpStr.Text_list[11]=0; gDpStr.Text_list[12] = 0;
			break;				
		case TEXT_LIST_CH2_DAMP:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173; gDpStr.Text_list[5] = 40;	gDpStr.Text_list[6] = 162; gDpStr.Text_list[7] = 0;
			break;							
		case TEXT_LIST_CH2_OFFSET:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 66;	gDpStr.Text_list[6] = 84; 
			gDpStr.Text_list[7] = 120; gDpStr.Text_list[8] = 43; gDpStr.Text_list[9] = 0;
			break;
		case TEXT_LIST_CH1_ASSIGN:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 164;	gDpStr.Text_list[6] = 38; 
			gDpStr.Text_list[7] = 0; gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;
			break;					
		case TEXT_LIST_CH2_ASSIGN:	
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;	gDpStr.Text_list[5] = 164;	gDpStr.Text_list[6] = 38; 
			gDpStr.Text_list[7] = 0; gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;
			break;		
		case TEXT_LIST_CH1_SET:
		case TEXT_LIST_CH2_SET:	
			gDpStr.Text_list[0] = 83;	gDpStr.Text_list[1] = 130;  gDpStr.Text_list[2] = 0; gDpStr.Text_list[3] = 0; 
			gDpStr.Text_list[4] = 0;	gDpStr.Text_list[5] = 0;	gDpStr.Text_list[6] = 0; 
			gDpStr.Text_list[7] = 0; gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;
			break;	
		case TEXT_LIST_CH1_TRIM:
		case TEXT_LIST_CH2_TRIM:	
			gDpStr.Text_list[0] = 156;	gDpStr.Text_list[1] = 58;	gDpStr.Text_list[2] = 0; gDpStr.Text_list[3] = 0; 
			gDpStr.Text_list[4] = 0;	gDpStr.Text_list[5] = 0;	gDpStr.Text_list[6] = 0; 
			gDpStr.Text_list[7] = 0; gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;
			break;	
		case TEXT_LIST_CH1_OUTPUT:
		case TEXT_LIST_CH2_OUTPUT:	
			gDpStr.Text_list[0] = 144;	gDpStr.Text_list[1] = 51;	gDpStr.Text_list[2] = 0; gDpStr.Text_list[3] = 0; 
			gDpStr.Text_list[4] = 0;	gDpStr.Text_list[5] = 0;	gDpStr.Text_list[6] = 0; 
			gDpStr.Text_list[7] = 0; 	gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;
			break;	
		case TEXT_LIST_ASSIGN:
			gDpStr.Text_list[0] = 164;	gDpStr.Text_list[1] = 38; 	gDpStr.Text_list[2] = 0;			
			break;
		case TEXT_LIST_ACT:
			gDpStr.Text_list[0] = 129;	gDpStr.Text_list[1] = 128;	gDpStr.Text_list[2] = 173; 
			gDpStr.Text_list[3] = 182; 	gDpStr.Text_list[4] = 172; 	gDpStr.Text_list[5] =0; 	gDpStr.Text_list[6] = 0; 
			break;
		case TEXT_LIST_STOP:
			gDpStr.Text_list[0] = 129;	gDpStr.Text_list[1] = 128;	gDpStr.Text_list[2] = 173; 
			gDpStr.Text_list[3] = 107;	gDpStr.Text_list[4] = 58;	gDpStr.Text_list[5] = 0;	
			break;
		case TEXT_LIST_TEST:
			gDpStr.Text_list[0] = 128;	gDpStr.Text_list[1] = 16;	gDpStr.Text_list[2] = 0; 
			gDpStr.Text_list[3] = 0;	gDpStr.Text_list[4] = 0;	gDpStr.Text_list[5] = 0;	
			break;
		case TEXT_LIST_INTV:
			gDpStr.Text_list[0] = 133;	gDpStr.Text_list[1] = 25;	gDpStr.Text_list[2] = 0; 
			gDpStr.Text_list[3] = 0;	gDpStr.Text_list[4] = 0;	gDpStr.Text_list[5] = 0;	
			break;
		case TEXT_LIST_TERM:
			gDpStr.Text_list[0] = 93; gDpStr.Text_list[1] = 12; gDpStr.Text_list[2] = 0;
			break;			
		case TEXT_LIST_ERROR_DELAY:
			gDpStr.Text_list[0] = 136;	gDpStr.Text_list[1] = 106;
			gDpStr.Text_list[2] = 93;	gDpStr.Text_list[3] = 12;	gDpStr.Text_list[4] = 0; 	
			break;
		case TEXT_LIST_ERROR_OUTPUT:
			gDpStr.Text_list[0] = 144;	gDpStr.Text_list[1] = 51;
			gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0;	gDpStr.Text_list[4] = 0;	
			break;
		case TEXT_LIST_SAVE_INTV:
			gDpStr.Text_list[0] = 126;	gDpStr.Text_list[1] = 124;
			gDpStr.Text_list[2] = 133;	gDpStr.Text_list[3] = 25;	gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_DOWNLOAD:
			gDpStr.Text_list[0] = 35;	gDpStr.Text_list[1] = 113;
			gDpStr.Text_list[2] = 52;	gDpStr.Text_list[3] = 45;	gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_DELETE:
			gDpStr.Text_list[0] = 79;	gDpStr.Text_list[1] = 131;
			gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0;	gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_DISPLAY_TERM:
			gDpStr.Text_list[0] = 170;	gDpStr.Text_list[1] = 61;
			gDpStr.Text_list[2] = 133;	gDpStr.Text_list[3] = 25;	gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_PROTOCL:
			gDpStr.Text_list[0] = 161;	gDpStr.Text_list[1] = 52;
			gDpStr.Text_list[2] = 156;	gDpStr.Text_list[3] = 147;	gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_BAUDRATE:
			gDpStr.Text_list[0] = 41;	gDpStr.Text_list[1] = 120;	gDpStr.Text_list[2] = 152; gDpStr.Text_list[3] = 173; 
			gDpStr.Text_list[4] = 127;	gDpStr.Text_list[5] = 89;	gDpStr.Text_list[6] = 173; 
			gDpStr.Text_list[7] = 88; 	gDpStr.Text_list[8] = 42; gDpStr.Text_list[9] = 0;
			break;	
		case TEXT_LIST_ADDRESS:
			gDpStr.Text_list[0] = 133;	gDpStr.Text_list[1] = 87;
			gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0;	gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_CH1_ADDRESS:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 133;	gDpStr.Text_list[6] = 87;
			gDpStr.Text_list[7] = 0;
			break;
		case TEXT_LIST_CH2_ADDRESS:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173;
			gDpStr.Text_list[5] = 133;	gDpStr.Text_list[6] = 87;
			gDpStr.Text_list[7] = 0;
			break;		
		case TEXT_LIST_PASSCODE:
			gDpStr.Text_list[0] = 77;	gDpStr.Text_list[1] = 67;
			gDpStr.Text_list[2] = 70;	gDpStr.Text_list[3] = 169;	gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_LANG:
			gDpStr.Text_list[0] = 101;	gDpStr.Text_list[1] = 100;
			gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0;	gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_RETURN_MEAS:
			gDpStr.Text_list[0] = 123;	gDpStr.Text_list[1] = 43;	gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 170; 
			gDpStr.Text_list[4] = 61;	gDpStr.Text_list[5] = 173;	gDpStr.Text_list[6] = 74; 
			gDpStr.Text_list[7] = 22; 	gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;
			break;	
		case TEXT_LIST_CH1_SITE_NAME:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173; gDpStr.Text_list[5] = 167;	gDpStr.Text_list[6] = 124; gDpStr.Text_list[7] = 173;
			gDpStr.Text_list[8] = 120; gDpStr.Text_list[9] = 55;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;
			break;		
		case TEXT_LIST_CH2_SITE_NAME:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173; gDpStr.Text_list[5] = 167;	gDpStr.Text_list[6] = 124; gDpStr.Text_list[7] = 173;
			gDpStr.Text_list[8] = 120; gDpStr.Text_list[9] = 55;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;
			break;	
		case TEXT_LIST_SITE_NAME:
			gDpStr.Text_list[0] = 167;	gDpStr.Text_list[1] = 124;  gDpStr.Text_list[2] = 173;
			gDpStr.Text_list[3] = 120;  gDpStr.Text_list[4] = 55;	gDpStr.Text_list[5] = 0; gDpStr.Text_list[6] = 0;			
			break;
		case TEXT_LIST_FACTORY_RESET:
			gDpStr.Text_list[0] = 20;	gDpStr.Text_list[1] = 124;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 142; 
			gDpStr.Text_list[4] = 25; gDpStr.Text_list[5] = 170;	gDpStr.Text_list[6] = 0; gDpStr.Text_list[7] = 0;
			gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;
			break;	
		case TEXT_LIST_CH1_PROFILE_NO:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173; gDpStr.Text_list[5] = 134;	gDpStr.Text_list[6] = 141; gDpStr.Text_list[7] = 90;
			gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;
			break;		
		case TEXT_LIST_CH1_TVG:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 0; gDpStr.Text_list[5] = 0;	gDpStr.Text_list[6] = 0; gDpStr.Text_list[7] = 0;
			gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;
			break;		
		case TEXT_LIST_CH1_WINDOW_RESET_TIME:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173; gDpStr.Text_list[5] = 116;	gDpStr.Text_list[6] = 42; gDpStr.Text_list[7] = 112;
			gDpStr.Text_list[8] = 173; gDpStr.Text_list[9] = 56;	gDpStr.Text_list[10] = 86; gDpStr.Text_list[11] = 173;
			gDpStr.Text_list[12] = 93;	gDpStr.Text_list[13] = 12; gDpStr.Text_list[14] = 0;
			break;		
		case TEXT_LIST_CH1_WINDOW_RANGE:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 2; 
			gDpStr.Text_list[4] = 173; gDpStr.Text_list[5] = 116;	gDpStr.Text_list[6] = 42; gDpStr.Text_list[7] = 112;
			gDpStr.Text_list[8] = 173; gDpStr.Text_list[9] = 71;	gDpStr.Text_list[10] = 115; gDpStr.Text_list[11] = 0;
			gDpStr.Text_list[12] = 0;	gDpStr.Text_list[13] = 0; gDpStr.Text_list[14] = 0;
			break;	
		case TEXT_LIST_CH2_PROFILE_NO:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173; gDpStr.Text_list[5] = 134;	gDpStr.Text_list[6] = 141; gDpStr.Text_list[7] = 90;
			gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;
			break;		
		case TEXT_LIST_CH2_TVG:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 0; gDpStr.Text_list[5] = 0;	gDpStr.Text_list[6] = 0; gDpStr.Text_list[7] = 0;
			gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;
			break;		
		case TEXT_LIST_CH2_WINDOW_RESET_TIME:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173; gDpStr.Text_list[5] = 116;	gDpStr.Text_list[6] = 42; gDpStr.Text_list[7] = 112;
			gDpStr.Text_list[8] = 173; gDpStr.Text_list[9] = 56;	gDpStr.Text_list[10] = 86; gDpStr.Text_list[11] = 173;
			gDpStr.Text_list[12] = 93;	gDpStr.Text_list[13] = 12; gDpStr.Text_list[14] = 0;
			break;		
		case TEXT_LIST_CH2_WINDOW_RANGE:
			gDpStr.Text_list[0] = 140;	gDpStr.Text_list[1] = 29;  gDpStr.Text_list[2] = 173; gDpStr.Text_list[3] = 3; 
			gDpStr.Text_list[4] = 173; gDpStr.Text_list[5] = 116;	gDpStr.Text_list[6] = 42; gDpStr.Text_list[7] = 112;
			gDpStr.Text_list[8] = 173; gDpStr.Text_list[9] = 71;	gDpStr.Text_list[10] = 115; gDpStr.Text_list[11] = 0;
			gDpStr.Text_list[12] = 0;	gDpStr.Text_list[13] = 0; gDpStr.Text_list[14] = 0;
			break;
		case TEXT_LIST_THR_SYNC:
			gDpStr.Text_list[0] = 64;	gDpStr.Text_list[1] = 153;  gDpStr.Text_list[2] = 127; gDpStr.Text_list[3] = 99; 
			gDpStr.Text_list[4] = 173; gDpStr.Text_list[5] = 43;	gDpStr.Text_list[6] = 25; gDpStr.Text_list[7] = 170;
			gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;
			break;		
		case TEXT_LIST_MEASUREMENT:
			gDpStr.Text_list[0] = 145;	gDpStr.Text_list[1] = 130;  gDpStr.Text_list[2] = 0; 
			break;
		case TEXT_LIST_BASE:
			gDpStr.Text_list[0] = 25;	gDpStr.Text_list[1] = 75;  gDpStr.Text_list[2] = 0; 
			break;		
		case TEXT_LIST_CALIBRATION:
			gDpStr.Text_list[0] = 73;	gDpStr.Text_list[1] = 130;  gDpStr.Text_list[2] = 0; 
			break;		
		case TEXT_LIST_OUTPUT:
			gDpStr.Text_list[0] = 144;	gDpStr.Text_list[1] = 51;	gDpStr.Text_list[2] = 0; 
			break;	
		case TEXT_LIST_CURRENT_MENU:
			gDpStr.Text_list[0] = 127;	gDpStr.Text_list[1] = 54;	gDpStr.Text_list[2] = 0; 
			break;	
		case TEXT_LIST_RELAY:
			gDpStr.Text_list[0] = 57;	gDpStr.Text_list[1] = 49;	gDpStr.Text_list[2] = 120; gDpStr.Text_list[3] = 0; 
			break;	
		case TEXT_LIST_CLEAN:
			gDpStr.Text_list[0] = 84;	gDpStr.Text_list[1] = 130;	gDpStr.Text_list[2] = 0; 
			break;			
		case TEXT_LIST_ERROR:
			gDpStr.Text_list[0] = 103;	gDpStr.Text_list[1] = 48;	gDpStr.Text_list[2] = 0; 
			break;	
		case TEXT_LIST_DATA:
			gDpStr.Text_list[0] = 41;	gDpStr.Text_list[1] = 120;	gDpStr.Text_list[2] = 152;  gDpStr.Text_list[3] = 0; 
			break;				
		case TEXT_LIST_COMM:
			gDpStr.Text_list[0] = 175;	gDpStr.Text_list[1] = 95;	gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0; 
			break;	
		case TEXT_LIST_SYSTEM:
			gDpStr.Text_list[0] = 93;	gDpStr.Text_list[1] = 91;	gDpStr.Text_list[2] = 155;	gDpStr.Text_list[3] = 0; 
			break;	
		case TEXT_LIST_ENGINEER:
			gDpStr.Text_list[0] = 104;	gDpStr.Text_list[1] = 136;	gDpStr.Text_list[2] = 34;	gDpStr.Text_list[3] = 100; gDpStr.Text_list[4] = 0; 
			break;	
		case TEXT_LIST_FACTORY:
			gDpStr.Text_list[0] = 20;	gDpStr.Text_list[1] = 124;	gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;	
		case TEXT_LIST_TEST_MENU:
			gDpStr.Text_list[0] = 154;	gDpStr.Text_list[1] = 91;	gDpStr.Text_list[2] = 156;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_SLUDGE:
			gDpStr.Text_list[0] = 92;	gDpStr.Text_list[1] = 48;	gDpStr.Text_list[2] = 136;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_DISTANCE:
			gDpStr.Text_list[0] = 80;	gDpStr.Text_list[1] = 139;	gDpStr.Text_list[2] = 90;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;		
		case TEXT_LIST_AUTO:
			gDpStr.Text_list[0] = 123;	gDpStr.Text_list[1] = 43;	gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;	
		case TEXT_LIST_MANUAL:
			gDpStr.Text_list[0] = 90;	gDpStr.Text_list[1] = 43;	gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;	
		case TEXT_LIST_LIGHT:
#if 0
			gDpStr.Text_list[0] = 126;	gDpStr.Text_list[1] = 31;	gDpStr.Text_list[2] = 42;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0;
#else
			gDpStr.Text_list[0] = 183;	gDpStr.Text_list[1] = 184;	gDpStr.Text_list[2] = 173;	gDpStr.Text_list[3] = 185; gDpStr.Text_list[4] = 0;
#endif
			break;	
		case TEXT_LIST_HEAVY:
#if 0
			gDpStr.Text_list[0] = 19;	gDpStr.Text_list[1] = 31;	gDpStr.Text_list[2] = 42;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
#else
			gDpStr.Text_list[0] = 137;	gDpStr.Text_list[1] = 181;	gDpStr.Text_list[2] = 173;	gDpStr.Text_list[3] = 185; gDpStr.Text_list[4] = 0;
#endif
			break;		
		case TEXT_LIST_HOLD:
			gDpStr.Text_list[0] = 19;	gDpStr.Text_list[1] = 130;	gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;	
		case TEXT_LIST_ALARM:
			gDpStr.Text_list[0] = 178;	gDpStr.Text_list[1] = 179;	gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;	
		case TEXT_LIST_TIMER:
			gDpStr.Text_list[0] = 149;	gDpStr.Text_list[1] = 120;	gDpStr.Text_list[2] = 59; gDpStr.Text_list[3] = 0; 
			gDpStr.Text_list[4] = 25; gDpStr.Text_list[5] = 170;	gDpStr.Text_list[6] = 0; gDpStr.Text_list[7] = 0;
			gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;
			break;	
		case TEXT_LIST_RESET:
			gDpStr.Text_list[0] = 142;	gDpStr.Text_list[1] = 25;	gDpStr.Text_list[2] = 170; gDpStr.Text_list[3] = 0; 
			gDpStr.Text_list[4] = 25; gDpStr.Text_list[5] = 170;	gDpStr.Text_list[6] = 0; gDpStr.Text_list[7] = 0;
			gDpStr.Text_list[8] = 0; gDpStr.Text_list[9] = 0;	gDpStr.Text_list[10] = 0; gDpStr.Text_list[11] = 0;
			break;	
		case TEXT_LIST_YES:
			gDpStr.Text_list[0] = 30;	gDpStr.Text_list[1] = 0;	gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_NO:
			gDpStr.Text_list[0] = 98;	gDpStr.Text_list[1] = 34;	gDpStr.Text_list[2] = 109;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_ON:
			gDpStr.Text_list[0] = 176;	gDpStr.Text_list[1] = 25;	gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_OFF:
			gDpStr.Text_list[0] = 177;	gDpStr.Text_list[1] = 25;	gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_KOREAN:
			gDpStr.Text_list[0] = 181;	gDpStr.Text_list[1] = 180;	gDpStr.Text_list[2] = 100;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_ENGLISH:
			gDpStr.Text_list[0] = 108;	gDpStr.Text_list[1] = 100;	gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;
		case TEXT_LIST_MODE:
			gDpStr.Text_list[0] = 62;	gDpStr.Text_list[1] = 45;	gDpStr.Text_list[2] = 0;	gDpStr.Text_list[3] = 0; gDpStr.Text_list[4] = 0; 
			break;
		default:
			break;
	}
}

void DpSTR_GuiLeft_KOR(U16 x0, U16 y0, U32 col_fw, U32 col_bg, sFONT ft, I08 *pStr)
{
	LCD_SetFont(&ft);
	LCD_SetTextColor(col_fw);
	LCD_SetBackColor(col_bg);
	LCD_DisplayStringAt_KOR(x0, y0,  (U08*)pStr, DP_ALIGN_LEFT);
}

void DpSTR_GuiLeft(U16 x0, U16 y0, U32 col_fw, U32 col_bg, sFONT ft, I08 *pStr)
{
	LCD_SetFont(&ft);
	LCD_SetTextColor(col_fw);
	LCD_SetBackColor(col_bg);
	LCD_DisplayStringAt(x0, y0, (U08*)pStr, DP_ALIGN_LEFT);
}

void DpSTR_GuiLeftCursor(U16 x0, U16 y0, U32 col_fw, U32 col_fw_cursor, U32 col_bg, U08 cursor, sFONT ft, I08 *pStr)
{
	LCD_SetFont(&ft);
	LCD_SetTextColor(col_fw);
	LCD_SetBackColor(col_bg);
	LCD_DisplayStringCursor(x0, y0, (U08*)pStr, DP_ALIGN_LEFT, col_fw, col_fw_cursor, cursor);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - for Debug
//------------------------------------------------------------------------------------------------------------------------------
void DpSTR_DebugExp(U08 xn, U08 yn, I08* pStr)
{

#if 0
	//if(!MnEGN_PrGet_Item(MnEGN_I03_fDP_DBG))
	//	return;

	if((x0 > 780) || (y0 > 460))
		return;

	DpFIG_DrwRect(x0, y0, 300, 18, _cBGD_SCRN, DpFIG_FILL);
	LCD_SetFont(&_fE12HsM);
	LCD_SetTextColor(_cSD_LIGHTGRAY);
	LCD_SetBackColor(_cBGD_SCRN);
	LCD_DisplayStringAt(x0, y0, (U08*)pStr, DP_ALIGN_LEFT);
#endif
}

void DpSTR_DebugExp_2(U08 y, I08* pStr)
{
	U16 x0 = 300;
	//U16 y0 = 360+(20*y);
	U16 y0 = 300+(20*y);

	if((x0 > 780) || (y0 > 460))
		return;

	DpFIG_DrwRect(x0, y0, 300, 18, _cBGD_SCRN, DpFIG_FILL);
	LCD_SetFont(&_fE12HsM);
	LCD_SetTextColor(_cSD_LIGHTGREEN);
	LCD_SetBackColor(_cBGD_SCRN);
	LCD_DisplayStringAt(x0, y0, (U08*)pStr, DP_ALIGN_LEFT);
}

void DpSTR_InitMain(void)
{
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			DpSTR_GuiList(TEXT_LIST_NO);
			_SPRINTF(gDpStr.sYnN[MENU_CHK_NO],	gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_YES);
			_SPRINTF(gDpStr.sYnN[MENU_CHK_YES], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_OFF);
			_SPRINTF(gDpStr.sOnF[MENU_CHK_NO],	gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_ON);
			_SPRINTF(gDpStr.sOnF[MENU_CHK_YES], gDpStr.Text_list);
			break;
		case MnSYS_LANG_ENG:
		default:
			_SPRINTF(gDpStr.sYnN[MENU_CHK_NO],  _sNo);
			_SPRINTF(gDpStr.sYnN[MENU_CHK_YES], _sYes);

			_SPRINTF(gDpStr.sOnF[MENU_CHK_NO],  _sOFF);
			_SPRINTF(gDpStr.sOnF[MENU_CHK_YES], _sON);
			break;
	}

}

//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

