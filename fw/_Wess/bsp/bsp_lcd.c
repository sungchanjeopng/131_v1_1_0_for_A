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
// hal
#include <string.h>
#include "stm32f7xx_hal.h"
#include "dma.h"
// bsp
#include "bsp_adc.h"
#include "bsp_demux.h"
#include "bsp_gpio.h"
#include "bsp_usb.h"
// font
#include "fonts.h"
#include "ft_han_sans_bold_150.h"
#include "ft_han_sans_bold_75.h"
#include "ft_han_sans_bold_35.h"
#include "ft_han_sans_bold_22.h"
#include "ft_han_sans_normal_22.h"
#include "ft_han_sans_bold_17.h"
#include "ft_han_sans_medium_12.h"
// display
#include "disp_color.h"
#include "disp_figure.h"
// self
#include "bsp_lcd.h"

#include "data_commu.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
static LCD_LS lLcd_aIdx[LCD_FRM_MAX];		// array: Draw Prop

static U08 lLcd_iAct = LCD_FRM_0;			// Index: Active Layer

#define LCD_BMP_HDR_SIZE    (54U)
#define LCD_BMP_MAX_WIDTH   (800U)
static U08 s_LcdBmpRow[(LCD_BMP_MAX_WIDTH * 3U) + 4U];


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
U32 LcdGet_SizeX(void)		{	return hLtdcHandler.LayerCfg[lLcd_iAct].ImageWidth;		}
U32 LcdGet_SizeY(void)		{	return hLtdcHandler.LayerCfg[lLcd_iAct].ImageHeight;	}

void LcdSet_SizeX(U32 width)	{	hLtdcHandler.LayerCfg[lLcd_iAct].ImageWidth  = width;		}
void LcdSet_SizeY(U32 height)	{	hLtdcHandler.LayerCfg[lLcd_iAct].ImageHeight = height;		}

void LcdSet_AlphaDft (U32 idx, U08 transp)		{	HAL_LTDC_SetAlpha		  (&hLtdcHandler, transp, idx);		}
void LcdSet_AlphaNoRd(U32 idx, U08 transp)		{	HAL_LTDC_SetAlpha_NoReload(&hLtdcHandler, transp, idx);		}
void LcdSet_AddrDft  (U32 idx, U32 addr)		{	HAL_LTDC_SetAddress			(&hLtdcHandler, addr, idx);		}
void LcdSet_AddrNoRd (U32 idx, U32 addr)		{	HAL_LTDC_SetAddress_NoReload(&hLtdcHandler, addr, idx);		}

void LcdSet_WindowDft(U16 LayerIndex, U16 Xpos, U16 Ypos, U16 Width, U16 Height)
{
	/* Reconfigure the layer size */
	HAL_LTDC_SetWindowSize(&hLtdcHandler, Width, Height, LayerIndex);

	/* Reconfigure the layer position */
	HAL_LTDC_SetWindowPosition(&hLtdcHandler, Xpos, Ypos, LayerIndex); 
}

void LcdSet_WindowNoRd(U16 LayerIndex, U16 Xpos, U16 Ypos, U16 Width, U16 Height)
{
	/* Reconfigure the layer size */
	HAL_LTDC_SetWindowSize_NoReload(&hLtdcHandler, Width, Height, LayerIndex);

	/* Reconfigure the layer position */
	HAL_LTDC_SetWindowPosition_NoReload(&hLtdcHandler, Xpos, Ypos, LayerIndex); 
}

void LcdSet_ColKeyDft(U32 LayerIndex, U32 RGBValue)
{  
  /* Configure and Enable the color Keying for LCD Layer */
  HAL_LTDC_ConfigColorKeying(&hLtdcHandler, RGBValue, LayerIndex);
  HAL_LTDC_EnableColorKeying(&hLtdcHandler, LayerIndex);
}

void LcdSet_ColKeyNoRd(U32 LayerIndex, U32 RGBValue)
{  
  /* Configure and Enable the color Keying for LCD Layer */
  HAL_LTDC_ConfigColorKeying_NoReload(&hLtdcHandler, RGBValue, LayerIndex);
  HAL_LTDC_EnableColorKeying_NoReload(&hLtdcHandler, LayerIndex);
}

void LcdSet_ViewDft(U32 LayerIndex, FunctionalState State)
{
	if(State == ENABLE)
	{
		__HAL_LTDC_LAYER_ENABLE(&hLtdcHandler, LayerIndex);
	}
	else
	{
		__HAL_LTDC_LAYER_DISABLE(&hLtdcHandler, LayerIndex);
	}
	/* Do not Sets the Reload  */
} 

void LcdSet_ViewReload(U32 LayerIndex, FunctionalState State)
{
	if(State == ENABLE)		__HAL_LTDC_LAYER_ENABLE (&hLtdcHandler, LayerIndex);
	else					__HAL_LTDC_LAYER_DISABLE(&hLtdcHandler, LayerIndex);

	__HAL_LTDC_RELOAD_CONFIG(&hLtdcHandler);
}

void LcdRst_ColKeyDft (U32 LayerIndex)	{	HAL_LTDC_DisableColorKeying			(&hLtdcHandler, LayerIndex);	}
void LcdRst_ColKeyNoRd(U32 LayerIndex)	{	HAL_LTDC_DisableColorKeying_NoReload(&hLtdcHandler, LayerIndex);	}

void LcdCfg_Reload(U32 ReloadType)		{	HAL_LTDC_Reload (&hLtdcHandler, ReloadType);		}


void LcdDraw_Pixel(U16 Xpos, U16 Ypos, U32 RGB_Code)
{
  /* Write data value to all SDRAM memory */
  if(hLtdcHandler.LayerCfg[lLcd_iAct].PixelFormat == LTDC_PIXEL_FORMAT_RGB565)
  { /* RGB565 format */
    *(__IO U16*) (hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress + (2*(Ypos*LcdGet_SizeX() + Xpos))) = (U16)RGB_Code;
  }
  else
  { /* ARGB8888 format */
    *(__IO U32*) (hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress + (4*(Ypos*LcdGet_SizeX() + Xpos))) = RGB_Code;
  }
}

