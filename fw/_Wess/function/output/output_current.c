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
#include "bsp_gpio.h"
#include "bsp_spi.h"
#include "bsp_demux.h"
// app
#include "app_main.h"
#include "app_math.h"
#include "app_status.h"
// measure
#include "measure_calc.h"
#include "measure_cal1_field0.h"
// menu
#include "menu_engineer.h"
#include "menu_measure.h"
#include "menu_factory.h"
#include "menu_output.h"
#include "menu_main.h"
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
#include "menu_engineer.h"
// screen
#include "screen_hybrid.h"

#include "disp_color.h"
#include "disp_figure.h"
#include "disp_string.h"
#include "fonts.h"
// self
#include "output_current.h"

#include "data_save.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
OuCUR_LS lOuCur;

//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
void OuCur_CalcMA(U08 ch, U16 msr)
{
	F32 dg_c;
	F32 dg_data = msr;
	U08 err_outp = MnOUT_ErrPrGet_Value(MnOS3_OPT_ERR_OUTP);

	if(ApSTT_GetStatus(ch)>= ApSTT_MSR_NG)
	{
		switch(err_outp)
		{
			case MnOS3_ERR_OUTPUT_HOLD:	return;
			case MnOS3_ERR_OUTPUT_38mA:	lOuCur.value[ch] = OuCUR_ERR038MA;	return;
			case MnOS3_ERR_OUTPUT_21mA:	lOuCur.value[ch] = OuCUR_ERR210MA;	return;	
			default:					return;
		}
	}

	dg_c = MTH_ConvAtoB(dg_data, lOuCur.set_04mA[ch], lOuCur.set_20mA[ch], OuCUR_04MA, OuCUR_20MA);
	
    if (dg_c < OuCUR_04MA)       dg_c = OuCUR_04MA;
    if (dg_c > OuCUR_20MA)       dg_c = OuCUR_20MA;

	lOuCur.value[ch] = dg_c;


}


void OuCur_DacSet(U08 ch)
{
	lOuCur.set_04mA[ch] = MnOUT_CurPrGet_CH_Value(ch, MnOS0_OPT_SINGLE_SET_04mA);
	lOuCur.set_20mA[ch] = MnOUT_CurPrGet_CH_Value(ch, MnOS0_OPT_SINGLE_SET_20mA);
	lOuCur.trm_12mA[ch] = MnOUT_CurPrGet_CH_Value(ch, MnOS0_OPT_SINGLE_TRM_12mA);
	lOuCur.trm_20mA[ch] = MnOUT_CurPrGet_CH_Value(ch, MnOS0_OPT_SINGLE_TRM_20mA);
	
	lOuCur.dac_04mA[ch] = (U16)((S32)MnFTR_PrGet_CH_Value(ch,MnFTR_OPT_SINGLE_04mA) - lOuCur.trm_20mA[ch]);
	lOuCur.dac_20mA[ch] = (U16)((S32)MnFTR_PrGet_CH_Value(ch,MnFTR_OPT_SINGLE_20mA) + lOuCur.trm_20mA[ch]);

	lOuCur.dac_38mA[ch] = lOuCur.dac_04mA[ch] - ((((lOuCur.dac_20mA[ch] - lOuCur.dac_04mA[ch]) + 5) / 8) / 10);
	lOuCur.dac_21mA[ch] = lOuCur.dac_20mA[ch] + ((lOuCur.dac_20mA[ch] - lOuCur.dac_04mA[ch]) / 16); 
}


