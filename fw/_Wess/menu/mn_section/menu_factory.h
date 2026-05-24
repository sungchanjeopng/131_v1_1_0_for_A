//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2022-01-20 12:00:00 +0900 $ (From 2020-07-13)
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___MENU_FACTORY_H___
#define ___MENU_FACTORY_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "app_main.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
// Item Index
enum {
	MnFTR_I00_SS_CH = 0,
	MnFTR_I01_CH0_04mA,
	MnFTR_I02_CH0_20mA,
	MnFTR_I03_CH1_04mA,
	MnFTR_I04_CH1_20mA,
	MnFTR_I05_CH1_TRIM_12MA,
	MnFTR_I06_CH1_TRIM_20MA,
	MnFTR_I07_CH1_OUTPUT_4MA,
	MnFTR_I08_CH2_TRIM_12MA,
	MnFTR_I09_CH2_TRIM_20MA,
	MnFTR_I10_CH2_OUTPUT_4MA,
	MnFTR_I11_RELAY_TEST,
	MnFTR_I12_LANG,
	MnFTR_I13_TIME,
	MnFTR_I14_VERSION,
	MnFTR_I15_CLEAN_TEST,
	// Number Max
	MnFTR_ITM_NUM,
};
#define MnFTR_ITM_I00			(MnFTR_I00_SS_CH)

enum {
	MnFTR_OPT_SINGLE_SS_CH = 0,
	MnFTR_OPT_SINGLE_04mA,
	MnFTR_OPT_SINGLE_20mA,
	MnFTR_OPT_SINGLE_TRIM_12MA,
	MnFTR_OPT_SINGLE_TRIM_20MA,
	MnFTR_OPT_SINGLE_OUTPUT_4MA,
	MnFTR_OPT_SINGLE_RELAY_TEST,
	MnFTR_OPT_SINGLE_LANG,
	MnFTR_OPT_SINGLE_TIME,
	MnFTR_OPT_SINGLE_VERSION,
	MnFTR_OPT_SINGLE_CLEAN_TEST,	
	// Number Max
	MnFTR_OPT_SINGLE_NUM,
};

#define MnFTR_OPT_SINGLE_MIN			(MnFTR_OPT_SINGLE_SS_CH)

#if 1
// Value - #0 (Sensor)
enum {
	MnFTR_SS_SINGLE = 0,
	MnFTR_SS_DUAL,
	// Number Max
	MnFTR_SS_NUM
};

#define MnFTR_CH_MIN			(MnFTR_SS_SINGLE)
#define MnFTR_CH_MAX			(MnFTR_SS_DUAL)
#define MnFTR_CH_DEF			(MnFTR_SS_DUAL)
// Value - #1 (Cfg. 4mA)
#define MnFTR_CFG_04mA_MIN		(0)
#define MnFTR_CFG_04mA_MAX		(65000)
#define MnFTR_CFG_04mA_DEF		(10641)

// Value - #2 (Cfg. 20mA)
#define MnFTR_CFG_20mA_MIN		(0)
#define MnFTR_CFG_20mA_MAX		(65000)
#define MnFTR_CFG_20mA_DEF		(53718)

#else
// Channel
enum {
	MnFTR_SS_SINGLE = 0,
	MnFTR_SS_DUAL,
	// Number Max
	MnFTR_SS_NUM
};
#endif

// Sensor Index
enum {
	MnFTR_CH_0 = 0,
	MnFTR_CH_1,
	// Number Max
	MnFTR_CH_NUM,
};


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Memory Parameter
typedef struct {
	U08 chnl;		// Channel - Signgle / Dual
	U16 cfg_4mA[APP_CH_NUM];
	U16 cfg_20mA[APP_CH_NUM];
} MnFTR_mPR;

// Local Struct
typedef struct {
	MnFTR_mPR mPr;
	U08 lyr;		// Layer Index

} MnFTR_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern Global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
extern U08 MnFTR_PrGet_SsChn(void);
extern S32 MnFTR_PrGet_Value(U08 iIt);
extern S32 MnFTR_PrGet_CH_Value(U08 ch,U08 iIt);

//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
extern void MnFTR_PrSet_Value(S32 val);
extern void MnFTR_PrRst_Factory(void);
extern void MnFTR_PrSet_CH_Value(U08 ch,S32 val);

//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
extern U08 MnFTR_GetLayer(void);
// Set
extern void MnFTR_SetLayer(U08 lyr);


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern void MnFTR_PrInitMain(void);
extern void MnFTR_InitMain(void);

//------------------------------------------------------------------------------------------------------------------------------
//  RF Module Version (구형 SD-1000 호환)
//------------------------------------------------------------------------------------------------------------------------------
enum {
	MnFTR_RF_VER_NEW = 0,	// c1d-330 신규 RF 포맷
	MnFTR_RF_VER_OLD,		// ENV110 / SD-1000 구형 포맷
	MnFTR_RF_VER_NUM,
};
#define MnFTR_RF_VER_MIN		(MnFTR_RF_VER_NEW)
#define MnFTR_RF_VER_MAX		(MnFTR_RF_VER_OLD)
#define MnFTR_RF_VER_DEF		(MnFTR_RF_VER_NEW)

extern U08 MnFTR_PrGet_RfVersion(void);
extern void MnFTR_PrSet_RfVersion(U08 ver);


#endif // ___MENU_FACTORY_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

