//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___SCREEN_INFO_H___
#define ___SCREEN_INFO_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Parameter
//------------------------------------------------------------------------------------------------------------------------------
// List Index
enum {
	ScINF_OPT_CH1_FREQ = 0,
	ScINF_OPT_CH1_OFFSET,
	ScINF_OPT_CH1_4mA,
	ScINF_OPT_CH1_20mA,
	ScINF_OPT_CH1_MSR_CYC,
	ScINF_OPT_CH1_DAMP,
	ScINF_OPT_CH2_FREQ,
	ScINF_OPT_CH2_OFFSET,
	ScINF_OPT_CH2_4mA,
	ScINF_OPT_CH2_20mA,
	ScINF_OPT_CH2_MSR_CYC,
	ScINF_OPT_CH2_DAMP,	
	
	ScINF_OPT_NUM,
};
#define ScINF_OPT_MIN	(ScINF_OPT_CH1_FREQ)
#define ScINF_OPT_MAX	(ScINF_OPT_NUM)

enum {
	// Left Side
	ScINF_OPT_SINGLE_FREQ = 0,
	ScINF_OPT_SINGLE_OFFSET,
	ScINF_OPT_SINGLE_4_20mA,
	ScINF_OPT_SINGLE_DAMP,
	ScINF_OPT_SINGLE_TVG,
	
	ScINF_OPT_SINGLE_NUM,
};
#define ScINF_OPT_SINGLE_MIN	(ScINF_OPT_SINGLE_FREQ)
#define ScINF_OPT_SINGLE_MAX	(ScINF_OPT_SINGLE_NUM)

// Measurement Channel
enum {
	ScINF_CH_0 = 0,
	ScINF_CH_1,
	// Number Max
	ScINF_CH_NUM,
};

#if 0
// Tx Cycle
enum {
	ScPRM_TX_CYC_SEC01 = 0,
	ScPRM_TX_CYC_SEC02,
	ScPRM_TX_CYC_SEC03,
	ScPRM_TX_CYC_SEC05,
	ScPRM_TX_CYC_SEC10,
	ScPRM_TX_CYC_SEC30,
	ScPRM_TX_CYC_SEC60,
	// Number Max
	ScPRM_TX_CYC_NUMB,
};
#endif

//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Memory Parameter
typedef union {
	S32 val;
	U08 iCh;
} ScINF_mPR;

// Display List
typedef union {
	U16 tx_cycle[ScINF_CH_NUM];	// Tx Cycle For Measure
	U16 filt_rst[ScINF_CH_NUM];	// Filter Reset Time
	U16 cln_intv[ScINF_CH_NUM];	// PCD Interval Time
	U16 cln_time[ScINF_CH_NUM];	// PCD Operation Time

} ScINF_LST;

// Local Struct
typedef struct {
	ScINF_mPR mPr;			// Memory - Parameter
	ScINF_LST lst;			// Memory - Parameter
	U08 lyr;				// Layer

} ScINF_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Vairables - Parameters
//------------------------------------------------------------------------------------------------------------------------------
extern U08 ScINF_PrGet_Chnnl(void);

//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Parameters
//------------------------------------------------------------------------------------------------------------------------------
extern void ScINF_PrSet_Value(S32 val);
extern void ScINF_PrRst_Factory(void);


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Vairables - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern void ScINF_SetLayer(U08 lyr);


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern void ScINF_PrInitMain(void);
extern void ScINF_InitMain(void);
extern void ScINF_ProcMain(void);



#endif // ___SCREEN_INFO_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