void OuCur_ProcSingle(void)
{
#if 0
	U08 lv_type = ScHYB_PrGet_LvTyp();
	U16 err_outp = MnOUT_ErrPrGet_Value(MnOS3_OPT_ERR_OUTP);


	//Measurement
	switch(lv_type)
	{
		case ScHYB_LVL_SLDG:
			lOuCur.out_valu[ScHYB_CH_0] = MsCAL_GetVl_RsltSldg(ScHYB_CH_0,0);
			break;
		case ScHYB_LVL_DIST:
			lOuCur.out_valu[ScHYB_CH_0] = MsCAL_GetVl_RsltDist(ScHYB_CH_0,0);
			break;
		default:
			break;
	}

	if(lOuCur.out_valu[ScHYB_CH_0]>=lOuCur.set_20mA[ScHYB_CH_0]) 	lOuCur.out_valu[ScHYB_CH_0]=lOuCur.set_20mA[ScHYB_CH_0];
		
	lOuCur.out_dac[ScHYB_CH_0] = MTH_ConvAtoB(lOuCur.out_valu[ScHYB_CH_0], lOuCur.set_04mA[ScHYB_CH_0], lOuCur.set_20mA[ScHYB_CH_0], lOuCur.dac_04mA[ScHYB_CH_0], lOuCur.dac_20mA[ScHYB_CH_0]);

	lOuCur.out_dac[ScHYB_CH_0] = lOuCur.out_dac[ScHYB_CH_0]+lOuCur.trm_12mA[MnFTR_CH_0];

	if(lOuCur.out_dac[ScHYB_CH_0]>=lOuCur.dac_20mA[ScHYB_CH_0])	lOuCur.out_dac[ScHYB_CH_0]=lOuCur.dac_20mA[ScHYB_CH_0];
	if(lOuCur.out_dac[ScHYB_CH_0]<=lOuCur.dac_04mA[ScHYB_CH_0])	lOuCur.out_dac[ScHYB_CH_0]=lOuCur.dac_04mA[ScHYB_CH_0];
	// Error
	if(ApSTT_GetStatus(ScHYB_CH_0)==ApSTT_MSR_NG)	
	{
		switch(err_outp)
		{
			case MnOS3_IV1_HOLD:	return;
			case MnOS3_IV1_38mA:	lOuCur.out_dac[ScHYB_CH_0] = lOuCur.dac_38mA[ScHYB_CH_0];	break;
			case MnOS3_IV1_21mA:	lOuCur.out_dac[ScHYB_CH_0] = lOuCur.dac_21mA[ScHYB_CH_0];	break;
			default:				return;
		}
	}
	
	OuCUR_WrDac(APP_CH_1, lOuCur.out_dac[ScHYB_CH_0]);
	OuCur_CalcMA(APP_CH_1, lOuCur.out_valu[APP_CH_1]);
#endif
}


void OuCur_ProcDual(U08 ch)
{
	U08 lv_type = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_OPERATION);
	U08 assign= MnOUT_CurPrGet_CH_Value(ch,MnOS0_OPT_SINGLE_ASSIGN);
	U16 err_outp = MnOUT_ErrPrGet_Value(MnOS3_OPT_ERR_OUTP);

	U08 msr_ch = ch;


	if((MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON))
	{
		switch(assign)
		{
			case MnOS0_ASSIGN_LIGHT:	
				lOuCur.out_valu[ch] = MsCAL1_Hunting_value(msr_ch, MsCAL_THR_LIGHT);
				break;
			case MnOS0_ASSIGN_HEAVY:
				lOuCur.out_valu[ch] = MsCAL1_Hunting_value(msr_ch, MsCAL_THR_HEAVY);
				break;
			default:		
				break;
		}
	}
	else
	{
		switch(assign)
		{
			case MnOS0_ASSIGN_LIGHT:	
				switch(lv_type)
				{
					case MnMS0_OPERATION_SLUDGE:		lOuCur.out_valu[ch] = MsCAL_GetVl_RsltSldg(msr_ch,MsCAL_THR_LIGHT);		break;
					case MnMS0_OPERATION_DISTANCE:		lOuCur.out_valu[ch] = MsCAL_GetVl_RsltDist(msr_ch,MsCAL_THR_LIGHT);		break;
					default:
						break;
				}
				break;
			case MnOS0_ASSIGN_HEAVY:
				switch(lv_type)
				{
					case MnMS0_OPERATION_SLUDGE:		lOuCur.out_valu[ch] = MsCAL_GetVl_RsltSldg(msr_ch,MsCAL_THR_HEAVY);		break;
					case MnMS0_OPERATION_DISTANCE:		lOuCur.out_valu[ch] = MsCAL_GetVl_RsltDist(msr_ch,MsCAL_THR_HEAVY);		break;
					default:
						break;
				}
				break;
			default:		
				break;
		}
	}
