//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___MENU_OUTPUT_H___
#define ___MENU_OUTPUT_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
#if 0
// Sub-Section List
enum {
	MnOUT_S00_CURRENT = 0,
	MnOUT_S01_RELAY,
	MnOUT_S02_PCD,
	MnOUT_S03_ERROR,
	// Number Max
	MnOUT_SCT_NUM,
};
#define MnOUT_SCT_I00			(MnOUT_S00_CURRENT)
#endif

// Sub-Section List
enum {
	MnOUT_SUB_CURRENT = 0,
	MnOUT_SUB_RELAY,
	MnOUT_SUB_CLEAN,
	MnOUT_SUB_ERROR,
	MnOUT_SUB_EXT_INPUT,
	// Number Max
	MnOUT_SUB_NUM,
};

#define MnOUT_SUB_MIN			(MnOUT_SUB_CURRENT)
#define MnOUT_SUB_MAX			(MnOUT_SUB_NUM-1)

enum {
	// Page #1
	MnOS0_OPT_CH1_ASSIGN   = 0,		// Assign    (Value)
	MnOS0_OPT_CH1_SET_04mA,			// Set 4mA   (Measurement Level)
	MnOS0_OPT_CH1_SET_20mA,			// Set 20mA  (Measurement Level)
	MnOS0_OPT_CH1_TRM_12mA,			// Trim 12mA  (DAC Value)
	MnOS0_OPT_CH1_TRM_20mA,			// Trim 20mA (DAC Value)
	MnOS0_OPT_CH1_OUT_04mA,
	// Page #2
	MnOS0_OPT_CH2_ASSIGN,
	MnOS0_OPT_CH2_SET_04mA,
	MnOS0_OPT_CH2_SET_20mA,
	MnOS0_OPT_CH2_TRM_12mA,			// Trim 12mA  (DAC Value)
	MnOS0_OPT_CH2_TRM_20mA,			// Trim 20mA (DAC Value)	
	MnOS0_OPT_CH2_OUT_04mA,
	// Number Max
	MnOS0_OPT_NUM,
};

enum {
	// Page #1
	MnOS0_OPT_SINGLE_ASSIGN   = 0,		// Assign    (Value)
	MnOS0_OPT_SINGLE_SET_04mA,			// Set 4mA   (Measurement Level)
	MnOS0_OPT_SINGLE_SET_20mA,			// Set 20mA  (Measurement Level)
	MnOS0_OPT_SINGLE_TRM_12mA,			// Trim 12mA  (DAC Value)
	MnOS0_OPT_SINGLE_TRM_20mA,			// Trim 20mA (DAC Value)
	MnOS0_OPT_SINGLE_OUT_04mA,

	// Number Max
	MnOS0_OPT_SINGLE_NUM,
};

#define MnOS0_OPT_SINGLE_MIN	(MnOS0_OPT_SINGLE_ASSIGN)
#define MnOS0_OPT_SINGLE_MAX	(MnOS0_OPT_SINGLE_NUM-1)


#define MnOS0_OPT_MIN	(MnOS0_OPT_CH1_ASSIGN)
#define MnOS0_OPT_MAX	(MnOS0_OPT_NUM-1)

// Assign Value
enum {
	MnOS0_ASSIGN_LIGHT = 0,
	MnOS0_ASSIGN_HEAVY,

	MnOS0_ASSIGN_NUM,
};

#define MnOS0_ASSIGN_MIN	(MnOS0_ASSIGN_LIGHT)
#define MnOS0_ASSIGN_MAX	(MnOS0_ASSIGN_NUM-1)
#define MnOS0_ASSGIN_DEF	(MnOS0_ASSIGN_HEAVY)

#define MnOS0_SET_MA_MIN	(0)
#define MnOS0_SET_MA_MAX	(1000)
#define MnOS0_SET_4MA_DEF	(0)
#define MnOS0_SET_20MA_DEF	(500)

#define MnOS0_TRIM_MIN	(-100)
#define MnOS0_TRIM_MAX	(100)
#define MnOS0_TRIM_DEF	(0)

