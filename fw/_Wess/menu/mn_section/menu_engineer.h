//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2022-01-20 12:00:00 +0900 $ (From 2020-07-13)
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___MENU_ENGINEER_H___
#define ___MENU_ENGINEER_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "app_main.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
enum {
	MnEGN_OPT_THRESHOLD_SYNC = 0,
	MnEGN_OPT_CH1_PROFILE,
	MnEGN_OPT_CH1_TVG,
	MnEGN_OPT_CH1_WINDOW_RESET_TIME,
	MnEGN_OPT_CH1_WINDOW_RANGE,
	MnEGN_OPT_CH2_PROFILE,
	MnEGN_OPT_CH2_TVG,
	MnEGN_OPT_CH2_WINDOW_RESET_TIME,
	MnEGN_OPT_CH2_WINDOW_RANGE,	
	MnEGN_OPT_MSR,
	// Number Max
	MnEGN_OPT_NUM,
};

enum {
	MnEGN_OPT_SINGLE_THRESHOLD_SYNC = 0,
	MnEGN_OPT_SINGLE_PROFILE,
	MnEGN_OPT_SINGLE_TVG,
	MnEGN_OPT_SINGLE_WINDOW_RESET_TIME,
	MnEGN_OPT_SINGLE_WINDOW_RANGE,
	MnEGN_OPT_SINGLE_MSR,
	// Number Max
	MnEGN_OPT_SINGLE_NUM,
};

#define MnEGN_OPT_SINGLE_MIN	(MnEGN_OPT_SINGLE_THRESHOLD_SYNC)
#define MnEGN_OPT_SINGLE_MAX	(MnEGN_OPT_SINGLE_NUM-1)

#define MnEGN_OPT_MIN			(MnEGN_OPT_THRESHOLD_SYNC)
#define MnEGN_OPT_MAX			(MnEGN_OPT_NUM-1)

enum {
	MnEGN_THRESHOLD_SYNC_OFF = 0,
	MnEGN_THRESHOLD_SYNC_ON,

	MnEGN_THRESHOLD_SYNC_NUM,
};

#define MnEGN_THRESHOLD_SYNC_MIN (MnEGN_THRESHOLD_SYNC_OFF)
#define MnEGN_THRESHOLD_SYNC_DFT (MnEGN_THRESHOLD_SYNC_OFF)
#define MnEGN_THRESHOLD_SYNC_MAX (MnEGN_THRESHOLD_SYNC_OFF)

#define MnEGN_PROFILE_MIN	(1)
#define MnEGN_PROFILE_DEF	(30)
#define MnEGN_PROFILE_MAX	(60)

#define MnEGN_TVG_MIN		(0)
#define MnEGN_TVG_MAX		(7)
#define MnEGN_TVG_DEF		(1)

#define MnEGN_WINDOW_RESET_TIME_MIN	(0)
#define MnEGN_WINDOW_RESET_TIME_MAX	(600)
#define MnEGN_WINDOW_RESET_TIME_DEF	(120)

#define MnEGN_WINDOW_RANGE_MIN	(1)
#define MnEGN_WINDOW_RANGE_MAX	(1000)
#define MnEGN_WINDOW_RANGE_DEF	(20)

enum {
	MnEGN_MSR_OFF = 0,
	MnEGN_MSR_ON,

	MnEGN_MSR_NUM,
};

#define MnEGN_MSR_MIN (MnEGN_MSR_OFF)
#define MnEGN_MSR_DEF (MnEGN_MSR_OFF)
#define MnEGN_MSR_MAX (MnEGN_MSR_NUM-1)



#if 0
// Item Index
enum {
	MnEGN_I00_THRESHOLD_MIN = 0,
	MnEGN_I01_SMOOTH_NUM,
	MnEGN_I02_SMOOTH_RANGE,
	MnEGN_I03_fDP_DBG,
	MnEGN_I04_fDP_ECHO,
	MnEGN_I05_RX_BPF,
	// Number Max
	MnEGN_ITM_NUM,
};
#define MnEGN_ITM_I00			(MnEGN_I00_THRESHOLD_MIN)

#define MnEGN_IV0_MIN			(1)
#define MnEGN_IV0_MAX			(99)
#define MnEGN_IV0_DEF			(50)


#define MnEGN_IV1_MIN			(0)
#define MnEGN_IV1_MAX			(5)
#define MnEGN_IV1_DEF			(2)

#define MnEGN_IV2_MIN			(0)
#define MnEGN_IV2_MAX			(10)
#define MnEGN_IV2_DEF			(1)


// Disp. Debug
enum {
	MnEGN_fDP_DBG_OFF = 0,
	MnEGN_fDP_DBG_ON,
	// Number Max
	MnEGN_fDP_DBG_NUM,
};

// Disp. Echo
enum {
	MnEGN_fDP_ECHO_OFF = 0,
	MnEGN_fDP_ECHO_ON,
	// Number Max
	MnEGN_fDP_ECHO_NUM,
};

enum {
	MnEGN_IV5_RX_BPF_0 = 0,
	MnEGN_IV5_RX_BPF_1,
	// Number Max
	MnEGN_IV5_RX_BPF_NUM,
};

#define MnEGN_IV5_MIN 	(MnEGN_IV5_RX_BPF_0)
#define MnEGN_IV5_MAX	(MnEGN_IV5_RX_BPF_1)
#define MnEGN_IV5_DEF	(MnEGN_IV5_RX_BPF_1)
#endif
//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Memory Parameter
typedef struct {
	U08 thr_min;
	U08 smooth_num;
	U08 smooth_range;
	U08 fDp_dbg;	// Flg: Disp. Debug String
	U08 fDp_echo;
	U08 rx_bpf;	// Band Pass Filter

	U08 thr_sync;
	U08 prof[APP_CH_NUM];
	U08 tvg[APP_CH_NUM];
	U16 window_time[APP_CH_NUM];
	U16 window_range[APP_CH_NUM];
	U08 msr;
} MnEGN_mPR;

// Local Struct
typedef struct {
	MnEGN_mPR mPr;
	U08 lyr;		// Layer Index

} MnEGN_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern Global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
extern S32 MnEGN_PrGet_Item(U08 itm);
extern S32 MnEGN_PrGet_CH_Item(U08 ch, U08 itm);

//------------------------------------------------------------------------------------------------------------------------------
//  Extern Global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
extern void MnEGN_PrSet_Value(U08 iIt,S32 val);		// Set
extern void MnEGN_PrRst_Factory(void);			// Factory Reset
extern void MnEGN_PrSet_Ch_Value(U08 ch,U08 iIt,S32 val);

//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
extern U08 MnEGN_GetLayer(void);
// Set
extern void MnEGN_SetLayer(U08 lyr);


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern void MnEGN_PrInitMain(void);
extern void MnEGN_InitMain(void);



#endif // ___MENU_ENGINEER_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

