//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DISP_STRING_H___
#define ___DISP_STRING_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "menu_main.h"
#include "fonts.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	I08 sYnN[MENU_CHK_NUM][64];		// No  / Yes
	I08 sOnF[MENU_CHK_NUM][64];		// Off / On
	I08 sMethod[MENU_CHK_NUM][8];	// Average / Last
	I08 Text_list[16];
} DpSTR_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Common
//------------------------------------------------------------------------------------------------------------------------------
#define _sYes			"Yes"
#define _sNo			"No"
#define _sEnable		"Enable"
#define _sENABLE		"ENABLE"
#define _sDisable		"Disable"
#define _sDISABLE		"DISABLE"
#define _sOn			"On"
#define _sON			"ON"
#define _sOff			"Off"
#define _sOFF			"OFF"
#define _sDot3			"..."

#define _sCheck			"Check"
#define _sStart			"Start"
#define _sRst			"Reset"
#define _sStop			"Stop"
#define _sDone			"Done ! !"

#define _sMIN			"M I N"
#define _sMAX			"MAX"

#define _sMin			"Min"
#define _sMax			"Max"
#define _sX				"X"
#define _sY				"Y"


#define _sSec_			"sec"
#define _sMin_			"min"
#define _sNOW_			"NOW"
#define _sCm_			"cm"

#define _sTim_1Sec		"1  sec"
#define _sTim_10Sec		"10  sec"
#define _sTim_1Min		"1  min"
#define _sTim_10Min		"10  min"
#define _sTim_1Hrs		"1  hour"
#define _sTim_24Hrs		"24  hour"

#define _sTim_12Hrs		"12  hour"
#define _sTim_5Day		"5  Day"
#define _sTim_10Day		"10  Day"
#define _sTim_30Day		"30  Day"
#define _sTim_60Day		"60  Day"



#define _sM_E_N_U		"M E N U"
#define _sMENU_OUTP		"M E N U  >  OUTPUT"

#define _sRpt_PrsKeep	">  Repeat:  Keep  Press"
#define _sExit_Prskey	">  Push  'EXIT'  or  OK,  to  Exit  Window"
#define _sSel_PsSet		">  Select  &  Push  'SET'"
#define _sCau_MsrRst	">  CAUTION:   Meas.'s  Prameters  Reset  !"
#define _sCaut_Reset	">  CAUTION:   All  Data  Reset  !"
#define _sOnOff_SttSt	">  'ON':  Start   /   'OFF':  Stop"


//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Button
//------------------------------------------------------------------------------------------------------------------------------
#define _sEXIT			"EXIT"
#define _sBACK			"BACK"
#define _sFUNC			" FN "
#define _sNEXT			"NEXT"
#define _sMENU			"MENU"
#define _sSAVE			"SAVE"
#define _sSET			"SET"
#define _sOK			"OK"

//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Screen (Hybrid)
//------------------------------------------------------------------------------------------------------------------------------
// Title
#define _sSldgLvlMtr	"Sludge   Level   Meter"
#define _sLEVEL			"LEVEL"
#define _sUNIT			"UNIT"
#define _sSS_DEP		"SENSOR    DEPTH"
#define _sTK_DEP		"TANK    DEPTH"
#define _sDEADZN		"DEADZONE"
// Contents
#define _sSludge		"Sludge"
#define _sDist			"Distance"
#define _sMeter			"Meter"
#define _sFeet			"Feet"
#define _sT_Dep			"T.Depth"			// Tank Depth
#define _sS_Dep			"S.Depth"			// Sensor /epth
#define _sDEADZ			"D.Zone"
#define _sFS_Loc		"FS.Loc."			// Field Structure - Location
#define _sFS_Dir		"FS.Dir."			// Field Structure - Direction
#define _sFS_Vel		"FS.Vel."			// Field Structure - Velocity
#define _sLocation		"Location"			// Field Structure - Location
#define _sDirection		"Direction"			// Field Structure - Direction
#define _sVelocity		"Velocity"		// Field Structure - Velocity
#define _sCurr			"Current"
#define _sCh_1			"ch   1"
#define _sCh_2			"ch   2"
#define _sCH_1			"CH   1"
#define _sCH_2			"CH   2"
#define _sDIFF_AVRG		"DIFF  /  AVRG"
// Massage
#define _sNG			"N G"
#define _sND			"N.D"
#define _sTBD			"TBD"
#define _sNotYet		"Not   Yet"
// FieldA
#if 0
#define _sDirection		"Direction"
#define _sVelocity		"Velocity"
#define _sPosition      "Position"
#endif
#define _sLeft			"Left"
#define _sRight			"Right"

