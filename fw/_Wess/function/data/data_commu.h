//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2022-01-20 12:00:00 +0900 $ (From 2020-07-13)
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___OUTPUT_COMMU_H___
#define ___OUTPUT_COMMU_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "bsp_rtc.h"
#include "bsp_uart.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------

#define MDB_RX_BUF_SIZE 	20


#define MDB_RX_PKT_SIZE		20		// Packet Buffer Size
#define MDB_TX_PKT_SIZE		12		// Packet Buffer Size

#define MB_CRC16_POLYNORMIAL    0xa001
// Secsor Index
enum {
	COM_CH_0 = 0,
	COM_CH_1,
	COM_CH_NUM,
};


#if 0
enum {
	MDB_PKT_00_SLAVE = 0,
	MDB_PKT_01_CMD,
	MDB_PKT_02_NULL,
	MDB_PKT_03_ADDR,
	MDB_PKT_04_NULL,
	MDB_PKT_05_SIZE,
	MDB_PKT_06_CLC_LO,
	MDB_PKT_07_CLC_HI,
};
#endif

enum {
	MDB_RX_00_SLAVE = 0,
	MDB_RX_01_CMD,
	MDB_RX_02_ADDR_H,
	MDB_RX_03_ADDR_L,
	MDB_RX_04_NULL,
	MDB_RX_05_SIZE,
	MDB_RX_06_CRC_LO,
	MDB_RX_07_CRC_HI,
};



enum {
	MDB_TX_00_SLAVE = 0,
	MDB_TX_01_CMD,
	MDB_TX_02_SIZE,
	MDB_TX_03_VALUE_HI,
	MDB_TX_04_VALUE_LO,
	MDB_TX_05_CRC_LO,
	MDB_TX_06_CRC_HI,
};



enum {
	MDB_CMD_00_ = 0,
	MDB_CMD_01_,
	MDB_CMD_02_,
	MDB_CMD_03_REQ_READ,
	MDB_CMD_04_,
	MDB_CMD_05_,
};

enum {
	MDB_ADDR_00_CH1_LIGHT = 0,
	MDB_ADDR_01_CH1_HEAVY = 1,	
	MDB_ADDR_02_CH2_LIGHT = 2,
	MDB_ADDR_03_CH2_HEAVY = 3,		
	MDB_ADDR_09_CH1_TMPRT = 9,
	MDB_ADDR_10_CH2_TMPRT = 10,
};

//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	RTC_TM time;		// Box - Time

} COM_LS;





typedef struct {
	U08 buf_cnt;
	U08 interrupt_buf[URT_IDX_MAX][MDB_RX_BUF_SIZE];
	U08 rx_buf[URT_IDX_MAX][MDB_RX_BUF_SIZE];
	U08 crc_lo;
	U08 crc_hi;
	U08 tx_buf[MDB_TX_PKT_SIZE];
	U08 tx_level[MDB_TX_PKT_SIZE];
	U08 tx_tmprt[MDB_TX_PKT_SIZE];
	U16 tx_crc;

	U08 value_buf[100];
	U08 f_rx[URT_IDX_MAX];
	U08 ota_fble;
} COM_MDB;



typedef struct {
	U32 tx_cnt;
} RF_LS;



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
// Set
extern void DaMdb_SetRxBuff(URT_IDX idx, U08 dr);



//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern void DaCOM_InitMain(void);
extern void DaCOM_ProcMain(void);
extern U08 Mdb_Getcrclo(void);
extern void DaBT_SetRxBuff(URT_IDX idx, U08 dr);
extern void DaBT_InItMain(void);
extern void DaBT_ProcMain(void);
extern U08 gBle_found_baud;
extern U08 DaBT_GetConnected(void);
extern void DaMdb_ProcMain(void);
extern void DaWrf_ProcMain_Old(void);


#endif // ___OUTPUT_COMMU_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

