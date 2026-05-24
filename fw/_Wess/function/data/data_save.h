//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DATA_SAVE_H___
#define ___DATA_SAVE_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
// app
#include "app_sys.h"
#include "measure_calc.h"
// bsp
#include "bsp_rtc.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
#define SAV_INTERVAL		1			// 1 Min.
#define SAV_MAX_BUF_CNT		20000		// 1 Min.

#define SAV_DOWN_OK			0xff

enum {
	SAV_MODE_IDLE = 0,
	SAV_MODE_SAVE,
	SAV_MODE_DUMP,

	SAV_MODE_MAX,
};


// Standard 
#if 0
enum {
	SAV_PKT_TM_YEAR = 0,
	SAV_PKT_TM_MONTH,
	SAV_PKT_TM_DAY,
	SAV_PKT_TM_HOUR,
	SAV_PKT_TM_MIN,
	SAV_PKT_VAL_CH0_H,
	SAV_PKT_VAL_CH0_L,	
	SAV_PKT_TPR_CH0_H,	
	SAV_PKT_TPR_CH0_L,
	SAV_PKT_VAL_CH1_H,
	SAV_PKT_VAL_CH1_L,	
	SAV_PKT_TPR_CH1_H,	
	SAV_PKT_TPR_CH1_L,

	SAV_PKT_MAX,
};
#else
enum {
	SAV_PKT_TM_YEAR = 0,
	SAV_PKT_TM_MONTH,
	SAV_PKT_TM_DAY,
	SAV_PKT_TM_HOUR,
	SAV_PKT_TM_MIN,
	SAV_PKT_VAL_CH1_LIGHT_H,
	SAV_PKT_VAL_CH1_LIGHT_L,
	SAV_PKT_VAL_CH1_HEAVY_H,
	SAV_PKT_VAL_CH1_HEAVY_L,
	SAV_PKT_TPR_CH1_H,	
	SAV_PKT_TPR_CH1_L,
	SAV_PKT_VAL_CH2_LIGHT_H,
	SAV_PKT_VAL_CH2_LIGHT_L,
	SAV_PKT_VAL_CH2_HEAVY_H,
	SAV_PKT_VAL_CH2_HEAVY_L,	
	SAV_PKT_TPR_CH2_H,	
	SAV_PKT_TPR_CH2_L,
	SAV_PKT_STT,

	SAV_PKT_MAX,
};


#endif

// Field A
enum {
	SAV_PKT_FLD_TM_YEAR  = 0,
	SAV_PKT_FLD_TM_MONTH,
	SAV_PKT_FLD_TM_DAY,
	SAV_PKT_FLD_TM_HOUR,
	SAV_PKT_FLD_TM_MIN,
	SAV_PKT_FLD_CH1_EVT,
	SAV_PKT_FLD_CH1_LIGHT_H,
	SAV_PKT_FLD_CH1_LIGHT_L,
	SAV_PKT_FLD_CH1_HEAVY_H,
	SAV_PKT_FLD_CH1_HEAVY_L,	
	SAV_PKT_FLD_CH1_RAW_H,
	SAV_PKT_FLD_CH1_RAW_L,		
	SAV_PKT_FLD_TPR_CH1_H,
	SAV_PKT_FLD_TPR_CH1_L,
	SAV_PKT_FLD_CH2_EVT,
	SAV_PKT_FLD_CH2_LIGHT_H,
	SAV_PKT_FLD_CH2_LIGHT_L,
	SAV_PKT_FLD_CH2_HEAVY_H,
	SAV_PKT_FLD_CH2_HEAVY_L,
	SAV_PKT_FLD_CH2_RAW_H,
	SAV_PKT_FLD_CH2_RAW_L,		
	SAV_PKT_FLD_TPR_CH2_H,
	SAV_PKT_FLD_TPR_CH2_L,
	SAV_PKT_FLD_STT,
	SAV_PKT_FLD_POS,
	SAV_PKT_FLD_DIR,
	SAV_PKT_FLD_VEL_H,
	SAV_PKT_FLD_VEL_L,
	
	SAV_PKT_FLD_MAX,
};


#define SAV_INTERVAL_01S	1		// 1 sec
#define SAV_INTERVAL_10S	10      // 10 sec
#define SAV_INTERVAL_01M	60      // 1 min
#define SAV_INTERVAL_10M	600     // 10 min
#define SAV_INTERVAL_01H	3600    // 1 hour
#define SAV_INTERVAL_10H	36000   // 10 hour


#define trend_buff_max		600



//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	#if 1
	RTC_TM prv_tim;
	#endif
	U08 pkt[SAV_PKT_MAX];

	U08 dump_f_en;
	U08 save_f_ov;		// overflow

	U16 t_1s_cnt;
	U32 dump_addr;		// Start memory address to dump
	U32 dump_cnt;		// Start memory address to dump
	U32 dump_size;


	U32 save_cnt;
	U32 save_addr;		// Start memory address to save
	U32 save_size;

	U08 save_loading;
} SAV_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get Local Variables
extern U32 DaSav_GetCnt(void);
extern U08 DaSav_GetDumfEn(void);
extern U08 DaSav_GetDumfEn(void);
extern U32 DaSav_GetDumpAddr(void);
extern U32 DaSav_GetSaveSize(void);

// Set Local Variables
extern void DaSav_SetDumfEn(U08 fen);
extern void DaSav_dumpSetinit(void);

// Operation
extern void DaSAV_InitVari(void);
extern void DaSAV_ProcSave(void);
extern void DaSAV_DumpInit(void);
extern U08 DaSAV_DumpProgress(U08 *rtn_pct);
extern U08 DaSAV_DumpProgress_Save_380(U08 *rtn_pct);
extern U08 DaSAV_DumpProgress_Save_160(U08 *rtn_pct);
extern U08 DaSAV_UsbExportCsv(I08 *filenameBuf, U16 filenameBufSize);
extern void DaSAV_DeleteData(void);

#endif // ___DATA_SAVE_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

