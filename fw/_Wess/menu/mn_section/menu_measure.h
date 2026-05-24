//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___MENU_MEASURE_H___
#define ___MENU_MEASURE_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "measure_calc.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
// Sub-Section List
enum {
	MnMSR_SUB_BASE = 0,		// Base
	MnMSR_SUB_CAL,		// Calibration
	// Number MAX
	MnMSR_SUB_NUM,	
};
#define MnMSR_SUB_MIN (MnMSR_SUB_BASE)
#define MnMSR_SUB_MAX (MnMSR_SUB_NUM-1)

// Base - Option List
enum {
	MnMS0_OPT_UNIT = 0,					// Unit
	MnMS0_OPT_CH1_OPERATION,		// Capture: Method Type
	MnMS0_OPT_CH1_EMPTY,			// Re-filtering Time
	MnMS0_OPT_CH1_DEADZONE,			// Measurement's Parameters - Reset
	MnMS0_OPT_CH1_MEASURE_CYCLE,			// Measure Run Enalble
	MnMS0_OPT_CH1_MEASURE_RESET,			// TEMP RUN Enable
	MnMS0_OPT_CH2_OPERATION,
	MnMS0_OPT_CH2_EMPTY,
	MnMS0_OPT_CH2_DEADZONE,
	MnMS0_OPT_CH2_MEASURE_CYCLE,
	MnMS0_OPT_CH2_MEASURE_RESET,
	// Number Max
	MnMS0_OPT_NUM,
};

enum {
	MnMS0_OPT_SINGLE_UNIT = 0,					// Unit
	MnMS0_OPT_SINGLE_OPERATION,		// Capture: Method Type
	MnMS0_OPT_SINGLE_EMPTY,			// Re-filtering Time
	MnMS0_OPT_SINGLE_DEADZONE,			// Measurement's Parameters - Reset
	MnMS0_OPT_SINGLE_MEASURE_CYCLE,			// Measure Run Enalble
	MnMS0_OPT_SINGLE_MEASURE_RESET,			// TEMP RUN Enable
	// Number Max
	MnMS0_OPT_SINGLE_NUM,
};

#define MnMS0_OPT_MIN			(MnMS0_OPT_UNIT)
#define MnMS0_OPT_MAX			(MnMS0_OPT_NUM-1)

#define MnMS0_OPT_SIGNLE_MIN	(MnMS0_OPT_SINGLE_UNIT)
#define MnMS0_OPT_SINGLE_MAX	(MnMS0_OPT_SINGLE_NUM-1)

// Value Unit
enum {
	MnMS0_UNIT_METER = 0,
	MnMS0_UNIT_PERCENT,

	MnMS0_UNIT_NUM,
};

#define MnMS0_UNIT_MIN		(MnMS0_UNIT_METER)
#define MnMS0_UNIT_MAX		(MnMS0_UNIT_METER)
#define MnMS0_UNIT_DEF		(MnMS0_UNIT_METER)

// Value Operation
enum {
	MnMS0_OPERATION_SLUDGE = 0,
	MnMS0_OPERATION_DISTANCE,

	MnMS0_OPERATION_NUM,
};

#define MnMS0_OPERATION_MIN	(MnMS0_OPERATION_SLUDGE)
#define MnMS0_OPERATION_MAX	(MnMS0_OPERATION_NUM-1)
#define MnMS0_OPERATION_DEF	(MnMS0_OPERATION_SLUDGE)

#define MnMS0_EMPTY_MIN (1)
#define MnMS0_EMPTY_MAX	(1000)
#define MnMS0_EMPTY_DEF (500)

#define MnMS0_DEADZONE_MIN (1)
#define MnMS0_DEADZONE_MAX (1000)
#define MnMS0_DEADZONE_DEF (50)

#define MnMS0_MSR_CYC_MIN  	(1)
#define MnMS0_MSR_CYC_MAX  	(50)
#define MnMS0_MSR_CYC_DEF	(3)

