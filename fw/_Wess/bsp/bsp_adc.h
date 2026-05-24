//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___BSP_ADC_H___
#define ___BSP_ADC_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
// core
#include "main.h"
#include "adc.h"
// bsp
#include "bsp_timer.h"
#include "bsp_dac.h"
// app
#include "app_main.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
enum {
	ADC_CH_SS0 = 0,
	ADC_CH_SS1,

	ADC_CH_NUMB
};

#define ADC_BUFF_MAX		(1100)
#define ADC_VAL_MAX			(4096.0)


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	U08 chnl_idx;
	U16 echo_idx;
	U16 echo_idx_max;
	U16 echo_aBf[ADC_CH_NUMB][ADC_BUFF_MAX];
	U16 tprt_aVl[ADC_CH_NUMB];		 		// Temperature Value
	U16 tprt_aVt[ADC_CH_NUMB]; 				// Temperature Volt

	U08 filed_sel;
} ADC_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get Local Variables
extern U16 ADC_GetTprtVal(U08 ch);
extern U16 ADC_GetTprtVlt(U08 ch);
extern U16 ADC_GetEchoVal(U08 ch, U16 idx);
extern U16 ADC_GetEchoIdx(void);
extern U16 ADC_GetEchoIdx_max(void);
extern U08 ADC_GetChnlIdx(void);
extern U32* ADC_GetEchoAddr(U08 ch);
extern U16 DAC_GetTvgValue(U08 i);
extern U08 ADC_Get_FieldSel(void);
// Set Local Variables
extern void ADC_SetEchoVal(U08 ch, U16 idx, U16 val);
extern void ADC_SetEchoIdx(U16 val);
// Operation
extern void ADC_InitVari(void);
extern void ADC_ProcTprt(void);
extern void ADC_ProcEcho(U08 ch);
extern void ADC_ProcEcho_FieldA(U08 ch);


#endif // ___BSP_ADC_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

