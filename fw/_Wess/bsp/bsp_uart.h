//--------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use,
//  copying, transfer or disclosure of such information is prohibited except by express written
//  agreement with WESS-Global Co.,LTD
//
//  $Date: 2022-05-26 12:00:00 +0900 $
//--------------------------------------------------------------------------------------------------

#ifndef ___BSP_UART_H___
#define ___BSP_UART_H___

//--------------------------------------------------------------------------------------------------
//  Includes
//--------------------------------------------------------------------------------------------------
#include "app_sys.h"


//--------------------------------------------------------------------------------------------------
//  Constant definitions
//--------------------------------------------------------------------------------------------------

#define URT_BR_9600     9600
#define URT_BR_19200    19200
#define URT_BR_38400    38400
#define URT_BR_115200   115200



//--------------------------------------------------------------------------------------------------
//  Type definitions
//--------------------------------------------------------------------------------------------------
typedef enum {
    URT_IDX_1 = 0,	// Only RS232, Debug Port
	URT_IDX_2,		// Only RS485, Output Port
	URT_IDX_RF,

    URT_IDX_MAX,
}URT_IDX;

typedef struct
{
	U08 buf_cnt;
}URT_PARAM;

typedef struct
{
	URT_PARAM rx_param[URT_IDX_MAX];
}URT_LS;
//--------------------------------------------------------------------------------------------------
//  Macros
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------
//  Local variables
//--------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
//  Extern global variables
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
//  Extern global APIs
//--------------------------------------------------------------------------------------------------
#if 0
extern U08 URT_GetBuf_cnt(URT_IDX idx);	
extern U08 URT_GetBuf(URT_IDX idx, U08 buf_idx);
extern U08* URT_GetAddr(URT_IDX idx);		
#endif
extern void URT_InitMain(U08 idx, U32 br);
extern void URT_TxPkt(U08 idx, U08* args, U08 size);
extern void _ISR_URT_Callback(URT_IDX idx, U08 rdr);

//extern void URT_DbgPrintf(URT_IDX idx, U08* c_str);

#endif // ___BSP_UART_H___

// EOF


