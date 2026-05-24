//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___screen_hybrid_H___
#define ___screen_hybrid_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
// Function - Indix
#if 0
enum {
	ScHYB_F00_LEVEL = 0,	// Level: Sludge / Distance
	ScHYB_F01_UNIT_,		// Unit: meter / feet
	ScHYB_F02_S_DEP,		// Sensor Depth
	ScHYB_F03_DEADZ,		// Deadzone
	ScHYB_F04_T_DEP,		// Tank Depth
	// Number Max
	ScHYB_FNC_NUMB			// If SsChn = Dual, Using Ch #
};

// Measurement Level
enum {
	ScHYB_LVL_SLDG = 0,		// Sludge
	ScHYB_LVL_DIST,			// Distance
	// Number Max
	ScHYB_LVL_NUMB
};
#define ScHYB_LVL_MIN		(ScHYB_LVL_SLDG)
#define ScHYB_LVL_DEF		(ScHYB_LVL_SLDG)
#define ScHYB_LVL_MAX		(ScHYB_LVL_NUMB-1)

// Measurement Channel
enum {
	ScHYB_CH_0 = 0,
	ScHYB_CH_1,
	// Number Max
	ScHYB_CH_NUMB
};

// Measurement Unit
enum {
	ScHYB_UNIT_METER = 0,
	ScHYB_UNIT_FEET,
	// Number Max
	ScHYB_UNIT_NUMB
};
#define ScHYB_UNIT_MIN		(ScHYB_UNIT_METER)
#define ScHYB_UNIT_DEF		(ScHYB_UNIT_METER)
#define ScHYB_UNIT_MAX		(ScHYB_UNIT_NUMB-1)

// Sensor Depth
#define ScHYB_SS_DEP_MIN		(1)
#define ScHYB_SS_DEP_DEF		(20)
#define ScHYB_SS_DEP_MAX		(50)

// Sensor DeadZone
#define ScHYB_DEADZ_MIN			(10)
#define ScHYB_DEADZ_DEF			(50)
#define ScHYB_DEADZ_MAX			(300)

// Tank Depth
#define ScHYB_TK_DEP_MIN		(100)
#define ScHYB_TK_DEP_DEF		(500)
#define ScHYB_TK_DEP_MAX		(1020)

// Error
#define ScHYB_PRM_INVALID		(0xffffffff)
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
	U16 sen_d[ScHYB_CH_NUMB];		// Sensor Depth
	U16 deadz[ScHYB_CH_NUMB];		// Sensor DeadZone
	U16 t_dep[ScHYB_CH_NUMB];		// Tank Depth
#endif
} ScHYB_mPR;

// Local Struct
typedef struct {
	ScHYB_mPR mPr;			// Memory - Parameter

	U08 lyr;				// Layer

} ScHYB_LS;


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
extern U08 ScHYB_PrGet_LvTyp(void);
extern U08 ScHYB_PrGet_Unit_(void);
extern U08 ScHYB_PrGet_Chnnl(void);
extern S32 ScHYB_PrGet_Value(U08 ch, U08 fnc);
// Set / Reset
extern void ScHYB_PrSet_Value(U08 iFn, S32 val);
extern void ScHYB_PrRst_Factory(void);


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Vairables - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern void ScHYB_SetLayer(U08 lyr);


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic Operation
//------------------------------------------------------------------------------------------------------------------------------
extern void ScHYB_PrInitMain(void);
extern void ScHYB_InitMain(void);
extern void ScHYB_ProcMain(void);



#endif // ___SCREEN_HYONT_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

