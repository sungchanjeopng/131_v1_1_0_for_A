//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___SCREEN_ECHO_H___
#define ___SCREEN_ECHO_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
// Function Indix - Single
enum {
	ScECO_REAL_CH_SEL = 0,
	ScECO_REAL_ECHO_AMP,
	ScECO_REAL_MEAS_RESET,
	ScECO_REAL_FREQ,
	ScECO_REAL_EMPTY,
	ScECO_REAL_DEADZONE,
	ScECO_REAL_TVG,

	ScECO_REAL_NUM,
};

#define ScECO_REAL_SEL_MIN	(ScECO_REAL_CH_SEL)
#define ScECO_REAL_SEL_MAX	(ScECO_REAL_NUM-1)

enum {
	ScECO_AVG_CH_SEL = 0,
	ScECO_AVG_THR_LIGHT,
	ScECO_AVG_THR_HEAVY,
	ScECO_AVG_ASF_LIGHT,
	ScECO_AVG_ASF_HEAVY,

	ScECO_AVG_NUM,
};

#define ScECO_AVG_SEL_MIN	(ScECO_AVG_CH_SEL)
#define ScECO_AVG_SEL_MAX	(ScECO_AVG_NUM-1)


#define ScECO_SEL_NUM		(ScECO_AVG_NUM)

enum {
	ScECO_TYPE_REAL = 0,
	ScECO_TYPE_AVG,

	ScECO_TYPE_NUM,
};

#define ScECO_FNC_PAGE			(5)


enum {
	ScECO_SAVE_OFF = 0,
	ScECO_SAVE_ON,

	ScECO_SAVE_NUM,
};


#if 0
enum {
	// Page 0
	ScECO_F00_THRSHD = 0,		// Threshold: 0~99
	ScECO_F01_ASF_VL,			// Abnormal Signal Filter
	ScECO_F02_TR_WID,			// Detection Width
	ScECO_F03_PROF_N,			// Profile Numb
	ScECO_F04_DAMP_N,			// Damping Numb
	// Page 1
	ScECO_F05_OFFSET,			// Offset
	ScECO_F06_CALIB,			// Calibration
	// Screen_Type
	ScECO_H00_SCREEN_TYPE,
	// Number Max (Dual)
	ScECO_FNC_NUM,				// If SsChn = Dual, Using Ch #
};

// Page
#define ScECO_FNC_PAGE			(5)

// Threshold
enum {
	ScECO_THRHD_MIN = 1,
	ScECO_THRHD_DFT = 50,
	ScECO_THRHD_MAX = 100,
};

// ASF (Abnormal Signal Filter)
enum {
	ScECO_ASF_V_MIN = 0,
	ScECO_ASF_V_DFT = 0,
	ScECO_ASF_V_MAX = 99,
};

// Tracking Width (Series 1: Time Window)
enum {
	ScECO_T_WID_MIN = 0,
	ScECO_T_WID_DFT = 20,
	ScECO_T_WID_MAX = 100,
};

#define ScECO_PROF_MIN			(1)
#define ScECO_PROF_DFT			(30)
#define ScECO_PROF_MAX			(60)

// Damping Numb.
enum {
	ScECO_DAMP_001 = 0,
	ScECO_DAMP_010,
	ScECO_DAMP_030,
	ScECO_DAMP_060,
	// Number Max
	ScECO_DAMP_NUM,
};
#define ScECO_DAMP_MIN			(1)
#define ScECO_DAMP_DFT			(ScECO_DAMP_001)
#define ScECO_DAMP_MAX			(60)

// Offset
enum {
	ScECO_OFFS_MIN = -99,
	ScECO_OFFS_DFT = 0,
	ScECO_OFFS_MAX = 99,
};

// Real / Avg
enum {
	ScECO_SCREEN_AVG = 0,
	ScECO_SCREEN_REAL,
	// Number Max
	ScECO_SCREEN_NUM,
};	
#define ScECO_SCREEN_DFT (ScECO_SCREEN_AVG)

// Measurement Channel
enum {
	ScECO_CH_0 = 0,
	ScECO_CH_1,
	// Number Max
	ScECO_CH_NUM
};
#endif

//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Memory Parameter
typedef struct {
	// Page #0
#if 0
	U16 thrhd[ScECO_CH_NUM];		// Threshold
	U16 asf_v[ScECO_CH_NUM];		// Abnormal Signal Filter
	U16 d_wid[ScECO_CH_NUM];		// Detection Width (Old: Time Window)
	U16 profn[ScECO_CH_NUM];		// Profile Number
	U16 dampn[ScECO_CH_NUM];		// Damping Number
	// Page #1
	#if 1
	S16 offst[ScECO_CH_NUM];		// Damping Number

	U08 screen_type;	
	#else
	S32 offst[ScECO_CH_NUM];		// Damping Number
	#endif
#endif

	// Dual Sensor
	U08 chnnl;						// Ch1 / ch2

} ScECO_mPR;

// Local Struct
typedef struct {
	ScECO_mPR mPr;			// Memory - Parameter
	U08 lyr;				// Layer
	U08 type;
	U08 save;
} ScECO_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters
//------------------------------------------------------------------------------------------------------------------------------
// Get
extern U08 ScECH_PrGet_Chnnl(void);
extern S32 ScECH_PrGet_Value(U08 iCh, U08 iFn);
extern U08 ScECH_GetType(void);
extern U08 ScECH_GetSave(void);
// Set / Reset
extern void ScECH_PrSet_Value(S32 val);
extern void ScECH_PrRst_Factory(void);
extern void ScECH_SetType(U08 sel);
extern void ScECH_SetSave(U08 sel);
extern void ScECH_PrSet_Chnnl(U08 ch);
//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Vairables - Basic
//------------------------------------------------------------------------------------------------------------------------------
// Get
extern U08 ScECH_GetLayer(void);
// Set
extern void ScECH_SetLayer(U08 lyr);


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic Operation
//------------------------------------------------------------------------------------------------------------------------------
extern void ScECH_PrInitMain(void);
extern void ScECH_InitMain(void);
extern void ScECH_ProcMain(void);



#endif // ___SCREEN_ECHO_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

