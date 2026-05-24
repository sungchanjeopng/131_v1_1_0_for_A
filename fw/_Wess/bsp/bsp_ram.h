//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___RAM_MAIN_H___
#define ___RAM_MAIN_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
//    4Mbit (512KB = 524,287)
//------------------------------------------------------------------------------------------------------------------------------
//0x57E40				// 360,000 = 20,000 * 18
#define MRM_SIZE_TRD_DAT		0x57E40			// 360,000 = 20,000 * 18
#define MRM_SIZE_TRD_PKT		SAV_PKT_MAX
#define MRM_SIZE_TRD_CNT		(0x57E40/SAV_PKT_MAX)
enum {
	//--------------------------------------------------------------------------------------------------------------------------
	// Start Reserved	0x00000 ~ 0x0007F	(128)
	//--------------------------------------------------------------------------------------------------------------------------
	_mADDR_START		= 0x00000,
	_mADDR_S_END		= 0x0007F,

	//--------------------------------------------------------------------------------------------------------------------------
	// Menu			0x00080 ~ 0x00FFF	(3,968)
	//--------------------------------------------------------------------------------------------------------------------------
	_mMENU_START 		= _mADDR_S_END+1,
	_mUNIT,				_mRSV00,
	_mCH1_OPERATION,	_mRSV01,
	_mCH2_OPERATION,	_mRSV02,
	_mCH1_EMPTY_L,		_mCH1_EMPTY_H,		
	_mCH2_EMPTY_L,		_mCH2_EMPTY_H,			
	_mCH1_DEADZONE_L,	_mCH1_DEADZONE_H,	
	_mCH2_DEADZONE_L,	_mCH2_DEADZONE_H,
	_mCH1_MSR_CYC,		_mRSV03,
	_mCH2_MSR_CYC,		_mRSV04,
	_mCH1_MSR_RST,		_mRSV05,
	_mCH2_MSR_RST,		_mRSV06,	
	_mCH1_FREQ,			_mRSV07,
	_mCH2_FREQ,			_mRSV08,
	_mCH1_ECHO_AMP,		_mRSV09,
	_mCH2_ECHO_AMP,		_mRSV10,
	_mCH1_THR_LIGHT_MODE,	_mRSV11,
	_mCH2_THR_LIGHT_MODE,	_mRSV12,	
	_mCH1_THR_HEAVY_MODE,	_mRSV13,
	_mCH2_THR_HEAVY_MODE,	_mRSV14,
	_mCH1_ASF_LIGHT_L,		_mCH1_ASF_LIGHT_H,	
	_mCH2_ASF_LIGHT_L,		_mCH2_ASF_LIGHT_H,		
	_mCH1_DAMP_L,		_mCH1_DAMP_H,		
	_mCH2_DAMP_L,		_mCH2_DAMP_H,
	_mCH1_OFFSET_L,		_mCH1_OFFSET_H,	
	_mCH2_OFFSET_L,		_mCH2_OFFSET_H,
	_mCH1_CURRENT_ASSIGN,	_mRSV15,
	_mCH2_CURRENT_ASSIGN,	_mRSV16,
	_mCH1_SET_4MA_L,	_mCH1_SET_4MA_H,
	_mCH2_SET_4MA_L,	_mCH2_SET_4MA_H,
	_mCH1_SET_20MA_L,	_mCH1_SET_20MA_H,		
	_mCH2_SET_20MA_L,	_mCH2_SET_20MA_H,
	_mCH1_TRIM_12MA_L,	_mCH1_TRIM_12MA_H,		
	_mCH2_TRIM_12MA_L,	_mCH2_TRIM_12MA_H,
	_mCH1_TRIM_20MA_L,	_mCH1_TRIM_20MA_H,		
	_mCH2_TRIM_20MA_L,	_mCH2_TRIM_20MA_H,
	_mRELAY_ASSIGN,		_mRSV17,
	_mRELAY_ACT_L,		_mRELAY_ACT_H,		
	_mRELAY_STOP_L,		_RELAY_STOP_H,	
	_mCLEAN_INTV_L,		_mCLEAN_INTV_H,	
	_mCLEAN_TERM_L,		_mCLEAN_TERM_H,
	_mERROR_DELAY_L,	_mERROR_DELAY_H,
	_mERROR_OUTPUT,		_mRSV18,
	_mSAVE_INTV,		_mRSV19,
	_mDISPLAY_TERM,		_mRSV20,
	_mDATA_Protocol,	_mRSV21,
	_mDATA_BAUD,		_mRSV22,
	_mDATA_ADDRESS_L,	_mDATA_ADDRESS_H,
	_mPASSCODE_L,		_mPASSCODE_H,
	_mLANG,				_mRSV23,
	_mCH1_SITE_NAME_L,	_mCH1_SITE_NAME_H,
	_mCH2_SITE_NAME_L,	_mCH2_SITE_NAME_H,
	_mRSV24,			_mRSV25,
	_mRSV26,			_mRSV27,	
	_mRTN_TIM,			_mRSV28,
	_mCH1_THR_LIGHT_VAL_L,	_mCH1_THR_LIGHT_VAL_H,
	_mCH1_THR_HEAVY_VAL_L,	_mCH1_THR_HEAVY_VAL_H,
	_mCH2_THR_LIGHT_VAL_L,	_mCH2_THR_LIGHT_VAL_H,
	_mCH2_THR_HEAVY_VAL_L,	_mCH2_THR_HEAVY_VAL_H,
	_mTHR_SYNC,			_mRSV29,
	_mCH1_PROF,			_mRSV30,
	_mCH2_PROF,			_mRSV31,
	_mCH1_TVG,			_mRSV32,
	_mCH2_TVG,			_mRSV33,
	_mCH1_WINDOW_TIME_L,	_mCH1_WINDOW_TIME_H,
	_mCH2_WINDOW_TIME_L,	_mCH2_WINDOW_TIME_H,
	_mCH1_WINDOW_RANGE_L,	_mCH1_WINDOW_RANGE_H,
	_mCH2_WINDOW_RANGE_L,	_mCH2_WINDOW_RANGE_H,
	_mSTRU_ON_OFF,		_mRSV34,
	_mHW_RX_AMP,		_mRSV35,
	_mCH1_SMOOTH_NUM,	_mRSV36,
	_mCH2_SMOOTH_NUM,	_mRSV37,
	_mCH1_SMOOTH_RANGE,	_mRSV38,
	_mCH2_SMOOTH_RANGE,	_mRSV39,
	_mCH1_THR_RANGE_L,	_mCH1_THR_RANGE_H,
	_mCH2_THR_RANGE_L,	_mCH2_THR_RANGE_H,
	_mCH1_THR_MIN_L,	_mCH1_THR_MIN_H,
	_mCH2_THR_MIN_L,	_mCH2_THR_MIN_H,
	_mCH1_PULSE_NUM_L,	_mCH1_PULSE_NUM_H,
	_mCH2_PULSE_NUM_L,	_mCH2_PULSE_NUM_H,
	_mCH1_ECHO_AMP_B_L,	_mCH1_ECHO_AMP_B_H,
	_mCH2_ECHO_AMP_B_L,	_mCH2_ECHO_AMP_B_H,
	_mFILTER_RANGE_L,_mFILTER_RANGE_H,
	_mJUDGE_HEIGHT_OUT_L,_mJUDGE_HEIGHT_OUT_H,
	_mFILTER_TIME_L,_mFILTER_TIME_H,	
	_mSENSOR_DISTANCE_L,_mSENSOR_DISTANCE_H,
	_mDEMO_MODE,		_mRSV40,
	_mDEBUG_MODE,		_mRSV41,
	_mCLEAN_MODE,		_mRSV42,
	_mALARM_TIMER,		_mRSV43,
	_mCH1_HOLD_LIGHT_VAL_L,	_mCH1_HOLD_LIGHT_VAL_H,
	_mCH1_HOLD_HEAVY_VAL_L,	_mCH1_HOLD_HEAVY_VAL_H,
	_mCH2_HOLD_LIGHT_VAL_L,	_mCH2_HOLD_LIGHT_VAL_H,
	_mCH2_HOLD_HEAVY_VAL_L,	_mCH2_HOLD_HEAVY_VAL_H,
	_mHW_FILTER,		_mRSV44,
	_mDAC_CH1_04MA_L, _mDAC_CH1_04MA_H,				// Channel 0: Cfg. 4mA (DAC)
	_mDAC_CH1_20MA_L, _mDAC_CH1_20MA_H,				// Channel 0: Cfg. 20mA (DAC)
	_mDAC_CH2_04MA_L, _mDAC_CH2_04MA_H,				// Channel 1: Cfg. 4mA (DAC)
	_mDAC_CH2_20MA_L, _mDAC_CH2_20MA_H,				// Channel 1: Cfg. 20mA (DAC)
	_mSENSOR_DUAL_SINGLE,		_mRSV45,
	_mCH1_ASF_HEAVY_L,		_mCH1_ASF_HEAVY_H,	
	_mCH2_ASF_HEAVY_L,		_mCH2_ASF_HEAVY_H,	
	_mNEXT_WAIT_TIME_L,		_mNEXT_WAIT_TIME_H,
	_mRF_CH1_ASSIGN,		_mRSV46,
	_mRF_CH2_ASSIGN,		_mRSV47,
	_mRF_CH1_ADDR_L,		_mRF_CH1_ADDR_H,
	_mRF_CH2_ADDR_L,		_mRF_CH2_ADDR_H,
	_mNAND_CH1_ECHO_BLOCK_L,	_mNAND_CH1_ECHO_BLOCK_H,
	_mNAND_CH1_ECHO_PAGE,		_mRSV48,
	_mNAND_CH1_META_PAGE,		_mRSV49,
	_mNAND_CH2_ECHO_BLOCK_L,	_mNAND_CH2_ECHO_BLOCK_H,
	_mNAND_CH2_ECHO_PAGE,		_mRSV50,
	_mNAND_CH2_META_PAGE,		_mRSV51,
	_mNAND_CH1_META_BLOCK_L,	_mNAND_CH1_META_BLOCK_H,
	_mNAND_CH2_META_BLOCK_L,	_mNAND_CH2_META_BLOCK_H,
	_mNAND_CH1_META_BUFFER_L,	_mNAND_CH1_META_BUFFER_H,
	_mNAND_CH2_META_BUFFER_L,	_mNAND_CH2_META_BUFFER_H,
	_mECHOSAVE_CH1_SAVEMODE,		_mRSV52,
	_mECHOSAVE_CH1_SAVEINTERVAL,	_mRSV53,
	_mNAND_CH1_ECHO_NUM_L,		_mNAND_CH1_ECHO_CNT_H,
	_mNAND_CH2_ECHO_NUM_L,		_mNAND_CH2_ECHO_CNT,H,
	_mCH1_AUTO_FAMP,			_mRSV54,
	_mCH2_AUTO_FAMP,			_mRSV55,
	_mNAND_CH1_auto_calib_NUM_L,		_mCH1_NAND_auto_calib_NUM_H,
	_mNAND_CH2_auto_calib_NUM_L,		_mCH2_NAND_auto_calib_NUM_H,
	_mNAND_CH1_auto_calib_CNT_L,		_mCH1_NAND_auto_calib_CNT_H,
	_mNAND_CH2_auto_calib_CNT_L,		_mCH2_NAND_auto_calib_CNT_H,
	_mNAND_CH1_AUTO_BLOCK_L,	_mNAND_CH1_AUTO_BLOCK_H,
	_mNAND_CH1_AUTO_PAGE,		_mRSV56,
	_mNAND_CH2_AUTO_BLOCK_L,	_mNAND_CH2_AUTO_BLOCK_H,
	_mNAND_CH2_AUTO_PAGE,		_mRSV57,
	_mECHOSAVE_CH2_SAVEMODE,	_mRSV58,
	_mECHOSAVE_CH2_SAVEINTERVAL,_mRSV59,
	_mAUTO_VOLT_DIFF_L,	_mAUTO_VOLT_DIFF_H,
	_mAUTO_VOLT_PEAK_L,		_mAUTO_VOLT_PEAK_H,
	_mAUTO_RANGE,		_mAUTO_THR_MIN,
	_mAUTO_THR_MAX,		_mNAND_CH1_CALIB_META_PAGE,
	_mNAND_CH2_CALIB_META_PAGE,		_mRSV60,
	_mNAND_CH1_CALIB_META_BLOCK_L,	_mNAND_CH1_CALIB_META_BLOCK_H,
	_mNAND_CH2_CALIB_META_BLOCK_L,	_mNAND_CH2_CALIB_META_BLOCK_H,
	_mAUTO_LEVEL_RANGE_L,			_mAUTO_LEVEL_RANGE_H,
	_mECHOSAVE_CH1_ECHO_VIEW_MODE,		_mECHOSAVE_CH2_ECHO_VIEW_MODE,
	_mAUTO_GAIN_CH1_FSLOPE,				_mAUTO_GAIN_CH2_FSLOPE,
	_mAUTO_GAIN_CH1_BEFORE_SLOPE_L,		_mAUTO_GAIN_BEFORE_CH1_SLOPE_H,
	_mAUTO_GAIN_CH2_BEFORE_SLOPE_L,		_mAUTO_GAIN_BEFORE_CH2_SLOPE_H,	
	_mAUTO_GAIN_CH1_SLOPE_XRANGE_L,		_mAUTO_GAIN_CH1_SLOPE_XRANGE_H,
	_mAUTO_GAIN_CH2_SLOPE_XRANGE_L,		_mAUTO_GAIN_CH2_SLOPE_XRANGE_H,
	_mAUTO_GAIN_CH1_BEFORE_MAX_L,		_mAUTO_GAIN_BEFORE_CH1_MAX_H,
	_mAUTO_GAIN_CH2_BEFORE_MAX_L,		_mAUTO_GAIN_BEFORE_CH2_MAX_H,	
	_mAUTO_GAIN_CH1_BEFORE_MIN_L,		_mAUTO_GAIN_BEFORE_CH1_MIN_H,
	_mAUTO_GAIN_CH2_BEFORE_MIN_L,		_mAUTO_GAIN_BEFORE_CH2_MIN_H,		
	_mAUTO_VOLT_MIN_L,				_mAUTO_VOLT_MIN_H,
	_mRSV61,
	_mRF_VERSION,		_mRF_VERSION_RSV,					// RF Version: 0=New, 1=Old(ENV110)
	_mMENU_END			= 0x00FFF,

