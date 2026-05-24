//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2022-01-20 12:00:00 +0900 $ (From 2020-07-13)
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___MENU_TEST_H___
#define ___MENU_TEST_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "app_main.h"
#include "measure_calc.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
enum {
	MnTST_OPT_HW_RX_AMP = 0,
	MnTST_OPT_CH1_SMOOTH_NO,
	MnTST_OPT_CH1_SMOOTH_RANGE,
	MnTST_OPT_CH1_THR_RANGE,
	MnTST_OPT_CH1_THR_MIN,
	MnTST_OPT_CH1_PULSE_NO,
	MnTST_OPT_CH1_ECHO_AMP_B,
	MnTST_OPT_CH2_SMOOTH_NO,
	MnTST_OPT_CH2_SMOOTH_RANGE,
	MnTST_OPT_CH2_THR_RANGE,
	MnTST_OPT_CH2_THR_MIN,
	MnTST_OPT_CH2_PULSE_NO,
	MnTST_OPT_CH2_ECHO_AMP_B,
	MnTST_OPT_FILTER_RANGE,
	MnTST_OPT_FILTER_TIME,
	MnTST_OPT_SENSOR_DISTANCE,
	MnTST_OPT_DEMO_MODE,
	MnTST_OPT_DEBUG_MODE,
#if 1
	MnTST_OPT_CH1_HEAVY_HOLD,
	MnTST_OPT_CH1_LIGHT_HOLD,
	MnTST_OPT_CH2_HEAVY_HOLD,
	MnTST_OPT_CH2_LIGHT_HOLD,
#endif
	MnTST_OPT_NUM,
};

#define MnTST_OPT_MIN	(MnTST_OPT_HW_RX_AMP)
#define MnTST_OPT_MAX	(MnTST_OPT_NUM-1)


enum {
	MnTST_OPT_SINGLE_HW_RX_AMP = 0,
	MnTST_OPT_SINGLE_SMOOTH_NO,
	MnTST_OPT_SINGLE_SMOOTH_RANGE,
	MnTST_OPT_SINGLE_THR_RANGE,
	MnTST_OPT_SINGLE_THR_MIN,
	MnTST_OPT_SINGLE_PULSE_NO,
	MnTST_OPT_SINGLE_ECHO_AMP_B,
	MnTST_OPT_SINGLE_FILTER_RANGE,
	MnTST_OPT_SINGLE_FILTER_TIME,
	MnTST_OPT_SINGLE_SENSOR_DISTANCE,
	MnTST_OPT_SINGLE_NEXT_WAIT_TIME,
	MnTST_OPT_SINGLE_DEMO_MODE,
	MnTST_OPT_SINGLE_DEBUG_MODE,
	MnTST_OPT_SINGLE_HEAVY_HOLD,
	MnTST_OPT_SINGLE_LIGHT_HOLD,

	MnTST_OPT_SINGLE_NUM,
};

#define MnTST_OPT_SINGLE_MIN	(MnTST_OPT_SINGLE_HW_RX_AMP)
#define MnTST_OPT_SINGLE_MAX	(MnTST_OPT_SINGLE_NUM-1)



enum {
	MnTST_HW_RX_AMP_47=0,
	MnTST_HW_RX_AMP_100,

	MnTST_HW_RX_AMP_NUN,
};

#define MnTST_HW_RX_AMP_MIN	(MnTST_HW_RX_AMP_47)
#define MnTST_HW_RX_AMP_MAX	(MnTST_HW_RX_AMP_NUN-1)
#define MnTST_HW_RX_AMP_DEF	(MnTST_HW_RX_AMP_100)

#define MnTST_SMOOTH_NO_MIN	(0)
#define MnTST_SMOOTH_NO_MAX	(5)
#define MnTST_SMOOTH_NO_DEF	(2)

#define MnTST_SMOOTH_RANGE_MIN	(0)
#define MnTST_SMOOTH_RANGE_MAX	(10)
#define MnTST_SMOOTH_RANGE_DEF	(5)

#define MnTST_THR_RANGE_MIN		(1)
#define MnTST_THR_RANGE_MAX		(300)
#define MnTST_THR_RANGE_DEF		(100)