#define _sCh_1TO0        "ch 2 -> ch 1"
#define _sCh_0TO1        "ch 1 -> ch 2"


//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Screen (Echo)
//------------------------------------------------------------------------------------------------------------------------------
#define _sECHO			"ECHO"
#define _sECHO_REAL		"Real time ECHO"
#define _sECHO_AVG		"Average ECHO"
#define _sLayer			"Layer"
#define _sTHRHD			"THRESHOLD"
#define _sThrhd			"Threshold"
#define _sCH1_THRHD		"CH1 THRESHOLD"
#define _sCH1_Thrhd		"CH1 Threshold"
#define _sCH2_THRHD		"CH2 THRESHOLD"
#define _sCH2_Thrhd		"CH2 Threshold"
#define _sASF_VAL		"ASF   VALUE"
#define _sASF_Val		"ASF   Value"
#define _sASF_LIGHT		"ASF   Light"
#define _sASF_HEAVY		"ASF   Heavy"
#define _sReal			"Real"
#define _sReal_Avg		"Real/Avg."
#define _sREAL_AVG		"REAL/AVG."
#define _sEcho_Amp      "Echo Amp"
#define _sThr_light		"Thr. Light"
#define _sThr_heavy		"Thr. Heavy"
#define _sASF			"ASF:"


#if 1
#define _sTRK_WID       "TR.   WIDTH"
#else
#define _sTRK_WID		"TRCKING   WID."
#endif
#define _sTRK_Wid		"TR.   Width"
#define _sProf_N		"Profile   N."
#define _sPROF_N		"PROFILE   N."
#define _sDamp_N		"Damp.   N."
#define _sDAMP_N		"DAMP.   N."
#define _sOFFS			"OFFSET"
#define _sOffs			"Offset"
#define _sFREQ			"FREQ."
#define _sFREQ			"FREQ."


//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Screen (Calibration)
//------------------------------------------------------------------------------------------------------------------------------
#define _sCALIBRATION	"CALIBRATION"
#define _sCalibration	"Calibration"
#define _sCalib			"Calib."
#define _sTX_WAV		"TX.   WAVE"
#define _sTxWave		"Tx.   Wave"
#define _sRX_AMP		"RX.   AMP"
#define _sRxAmp			"Rx.   Amp"
#define _sRX_GAIN		"RX.   GAIN"
#define _sRxGain		"Rx.   Gain"
#define _sRX_TRANS		"RX.   TRANS"
#define _sRxTrans		"Rx.   Trans"
#define _sTVG			"TVG"
#define _sTVG_Mode		"TVG	Mode"
#define _sTVG_MODE		"TVG	MODE"
#define _sTVG_CUSTOM	"TVG    CUSTOM"
#define _sTVG_Custom	"TVG    Custom"
#define _sConfig		"Config."


//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Screen (Information)
//------------------------------------------------------------------------------------------------------------------------------
#define _sINFO			"INFORMATION"
#define _sCptCyc		"Capture   Cycle"
#define _sCptMtd		"Capture   Method"
#define _sRxAMP			"Rx.   AMP"
#define _sRxGain		"Rx.   Gain"
#define _sRsmTim		"Resume Time"

#define _siNF_FREQ		"Frequency (kHz)"
#define _siNF_Offset	"Offset (m)"
#define _sINF_4_20mA	"4 / 20 mA (m)"
#define _sINF_msr_cyc	"Measure Cycle (s)"
#define _sINF_DAMP		"Damping"
#define _sINF_TVG		"TVG"
//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Menu (Measurement)
//------------------------------------------------------------------------------------------------------------------------------
#define _sMEAS			"MEASUREMENT"
#define _sMeas			"Measurement"
// Section
#define _sBase			"Base"
#define _sFieldA		"FieldA"
#define _sAlarm			"Alarm"
// Item
#define _sUnit			"Unit"
#define _sCH1_OPER		"CH1 Operation"
#define _sCH1_EMPTY		"CH1 Empty"
#define _sCH1_DEADZONE	"CH1 Dead Zone"
#define _sCH1_MEASURE_CYCLE "CH1 Measure Cycle"
#define _sCH1_MEASURE_RESET	"CH1 Measure Reset"
#define _sCH2_OPER		"CH2 Operation"
#define _sCH2_EMPTY		"CH2 Empty"
#define _sCH2_DEADZONE	"CH2 Dead Zone"
#define _sCH2_MEASURE_CYCLE "CH2 Measure Cycle"
#define _sCH2_MEASURE_RESET	"CH2 Measure Reset"

