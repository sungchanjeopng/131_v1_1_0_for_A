//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___NAND_MAIN_H___
#define ___NAND_MAIN_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "measure_calc.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
#define NAND_PAGE_SIZE			((U16)0x0800) /* 2 * 1024 bytes per page w/o Spare Area */
#define NAND_BLOCK_SIZE			((U16)0x0040) /* 64 pages per block */
#define NAND_PLANE_SIZE			((U16)0x0200) /* 512 Block per plane */
#define NAND_SPARE_AREA_SIZE	((U16)0x0040) /* last 64 bytes as spare area */
#define NAND_MAX_PLANE			((U16)0x0002) /* 2 planes of 512 block */


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------

typedef struct {
	U16 echo_main[1024];
	U16 block;
	U08 page;
	U16 num;
	U08 ch;
	
	U08 year;
	U08 month;
	U08 hour;
	U08 day;
	U08 min;
	U08 sec;

	U16 rslt_sldg[MsCAL_THR_TYPE_NUM];
	U16 rslt_dist[MsCAL_THR_TYPE_NUM];
	U16 trac_dist[MsCAL_THR_TYPE_NUM];

	U16 empty;
	U16 dead;
	U16 echo_amp;
	U16 thr[MsCAL_THR_TYPE_NUM];
	U16 asf[MsCAL_THR_TYPE_NUM];

	U16 each_slope_val[2][2];
	U16 each_thr_val[2][2];
	U16 each_slope;
	U16 result_slope;
	U16 result_echo_amp;
	U16 result_thr;
	U16 input_val;
	U16 output_val;

	U32 save_interval[APP_CH_NUM];
} NND_Echo;






//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------
#define _NAND_DP_DBG_


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------
extern NND_Echo nnd_echo;
extern U16 nand_auto_calib_num[APP_CH_NUM];
extern U16 nand_auto_calib_cnt[APP_CH_NUM];

extern U16 nand_echo_num[APP_CH_NUM];

extern U16 nand_auto_calib_block[APP_CH_NUM];
extern U16 nand_auto_calib_page[APP_CH_NUM];

extern U16 nand_meta_calib_block[APP_CH_NUM];
extern U16 nand_meta_calib_page[APP_CH_NUM];
extern U16 nand_auto_calib_sel[APP_CH_NUM];
extern U16 nand_auto_calib_sel_cnt[APP_CH_NUM];
#define nand_meta_calib_block_value 451
#define nand_meta_calib_block_range 10
//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get Local Variables
extern U16 NND_Meta_Getmain(U08 ch, U16 cnt, U08 idx);
extern U16 NND_Meta_GetEchocnt(U08 ch);
extern U16 NND_Meta_GetEchonum(U08 ch);
// Set Local Variables
// Operation
extern void NND_InitMain(void);

//extern void NND_ChkID(void);
extern void NND_Delete_Main(U08 ch);
extern void NND_Echo_buffer_Read(U16 cnt);
extern void NND_Echo_Save(U08 ch);
extern void NND_Echo_Read(U08 ch);
extern void BSP_NND_Read_Page_8b(U16 block, U16 page, U08 *pBuffer, U32 NumPage);
extern void BSP_NND_Write_Page_8b(U16 block, U16 page, U08 *pBuffer, U32 NumPage);
extern void BSP_NND_Read_Page_16b(U16 block, U16 page, U16 *pBuffer, U32 NumPage);
extern void BSP_NND_Write_Page_16b(U16 block, U16 page, U16 *pBuffer, U32 NumPage);
extern void BSP_NND_Read_SpareArea_8b(U32 page_no, U08 *pBuffer, U32 NumSpareArea);
extern void BSP_NND_Write_SpareArea_8b(U32 page_no, U08 *pBuffer, U32 NumSpareArea);
extern void BSP_NND_Read_SpareArea_16b(U16 block, U16 page, U16 *pBuffer, U32 NumPage);
extern void BSP_NND_Write_SpareArea_16b(U32 page_no, U16 *pBuffer, U32 NumSpareArea);
extern void BSP_NND_Erase_Block(U16 block, U16 page);

extern void NND_Echo_AutoGain_ProfSave(U08 ch, U08 gain);
extern void NND_Echo_AutoGain_RealSave(U08 ch, U08 gain, U08 cnt);

extern void NND_auto_calib_Read(U08 ch,U08 sel);
extern void NND_auto_calib_buffer_Read(U16 cnt);

extern void NND_Echo_ProcSave(void);
#endif // ___NAND_MAIN_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------