enum {
	MnMS0_MSR_RESET_NO = 0,
	MnMS0_MSR_RESET_YES,

	MnMS0_MSR_RESET_NUM,
};

#define MnMS0_MSR_RESET_MIN	(MnMS0_MSR_RESET_NO)
#define MnMS0_MSR_RESET_MAX	(MnMS0_MSR_RESET_NUM-1)

// Calibration - Option List
enum {
	MnMS1_OPT_CH1_FREQ = 0,
	MnMS1_OPT_CH1_ECHO_AMP,
	MnMS1_OPT_CH1_THR_HEAVY,
	MnMS1_OPT_CH1_THR_LIGHT,
	MnMS1_OPT_CH1_ASF_HEAVY,
	MnMS1_OPT_CH1_ASF_LIGHT,
	MnMS1_OPT_CH1_DAMPING,
	MnMS1_OPT_CH1_OFFSET,
	MnMS1_OPT_CH2_FREQ,
	MnMS1_OPT_CH2_ECHO_AMP,
	MnMS1_OPT_CH2_THR_HEAVY,
	MnMS1_OPT_CH2_THR_LIGHT,
	MnMS1_OPT_CH2_ASF_HEAVY,
	MnMS1_OPT_CH2_ASF_LIGHT,
	MnMS1_OPT_CH2_DAMPING,
	MnMS1_OPT_CH2_OFFSET,

	// Number Max
	MnMS1_OPT_NUM,
};

enum {
	MnMS1_OPT_SINGLE_FREQ = 0,
	MnMS1_OPT_SINGLE_ECHO_AMP,
	MnMS1_OPT_SINGLE_THR_HEAVY,
	MnMS1_OPT_SINGLE_THR_LIGHT,
	MnMS1_OPT_SINGLE_ASF_HEAVY,
	MnMS1_OPT_SINGLE_ASF_LIGHT,
	MnMS1_OPT_SINGLE_DAMPING,
	MnMS1_OPT_SINGLE_OFFSET,

	// Number Max
	MnMS1_OPT_SINGLE_NUM,
};

	
#define MnMS1_OPT_MIN	(MnMS1_OPT_CH1_FREQ)
#define MnMS1_OPT_MAX	(MnMS1_OPT_NUM-1)

#define MnMS1_OPT_SINGLE_MIN	(MnMS1_OPT_SINGLE_FREQ)
#define MnMS1_OPT_SINGLE_MAX	(MnMS1_OPT_SINGLE_NUM-1)

// Value Frequency
enum {
	MnMS1_FREQ_380K = 0,
	MnMS1_FREQ_270K,
	MnMS1_FREQ_160K,
	MnMS1_FREQ_130K,

	MnMS1_FREQ_NUM,
};

#define MnMS1_FREQ_MIN	(MnMS1_FREQ_380K)
#define MnMS1_FREQ_MAX	(MnMS1_FREQ_NUM-1)
#define MnMS1_FREQ_DEF	(MnMS1_FREQ_380K)

#define MnMS1_ECHO_AMP_MIN	(1)
#define MnMS1_ECHO_AMP_MAX	(50)
#define MnMS1_ECHO_AMP_DEF	(15)

enum {
	MnMS1_THRESHOLD_AUTO = 0,
	MnMS1_THRESHOLD_MANUAL,

	MnMS1_THRESHOLD_TYPE_NUM,
};
	
enum {
	MnMS1_OPT_CH1_THR_LIGHT_VAL,
	MnMS1_OPT_CH1_THR_HEAVY_VAL,	
	MnMS1_OPT_CH2_THR_LIGHT_VAL,
	MnMS1_OPT_CH2_THR_HEAVY_VAL,

	MnMS1_OPT_THR_VAL_NUM,
};


