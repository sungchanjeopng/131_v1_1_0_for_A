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
// display
#include "disp_color.h"
#include "disp_string.h"
#include "disp_titlebar.h"
// menu - section
#include "menu_measure.h"
#include "menu_output.h"
#include "menu_data.h"
#include "menu_system.h"
#include "menu_engineer.h"
#include "menu_factory.h"
#include "menu_test.h"
#include "dp_menu_main.h"
// menu - layer
#include "menu_lyr0_section.h"
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
#include "menu_lyr4_addition.h"
// function
#include "input_key.h"
#include "input_main.h"
// self
#include "menu_main.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MENU_LS lMn;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 MENU_GetLayer(void)				{	return lMn.lyr;		}
U08 MENU_GetSection(void)			{	return lMn.sct;		}
U08 MENU_GetFgHiddn(void)			{	return lMn.fHd;		}
S32 MENU_GetPassMode(void)      {  return lMn.pass_mode;  }
S32 MENU_GetPassdig(void)      {  return lMn.pass_dig;  }
S32 MENU_GetPassVal(void)      {  return lMn.pass_val;  }

// Set
void MENU_SetLayer(U08 lyr)			{	lMn.lyr = lyr;		}
void MENU_SetSection(U08 sct)		{	lMn.sct = sct;		}
void MENU_SetFgHiddn(U08 fHd)		{	lMn.fHd = fHd;		}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Parameters
//------------------------------------------------------------------------------------------------------------------------------
void MENU_PrInitMain(void)
{
	MnMSR_PrInitMain();
	MnOUT_PrInitMain();
	MnDAT_PrInitMain();
	MnSYS_PrInitMain();

	MnEGN_PrInitMain();
	MnFTR_PrInitMain();
	MnTST_PrInitMain();
}


