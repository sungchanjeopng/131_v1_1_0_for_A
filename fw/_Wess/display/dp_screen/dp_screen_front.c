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
#include "app_status.h"
#include "app_sys.h"
// measure
#include "measure_calc.h"
#include "measure_temperature.h"
#include "measure_cal1_field0.h"
// display
#include "disp_main.h"
#include "disp_color.h"
#include "disp_string.h"
#include "disp_figure.h"
#include "disp_titlebar.h"
#include "disp_button.h"
#include "disp_popup.h"
// menu
#include "menu_factory.h"
#include "menu_measure.h"
#include "menu_output.h"
#include "menu_system.h"
#include "menu_engineer.h"
// screen
#include "screen_main.h"
#include "screen_hybrid.h"
#include "screen_frt1_list.h"
#include "screen_frt2_value.h"
// disp - screen
#include "dp_screen_main.h"
// self
#include "dp_screen_front.h"
// function
#include "output_current.h"

#include "data_save.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
DpFRT_LS lDpFrt;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Line
//------------------------------------------------------------------------------------------------------------------------------
void DpFrtLin_Hori0(void)
{
	#if 1
	DpFIG_DrwRect(15, 235+(2*0), 410, 2, _chyb_LN_H00, 0);
	DpFIG_DrwRect(15, 235+(2*1), 410, 2, _chyb_LN_H01, 0);
	DpFIG_DrwRect(15, 235+(2*2), 410, 2, _chyb_LN_H02, 0);
	#else
	DpFIG_DrwRect(15, 235+(2*0), 490, 2, _chyb_LN_H00, 0);
	DpFIG_DrwRect(15, 235+(2*1), 490, 2, _chyb_LN_H01, 0);
	DpFIG_DrwRect(15, 235+(2*2), 490, 2, _chyb_LN_H02, 0);
	#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Level
//------------------------------------------------------------------------------------------------------------------------------
void DpFrtLvl_FgrlIcon(void)
{
	DpFIG_DrwCirc(35, 108, 5,     _chyb_LVL_ICON, _F_T);
	DpFIG_DrwCirc(40, 88,  6,     _chyb_LVL_ICON, _F_T);
	DpFIG_DrwElli(55, 105, 10, 8, _chyb_LVL_ICON, _F_T);
}

void DpFrtLvl_StrTitle(U08 type)
{
	I08 pSt0[64] = {0, };
	U08 i;
	U32 font;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_LANG_KOR);


	if(type == MnFTR_SS_DUAL)
	{
		for(i=0; i<APP_CH_NUM; i++)
		{
			switch(MnOUT_CurPrGet_CH_Value(i, MnOS0_OPT_SINGLE_ASSIGN))
			{
				case MnOS0_ASSIGN_LIGHT:	font = _cLight_level;	break;
				case MnOS0_ASSIGN_HEAVY:	font = _cHeavy_level;	break;
				default:
					break;
			}


			switch(lang)
			{
				case MnSYS_LANG_ENG:
					if(i==0)
						DpSTR_GuiLeft(70, 13, _cTTB_ST_PRDT, _cTTB_BG_MID, _fE22HsBKOR, pSt0);

					_SPRINTF(pSt0, _sLight_level);
					DpFIG_DrwRect(DpFRT_LVL_VALU_X0+(i*380), DpFRT_LVL_VALU_Y0, 100, 30, _cBGD_SCRN, DpFIG_FILL);
					DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+(i*380), DpFRT_LVL_VALU_Y0, _cLight_level, _cBGD_SCRN, _fE17HsB, pSt0);
					
					_SPRINTF(pSt0, _sHeavy_level);
					
					DpFIG_DrwRect(DpFRT_LVL_VALU_X0+(i*380)+175, DpFRT_LVL_VALU_Y0, 100, 30, _cBGD_SCRN, DpFIG_FILL);
					DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+(i*380)+175, DpFRT_LVL_VALU_Y0, _cHeavy_level, _cBGD_SCRN, _fE17HsB, pSt0);

					_SPRINTF(pSt0, _sCurrent_Title);
					
					DpFIG_DrwRect(DpFRT_SUB_VALU_X0+(i*380)+175, DpFRT_SUB_VALU_Y0, 150, 30, _cBGD_SCRN, DpFIG_FILL);
					DpSTR_GuiLeft(DpFRT_SUB_VALU_X0+(i*380)+175, DpFRT_SUB_VALU_Y0, font, _cBGD_SCRN, _fE17HsB, pSt0);				
					break;
				case MnSYS_LANG_KOR:
					if(i==0)
					{
						DpSTR_GuiList(TEXT_LIST_SLUDGE_LEVEL_METER);
						DpSTR_GuiLeft_KOR(70, 13, _cTTB_ST_PRDT, _cTTB_BG_MID, _fE22HsBKOR, gDpStr.Text_list);
					}

					DpSTR_GuiList(TEXT_LIST_LIGHT_LEVEL);
					
					DpFIG_DrwRect(DpFRT_LVL_VALU_X0+(i*380), DpFRT_LVL_VALU_Y0, 100, 30, _cBGD_SCRN, DpFIG_FILL);
					DpSTR_GuiLeft_KOR(DpFRT_LVL_VALU_X0+(i*380), DpFRT_LVL_VALU_Y0, _cLight_level, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);
					_SPRINTF(pSt0, "(m)");
					DpSTR_GuiLeft(DpFRT_SUB_VALU_X0+(i*380)+145, DpFRT_LVL_VALU_Y0, _cLight_level, _cBGD_SCRN, _fE17HsB, pSt0);	
					
					DpSTR_GuiList(TEXT_LIST_HEAVY_LEVEL);
					DpFIG_DrwRect(DpFRT_LVL_VALU_X0+(i*380)+180, DpFRT_LVL_VALU_Y0, 100, 30, _cBGD_SCRN, DpFIG_FILL);
					DpSTR_GuiLeft_KOR(DpFRT_LVL_VALU_X0+(i*380)+180, DpFRT_LVL_VALU_Y0, _cHeavy_level, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);
					_SPRINTF(pSt0, "(m)");
					DpSTR_GuiLeft(DpFRT_SUB_VALU_X0+(i*380)+180+145, DpFRT_LVL_VALU_Y0, _cHeavy_level, _cBGD_SCRN, _fE17HsB, pSt0);	

					DpSTR_GuiList(TEXT_LIST_CURRENT);
					DpFIG_DrwRect(DpFRT_SUB_VALU_X0+(i*380)+180, DpFRT_SUB_VALU_Y0, 150, 30, _cBGD_SCRN, DpFIG_FILL);
					DpSTR_GuiLeft_KOR(DpFRT_LVL_VALU_X0+(i*380)+180, DpFRT_SUB_VALU_Y0, font, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);		
					_SPRINTF(pSt0, "(mA)");
					DpSTR_GuiLeft(DpFRT_SUB_VALU_X0+(i*380)+180+115, DpFRT_SUB_VALU_Y0, font, _cBGD_SCRN, _fE17HsB, pSt0);	

					break;
				default:
					break;
			}

		}
	}
	else if (type == MnFTR_SS_SINGLE)
	{
		switch(MnOUT_CurPrGet_CH_Value(APP_CH_1, MnOS0_OPT_SINGLE_ASSIGN))
		{
			case MnOS0_ASSIGN_LIGHT:	font = _cLight_level;	break;
			case MnOS0_ASSIGN_HEAVY:	font = _cHeavy_level;	break;
			default:
				break;
		}	
		
		if(lang == MnSYS_LANG_ENG)
		{
			DpSTR_GuiLeft(70, 13, _cTTB_ST_PRDT, _cTTB_BG_MID, _fE22HsBKOR, pSt0);
			
			_SPRINTF(pSt0, _sLight_level);
			DpFIG_DrwRect(DpFRT_LVL_VALU_X0, DpFRT_LVL_VALU_SINGLE_Y0, 100, 30, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(DpFRT_LVL_VALU_X0, DpFRT_LVL_VALU_SINGLE_Y0, _cLight_level, _cBGD_SCRN,  _fE17HsB, pSt0);
			
			_SPRINTF(pSt0, _sHeavy_level);
			
			DpFIG_DrwRect(DpFRT_LVL_VALU_X0, DpFRT_LVL_VALU_SINGLE_Y1, 100, 30, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(DpFRT_LVL_VALU_X0, DpFRT_LVL_VALU_SINGLE_Y1, _cHeavy_level, _cBGD_SCRN, _fE17HsB, pSt0);
			
			_SPRINTF(pSt0, _sCurrent_Title);
			
			DpFIG_DrwRect(600, DpFRT_LVL_VALU_SINGLE_Y1-20, 150, 30, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(600, DpFRT_LVL_VALU_SINGLE_Y1-20, font, _cBGD_SCRN, _fE17HsB, pSt0);	
		}
		else if (lang == MnSYS_LANG_KOR)
		{
			DpSTR_GuiList(TEXT_LIST_SLUDGE_LEVEL_METER);
			DpSTR_GuiLeft_KOR(70, 13, _cTTB_ST_PRDT, _cTTB_BG_MID, _fE22HsBKOR, gDpStr.Text_list);		

			DpSTR_GuiList(TEXT_LIST_LIGHT_LEVEL);
			DpFIG_DrwRect(DpFRT_LVL_VALU_X0, DpFRT_LVL_VALU_SINGLE_Y0, 100, 30, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft_KOR(DpFRT_LVL_VALU_X0, DpFRT_LVL_VALU_SINGLE_Y0, _cLight_level, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);
			_SPRINTF(pSt0, "(m)");
			DpSTR_GuiLeft(DpFRT_SUB_VALU_X0+150, DpFRT_LVL_VALU_SINGLE_Y0, _cLight_level, _cBGD_SCRN, _fE17HsB, pSt0);		

			DpSTR_GuiList(TEXT_LIST_HEAVY_LEVEL);
			DpFIG_DrwRect(DpFRT_LVL_VALU_X0, DpFRT_LVL_VALU_SINGLE_Y1, 100, 30, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft_KOR(DpFRT_LVL_VALU_X0, DpFRT_LVL_VALU_SINGLE_Y1, _cHeavy_level, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);
			_SPRINTF(pSt0, "(m)");
			DpSTR_GuiLeft(DpFRT_SUB_VALU_X0+150, DpFRT_LVL_VALU_SINGLE_Y1, _cHeavy_level, _cBGD_SCRN, _fE17HsB, pSt0);				

			DpSTR_GuiList(TEXT_LIST_CURRENT);
			DpFIG_DrwRect(600, DpFRT_LVL_VALU_SINGLE_Y1-20, 150, 30, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft_KOR(600, DpFRT_LVL_VALU_SINGLE_Y1-20, font, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);		
			_SPRINTF(pSt0, "(mA)");
			DpSTR_GuiLeft(730, DpFRT_LVL_VALU_SINGLE_Y1-20, font, _cBGD_SCRN, _fE17HsB, pSt0);				
		}
	}
}


void DpFrt_lvl_StrValue_current(U08 i)
{
	U32 font;
	U16 current[APP_CH_NUM];
	I08 pSt0[64] = {0, };
	U08 type = MnFTR_PrGet_SsChn();

	current[i] = OuCUR_GetOutp_Value(i);
	
	if(type == MnFTR_SS_DUAL)
	{
		switch(MnOUT_CurPrGet_CH_Value(i, MnOS0_OPT_SINGLE_ASSIGN))
		{
			case MnOS0_ASSIGN_LIGHT:	font = _cLight_level;	break;
			case MnOS0_ASSIGN_HEAVY:	font = _cHeavy_level;	break;
			default:
				break;
		}
		
		if(current[i] >= 1000)	_SPRINTF(pSt0, "%2d.%02d", current[i]/100, current[i]%100);
		else					_SPRINTF(pSt0, "%1d.%02d", current[i]/100, current[i]%100); 	
		
		DpFIG_DrwRect(DpFRT_SUB_VALU_X0+(i*380)+175+20, DpFRT_SUB_VALU_Y0+40, 180, 50, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(DpFRT_SUB_VALU_X0+(i*380)+175+20, DpFRT_SUB_VALU_Y0+40, font, _cBGD_SCRN, _fE35HsB, pSt0);	
	}
	else if(type == MnFTR_SS_SINGLE)
	{
		switch(MnOUT_CurPrGet_CH_Value(i, MnOS0_OPT_SINGLE_ASSIGN))
		{
			case MnOS0_ASSIGN_LIGHT:	font = _cLight_level;	break;
			case MnOS0_ASSIGN_HEAVY:	font = _cHeavy_level;	break;
			default:
				break;
		}
		
		if(current[i] >= 1000)	_SPRINTF(pSt0, "%2d.%02d", current[i]/100, current[i]%100);
		else					_SPRINTF(pSt0, "%1d.%02d", current[i]/100, current[i]%100); 	
		
		DpFIG_DrwRect(600, DpFRT_LVL_VALU_SINGLE_Y1+10, 160, 60, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(600, DpFRT_LVL_VALU_SINGLE_Y1+10, font, _cBGD_SCRN, _fE35HsB, pSt0);	
	}
}

void DpFrt_lvl_StrValue_msr(void)
{
	U08 lang =MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);
	//U08 pos = MsCAL1_Getrst_pos();
	U08 dir = MsCAL1_Getrst_dir();
	//U16 vel = MsCAL1_Getrst_vel();
	I08 pSt0[64] = {0, };
	U64 color;



	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR))
	{			
		color = _cSD_WHITE;
		switch(lang)
		{
			case MnSYS_LANG_ENG:
				_SPRINTF(pSt0, "Sludge Collector  ");
				
				DpFIG_DrwRect(DpFRT_LVL_VALU_X0+10, DpFRT_SUB_VALU_Y1, 700, 20, _cBGD_SCRN, DpFIG_FILL);
				DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+10, DpFRT_SUB_VALU_Y1, _cSD_WHITE, _cBGD_SCRN, _fE12HsM, pSt0); 

#if 0
				switch(pos)
				{
					case CAL1_FIN_POS_NONE:		_SPRINTF(pSt0, "Position (	-  )"); 			break;
					default:					_SPRINTF(pSt0, "Position ( %d )", pos);			break;
				}
	
				DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+180, DpFRT_SUB_VALU_Y1, color, _cBGD_SCRN, _fE12HsM, pSt0);
#endif				
				switch(dir)
				{
					case CAL1_DIRE_NONE:		_SPRINTF(pSt0, "Direction :   -	");				break;
					case CAL1_DIRE_CH_2TO1: 	_SPRINTF(pSt0, "Direction : CH 2 -> CH 1"); 		break;
					case CAL1_DIRE_CH_1TO2: 	_SPRINTF(pSt0, "Direction : CH 1 -> CH 2"); 		break;
					default:																			break;
				}	
	
				DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+170, DpFRT_SUB_VALU_Y1, color, _cBGD_SCRN, _fE12HsM, pSt0);	
#if 0	
				if(!MsCAL1_GetfDp_cyc()) 	_SPRINTF(pSt0, "Velocity (	-  )");
				else
				{
					_SPRINTF(pSt0, "Velocity (%2d.%02d m/min)", vel/100, vel%100); 
				}
				
				DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+540, DpFRT_SUB_VALU_Y1, color, _cBGD_SCRN, _fE12HsM, pSt0);		
#endif
				break;
			case MnSYS_LANG_KOR:
				DpSTR_GuiList(TEXT_LIST_SLUDGE_COLLECTOR);
				
				DpFIG_DrwRect(DpFRT_LVL_VALU_X0+10, DpFRT_SUB_VALU_Y1, 700, 20, _cBGD_SCRN, DpFIG_FILL);
				DpSTR_GuiLeft_KOR(DpFRT_LVL_VALU_X0+10, DpFRT_SUB_VALU_Y1, _cSD_WHITE, _cBGD_SCRN, _fE12HsMKOR, gDpStr.Text_list);	
#if 0
				DpSTR_GuiList(TEXT_LIST_POSITION);
				DpSTR_GuiLeft_KOR(DpFRT_LVL_VALU_X0+180, DpFRT_SUB_VALU_Y1, _cSD_WHITE, _cBGD_SCRN, _fE12HsMKOR, gDpStr.Text_list);

				switch(pos)
				{
					case CAL1_FIN_POS_NONE:		_SPRINTF(pSt0, "(	-  )"); 			break;
					default:					_SPRINTF(pSt0, "( %d )", pos);			break;
				}

				DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+220, DpFRT_SUB_VALU_Y1, color, _cBGD_SCRN, _fE12HsM, pSt0);				
#endif
				
				DpSTR_GuiList(TEXT_LIST_DIRECTION);
				DpSTR_GuiLeft_KOR(DpFRT_LVL_VALU_X0+120, DpFRT_SUB_VALU_Y1, _cSD_WHITE, _cBGD_SCRN, _fE12HsMKOR, gDpStr.Text_list);

				switch(dir)
				{
					case CAL1_DIRE_CH_2TO1:		_SPRINTF(pSt0, ":      -	  ");			break;
					case CAL1_DIRE_NONE: 		_SPRINTF(pSt0, ":    CH 2 -> CH 1"); 		break;
					case CAL1_DIRE_CH_1TO2: 	_SPRINTF(pSt0, ":    CH 1 -> CH 2"); 		break;
					default:															break;
				}		
	
				DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+180, DpFRT_SUB_VALU_Y1, color, _cBGD_SCRN, _fE12HsM, pSt0);	

#if 0
				DpSTR_GuiList(TEXT_LIST_VELOCITY);
				DpSTR_GuiLeft_KOR(DpFRT_LVL_VALU_X0+540, DpFRT_SUB_VALU_Y1, _cSD_WHITE, _cBGD_SCRN, _fE12HsMKOR, gDpStr.Text_list);

				if(!MsCAL1_GetfDp_cyc()) 	_SPRINTF(pSt0, "(	-  )");
				else
				{
					_SPRINTF(pSt0, "(%2d.%02d m/min)", vel/100, vel%100); 
				}
				DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+600, DpFRT_SUB_VALU_Y1, color, _cBGD_SCRN, _fE12HsM, pSt0);		