enum {
	MnOUT_RLY_0 = 0,
	MnOUT_RLY_1,
	MnOUT_RLY_2,
	MnOUT_RLY_3,
	// Number Max
	MnOUT_RLY_NUM,
};

enum {
	MnOS1_RLY_ITEM_ASSIGN = 0,
	MnOS1_RLY_ITEM_ACT,
	MnOS1_RLY_ITEM_STOP,
	// Number Max
	MnOS1_RLY_ITEM_NUM,
};

enum {
	MnOS1_OPT_R1_ASSIGN = 0,
	MnOS1_OPT_R1_ACT,
	MnOS1_OPT_R1_STOP,
	MnOS1_OPT_R2_ASSIGN,
	MnOS1_OPT_R2_ACT,
	MnOS1_OPT_R2_STOP,
	MnOS1_OPT_R3_ASSIGN,
	MnOS1_OPT_R3_ACT,
	MnOS1_OPT_R3_STOP,
	MnOS1_OPT_R4_ASSIGN,
	MnOS1_OPT_R4_ACT,
	MnOS1_OPT_R4_STOP,
	MnOS1_OPT_TEST,

	MnOS1_OPT_NUM,
};

#define MnOS1_OPT_RLY_IDX(_it)		((U08)((_it) / MnOS1_RLY_ITEM_NUM))
#define MnOS1_OPT_RLY_ITEM(_it)		((U08)((_it) % MnOS1_RLY_ITEM_NUM))
#define MnOS1_OPT_RLY_ASSIGN(_rly)	((U08)(((_rly) * MnOS1_RLY_ITEM_NUM) + MnOS1_RLY_ITEM_ASSIGN))
#define MnOS1_OPT_RLY_ACT(_rly)		((U08)(((_rly) * MnOS1_RLY_ITEM_NUM) + MnOS1_RLY_ITEM_ACT))
#define MnOS1_OPT_RLY_STOP(_rly)		((U08)(((_rly) * MnOS1_RLY_ITEM_NUM) + MnOS1_RLY_ITEM_STOP))

#define MnOS1_OPT_ASSIGN	(MnOS1_OPT_R1_ASSIGN)
#define MnOS1_OPT_ACT		(MnOS1_OPT_R1_ACT)
#define MnOS1_OPT_STOP		(MnOS1_OPT_R1_STOP)

#define MnOS1_OPT_MIN (MnOS1_OPT_ASSIGN)
#define MnOS1_OPT_MAX (MnOS1_OPT_NUM-1)

// Value - Relay Item #0 (Assign)
enum {
	MnOS1_ASSIGN_CH1_LIGHT = 0,
	MnOS1_ASSIGN_CH1_HEAVY,
	MnOS1_ASSIGN_CH2_LIGHT,
	MnOS1_ASSIGN_CH2_HEAVY,
	// Number Max
	MnOS1_ASSIGN_NUM,
};
#define MnOS1_ASSIGN_MIN			(MnOS1_ASSIGN_CH1_LIGHT)
#define MnOS1_ASSIGN_MAX			(MnOS1_ASSIGN_NUM-1)
#define MnOS1_ASSIGN_DEF			(MnOS1_ASSIGN_CH1_HEAVY)

// Value - Relay Item #1 (Act)
#define MnOS1_ACT_MIN			(0)
#define MnOS1_ACT_MAX			(1000)
#define MnOS1_ACT_DEF			(900)
// Value - Relay Item #2 (Stop)
#define MnOS1_STOP_MIN			(0)
#define MnOS1_STOP_MAX			(1000)
#define MnOS1_STOP_DEF			(800)	// 10m
// Value - Factory Relay Test
#define MnOS1_TEST_MIN			(0)
#define MnOS1_TEST_MAX			(1000)
#define MnOS1_TEST_DEF			(0)

enum {
	MnOS2_OPT_MODE=0,
	MnOS2_OPT_INTV,			// Clean Interval Time
	MnOS2_OPT_TERM,			// Clean Operation Time
	// Number Max
	MnOS2_OPT_NUM,
};
	