void MENU_PrRst_Factory(void)
{
	MnMSR_PrRst_Factory();
	MnOUT_PrRst_Factory();
	MnDAT_PrRst_Factory();
	MnSYS_PrRst_Factory();
	// Hidden Menu
	MnEGN_PrRst_Factory();
	MnFTR_PrRst_Factory();
	MnTST_PrRst_Factory();

	MENU_PrInitMain();
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void MENU_InitSect(U08 Sel)
{
	switch(Sel)
	{	// Open Menu
		case MENU_SC0_MEAS:			MnMSR_InitMain();			break;
		case MENU_SC1_OUTP:			MnOUT_InitMain();			break;
		case MENU_SC2_DATA:			MnDAT_InitMain();			break;
		case MENU_SC3_SYST:			MnSYS_InitMain();			break;
		// Hidden Menu
		case MENU_SC4_EGNR:			MnEGN_InitMain();			break;
		case MENU_SC5_FCTR:			MnFTR_InitMain();			break;
		case MENU_SC6_TEST:			MnTST_InitMain();			break;
		default:					break;
	}
}

void MENU_InitMain(void)
{
  U08 i;

  lMn.lyr = MENU_L0_SECTION;
  lMn.sct = MENU_SC0_MEAS;
  lMn.fHd = _F_F;
  lMn.fTt = _F_F;
  lMn.pass = _F_T;
  lMn.pass_val = 0;
  lMn.pass_mode = PASS_UPDN_DIG;
  lMn.pass_dig = 0;
  lMn.step = MENU_S0_INTRO;

  for(i=0; i<MENU_SCN_NUM; i++)
    MENU_InitSect(i);
}

void MENU_ExitMain(void)
{
  if(lMn.fHd)
    lMn.sct = MENU_SC3_SYST;

  lMn.fHd = _F_F;
  lMn.fTt = _F_F;
  lMn.pass = _F_T;  
  lMn.pass_val = 0;
  lMn.pass_mode = PASS_UPDN_DIG;
  lMn.pass_dig = 0;
  lMn.step = MENU_S0_INTRO;

  APP_SetMode(APP_MD0_SCRN);
}

void MENU_Passcode(void)
{
  U08 evt = INPU_GetKeyEvt();
  U08 key = INPU_GetKeyIdx();
  S32 min = 0;
  S32 max = 9999;
  S32 dig_min = 0;
  S32 dig_max = log10(max);

  switch(evt)
  {
    case KEY_EVT_PUSH:
    case KEY_EVT_DTT_L:
    case KEY_EVT_SHORT:
    case KEY_EVT_REPEAT:
    case KEY_EVT_LONG:
      switch(key)
      {
        case KEY_IDX_MENU:    
			switch(lMn.pass_mode)
			{
			  case PASS_UPDN_DIG:
			  	MENU_ExitMain(); 
				break;
			  case PASS_UPDN_DIG_VALUE:	
			  	lMn.pass_mode = PASS_UPDN_DIG;	
			  	break;
			} 
			break;
        case KEY_IDX_PREV:		
        case KEY_IDX_NEXT:		  
          switch(lMn.pass_mode)
          {
            case PASS_UPDN_DIG:
              switch(key)
              {
                case KEY_IDX_PREV:
                  if(++lMn.pass_dig > dig_max)   lMn.pass_dig = dig_min;
                  break;
                case KEY_IDX_NEXT:
                  if(--lMn.pass_dig< dig_min)   lMn.pass_dig = dig_max;
                  break;
                default:
                  break;
              }
              break;
            case PASS_UPDN_DIG_VALUE:
              switch(key)
              {
                case KEY_IDX_PREV:
                  switch(lMn.pass_dig)
                  {
                    case 4: lMn.pass_val-=10000;  break;
                    case 3: lMn.pass_val-=1000;    break;
                    case 2: lMn.pass_val-=100;    break;
                    case 1: lMn.pass_val-=10;     break;
                    case 0: lMn.pass_val-=1;    break;
                    default:  
                    	break;        
                  }
                  if(lMn.pass_val<min)  lMn.pass_val= min;
                  break;
                case KEY_IDX_NEXT:
                  switch(lMn.pass_dig)
                  {
                    case 4: lMn.pass_val+=10000;  break;
                    case 3: lMn.pass_val+=1000;  break;
                    case 2: lMn.pass_val+=100;  break;
                    case 1: lMn.pass_val+=10;   break;
                    case 0: lMn.pass_val+=1;    break;
                    default:  break;        
                  }  
                  if(lMn.pass_val>max)  
				  	lMn.pass_val= max;
                  break;
                default:  
                  break;
              }
              break;
            default:  break;
          }
          break;
        case KEY_IDX_ENTER: 
			switch(lMn.pass_mode)
			{
			  case PASS_UPDN_DIG:
			  	lMn.pass_mode =  PASS_UPDN_DIG_VALUE;
				break;
			  case PASS_UPDN_DIG_VALUE:	
				if((lMn.pass_val == MnSYS_PrGetBase_Item(MnSYS_OPT_PASSCODE)) || (lMn.pass_val == 129))
				 lMn.pass= _F_F;
			  	break;
			} 
			break;					
        default:          break;
      }
      break;
    default:
      break;
  }
  
  INPU_ClrKeyEvt(KEY_EVT_NONE);
  DpMn_PopIntro();
  DpMn_PopUpdat();

}

void MENU_ProcMain(void)
{
  U08 evt = INPU_GetKeyEvt();

  if(!lMn.fTt)
  {
    DpTTB_UdtIntro(TEXT_LIST_MENU, 70, _cTTB_ST_TITLE);
    lMn.fTt = _F_T;
  }

  if(lMn.pass)
  {
  	switch(lMn.step)
  	{
  		case MENU_S0_INTRO:
			switch(evt)
			{
				case KEY_EVT_PUSH:
				case KEY_EVT_DTT_L:
				case KEY_EVT_SHORT:
				case KEY_EVT_REPEAT:
				case KEY_EVT_LONG:	
					lMn.step = MENU_S1_STDBY;				
					break;
				default:
					break;
			}
			DpMn_PopIntro();
			DpMn_PopUpdat();
			break;
		case MENU_S1_STDBY:
			MENU_Passcode();
			lMn.step = MENU_S0_INTRO;
			break;
  	}
  }

  if(lMn.pass==_F_T)  return;
  
  switch(lMn.lyr)
  {
    case MENU_L0_SECTION:    MnLY0_ProcSection();      break;
    case MENU_L1_SUB_SCT:    MnLY1_ProcSubSct();        break;
    case MENU_L2_ITEM:      MnLY2_ProcItem();        break;
    case MENU_L3_VALUE:     MnLY3_ProcValue();        break;
    case MENU_L4_ADDITION:    MnLY4_ProcAddition();      break;
    default:          lMn.lyr = MENU_L0_SECTION;    break;
  }
}




//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