static void LcdDraw_Char(U16 Xpos, U16 Ypos, const U08 *c)
{
	U32 i = 0, j = 0;
	U16 height, width;
	U08  offset;
	U08  *pchar;
	U32 line;

	Xpos = 799 - Xpos;
	Ypos = 479 - Ypos;

	height = lLcd_aIdx[lLcd_iAct].pFont->info->Height;
	width  = lLcd_aIdx[lLcd_iAct].pFont->info->Width;

	offset = 8 * ((width + 7)/8) - width ;

	for(i = 0; i < height; i++)
	{
		pchar = ((U08 *)c + (width + 7)/8 * i);

		switch(((width + 7)/8))
		{
			case 1:
				line =  pchar[0];      
				break;
			case 2:
				line =  (pchar[0]<< 8) | pchar[1];      
				break;
			case 3:
				line =	(pchar[0]<< 16) | (pchar[1]<< 8) | pchar[2];
				break;
			case 4:
			default:
				line =	(pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2]<< 8) | pchar[3];
				break;
		} 

		for (j = 0; j < width; j++)
		{
			if(line & (1 << (width- j + offset- 1))) 
			{
				LcdDraw_Pixel((Xpos - j), Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
			}
			else
			{
				LcdDraw_Pixel((Xpos - j), Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			} 
		}
		Ypos--;
	}
}

static void LcdDraw_Char_2(U16 Xpos, U16 Ypos, U16 fw, U16 fh, const U08 *c)
{
	U32 i = 0, j = 0;
	U16 height, width;
	U08 offset;
	U08 *pchar;
	U08 char_bytes;
	U64 char_bit;
	U32 line[6];

	Xpos = 799 - Xpos;
	Ypos = 479 - Ypos;

	height = fh;
	width  = fw;

	char_bytes = (width+7)/8;
	
	offset = (char_bytes*8) - width;

	for(i=0; i<height; i++)
	{
		pchar = ((U08 *)c + (char_bytes*i));

		switch(char_bytes)
		{
			case 1:
				line[0] = pchar[0];
				break;
			case 2:
				line[0] = (pchar[0]<< 8) | pchar[1];
				break;
			case 3:
				line[0] = (pchar[0]<< 16) | (pchar[1]<< 8) | pchar[2];
				break;
			case 4:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2]<< 8) | pchar[3];
				break;
			case 5:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2]<< 8) | pchar[3];
				line[1] = pchar[4];
				break;
			case 6:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2]<< 8) | pchar[3];
				line[1] = (pchar[4]<< 8 ) | pchar[5];
				break;
			case 7:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2]<< 8) | pchar[3];
				line[1] = (pchar[4]<< 16) | (pchar[5]<< 8 ) | pchar[6];
				break;
			case 8:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2]<< 8) | pchar[3];
				line[1] = (pchar[4]<< 24) | (pchar[5]<< 16) | (pchar[6]<< 8) | pchar[7];
				break;
			case 9:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2]<< 8) | pchar[3];
				line[1] = (pchar[4]<< 24) | (pchar[5]<< 16) | (pchar[6]<< 8) | pchar[7];
				line[2] = pchar[8];
				break;
			case 10:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2]<< 8) | pchar[3];
				line[1] = (pchar[4]<< 24) | (pchar[5]<< 16) | (pchar[6]<< 8) | pchar[7];
				line[2] = (pchar[8]<< 8 ) | pchar[9];
				break;
			case 11:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2]<< 8) | pchar[3];
				line[1] = (pchar[4]<< 24) | (pchar[5]<< 16) | (pchar[6]<< 8) | pchar[7];
				line[2] = (pchar[8]<< 16) | (pchar[9]<< 8 ) | pchar[10];
				break;
			case 12:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24) | (pchar[5]<< 16) | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24) | (pchar[9]<< 16) | (pchar[10]<< 8) | pchar[11];
				break;
			case 13:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24) | (pchar[5]<< 16) | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24) | (pchar[9]<< 16) | (pchar[10]<< 8) | pchar[11];
				line[3] = pchar[12];
				break;
			case 14:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24) | (pchar[5]<< 16) | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24) | (pchar[9]<< 16) | (pchar[10]<< 8) | pchar[11];
				line[3] = (pchar[12]<< 8) | pchar[13];
				break;
			case 15:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24) | (pchar[5]<< 16) | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24) | (pchar[9]<< 16) | (pchar[10]<< 8) | pchar[11];
				line[3] = (pchar[12]<< 16) | (pchar[13]<< 8) | pchar[14];
				break;
			case 16:
				line[0] = (pchar[0]<< 24)  | (pchar[1]<< 16)  | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24)  | (pchar[5]<< 16)  | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24)  | (pchar[9]<< 16)  | (pchar[10]<< 8) | pchar[11];
				line[3] = (pchar[12]<< 24) | (pchar[13]<< 16) | (pchar[14]<< 8) | pchar[15];
				break;
			case 17:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24) | (pchar[5]<< 16) | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24) | (pchar[9]<< 16) | (pchar[10]<< 8) | pchar[11];
				line[3] = (pchar[12]<< 24) | (pchar[13]<< 16) | (pchar[14]<< 8) | pchar[15];
				line[4] = pchar[16];
				break;
			case 18:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24) | (pchar[5]<< 16) | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24) | (pchar[9]<< 16) | (pchar[10]<< 8) | pchar[11];
				line[3] = (pchar[12]<< 24) | (pchar[13]<< 16) | (pchar[14]<< 8) | pchar[15];
				line[4] = (pchar[16]<< 8) | pchar[17];
				break;
			case 19:
				line[0] = (pchar[0]<< 24) | (pchar[1]<< 16) | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24) | (pchar[5]<< 16) | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24) | (pchar[9]<< 16) | (pchar[10]<< 8) | pchar[11];
				line[3] = (pchar[12]<< 24) | (pchar[13]<< 16) | (pchar[14]<< 8) | pchar[15];
				line[4] = (pchar[16]<< 16) | (pchar[17]<< 8) | pchar[18];
				break;
			case 20:
				line[0] = (pchar[0]<< 24)  | (pchar[1]<< 16)  | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24)  | (pchar[5]<< 16)  | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24)  | (pchar[9]<< 16)  | (pchar[10]<< 8) | pchar[11];
				line[3] = (pchar[12]<< 24) | (pchar[13]<< 16) | (pchar[14]<< 8) | pchar[15];
				line[4] = (pchar[16]<< 24) | (pchar[17]<< 16) | (pchar[18]<< 8) | pchar[19];
				break;
			case 21:
				line[0] = (pchar[0]<< 24)  | (pchar[1]<< 16)  | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24)  | (pchar[5]<< 16)  | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24)  | (pchar[9]<< 16)  | (pchar[10]<< 8) | pchar[11];
				line[3] = (pchar[12]<< 24) | (pchar[13]<< 16) | (pchar[14]<< 8) | pchar[15];
				line[4] = (pchar[16]<< 24) | (pchar[17]<< 16) | (pchar[18]<< 8) | pchar[19];
				line[5] = pchar[20];
				break;
			case 22:
				line[0] = (pchar[0]<< 24)  | (pchar[1]<< 16)  | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24)  | (pchar[5]<< 16)  | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24)  | (pchar[9]<< 16)  | (pchar[10]<< 8) | pchar[11];
				line[3] = (pchar[12]<< 24) | (pchar[13]<< 16) | (pchar[14]<< 8) | pchar[15];
				line[4] = (pchar[16]<< 24) | (pchar[17]<< 16) | (pchar[18]<< 8) | pchar[19];
				line[5] = (pchar[20]<< 8)  | pchar[21];
				break;
			case 23:
				line[0] = (pchar[0]<< 24)  | (pchar[1]<< 16)  | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24)  | (pchar[5]<< 16)  | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24)  | (pchar[9]<< 16)  | (pchar[10]<< 8) | pchar[11];
				line[3] = (pchar[12]<< 24) | (pchar[13]<< 16) | (pchar[14]<< 8) | pchar[15];
				line[4] = (pchar[16]<< 24) | (pchar[17]<< 16) | (pchar[18]<< 8) | pchar[19];
				line[5] = (pchar[20]<< 16) | (pchar[21]<< 8)  | pchar[22];
				break;
			case 24:
				line[0] = (pchar[0]<< 24)  | (pchar[1]<< 16)  | (pchar[2] << 8) | pchar[3];
				line[1] = (pchar[4]<< 24)  | (pchar[5]<< 16)  | (pchar[6] << 8) | pchar[7];
				line[2] = (pchar[8]<< 24)  | (pchar[9]<< 16)  | (pchar[10]<< 8) | pchar[11];
				line[3] = (pchar[12]<< 24) | (pchar[13]<< 16) | (pchar[14]<< 8) | pchar[15];
				line[4] = (pchar[16]<< 24) | (pchar[17]<< 16) | (pchar[18]<< 8) | pchar[19];
				line[5] = (pchar[20]<< 24) | (pchar[21]<< 16) | (pchar[22]<< 8) | pchar[23];
				break;
		} 

		if(char_bytes<5)
		{
			for (j=0; j<width; j++)
			{
				char_bit = 1 << (width-j+offset-1);

				if	(line[0] & char_bit)	LcdDraw_Pixel(Xpos-j, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
		}
		else if(char_bytes<9)
		{
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);

				if	(line[0] & char_bit)	LcdDraw_Pixel(Xpos-j, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
			
			for (j=0; j<(width-32); j++)
			{
				char_bit = 1 << (width-32-j+offset-1);
				
				if	(line[1] & char_bit)	LcdDraw_Pixel(Xpos-j-32, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j-32, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
		}
		else if(char_bytes<13)
		{
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);

				if	(line[0] & char_bit)	LcdDraw_Pixel(Xpos-j, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
			
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);
				
				if	(line[1] & char_bit)	LcdDraw_Pixel(Xpos-j-32, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j-32, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
			
			for (j=0; j<(width-64); j++)
			{
				char_bit = 1 << (width-64-j+offset-1);
				
				if	(line[2] & char_bit)	LcdDraw_Pixel((Xpos-j-64), Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel((Xpos-j-64), Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
		}
		else if(char_bytes<17)
		{
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);

				if	(line[0] & char_bit)	LcdDraw_Pixel(Xpos-j, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
			
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);
				
				if	(line[1] & char_bit)	LcdDraw_Pixel(Xpos-j-32, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j-32, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
	
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);
				
				if	(line[2] & char_bit)	LcdDraw_Pixel(Xpos-j-64, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j-64, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}

			for (j=0; j<(width-96); j++)
			{
				char_bit = 1 << (width-96-j+offset-1);
				
				if	(line[3] & char_bit)	LcdDraw_Pixel((Xpos-j-96), Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel((Xpos-j-96), Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
		}
		else if (char_bytes<21)
		{
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);

				if	(line[0] & char_bit)	LcdDraw_Pixel(Xpos-j, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
			
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);
				
				if	(line[1] & char_bit)	LcdDraw_Pixel(Xpos-j-32, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j-32, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
	
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);
				
				if	(line[2] & char_bit)	LcdDraw_Pixel(Xpos-j-64, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j-64, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}

			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);
				
				if	(line[3] & char_bit)	LcdDraw_Pixel(Xpos-j-96, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j-96, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}

			for (j=0; j<(width-128); j++)
			{
				char_bit = 1 << (width-128-j+offset-1);
				
				if	(line[4] & char_bit)	LcdDraw_Pixel((Xpos-j-128), Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel((Xpos-j-128), Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
		}
		else
		{
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);
			
				if	(line[0] & char_bit)	LcdDraw_Pixel(Xpos-j, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
			
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);
				
				if	(line[1] & char_bit)	LcdDraw_Pixel(Xpos-j-32, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j-32, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
			
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);
				
				if	(line[2] & char_bit)	LcdDraw_Pixel(Xpos-j-64, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j-64, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
			
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);
				
				if	(line[3] & char_bit)	LcdDraw_Pixel(Xpos-j-96, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j-96, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
			
			for (j=0; j<32; j++)
			{
				char_bit = 1 << (32-j-1);
				
				if	(line[4] & char_bit)	LcdDraw_Pixel(Xpos-j-128, Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel(Xpos-j-128, Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
			
			for (j=0; j<(width-160); j++)
			{
				char_bit = 1 << (width-160-j+offset-1);
				
				if	(line[5] & char_bit)	LcdDraw_Pixel((Xpos-j-160), Ypos, lLcd_aIdx[lLcd_iAct].TextColor);
				else						LcdDraw_Pixel((Xpos-j-160), Ypos, lLcd_aIdx[lLcd_iAct].BackColor);
			}
		}
		
		Ypos--;
	}
}


/**
  * @brief  Fills a buffer.
  * @param  LayerIndex: Layer index
  * @param  pDst: Pointer to destination buffer
  * @param  xSize: Buffer width
  * @param  ySize: Buffer height
  * @param  OffLine: Offset
  * @param  ColorIndex: Color index
  * @retval None
  */
static void LcdLl_FillBuffer(U32 LayerIndex, void *pDst, U32 xSize, U32 ySize, U32 OffLine, U32 ColorIndex) 
{
  /* Register to memory mode with ARGB8888 as color Mode */ 
  hDma2dHandler.Init.Mode         = DMA2D_R2M;
  if(hLtdcHandler.LayerCfg[lLcd_iAct].PixelFormat == LTDC_PIXEL_FORMAT_RGB565)
  { /* RGB565 format */ 
    hDma2dHandler.Init.ColorMode    = DMA2D_RGB565;
  }
  else
  { /* ARGB8888 format */
    hDma2dHandler.Init.ColorMode    = DMA2D_ARGB8888;
  }
  hDma2dHandler.Init.OutputOffset = OffLine;      
  
  hDma2dHandler.Instance = DMA2D;
  
  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hDma2dHandler) == HAL_OK) 
  {
    if(HAL_DMA2D_ConfigLayer(&hDma2dHandler, LayerIndex) == HAL_OK) 
    {
      if (HAL_DMA2D_Start(&hDma2dHandler, ColorIndex, (U32)pDst, xSize, ySize) == HAL_OK)
      {
        /* Polling For DMA transfer */  
        HAL_DMA2D_PollForTransfer(&hDma2dHandler, 10);
      }
    }
  } 
}

/**
  * @brief  Converts a line to an ARGB8888 pixel format.
  * @param  pSrc: Pointer to source buffer
  * @param  pDst: Output color
  * @param  xSize: Buffer width
  * @param  ColorMode: Input color mode   
  * @retval None
  */
static void LcdLl_CvtLine2ARGB8888(void *pSrc, void *pDst, U32 xSize, U32 ColorMode)
{    
  /* Configure the DMA2D Mode, Color Mode and output offset */
  hDma2dHandler.Init.Mode         = DMA2D_M2M_PFC;
  hDma2dHandler.Init.ColorMode    = DMA2D_ARGB8888;
  hDma2dHandler.Init.OutputOffset = 0;     
  
  /* Foreground Configuration */
  hDma2dHandler.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hDma2dHandler.LayerCfg[1].InputAlpha = 0xFF;
  hDma2dHandler.LayerCfg[1].InputColorMode = ColorMode;
  hDma2dHandler.LayerCfg[1].InputOffset = 0;
  
  hDma2dHandler.Instance = DMA2D; 
  
  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hDma2dHandler) == HAL_OK) 
  {
    if(HAL_DMA2D_ConfigLayer(&hDma2dHandler, 1) == HAL_OK) 
    {
      if (HAL_DMA2D_Start(&hDma2dHandler, (U32)pSrc, (U32)pDst, xSize, 1) == HAL_OK)
      {
        /* Polling For DMA transfer */  
        HAL_DMA2D_PollForTransfer(&hDma2dHandler, 10);
      }
    }
  } 
}

void LcdInit_Default(U16 LayerIndex, U32 FB_Address)
{     
  LCD_LayerCfgTypeDef  layer_cfg;

  /* Layer Init */
  layer_cfg.WindowX0 = 0;
  layer_cfg.WindowX1 = LcdGet_SizeX();
  layer_cfg.WindowY0 = 0;
  layer_cfg.WindowY1 = LcdGet_SizeY(); 
  layer_cfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  layer_cfg.FBStartAdress = FB_Address;
  layer_cfg.Alpha = 255;
  layer_cfg.Alpha0 = 0;
  layer_cfg.Backcolor.Blue = 0;
  layer_cfg.Backcolor.Green = 0;
  layer_cfg.Backcolor.Red = 0;
  layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  layer_cfg.ImageWidth = LcdGet_SizeX();
  layer_cfg.ImageHeight = LcdGet_SizeY();
  
  HAL_LTDC_ConfigLayer(&hLtdcHandler, &layer_cfg, LayerIndex); 

  lLcd_aIdx[LayerIndex].BackColor = _cSD_BLACK;
  lLcd_aIdx[LayerIndex].pFont     = &Ft22_HanSansBold;
  lLcd_aIdx[LayerIndex].TextColor = _cSD_WHITE; 
}

void LcdInit_Rgb565(U16 LayerIndex, U32 FB_Address)
{     
  LCD_LayerCfgTypeDef  layer_cfg;

  /* Layer Init */
  layer_cfg.WindowX0 = 0;
  layer_cfg.WindowX1 = LcdGet_SizeX();
  layer_cfg.WindowY0 = 0;
  layer_cfg.WindowY1 = LcdGet_SizeY(); 
  layer_cfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  layer_cfg.FBStartAdress = FB_Address;
  layer_cfg.Alpha = 255;
  layer_cfg.Alpha0 = 0;
  layer_cfg.Backcolor.Blue = 0;
  layer_cfg.Backcolor.Green = 0;
  layer_cfg.Backcolor.Red = 0;
  layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  layer_cfg.ImageWidth = LcdGet_SizeX();
  layer_cfg.ImageHeight = LcdGet_SizeY();
  
  HAL_LTDC_ConfigLayer(&hLtdcHandler, &layer_cfg, LayerIndex); 

  lLcd_aIdx[LayerIndex].BackColor = _cSD_BLACK;
  lLcd_aIdx[LayerIndex].pFont     = &Ft22_HanSansBold;
  lLcd_aIdx[LayerIndex].TextColor = _cSD_WHITE;
}

U32 LcdRead_Pixel(U16 Xpos, U16 Ypos)
{
  U32 ret = 0;
  
  if(hLtdcHandler.LayerCfg[lLcd_iAct].PixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
  {
    /* Read data value from SDRAM memory */
    ret = *(__IO U32*) (hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress + (4*(Ypos*LcdGet_SizeX() + Xpos)));
  }
  else if(hLtdcHandler.LayerCfg[lLcd_iAct].PixelFormat == LTDC_PIXEL_FORMAT_RGB888)
  {
    /* Read data value from SDRAM memory */
    ret = (*(__IO U32*) (hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress + (4*(Ypos*LcdGet_SizeX() + Xpos))) & 0x00FFFFFF);
  }
  else if((hLtdcHandler.LayerCfg[lLcd_iAct].PixelFormat == LTDC_PIXEL_FORMAT_RGB565) || \
          (hLtdcHandler.LayerCfg[lLcd_iAct].PixelFormat == LTDC_PIXEL_FORMAT_ARGB4444) || \
          (hLtdcHandler.LayerCfg[lLcd_iAct].PixelFormat == LTDC_PIXEL_FORMAT_AL88))  
  {
    /* Read data value from SDRAM memory */
    ret = *(__IO U16*) (hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress + (2*(Ypos*LcdGet_SizeX() + Xpos)));    
  }
  else
  {
    /* Read data value from SDRAM memory */
    ret = *(__IO U08*) (hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress + (2*(Ypos*LcdGet_SizeX() + Xpos)));    
  }
  
  return ret;
}

static void LcdBmp_PutLe16(U08 *p, U16 v)
{
	p[0] = (U08)(v & 0xFFU);
	p[1] = (U08)((v >> 8) & 0xFFU);
}

static void LcdBmp_PutLe32(U08 *p, U32 v)
{
	p[0] = (U08)(v & 0xFFU);
	p[1] = (U08)((v >> 8) & 0xFFU);
	p[2] = (U08)((v >> 16) & 0xFFU);
	p[3] = (U08)((v >> 24) & 0xFFU);
}

static void LcdBmp_PixelToBgr(U32 pix, U32 fmt, U08 *bgr)
{
	U08 r, g, b;

	if(fmt == LTDC_PIXEL_FORMAT_RGB565)
	{
		U16 p = (U16)pix;
		r = (U08)(((p >> 11) & 0x1FU) << 3);
		g = (U08)(((p >> 5)  & 0x3FU) << 2);
		b = (U08)((p & 0x1FU) << 3);
		r |= (r >> 5);
		g |= (g >> 6);
		b |= (b >> 5);
	}
	else
	{
		// ARGB8888/RGB888 are stored as 0xAARRGGBB / 0x00RRGGBB by the LTDC layer.
		r = (U08)((pix >> 16) & 0xFFU);
		g = (U08)((pix >> 8)  & 0xFFU);
		b = (U08)(pix & 0xFFU);
	}

	bgr[0] = b;
	bgr[1] = g;
	bgr[2] = r;
}

static void LcdBmp_MakeHeader(U08 *hdr, U32 width, U32 height, U32 rowBytes)
{
	U32 pixelBytes = rowBytes * height;
	U32 fileSize = LCD_BMP_HDR_SIZE + pixelBytes;

	memset(hdr, 0, LCD_BMP_HDR_SIZE);
	hdr[0] = 'B';
	hdr[1] = 'M';
	LcdBmp_PutLe32(&hdr[2], fileSize);
	LcdBmp_PutLe32(&hdr[10], LCD_BMP_HDR_SIZE);
	LcdBmp_PutLe32(&hdr[14], 40U);
	LcdBmp_PutLe32(&hdr[18], width);
	LcdBmp_PutLe32(&hdr[22], height);       // positive height: rows are written bottom-up.
	LcdBmp_PutLe16(&hdr[26], 1U);
	LcdBmp_PutLe16(&hdr[28], 24U);
	LcdBmp_PutLe32(&hdr[34], pixelBytes);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U32 LCD_GetTextColor(void)		{	return lLcd_aIdx[lLcd_iAct].TextColor;		}
U32 LCD_GetBackColor(void)		{	return lLcd_aIdx[lLcd_iAct].BackColor;		}
U08 LCD_GetLayer(void)			{	return lLcd_iAct;							}
sFONT *LCD_GetFont(void)		{	return lLcd_aIdx[lLcd_iAct].pFont;			}
// Set
void LCD_SetTextColor(U32 Color)	{	lLcd_aIdx[lLcd_iAct].TextColor = Color;	}
void LCD_SetBackColor(U32 Color)	{	lLcd_aIdx[lLcd_iAct].BackColor = Color;	}
void LCD_SetFont(sFONT *fonts)		{	lLcd_aIdx[lLcd_iAct].pFont = fonts;		}
void LCD_SetLayer(U08 idx)			{	lLcd_iAct = idx;						}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void LCD_InitMain(void)
{
	LcdInit_Default(LCD_FRM_0, LCD_FB_START_ADDRESS);
	LcdInit_Default(LCD_FRM_1, LCD_FB_START_ADDRESS+0x00200000);
	
	LCD_SetLayer(LCD_FRM_0);
	while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS)); // wait for VSYNC
	LCD_ClearScrn(_cBGD_SCRN);
	LcdSet_ViewReload(LCD_FRM_0, DISABLE);

	LCD_SetLayer(LCD_FRM_1);
	while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS)); // wait for VSYNC
	LCD_ClearScrn(_cBGD_SCRN);
	LcdSet_ViewReload(LCD_FRM_1, DISABLE);

#ifdef _DBG_LOOP_EN_
	LCD_CfgBackLight(TRUE);
#endif
}

void LCD_Copy_Frame(void)
{
	if(lLcd_iAct == 1)
	{
		for(U08 i=0; i<6; i++)
		{
			HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0000000+(0x3E800*i)), (uint32_t) (0xD0200000+(0x3E800*i)), 64000);
			while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
			DaMdb_ProcMain();
		}
		#if 0
		HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0000000), (uint32_t) (0xD0200000), 64000);
		while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
		HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0000000+(0x3E800*1)), (uint32_t) (0xD0200000+(0x3E800*1)), 64000);
		while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
		HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0000000+(0x3E800*2)), (uint32_t) (0xD0200000+(0x3E800*2)), 64000);
		while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
		HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0000000+(0x3E800*3)), (uint32_t) (0xD0200000+(0x3E800*3)), 64000);
		while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
		HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0000000+(0x3E800*4)), (uint32_t) (0xD0200000+(0x3E800*4)), 64000);
		while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
		HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0000000+(0x3E800*5)), (uint32_t) (0xD0200000+(0x3E800*5)), 64000);
		while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
		#endif
	}
	else if(lLcd_iAct == 0)
	{

		for(U08 i=0; i<6; i++)
		{
			HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0200000+(0x3E800*i)), (uint32_t) (0xD0000000+(0x3E800*i)), 64000);
			while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
			DaMdb_ProcMain();
		}	

		#if 0
		HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0200000), (uint32_t) (0xD0000000), 64000);
		while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
		HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0200000+(0x3E800*1)), (uint32_t) (0xD0000000+(0x3E800*1)), 64000);
		while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
		HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0200000+(0x3E800*2)), (uint32_t) (0xD0000000+(0x3E800*2)), 64000);
		while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
		HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0200000+(0x3E800*3)), (uint32_t) (0xD0000000+(0x3E800*3)), 64000);
		while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
		HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0200000+(0x3E800*4)), (uint32_t) (0xD0000000+(0x3E800*4)), 64000);
		while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
		HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t) (0xD0200000+(0x3E800*5)), (uint32_t) (0xD0000000+(0x3E800*5)), 64000);
		while(HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, 1000) != HAL_OK);
		#endif
	}
}

