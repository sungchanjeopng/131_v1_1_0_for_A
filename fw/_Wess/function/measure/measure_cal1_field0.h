//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2022-01-20 12:00:00 +0900 $ (From 2020-07-13)
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___MEASURE_CAL1_FIELD0_H___
#define ___MEASURE_CAL1_FIELD0_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "measure_calc.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
#define CAL1_DTT_DP_CNT		5 // Display Counter


//Detect 
enum {
	CAL1_EVT_NONE   = 0x00,
	CAL1_EVT_PASS	= 0x01,
	CAL1_EVT_EXIT   = 0x02,
};

//Detect Channel
enum {
	CAL1_CH_1 = 0,
	CAL1_CH_2,

	CAL1_CH_NUM,
};

//Detect Number
enum {
	CAL1_DTT_NONE = 0,	
	CAL1_DTT_1ST,  		// Judge 1 (First)
 	CAL1_DTT_2ND,   	// Judge 2 (Last)

	CAL1_DTT_NUM,
};

//Detect Direction
enum {
	CAL1_DIRE_NONE = 0,
	CAL1_DIRE_CH_1TO2,	// CAL1_DIRE_CH_1 ->   CAL1_DIRE_CH_2
	CAL1_DIRE_CH_2TO1,	// CAL1_DIRE_CH_2 ->   CAL1_DIRE_CH_1

	CAL1_DIRE_NUM,
};

enum {
	CAL1_FIN_DIRE_NONE = 0,
	CAL1_FIN_DIRE_CH_1TO2,	// CAL1_DIRE_CH_1 ->   CAL1_DIRE_CH_2
	CAL1_FIN_DIRE_CH_2TO1,	// CAL1_DIRE_CH_2 ->   CAL1_DIRE_CH_1
	CAL1_FIN_DIRE_CIRCUL,

	CAL1_FIN_DIRE_NUM,
};

//Detect position
enum {
	CAL1_POS_CH_NONE = 0,
	CAL1_POS_CH_1,
	CAL1_POS_CH_2,
	
	CAL1_POS_CH_NUM,
};

enum {
	CAL1_FIN_POS_NONE = 0,
	CAL1_FIN_POS_START,
	CAL1_FIN_POS_CH_1,
	CAL1_FIN_POS_CH_1_CH2,
	CAL1_FIN_POS_CH_2,
	CAL1_FIN_POS_END,
	
	CAL1_FIN_POS_NUM,
};

enum {
	CAL1_TIME_1ST,  		
 	CAL1_TIME_2ND,   

	CAL1_TIME_NUM,
};



enum {
	CAL1_RST_DET_NONE,
	CAL1_RST_DET_STEP1,
	CAL1_RST_DET_STEP2,
	CAL1_RST_DET_STEP3,
	CAL1_RST_DET_STEP4,
	
	CAL1_DET_RST_NUM,

};

enum {
	CAL1_DETECT_IDLE,
	CAL1_DETECT_STEP1,
	CAL1_DETECT_STEP2,
	CAL1_DETECT_STEP3,

	CAL1_DETECT_STEP_NUM,
};

//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------

//Detect Time
typedef	struct {
	U64 start;
	U64 stop;
	U32 elapsed;
	U64 start_old;
	U64 stop_old;

	U64 delay_time;
} CAL1_TIM;	// sec

typedef	struct {
	U08 dir;
	U08 pos;
	U08 pos_old;
	U64 tim[CAL1_TIME_NUM];	// delta t (sec.)
	U16 vel;	// m/s
	U64 cyc;

	U08 detect[CAL1_CH_NUM];
	U16 detect_tim[CAL1_CH_NUM];
	U16 detect_level[CAL1_CH_NUM];


	U08 detect_2[CAL1_CH_NUM];
	U16 detect_tim_2[CAL1_CH_NUM];
	U16 detect_level_2[CAL1_CH_NUM];	
} CAL1_RESULT;

typedef struct {
	U08 dtt[CAL1_CH_NUM];
	U08 dtt_cnt;
	U08 cyc;
} CAL1_SCREEN;

typedef struct {
	U08 stt;
	U32 next_w_cnt;
} CAL1_JUDGE;


typedef struct{
	U16 cnt[APP_CH_NUM];
	S32 buff[APP_CH_NUM][MsCAL_THR_TYPE_NUM][1200];
	U16 value[APP_CH_NUM][MsCAL_THR_TYPE_NUM];
} CAL1_HUNTING;

typedef	struct {
	U08 evt[CAL1_CH_NUM];		// Event
	U08 stt[CAL1_CH_NUM];		// Event

	U64 tick_1sec[CAL1_CH_NUM];

	// Detect
	U08 fDtt[CAL1_CH_NUM];
	CAL1_TIM dtt_tim[CAL1_CH_NUM];
	U16 track_rlst[CAL1_CH_NUM];

	
	// Screen
	CAL1_SCREEN fDp;
	// Result
	CAL1_RESULT rst;
	// Judge
	CAL1_JUDGE  jdg;

	CAL1_HUNTING hunting;


	U16 rlst_old[CAL1_CH_NUM][MsCAL_THR_TYPE_NUM];	
	U08 fin_pos;
	U08 fin_dir;
} CAL1_LV;

//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
extern U08 MsCAL1_Getrst_pos(void);
extern U08 MsCAL1_Getrst_dir(void);
extern U08 MsCAL1_Getfin_pos(void);
extern U08 MsCAL1_Getfin_dir(void);
extern U16 MsCAL1_Getrst_vel(void);
extern U08 MsCAL1_Getrst_evt(U08 ch);
extern U08 MsCAL1_Getjdg_stt(void);
extern U08 MsCAL1_GetfDp_dtt(U08 ch);
extern U08 MsCAL1_Get_fdtt(U08 ch);
extern U08 MsCAL1_GetfDp_cyc(void);
extern U16 MsCAL1_Getrst_Value_old(U08 ch, U08 type);
extern U08 MsCal1_Getrst_dtt(U08 ch);
extern U64 MsCAL1_Getrst_cyc(void);
extern U16 MsCAL1_Hunting_value(U08 ch,U08 type);
// Get Not
extern U08 MsCAL1_Getrst_tim(void);
// Set
extern void MsCAL1_Setrst_cyc(U64 cyc);

//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern void MsCAL1_InitVari(void);
extern void MsCal1_ProcDetect(U08 ch);
extern void MsCAL1_ProcMain(void);
extern void MsCal1_ProcJudge(void);
extern void MsCal1_CalcResult(void);
extern void MsCal1_Hunting_Proc(void);


#endif // ___MEASURE_CAL1_FIELD0_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