	//--------------------------------------------------------------------------------------------------------------------------
	// Trend			0x10000 ~ 0x6FFFF	(393,216)
	//--------------------------------------------------------------------------------------------------------------------------
#if 1
	//START
	_mTREND_START       = _mMENU_END+1,
	// Header Information 	(0x10000 ~ 0x101FF) (2048)
	_mTrHDR_START  		= _mTREND_START,
	_mTrHDR_TYPE   		= _mTrHDR_START,
	_mTrHDR_SIZE_H,		_mTrHDR_SIZE_L,				
	_mTrHDR_INST,		_mTrHDR_RSV00,		
	_mTrHDR_MODEL,		_mTrHDR_RSV01,	
	_mTrHDR_SN3,		_mTrHDR_SN2,
	_mTrHDR_SN1,		_mTrHDR_SN0,
	_mTrHDR_SAV_OVF,		_mTrHDR_RSV02,
	_mTrHDR_DSP_RNG,		_mTrHDR_RSV03,
	_mTrHDR_SAV_CNT3,		_mTrHDR_SAV_CNT2,			
	_mTrHDR_SAV_CNT1,		_mTrHDR_SAV_CNT0,
	_mTrHDR_SAV_ADDR3,		_mTrHDR_SAV_ADDR2,			
	_mTrHDR_SAV_ADDR1,		_mTrHDR_SAV_ADDR0,
	_mTrHDR_DAT_BEGIN_YEAR,	_mTrHDR_DAT_BEGIN_MONTH,	
	_mTrHDR_DAT_BEGIN_DAY,	_mTrHDR_DAT_BEGIN_HOUR,
	_mTrHDR_DAT_BEGIN_MIN,	_mTrHDR_DAT_BEGIN_SEC,		
	_mTrHDR_DAT_FINIS_YEAR,	_mTrHDR_DAT_FINIS_MONTH,	
	_mTrHDR_DAT_FINIS_DAY,	_mTrHDR_DAT_FINIS_HOUR,
	_mTrHDR_DAT_END_MIN,	_mTrHDR_DAT_END_SEC,		
	_mTrHDR_END				= _mTrHDR_START + 0x001FF,
	// Header Reserved      (0x10200 ~ 0x107FF) 
	_mTrHDR_RSV_END			= 0x107FF,
	// Body	Information		(0x10800 ~ 0x68640) (360,600)
	_mTrBOD_START			= _mTrHDR_RSV_END+1,
	_mTrBOD_END				= _mTrBOD_START+MRM_SIZE_TRD_DAT,
	