void LCD_Reload(void)
{
	while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS)); // wait for VSYNC
	
	LcdSet_ViewReload(lLcd_iAct^1, DISABLE);
	LcdSet_ViewReload(lLcd_iAct, ENABLE);
	
	lLcd_iAct ^= 1;
	LCD_SetLayer(lLcd_iAct);
}

void LCD_FlipFrame(void)
{
	LCD_Reload();
	LCD_Copy_Frame();
}

void LCD_CfgBackLight(U08 en)
{ 
	if(en)		DMX_SetIo(DMX_OUT_LCD_BL, GPIO_PIN_SET);	/* Assert LCD_BL_CTRL pin */
	else		DMX_SetIo(DMX_OUT_LCD_BL, GPIO_PIN_RESET);	/* De-assert LCD_BL_CTRL pin */
}

U08 LCD_SaveBmpUsb(I08 *filenameBuf, U16 filenameBufSize)
{
	BSP_USB_FILE file;
	I08 fname[BspUsb_FILENAME_MAX];
	U08 hdr[LCD_BMP_HDR_SIZE];
	U32 width = LcdGet_SizeX();
	U32 height = LcdGet_SizeY();
	U32 fmt = hLtdcHandler.LayerCfg[lLcd_iAct].PixelFormat;
	U32 rowBytes;
	U32 x;
	S32 y;
	U08 ret;

	if((width == 0U) || (height == 0U) || (width > LCD_BMP_MAX_WIDTH))
		return BspUsb_FILE_INVALID_PARAM;
	if((fmt != LTDC_PIXEL_FORMAT_RGB565) && (fmt != LTDC_PIXEL_FORMAT_RGB888) && (fmt != LTDC_PIXEL_FORMAT_ARGB8888))
		return BspUsb_FILE_INVALID_PARAM;

	rowBytes = ((width * 3U) + 3U) & ~3U;
	BspUsb_MakeFilename(fname, sizeof(fname), "LCD", ".bmp");
	ret = BspUsb_FileOpenUnique(&file, fname);
	if(ret != BspUsb_FILE_OK)
		return ret;

	if((filenameBuf != (void *)0) && (filenameBufSize != 0U))
	{
		strncpy(filenameBuf, file.name, filenameBufSize - 1U);
		filenameBuf[filenameBufSize - 1U] = 0;
	}

	LcdBmp_MakeHeader(hdr, width, height, rowBytes);
	BspUsb_FileWrite(&file, hdr, sizeof(hdr));

	// BMP stores positive-height images bottom-up. Convert active LTDC layer to 24-bit BGR rows.
	for(y = (S32)height - 1; (y >= 0) && (file.error == BspUsb_FILE_OK); y--)
	{
		memset(s_LcdBmpRow, 0, rowBytes);
		for(x = 0; x < width; x++)
		{
			U08 *dst = &s_LcdBmpRow[x * 3U];
			U32 pix = LcdRead_Pixel((U16)x, (U16)y);
			LcdBmp_PixelToBgr(pix, fmt, dst);
		}
		BspUsb_FileWrite(&file, s_LcdBmpRow, rowBytes);
		if((((U32)y) & 0x0FU) == 0U)
			DaMdb_ProcMain();
	}

	ret = BspUsb_FileClose(&file);
	if((filenameBuf != (void *)0) && (filenameBufSize != 0U))
	{
		strncpy(filenameBuf, file.name, filenameBufSize - 1U);
		filenameBuf[filenameBufSize - 1U] = 0;
	}
	return ret;
}

