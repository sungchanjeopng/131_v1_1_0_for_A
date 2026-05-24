//------------------------------------------------------------------------------------------------------------------------------
//  NAND Stub for A hardware (no NAND chip)
//  All NAND functions are no-ops. Auto-calib/auto-gain runs in memory only,
//  no persistence across reboot.
//------------------------------------------------------------------------------------------------------------------------------

#include "bsp_nand.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Variable stubs (referenced by other modules)
//------------------------------------------------------------------------------------------------------------------------------
NND_Echo nnd_echo;
U16 nand_auto_calib_num[APP_CH_NUM];
U16 nand_auto_calib_cnt[APP_CH_NUM];
U16 nand_echo_num[APP_CH_NUM];
U16 nand_auto_calib_block[APP_CH_NUM];
U16 nand_auto_calib_page[APP_CH_NUM];
U16 nand_meta_calib_block[APP_CH_NUM];
U16 nand_meta_calib_page[APP_CH_NUM];
U16 nand_auto_calib_sel[APP_CH_NUM];
U16 nand_auto_calib_sel_cnt[APP_CH_NUM];

//------------------------------------------------------------------------------------------------------------------------------
//  Function stubs (no-op)
//------------------------------------------------------------------------------------------------------------------------------
U16 NND_Meta_Getmain(U08 ch, U16 cnt, U08 idx)	{ (void)ch; (void)cnt; (void)idx; return 0; }
U16 NND_Meta_GetEchocnt(U08 ch)					{ (void)ch; return 0; }
U16 NND_Meta_GetEchonum(U08 ch)					{ (void)ch; return 0; }

void NND_InitMain(void)							{ }
void NND_ChkID(void)							{ }
void NND_Delete_Main(U08 ch)					{ (void)ch; }
void NND_Echo_buffer_Read(U16 cnt)				{ (void)cnt; }
void NND_Echo_Save(U08 ch)						{ (void)ch; }
void NND_Echo_Read(U08 ch)						{ (void)ch; }
void NND_Echo_ProcSave(void)					{ }

void NND_auto_calib_Read(U08 ch, U08 sel)		{ (void)ch; (void)sel; }
void NND_auto_calib_buffer_Read(U16 cnt)		{ (void)cnt; }

void NND_Echo_AutoGain_ProfSave(U08 ch, U08 gain)				{ (void)ch; (void)gain; }
void NND_Echo_AutoGain_RealSave(U08 ch, U08 gain, U08 cnt)		{ (void)ch; (void)gain; (void)cnt; }

void BSP_NND_Read_Page_8b(U16 block, U16 page, U08 *pBuffer, U32 NumPage)		{ (void)block; (void)page; (void)pBuffer; (void)NumPage; }
void BSP_NND_Write_Page_8b(U16 block, U16 page, U08 *pBuffer, U32 NumPage)		{ (void)block; (void)page; (void)pBuffer; (void)NumPage; }
void BSP_NND_Read_Page_16b(U16 block, U16 page, U16 *pBuffer, U32 NumPage)		{ (void)block; (void)page; (void)pBuffer; (void)NumPage; }
void BSP_NND_Write_Page_16b(U16 block, U16 page, U16 *pBuffer, U32 NumPage)		{ (void)block; (void)page; (void)pBuffer; (void)NumPage; }
void BSP_NND_Read_SpareArea_8b(U32 page_no, U08 *pBuffer, U32 NumSpareArea)		{ (void)page_no; (void)pBuffer; (void)NumSpareArea; }
void BSP_NND_Write_SpareArea_8b(U32 page_no, U08 *pBuffer, U32 NumSpareArea)	{ (void)page_no; (void)pBuffer; (void)NumSpareArea; }
void BSP_NND_Read_SpareArea_16b(U16 block, U16 page, U16 *pBuffer, U32 NumPage)	{ (void)block; (void)page; (void)pBuffer; (void)NumPage; }
void BSP_NND_Write_SpareArea_16b(U32 page_no, U16 *pBuffer, U32 NumSpareArea)	{ (void)page_no; (void)pBuffer; (void)NumSpareArea; }
void BSP_NND_Erase_Block(U16 block, U16 page)									{ (void)block; (void)page; }