#if 0
	if((MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON) && (MsCal1_Getrst_dtt(ch)==TRUE))
	{
		switch(assign)
		{
			case MnOS0_ASSIGN_LIGHT:			lOuCur.out_valu[ch] = DaSav_GetTrendValue(ch);		break;
			case MnOS0_ASSIGN_HEAVY:			lOuCur.out_valu[ch] = DaSav_GetTrendValue(ch);		break;
		}
	}
#endif
	if(lOuCur.out_valu[ch]>=lOuCur.set_20mA[ch]) 	lOuCur.out_valu[ch]=lOuCur.set_20mA[ch];

	lOuCur.out_dac[ch] = MTH_ConvAtoB(lOuCur.out_valu[ch], lOuCur.set_04mA[ch], lOuCur.set_20mA[ch], lOuCur.dac_04mA[ch], lOuCur.dac_20mA[ch]);


	lOuCur.out_dac[ch] = lOuCur.out_dac[ch]+lOuCur.trm_12mA[ch];
	if(lOuCur.out_dac[ch]>=lOuCur.dac_20mA[ch])	lOuCur.out_dac[ch]=lOuCur.dac_20mA[ch];
	if(lOuCur.out_dac[ch]<=lOuCur.dac_04mA[ch])	lOuCur.out_dac[ch]=lOuCur.dac_04mA[ch];




#if 1
	//Error
	if(ApSTT_GetStatus(ch)>= ApSTT_MSR_NG)
	{
		switch(err_outp)
		{
			case MnOS3_ERR_OUTPUT_HOLD:	return;
			case MnOS3_ERR_OUTPUT_38mA:	lOuCur.out_dac[ch] = lOuCur.dac_38mA[ch];	break;
			case MnOS3_ERR_OUTPUT_21mA:	lOuCur.out_dac[ch] = lOuCur.dac_21mA[ch];	break;	
			default:					return;
		}
	}
#endif

	OuCUR_WrDac(ch, lOuCur.out_dac[ch]);
	OuCur_CalcMA(ch, lOuCur.out_valu[ch]);

}

void OuCur_ProcMsr(U08 ch)
{	
	OuCur_DacSet(ch); 
	OuCur_ProcDual(ch);
}