#define _sOperation "Operation"
#define _sEmpty 	"Empty"
#define _sDeadzone	"Dead Zone"
#define _sMeasure_cycle "Measure Cycle"
#define _sMeasure_reset "Measure Reset"

#define _sAddress		"Address"

#define _sCH1_FREQ		"CH1 Frequency"
#define _sCH1_ECHO_AMP	"CH1 Echo Amp"
#define _sCH1_THR_HEAVY "CH1 Thr. Heavy"
#define _sCH1_THR_LIGHT	"CH1 Thr. Light"
#define _sCH1_ASF_LIGHT	"CH1 ASF  Light"
#define _sCH1_ASF_HEAVY	"CH1 ASF  Heavy"
#define _sCH1_DAMPING 	"CH1 Damping"
#define _sCH1_OFFSET	"CH1 Offset"
#define _sCH2_FREQ		"CH2 Frequency"
#define _sCH2_ECHO_AMP	"CH2 Echo Amp"
#define _sCH2_THR_HEAVY "CH2 Thr. Heavy"
#define _sCH2_THR_LIGHT	"CH2 Thr. Light"
#define _sCH2_ASF_LIGHT	"CH2 ASF  Light"
#define _sCH2_ASF_HEAVY	"CH2 ASF  Heavy"
#define _sCH2_DAMPING 	"CH2 Damping"
#define _sCH2_OFFSET	"CH2 Offset"

#define _sFrequency "Frequency"
#define _sEcho_Amp	"Echo Amp"
#define _sDamping	"Damping"
#define _sOffset	"Offset"

#define _sAUTO			"Auto"
#define _sMANUAL		"Manual"

#define _sCYCLE			"CYCLE"
#define _sCycle			"Cycle"
#define _sMETHOD		"METHOD"
#define _sMethod		"Method"
#define _sREFILT		"RE-FILTERING"
#define _sReFilt		"Re-filtering"
#define _sMSR_RST		"Measurement    RESET"
#define _sMsr_Rst		"Reset"
#define _sRUN			"RUN"
#define _sRun			"Run"
#define _sTEMP 			"TEMP COMP."
#define _sTemp			"Temp Comp."

#define _sFieldA_Run	 "FieldA   Run"
#define _sFIELDA_RUN	 "FIELDA   RUN"

// Method Type
#define _sAVG			"AVERAGE"
#define _sLAST			"LAST"

//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Menu (Output)
//------------------------------------------------------------------------------------------------------------------------------
#define _sOUTP			"OUTPUT"
#define _sOutp			"Output"
// Section
#define _sRelay			"Relay"
#define _sPCD			"Clean"
#define _sErr			"Error"
// Current
#define _sCH1_Assign	"CH1 Assign"
#define _sCH2_Assign	"CH2 Assign"
#define _sCH1_ASSIGN	"CH1 Assign"
#define _sCH2_ASSIGN	"CH2 Assign"


#define _sCH1_SET_04mA	"CH1 SET   4mA"
#define _sCH1_Set_04mA	"CH1 Set   4mA"
#define _sCH1_SET_20mA	"CH1 SET   20mA"
#define _sCH1_Set_20mA	"CH1 Set   20mA"
#define _sCH1_TRM_04mA	"CH1 TRIM   4mA"
#define _sCH1_Trm_04mA	"CH1 Trim   4mA"
#define _sCH1_TRM_12mA	"CH1 TRIM   12mA"
#define _sCH1_Trm_12mA	"CH1 Trim   12mA"
#define _sCH1_TRM_20mA	"CH1 TRIM   20mA"
#define _sCH1_Trm_20mA	"CH1 Trim   20mA"
#define _sCH1_OUT_04mA 	"CH1 OUT   4mA"
#define _sCH1_Out_04mA	"CH1 Out   4mA"

