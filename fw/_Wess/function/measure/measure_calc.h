//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___MEASURE_CALC_H___
#define ___MEASURE_CALC_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "bsp_adc.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
#define MsCAL_CNST_MT2FT		(3.280839895)
#define MsCAL_CNST_FT2MT		(0.304800000001219)

#define MsCAL_NG_LEVEL			(0xFFFF)
#define MsCAL_NG_ASF_			(MsCAL_NG_LEVEL)

#define MsCAL_PROF_MAX			(100)
#define MsCAL_DAMP_MAX			(100)
#define MsCAL_CYCL_MAX			(30)

#define MsCAL_THR_MAX			(ADC_VAL_MAX)
#define MsCAL_THR_MIN			(ADC_VAL_MAX/2)

#define MsCAL_TRACK_RANGE		(100)

#define MsCAL_SIGNAL_OK_TIME	(15)		//Signal Stabilization Time
#define MsCAL_SIGNAL_NG_TIME	(15)			//Signal Stabilization Time

#define MsCAL_FIELD_THR			(1800)
enum {
	MsCAL_CH_S0 = 0,
	MsCAL_CH_S1,

	MsCAL_CH_NUM
};

enum {
	MsCAL_THR_LIGHT = 0,
	MsCAL_THR_HEAVY,

	MsCAL_THR_TYPE_NUM
};


enum {
	MsCAL_RTN_OK = 0,
	MsCAL_RTN_NG_ST1,		// Threshold
	MsCAL_RTN_NG_ST2,		// ASF
	MsCAL_RTN_NG_ST3,		// TW

	MsCAL_RTN_NUMB
};

enum {
	ERROR_OFF=0,
	ERROR_ON,
};

enum {
	SIGNAL_NG=0,
	SIGNAL_OK,
};	

#define Re_Filter_Range			(20)
enum {
	Tracking_OFF = 0,
	Tracking_ON,
};
	

//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef union {
	struct
	{
		U08 err:1;
		U08 _rsv:7;
	} b;
	U08 byte;

} MsCAL_FLG;

typedef struct {
	MsCAL_FLG f;

	U16 aEco_rslt[MsCAL_CH_NUM][ADC_BUFF_MAX];
	U16 aEco_filed_rlst[MsCAL_CH_NUM][ADC_BUFF_MAX];
	U16 aEco_filed_prof[MsCAL_CH_NUM][11][ADC_BUFF_MAX];
	U16 dist_prof[MsCAL_CH_NUM][ADC_BUFF_MAX];
	U16 aEco_real[MsCAL_CH_NUM][ADC_BUFF_MAX];
	U16 aEco_field_real[MsCAL_CH_NUM][ADC_BUFF_MAX];
	U16 dist_damp[MsCAL_CH_NUM][MsCAL_THR_TYPE_NUM][MsCAL_DAMP_MAX];
	U16 dist_cycl[MsCAL_CH_NUM][MsCAL_CYCL_MAX];
	U16 rslt_dist[MsCAL_CH_NUM][MsCAL_THR_TYPE_NUM];
	U16 rslt_sldg[MsCAL_CH_NUM][MsCAL_THR_TYPE_NUM];
	U16 stp3_dist[MsCAL_CH_NUM][MsCAL_THR_TYPE_NUM];									// Distance
	U16 stp3_sldg[MsCAL_CH_NUM][MsCAL_THR_TYPE_NUM];									// Sludge
	U16 diff_dist;					 // Differancial Distance
	U16 diff_sldg;					 // Differancial Sludge
	U16 avrg_dist;					 // Average Value
	U16 avrg_sldg;					 // Average Value
	U16 mini_dist;					 // mininum Value
	U16 mini_sldg;					 // mininum Value
	U08 mini_sens;
	U16 field_sldg[MsCAL_CH_NUM];
	U16 field_dist[MsCAL_CH_NUM];
	U08 fRefilter[MsCAL_CH_NUM][MsCAL_THR_TYPE_NUM];					 // Re-filtering 	   (Time windows)
	U16 Refilter_cnt[MsCAL_CH_NUM][MsCAL_THR_TYPE_NUM];				 // Re-filtering Counter(Time windows)
	U16 Tracking_dist[MsCAL_CH_NUM][MsCAL_THR_TYPE_NUM]; // Tracking Distance(Time Windows)
	U16 NOT_Tracking_dist[MsCAL_CH_NUM][MsCAL_THR_TYPE_NUM]; // Tracking Distance(Time Windows)



	U16 save_real[MsCAL_CH_NUM][ADC_BUFF_MAX];
	U16 save_rslt[MsCAL_CH_NUM][ADC_BUFF_MAX];

	U16 csave_avg[APP_CH_NUM];

	U32	thr[MsCAL_CH_NUM][MsCAL_THR_TYPE_NUM];
	U32 thr_max[MsCAL_CH_NUM];
	U32 thr_min[MsCAL_CH_NUM];

	U08 f_run[MsCAL_CH_NUM];
	U16 error_sec[MsCAL_CH_NUM];
	
	U16 signal_ok_sec[MsCAL_CH_NUM];
	U16 signal_ng_sec[MsCAL_CH_NUM];
	U16 f_signal[MsCAL_CH_NUM];

	U08 stt[MsCAL_CH_NUM];
	U16 cProf;					// Profile Count

	U16 asf_r[MsCAL_CH_NUM];
	U16 asf_h[MsCAL_CH_NUM];

	U16 cnt;
	U16 valu[APP_CH_NUM];
	U16 step;
} MsCAL_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------
extern U16 *SDRAM_aEco_prof_S2;
extern U16 *SDRAM_aEco_prof_S3;