void OuCur_ProcCfg(U08 ch)
{
	U08 iSc = MENU_GetSection();
	U08 sub = MnLY1_GetSection();
	U08 iIt = MnLY2_GetIdxItem();
	S32 trm_12mA[MnOUT_CH_NUM] = {0, };
	S32 trm_20mA[MnOUT_CH_NUM] = {0, };
	U16 dac_04mA[MnOUT_CH_NUM] = {0, };
	U16 dac_20mA[MnOUT_CH_NUM] = {0, };
	U16 dac_12mA[MnOUT_CH_NUM] = {0, };
	U16 out_cur;

	trm_12mA[ch] = MnOUT_CurPrGet_CH_Value(ch,MnOS0_OPT_SINGLE_TRM_12mA);
	trm_20mA[ch] = MnOUT_CurPrGet_CH_Value(ch,MnOS0_OPT_SINGLE_TRM_20mA);
	dac_04mA[ch] = MnFTR_PrGet_CH_Value(ch,MnFTR_OPT_SINGLE_04mA);
	dac_20mA[ch] = MnFTR_PrGet_CH_Value(ch,MnFTR_OPT_SINGLE_20mA);
	dac_12mA[ch] = (dac_20mA[ch]-dac_04mA[ch])/2+dac_04mA[ch];	

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(iSc)
		{
			case MENU_SC1_OUTP:		
				switch(sub)
				{
					case MnOUT_SUB_CURRENT:
						switch(iIt)
						{
							case MnOS0_OPT_CH1_TRM_12mA:	out_cur =	(U16)((S32)MnLY3_GetValue() + dac_12mA[ch]);						break;
							case MnOS0_OPT_CH1_TRM_20mA:	out_cur =	(U16)((S32)MnLY3_GetValue() + dac_20mA[ch] + trm_12mA[ch]);			break;
							case MnOS0_OPT_CH1_OUT_04mA:	out_cur = 	dac_04mA[ch] + trm_12mA[ch] -  trm_20mA[ch];						break;
							case MnOS0_OPT_CH2_TRM_12mA:	out_cur =	(U16)((S32)MnLY3_GetValue() + dac_12mA[ch]);						break;
							case MnOS0_OPT_CH2_TRM_20mA:	out_cur =	(U16)((S32)MnLY3_GetValue() + dac_20mA[ch] + trm_12mA[ch]);			break;
							case MnOS0_OPT_CH2_OUT_04mA:	out_cur = 	dac_04mA[ch] + trm_12mA[ch] -  trm_20mA[ch];						break;
							default:																																
								return;
						}
						break;					
					default:
						break;
				}
				break;

			case MENU_SC5_FCTR:
				switch(iIt)
				{
					case MnFTR_I00_SS_CH:
						break;
					case MnFTR_I01_CH0_04mA:
					case MnFTR_I02_CH0_20mA:
					case MnFTR_I03_CH1_04mA:
					case MnFTR_I04_CH1_20mA:
						out_cur = (U16)((S32)MnLY3_GetValue());
						break;
					case MnFTR_I05_CH1_TRIM_12MA:			out_cur =	(U16)((S32)MnLY3_GetValue() + dac_12mA[ch]);						break;
					case MnFTR_I06_CH1_TRIM_20MA:			out_cur =	(U16)((S32)MnLY3_GetValue() + dac_20mA[ch] + trm_12mA[ch]);			break;
					case MnFTR_I07_CH1_OUTPUT_4MA:			out_cur = 	dac_04mA[ch] + trm_12mA[ch] -  trm_20mA[ch];						break;
					case MnFTR_I08_CH2_TRIM_12MA:			out_cur =	(U16)((S32)MnLY3_GetValue() + dac_12mA[ch]);						break;
					case MnFTR_I09_CH2_TRIM_20MA:			out_cur =	(U16)((S32)MnLY3_GetValue() + dac_20mA[ch] + trm_12mA[ch]);			break;
					case MnFTR_I10_CH2_OUTPUT_4MA:			out_cur = 	dac_04mA[ch] + trm_12mA[ch] -  trm_20mA[ch];						break;
					default:
						break;
				}
				break;
			default:		return;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(iSc)
		{
			case MENU_SC1_OUTP: 	
				switch(sub)
				{
					case MnOUT_SUB_CURRENT:
						switch(iIt)
						{
							case MnOS0_OPT_SINGLE_TRM_12mA:	out_cur =	(U16)((S32)MnLY3_GetValue() + dac_12mA[ch]);						break;
							case MnOS0_OPT_SINGLE_TRM_20mA:	out_cur =	(U16)((S32)MnLY3_GetValue() + dac_20mA[ch] + trm_12mA[ch]); 		break;
							case MnOS0_OPT_SINGLE_OUT_04mA:	out_cur =	dac_04mA[ch] + trm_12mA[ch] -  trm_20mA[ch];						break;

							default:																																
								return;
						}
						break;					
					default:
						break;
				}
				break;
		
			case MENU_SC5_FCTR:
				switch(iIt)
				{
					case MnFTR_OPT_SINGLE_SS_CH:
						break;
					case MnFTR_OPT_SINGLE_04mA:
					case MnFTR_OPT_SINGLE_20mA:
						out_cur = (U16)((S32)MnLY3_GetValue());
						break;
					case MnFTR_OPT_SINGLE_TRIM_12MA:			out_cur =	(U16)((S32)MnLY3_GetValue() + dac_12mA[ch]);						break;
					case MnFTR_OPT_SINGLE_TRIM_20MA:			out_cur =	(U16)((S32)MnLY3_GetValue() + dac_20mA[ch] + trm_12mA[ch]); 		break;
					case MnFTR_OPT_SINGLE_OUTPUT_4MA:			out_cur =	dac_04mA[ch] + trm_12mA[ch] -  trm_20mA[ch];						break;
					default:
						break;
				}
				break;
			default:		return;
		}
	}

	OuCUR_WrDac(ch, out_cur);

}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 OuCUR_GetOutp_Type(U08 ch)					   {	 return lOuCur.type[ch];	}
U16 OuCUR_GetOutp_Value(U08 ch)					   {	 return lOuCur.value[ch];	}	