#define MnMS1_THRESHOLD_MIN	(MnMS1_THRESHOLD_AUTO)
#define MnMS1_THRESHOLD_MAX	(MnMS1_THRESHOLD_TYPE_NUM-1)
#define MnMS1_THRESHOLD_DEF	(MnMS1_THRESHOLD_AUTO)

#define MnMS1_THR_VAL_MANUAL_MIN (0)
#define MnMS1_THR_VAL_MANUAL_DEF (16)
#define MnMS1_THR_VAL_MANUAL_MAX (32)

#define MnMS1_THR_VAL_AUTO_MIN (0)
#define MnMS1_THR_VAL_AUTO_MAX (95)
#define MnMS1_THR_VAL_AUTO_DEF (50)

#define MnMS1_ASF_MIN	(0)
#define	MnMS1_ASF_MAX	(9999)
#define MnMS1_ASF_DEF	(0)

#define MnMS1_DAMPING_MIN	(1)
#define MnMS1_DAMPING_MAX	(100)
#define MnMS1_DAMPING_DEF	(20)

#define MnMS1_OFFSET_MIN	(-100)
#define MnMS1_OFFSET_MAX	(100)
#define MnMS1_OFFSET_DEF	(0)


#if 0
// Value - Base Item #0  		(Threshold Mode)
enum {
	MnMS0_IV0_AUTO = 0,
	MnMS0_IV0_MANUAL,
	// Number Max
	MnMS0_IV0_VAL_NUM,
};
	
#define MnMS0_IV0_MIN		(MnMS0_IV0_AUTO)
#define MnMS0_IV0_MAX		(MnMS0_IV0_VAL_NUM-1)
#define MnMS0_IV0_DEF		(MnMS0_IV0_AUTO)

// Value - Base Item #1  		(Threshold	Mode)
enum {
	MnMS0_IV1_AUTO = 0,
	MnMS0_IV1_MANUAL,
	// Number Max
	MnMS0_IV1_VAL_NUM,
};
	
#define MnMS0_IV1_MIN		(MnMS0_IV1_AUTO)
#define MnMS0_IV1_MAX		(MnMS0_IV1_VAL_NUM-1)
#define MnMS0_IV1_DEF		(MnMS0_IV1_AUTO)


// Value - Base Item #2  (Re-filtering)

#define MnMS0_IV2_MIN		(0)
#define MnMS0_IV2_DEF		(60)
#define MnMS0_IV2_MAX		(600)

// Value - Base Item #3  (Reset)

enum {
	MnMS0_IV3_NO = 0,
	MnMS0_IV3_YES,
	// Number Max
	MnMS0_IV3_VAL_NUM,
};
	
#define MnMS0_IV3_MIN		(MnMS0_IV3_NO)
#define MnMS0_IV3_MAX		(MnMS0_IV3_VAL_NUM-1)
#define MnMS0_IV3_DEF		(MnMS0_IV3_NO)


// Value - Base Item #4  (Run)

enum {
	MnMS0_IV4_OFF = 0,
	MnMS0_IV4_ON,
	// Number Max
	MnMS0_IV4_VAL_NUM,
};
	
#define MnMS0_IV4_MIN		(MnMS0_IV4_OFF)
#define MnMS0_IV4_MAX		(MnMS0_IV4_VAL_NUM-1)
#define MnMS0_IV4_DEF		(MnMS0_IV4_ON)

enum {
	MnMS0_IV5_OFF = 0,
	MnMS0_IV5_ON,
	// Number Max
	MnMS0_IV5_VAL_NUM,
};
#define MnMS0_IV5_MIN		(MnMS0_IV5_OFF)
#define MnMS0_IV5_MAX		(MnMS0_IV5_VAL_NUM-1)
#define MnMS0_IV5_DEF		(MnMS0_IV5_ON)




#if 1
// Flag Run
enum {
	MnMSR_fEN_OFF = 0,
	MnMSR_fEN_ON,
	// Number Max
	MnMSR_fEN_NUM,
};