//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get Local Variables - Result
extern U16 MsCAL_GetVl_TracDist(U08 iCh, U08 type);
extern U16 MsCAL_GetVl_EchoReal(U08 iCh, U16 idx);
extern U16 MsCAL_GetVl_RsltDist(U08 iCh, U08 type);
extern U16 MsCAL_GetVl_RsltSldg(U08 iCh, U08 type);
extern U16 MsCAL_GetVl_Stp3Dist(U08 iCh, U08 type);
extern U16 MsCAL_GetVl_Stp3Sldg(U08 iCh, U08 type);
extern U16 MsCAL_GetVl_EchoBuff(U08 iCh, U16 idx);
extern U16 MsCAL_GetVl_SaveBuff(U08 iCh, U16 idx);
extern U16 MsCAL_GetVl_SaveReal(U08 iCh, U16 idx);	

extern U16 MsCAL_GetVl_DiffDist(void);
extern U16 MsCAL_GetVl_DiffSldg(void);
extern U16 MsCAL_GetVl_AvrgDist(void);
extern U16 MsCAL_GetVl_AvrgSldg(void);
extern U16 MsCAL_GetVl_MiniDist(void);
extern U16 MsCAL_GetVl_MiniSldg(void);
extern U08 MsCAL_GetVl_MiniSens(void);
extern U32 MsCAL_GetVl_Threshold(U08 ich, U08 type);
extern U32 MsCAL_GetVl_Threshold_Max(U08 iCh);
extern U32 MsCAL_GetVl_Threshold_Min(U08 iCh);
extern U16 MsCAL_GetVl_ASF_R(U08 iCh);
extern U16 MsCAL_GetVl_ASF_H(U08 iCh);
extern U08 MsCAL_Get_Stt(U08 iCh);

extern U16 MsCAL_GetVl_FieldBuff(U08 iCh, U16 idx);
extern U16 MsCAL_GetVl_FieldReal(U08 iCh, U16 idx);
extern U16 MsCAL_GetVl_FieldDist(U08 iCh);
extern U16 MsCAL_GetVl_FieldSldg(U08 iCh);	
// Set Local Variables
extern void MsCAL_SetVl_ASF_R(U08 iCh,U16 val);	
extern void MsCAL_SetVl_ASF_H(U08 iCh,U16 val);	
extern void MsCAL_SetVl_RsltDist(U08 iCh,U08 type, U16 val);
extern void MsCAL_SetVl_RsltSldg(U08 iCh,U08 type, U16 val);		


// Converter Unit
extern F32 MsCAL_Feet2Meter(U16 feet);
extern F32 MsCAL_Meter2Feet(U16 meter);
// Basic
extern void MsCAL_InitVari(void);
extern void MsCAL_ProcProf(U08 iCh, U32 idx);
extern void MsCAL_Proc3Stp(U08 iCh);
extern void MsCAL_ProcDamp(U08 iCh, U16 idx);
extern U16 CalPrc_GetAsfCnt(U08 ch, U16 st, U16 thd);

#if 1
extern void MsCAL_ProcCycle(U08 iCh, U16 cnt);
extern void MsCalPrc_DualParam();

extern U16 TPRT_Calib(U08 ch, U16 index);
extern void CalPrc_Tprt_Check(U08 ch);
extern void MsCAL_ProcSmooth(U08 ch);
extern void CalPrc_ResetFlag(U08 ch);
extern void CalPrc_SttCheck(U08 iCh);
extern void MsCAL_CheckWeak(U08 iCh);
extern void MsCAL_ProcReal(U08 iCh);
extern void MsCAL_SaveEcho(U08 ch);
extern void CalPrc_Threshold_Value(U08 ch);

extern void MsCal_fieldReal(U08 iCh);
extern void MsCAL_FieldAProf(U08 iCh, U08 idx);

extern void MsCAL_ProcRealSave(U32 idx);

extern void MsCAL_ProcRealSave160(U32 idx);
extern void MsCAL_ProcRealSave380(U32 idx);

extern void MsCAL_ProcAvgSave(U08 ch);
#endif
#endif // ___MEASURE_CALC_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

