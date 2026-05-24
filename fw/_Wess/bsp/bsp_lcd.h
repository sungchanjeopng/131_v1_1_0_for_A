//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___BSP_LCD_H___
#define ___BSP_LCD_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "fonts.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
enum {
	LCD_FRM_0 = 0,
	LCD_FRM_1,

	LCD_FRM_MAX,
};

enum {
	DP_ALIGN_CENTER = 0x01,		/* Center mode */
	DP_ALIGN_RIGHT,				/* Right mode  */
	DP_ALIGN_LEFT				/* Left mode   */
};

#define MAX_LAYER_NUMBER		((U32)2)
#define LTDC_ACTIVE_LAYER		((U32)1) /* Layer 1 */

#define LCD_OK					((U08)0x00)
#define LCD_ERROR				((U08)0x01)
#define LCD_TIMEOUT				((U08)0x02)

#define LCD_FB_START_ADDRESS	((U32)0xD0000000)


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	U32 TextColor; 
	U32 BackColor;  

	sFONT *pFont;

} LCD_LS;

typedef struct {
	I16 x;
	I16 y;

} LCD_PNT, *pLCD_PNT;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------
#define POLY_X(Z)           ((int32_t)((Points + Z)->x))
#define POLY_Y(Z)           ((int32_t)((Points + Z)->y))      

#define hLtdcHandler 			hltdc
#define hDma2dHandler 			hdma2d
#define LCD_LayerCfgTypeDef		LTDC_LayerCfgTypeDef
#define LCD_DEFAULT_FONT        Ft24_Courier     
#define LCD_RELOAD_IMMEDIATE			((U32)LTDC_SRCR_IMR)
#define LCD_RELOAD_VERTICAL_BLANKING	((U32)LTDC_SRCR_VBR) 


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------
extern const U08 _gimg_menu_fact_rel[];
extern const U08 _gimg_menu_fact_sel[];
extern const U08 _gimg_menu_opti_rel[];
extern const U08 _gimg_menu_opti_sel[];


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get Local Variables
extern U32 LcdGet_SizeX(void);
extern U32 LcdGet_SizeY(void);
extern U32 LcdRead_Pixel(U16 Xpos, U16 Ypos);
extern U32 LCD_GetTextColor(void);
extern U32 LCD_GetBackColor(void);
extern U08 LCD_GetLayer(void);
extern sFONT *LCD_GetFont(void);
// Set Local Variables
extern void LCD_SetTextColor(U32 Color);
extern void LCD_SetBackColor(U32 Color);
extern void LCD_SetFont(sFONT *fonts);
extern void LCD_SetLayer(U08 idx);
// Operation
extern void LCD_InitMain(void);
extern void LCD_Copy_Frame(void);
extern void LCD_Reload(void);
extern void LCD_FlipFrame(void);
extern void LCD_CfgBackLight(U08 en);
extern U08 LCD_SaveBmpUsb(I08 *filenameBuf, U16 filenameBufSize);
// Clear
extern void LCD_ClearScrn(U32 Color);
extern void LCD_ClearStringLine(U32 Line);
// Display
extern void LCD_DisplayEn(void);
extern void LCD_DisplayChar(U16 Xpos, U16 Ypos, U08 Ascii);
extern void LCD_DisplayStringLeft(U16 Line, U08 *ptr);
extern void LCD_DisplayStringAt(U16 Xpos, U16 Ypos, U08 *Text, U08 Mode);
extern void LCD_DisplayStringAt_KOR(U16 Xpos, U16 Ypos, U08 *Text, U08 Mode);
extern void LCD_DisplayStringCursor(U16 Xpos, U16 Ypos, U08 *Text, U08 Mode, U32 col_fw, U32 col_fw_cursor, U08 cursor);
extern void LCD_DisplayOff(void);
extern void LCD_DisplayOn(void);
// Draw
extern void LCD_DrawHLine(U16 Xpos, U16 Ypos, U16 Length);
extern void LCD_DrawVLine(U16 Xpos, U16 Ypos, U16 Length);
extern void LCD_DrawLine(U16 x1, U16 y1, U16 x2, U16 y2);
extern void LCD_DrawRect(U16 Xpos, U16 Ypos, U16 Width, U16 Height);
extern void LCD_DrawCircle(U16 Xpos, U16 Ypos, U16 Radius);
extern void LCD_DrawPolygon(pLCD_PNT Points, U16 PointCount);
extern void LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius);
extern void LCD_DrawBitmap(U32 Xpos, U32 Ypos, U08 *pbmp);
extern void LCD_DrawBitmap_2(U32 x, U32 y, U32 w, U32 h, U08 *pbmp);
// Fill
extern void LCD_FillRect(U16 Xpos, U16 Ypos, U16 Width, U16 Height);
extern void LCD_FillCircle(U16 Xpos, U16 Ypos, U16 Radius);
extern void LCD_FillTriangle(U16 x1, U16 x2, U16 x3, U16 y1, U16 y2, U16 y3);
extern void LCD_FillPolygon(pLCD_PNT Points, U16 PointCount);
extern void LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius);


#endif // ___BSP_LCD_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