	_mTREND_END				= 0x6FFFF,
#else
	//--------------------------------------------------------------------------------------------------------------------------
	// FONT				0x01000 ~ 0x6FFFF	(393,216)
	//--------------------------------------------------------------------------------------------------------------------------
	// Font - Start
	_mFONT_START		= _mMENU_END + 1,
	// Font - End
	_mFONT_END			= 0x6FFFF,
#endif
	//--------------------------------------------------------------------------------------------------------------------------
	// End Reserved		0x70000 ~ 0x7FFFF	(65,536)
	//--------------------------------------------------------------------------------------------------------------------------
	_mADDR_END			= 0x7FFFF
};


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------


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
extern U08  MRM_RdByte(U32 addr);
extern U16  MRM_RdWord(U32 addr);
extern U32  MRM_RdLong(U32 addr);
extern void MRM_RdBulk(U32 addr, U08* buf, U08 cnt);
// Set Local Variables
extern void MRM_WrByte(U32 addr, U08 data);
extern void MRM_WrWord(U32 addr, U16 data);
extern void MRM_WrLong(U32 addr, U32 data);
extern void MRM_WrBulk(U32 addr, U08* buf, U08 cnt);
// Operation
extern void MRM_InitVari(void);


#endif // ___RAM_MAIN_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