#define _sCH2_SET_04mA	"CH2 SET   4mA"
#define _sCH2_Set_04mA	"CH2 Set   4mA"
#define _sCH2_SET_20mA	"CH2 SET   20mA"
#define _sCH2_Set_20mA	"CH2 Set   20mA"
#define _sCH2_TRM_04mA	"CH2 TRIM   4mA"
#define _sCH2_Trm_04mA	"CH2 Trim   4mA"
#define _sCH2_TRM_12mA	"CH2 TRIM   12mA"
#define _sCH2_Trm_12mA	"CH2 Trim   12mA"
#define _sCH2_TRM_20mA	"CH2 TRIM   20mA"
#define _sCH2_Trm_20mA	"CH2 Trim   20mA"
#define _sCH2_OUT_04mA 	"CH2 OUT   4mA"
#define _sCH2_Out_04mA	"CH2 Out   4mA"

#define _sLight			"Light"
#define _sHeavy			"Heavy"

#define _sLight_level	"Light Level (m)"
#define _sHeavy_level	"Heavy Level (m)"

#define _sEmpty_Title	"Empty (m)"
#define _sCurrent_Title	"Current (mA)"
#define _sCH1_Current_Title	"CH1 Current (mA)"
#define _sCH2_Current_Title	"CH2 Current (mA)"


#define _sCH1_Light		"CH1 Light"
#define _sCH1_Heavy		"CH1 Heavy"
#define _sCH2_Light		"CH2 Light"
#define _sCH2_Heavy		"CH2 Heavy"

#define _sDiff			"Difference"
#define _sAvg			"Average"
// Relay
#define _sASSIGN		"ASSIGN"
#define _sAssign		"Assign"
#define _sACT			"ACT"
#define _sAct			"Act"
#define _sSTOP			"STOP"
#define _sStop			"Stop"
#define _sTEST			"TEST"
#define _sTest			"Test"

// PCD
#define _sMode		"Mode"
#define _sIntv		"Interval"
#define _sINTV		"Interval"
#define _sTerm		"Term"
#define _sTERM		"Term"
// Error
#define _sHoldTim		"Holding   t."
#define _sHOLDTIME		"Holding   time"
#define _sErr_Delay		"Error Delay"
#define _sErr_Output	"Error Output"
#define _sCURRENT		"CURRENT"
#define _sHold			"Hold"
#define _s3_8mA			"3.8 mA"
#define _s21_0mA		"21.0 mA"


//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Menu (Data)
//------------------------------------------------------------------------------------------------------------------------------
#define _sDATA			"DATA"
#define _sData			"Data"
// Section
#define _sSAVE			"SAVE"
#define _sSave			"Save"
#define _sCmnctn		"Comm."
// Save
#define _sSAV_ENABLE	"ENABLE"
#define _sSAV_Enable	"Enable"
#define _sSAV_ASSIGN	"ASSIGN"
#define _sSAV_Assign	"Assign"
#define _sSAV_INTV		"Saving Interval"
#define _sSAV_Intv		"Saving Interval"
#define _sSAV_DOWN		"DOWNLOAD"
#define _sSAV_Down		"Download"
#define	_sSAV_DEL		"DELETE"
#define _sSAV_Del		"Delete"
#define _sDisplay_term	"Display Term"
// Communication
#define _sCOM_Type		"Type"
#define _sCOM_Protocol	"Protocol"
#define _sCOM_Baud		"Baudrate"
#define _sCOM_Addr		"Address"
#define _sCOM_RF		"RF"
#define _sCOM_Std		"Standard"
#define _sCOM_Mdb		"Modbus"
#define _sCOM_FidA		"FieldA"
#define _sCOM_Br4800	"4800"
#define _sCOM_Br9600	"9600"
#define _sCOM_Br19200	"19200"
#define _sCOM_Br115200	"115200"

#define _sCH1_Address	"CH1 Address"
#define _sCH2_Address	"CH2 Address"
//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Menu (System)
//------------------------------------------------------------------------------------------------------------------------------
#define _sSYST			"SYSTEM"
#define _sSyst			"System"
#define _sPasscode		"Passcode"
#define _sCH1_SITE_NAME	"CH1 Site Name"
#define _sCH2_SITE_NAME "CH2 Site Name"
#define _sSITE_NAME		"Site Name"
#define _sRTN_TIM		"RETURN   TIME"
#define _sRtnTim		"Return  Time"
#define _sFTR_RST		"FACTORY    RESET"
#define _sFtrRst		"Factory  RES"
#define _sTIME			"TIME"
#define _sTime			"Time"
#define _sLANG			"LANGUAGE"
#define _sLang			"Language"

