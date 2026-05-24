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
// display
#include "disp_color.h"
#include "disp_string.h"
#include "disp_figure.h"
#include "disp_titlebar.h"
#include "disp_button.h"
// selp
#include "disp_figure.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
DpFIG_LS lDpFig;


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation - Initial
//------------------------------------------------------------------------------------------------------------------------------
void DpFIG_InitMain(void)
{

}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Live
//------------------------------------------------------------------------------------------------------------------------------
void DpFIG_LiveLnH(U16 x0, U16 y0, U16 len, U32 col)
{
	LCD_SetTextColor(col);
	LCD_DrawHLine(x0, y0, len);

	if(LCD_GetLayer() == LCD_FRM_0)		LCD_SetLayer(LCD_FRM_1);
	else								LCD_SetLayer(LCD_FRM_0);

	LCD_SetTextColor(col);
	LCD_DrawHLine(x0, y0, len);

	if(LCD_GetLayer() == LCD_FRM_0)		LCD_SetLayer(LCD_FRM_1);
	else								LCD_SetLayer(LCD_FRM_0);
}

void DpFIG_LiveRct(U16 x0, U16 y0, U16 wid, U16 hei, U32 col, U08 opt)
{
	U08 i;

	LCD_SetTextColor(col);

	if(opt == DpFIG_FILL)
		LCD_FillRect(x0, y0, wid, hei);
	else
	{
		if((opt >= wid/2) || (opt >= hei/2) || (opt >= DpFIG_TK_NUMB))
			return;

		for(i=0; i<opt; i++)
			LCD_DrawRect(x0+i, y0+i, wid-(i*2), hei-(i*2));
	}

	if(LCD_GetLayer() == LCD_FRM_0)		LCD_SetLayer(LCD_FRM_1);
	else								LCD_SetLayer(LCD_FRM_0);

	LCD_SetTextColor(col);

	if(opt == DpFIG_FILL)
		LCD_FillRect(x0, y0, wid, hei);
	else
	{
		if((opt >= wid/2) || (opt >= hei/2) || (opt >= DpFIG_TK_NUMB))
			return;

		for(i=0; i<opt; i++)
			LCD_DrawRect(x0+i, y0+i, wid-(i*2), hei-(i*2));
	}

	if(LCD_GetLayer() == LCD_FRM_0)		LCD_SetLayer(LCD_FRM_1);
	else								LCD_SetLayer(LCD_FRM_0);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Draw
//------------------------------------------------------------------------------------------------------------------------------
void DpFIG_DrwLinH(U16 x0, U16 y0, U16 len, U32 col)
{
	LCD_SetTextColor(col);
	LCD_DrawHLine(x0, y0, len);
}

void DpFIG_DrwLinV(U16 x0, U16 y0, U16 len, U32 col)
{
	LCD_SetTextColor(col);
	LCD_DrawVLine(x0, y0, len);
}

void DpFIG_DrwLine(U16 x0, U16 y0, U16 x1, U16 y1, U32 col)
{
	LCD_SetTextColor(col);
	LCD_DrawLine(x0, y0, x1, y1);
}

void DpFIG_DrwRect(U16 x0, U16 y0, U16 wid, U16 hei, U32 col, U08 opt)
{
	U08 i;

	LCD_SetTextColor(col);

	if(opt == DpFIG_FILL)
		LCD_FillRect(x0, y0, wid, hei);
	else
	{
		if((opt >= wid/2) || (opt >= hei/2) || (opt >= DpFIG_TK_NUMB))
			return;

		for(i=0; i<opt; i++)
			LCD_DrawRect(x0+i, y0+i, wid-(i*2), hei-(i*2));
	}
}

void DpFIG_DrwCirc(U16 x0, U16 y0, U16 rad, U32 col, U08 fFill)
{
	LCD_SetTextColor(col);

	if(fFill)		LCD_FillCircle(x0, y0, rad);
	else			LCD_DrawCircle(x0, y0, rad);
}

void DpFIG_DrwElli(U16 x0, U16 y0, U16 xR, U16 yR, U32 col, U08 fFill)
{
	LCD_SetTextColor(col);

	if(fFill)		LCD_FillEllipse(x0, y0, xR, yR);
	else			LCD_DrawEllipse(x0, y0, xR, yR);
}

void DpFIG_DrwTria(U16 x0, U16 y0, U16 x1, U16 y1, U16 x2, U16 y2, U32 col)
{
	LCD_SetTextColor(col);
	LCD_FillTriangle(x0, x1, x2, y0, y1, y2);
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