#define MnOS2_OPT_MIN			(MnOS2_OPT_INTV)
#define MnOS2_OPT_MAX			(MnOS2_OPT_NUM-1)

#define MnOS2_MODE_MIN			(0)
#define MnOS2_MODE_MAX			(2)
#define MnOS2_MODE_DEF			(0)

// Value - PCD Item #1 (Clean Interval Time - Sec.)
#define MnOS2_INTV_MIN			(1)
#define MnOS2_INTV_MAX			(6000)
#define MnOS2_INTV_DEF			(60)
// Value - PCD Item #2 (Clean Operation Time - Sec.)
#define MnOS2_TERM_MIN			(1)
#define MnOS2_TERM_MAX			(100)
#define MnOS2_TERM_DEF			(3)

// Item List - Sub-Section #3 (Error)
enum {
	MnOS3_OPT_ERR_DELAY = 0,
	MnOS3_OPT_ERR_OUTP,			// Error Output Type (Fail-Safe Hold Time)
	// Number Max
	MnOS3_OPT_NUM,
};
	
#define MnOS3_OPT_MIN			(MnOS3_OPT_ERR_DELAY)
#define MnOS3_OPT_MAX			(MnOS3_OPT_NUM-1)

#define MnOS3_ERR_DELAY_MIN		(20)
#define MnOS3_ERR_DELAY_MAX		(999)
#define MnOS3_ERR_DELAY_DEF		(120)

// Value - Error Item #1 (Output Type)
enum {
	MnOS3_ERR_OUTPUT_HOLD = 0,
	MnOS3_ERR_OUTPUT_38mA,
	MnOS3_ERR_OUTPUT_21mA,
	// Number Max
	MnOS3_ERR_OUTPUT_NUM,
};
#define MnOS3_ERR_OUTPUT_MIN			(MnOS3_ERR_OUTPUT_HOLD)
#define MnOS3_ERR_OUTPUT_MAX			(MnOS3_ERR_OUTPUT_NUM-1)
#define MnOS3_ERR_OUTPUT_DEF			(MnOS3_ERR_OUTPUT_HOLD)

// Item List - Sub-Section #4 (External Input)
enum {
	MnOS4_OPT_EXT1 = 0,
	MnOS4_OPT_EXT2,
	MnOS4_OPT_EXT1_TARGET,
	MnOS4_OPT_EXT2_TARGET,
	// Number Max
	MnOS4_OPT_NUM,
};

#define MnOS4_OPT_MIN			(MnOS4_OPT_EXT1)
#define MnOS4_OPT_MAX			(MnOS4_OPT_NUM-1)
#define MnOS4_OPT_MENU_NUM		(MnOS4_OPT_EXT2+1)

enum {
	MnOS4_EXT_INPUT_1 = 0,
	MnOS4_EXT_INPUT_2,
	// Number Max
	MnOS4_EXT_INPUT_NUM,
};

enum {
	MnOS4_ENABLE_OFF = 0,
	MnOS4_ENABLE_ON,
	// Number Max
	MnOS4_ENABLE_NUM,
};

#define MnOS4_ENABLE_MIN		(MnOS4_ENABLE_OFF)
#define MnOS4_ENABLE_MAX		(MnOS4_ENABLE_NUM-1)
#define MnOS4_ENABLE_DEF		(MnOS4_ENABLE_OFF)

enum {
	MnOS4_TARGET_CH1 = 0,
	MnOS4_TARGET_CH2,
	// Number Max
	MnOS4_TARGET_NUM,
};

#define MnOS4_TARGET_MIN		(MnOS4_TARGET_CH1)
#define MnOS4_TARGET_MAX		(MnOS4_TARGET_NUM-1)
#define MnOS4_TARGET_DEF		(MnOS4_TARGET_CH1)

enum {
	MnOS4_VALUE_OFF = 0,
	MnOS4_VALUE_ON,
	// Number Max
	MnOS4_VALUE_NUM,
};