void LCD_ClearScrn(U32 Color)
{ 
	LcdLl_FillBuffer(lLcd_iAct, (U32 *)(hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress), LcdGet_SizeX(), LcdGet_SizeY(), 0, Color);
}

void LCD_ClearStringLine(U32 Line)
{
	U32 color_backup = lLcd_aIdx[lLcd_iAct].TextColor;
	lLcd_aIdx[lLcd_iAct].TextColor = lLcd_aIdx[lLcd_iAct].BackColor;

	/* Draw rectangle with background color */
	LCD_FillRect(0, (Line * lLcd_aIdx[lLcd_iAct].pFont->info->Height), LcdGet_SizeX(), lLcd_aIdx[lLcd_iAct].pFont->info->Height);

	lLcd_aIdx[lLcd_iAct].TextColor = color_backup;
	LCD_SetTextColor(lLcd_aIdx[lLcd_iAct].TextColor);  
}

void LCD_DisplayEn(void)
{
  __HAL_LTDC_ENABLE(&hLtdcHandler);

  DMX_SetIo(DMX_OUT_LCD_DISP, GPIO_PIN_SET);
}

void LCD_DisplayOn(void)
{
  /* Display On */
  __HAL_LTDC_ENABLE(&hLtdcHandler);
  
  DMX_SetIo(DMX_OUT_LCD_DISP, GPIO_PIN_SET);        /* Assert LCD_DISP pin */

  LCD_CfgBackLight(TRUE);
}