#define _sAlarm_timer	"Alarm  Timer"
#define _sAlarm_reset	"Alarm  Reset"

//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Menu (Engineer)
//------------------------------------------------------------------------------------------------------------------------------
#define _sEGNR			"ENGINEER"
#define _sEgnr			"Engineer"
//#define _sTHR_MIN		"THRESHOLD MIN"
#define _sThr_Min		"Threshold Min"
#define _sSmooth_Num	"Smooth Num"
#define _sSMOOTH_NUM	"SMOOTH NUM"
#define _sSmooth_Range	"Smooth Range"
#define _sSMOOTH_RANGE	"SMOOTH RANGE"
#define _sDP_DBG		"DISPLAY    DEBUG"
#define _sDpDbg			"Disp.  Debug"
#define _sDP_ECHO		"DISPLAY    ECHO"
#define _sDpEcho		"Disp.  Echo"
#define _sRX_BPF		"RX    BPF"
#define _sRx_BPF		"Rx    BPF"

#define _sThr_Sync		"Threshold Sync"
#define _sCH1_Profile	"CH1 Profile No."
#define _sCH1_TVG		"CH1 TVG"
#define _sCH1_Window_Reset_Time "CH1 Window Reset Time"
#define _sCH1_Window_Range		"CH1 Window Range"
#define _sCH2_Profile	"CH2 Profile No."
#define _sCH2_TVG		"CH2 TVG"
#define _sCH2_Window_Reset_Time "CH2 Window Reset Time"
#define _sCH2_Window_Range		"CH2 Window Range"
#define _sStruct_MSR			"MSR"

//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Menu (Factory)
//------------------------------------------------------------------------------------------------------------------------------
#define _sFCTR			"FACTORY"
#define _sFctr			"Factory"
#define _sSS_TYPE		"SENSOR    TYPE"
#define _sCHNNL			"CHANNEL"
#define _sChnl			"Channel"
#define _sSingle		"Single"
#define _sDual			"Dual"
#define _sMulti			"Multi"
#define _sCfg4mA		"Config. 4mA"
#define _sCfg20mA		"Config. 20mA"
#define _sCFG_4mA		"CONFIG. 4mA"
#define _sCFG_20mA		"CONFIG. 20mA"
#define _sCH0_4mA		"CH1   4mA"
#define _sCH0_20mA		"CH1   20mA"
#define _sCH1_4mA		"CH2   4mA"
#define _sCH1_20mA		"CH2   20mA"
#define _sTest			"Test"

//------------------------------------------------------------------------------------------------------------------------------
//  Macros - Menu (Test)
//------------------------------------------------------------------------------------------------------------------------------
#define _sHW_RX_AMP		"HW Rx AMP"
#define _sCH1_SMOOTH_NUM	"CH1  Smooth No."
#define _sCH1_SMOOTH_RANGE	"CH1  Smooth Range"
#define _sCH1_THRESHOLD_RANGE	"CH1 Thr. Range"
#define _sCH1_THRESHOLD_MIN		"CH1 Thr. Min"
#define _sCH1_PULSE_NUM			"CH1 Pulse No."
#define _sCH1_ECHO_AMP_B		"CH1 Echo AMP B"
#define _sCH2_SMOOTH_NUM		"CH2  Smooth No."
#define _sCH2_SMOOTH_RANGE		"CH2  Smooth Range"
#define _sCH2_THRESHOLD_RANGE	"CH2 Thr. Range"
#define _sCH2_THRESHOLD_MIN		"CH2 Thr. Min"
#define _sCH2_PULSE_NUM			"CH2 Pulse No."
#define _sCH2_ECHO_AMP_B		"CH2 Echo AMP B"

#define _filter_range	 "Filter Range"
#define _sJdg_Hei_Out	 "Judge   Height  Out"
#define _sJDG_HEI_OUT	 "JUDGE   Height  OUT"
#define _filter_time	 "Filter Time"
#define _sNext_Wait_Time "Next   Wait   Time"
#define _sNEXT_WAIT_TIME "NEXT   WAIT   TIME"
#define _sSensor_Distance "Sensor   Distance"
#define _sSENSOR_DISTANCE "SENSOR   DISTANCE"
#define _sJudge_Cycle	  "Judge   Cycle"
#define _sJUDGE_CYCLE	  "JUDGE   CYCLE"
#define _sEcho_Download	  "Echo Download"
#define _sDebug_Mode	  "Debug  Mode"


