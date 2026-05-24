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
// display
#include "disp_color.h"
#include "disp_string.h"
#include "disp_figure.h"
#include "disp_titlebar.h"
#include "disp_popup.h"
#include "menu_system.h"
// self
#include "disp_button.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
U32 lDpBtn_cBgd[16];


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - API
//------------------------------------------------------------------------------------------------------------------------------
void BtnDraw_Circle(U08 idx, U08 stt)
{
	U16 x0 = DpBTN_BOX_X0_ + 40;
	U16 y0 = DpBTN_BOX_Y0_ + 25;

	DpFIG_DrwCirc(x0, y0, 10, _cSD_GRAY, _F_T);
}

void BtnDraw_BackGround(U08 idx, U08 atv)
{
	U08 i = 0;
	U08 tk = 4;			// Gradation Thickness
	U16 x0 = DpBTN_BOX_X0_ + (DpBTN_BOX_GAP*idx) + (DpBTN_BOX_WID*idx);
	U16 y0 = DpBTN_BOX_Y0_;
	U16 wd = DpBTN_BOX_WID;

	HAL_Delay(1);

	if(atv != DpBTN_ATV_DISABLE)
	{
		DpFIG_DrwLinH(x0+4, y0-2,        DpBTN_BOX_WID-8, _cSD_BLACK);
		DpFIG_DrwLinH(x0+4, y0-1,        DpBTN_BOX_WID-8, 0xff8B8983);
		DpFIG_DrwRect(x0+2, y0+(tk*i++), DpBTN_BOX_WID-4, tk, _cBTN_BG_G02, DpFIG_FILL);
	}
	for(i=0; i<11; i++)
	{
		switch(atv)
		{
			case DpBTN_ATV_DISABLE:		DpFIG_DrwRect(x0, y0+(tk*i)-2, wd, tk+4, _cBTN_BG_DISA,    DpFIG_FILL);		break;
			case DpBTN_ATV_ENABLE:		DpFIG_DrwRect(x0, y0+(tk*i)-2, wd, tk+4, lDpBtn_cBgd[i+2], DpFIG_FILL);		break;
		}
	}

	if(atv == DpBTN_ATV_DISABLE)
		return;
	DpFIG_DrwRect(x0+2,  y0+(tk*i++), DpBTN_BOX_WID-4, tk, _cBTN_BG_G13, DpFIG_FILL);
	DpFIG_DrwLinH(x0+4,  y0+(tk*i)+1, DpBTN_BOX_WID-8, 0xff191C21);
	DpFIG_DrwLinH(x0+8,  y0+(tk*i)+2, DpBTN_BOX_WID-16, _cSD_BLACK);
	DpFIG_DrwLinH(x0+10, y0+(tk*i)+3, DpBTN_BOX_WID-20, 0xff0e0f0e);
	DpFIG_DrwLinH(x0+10, y0+(tk*i)+4, DpBTN_BOX_WID-20, 0xff121312);
	DpFIG_DrwLinH(x0+10, y0+(tk*i)+5, DpBTN_BOX_WID-20, 0xff131413);
	DpFIG_DrwLinH(x0+10, y0+(tk*i)+6, DpBTN_BOX_WID-20, 0xff141514);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void DpBTN_InitVari(void)
{
	lDpBtn_cBgd[0]  = _cBTN_BG_G00;
	lDpBtn_cBgd[1]  = _cBTN_BG_G01;
	lDpBtn_cBgd[2]  = _cBTN_BG_G02;
	lDpBtn_cBgd[3]  = _cBTN_BG_G03;
	lDpBtn_cBgd[4]  = _cBTN_BG_G04;
	lDpBtn_cBgd[5]  = _cBTN_BG_G05;
	lDpBtn_cBgd[6]  = _cBTN_BG_G06;
	lDpBtn_cBgd[7]  = _cBTN_BG_G07;
	lDpBtn_cBgd[8]  = _cBTN_BG_G08;
	lDpBtn_cBgd[9]  = _cBTN_BG_G09;
	lDpBtn_cBgd[10] = _cBTN_BG_G10;
	lDpBtn_cBgd[11] = _cBTN_BG_G11;
	lDpBtn_cBgd[12] = _cBTN_BG_G12;
	lDpBtn_cBgd[13] = _cBTN_BG_G13;
}

void DpBTN_ClearBtn(U08 idx)
{
	BtnDraw_BackGround(idx, DpBTN_ATV_DISABLE);
}

void DpBTN_UdtEvent(U08 idx, U08 fPsh)
{
	U32 col;
	U16 x0 = DpBTN_BOX_X0_ + (DpBTN_BOX_GAP*idx) + (DpBTN_BOX_WID*idx);
	U16 y0 = DpBTN_BOX_Y0_;

	if(idx >= DpBTN_IDX_NUM)
		return;

	if(fPsh)		col = _cBTN_FG_SELE;
	else			col = _cBGD_SCRN;

	DpFIG_LiveRct(x0-3, y0-5, DpBTN_BOX_WID+6, DpBTN_BOX_HEI+8, col, 3);
}

void DpBTN_UdtStrng(U08 idx, U08 stt, U08 list, I08 offs)
{
	U08 atv;
	U32 cFw, cBw;
	U16 x0 = DpBTN_BOX_X0_ + (DpBTN_BOX_GAP*idx) + (DpBTN_BOX_WID*idx) + offs;
	U16 y0 = DpBTN_BOX_Y0_ + 12;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);
	switch(stt)
	{
		case DpBTN_STT_DISA:	cFw = _cBTN_ST_DISA;	atv = DpBTN_ATV_DISABLE;	cBw = _cBTN_BG_DISA;	break;
		case DpBTN_STT_ACTV:	cFw = _cBTN_ST_ACTV;	atv = DpBTN_ATV_ENABLE;		cBw = _cBTN_BG_G06;		break;
		case DpBTN_STT_IDLE:
		default:				cFw = _cBTN_ST_IDLE;	atv = DpBTN_ATV_ENABLE;		cBw = _cBTN_BG_G06;		break;
	}

	BtnDraw_BackGround(idx, atv);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			if(list==TEXT_LIST_FUNC)
			{
				DpSTR_GuiLeft(x0+10, y0, cFw, cBw, _fE17HsB, _sFUNC);	
				break;
			}
			DpSTR_GuiList(list);
			if(list==TEXT_LIST_EXIT)
				x0 = x0-13;
			if(list==TEXT_LIST_SET)
				x0 = x0-5;
			DpSTR_GuiLeft_KOR(x0+5, y0, cFw, cBw, _fE17HsBKOR, gDpStr.Text_list);	
			break;
		case MnSYS_LANG_ENG:
			switch(list)
			{
				case TEXT_LIST_MENU:		DpSTR_GuiLeft(x0, y0, cFw, cBw, _fE17HsB, _sMENU);	break;
				case TEXT_LIST_BACK:		DpSTR_GuiLeft(x0, y0, cFw, cBw, _fE17HsB, _sBACK);	break;
				case TEXT_LIST_EXIT:		DpSTR_GuiLeft(x0, y0, cFw, cBw, _fE17HsB, _sEXIT);	break;
				case TEXT_LIST_SAVE:		DpSTR_GuiLeft(x0, y0, cFw, cBw, _fE17HsB, _sSAVE);	break;
				case TEXT_LIST_SET:			DpSTR_GuiLeft(x0, y0, cFw, cBw, _fE17HsB, _sSET);	break;
				case TEXT_LIST_FUNC:		DpSTR_GuiLeft(x0, y0, cFw, cBw, _fE17HsB, _sFUNC);	break;
			}
			break;
	}
}