void LCD_DisplayOff(void)
{
  /* Display Off */
  __HAL_LTDC_DISABLE(&hLtdcHandler);

  DMX_SetIo(DMX_OUT_LCD_DISP, GPIO_PIN_RESET);      /* De-assert LCD_DISP pin */
  
  LCD_CfgBackLight(FALSE);
}

void LCD_DisplayChar(U16 Xpos, U16 Ypos, U08 Ascii)
{
	LcdDraw_Char(Xpos, Ypos, &lLcd_aIdx[lLcd_iAct].pFont->table[(Ascii-' ') *\
	lLcd_aIdx[lLcd_iAct].pFont->info->Height * ((lLcd_aIdx[lLcd_iAct].pFont->info->Width + 7) / 8)]);
}





#if 0
void LCD_DisplayStringAt_KOR(U16 Xpos, U16 Ypos, U08 *char_idx,U08 Mode)
{
	U16 ref_column = 1;//, i = 0;
	U32 size = 0, xsize = 0; 
	U08 *ptr = Text;
	uint16_t char_width  = 0;
	uint16_t char_height = 0;
	uint32_t char_tbl_pt = 0;
	uint8_t  char_space = 2;

	/* Get the text size */
	while (*ptr++) size ++ ;

	/* Characters number per line */
	xsize = (LcdGet_SizeX()/lLcd_aIdx[lLcd_iAct].pFont->info->Width);

	switch(Mode)
	{
		case DP_ALIGN_CENTER:
			ref_column = Xpos + ((xsize - size)* lLcd_aIdx[lLcd_iAct].pFont->info->Width) / 2;
			break;

		case DP_ALIGN_LEFT:
			ref_column = Xpos;
			break;
		case DP_ALIGN_RIGHT:
			ref_column = - Xpos + ((xsize - size)*lLcd_aIdx[lLcd_iAct].pFont->info->Width);
			break;
		default:
			ref_column = Xpos;
			break;
	}

	/* Send the string character by character on LCD */
	while((*Text != 0))
	{
		char_idx = (*Text-0x20);

		if(char_idx < 0)
			char_idx = 0;

		char_width  = lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].Width;
		char_height = lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].Height;
		char_tbl_pt = lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].pt;
		
		if(char_width > (LcdGet_SizeX()-ref_column))
			break;
		
		/* Display one character on LCD */
		LcdDraw_Char_2(ref_column, Ypos, char_width, char_height, &lLcd_aIdx[lLcd_iAct].pFont->table[char_tbl_pt]);
		/* Decrement the column position by 16 */
		ref_column += char_width;
		ref_column += char_space;
		/* Point on the next character */
		Text++;

	}
}
#endif



