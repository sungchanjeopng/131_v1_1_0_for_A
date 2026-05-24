//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2022-01-20 12:00:00 +0900 $ (From 2020-07-13)
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___SCREEN_CALIB_H___
#define ___SCREEN_CALIB_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "menu_engineer.h"

//bsp
#include "bsp_adc.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
#if 1
// Function Indix
enum {
	ScCLB_OPT_CH_SEL = 0,
	ScCLB_OPT_TREND_LEFT,
	ScCLB_OPT_TREND_RIGHT,
	ScCLB_OPT_NUM,
};

#if 0
enum {
	// TVG #1
	ScCLB_F00_FREQ = 0,				// FREQuency
	ScCLB_F01_TX_WAV,				// Transmit(Tx): Waveform Number
	ScCLB_F02_RX_GAIN,				// Receive(Rx): Gain (VCA: 1~50) 		 // Y=a(x+b) --- a
	ScCLB_F03_RX_TRANS,	
	ScCLB_F04_RX_AMP,				// Receive(Rx): AMP  (x47 or x100)
	// TVG #2	
	ScCLB_F05_TVG_fEN,				// TVG Graph Enable
	ScCLB_F06_TVG_CUSTOM,			// TVG Custom
	// Number Max
	ScCLB_FNC_NUM,
};

#define ScCLB_ITM_I00				(ScCLB_F00_FREQ)
#define ScCLB_ITM_MAX				(ScCLB_FNC_NUM-1)
#endif
// FREQuency Index
enum {
	ScCLB_FREQ_130K,
	ScCLB_FREQ_160K,
	ScCLB_FREQ_270K,
	ScCLB_FREQ_380K,
	// Number Max
	ScCLB_FREQ_NUM,
};
#define ScCLB_FREQ_MIN				(ScCLB_FREQ_130K)
#define ScCLB_FREQ_DEF				(ScCLB_FREQ_380K)
#define ScCLB_FREQ_MAX				(ScCLB_FREQ_NUM - 1)

// Tx Wave Number
enum {
	ScCLB_TX_WAV_MIN = 5,
	ScCLB_TX_WAV_DEF = 10,
	ScCLB_TX_WAV_MAX = 60,
};

#if 1
// Rx Gain Slope
enum {
	ScCLB_RX_GAIN_MIN = 0,
	ScCLB_RX_GAIN_DEF = 15,
	ScCLB_RX_GAIN_MAX = 50,
};


#define ScCLB_RX_TRANS_MIN 			(-2000)
#define ScCLB_RX_TRANS_DEF 			(0)
#define ScCLB_RX_TRANS_MAX 			(2000)
#define ScCLB_RX_TRANS_CNT 			(10)


#else
// Rx Gain
enum {
	ScCLB_RX_GAIN_MIN = 1,			// x  0.01
	ScCLB_RX_GAIN_DEF = 10,			// x  0.10
	ScCLB_RX_GAIN_CNT = 100,		// x  1.00
	ScCLB_RX_GAIN_MAX = 10000,		// x100.00
};
#endif
// Rx AMP
enum {
	ScCLB_RX_AMP_x47 = 0,
	ScCLB_RX_AMP_x100,
	// Number Max
	ScCLB_RX_AMP_NUM,
};

#define ScCLB_RX_AMP_MIN			(ScCLB_RX_AMP_x47)
#define ScCLB_RX_AMP_DEF			(ScCLB_RX_AMP_x100)
#define ScCLB_RX_AMP_MAX			(ScCLB_RX_AMP_NUM-1)

// TVG
enum {
	ScCLB_TVG_MIN = 0,
	ScCLB_TVG_DEF = 1,
	ScCLB_TVG_MAX = 7,
};

#define ScCLB_TVG_OFF				(ScCLB_TVG_MIN)
#define ScCLB_TVG_CUSTOM			(7)
#define ScCLB_TVG_NUM				(7)

enum {
	ScCLB_TVG_MOD_V0 = 0,
	ScCLB_TVG_MOD_V1,
	// Number Max
	ScCLB_TVG_MOD_NUM
};
#define ScCLB_TVG_MOD_MIN 			(ScCLB_TVG_MOD_V0)
#define ScCLB_TVG_MOD_MAX			(ScCLB_TVG_MOD_NUM-1)
#define ScCLB_TVG_MOD_DEF			(ScCLB_TVG_MOD_V1)


#define TVG_IDX_MAX 				ADC_BUFF_MAX/20

// Selected Channel
enum {
	ScCLB_CH_0 = 0,
	ScCLB_CH_1,
	// Number Max
	ScCLB_CH_NUM
};

enum	{
	ScCLB_TVG_CUSTOM_MODE_X = 0,
	ScCLB_TVG_CUSTOM_MODE_Y,

	ScCLB_TVT_CUSTOM_MODE_NUM
};

#define ScCLB_TVG_X_AXIS_MIN 			(0)
#define ScCLB_TVG_X_AXIS_MAX			(TVG_IDX_MAX)
#define ScCLB_TVG_X_AXIS_DEF			(0)

#define ScCLB_TVG_Y_VALUE_MIN			(0)
#define ScCLB_TVG_Y_VALUE_MAX			(200)
#endif




//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Parameter (Memory)
typedef struct {
#if 0
	// TVG (ON & OFF)
	U08 FREQ[ScCLB_CH_NUM];							// FREQuency
	U16 wave[ScCLB_CH_NUM];						// Tx. Waveform Number
	U08 amp[ScCLB_CH_NUM];						// Rx. Amp
	U16 gain[ScCLB_CH_NUM];						// Rx. Gain
	S16 gain_trans[ScCLB_CH_NUM];				// Rx. Gain Y-Translation
	U16 aTvg[ScCLB_CH_NUM][ScCLB_TVG_NUM];		// TVG Array Value
	U16 aTvg_custom[ScCLB_CH_NUM][TVG_IDX_MAX];	// TVG Array Value	
	U08 aTvg_x_axis[ScCLB_CH_NUM];			// TVG Array Value		
	U08 aTvg_x_y[ScCLB_CH_NUM];			// TVG Array Value		
	// TVG (Flag)
	U08 fTvg[ScCLB_CH_NUM];						// TVG (Flag)
	U08 tvg_mod[ScCLB_CH_NUM];
	// Sensor Index
#endif
	U08 ch;									// Ch1 / ch2

} ScCLB_mPR;

// Local Struct
typedef struct {
	ScCLB_mPR mPr;			// Parameter (Memory)
	U08 lyr;				// Layer

} ScCLB_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------
extern U16 lMsr_aTvg[MnEGN_TVG_MAX][TVG_IDX_MAX];
//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Parameters
//------------------------------------------------------------------------------------------------------------------------------
// TVG
#if 0
extern U16  ScCLB_PrGet_Tvg_Custom(U08 ch, U08 x);
extern void ScCLB_PrSet_Tvg_Custom(U08 ch, U08 x, U16 val);
extern U08 ScCLB_PrGet_Tvg_x_axis(U08 ch);
#endif
// Get
extern S32 ScCLB_PrGet_Value(U08 iCh, U08 iFn);
extern U08 ScCLB_GetCh(void);
// Set / Reset
extern void ScCLB_PrSet_Value(S32 val);
extern void ScCLB_PrRst_Factory(void);
extern void ScCLB_SetCh(U08 ch);	

//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
extern U08  ScCLB_GetLayer(void);
extern void ScCLB_SetLayer(U08 lyr);


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern void ScCLB_PrInitMain(void);
extern void ScCLB_InitMain(void);
extern void ScCLB_ProcMain(void);



#endif // ___SCREEN_CALIB_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