#endif

#endif


//TBD 
#define MnMSI_I07_VEL_UNIT 		(2) 




// Value - FieldA Item #7  (Velocity Unit)
enum {
	MnMS1_IV7_m_sec = 0,
	MnMS1_IV7_m_min,
	MnMS1_IV7_m_hour,
	MnMS1_IV7_km_min,
	MnMS1_IV7_km_hour,
	// Number Max
	MnMS1_IV7_VAL_NUM,
};

enum {
	MnMSR_CH_0 = 0,
	MnMSR_CH_1,
	// Number Max
	MnMSR_CH_NUM,
};
//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Memory Parameter
typedef struct {
	U16 thr_mod[MnMSR_CH_NUM];	// Threshold Mode
	U16 cpt_mtd;				// Capture Method
	U16 re_ftr;					// Re-filtering Time
	U08 fRun;					// Flg: Measure Run
	U08 fTemp;					// Temp Enalbe

	U08 unit;
	U08 operation[MnMSR_CH_NUM];
	U16 empty[MnMSR_CH_NUM];
	U16 deadzone[MnMSR_CH_NUM];
	U08 measure_cycle[MnMSR_CH_NUM];
} MnMSR_base;
#if 0
typedef struct {
#if 0
	U08 fRun;					// FieldA Run
	U16 jdg_height_in;			// Judge Height IN
	U16 jdg_height_out;			// Judge Height OUT
	U16 jdg_time;				// Judge Time
	U16 next_wait_time;			// Next Wait Time
	U16 sen_dis;				// Sensor Distance
	U08 jdg_cyc;
#endif																																																																										`
} MnMSR_FidA;
#endif

typedef struct {
	U08 freq[MnMSR_CH_NUM];
	U08 echo_amp[MnMSR_CH_NUM];
	U08 thr_light_mod[MnMSR_CH_NUM];
	U08 thr_heavy_mod[MnMSR_CH_NUM];
	U16 asf[MnMSR_CH_NUM][MsCAL_THR_TYPE_NUM];
	U16 damp[MnMSR_CH_NUM];
	S16 offset[MnMSR_CH_NUM];
	U16 thr_val[MnMSR_CH_NUM][MsCAL_THR_TYPE_NUM];
} MnMSR_Cal;


// Local Struct
typedef struct {
	MnMSR_base mBasePr;
	MnMSR_Cal  mCalPr;
	U08 lyr;					// Layer Index

} MnMSR_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern Global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
extern S32 MnMSR_BaseGet_Value(U08 iIt);
extern S32 MnMSR_BaseGet_Ch_Value(U08 ch,U08 iIt);
extern S32 MnMSR_CalGet_Value(U08 iIt);
extern S32 MnMSR_CalGet_Ch_Value(U08 ch,U08 iIt);
extern S32 MnMSR_Get_Threshold_Value(U08 sel);
extern S32 MnMSR_Get_Threshold_Ch_Value(U08 ch, U08 sel);
//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
extern void MnMSR_PrRst_Factory(void);
extern void MnMSR_BaseSet_Value(U08 iIt,S32 val);
extern void MnMSR_BaseSet_Ch_Value(U08 ch,U08 iIt,S32 val);
extern void MnMSR_CalSet_Value(U08 iIt, S32 val);
extern void MnMSR_Set_Threshold_Value(U08 sel, S32 val);
extern void MnMSR_CalSet_Ch_Value(U08 ch, U08 iIt, S32 val);
extern void MnMSR_Set_Threshold_Ch_Value(U08 ch,U08 sel, S32 val);
//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Varables
//------------------------------------------------------------------------------------------------------------------------------
// Get
extern U08 MnMSR_GetLayer(void);
// Set
extern void MnMSR_SetLayer(U08 lyr);


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern void MnMSR_PrInitMain(void);
extern void MnMSR_InitMain(void);



#endif // ___MENU_MEASURE_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

