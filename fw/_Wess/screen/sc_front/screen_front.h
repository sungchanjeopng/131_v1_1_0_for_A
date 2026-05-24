//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___SCREEN_FRONT_H___
#define ___SCREEN_FRONT_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
#if 0
// Function - Indix
enum {
	ScFRT_F00_CH = 0,
	// Number Max
	ScFRT_FNC_NUMB			// If SsChn = Dual, Using Ch #
};

// Measurement Level
enum {
	ScFRT_LVL_SLDG = 0,		// Sludge
	ScFRT_LVL_DIST,			// Distance
	// Number Max
	ScFRT_LVL_NUMB
};
#define ScFRT_LVL_MIN		(ScFRT_LVL_SLDG)
#define ScFRT_LVL_DEF		(ScFRT_LVL_SLDG)
#define ScFRT_LVL_MAX		(ScFRT_LVL_NUMB-1)

// Measurement Channel
enum {
	ScFRT_CH_0 = 0,
	ScFRT_CH_1,
	// Number Max
	ScFRT_CH_NUMB
};

// Measurement Unit
enum {
	ScFRT_UNIT_METER = 0,
	ScFRT_UNIT_FEET,
	// Number Max
	ScFRT_UNIT_NUMB
};
#define ScFRT_UNIT_MIN		(ScFRT_UNIT_METER)
#define ScFRT_UNIT_DEF		(ScFRT_UNIT_METER)
#define ScFRT_UNIT_MAX		(ScFRT_UNIT_NUMB-1)

// Sensor Depth
#define ScFRT_SS_DEP_MIN		(1)
#define ScFRT_SS_DEP_DEF		(20)
#define ScFRT_SS_DEP_MAX		(50)

// Sensor DeadZone
#define ScFRT_DEADZ_MIN			(10)
#define ScFRT_DEADZ_DEF			(50)
#define ScFRT_DEADZ_MAX			(300)

// Tank Depth
#define ScFRT_TK_DEP_MIN		(100)
#define ScFRT_TK_DEP_DEF		(500)
#define ScFRT_TK_DEP_MAX		(1020)

// Error
#define ScFRT_PRM_INVALID		(0xffffffff)
#endif

//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Memory Parameter
typedef struct {
#if 0
	U08 level;						// Distance / Sludge
	U08 chnnl;						// ch1 / ch2
	U08 unit_;						// Meter / Peet
	U16 sen_d[ScFRT_CH_NUMB];		// Sensor Depth
	U16 deadz[ScFRT_CH_NUMB];		// Sensor DeadZone
	U16 t_dep[ScFRT_CH_NUMB];		// Tank Depth
#endif
} ScFRT_mPR;

// Local Struct
typedef struct {
	ScFRT_mPR mPr;			// Memory - Parameter

	U08 lyr;				// Layer
} ScFRT_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters
//------------------------------------------------------------------------------------------------------------------------------
// Get
extern U08 ScFRT_PrGet_LvTyp(void);
extern U08 ScFRT_PrGet_Unit_(void);
extern S32 ScFRT_PrGet_Value(U08 ch, U08 fnc);
// Set / Reset
extern void ScFRT_PrSet_Value(S32 val);
extern void ScFRT_PrRst_Factory(void);


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Vairables - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern U08 ScFRT_GetLayer(void);
extern void ScFRT_SetLayer(U08 lyr);


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic Operation
//------------------------------------------------------------------------------------------------------------------------------
extern void ScFRT_InitMain(void);
extern void ScFRT_ProcMain(void);



#endif // ___SCREEN_FRONT_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