#define MnOS4_VALUE_MIN		(MnOS4_VALUE_OFF)
#define MnOS4_VALUE_MAX		(MnOS4_VALUE_NUM-1)
#define MnOS4_VALUE_DEF		(MnOS4_VALUE_OFF)

#if 0

// Item List - Sub-Section #1 (Relay)
enum {
	MnOS1_I00_ASSIGN = 0,	
	MnOS1_I01_ACT ,
	MnOS1_I02_STOP,
	MnOS1_I03_TEST,
	// Number Max
	MnOS1_ITM_NUM,
};
#define MnOS1_ITM_I00			(MnOS1_I00_ASSIGN)
// Value - Relay Item #0 (Assign)
enum {
	MnOS1_IV0_CH_0 = 0,
	MnOS1_IV0_CH_1,
	MnOS1_IV0_DIFF,
	MnOS1_IV0_AVRG,
	// Number Max
	MnOS1_IV0_VAL_NUM,
};
#define MnOS1_IV0_MIN			(MnOS1_IV0_CH_0)
#define MnOS1_IV0_MAX			(MnOS1_IV0_VAL_NUM-1)
#define MnOS1_IV0_DEF			(MnOS1_IV0_CH_0)
// Value - Relay Item #1 (Act)
#define MnOS1_IV1_MIN			(0)
#define MnOS1_IV1_MAX			(1000)
#define MnOS1_IV1_DEF			(900)
// Value - Relay Item #2 (Stop)
#define MnOS1_IV2_MIN			(0)
#define MnOS1_IV2_MAX			(1000)
#define MnOS1_IV2_DEF			(800)	// 10m
// Value - Relay Item #3 (Test)
#define MnOS1_IV3_MIN			(0)
#define MnOS1_IV3_MAX			(1000)
#define MnOS1_IV3_DEF			(0)	// 10m

// Item List - Sub-Section #2 (PCD)
enum {
	MnOS2_I00_fEN = 0,			// Enable
	MnOS2_I01_CLN_INTV,			// Clean Interval Time
	MnOS2_I02_CLN_OPER,			// Clean Operation Time
	// Number Max
	MnOS2_ITM_NUM,
};
#define MnOS2_ITM_I00			(MnOS2_I00_fEN)
// Value - PCD Item #0 (Enable)
enum {
	MnOS2_IV0_OFF = 0,
	MnOS2_IV0_ON,
	// Number Max
	MnOS2_IV0_VAL_NUM,
};
#define MnOS2_IV0_MIN			(MnOS2_IV0_OFF)
#define MnOS2_IV0_MAX			(MnOS2_IV0_VAL_NUM-1)
#define MnOS2_IV0_DEF			(MnOS2_IV0_ON)
// Value - PCD Item #1 (Clean Interval Time - Sec.)
#define MnOS2_IV1_MIN			(0)
#define MnOS2_IV1_MAX			(6000)
#define MnOS2_IV1_DEF			(60)
// Value - PCD Item #2 (Clean Operation Time - Sec.)
#define MnOS2_IV2_MIN			(0)
#define MnOS2_IV2_MAX			(100)
#define MnOS2_IV2_DEF			(3)

// Item List - Sub-Section #3 (Error)
enum {
	MnOS3_I00_ERR_HOLD = 0,			// Error Hold Time (Fail-Safe Hold Time)
	MnOS3_I01_ERR_OUTP,			// Error Output Type (Fail-Safe Hold Time)
	// Number Max
	MnOS3_ITM_NUM,
};
#define MnOS3_ITM_I00			(MnOS3_I00_ERR_HOLD)
// Value - Error Item #0 (Hold Time)
#define MnOS3_IV0_MIN			(20)
#define MnOS3_IV0_MAX			(990)
#define MnOS3_IV0_DEF			(120)
// Value - Error Item #1 (Output Type)
enum {
	MnOS3_IV1_HOLD = 0,
	MnOS3_IV1_38mA,
	MnOS3_IV1_21mA,
	// Number Max
	MnOS3_IV1_VAL_NUM,
};
#define MnOS3_IV1_MIN			(MnOS3_IV1_HOLD)
#define MnOS3_IV1_MAX			(MnOS3_IV1_VAL_NUM-1)
#define MnOS3_IV1_DEF			(MnOS3_IV1_HOLD)