#define MnTST_THR_MIN_MIN		(0)
#define MnTST_THR_MIN_MAX		(33)
#define MnTST_THR_MIN_DEF		(12)

#define MnTST_PULSE_NO_MIN		(10)
#define MnTST_PULSE_NO_MAX		(100)
#define MnTST_PULSE_NO_DEF		(60)

#define MnTST_ECHO_AMP_B_MIN	(0)
#define MnTST_ECHO_AMP_B_MAX	(1000)
#define MnTST_ECHO_AMP_B_DEF	(0)

#define MnTST_FILTER_RANGE_MIN	(1)
#define MnTST_FILTER_RANGE_MAX	(1000)
#define MnTST_FILTER_RANGE_DEF	(15)

#define MnTST_JUDGE_HEIGHT_OUT_MIN	(1)
#define MnTST_JUDGE_HEIGHT_OUT_MAX	(1000)
#define MnTST_JUDGE_HEIGHT_OUT_DEF	(15)

#define MnTST_FILTER_TIME_MIN	(0)
#define MnTST_FILTER_TIME_MAX	(6000)
#define MnTST_FILTER_TIME_DEF	(600)

#define MnTST_SENSOR_DISTANCE_MIN	(10)
#define MnTST_SENSOR_DISTANCE_MAX	(9999)
#define MnTST_SENSOR_DISTANCE_DEF	(100)

#define MnTST_NEXT_WAIT_TIME_MIN	(1)
#define MnTST_NEXT_WAIT_TIME_MAX	(9999)
#define MnTST_NEXT_WAIT_TIME_DEF	(600)




#define MnTST_DEMO_MODE_MIN	(0)
#define MnTST_DEMO_MODE_MAX	(1)
#define MnTST_DEMO_MODE_DEF	(0)

enum {
	MnTST_DEBUG_MODE_OFF = 0,
	MnTST_DEBUG_MODE_ON,

	MnTST_DEBUG_MODE_NUM,
};

#define MnTST_DEBUG_MODE_MIN	(MnTST_DEBUG_MODE_OFF)
#define MnTST_DEBUG_MODE_MAX	(MnTST_DEBUG_MODE_NUM-1)
#define MnTST_DEBUG_MODE_DEF	(MnTST_DEBUG_MODE_OFF)

#define MnTST_HOLD_VALUE_MIN	(0)
#define MnTST_HOLD_VALUE_MAX	(1000)
#define MnTST_HOLD_VALUE_DEF	(0)

enum {
	MnTST_HW_FILTER_1 = 0,
	MnTST_HW_FILTER_2,

	MnTST_HW_FILTER_NUM,
};


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Memory Parameter
typedef struct {
	U08 hw_rx_amp;
	U08 smooth_num[APP_CH_NUM];
	U08 smooth_range[APP_CH_NUM];
	U16 thr_range[APP_CH_NUM];
	U16 thr_min[APP_CH_NUM];
	U16 pulse_num[APP_CH_NUM];
	U16 echo_amp_b[APP_CH_NUM];
	U16 judge_heigh_in;
	U16 judge_heigh_out;
	U16 judge_time;
	U16 sensor_distance;
	U16 next_wait_time;
	U08 demo_mode;
	U08 debug_mode;
	U16 hold_value[APP_CH_NUM][MsCAL_THR_TYPE_NUM];
} MnTST_mPR;

// Local Struct
typedef struct {
	MnTST_mPR mPr;
	U08 lyr;		// Layer Index

} MnTST_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern Global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
extern S32 MnTST_PrGet_Value(U08 itm);
extern S32 MnTST_PrGet_CH_Value(U08 ch,U08 itm);

//------------------------------------------------------------------------------------------------------------------------------
//  Extern Global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
extern void MnTST_PrSet_Value(S32 val);			// Set
extern void MnTST_PrRst_Factory(void);			// Factory Reset


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
extern U08 MnTST_GetLayer(void);
// Set
extern void MnTST_SetLayer(U08 lyr);


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern void MnTST_PrInitMain(void);
extern void MnTST_InitMain(void);



#endif // ___MENU_TEST_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