void LCD_DisplayStringAt_KOR(U16 Xpos, U16 Ypos, U08 *Text, U08 Mode)
{
	U16 ref_column = 1;//, i = 0;
	U32 size = 0, xsize = 0; 
	U08 *ptr = Text;
	uint8_t  char_idx = 0;
	uint16_t char_width  = 0;
	uint16_t char_height = 0;
	uint32_t char_tbl_pt = 0;
	uint8_t  char_space = 2;

	/* Get the text size */
	while (*ptr++) size ++ ;

	/* Characters number per line */
	xsize = (LcdGet_SizeX()/lLcd_aIdx[lLcd_iAct].pFont->info->Width);

	switch(Mode)
	{
		case DP_ALIGN_CENTER:
			ref_column = Xpos + ((xsize - size)* lLcd_aIdx[lLcd_iAct].pFont->info->Width) / 2;
			break;

		case DP_ALIGN_LEFT:
			ref_column = Xpos;
			break;
		case DP_ALIGN_RIGHT:
			ref_column = - Xpos + ((xsize - size)*lLcd_aIdx[lLcd_iAct].pFont->info->Width);
			break;
		default:
			ref_column = Xpos;
			break;
	}

	/* Send the string character by character on LCD */
	while((*Text != 0))
	{
		char_idx = (*Text);

		if(char_idx < 0)
			char_idx = 0;

		char_width  = lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].Width;
		char_height = lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].Height;
		char_tbl_pt = lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].pt;
		
		if(char_width > (LcdGet_SizeX()-ref_column))
			break;
		
		/* Display one character on LCD */
		LcdDraw_Char_2(ref_column, Ypos, char_width, char_height, &lLcd_aIdx[lLcd_iAct].pFont->table[char_tbl_pt]);
		/* Decrement the column position by 16 */
		ref_column += char_width;
		ref_column += char_space;
		/* Point on the next character */
			Text++;

	}
#if 0
	I08 sDbg[32];
	U08 a;
	
	_SPRINTF(sDbg, "%d %d %d %d", lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].Height,char_idx,Text ,*Text);
	DpFIG_DrwRect(150, 30, 400, 25, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(150, 30, _cECO_LVL_TITL, _cBGD_SCRN, _fE17HsB, sDbg);
#endif
}


void LCD_DisplayStringAt(U16 Xpos, U16 Ypos, U08 *Text, U08 Mode)
{
	U16 ref_column = 1;//, i = 0;
	U32 size = 0, xsize = 0; 
	U08 *ptr = Text;
	uint8_t  char_idx = 0;
	uint16_t char_width  = 0;
	uint16_t char_height = 0;
	uint32_t char_tbl_pt = 0;
	uint8_t  char_space = 2;

	/* Get the text size */
	while (*ptr++) size ++ ;

	/* Characters number per line */
	xsize = (LcdGet_SizeX()/lLcd_aIdx[lLcd_iAct].pFont->info->Width);

	switch(Mode)
	{
		case DP_ALIGN_CENTER:
			ref_column = Xpos + ((xsize - size)* lLcd_aIdx[lLcd_iAct].pFont->info->Width) / 2;
			break;

		case DP_ALIGN_LEFT:
			ref_column = Xpos;
			break;
		case DP_ALIGN_RIGHT:
			ref_column = - Xpos + ((xsize - size)*lLcd_aIdx[lLcd_iAct].pFont->info->Width);
			break;
		default:
			ref_column = Xpos;
			break;
	}

	/* Send the string character by character on LCD */
	while((*Text != 0))
	{
		if(*Text>=0x20)
			char_idx = (*Text-0x20);
		else
			char_idx = *Text-0x20;
		if(char_idx < 0)
			char_idx = 0;

		char_width  = lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].Width;
		char_height = lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].Height;
		char_tbl_pt = lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].pt;
		
		if(char_width > (LcdGet_SizeX()-ref_column))
			break;
		
		/* Display one character on LCD */
		LcdDraw_Char_2(ref_column, Ypos, char_width, char_height, &lLcd_aIdx[lLcd_iAct].pFont->table[char_tbl_pt]);
		/* Decrement the column position by 16 */
		ref_column += char_width;
		ref_column += char_space;
		/* Point on the next character */
		Text++;

	}
}

void LCD_DisplayStringCursor(U16 Xpos, U16 Ypos, U08 *Text, U08 Mode, U32 col_fw, U32 col_fw_cursor, U08 cursor)
{
	U16 ref_column = 1;//, i = 0;
	U32 size = 0, xsize = 0; 
	U08 i = 0;
	U08 *ptr = Text;
	uint8_t  char_idx = 0;
	uint16_t char_width  = 0;
	uint16_t char_height = 0;
	uint32_t char_tbl_pt = 0;
	uint8_t  char_space = 2;

	/* Get the text size */
	while (*ptr++) size ++ ;

	/* Characters number per line */
	xsize = (LcdGet_SizeX()/lLcd_aIdx[lLcd_iAct].pFont->info->Width);

	switch(Mode)
	{
		case DP_ALIGN_CENTER:
			ref_column = Xpos + ((xsize - size)* lLcd_aIdx[lLcd_iAct].pFont->info->Width) / 2;
			break;

		case DP_ALIGN_LEFT:
			ref_column = Xpos;
			break;

		case DP_ALIGN_RIGHT:
			ref_column = - Xpos + ((xsize - size)*lLcd_aIdx[lLcd_iAct].pFont->info->Width);
			break;

		default:
			ref_column = Xpos;
			break;
	}

	/* Send the string character by character on LCD */
	while((*Text != 0))
	{
		char_idx = (*Text-0x20);

		if(char_idx < 0)
			char_idx = 0;

		char_width  = lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].Width;
		char_height = lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].Height;
		char_tbl_pt = lLcd_aIdx[lLcd_iAct].pFont->info[char_idx].pt;

		DpFIG_DrwRect(ref_column, Ypos+char_height-3, char_width+50, 6,_cPOP_BG_WND,DpFIG_FILL);
		DpFIG_DrwRect(ref_column, Ypos+char_height-3, char_width+50, 6,_cPOP_BG_WND,DpFIG_FILL);

		switch((char_idx-6)/10)
		{
			case 1:		
				if(cursor == i)	
				{
					LCD_SetTextColor(col_fw_cursor);
					DpFIG_DrwLinH(ref_column, Ypos+char_height+2, char_width, col_fw_cursor);
					DpFIG_DrwLinH(ref_column, Ypos+char_height+1, char_width, col_fw_cursor);
					DpFIG_DrwLinH(ref_column, Ypos+char_height, char_width, col_fw_cursor);
					DpFIG_DrwLinH(ref_column, Ypos+char_height-1, char_width, col_fw_cursor);
					DpFIG_DrwLinH(ref_column, Ypos+char_height-2, char_width, col_fw_cursor);
				}
				else			LCD_SetTextColor(col_fw);
				break;
			default:
				i--;
				LCD_SetTextColor(col_fw);
				break;
		}

		if(char_width > (LcdGet_SizeX()-ref_column))
			break;
		
		/* Display one character on LCD */
		LcdDraw_Char_2(ref_column, Ypos, char_width, char_height, &lLcd_aIdx[lLcd_iAct].pFont->table[char_tbl_pt]);

		/* Decrement the column position by 16 */
		ref_column += char_width;
		ref_column += char_space;
		/* Point on the next character */
		Text++;
		i++;
	}
}

void LCD_DisplayStringLeft(U16 Line, U08 *ptr)
{  
  LCD_DisplayStringAt(0, LINE(Line), ptr, DP_ALIGN_LEFT);
}