enum {
	TEXT_LIST_ECHO_AMP = 0,
	TEXT_LIST_THR_LIGHT,
	TEXT_LIST_THR_HEAVY,
	TEXT_LIST_FREQ,
	TEXT_LIST_OFFSET,
	TEXT_LIST_DAMPING,
	TEXT_LIST_CH_1,
	TEXT_LIST_CH_2,
	TEXT_LIST_LIGHT_LEVEL,
	TEXT_LIST_HEAVY_LEVEL,
	TEXT_LIST_EMPTY,
	TEXT_LIST_CURRENT,
	TEXT_LIST_CH1_CURRENT,
	TEXT_LIST_CH2_CURRENT,
	TEXT_LIST_MAX_VALUE,
	TEXT_LIST_MIN_VALUE,
	TEXT_LIST_TIME,
	TEXT_LIST_SLUDGE_LEVEL_METER,
	TEXT_LIST_TANK_SCREEN,
	TEXT_LIST_REAL_ECHO_SCREEN,
	TEXT_LIST_AVG_ECHO_SCREEN,
	TEXT_LIST_PARAMETER_SCREEN,
	TEXT_LIST_DATA_TREND_SCREEN,
	TEXT_LIST_MENU,
	TEXT_LIST_EXIT,
	TEXT_LIST_BACK,
	TEXT_LIST_NEXT,
	TEXT_LIST_SAVE,
	TEXT_LIST_SET,
	TEXT_LIST_OK,
	TEXT_LIST_FUNC,
	TEXT_LIST_SLUDGE_COLLECTOR,
	TEXT_LIST_SLUDGE_COLLECTOR_DETECT,
	TEXT_LIST_DIRECTION,
	TEXT_LIST_POSITION,
	TEXT_LIST_VELOCITY,

	TEXT_LIST_UNIT,
	TEXT_LIST_CH1_OPERATION,
	TEXT_LIST_CH1_EMPTY,
	TEXT_LIST_CH1_DEADZONE,
	TEXT_LIST_CH1_MSR_CYC,
	TEXT_LIST_CH1_MSR_RST,
	TEXT_LIST_CH2_OPERATION,
	TEXT_LIST_CH2_EMPTY,
	TEXT_LIST_CH2_DEADZONE,
	TEXT_LIST_CH2_MSR_CYC,
	TEXT_LIST_CH2_MSR_RST,

	TEXT_LIST_OPERATION,
	TEXT_LIST_DEADZONE,
	TEXT_LIST_MSR_CYC,
	TEXT_LIST_MSR_RST,

	TEXT_LIST_CH1_FREQ,
	TEXT_LIST_CH1_ECHO_AMP,
	TEXT_LIST_CH1_THR_HEAVY,
	TEXT_LIST_CH1_THR_LIGHT,
	TEXT_LIST_CH1_HEAVY,
	TEXT_LIST_CH1_LIGHT,	
	TEXT_LIST_CH1_ASF_VALUE,
	TEXT_LIST_CH1_DAMP,
	TEXT_LIST_CH1_OFFSET,
	TEXT_LIST_CH2_FREQ,
	TEXT_LIST_CH2_ECHO_AMP,
	TEXT_LIST_CH2_THR_HEAVY,
	TEXT_LIST_CH2_THR_LIGHT,
	TEXT_LIST_CH2_HEAVY,
	TEXT_LIST_CH2_LIGHT,		
	TEXT_LIST_CH2_ASF_VALUE,
	TEXT_LIST_CH2_DAMP,
	TEXT_LIST_CH2_OFFSET,	

	TEXT_LIST_CH1_ASSIGN,
	TEXT_LIST_CH1_SET,
	TEXT_LIST_CH1_TRIM,
	TEXT_LIST_CH1_OUTPUT,
	TEXT_LIST_CH2_ASSIGN,
	TEXT_LIST_CH2_SET,
	TEXT_LIST_CH2_TRIM,
	TEXT_LIST_CH2_OUTPUT,


	TEXT_LIST_ASSIGN,
	TEXT_LIST_ACT,
	TEXT_LIST_STOP,
	TEXT_LIST_TEST,