#endif
enum {
	MnOUT_CH_0 = 0,
	MnOUT_CH_1,
	// Number Max
	MnOUT_CH_NUM,
};
//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Memory Parameter
// Parameter - Current Item
typedef struct {
	U08 assign[MnOUT_CH_NUM];		// mA Assign
	U16 set_4ma[MnOUT_CH_NUM];		// Set 4mA   - Measurement Level
	U16 set_20ma[MnOUT_CH_NUM];		// Set 20mA  - Measurement Level
	S08 trm_12ma[MnOUT_CH_NUM];		// Trim 4mA  - DAC Value
	S08 trm_20ma[MnOUT_CH_NUM];		// Trim 20mA - DAC Value
} MnOUT_cur;

// Parameter - Relay Item
typedef struct {
	U08 assign[MnOUT_RLY_NUM];	// Relay Assign
	U16 act[MnOUT_RLY_NUM];		// Relay Act
	U16 stop[MnOUT_RLY_NUM];		// Relay Stop
} MnOUT_rly;

// Parameter - PCD Item
typedef struct {
	U08 mode;
	U16 clr_intv;		// Clean Interval Time
	U16 clr_oper;		// Clean Operation Time
} MnOUT_pcd;

// Parameter - Error Item
typedef struct {
	U16 hold;			// Hold Time (Fail-Safe Hold Time)
	U08 outp;			// Output Type (Fail-Safe Hold Time)
} MnOUT_err;

// Parameter - External Input Item
typedef struct {
	U08 enable[MnOS4_EXT_INPUT_NUM];	// OFF / ON
	U08 target[MnOS4_EXT_INPUT_NUM];	// CH1 / CH2
} MnOUT_ext;

// Parameter - Sub-Section
typedef struct {
	MnOUT_cur mCurPr;
	MnOUT_rly mRlyPr;
	MnOUT_pcd mPcdPr;
	MnOUT_err mErrPr;
	MnOUT_ext mExtPr;
	
	U08 lyr;
} MnOUT_LS;



//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
#if 0
extern S32 MnOUT_PrGet_Value(U08 iSb, U08 iIt);
#endif
extern S32 MnOUT_CurPrGet_Value(U08 iIt);
extern S32 MnOUT_CurPrGet_CH_Value(U08 ch,U08 iIt);
extern S32 MnOUT_RlyPrGet_Value(U08 iIt);
extern S32 MnOUT_PcdPrGet_Value(U08 iIt);
extern S32 MnOUT_ErrPrGet_Value(U08 iIt);
extern S32 MnOUT_ExtPrGet_Value(U08 iIt);
//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
extern void MnOUT_CurPrSet_Value(U08 iIt, S32 val);
extern void MnOUT_RlyPrSet_Value(U08 iIt, S32 val);
extern void MnOUT_PcdPrSet_Value(U08 iIt, S32 val);
extern void MnOUT_ErrPrSet_Value(U08 iIt, S32 val);
extern void MnOUT_ExtPrSet_Value(U08 iIt, S32 val);
extern void MnOUT_CurPrSet_Ch_Value(U08 ch,U08 iIt, S32 val);

extern void MnOUT_PrRst_Factory(void);
#if 0
extern void MnOUT_PrSet_Value(U08 iSb, U08 iIt, S32 val);
#endif


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Varables
//------------------------------------------------------------------------------------------------------------------------------
// Get
extern U08 MnOUT_GetLayer(void);
// Set
extern void MnOUT_SetLayer(U08 lyr);


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern void MnOUT_PrInitMain(void);
extern void MnOUT_InitMain(void);



#endif // ___MENU_OUTPUT_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