#endif
				break;					
			default:
				break;
		}
	}
}

void DpFrtLvl_StrValue(void)
{
	U16 valu[APP_CH_NUM][MsCAL_THR_TYPE_NUM];
	I08 pSt0[64] = {0, };
	U08 i,j;
	U08 type = MnFTR_PrGet_SsChn();


	if(type == MnFTR_SS_DUAL)
	{
		for(i=0; i<APP_CH_NUM; i++)
		{

			for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
			{
				switch(MnMSR_BaseGet_Ch_Value(i, MnMS0_OPT_SINGLE_OPERATION))
				{		
					case MnMS0_OPERATION_DISTANCE:
						valu[i][j] = MsCAL_GetVl_RsltDist(i, j);
						break;
					case MnMS0_OPERATION_SLUDGE:
						valu[i][j] = MsCAL_GetVl_RsltSldg(i, j);
						break;
					default:	
						break;
				}

				if((MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON))
				{
					valu[i][j] = MsCAL1_Hunting_value(i, j);
				}

			}
			if(valu[i][MsCAL_THR_LIGHT] >= 1000)	_SPRINTF(pSt0, "%2d.%02d", valu[i][MsCAL_THR_LIGHT]/100, valu[i][MsCAL_THR_LIGHT]%100);
			else									_SPRINTF(pSt0, "%1d.%02d", valu[i][MsCAL_THR_LIGHT]/100, valu[i][MsCAL_THR_LIGHT]%100);
			
			DpFIG_DrwRect(DpFRT_LVL_VALU_X0+i*380+20, DpFRT_LVL_VALU_Y0+40, 150, 50, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+i*380+20, DpFRT_LVL_VALU_Y0+40, _cLight_level, _cBGD_SCRN, _fE35HsB, pSt0);
			
			
			if(valu[i][MsCAL_THR_HEAVY] >= 1000)	_SPRINTF(pSt0, "%2d.%02d", valu[i][MsCAL_THR_HEAVY]/100, valu[i][MsCAL_THR_HEAVY]%100);
			else									_SPRINTF(pSt0, "%1d.%02d", valu[i][MsCAL_THR_HEAVY]/100, valu[i][MsCAL_THR_HEAVY]%100);
			
			DpFIG_DrwRect(DpFRT_LVL_VALU_X0+(i*380)+175+20, DpFRT_LVL_VALU_Y0+40, 150, 50, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+(i*380)+175+20, DpFRT_LVL_VALU_Y0+40, _cHeavy_level, _cBGD_SCRN, _fE35HsB, pSt0);

			DpFrt_lvl_StrValue_msr();
			DpFrt_lvl_StrValue_current(i);
		}
	}
	else if(type == MnFTR_SS_SINGLE)
	{

		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
		{
	
			switch(MnMSR_BaseGet_Ch_Value(APP_CH_1, MnMS0_OPT_SINGLE_OPERATION))
			{		
				case MnMS0_OPERATION_DISTANCE:
					valu[APP_CH_1][j] = MsCAL_GetVl_RsltDist(APP_CH_1, j);
					break;
				case MnMS0_OPERATION_SLUDGE:
					valu[APP_CH_1][j] = MsCAL_GetVl_RsltSldg(APP_CH_1, j);
					break;
				default:	
					break;
			}
		}

		
		if(valu[APP_CH_1][MsCAL_THR_LIGHT] >= 1000)	_SPRINTF(pSt0, "%2d.%02d", valu[APP_CH_1][MsCAL_THR_LIGHT]/100, valu[APP_CH_1][MsCAL_THR_LIGHT]%100);
		else										_SPRINTF(pSt0, "%1d.%02d", valu[APP_CH_1][MsCAL_THR_LIGHT]/100, valu[APP_CH_1][MsCAL_THR_LIGHT]%100);


		DpFIG_DrwRect(DpFRT_LVL_VALU_X0+250, DpFRT_LVL_VALU_SINGLE_Y0-40, 200, 100, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+250, DpFRT_LVL_VALU_SINGLE_Y0-40, _cLight_level, _cBGD_SCRN, _fE75HsB, pSt0);


		if(valu[APP_CH_1][MsCAL_THR_HEAVY] >= 1000)	_SPRINTF(pSt0, "%2d.%02d", valu[APP_CH_1][MsCAL_THR_HEAVY]/100, valu[APP_CH_1][MsCAL_THR_HEAVY]%100);
		else										_SPRINTF(pSt0, "%1d.%02d", valu[APP_CH_1][MsCAL_THR_HEAVY]/100, valu[APP_CH_1][MsCAL_THR_HEAVY]%100);

		DpFIG_DrwRect(DpFRT_LVL_VALU_X0+250, DpFRT_LVL_VALU_SINGLE_Y1-40, 200, 100, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(DpFRT_LVL_VALU_X0+250, DpFRT_LVL_VALU_SINGLE_Y1-40, _cHeavy_level, _cBGD_SCRN, _fE75HsB, pSt0);		

		DpFrt_lvl_StrValue_msr();
		DpFrt_lvl_StrValue_current(APP_CH_1);
	}
}

void DpFrtLvl_StrSub(U08 type)
{
	U16 empty[APP_CH_NUM];
	I08 pSt0[32] = {0, };
	U08 i;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_LANG_KOR);


	
	if(type == MnFTR_SS_DUAL)
	{
		for(i=0; i<APP_CH_NUM; i++)
		{
			switch(lang)
			{
				case MnSYS_LANG_KOR:
					DpSTR_GuiList(TEXT_LIST_EMPTY);
					DpFIG_DrwRect(DpFRT_SUB_VALU_X0+(i*380), DpFRT_SUB_VALU_Y0, 150, 30, _cBGD_SCRN, DpFIG_FILL);
					DpSTR_GuiLeft_KOR(DpFRT_SUB_VALU_X0+(i*380), DpFRT_SUB_VALU_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);	
					_SPRINTF(pSt0, "(m)");
					DpSTR_GuiLeft(DpFRT_SUB_VALU_X0+(i*380)+117, DpFRT_SUB_VALU_Y0, _cSD_WHITE, _cBGD_SCRN, _fE17HsB, pSt0);	

					break;
				case MnSYS_LANG_ENG:
					_SPRINTF(pSt0, _sEmpty_Title);
					
					DpFIG_DrwRect(DpFRT_SUB_VALU_X0+(i*380), DpFRT_SUB_VALU_Y0, 150, 30, _cBGD_SCRN, DpFIG_FILL);
					DpSTR_GuiLeft(DpFRT_SUB_VALU_X0+(i*380), DpFRT_SUB_VALU_Y0, _cSD_WHITE, _cBGD_SCRN, _fE17HsB, pSt0);
					break;
				default:	
					break;

			}
			empty[i] = MnMSR_BaseGet_Ch_Value(i, MnMS0_OPT_SINGLE_EMPTY);
			if(empty[i] >= 1000)	_SPRINTF(pSt0, "%2d.%02d", empty[i]/100, empty[i]%100);
			else					_SPRINTF(pSt0, "%1d.%02d", empty[i]/100, empty[i]%100);		

			DpFIG_DrwRect(DpFRT_SUB_VALU_X0+i*380+20, DpFRT_SUB_VALU_Y0+40, 150, 20, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(DpFRT_SUB_VALU_X0+i*380+20, DpFRT_SUB_VALU_Y0+40, _cSD_WHITE, _cBGD_SCRN, _fE35HsB, pSt0);				
		}
	}
#if 1
	else if (type == MnFTR_SS_SINGLE)
	{
		if(lang== MnSYS_LANG_KOR)
		{
			DpSTR_GuiList(TEXT_LIST_EMPTY);
			DpFIG_DrwRect(600, DpFRT_LVL_VALU_SINGLE_Y0-20, 150, 30, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft_KOR(600, DpFRT_LVL_VALU_SINGLE_Y0-20, _cSD_WHITE, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);		
			_SPRINTF(pSt0, "(m)");
			DpSTR_GuiLeft(730, DpFRT_LVL_VALU_SINGLE_Y0-20, _cSD_WHITE, _cBGD_SCRN, _fE17HsB, pSt0);				
		}
		else if(lang == MnSYS_LANG_ENG)
		{
			_SPRINTF(pSt0, _sEmpty_Title);
			
			DpFIG_DrwRect(600, DpFRT_LVL_VALU_SINGLE_Y0-20, 150, 30, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(600, DpFRT_LVL_VALU_SINGLE_Y0-20, _cSD_WHITE, _cBGD_SCRN, _fE17HsB, pSt0);
		}
		
		empty[APP_CH_1] = MnMSR_BaseGet_Ch_Value(APP_CH_1, MnMS0_OPT_SINGLE_EMPTY);
		if(empty[APP_CH_1] >= 1000)	_SPRINTF(pSt0, "%2d.%02d", empty[APP_CH_1]/100, empty[APP_CH_1]%100);
		else						_SPRINTF(pSt0, "%1d.%02d", empty[APP_CH_1]/100, empty[APP_CH_1]%100);		

		DpFIG_DrwRect(600, DpFRT_LVL_VALU_SINGLE_Y0+10, 150, 20, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(600, DpFRT_LVL_VALU_SINGLE_Y0+10, _cSD_WHITE, _cBGD_SCRN, _fE35HsB, pSt0);			
	}
#endif
}

void DpFrtLvl_StrChnl(void)
{
	I08 pSt0[128] = {0, };
	U16 site_name;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_LANG_KOR);

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			_SPRINTF(pSt0, _sCH_1);
			DpFIG_DrwRect(DpFRT_LVL_CHNL_X0, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft(DpFRT_LVL_CHNL_X0, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, pSt0);	
			_SPRINTF(pSt0, _sCH_2); 
			DpFIG_DrwRect(DpFRT_LVL_CHNL_X1, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft(DpFRT_LVL_CHNL_X1, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, pSt0);
			break;
		case MnSYS_LANG_KOR:
			DpSTR_GuiList(TEXT_LIST_CH_1);
			DpFIG_DrwRect(DpFRT_LVL_CHNL_X0, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft_KOR(DpFRT_LVL_CHNL_X0, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);	

			#if 0
			_SPRINTF(pSt0, "1");
			DpSTR_GuiLeft(DpFRT_LVL_CHNL_X0+70, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, pSt0);
			#endif
			DpSTR_GuiList(TEXT_LIST_CH_2);
			DpFIG_DrwRect(DpFRT_LVL_CHNL_X1, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft_KOR(DpFRT_LVL_CHNL_X1, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);	

			#if 0
			_SPRINTF(pSt0, "2");
			DpSTR_GuiLeft(DpFRT_LVL_CHNL_X1+70, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, pSt0);		
			#endif
			break;
	}

	//DpFIG_DrwRect(DpFRT_LVL_CHNL_X0, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	site_name = MnSYS_PrGet_site_name(APP_CH_1);	

	_SPRINTF(pSt0, "(%c%d%d)",site_name/100,(site_name%100)/10,(site_name%100)%10);
	
	DpFIG_DrwRect(DpFRT_LVL_CHNL_X0+90, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	DpSTR_GuiLeft(DpFRT_LVL_CHNL_X0+90, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, pSt0);

	site_name = MnSYS_PrGet_site_name(APP_CH_2);	
	
	_SPRINTF(pSt0, "(%c%d%d)",site_name/100,(site_name%100)/10,(site_name%100)%10);
	DpFIG_DrwRect(DpFRT_LVL_CHNL_X1+90, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	DpSTR_GuiLeft(DpFRT_LVL_CHNL_X1+90, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, pSt0);	

}

void DpFrtBox_StrTime(void)
{
	I08 pSt0[32] = {0, };
	RTC_TM valu = RTC_GetTime();
	
	_SPRINTF(pSt0, "20%02d - %d - %d  %2d:%02d", valu.year, valu.month, valu.day, valu.hours, valu.minutes);
	DpFIG_DrwRect(DpFRT_BX_RTC_T_X0, DpFRT_BX_RTC_T_Y0, 250, 25, _cBGD_SCRN, 0);
	DpSTR_GuiLeft(DpFRT_BX_RTC_T_X0, DpFRT_BX_RTC_T_Y0, _chyb_TANK_VAL, _cBGD_SCRN, _fE17HsB, pSt0);
}

//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Tank
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Pop-Up Window
//------------------------------------------------------------------------------------------------------------------------------
void DpFR2_ValUpdat(void)
{
#if 0
	I08 sCtt[3][16] = {{0, }, };
	U16 y0[2] = {DpPOP_CT1_Y0, DpPOP_CT2_Y0};
	U08 iFn = ScFR1_GetIdxFunc();
	S32 val = ScFR2_GetValue();

	DpFIG_DrwRect(250, 175, 200, 45, _cPOP_BG_WND, 0); // Clear
	DpFIG_DrwRect(250, 235, 200, 45, _cPOP_BG_WND, 0); // Clear
	
	switch(iFn)
	{
		case ScFRT_F00_CH:		_SPRINTF(sCtt[0], _sCh_1);		_SPRINTF(sCtt[1], _sCh_2);		break;
	}

	switch(iFn)
	{
		case ScFRT_F00_CH:
			DpSTR_GuiLeft(DpPOP_CT1_X0, y0[0],   _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, sCtt[0]);
			DpSTR_GuiLeft(DpPOP_CT1_X0, y0[1],   _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, sCtt[1]);
			DpSTR_GuiLeft(DpPOP_CT1_X0, y0[val], _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, sCtt[val]);
			break;
		default:	break;
	}
#endif
}

void DpFR2_ValIntro(void)
{
#if 0
	I08 sTit[16] = {0, };
	I08 sOld[16] = {0, };
	U08 iFn = ScFR1_GetIdxFunc();

	// Pop-Up Window
	DpPOP_DrwIntro();
	// Button
	DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_DOWN);
	DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_UP__);

	// Title
	switch(iFn)
	{
		case ScFRT_F00_CH:			_SPRINTF(sTit, _sCHNNL);			break;
		default:					_SPRINTF(sTit, _sNG);				break;
	}
	DpPOP_UdtTitle(sTit);

	// Contents
	switch(iFn)
	{
		case ScFRT_F00_CH:
			switch(ScHYB_PrGet_Chnnl())
			{
				case ScFRT_CH_0:			_SPRINTF(sOld, _sCh_1);			break;
				case ScFRT_CH_1:			_SPRINTF(sOld, _sCh_2);			break;
				default:					_SPRINTF(sOld, _sNG);			break;
			}
			break;
		default:
			break;
	}
		
	// Value
	DpFR2_ValUpdat();
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L1
//------------------------------------------------------------------------------------------------------------------------------
void DpFR1_LstUpdat(void)
{
#if 0
	U08 i;
	U08 iFn = ScFR1_GetIdxFunc();
	U16 aSl[DpSCR_SBX_aNUMB];

	for(i=0; i<ScFRT_FNC_NUMB; i++)
		DpFIG_DrwRect(lDpFrt.sbx.aX0[i], lDpFrt.sbx.aY0[i], lDpFrt.sbx.aWd[i], lDpFrt.sbx.aHt[i], _cBGD_SCRN, 2);

	if(MnFTR_PrGet_SsChn() == MnFTR_SS_DUAL)
	{
		i = ScFRT_F00_CH;
		DpFIG_DrwRect(lDpFrt.sbx.aX0[i], lDpFrt.sbx.aY0[i], lDpFrt.sbx.aWd[i], lDpFrt.sbx.aHt[i], _cBGD_SCRN, 2);
	}
	
	aSl[DpSCR_SBX_aX0] = lDpFrt.sbx.aX0[iFn];
	aSl[DpSCR_SBX_aY0] = lDpFrt.sbx.aY0[iFn];
	aSl[DpSCR_SBX_aWd] = lDpFrt.sbx.aWd[iFn];
	aSl[DpSCR_SBX_aHt] = lDpFrt.sbx.aHt[iFn];

	DpFIG_DrwRect(aSl[DpSCR_SBX_aX0], aSl[DpSCR_SBX_aY0], aSl[DpSCR_SBX_aWd], aSl[DpSCR_SBX_aHt], _cBTN_FG_SELE, 2);
	DpSCR_LnHrBttn();
#endif
}

void DpFR1_LstIntro(void)
{
	DpFR1_LstUpdat();
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L0
//------------------------------------------------------------------------------------------------------------------------------
void DpFR0_FncStdBy(void)
{
	DpFrtLvl_StrValue();
	//DpFrtBox_StrTime();
}

void DpFR0_FncIntro(void)
{
	U08 type = MnFTR_PrGet_SsChn();

	DpFRT_InitVari();
	// Title
	DpTTB_UdtIntro(TEXT_LIST_SLUDGE_LEVEL_METER, 70, _cTTB_ST_TITLE);

	// Draw Screen Clear (& Status Update Flag Enable)
	DISP_IntroScrn();

	if(type == MnFTR_SS_DUAL)
		DpFrtLvl_StrChnl();

	DpFrtLvl_StrSub(type);

	// Level
	//DpFrtLvl_FgrlIcon();
	DpFrtLvl_StrTitle(type);

	// Update Parameter

	// Update Parameter
	DpFR0_FncStdBy();

	if(type == MnFTR_SS_DUAL)
	{
		DpFIG_DrwLinH(DpFRT_LINE_X0, DpFRT_LINE_Y0, DpFRT_LINE_WD, _cSD_WHITE);
		DpFIG_DrwLinH(DpFRT_LINE_X1, DpFRT_LINE_Y0, DpFRT_LINE_WD, _cSD_WHITE);
		DpFIG_DrwLinH(DpFRT_LINE_X0, DpFRT_LINE_Y1, DpFRT_LINE_WD, _cSD_WHITE);
		DpFIG_DrwLinH(DpFRT_LINE_X1, DpFRT_LINE_Y1, DpFRT_LINE_WD, _cSD_WHITE);	
	}
	else
	{
		DpFIG_DrwLinV(DpFRT_LINE_SINGLE_X0,DpFRT_LINE_Y0-20,260,_cSD_WHITE);
	}
#if 0
	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR))
		DpFIG_DrwLinH(DpFRT_LINE_X0, DpFRT_LINE_Y2, 800-DpFRT_LINE_X0-DpFRT_LINE_X0, _cSD_WHITE);
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void DpFRT_InitVari(void)
{
	lDpFrt.level = 0xffff;
	lDpFrt.bx_lv = 0xffff;
	lDpFrt.curr = 0xffff;
	lDpFrt.tprt = 0xffff;
	lDpFrt.unit = 0xff;
	lDpFrt.time.minutes = 0;

#if 0
	lDpFrt.sbx.aX0[ScFRT_F00_CH] = DpFRT_LVL_CHNL_X0 - 8;
	lDpFrt.sbx.aY0[ScFRT_F00_CH] = DpFRT_LVL_CHNL_Y0 - 3;
	lDpFrt.sbx.aWd[ScFRT_F00_CH] = DpFRT_LVL_CHNL_WD;
	lDpFrt.sbx.aHt[ScFRT_F00_CH] = DpFRT_LVL_CHNL_HT;
#endif
}




//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