// Set
void OuCUR_SetOutp_Type(U08 ch, U08 type)		{		 lOuCur.type[ch] = type;	}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void OuCUR_WrDac(U08 ch, U16 ad)
{
	U08 wr_data[3];
	U08 cmd = 0;

	if		(ch == APP_CH_1)	cmd = 0x18;
	else if	(ch == APP_CH_2)	cmd = 0x19;

	wr_data[0] = (cmd & 0x3f);
	wr_data[1] = ((ad  & 0xff00) >>  8);
	wr_data[2] = ((ad  & 0x00ff) >>  0);

	SPI_SetCurrent();
	
	DMX_SetIo(DMX_OUT_CS_CURRENT , GIO_LV_LO);
	SPI_WrSize((U08*)wr_data, 3);
	DMX_SetIo(DMX_OUT_CS_CURRENT , GIO_LV_HI);

}

void OuCUR_InitMain(void)
{
	U08 i;
	
	lOuCur.value[APP_CH_1] = 400;
	lOuCur.value[APP_CH_2] = 400;
	lOuCur.out_dac[APP_CH_1] = OuCUR_04MA_AD;
	lOuCur.out_dac[APP_CH_2] = OuCUR_04MA_AD;

	for(i=0; i<APP_CH_NUM; i++)
	{
		lOuCur.stt[i] = ApSTT_MSR_OK;

		lOuCur.type[i] = OuCUR_TYPE_MSR;
		lOuCur.out_valu[i] = 400;
		lOuCur.set_04mA[i] = MnOS0_SET_4MA_DEF;
		lOuCur.set_20mA[i] = MnOS0_SET_20MA_DEF;
		lOuCur.trm_12mA[i] = MnOS0_TRIM_DEF;
		lOuCur.trm_20mA[i] = MnOS0_TRIM_DEF;
		lOuCur.dac_04mA[i] = MnFTR_CFG_04mA_DEF;
		lOuCur.dac_20mA[i] = MnFTR_CFG_20mA_DEF;
		lOuCur.dac_38mA[i] = lOuCur.dac_04mA[i] - ((((lOuCur.dac_20mA[i] - lOuCur.dac_04mA[i]) + 5) / 8) / 10);
		lOuCur.dac_21mA[i] = lOuCur.dac_20mA[i] + ((lOuCur.dac_20mA[i] - lOuCur.dac_04mA[i]) / 16); 

		OuCUR_WrDac(i, OuCUR_04MA_AD);
	}
}

void OuCUR_ProcMain(void)
{

	switch(lOuCur.type[APP_CH_1])
	{
		case OuCUR_TYPE_MSR:			OuCur_ProcMsr(APP_CH_1);					break;
		case OuCUR_TYPE_CHK:			OuCur_ProcCfg(APP_CH_1);					break;
		default:																	break;
	}

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(lOuCur.type[APP_CH_2])
		{
			case OuCUR_TYPE_MSR:			OuCur_ProcMsr(APP_CH_2);					break;
			case OuCUR_TYPE_CHK:			OuCur_ProcCfg(APP_CH_2);					break;
			default:						break;
		}
	}
	
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