void LCD_DrawHLine(U16 Xpos, U16 Ypos, U16 Length)
{
  U32  Xaddress = 0;

  Xpos = 799 - Xpos;
  Ypos = 479 - Ypos;

  Xpos -= Length;
  
  /* Get the line address */
  if(hLtdcHandler.LayerCfg[lLcd_iAct].PixelFormat == LTDC_PIXEL_FORMAT_RGB565)
  { /* RGB565 format */
    Xaddress = (hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress) + 2*(LcdGet_SizeX()*Ypos + Xpos);
  }
  else
  { /* ARGB8888 format */
    Xaddress = (hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress) + 4*(LcdGet_SizeX()*Ypos + Xpos);
  }
  
  /* Write line */
  LcdLl_FillBuffer(lLcd_iAct, (U32 *)Xaddress, Length, 1, 0, lLcd_aIdx[lLcd_iAct].TextColor);
}

void LCD_DrawVLine(U16 Xpos, U16 Ypos, U16 Length)
{
  U32  Xaddress = 0;

  Xpos = 799 - Xpos;
  Ypos = 479 - Ypos;

  Ypos -= Length;
  
  
  /* Get the line address */
  if(hLtdcHandler.LayerCfg[lLcd_iAct].PixelFormat == LTDC_PIXEL_FORMAT_RGB565)
  { /* RGB565 format */
    Xaddress = (hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress) + 2*(LcdGet_SizeX()*Ypos + Xpos);
  }
  else
  { /* ARGB8888 format */
    Xaddress = (hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress) + 4*(LcdGet_SizeX()*Ypos + Xpos);
  }
  
  /* Write line */
  LcdLl_FillBuffer(lLcd_iAct, (U32 *)Xaddress, 1, Length, (LcdGet_SizeX() - 1), lLcd_aIdx[lLcd_iAct].TextColor);
}

/**
  * @brief  Draws an uni-line (between two points).
  * @param  x1: Point 1 X position
  * @param  y1: Point 1 Y position
  * @param  x2: Point 2 X position
  * @param  y2: Point 2 Y position
  * @retval None
  */
void LCD_DrawLine(U16 x1, U16 y1, U16 x2, U16 y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, num_add = 0, num_pixels = 0, 
  curpixel = 0;
  
  deltax = _ABS(x2 - x1);        /* The difference between the x's */
  deltay = _ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    num_add = deltay;
    num_pixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    num_add = deltax;
    num_pixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= num_pixels; curpixel++)
  {
    LcdDraw_Pixel(799-x, 479-y, lLcd_aIdx[lLcd_iAct].TextColor);   /* Draw the current pixel */
    num += num_add;                            /* Increase the numerator by the top of the fraction */
    if (num >= den)                           /* Check if numerator >= denominator */
    {
      num -= den;                             /* Calculate the new numerator value */
      x += xinc1;                             /* Change the x as appropriate */
      y += yinc1;                             /* Change the y as appropriate */
    }
    x += xinc2;                               /* Change the x as appropriate */
    y += yinc2;                               /* Change the y as appropriate */
  }
}

/**
  * @brief  Draws a rectangle.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Width: Rectangle width  
  * @param  Height: Rectangle height
  * @retval None
  */
void LCD_DrawRect(U16 Xpos, U16 Ypos, U16 Width, U16 Height)
{
  /* Draw horizontal lines */
  LCD_DrawHLine(Xpos, Ypos, Width);
  LCD_DrawHLine(Xpos, (Ypos+ Height), Width);
  
  /* Draw vertical lines */
  LCD_DrawVLine(Xpos, Ypos, Height);
  LCD_DrawVLine((Xpos + Width), Ypos, Height);
}

/**
  * @brief  Draws a circle.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  Radius: Circle radius
  * @retval None
  */
void LCD_DrawCircle(U16 Xpos, U16 Ypos, U16 Radius)
{
  int32_t   decision;    /* Decision Variable */ 
  U32  current_x;   /* Current X Value */
  U32  current_y;   /* Current Y Value */
  
  Xpos = 799 - Xpos;
  Ypos = 479 - Ypos;
  
  decision = 3 - (Radius << 1);
  current_x = 0;
  current_y = Radius;
  
  while (current_x <= current_y)
  {
    LcdDraw_Pixel((Xpos + current_x), (Ypos - current_y), lLcd_aIdx[lLcd_iAct].TextColor);
    LcdDraw_Pixel((Xpos - current_x), (Ypos - current_y), lLcd_aIdx[lLcd_iAct].TextColor);
    LcdDraw_Pixel((Xpos + current_y), (Ypos - current_x), lLcd_aIdx[lLcd_iAct].TextColor);
    LcdDraw_Pixel((Xpos - current_y), (Ypos - current_x), lLcd_aIdx[lLcd_iAct].TextColor);
    LcdDraw_Pixel((Xpos + current_x), (Ypos + current_y), lLcd_aIdx[lLcd_iAct].TextColor);
    LcdDraw_Pixel((Xpos - current_x), (Ypos + current_y), lLcd_aIdx[lLcd_iAct].TextColor);
    LcdDraw_Pixel((Xpos + current_y), (Ypos + current_x), lLcd_aIdx[lLcd_iAct].TextColor);
    LcdDraw_Pixel((Xpos - current_y), (Ypos + current_x), lLcd_aIdx[lLcd_iAct].TextColor);
    
    if (decision < 0)
    { 
      decision += (current_x << 2) + 6;
    }
    else
    {
      decision += ((current_x - current_y) << 2) + 10;
      current_y--;
    }
    current_x++;
  } 
}

/**
  * @brief  Draws an poly-line (between many points).
  * @param  Points: Pointer to the points array
  * @param  PointCount: Number of points
  * @retval None
  */
void LCD_DrawPolygon(pLCD_PNT Points, U16 PointCount)
{
  int16_t x = 0, y = 0;
  
  if(PointCount < 2)
  {
    return;
  }
  
  LCD_DrawLine(Points->x, Points->y, (Points+PointCount-1)->x, (Points+PointCount-1)->y);
  
  while(--PointCount)
  {
    x = Points->x;
    y = Points->y;
    Points++;
    LCD_DrawLine(x, y, Points->x, Points->y);
  }
}

/**
  * @brief  Draws an ellipse on LCD.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  XRadius: Ellipse X radius
  * @param  YRadius: Ellipse Y radius
  * @retval None
  */
void LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius)
{
  int x = 0, y = -YRadius, err = 2-2*XRadius, e2;
  float k = 0, rad1 = 0, rad2 = 0;
  
  Xpos = 799 - Xpos;
  Ypos = 479 - Ypos;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  k = (float)(rad2/rad1);  
  
  do { 
    LcdDraw_Pixel((Xpos-(U16)(x/k)), (Ypos+y), lLcd_aIdx[lLcd_iAct].TextColor);
    LcdDraw_Pixel((Xpos+(U16)(x/k)), (Ypos+y), lLcd_aIdx[lLcd_iAct].TextColor);
    LcdDraw_Pixel((Xpos+(U16)(x/k)), (Ypos-y), lLcd_aIdx[lLcd_iAct].TextColor);
    LcdDraw_Pixel((Xpos-(U16)(x/k)), (Ypos-y), lLcd_aIdx[lLcd_iAct].TextColor);      
    
    e2 = err;
    if (e2 <= x) {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;     
  }
  while (y <= 0);
}

void LCD_DrawBitmap(U32 Xpos, U32 Ypos, U08 *pbmp)
{
  U32 index = 0, width = 0, height = 0, bit_pixel = 0;
  U32 address;
  U32 input_color_mode = 0;

  Xpos = 799 - Xpos;
  Ypos = 479 - Ypos;

  /* Set the address */
  address = hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress + (((LcdGet_SizeX()*Ypos) + Xpos)*(4));

  width = *(U08 *) (pbmp);
  height = *(U08 *) (pbmp + 1);
  bit_pixel = *(U08 *) (pbmp + 2);
  
  /* Get the layer pixel format */    
  if ((bit_pixel/8) == 4)
  {
    input_color_mode = CM_ARGB8888;
  }
  else if ((bit_pixel/8) == 2)
  {
    input_color_mode = CM_RGB565;   
  }
  else 
  {
    input_color_mode = CM_RGB888;
  }
  
  /* Bypass the bitmap header */
  pbmp += 4+(width * height * 4);
  
  /* Convert picture to ARGB8888 pixel format */
  for(index=0; index < height; index++)
  {
    /* Pixel format conversion */
    LcdLl_CvtLine2ARGB8888((U32 *)pbmp, (U32 *)address, width, input_color_mode);
    
    /* Increment the source and destination buffers */
    address+=  (LcdGet_SizeX()*4);
	
    pbmp -= width*(bit_pixel/8);
  } 
}

void LCD_DrawBitmap_2(U32 x, U32 y, U32 w, U32 h, U08 *pbmp)
{
	U32 index = 0, width = 0, height = 0, bit_pixel = 0;
	U32 address;
	U32 input_color_mode = 0;

	/* Get bitmap data address offset */
	//index = *(__IO uint16_t *) (pbmp + 10);
	//index |= (*(__IO uint16_t *) (pbmp + 12)) << 16;

	width = w;
	height = h;
	bit_pixel = 32;

	/* Set the address */
	address = hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress + (((LcdGet_SizeX()*y) + x)*(4));

	/* Get the layer pixel format */    
	if 		((bit_pixel/8) == 4)	input_color_mode = CM_ARGB8888;
	else if ((bit_pixel/8) == 2)	input_color_mode = CM_RGB565;   
	else 							input_color_mode = CM_RGB888;

	/* Bypass the bitmap header */
	pbmp += (width * (height - 1) * (bit_pixel/8));

	/* Convert picture to ARGB8888 pixel format */
	for(index=0; index < height; index++)
	{
		/* Pixel format conversion */
		LcdLl_CvtLine2ARGB8888((uint32_t *)pbmp, (uint32_t *)address, width, input_color_mode);

		/* Increment the source and destination buffers */
		address += (LcdGet_SizeX()*4);
		pbmp -= width*(bit_pixel/8);
	} 	
}

void LCD_FillRect(U16 Xpos, U16 Ypos, U16 Width, U16 Height)
{
	U32  x_address = 0;
	
	Xpos = 799 - Xpos;
	Ypos = 479 - Ypos;

	Xpos -= Width;
	Ypos -= Height;

	/* Set the text color */
	LCD_SetTextColor(lLcd_aIdx[lLcd_iAct].TextColor);

	/* Get the rectangle start address */
	if(hLtdcHandler.LayerCfg[lLcd_iAct].PixelFormat == LTDC_PIXEL_FORMAT_RGB565)
	{ /* RGB565 format */
		x_address = (hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress) + 2*(LcdGet_SizeX()*Ypos + Xpos);
	}
	else
	{ /* ARGB8888 format */
		x_address = (hLtdcHandler.LayerCfg[lLcd_iAct].FBStartAdress) + 4*(LcdGet_SizeX()*Ypos + Xpos);
	}
	/* Fill the rectangle */
	LcdLl_FillBuffer(lLcd_iAct, (U32 *)x_address, Width, Height, (LcdGet_SizeX() - Width), lLcd_aIdx[lLcd_iAct].TextColor);
}

void LCD_FillCircle(U16 Xpos, U16 Ypos, U16 Radius)
{
	int32_t  decision;     /* Decision Variable */ 
	U32  current_x;   /* Current X Value */
	U32  current_y;   /* Current Y Value */

	decision = 3 - (Radius << 1);

	current_x = 0;
	current_y = Radius;

	LCD_SetTextColor(lLcd_aIdx[lLcd_iAct].TextColor);

	while (current_x <= current_y)
	{
		if(current_y > 0) 
		{
			LCD_DrawHLine(Xpos - current_y, Ypos + current_x, 2*current_y);
			LCD_DrawHLine(Xpos - current_y, Ypos - current_x, 2*current_y);
		}

		if(current_x > 0) 
		{
			LCD_DrawHLine(Xpos - current_x, Ypos - current_y, 2*current_x);
			LCD_DrawHLine(Xpos - current_x, Ypos + current_y, 2*current_x);
		}
		if (decision < 0)
		{ 
			decision += (current_x << 2) + 6;
		}
		else
		{
			decision += ((current_x - current_y) << 2) + 10;
			current_y--;
		}

		current_x++;
	}

	LCD_SetTextColor(lLcd_aIdx[lLcd_iAct].TextColor);
	LCD_DrawCircle(Xpos, Ypos, Radius);
}

void LCD_FillTriangle(U16 x1, U16 x2, U16 x3, U16 y1, U16 y2, U16 y3)
{ 
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, num_add = 0, num_pixels = 0,
  curpixel = 0;
  
  deltax = _ABS(x2 - x1);        /* The difference between the x's */
  deltay = _ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    num_add = deltay;
    num_pixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    num_add = deltax;
    num_pixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= num_pixels; curpixel++)
  {
    LCD_DrawLine(x, y, x3, y3);
    
    num += num_add;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  } 
}

void LCD_FillPolygon(pLCD_PNT Points, U16 PointCount)
{
  int16_t X = 0, Y = 0, X2 = 0, Y2 = 0, X_center = 0, Y_center = 0, X_first = 0, Y_first = 0, pixelX = 0, pixelY = 0, counter = 0;
  U16  image_left = 0, image_right = 0, image_top = 0, image_bottom = 0;
  
  image_left = image_right  = Points->x;
  image_top  = image_bottom = Points->y;
  
  for(counter = 1; counter < PointCount; counter++)
  {
    pixelX = POLY_X(counter);
    if(pixelX < image_left)
    {
      image_left = pixelX;
    }
    if(pixelX > image_right)
    {
      image_right = pixelX;
    }
    
    pixelY = POLY_Y(counter);
    if(pixelY < image_top)
    { 
      image_top = pixelY;
    }
    if(pixelY > image_bottom)
    {
      image_bottom = pixelY;
    }
  }  
  
  if(PointCount < 2)
  {
    return;
  }
  
  X_center = (image_left + image_right)/2;
  Y_center = (image_bottom + image_top)/2;
  
  X_first = Points->x;
  Y_first = Points->y;
  
  while(--PointCount)
  {
    X = Points->x;
    Y = Points->y;
    Points++;
    X2 = Points->x;
    Y2 = Points->y;    
    
    LCD_FillTriangle(X, X2, X_center, Y, Y2, Y_center);
    LCD_FillTriangle(X, X_center, X2, Y, Y_center, Y2);
    LCD_FillTriangle(X_center, X2, X, Y_center, Y2, Y);   
  }
  
  LCD_FillTriangle(X_first, X2, X_center, Y_first, Y2, Y_center);
  LCD_FillTriangle(X_first, X_center, X2, Y_first, Y_center, Y2);
  LCD_FillTriangle(X_center, X2, X_first, Y_center, Y2, Y_first);   
}

/**
  * @brief  Draws a full ellipse.
  * @param  Xpos: X position
  * @param  Ypos: Y position
  * @param  XRadius: Ellipse X radius
  * @param  YRadius: Ellipse Y radius  
  * @retval None
  */
void LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius)
{
  int x = 0, y = -YRadius, err = 2-2*XRadius, e2;
  float k = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  k = (float)(rad2/rad1);
  
  do 
  {       
    LCD_DrawHLine((Xpos-(U16)(x/k)), (Ypos+y), (2*(U16)(x/k) + 1));
    LCD_DrawHLine((Xpos-(U16)(x/k)), (Ypos-y), (2*(U16)(x/k) + 1));
    
    e2 = err;
    if (e2 <= x) 
    {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;
  }
  while (y <= 0);
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