	TEXT_LIST_MODE,
	TEXT_LIST_INTV,
	TEXT_LIST_TERM,

	TEXT_LIST_ERROR_DELAY,
	TEXT_LIST_ERROR_OUTPUT,

	TEXT_LIST_SAVE_INTV,
	TEXT_LIST_DOWNLOAD,
	TEXT_LIST_DELETE,
	TEXT_LIST_DISPLAY_TERM,
	
	TEXT_LIST_PROTOCL,
	TEXT_LIST_BAUDRATE,
	TEXT_LIST_ADDRESS,
	TEXT_LIST_CH1_ADDRESS,
	TEXT_LIST_CH2_ADDRESS,
	TEXT_LIST_PASSCODE,
	TEXT_LIST_LANG,
	TEXT_LIST_RETURN_MEAS,
	TEXT_LIST_CH1_SITE_NAME,
	TEXT_LIST_CH2_SITE_NAME,
	TEXT_LIST_SITE_NAME,
	TEXT_LIST_FACTORY_RESET,

	TEXT_LIST_CH1_PROFILE_NO,
	TEXT_LIST_CH1_TVG,
	TEXT_LIST_CH1_WINDOW_RESET_TIME,
	TEXT_LIST_CH1_WINDOW_RANGE,
	TEXT_LIST_CH2_PROFILE_NO,
	TEXT_LIST_CH2_TVG,
	TEXT_LIST_CH2_WINDOW_RESET_TIME,
	TEXT_LIST_CH2_WINDOW_RANGE,	

	TEXT_LIST_THR_SYNC,
	TEXT_LIST_MSR,

	TEXT_LIST_MEASUREMENT,
	TEXT_LIST_BASE,
	TEXT_LIST_CALIBRATION,
	TEXT_LIST_OUTPUT,
	TEXT_LIST_CURRENT_MENU,
	TEXT_LIST_RELAY,
	TEXT_LIST_CLEAN,
	TEXT_LIST_ERROR,
	TEXT_LIST_DATA,
	TEXT_LIST_COMM,
	TEXT_LIST_SYSTEM,
	TEXT_LIST_ENGINEER,
	TEXT_LIST_FACTORY,
	TEXT_LIST_TEST_MENU,

	TEXT_LIST_SLUDGE,
	TEXT_LIST_DISTANCE,
	TEXT_LIST_AUTO,
	TEXT_LIST_MANUAL,
	TEXT_LIST_LIGHT,
	TEXT_LIST_HEAVY,

	TEXT_LIST_HOLD,
	TEXT_LIST_ALARM,
	TEXT_LIST_RESET,

	TEXT_LIST_YES,
	TEXT_LIST_NO,
	TEXT_LIST_ON,
	TEXT_LIST_OFF,
	TEXT_LIST_TIMER,

	TEXT_LIST_KOREAN,
	TEXT_LIST_ENGLISH,

	TEXT_LIST_NUM,
};

//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------
extern DpSTR_LS gDpStr;

//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get Local Variables
// Set Local Variables
// Operation - Initial
extern void DpSTR_InitMain(void);
// Operation - Live
extern void DpSTR_LiveLft(U16 x0, U16 y0, U32 col_fw, U32 col_bg, sFONT ft, I08 *pStr);
// Operation - Draw for Flip
extern void DpSTR_TitleBar_KOR(I08* pStr, U16 x0, U32 col);
extern void DpSTR_TitleBar(I08* pStr, U16 x0, U32 col);
extern void DpSTR_GuiLeft_KOR(U16 x0, U16 y0, U32 col_fw, U32 col_bg, sFONT ft, I08 *pStr);
extern void DpSTR_GuiList(U08 iIt);
extern void DpSTR_GuiLeft(U16 x0, U16 y0, U32 col_fw, U32 col_bg, sFONT ft, I08 *pStr);
extern void DpSTR_GuiLeftCursor(U16 x0, U16 y0, U32 col_fw, U32 col_fw_cursor, U32 col_bg, U08 cursor, sFONT ft, I08 *pStr);
// Operation - for Debug
extern void DpSTR_DebugMsr(void);
extern void DpSTR_DebugExp(U08 xn, U08 yn, I08* pStr);

extern void DpSTR_DebugExp_2(U08 y, I08* pStr);

#endif // ___DISP_STRING_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