void DpBTN_UdtArrow(U08 idx, U08 opt)
{
	U16 x0 = DpBTN_BOX_X0_ + (DpBTN_BOX_GAP*idx) + (DpBTN_BOX_WID*idx) + 25;
	U16 y0 = DpBTN_BOX_Y0_ + 20;
	U16 x1 = x0 + 20;
	U16 y1 = DpBTN_BOX_Y0_ + 8;

	BtnDraw_BackGround(idx, DpBTN_ATV_ENABLE);

	switch(idx)
	{
		case DpBTN_I1_PREV:
			switch(opt)
			{
				case DpBTN_PREV_LEFT:
					DpFIG_DrwRect(x0,    y0,   40, 7, _cBTN_FG_PEND, DpFIG_FILL);
					DpFIG_DrwCirc(x0,    y0+4, 3,     _cBTN_FG_PEND, _F_T);
					DpFIG_DrwCirc(x0+40, y0+4, 3,     _cBTN_FG_PEND, _F_T);
					DpFIG_DrwTria(x0, y0,   x0+10, y0,   x0+10, y0-7,  _cBTN_FG_PEND);
					DpFIG_DrwTria(x0, y0+7, x0+10, y0+7, x0+10, y0+15, _cBTN_FG_PEND);
					break;
			
				case DpBTN_PREV_UP__:
					DpFIG_DrwRect(x1,   y0-12, 7, 30, _cBTN_FG_PEND, DpFIG_FILL);
					DpFIG_DrwCirc(x1+4, y0-12,    3,  _cBTN_FG_PEND, _F_T);
					DpFIG_DrwCirc(x1+4, y0+30-12, 3,  _cBTN_FG_PEND, _F_T);
					DpFIG_DrwTria(x1,   y1, x1,   y1+10, x1-7,  y1+10, _cBTN_FG_PEND);
					DpFIG_DrwTria(x1+7, y1, x1+7, y1+10, x1+15, y1+10, _cBTN_FG_PEND);
					break;

				case DpBTN_PREV_DOWN:
					DpFIG_DrwRect(x1,   y0-12, 7, 30, _cBTN_FG_PEND, DpFIG_FILL);
					DpFIG_DrwCirc(x1+4, y0-12,    3,  _cBTN_FG_PEND, _F_T);
					DpFIG_DrwCirc(x1+4, y0+30-12, 3,  _cBTN_FG_PEND, _F_T);
					DpFIG_DrwTria(x1,   y1+30, x1,   y1+20, x1-7,  y1+20, _cBTN_FG_PEND);
					DpFIG_DrwTria(x1+7, y1+30, x1+7, y1+20, x1+15, y1+20, _cBTN_FG_PEND);
					break;
			}
			break;

		case DpBTN_I2_NEXT:
			switch(opt)
			{
				case DpBTN_NEXT_RIGH:
					DpFIG_DrwRect(x0,    y0,   40, 7, _cBTN_FG_PEND, DpFIG_FILL);
					DpFIG_DrwCirc(x0,    y0+4, 3,     _cBTN_FG_PEND, _F_T);
					DpFIG_DrwCirc(x0+40, y0+4, 3,     _cBTN_FG_PEND, _F_T);
					DpFIG_DrwTria(x0+40, y0,   x0+40-10, y0,   x0+40-10, y0-8,   _cBTN_FG_PEND);
					DpFIG_DrwTria(x0+40, y0+7, x0+40-10, y0+7, x0+40-10, y0+8+7, _cBTN_FG_PEND);
					break;
			
				case DpBTN_NEXT_UP__:
					DpFIG_DrwRect(x1,   y0-12, 7, 30, _cBTN_FG_PEND, DpFIG_FILL);
					DpFIG_DrwCirc(x1+4, y0-12,    3,  _cBTN_FG_PEND, _F_T);
					DpFIG_DrwCirc(x1+4, y0+30-12, 3,  _cBTN_FG_PEND, _F_T);
					DpFIG_DrwTria(x1,   y1, x1,   y1+10, x1-7,  y1+10, _cBTN_FG_PEND);
					DpFIG_DrwTria(x1+7, y1, x1+7, y1+10, x1+15, y1+10, _cBTN_FG_PEND);
					break;

				case DpBTN_NEXT_DOWN:
					DpFIG_DrwRect(x1,   y0-12, 7, 30, _cBTN_FG_PEND, DpFIG_FILL);
					DpFIG_DrwCirc(x1+4, y0-12,    3,  _cBTN_FG_PEND, _F_T);
					DpFIG_DrwCirc(x1+4, y0+30-12, 3,  _cBTN_FG_PEND, _F_T);
					DpFIG_DrwTria(x1,   y1+30, x1,   y1+20, x1-7,  y1+20, _cBTN_FG_PEND);
					DpFIG_DrwTria(x1+7, y1+30, x1+7, y1+20, x1+15, y1+20, _cBTN_FG_PEND);
					break;
			}
			break;

		case DpBTN_I3_ENTR:
			switch(opt)
			{
				case DpBTN_NEXT_RIGH:
					DpFIG_DrwRect(x0,    y0,   40, 7, _cBTN_FG_PEND, DpFIG_FILL);
					DpFIG_DrwCirc(x0,    y0+4, 3,     _cBTN_FG_PEND, _F_T);
					DpFIG_DrwCirc(x0+40, y0+4, 3,     _cBTN_FG_PEND, _F_T);
					DpFIG_DrwTria(x0+40, y0,   x0+40-10, y0,   x0+40-10, y0-7,  _cBTN_FG_PEND);
					DpFIG_DrwTria(x0+40, y0+7, x0+40-10, y0+7, x0+40-10, y0+15, _cBTN_FG_PEND);
					break;
			}
			break;
	}
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

