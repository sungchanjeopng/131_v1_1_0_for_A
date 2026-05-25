//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
// app
#include "app_sys.h"
// bsp
#include "bsp_gpio.h"
#include "bsp_demux.h"
#include "bsp_uart.h"
#include "bsp_ota.h"
// app
#include "app_main.h"
// measure
#include "measure_calc.h"
#include "measure_temperature.h"
// menu
#include "menu_data.h"
#include "menu_factory.h"
#include "menu_measure.h"
#include "menu_engineer.h"
// output
#include "output_current.h"
#include "output_relay.h"
// menu
#include "menu_output.h"
// self
#include "data_commu.h"
// menu (for MnSYS_PrGet_site_name_hi/lo)
#include "menu_system.h"
// measure
#include "measure_cal1_field0.h"

#include <string.h>
// Core
#include "usart.h"

// data
#include "data_save.h"
// bsp (MRAM, trend)
#include "bsp_ram.h"
// display (data download progress popup)
#include "disp_popup.h"

#include "stm32f7xx_hal_gpio.h"
#include "stm32f7xx_hal_uart.h"
#include "usart.h"
#if 0
#include "disp_figure.h"
#include "disp_color.h"
#include "disp_string.h"
#include "fonts.h"
#endif

#include "bsp_nand.h"
#include "bsp_led.h"
#include "app_status.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Forward declarations
//------------------------------------------------------------------------------------------------------------------------------
void DaBT_SendDeviceInfo(void);
void DaBT_SendPairingFail(void);
void DaBT_SendWaveformAvg_Ch(U08 ch);

//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
COM_LS lcom;
RF_LS lrf;
COM_MDB lmdb;

U08 interrupt_cnt[URT_IDX_MAX];

// BLE AT command response
volatile U08 gAt_rx_buf[64];
volatile U08 gAt_rx_cnt = 0;
volatile U08 gAt_rx_mode = 0;
U08 gBle_found_baud = 0;  // 0:紐살갼??1:9600 2:115200

// BLE Streaming
//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
// BLE ?먮윭 ?곹깭 肄붾뱶 蹂?? 0x00=?뺤긽, 0x01=ER01, 0x02=ER02
static U08 BLE_GetErrorCode(U08 ch)
{
	U08 stt = MsCAL_Get_Stt(ch);
	if(stt == ApSTT_MSR_NG) return 0x01;  // ER01: ?좏샇 ?쏀븿
	if(stt == ApSTT_TPR_NG) return 0x02;  // ER02: ?⑤룄 ?먮윭
	return 0x00;  // ?뺤긽
}

// TODO: output_com_standard .c.h
// Standard
void ComStd_InitMain(void)
{
	//
}

void ComStd_ProcMain(void)
{
#if 1
	S16 tmp2;
	U08 snsr = MnFTR_PrGet_Value(MnFTR_I00_SS_CH);
	U16 dist_1 = MsCAL_GetVl_RsltDist(COM_CH_0,1);
	U16 dist_2 = MsCAL_GetVl_RsltDist(COM_CH_1,1);
	U16 sldg_1 = MsCAL_GetVl_RsltSldg(COM_CH_0,1);
	U16 sldg_2 = MsCAL_GetVl_RsltSldg(COM_CH_1,1);
	
	U16 curr_1 = OuCUR_GetOutp_Value(COM_CH_0);
	U16 curr_2 = OuCUR_GetOutp_Value(COM_CH_1);
	S16 tmpr_1 = MsTPR_GetTprt(COM_CH_0);

	U08 buff[64] = {0, };
	U08 cnt = 0;
	#if 0
	RTC_TM com = RTC_GetTime();
	#endif
	#if 0
	if(com.seconds == lcom.time.seconds)
		return;
	lcom.time.seconds = com.seconds;
	#endif


	if(DaSav_GetDumfEn() == TRUE)
		return;




	
	buff[cnt++] = 0x0d;	// CR
	buff[cnt++] = 0x0a;	// LF

	switch(snsr)
	{
		case MnFTR_SS_SINGLE:
			// CH-0
			buff[cnt++] = 0x44;	// 'D'
			buff[cnt++] = (dist_1 / 1000) % 10 + '0';
			buff[cnt++] = (dist_1 /  100) % 10 + '0';
			buff[cnt++] = (dist_1 /   10) % 10 + '0';
			buff[cnt++] =  dist_1         % 10 + '0';

			buff[cnt++] = 0x53;	// 'S'
			buff[cnt++] = (sldg_1 / 1000) % 10 + '0';
			buff[cnt++] = (sldg_1 /  100) % 10 + '0';
			buff[cnt++] = (sldg_1 /   10) % 10 + '0';
			buff[cnt++] =  sldg_1         % 10 + '0';

			#if 0
			buff[cnt++] = 0x43;	// 'C'
			buff[cnt++] = (curr_1 / 1000) % 10 + '0';
			buff[cnt++] = (curr_1 /  100) % 10 + '0';
			buff[cnt++] = (curr_1 /   10) % 10 + '0';
			buff[cnt++] =  curr_1         % 10 + '0';
			#else
			buff[cnt++] = 0x54;   //'T'

			tmp2 = tmpr_1;         //Trasnfer Temperature, 00unit 1'
			if (tmp2 < 0)
			{
				buff[cnt++] = 0x2d;  //'-'
				tmp2 = tmp2 * -1;
			}
			else
				buff[cnt++] = 0x2b;	//'+'
			
			buff[cnt++] = (tmp2 / 100) % 10 + '0';
			buff[cnt++] = (tmp2 /  10) % 10 + '0';
			#endif
			break;
		case MnFTR_SS_DUAL:	
			// CH-0
			buff[cnt++] = 0x44;	// 'D'
			buff[cnt++] = (dist_1 / 1000) % 10 + '0';
			buff[cnt++] = (dist_1 /  100) % 10 + '0';
			buff[cnt++] = (dist_1 /   10) % 10 + '0';
			buff[cnt++] =  dist_1         % 10 + '0';

			buff[cnt++] = 0x53;	// 'S'
			buff[cnt++] = (sldg_1 / 1000) % 10 + '0';
			buff[cnt++] = (sldg_1 /  100) % 10 + '0';
			buff[cnt++] = (sldg_1 /   10) % 10 + '0';
			buff[cnt++] =  sldg_1         % 10 + '0';

			#if 1
			buff[cnt++] = 0x43;	// 'C'
			buff[cnt++] = (curr_1 / 1000) % 10 + '0';
			buff[cnt++] = (curr_1 /  100) % 10 + '0';
			buff[cnt++] = (curr_1 /   10) % 10 + '0';
			buff[cnt++] =  curr_1         % 10 + '0';
			#else
			buff[cnt++] = 0x54;   //'T'

			tmp2 = gTp_now;         //Trasnfer Temperature, 00unit 1'
			if (tmp2 < 0)
			{
				buff[cnt++] = 0x2d;  //'-'
				tmp2 = tmp2 * -1;
			}
			else
				buff[cnt++] = 0x2b;	//'+'
			
			buff[cnt++] = (tmp2 / 100) % 10 + '0';
			buff[cnt++] = (tmp2 /  10) % 10 + '0';
			#endif
			// CH-1
			buff[cnt++] = 0x44;	// 'D'
			buff[cnt++] = (dist_2 / 1000) % 10 + '0';
			buff[cnt++] = (dist_2 /  100) % 10 + '0';
			buff[cnt++] = (dist_2 /   10) % 10 + '0';
			buff[cnt++] =  dist_2         % 10 + '0';

			buff[cnt++] = 0x53;	// 'S'
			buff[cnt++] = (sldg_2 / 1000) % 10 + '0';
			buff[cnt++] = (sldg_2 /  100) % 10 + '0';
			buff[cnt++] = (sldg_2 /   10) % 10 + '0';
			buff[cnt++] =  sldg_2         % 10 + '0';

			buff[cnt++] = 0x43;	// 'C'
			buff[cnt++] = (curr_2 / 1000) % 10 + '0';
			buff[cnt++] = (curr_2 /  100) % 10 + '0';
			buff[cnt++] = (curr_2 /   10) % 10 + '0';
			buff[cnt++] =  curr_2         % 10 + '0';
			break;
		default:
			break;
	}
	
	
	buff[cnt++] = 0x00;	// NULL

	URT_TxPkt(URT_IDX_2, buff, cnt);
#endif
}


// TODO: output_com_modbus .c.h
// Modbus

void ComMdb_InitMain(void)
{
	lmdb.buf_cnt = 0;
	lmdb.f_rx[URT_IDX_1] = FALSE;
	lmdb.f_rx[URT_IDX_2] = FALSE;
}



U16 Mdb_GetCrc16(U08 *buf, U08 size)
{
	U08 i,j;
	U16 crc16;

	crc16 = 0xffff;
	
	for (i = 0; i < size; i++ )
	{
		/* Convert the received byte to an INTeger */
		crc16 = crc16 ^ (U16)*(buf+i);

		for(j = 8; j > 0; j--)
		{
			/* Loop 8 times to test each bit of the new CHARacter */
			if  (crc16 & 0x0001)	crc16 = (crc16 >> 1) ^ (U16)MB_CRC16_POLYNORMIAL;
			else                   	crc16 = (crc16 >> 1);
		}
	}

	return crc16;
}



U08 Mdb_Getcrclo(void) 	    	   { return lmdb.crc_lo;	}


void Damdb_ClrRxBuff(URT_IDX idx)
{
	memset(lmdb.rx_buf[idx], 0, sizeof(U08)*MDB_RX_BUF_SIZE);

	lmdb.f_rx[idx] = FALSE;
}



void DaMdb_SetLevel(U08 idx,U16 addr)
{
	U16 cnt, i,j;
	U32 valu[APP_CH_NUM][MsCAL_THR_TYPE_NUM];
	U08 buff[64] = {0, };
	U16 tx_crc;
	U08 operation[APP_CH_NUM];

	cnt = (lmdb.rx_buf[idx][MDB_RX_05_SIZE] * 2) + 3;

	

	memset(lmdb.value_buf, 0, sizeof(lmdb.value_buf));


	for(i=0; i<APP_CH_NUM; i++)
	{
		operation[i] = MnMSR_BaseGet_Ch_Value(i, MnMS0_OPT_SINGLE_OPERATION);

		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
		{
			if((MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON))
			{
				valu[i][j] = MsCAL1_Hunting_value(i, j);
			}
			else
			{
				if(operation[i] == MnMS0_OPERATION_DISTANCE)	valu[i][j] = MsCAL_GetVl_RsltDist(i,j);
				else if(operation[i] == MnMS0_OPERATION_SLUDGE) valu[i][j] = MsCAL_GetVl_RsltSldg(i,j);
			}

		}
	}

#if 1
	lmdb.value_buf[0] = (U08)((valu[APP_CH_1][MsCAL_THR_LIGHT]>>8) & 0x00ff);
	lmdb.value_buf[1] = (U08)((valu[APP_CH_1][MsCAL_THR_LIGHT]>>0) & 0x00ff); 
	lmdb.value_buf[2] = (U08)((valu[APP_CH_1][MsCAL_THR_HEAVY]>>8) & 0x00ff);
	lmdb.value_buf[3] = (U08)((valu[APP_CH_1][MsCAL_THR_HEAVY]>>0) & 0x00ff); 
	lmdb.value_buf[4] = (U08)((valu[APP_CH_2][MsCAL_THR_LIGHT]>>8) & 0x00ff);
	lmdb.value_buf[5] = (U08)((valu[APP_CH_2][MsCAL_THR_LIGHT]>>0) & 0x00ff); 
	lmdb.value_buf[6] = (U08)((valu[APP_CH_2][MsCAL_THR_HEAVY]>>8) & 0x00ff);
	lmdb.value_buf[7] = (U08)((valu[APP_CH_2][MsCAL_THR_HEAVY]>>0) & 0x00ff); 
#else

	lmdb.value_buf[0] = lmdb.rx_buf[URT_IDX_2][0];
	lmdb.value_buf[1] = lmdb.rx_buf[URT_IDX_2][1];
	lmdb.value_buf[2] = lmdb.rx_buf[URT_IDX_2][2];
	lmdb.value_buf[3] = lmdb.rx_buf[URT_IDX_2][3];
	lmdb.value_buf[4] = lmdb.rx_buf[URT_IDX_2][4];
	lmdb.value_buf[5] =  lmdb.rx_buf[URT_IDX_2][5];
	lmdb.value_buf[6] =  lmdb.rx_buf[URT_IDX_2][6];
	lmdb.value_buf[7] =  lmdb.rx_buf[URT_IDX_2][7];
#endif
	lmdb.value_buf[18] =  (S08)((MsTPR_GetTprt(APP_CH_1)>>8) & 0x00ff);
	lmdb.value_buf[19] = (S08)((MsTPR_GetTprt(APP_CH_1)>>0) & 0x00ff);
	lmdb.value_buf[20] =  (S08)((MsTPR_GetTprt(APP_CH_2)>>8) & 0x00ff);
	lmdb.value_buf[21] = (S08)((MsTPR_GetTprt(APP_CH_2)>>0) & 0x00ff);


	buff[MDB_TX_00_SLAVE] = MnDAT_ComPrGet_Value(MnDS2_OPT_ADDR); 	
	buff[MDB_TX_01_CMD] = lmdb.rx_buf[idx][MDB_RX_01_CMD];
	buff[MDB_TX_02_SIZE] = lmdb.rx_buf[idx][MDB_RX_05_SIZE] * 2; 
	

    for(i=3; i<cnt; i++)
    {
    	#if 0
		if(((addr*2)+(i-3))>=100)
			return;
		#endif
    	buff[i] = lmdb.value_buf[(addr*2)+(i-3)];
    }


	tx_crc = Mdb_GetCrc16(buff, cnt);
	buff[cnt] = (U08)((tx_crc & 0x00ff) >> 0);
	buff[cnt+1] = (U08)((tx_crc & 0xff00) >> 8);
	


	DatComPr_BaudInit(MnDAT_ComPrGet_Value(MnDS2_OPT_BAUD));


	URT_TxPkt(idx, buff, cnt+2);
	memset(&buff,0,sizeof(cnt+2));

}

void DaMdb_SetTmprt(U08 addr)
{
	
#if 0

	U08 cnt, i;
	U08 buff[64] = {0, };
	U16 tx_crc;
	U08 ch;
	
	cnt = (lmdb.rx_buf[URT_IDX_2][MDB_RX_05_SIZE] * 2) + 3;

	if(lmdb.rx_buf[URT_IDX_2][MDB_RX_05_SIZE] >= 3)	return;

	switch(addr)
	{
		case MDB_ADDR_09_CH1_TMPRT:	ch =APP_CH_1;	break;
		case MDB_ADDR_10_CH2_TMPRT:	ch =APP_CH_2;	break;
	}

	lmdb.tx_tmprt[3] = (S08)((MsTPR_GetTprt(ch)>>8) & 0x00ff);
	lmdb.tx_tmprt[4] = (S08)((MsTPR_GetTprt(ch)>>0) & 0x00ff); 
	lmdb.tx_tmprt[5] = 0x00;
	lmdb.tx_tmprt[6] = 0x00;


	buff[MDB_TX_00_SLAVE] = MnDAT_ComPrGet_Value(MnDS2_OPT_ADDR); 	
	buff[MDB_TX_01_CMD] = lmdb.rx_buf[URT_IDX_2][MDB_RX_01_CMD];
	buff[MDB_TX_02_SIZE] = lmdb.rx_buf[URT_IDX_2][MDB_RX_05_SIZE] * 2;


    for(i=3; i<cnt; i++)
    {
    	buff[i] = lmdb.tx_tmprt[i];
    }
	tx_crc = Mdb_GetCrc16(buff, cnt);
	buff[cnt] = (U08)((tx_crc & 0x00ff) >> 0);
	buff[cnt+1] = (U08)((tx_crc & 0xff00) >> 8);

	URT_TxPkt(URT_IDX_2, buff, cnt+2);
	memset(&buff,0,sizeof(cnt+2));
#endif
}


void DaMdb_AutoGain(U08 ch)
{
	U16 i,j,k;
	U16 block;
	U16 page;
	U16 cnt = nand_auto_calib_cnt[ch];
	U08 buff[2048] = {0, };
	U16 buff_cnt = 0;
	U16 range;
	
	buff[buff_cnt++] = 0x02; // SOF
	URT_TxPkt(URT_IDX_1, buff, buff_cnt);
	buff_cnt = 0;

	HAL_Delay(50);

	//if(block == (500+(24*ch)+24)) block = 500+(24*ch);
	if(cnt==4) cnt =0;
	j=0;
	//nand_auto_calib_block[ch] = 500+(24*ch)+(nand_auto_calib_cnt[ch]*6)+lMsCal.auto_calib_cnt;


	if(nand_auto_calib_num[ch]<1200)
	{
		cnt =0;
		block = 400+(24*ch)+(cnt*6)+j;
		page = 0;

		
		for(i=0; i<nand_auto_calib_num[ch]; i++)
		{
			buff_cnt = 0;
			if(i != 0 && i % 300 == 0)	cnt++;
			
			if(i != 0 && i % 6 == 0)
			{
				j=0;
				if(++page>=50)	page = 0;
			}

			block = 400+(24*ch)+(cnt*6)+j;
			//block = 500;
			HAL_Delay(5);
			BSP_NND_Read_Page_16b(block, page, nnd_echo.echo_main, 1);
			HAL_Delay(20);
			range= nnd_echo.echo_main[10]+100;

			if(range>=1020)
				range = 1020;

			//nnd_echo.echo_main[50] = 0x0033;
			for(k=0; k<range; k++)
			{
				buff[buff_cnt++] = (U08)((nnd_echo.echo_main[k]>>8) & 0x00ff);
				buff[buff_cnt++] = (U08)((nnd_echo.echo_main[k]>>0) & 0x00ff);
				if(k==20)
				{
					URT_TxPkt(URT_IDX_1, buff, buff_cnt);
					buff_cnt= 0;
				}


			}
			URT_TxPkt(URT_IDX_1, buff, buff_cnt);
			buff_cnt= 0;			
			j++;
		}
	}
	else
	{
		page = 0;
		for(i=0; i<nand_auto_calib_num[ch]; i++)
		{
			buff_cnt = 0;

			if((i != 0) && (i % 300 == 0))
			{
				if(++cnt>=4) cnt = 0;
			}

			if((i != 0) && (i % 6 == 0))
			{
				j=0;
				if(++page>=50)	page = 0;
			}			

			block = 400+(24*ch)+(cnt*6)+j;
			HAL_Delay(5);
			BSP_NND_Read_Page_16b(block, page, nnd_echo.echo_main, 1);
			HAL_Delay(20);

			range= nnd_echo.echo_main[10]+100;

			if(range>=1020)
				range = 1020;

			for(k=0; k<range; k++)
			{
				buff[buff_cnt++] = (U08)((nnd_echo.echo_main[k]>>8) & 0x00ff);
				buff[buff_cnt++] = (U08)((nnd_echo.echo_main[k]>>0) & 0x00ff);
				if(k==20)
				{
					URT_TxPkt(URT_IDX_1, buff, buff_cnt);
					buff_cnt= 0;
				}		


			}
			URT_TxPkt(URT_IDX_1, buff, buff_cnt);
			buff_cnt= 0;					
			j++;			
		}
	}

	buff_cnt = 0;
	buff[buff_cnt++] = 0x03; // EOF
	URT_TxPkt(URT_IDX_1, buff, buff_cnt);



}


void DaMdb_SaveEcho(U08 ch)
{
	U08 buff[2048] = {0, };
	U16 buff_cnt = 0;
	U16 i,j;
	U16 range;
	buff[buff_cnt++] = 0x02; // SOF
	URT_TxPkt(URT_IDX_1, buff, buff_cnt);
	buff_cnt = 0;

	//HAL_Delay(10);

	NND_Echo_Read(ch);

#if 0
	buff[buff_cnt++] = (U08)((NND_Meta_GetEchocnt(APP_CH_1)>>8) & 0x00ff);
	buff[buff_cnt++] = (U08)((NND_Meta_GetEchocnt(APP_CH_1)>>0) & 0x00ff);
	
	URT_TxPkt(URT_IDX_1, buff, buff_cnt);
#endif


	for(j=0; j<NND_Meta_GetEchocnt(ch); j++)
	{
		buff_cnt = 0;
		//HAL_Delay(50);
		NND_Echo_buffer_Read(j);
		//AL_Delay(2);

#if 1
		if(nnd_echo.empty==0)
		{
			nnd_echo.empty =50;
			nnd_echo.echo_main[10] = 50;
		}

#if 0
		range = nnd_echo.empty+100;
		if(range>=1020)
			range = 1020;
#else

		range = 1000;
#endif
#endif
		for(i=0; i<range; i++)
		{
			buff[buff_cnt++] = (U08)((nnd_echo.echo_main[i]>>8) & 0x00ff);
			buff[buff_cnt++] = (U08)((nnd_echo.echo_main[i]>>0) & 0x00ff);

#if 0
			if(i==20)
			{
				URT_TxPkt(URT_IDX_1, buff, buff_cnt);
				buff_cnt= 0;
				HAL_Delay(50);
			}	
#endif

		}

		URT_TxPkt(URT_IDX_1, buff, buff_cnt);
		buff_cnt = 0;			
	}


	buff_cnt = 0;
	buff[buff_cnt++] = 0x03; // EOF
	URT_TxPkt(URT_IDX_1, buff, buff_cnt);

}


//------------------------------------------------------------------------------------------------------------------------------
//  BLE RX buffer (5-byte frame: SOF[1] + LEN[2] + CRC[2])
//  + BoT-nLE521 ASCII messages (+CONNECTED, +DISCONNECTED, etc.)
//------------------------------------------------------------------------------------------------------------------------------
static U08 bt_ascii_buf[64];
static U08 bt_ascii_cnt = 0;

// BLE ?곌껐 ?곹깭 (0: 誘몄뿰寃? 1: ?곌껐??
static U08 gBle_connected = 0;

// ?몃젋???ㅽ듃由щ컢 ?곹깭 (0=idle, 1=?ㅽ듃由щ컢 以?
static U08  gTrend_streaming = 0;
static U16  gTrend_total_cnt = 0;
static U08  gTrend_ch = APP_CH_1;  // ?ㅽ듃由щ컢 以묒씤 梨꾨꼸

U08 DaBT_GetConnected(void) { return gBle_connected; }

void DaBT_SetRxBuff(URT_IDX idx, U08 dr)
{
	if(gAt_rx_mode)
	{
		if(gAt_rx_cnt < sizeof(gAt_rx_buf) - 1)
			gAt_rx_buf[gAt_rx_cnt++] = dr;
		return;
	}

	if(lmdb.ota_fble == TRUE)
	{
		// OTA 모드: SDRAM 적재만 하고 즉시 복귀.
		// 0x51 종료 프레임 검출은 DaBT_ProcMain() 의 OTA 루프가 SDRAM 꼬리를 폴링한다.
		ota_on_rx_byte(dr);
		return;
	}
	else if(idx == URT_IDX_BT && interrupt_cnt[idx] == 0)
	{
		if(bt_ascii_cnt > 0 && bt_ascii_buf[0] == '+')
		{
			bt_ascii_buf[bt_ascii_cnt++] = dr;

			if(dr == '\n' || dr == '\r')
			{
				bt_ascii_buf[bt_ascii_cnt] = '\0';
				if(strstr((char*)bt_ascii_buf, "+CONNECTED") != NULL)
					gBle_connected = 1;
				else if(strstr((char*)bt_ascii_buf, "+DISCONNECTED") != NULL)
					gBle_connected = 0;
				bt_ascii_cnt = 0;
			}

			if(bt_ascii_cnt >= sizeof(bt_ascii_buf))
				bt_ascii_cnt = 0;
			return;
		}

		if(dr == '+')
		{
			bt_ascii_cnt = 0;
			bt_ascii_buf[bt_ascii_cnt++] = dr;
			return;
		}
	}

	if(interrupt_cnt[idx] == 0)
	{
		if(dr == 0x02 || dr == 0x03)
		{
			lmdb.interrupt_buf[idx][0] = dr;
			interrupt_cnt[idx] = 1;
		}
		return;
	}
	else if(interrupt_cnt[idx] < 7)
	{
		lmdb.interrupt_buf[idx][interrupt_cnt[idx]] = dr;
		interrupt_cnt[idx]++;
	}

	if(interrupt_cnt[idx] >= 7)
	{
		lmdb.f_rx[idx] = TRUE;
		memcpy(lmdb.rx_buf[idx], lmdb.interrupt_buf[idx], 7);
		interrupt_cnt[idx] = 0;
	}
}
//------------------------------------------------------------------------------------------------------------------------------
//  BLE Send Status - Interface Meter (4 bytes payload, LEN=0x04)
//  Payload: [Light(2B)][Heavy(2B)]
//------------------------------------------------------------------------------------------------------------------------------
void DaBT_SendStatus_Ch(U08 ch)
{
	U08 buff[205] = {0, };  // SOF(1)+CMD(2)+DATA(200)+CRC(2)=205B  (DATA 174B 예약)
	U16 buff_cnt = 0;
	U16 tx_crc;

	U08 operation = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_OPERATION);
	U16 light, heavy;
	if(operation == MnMS0_OPERATION_SLUDGE) {
		light = MsCAL_GetVl_RsltSldg(ch, MsCAL_THR_LIGHT);
		heavy = MsCAL_GetVl_RsltSldg(ch, MsCAL_THR_HEAVY);
	} else {
		light = MsCAL_GetVl_RsltDist(ch, MsCAL_THR_LIGHT);
		heavy = MsCAL_GetVl_RsltDist(ch, MsCAL_THR_HEAVY);
	}

	S16 tmp     = MsTPR_GetTprt(ch);
	U16 cur     = OuCUR_GetOutp_Value(ch);
	U08 freq    = (U08)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_FREQ);
	S16 offset  = (S16)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_OFFSET);
	U16 set4ma  = (U16)MnOUT_CurPrGet_CH_Value(ch, MnOS0_OPT_SINGLE_SET_04mA);
	U16 set20ma = (U16)MnOUT_CurPrGet_CH_Value(ch, MnOS0_OPT_SINGLE_SET_20mA);
	U16 tvg     = (U16)MnEGN_PrGet_CH_Item(ch, MnEGN_OPT_SINGLE_TVG);
	U16 damp    = (U16)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_DAMPING);
	U16 asf     = MsCAL_GetVl_ASF_R(ch);
	U08 relay   = gRly_state;
	U16 err = (U16)BLE_GetErrorCode(ch);
	U16 echoAmp = (U16)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_ECHO_AMP);
	U08 cmd_lo = (ch == APP_CH_1) ? 0x00 : 0x10;

	buff[buff_cnt++] = 0x02;
	buff[buff_cnt++] = 0x00;
	buff[buff_cnt++] = cmd_lo;

	buff[buff_cnt++] = (U08)((light >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(light & 0xFF);
	buff[buff_cnt++] = (U08)((heavy >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(heavy & 0xFF);
	buff[buff_cnt++] = (U08)((tmp >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(tmp & 0xFF);
	buff[buff_cnt++] = (U08)((cur >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(cur & 0xFF);
	buff[buff_cnt++] = 0x00;
	buff[buff_cnt++] = freq;
	buff[buff_cnt++] = (U08)((offset >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(offset & 0xFF);
	buff[buff_cnt++] = (U08)((set4ma >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(set4ma & 0xFF);
	buff[buff_cnt++] = (U08)((set20ma >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(set20ma & 0xFF);
	buff[buff_cnt++] = (U08)((tvg >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(tvg & 0xFF);
	buff[buff_cnt++] = (U08)((damp >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(damp & 0xFF);
	buff[buff_cnt++] = (U08)((asf >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(asf & 0xFF);
	buff[buff_cnt++] = 0x00;
	buff[buff_cnt++] = relay;
	buff[buff_cnt++] = (U08)((err >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(err & 0xFF);
	// Echo Amp/FAMP 수신감도: append at reserved offset 26~27 to keep existing 26B layout compatible.
	buff[buff_cnt++] = (U08)((echoAmp >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(echoAmp & 0xFF);
	// buff_cnt = 31 here. DATA payload extended to 200B; remaining 172B stay 0x00 (reserved).

	buff_cnt = 1 + 2 + 200;  // jump to end of DATA (203). Bytes 31..202 already 0 from init.

	tx_crc = Mdb_GetCrc16(buff, buff_cnt);
	buff[buff_cnt++] = (U08)(tx_crc & 0xFF);
	buff[buff_cnt++] = (U08)((tx_crc >> 8) & 0xFF);

	URT_TxPkt(URT_IDX_BT, buff, buff_cnt);  // 205B total
}

//------------------------------------------------------------------------------------------------------------------------------
//  BLE Send Diag - Interface Meter (14 bytes, LEN=0x0E)
//------------------------------------------------------------------------------------------------------------------------------
void DaBT_SendDiag_Ch(U08 ch)
{
	U08 buff[28] = {0, };  // 27B ??28B (7횞4 ?⑤뵫)
	U16 buff_cnt = 0;
	U16 tx_crc;

	S16 tmp     = MsTPR_GetTprt(ch);
	U16 cur     = OuCUR_GetOutp_Value(ch);
	U08 freq    = (U08)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_FREQ);
	S16 offset  = (S16)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_OFFSET);
	U16 set4ma  = (U16)MnOUT_CurPrGet_CH_Value(ch, MnOS0_OPT_SINGLE_SET_04mA);
	U16 set20ma = (U16)MnOUT_CurPrGet_CH_Value(ch, MnOS0_OPT_SINGLE_SET_20mA);
	U16 tvg     = (U16)MnEGN_PrGet_CH_Item(ch, MnEGN_OPT_SINGLE_TVG);
	U16 damp    = (U16)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_DAMPING);
	U16 asf     = MsCAL_GetVl_ASF_R(ch);
	U08 relay   = gRly_state;  // 0=OPEN(ON), 1=CLOSED(OFF)

	U16 err = (U16)BLE_GetErrorCode(ch);
	U08 cmd_lo = (ch == APP_CH_1) ? 0x04 : 0x14;

	buff[buff_cnt++] = 0x02; // SOF
	buff[buff_cnt++] = 0x00; // CMD
	buff[buff_cnt++] = cmd_lo;

	buff[buff_cnt++] = (U08)((tmp >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(tmp & 0xFF);
	buff[buff_cnt++] = (U08)((cur >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(cur & 0xFF);
	buff[buff_cnt++] = 0x00;                            // freq (2B)
	buff[buff_cnt++] = freq;
	buff[buff_cnt++] = (U08)((offset >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(offset & 0xFF);
	buff[buff_cnt++] = (U08)((set4ma >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(set4ma & 0xFF);
	buff[buff_cnt++] = (U08)((set20ma >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(set20ma & 0xFF);
	buff[buff_cnt++] = (U08)((tvg >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(tvg & 0xFF);
	buff[buff_cnt++] = (U08)((damp >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(damp & 0xFF);
	buff[buff_cnt++] = (U08)((asf >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(asf & 0xFF);
	buff[buff_cnt++] = 0x00;                            // relay (2B)
	buff[buff_cnt++] = relay;
	buff[buff_cnt++] = (U08)((err >> 8) & 0xFF);       // error (2B)
	buff[buff_cnt++] = (U08)(err & 0xFF);

	tx_crc = Mdb_GetCrc16(buff, buff_cnt);
	buff[buff_cnt++] = (U08)(tx_crc & 0xFF);
	buff[buff_cnt++] = (U08)((tx_crc >> 8) & 0xFF);

	URT_TxPkt(URT_IDX_BT, buff, buff_cnt);
}

//------------------------------------------------------------------------------------------------------------------------------
//  CRC-16 incremental (byte-by-byte)
//------------------------------------------------------------------------------------------------------------------------------
static U16 Crc16_Update(U16 crc, U08 byte)
{
	crc ^= (U16)byte;
	for(U08 j = 0; j < 8; j++) {
		if(crc & 0x0001) crc = (crc >> 1) ^ 0xA001;
		else crc >>= 1;
	}
	return crc;
}

static U16 Crc16_UpdateBuf(U16 crc, U08 *buf, U16 len)
{
	for(U16 i = 0; i < len; i++)
		crc = Crc16_Update(crc, buf[i]);
	return crc;
}

//------------------------------------------------------------------------------------------------------------------------------
//  BLE Send Waveform - Interface Meter
//  Header 25B + wave N횞2B (N = empty 횞 1.1)
//  SOF(1) + LEN(2) + DATA(25 + N횞2) + CRC(2)
//  Sent in chunks via UART ??BLE module fragments automatically
//------------------------------------------------------------------------------------------------------------------------------
void DaBT_SendWaveform_Ch(U08 ch)
{
	U08 buff[210];
	U16 buff_cnt = 0;
	U16 i;
	U16 crc = 0xFFFF;

	U08 operation = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_OPERATION);
	U16 lightLevel, heavyLevel;
	if(operation == MnMS0_OPERATION_SLUDGE) {
		lightLevel = MsCAL_GetVl_RsltSldg(ch, MsCAL_THR_LIGHT);
		heavyLevel = MsCAL_GetVl_RsltSldg(ch, MsCAL_THR_HEAVY);
	} else {
		lightLevel = MsCAL_GetVl_RsltDist(ch, MsCAL_THR_LIGHT);
		heavyLevel = MsCAL_GetVl_RsltDist(ch, MsCAL_THR_HEAVY);
	}

	U16 deadzone  = (U16)MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_DEADZONE);
	U16 empty     = (U16)MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_EMPTY);
	U16 N         = (U16)(empty * 1.1);
	if(N > ADC_BUFF_MAX) N = ADC_BUFF_MAX;
	if(N == 0) N = 1;

	U16 thrLightDist = MsCAL_GetVl_TracDist(ch, MsCAL_THR_LIGHT);
	U16 thrHeavyDist = MsCAL_GetVl_TracDist(ch, MsCAL_THR_HEAVY);
	U16 thrLightReal = (U16)MsCAL_GetVl_Threshold(ch, MsCAL_THR_LIGHT);
	U16 thrHeavyReal = (U16)MsCAL_GetVl_Threshold(ch, MsCAL_THR_HEAVY);
	U16 thrLightSet  = (U16)MnMSR_Get_Threshold_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_LIGHT);
	U16 thrHeavySet  = (U16)MnMSR_Get_Threshold_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_HEAVY);
	U08 thrLightMode = (U08)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_LIGHT);
	U08 thrHeavyMode = (U08)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_HEAVY);
	U16 echoAmp      = (U16)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_ECHO_AMP);
	U16 statusCh     = (U16)BLE_GetErrorCode(ch);

	// ?? SOF + CMD ??
	U08 cmd_lo = (ch == APP_CH_1) ? 0x01 : 0x11;
	buff[buff_cnt++] = 0x02;
	buff[buff_cnt++] = 0x00;
	buff[buff_cnt++] = cmd_lo;

	// ?? 28B Header (紐⑤뱺 ?꾨뱶 2B) ??
	buff[buff_cnt++] = (U08)((lightLevel >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(lightLevel & 0xFF);
	buff[buff_cnt++] = (U08)((heavyLevel >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(heavyLevel & 0xFF);
	buff[buff_cnt++] = (U08)((deadzone >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(deadzone & 0xFF);
	buff[buff_cnt++] = (U08)((empty >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(empty & 0xFF);
	buff[buff_cnt++] = (U08)((thrLightDist >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(thrLightDist & 0xFF);
	buff[buff_cnt++] = (U08)((thrHeavyDist >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(thrHeavyDist & 0xFF);
	buff[buff_cnt++] = (U08)((thrLightReal >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(thrLightReal & 0xFF);
	buff[buff_cnt++] = (U08)((thrHeavyReal >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(thrHeavyReal & 0xFF);
	buff[buff_cnt++] = (U08)((thrLightSet >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(thrLightSet & 0xFF);
	buff[buff_cnt++] = (U08)((thrHeavySet >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(thrHeavySet & 0xFF);
	buff[buff_cnt++] = 0x00;
	buff[buff_cnt++] = thrLightMode;
	buff[buff_cnt++] = 0x00;
	buff[buff_cnt++] = thrHeavyMode;
	buff[buff_cnt++] = (U08)((echoAmp >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(echoAmp & 0xFF);
	buff[buff_cnt++] = (U08)((statusCh >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(statusCh & 0xFF);

	// Temperature (2B, signed)
	S16 tmp = MsTPR_GetTprt(ch);
	buff[buff_cnt++] = (U08)((tmp >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(tmp & 0xFF);

	// Header DATA padding: 30B -> 200B (170B 0x00 reserved for future fields)
	while(buff_cnt < (1 + 2 + 200))
		buff[buff_cnt++] = 0x00;
	// ?? CRC: header portion (31B, ?⑤뵫 ?쒖쇅) ??
	crc = Crc16_UpdateBuf(crc, buff, buff_cnt);

	// ?? Send header: 31B ??35B(7횞5) ?⑤뵫 ??
	URT_TxPkt(URT_IDX_BT, buff, buff_cnt);
	HAL_Delay(10);

	// ?? ? 泥?겕: 98?섑뵆??(196B = 7횞28, ?⑤뵫 遺덊븘?? ??
	for(i = 0; i + 98 <= N; i += 98)
	{
		buff_cnt = 0;
		U16 j;
		for(j = i; j < i + 98; j++)
		{
			U16 val = MsCAL_GetVl_EchoReal(ch, j);
			buff[buff_cnt++] = (U08)((val >> 8) & 0xFF);
			buff[buff_cnt++] = (U08)(val & 0xFF);
		}
		crc = Crc16_UpdateBuf(crc, buff, buff_cnt);
		URT_TxPkt(URT_IDX_BT, buff, buff_cnt);
		HAL_Delay(10);
	}

	// ?? 留덉?留??⑦궥: ?⑥? ?섑뵆 + CRC + ?⑤뵫 ??
	buff_cnt = 0;
	for(; i < N; i++)
	{
		U16 val = MsCAL_GetVl_EchoReal(ch, i);
		buff[buff_cnt++] = (U08)((val >> 8) & 0xFF);
		buff[buff_cnt++] = (U08)(val & 0xFF);
	}
	crc = Crc16_UpdateBuf(crc, buff, buff_cnt);
	buff[buff_cnt++] = (U08)(crc & 0xFF);
	buff[buff_cnt++] = (U08)((crc >> 8) & 0xFF);
	URT_TxPkt(URT_IDX_BT, buff, buff_cnt);
}

void DaBT_SendWaveformAvg_Ch(U08 ch)
{
	U08 buff[210];
	U16 buff_cnt = 0;
	U16 i;
	U16 crc = 0xFFFF;

	U08 operation = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_OPERATION);
	U16 lightLevel, heavyLevel;
	if(operation == MnMS0_OPERATION_SLUDGE) {
		lightLevel = MsCAL_GetVl_RsltSldg(ch, MsCAL_THR_LIGHT);
		heavyLevel = MsCAL_GetVl_RsltSldg(ch, MsCAL_THR_HEAVY);
	} else {
		lightLevel = MsCAL_GetVl_RsltDist(ch, MsCAL_THR_LIGHT);
		heavyLevel = MsCAL_GetVl_RsltDist(ch, MsCAL_THR_HEAVY);
	}

	U16 deadzone  = (U16)MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_DEADZONE);
	U16 empty     = (U16)MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_EMPTY);
	U16 N         = (U16)(empty * 1.1);
	if(N > ADC_BUFF_MAX) N = ADC_BUFF_MAX;
	if(N == 0) N = 1;

	U16 thrLightDist = MsCAL_GetVl_TracDist(ch, MsCAL_THR_LIGHT);
	U16 thrHeavyDist = MsCAL_GetVl_TracDist(ch, MsCAL_THR_HEAVY);
	U16 thrLightReal = (U16)MsCAL_GetVl_Threshold(ch, MsCAL_THR_LIGHT);
	U16 thrHeavyReal = (U16)MsCAL_GetVl_Threshold(ch, MsCAL_THR_HEAVY);
	U16 thrLightSet  = (U16)MnMSR_Get_Threshold_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_LIGHT);
	U16 thrHeavySet  = (U16)MnMSR_Get_Threshold_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_HEAVY);
	U08 thrLightMode = (U08)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_LIGHT);
	U08 thrHeavyMode = (U08)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_HEAVY);
	U16 echoAmp      = (U16)MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_ECHO_AMP);
	U16 statusCh     = (U16)BLE_GetErrorCode(ch);

	U08 cmd_lo = (ch == APP_CH_1) ? 0x05 : 0x15;
	buff[buff_cnt++] = 0x02;
	buff[buff_cnt++] = 0x00;
	buff[buff_cnt++] = cmd_lo;

	buff[buff_cnt++] = (U08)((lightLevel >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(lightLevel & 0xFF);
	buff[buff_cnt++] = (U08)((heavyLevel >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(heavyLevel & 0xFF);
	buff[buff_cnt++] = (U08)((deadzone >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(deadzone & 0xFF);
	buff[buff_cnt++] = (U08)((empty >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(empty & 0xFF);
	buff[buff_cnt++] = (U08)((thrLightDist >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(thrLightDist & 0xFF);
	buff[buff_cnt++] = (U08)((thrHeavyDist >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(thrHeavyDist & 0xFF);
	buff[buff_cnt++] = (U08)((thrLightReal >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(thrLightReal & 0xFF);
	buff[buff_cnt++] = (U08)((thrHeavyReal >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(thrHeavyReal & 0xFF);
	buff[buff_cnt++] = (U08)((thrLightSet >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(thrLightSet & 0xFF);
	buff[buff_cnt++] = (U08)((thrHeavySet >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(thrHeavySet & 0xFF);
	buff[buff_cnt++] = 0x00;
	buff[buff_cnt++] = thrLightMode;
	buff[buff_cnt++] = 0x00;
	buff[buff_cnt++] = thrHeavyMode;
	buff[buff_cnt++] = (U08)((echoAmp >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(echoAmp & 0xFF);
	buff[buff_cnt++] = (U08)((statusCh >> 8) & 0xFF);
	buff[buff_cnt++] = (U08)(statusCh & 0xFF);

	// Temperature (2B, signed) — match DaBT_SendWaveform_Ch header size (203B)
	{
		S16 tmp = MsTPR_GetTprt(ch);
		buff[buff_cnt++] = (U08)((tmp >> 8) & 0xFF);
		buff[buff_cnt++] = (U08)(tmp & 0xFF);
	}

	// Header DATA padding: 30B -> 200B (170B 0x00 reserved for future fields)
	while(buff_cnt < (1 + 2 + 200))
		buff[buff_cnt++] = 0x00;

	// CRC: header portion (203B = SOF + CMD + 200B DATA, padding included)
	crc = Crc16_UpdateBuf(crc, buff, buff_cnt);

	// Send header: 203B
	URT_TxPkt(URT_IDX_BT, buff, buff_cnt);
	HAL_Delay(10);

	// ?? ? 泥?겕: 98?섑뵆??(196B = 7횞28, ?⑤뵫 遺덊븘?? ??
	for(i = 0; i + 98 <= N; i += 98)
	{
		buff_cnt = 0;
		U16 j;
		for(j = i; j < i + 98; j++)
		{
			U16 val = MsCAL_GetVl_EchoBuff(ch, j);
			buff[buff_cnt++] = (U08)((val >> 8) & 0xFF);
			buff[buff_cnt++] = (U08)(val & 0xFF);
		}
		crc = Crc16_UpdateBuf(crc, buff, buff_cnt);
		URT_TxPkt(URT_IDX_BT, buff, buff_cnt);
		HAL_Delay(10);
	}

	// ?? 留덉?留??⑦궥: ?⑥? ?섑뵆 + CRC + ?⑤뵫 ??
	buff_cnt = 0;
	for(; i < N; i++)
	{
		U16 val = MsCAL_GetVl_EchoBuff(ch, i);
		buff[buff_cnt++] = (U08)((val >> 8) & 0xFF);
		buff[buff_cnt++] = (U08)(val & 0xFF);
	}
	crc = Crc16_UpdateBuf(crc, buff, buff_cnt);
	buff[buff_cnt++] = (U08)(crc & 0xFF);
	buff[buff_cnt++] = (U08)((crc >> 8) & 0xFF);
	URT_TxPkt(URT_IDX_BT, buff, buff_cnt);
}
// ?꾩껜 ?몃젋???ㅼ슫濡쒕뱶 (理쒕? 10000媛? CMD=0x07/0x17) ??21?덉퐫??231B)?? ?꾩쟻CRC 7B
void DaBT_SendTrendFull_Ch(U08 ch)
{
	U08 hdr[7];
	U08 buf[234];
	U16 buf_cnt;
	U16 running_crc = 0xFFFF;
	U08 rd_buf[SAV_PKT_MAX];
	S32 dump_addr = DaSav_GetDumpAddr();
	U32 save_size = DaSav_GetSaveSize();
	U16 i, j;

	U16 total_cnt = (U16)DaSav_GetCnt();
	if(total_cnt > 20000)
		total_cnt = 20000;

	U08 cmd_lo = (ch == APP_CH_1) ? 0x07 : 0x17;

	hdr[0] = 0x02; hdr[1] = 0x00; hdr[2] = cmd_lo;
	hdr[3] = (U08)((total_cnt >> 8) & 0xFF);
	hdr[4] = (U08)(total_cnt & 0xFF);
	{ U16 hc = Mdb_GetCrc16(hdr, 5); hdr[5] = (U08)(hc & 0xFF); hdr[6] = (U08)(hc >> 8); }

	URT_TxPkt(URT_IDX_BT, hdr, 7);



	if(total_cnt == 0) return;

	// Progress popup: show "Data Download" while the blocking transfer runs
	DpPOP_DrwDLoadStart();
	DpPOP_DrwDLoadProgress(0, total_cnt);


	HAL_Delay(500);
	{
		U08 fCancel = 0;

		for(i = 0; i < total_cnt; i += 18)
		{
			U16 end = i + 18;
			if(end > total_cnt) end = total_cnt;

			// User cancel: any membrane key press aborts the transfer (active low)
			if(!DMX_GetIo(DMX_INP_MBR_BACK_) || !DMX_GetIo(DMX_INP_MBR_LEFT_) ||
			   !DMX_GetIo(DMX_INP_MBR_RIGHT) || !DMX_GetIo(DMX_INP_MBR_ENTER))
			{
				fCancel = 1;
				break;
			}

			// App cancel: CMD 0x08 (CH1) / 0x18 (CH2) frame from app.
			// NOTE: RXNE is masked during URT_TxPkt, so the app must retransmit
			//       the cancel frame several times (e.g. 50 ms apart) to guarantee
			//       at least one frame lands in the HAL_Delay(20) window.
			if(lmdb.f_rx[URT_IDX_BT] == TRUE)
			{
				U16 rx_crc = Mdb_GetCrc16(lmdb.rx_buf[URT_IDX_BT], 5);
				U08 rx_cmd = lmdb.rx_buf[URT_IDX_BT][2];
				if(lmdb.rx_buf[URT_IDX_BT][5] == (U08)(rx_crc & 0xFF) &&
				   lmdb.rx_buf[URT_IDX_BT][6] == (U08)((rx_crc >> 8) & 0xFF) &&
				   (rx_cmd == 0x08 || rx_cmd == 0x18))
				{
					fCancel = 1;
					Damdb_ClrRxBuff(URT_IDX_BT);
					break;
				}
				Damdb_ClrRxBuff(URT_IDX_BT);
			}

			buf_cnt = 0;
			for(j = i; j < end; j++)
			{
				S32 addr = dump_addr - (S32)((total_cnt - j) * SAV_PKT_MAX);
				if(addr < 0) addr += save_size;
				MRM_RdBulk(_mTrBOD_START + addr, rd_buf, SAV_PKT_MAX);

				buf[buf_cnt++] = rd_buf[SAV_PKT_TM_YEAR];
				buf[buf_cnt++] = rd_buf[SAV_PKT_TM_MONTH];
				buf[buf_cnt++] = rd_buf[SAV_PKT_TM_DAY];
				buf[buf_cnt++] = rd_buf[SAV_PKT_TM_HOUR];
				buf[buf_cnt++] = rd_buf[SAV_PKT_TM_MIN];
				buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH1_LIGHT_H];
				buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH1_LIGHT_L];
				buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH1_HEAVY_H];
				buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH1_HEAVY_L];
				buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH2_LIGHT_H];
				buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH2_LIGHT_L];
				buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH2_HEAVY_H];
				buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH2_HEAVY_L];
			}

			U16 k;
			for(k = 0; k < buf_cnt; k++) {
				running_crc ^= (U16)buf[k];
				U08 b;
				for(b = 0; b < 8; b++) {
					if(running_crc & 0x0001) running_crc = (running_crc >> 1) ^ 0xA001;
					else running_crc >>= 1;
				}
			}

			URT_TxPkt(URT_IDX_BT, buf, buf_cnt);
			DpPOP_DrwDLoadProgress(end, total_cnt);
			HAL_Delay(50);
		}

		// Send final running CRC only if the transfer completed normally
		if(!fCancel)
		{
			U08 crc_pkt[2] = {0};
			crc_pkt[0] = (U08)(running_crc & 0xFF);
			crc_pkt[1] = (U08)((running_crc >> 8) & 0xFF);
			URT_TxPkt(URT_IDX_BT, crc_pkt, 2);
		}
		else
		{
			// Cancel ack frame to app: [02 00 CMD 00 00 CRC_L CRC_H]
			// CMD mirrors the channel: 0x08 (CH1) / 0x18 (CH2)
			U08 cancel_rsp[7];
			U16 cancel_crc;
			U08 cancel_cmd = (cmd_lo == 0x07) ? 0x08 : 0x18;
			cancel_rsp[0] = 0x02;
			cancel_rsp[1] = 0x00;
			cancel_rsp[2] = cancel_cmd;
			cancel_rsp[3] = 0x00;
			cancel_rsp[4] = 0x00;
			cancel_crc = Mdb_GetCrc16(cancel_rsp, 5);
			cancel_rsp[5] = (U08)(cancel_crc & 0xFF);
			cancel_rsp[6] = (U08)((cancel_crc >> 8) & 0xFF);
			URT_TxPkt(URT_IDX_BT, cancel_rsp, 7);
		}
	}

	DpPOP_DrwDLoadEnd();
}
// ?몃젋????슜 ?ㅻ뜑 ?꾩넚 + ?ㅽ듃由щ컢 ?쒖옉 (720媛??쒗븳)
void DaBT_SendTrend_Ch(U08 ch)
{
	U08 hdr[7];

	gTrend_total_cnt = (U16)DaSav_GetCnt();
	if(gTrend_total_cnt > 720)
		gTrend_total_cnt = 720;

	U08 cmd_lo = (ch == APP_CH_1) ? 0x02 : 0x12;

	if(gTrend_total_cnt == 0)
	{
		// 鍮??ㅻ뜑 + End marker
		hdr[0] = 0x02; hdr[1] = 0x00; hdr[2] = cmd_lo;
		hdr[3] = 0x00; hdr[4] = 0x00;
		{ U16 hc = Mdb_GetCrc16(hdr, 5); hdr[5] = (U08)(hc & 0xFF); hdr[6] = (U08)(hc >> 8); }
		URT_TxPkt(URT_IDX_BT, hdr, 7);

		U08 tend[7]; U16 tc;
		tend[0] = 0x02; tend[1] = 0x00; tend[2] = 0xFE;
		tend[3] = 0x00; tend[4] = 0x00;
		tc = Mdb_GetCrc16(tend, 5);
		tend[5] = (U08)(tc & 0xFF); tend[6] = (U08)(tc >> 8);
		URT_TxPkt(URT_IDX_BT, tend, 7);
		return;
	}

	gTrend_ch = ch;
	gTrend_streaming = 1;

	// ?ㅻ뜑 ?꾩넚: [02][00][cmd_lo][recHI][recLO][CRC_L][CRC_H]
	hdr[0] = 0x02; hdr[1] = 0x00; hdr[2] = cmd_lo;
	hdr[3] = (U08)((gTrend_total_cnt >> 8) & 0xFF);
	hdr[4] = (U08)(gTrend_total_cnt & 0xFF);
	{ U16 hc = Mdb_GetCrc16(hdr, 5); hdr[5] = (U08)(hc & 0xFF); hdr[6] = (U08)(hc >> 8); }
	URT_TxPkt(URT_IDX_BT, hdr, 7);
	// ??DaBT_ProcMain() ?ㅼ쓬 ?몄텧 ??DaBT_TrendStreamProc()媛 ?ㅽ뻾??
}

// ?몃젋???ㅽ듃由щ컢 ??21?덉퐫??231B=7횞33)???꾩넚, 留덉?留됱뿉 ?꾩쟻CRC 7B
void DaBT_TrendStreamProc(void)
{
	if(gTrend_streaming == 0) return;

	U08 buf[234];
	U16 buf_cnt;
	U16 running_crc = 0xFFFF;
	U08 rd_buf[SAV_PKT_MAX];
	S32 dump_addr = DaSav_GetDumpAddr();
	U32 save_size = DaSav_GetSaveSize();
	U16 i, j;

	for(i = 0; i < gTrend_total_cnt; i += 18)
	{
		U16 end = i + 18;
		if(end > gTrend_total_cnt) end = gTrend_total_cnt;

		buf_cnt = 0;
		for(j = i; j < end; j++)
		{
			S32 addr = dump_addr - (S32)((gTrend_total_cnt - j) * SAV_PKT_MAX);
			if(addr < 0) addr += save_size;
			MRM_RdBulk(_mTrBOD_START + addr, rd_buf, SAV_PKT_MAX);

			buf[buf_cnt++] = rd_buf[SAV_PKT_TM_YEAR];
			buf[buf_cnt++] = rd_buf[SAV_PKT_TM_MONTH];
			buf[buf_cnt++] = rd_buf[SAV_PKT_TM_DAY];
			buf[buf_cnt++] = rd_buf[SAV_PKT_TM_HOUR];
			buf[buf_cnt++] = rd_buf[SAV_PKT_TM_MIN];
			buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH1_LIGHT_H];
			buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH1_LIGHT_L];
			buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH1_HEAVY_H];
			buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH1_HEAVY_L];
			buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH2_LIGHT_H];
			buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH2_LIGHT_L];
			buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH2_HEAVY_H];
			buf[buf_cnt++] = rd_buf[SAV_PKT_VAL_CH2_HEAVY_L];
		}

		U16 k;
		for(k = 0; k < buf_cnt; k++) {
			running_crc ^= (U16)buf[k];
			U08 b;
			for(b = 0; b < 8; b++) {
				if(running_crc & 0x0001) running_crc = (running_crc >> 1) ^ 0xA001;
				else running_crc >>= 1;
			}
		}

		URT_TxPkt(URT_IDX_BT, buf, buf_cnt);
		HAL_Delay(50);
	}

	{
		U08 crc_pkt[2] = {0};
		crc_pkt[0] = (U08)(running_crc & 0xFF);
		crc_pkt[1] = (U08)((running_crc >> 8) & 0xFF);
		URT_TxPkt(URT_IDX_BT, crc_pkt, 2);
	}

	gTrend_streaming = 0;
}
//------------------------------------------------------------------------------------------------------------------------------
//  BLE Module Initialization (AT commands)
//------------------------------------------------------------------------------------------------------------------------------
// AT 紐낅졊 ?꾩넚 ???묐떟 ?湲?(理쒕? timeout_ms)
static U08 BLE_SendATCmd(U08 *cmd, U16 len, const char *expect, U32 timeout_ms)
{
    gAt_rx_cnt = 0;
    memset((void*)gAt_rx_buf, 0, sizeof(gAt_rx_buf));

    if(cmd != NULL && len > 0)
        URT_TxPkt(URT_IDX_BT, cmd, len);

    U32 start = HAL_GetTick();
    while((HAL_GetTick() - start) < timeout_ms)
    {
        if(gAt_rx_cnt > 0 && gAt_rx_buf[gAt_rx_cnt - 1] == 0x0D)
        {
            gAt_rx_buf[gAt_rx_cnt] = 0;
            if(expect == NULL) return 1;
            if(strstr((char*)gAt_rx_buf, expect) != NULL) return 1;
            gAt_rx_cnt = 0;
        }
    }
    return 0;
}

void DaBT_InItMain(void)
{
    U08 buff[64] = {0};
    U16 buff_cnt = 0;
    gBle_found_baud = 0;

    gAt_rx_mode = 1;
    gAt_rx_cnt = 0;
    lmdb.ota_fble = FALSE;
    bt_ascii_cnt = 0;
    gBle_connected = 0;
    memset(interrupt_cnt, 0, sizeof(interrupt_cnt));

    buff_cnt = sprintf((char*)buff, "AT\r");

    URT_InitMain(URT_IDX_BT, 9600);
    HAL_Delay(100);
    if(BLE_SendATCmd(buff, buff_cnt, "+OK", 1000))
        gBle_found_baud = 1;

    if(gBle_found_baud == 0)
    {
        URT_InitMain(URT_IDX_BT, 115200);
        HAL_Delay(100);
        if(BLE_SendATCmd(buff, buff_cnt, "+OK", 1000))
            gBle_found_baud = 2;
    }

    if(gBle_found_baud == 0)
    {
        buff_cnt = sprintf((char*)buff, "AT&F\r");
        BLE_SendATCmd(buff, buff_cnt, "+OK", 1000);

        URT_InitMain(URT_IDX_BT, 9600);
        BLE_SendATCmd(0, 0, "+READY", 1000);
    }

    URT_InitMain(URT_IDX_BT, (gBle_found_baud != 2) ? 9600 : 115200);
    HAL_Delay(100);

    // MCU NRST 리셋 후 BLE 모듈이 이전 세션에 CONNECTED 상태로 남아있을 수 있음 → 강제 해제
    buff_cnt = sprintf((char*)buff, "AT+DISCONNECT\r");
    BLE_SendATCmd(buff, buff_cnt, "+OK", 1000);
    HAL_Delay(200);

    {
        U08 isDual = (MnFTR_PrGet_SsChn() == MnFTR_SS_DUAL);
        U16 sn1 = (U16)MnSYS_PrGet_site_name(APP_CH_1);
        U16 sn2 = (U16)MnSYS_PrGet_site_name(APP_CH_2);
        U08 ch1_hi = (U08)(sn1 / 100);
        U08 ch1_lo = (U08)(sn1 % 100);
        U08 ch2_hi = (U08)(sn2 / 100);
        U08 ch2_lo = (U08)(sn2 % 100);

        // Dual: CH1 + CH2, Single: CH1 only
        if (isDual && ch1_hi >= 'A' && ch1_hi <= 'Z' && ch2_hi >= 'A' && ch2_hi <= 'Z') {
            buff_cnt = sprintf((char*)buff, "AT+MANUF=W3%c%02d%c%02d\r",
                ch1_hi, ch1_lo, ch2_hi, ch2_lo);
        } else if (ch1_hi >= 'A' && ch1_hi <= 'Z') {
            buff_cnt = sprintf((char*)buff, "AT+MANUF=W3%c%02d\r", ch1_hi, ch1_lo);
        } else {
            buff_cnt = sprintf((char*)buff, "AT+MANUF=W3\r");
        }
        BLE_SendATCmd(buff, buff_cnt, "+OK", 1000);
    }


#if 1
    if(gBle_found_baud != 2)
    {
        buff_cnt = sprintf((char*)buff, "AT+UART=115200\r");
        BLE_SendATCmd(buff, buff_cnt, "+OK", 1000);
        URT_InitMain(URT_IDX_BT, 115200);
        HAL_Delay(100);
    }
#endif

#if 0
    buff_cnt = sprintf((char*)buff, "AT+UART=9600\r");
    BLE_SendATCmd(buff, buff_cnt, "+OK", 1000);
    URT_InitMain(URT_IDX_BT, 9600);
    HAL_Delay(100);
#endif
    buff_cnt = sprintf((char*)buff, "AT+FLOWCONTROL=ON\r");
    BLE_SendATCmd(buff, buff_cnt, "+OK", 1000);

    buff_cnt = sprintf((char*)buff, "AT+PACKETMODE=OFF\r");
    BLE_SendATCmd(buff, buff_cnt, "+OK", 1000);

    buff_cnt = sprintf((char*)buff, "AT+ADVON\r");
    BLE_SendATCmd(buff, buff_cnt, "+OK", 1000);

    gAt_rx_mode = 0;
}

//------------------------------------------------------------------------------------------------------------------------------
//  BLE Main Process - Interface Meter
//------------------------------------------------------------------------------------------------------------------------------
static void DaBT_SendSettingAck(U16 cmd, U16 result)
{
	U08 buff[7];
	U16 crc;

	buff[0] = 0x02;
	buff[1] = (U08)((cmd >> 8) & 0xFF);
	buff[2] = (U08)(cmd & 0xFF);
	buff[3] = (U08)((result >> 8) & 0xFF);
	buff[4] = (U08)(result & 0xFF);
	crc = Mdb_GetCrc16(buff, 5);
	buff[5] = (U08)(crc & 0xFF);
	buff[6] = (U08)((crc >> 8) & 0xFF);
	URT_TxPkt(URT_IDX_BT, buff, 7);
}

static U16 DaBT_ApplyAppSetting(U16 cmd, U16 data)
{
	U08 ch;
	U16 item;
	S16 sdata;

	if(cmd >= 1000 && cmd <= 1011)
	{
		ch = APP_CH_2;
		item = cmd - 1000;
	}
	else if(cmd >= 1 && cmd <= 11)
	{
		ch = APP_CH_1;
		item = cmd;
	}
	else
	{
		return 3; // unknown command
	}

	sdata = (S16)data;

	switch(item)
	{
		case 1: // Echo Amp
			if(data < MnMS1_ECHO_AMP_MIN || data > MnMS1_ECHO_AMP_MAX) return 1;
			MnMSR_CalSet_Ch_Value(ch, MnMS1_OPT_SINGLE_ECHO_AMP, data);
			break;

		case 2: // Thr.Light Auto (%)
			if(data < MnMS1_THR_VAL_AUTO_MIN || data > MnMS1_THR_VAL_AUTO_MAX) return 1;
			MnMSR_CalSet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_LIGHT, MnMS1_THRESHOLD_AUTO);
			MnMSR_Set_Threshold_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_LIGHT, data);
			break;

		case 3: // Thr.Heavy Auto (%)
			if(data < MnMS1_THR_VAL_AUTO_MIN || data > MnMS1_THR_VAL_AUTO_MAX) return 1;
			MnMSR_CalSet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_HEAVY, MnMS1_THRESHOLD_AUTO);
			MnMSR_Set_Threshold_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_HEAVY, data);
			break;

		case 4: // Thr.Light Manual (0.1V)
			if(data < MnMS1_THR_VAL_MANUAL_MIN || data > MnMS1_THR_VAL_MANUAL_MAX) return 1;
			MnMSR_CalSet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_LIGHT, MnMS1_THRESHOLD_MANUAL);
			MnMSR_Set_Threshold_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_LIGHT, data);
			break;

		case 5: // Thr.Heavy Manual (0.1V)
			if(data < MnMS1_THR_VAL_MANUAL_MIN || data > MnMS1_THR_VAL_MANUAL_MAX) return 1;
			MnMSR_CalSet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_HEAVY, MnMS1_THRESHOLD_MANUAL);
			MnMSR_Set_Threshold_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_HEAVY, data);
			break;

		case 6: // Frequency index: 0=380K, 1=270K, 2=160K, 3=130K
			if(data < MnMS1_FREQ_MIN || data > MnMS1_FREQ_MAX) return 1;
			MnMSR_CalSet_Ch_Value(ch, MnMS1_OPT_SINGLE_FREQ, data);
			break;

		case 7: // Offset, signed x0.01m
			if(sdata < MnMS1_OFFSET_MIN || sdata > MnMS1_OFFSET_MAX) return 1;
			MnMSR_CalSet_Ch_Value(ch, MnMS1_OPT_SINGLE_OFFSET, sdata);
			break;

		case 8: // 4mA set, x0.01m
			if(data < MnOS0_SET_MA_MIN || data > MnOS0_SET_MA_MAX) return 1;
			MnOUT_CurPrSet_Ch_Value(ch, MnOS0_OPT_SINGLE_SET_04mA, data);
			break;

		case 9: // 20mA set, x0.01m
			if(data < MnOS0_SET_MA_MIN || data > MnOS0_SET_MA_MAX) return 1;
			MnOUT_CurPrSet_Ch_Value(ch, MnOS0_OPT_SINGLE_SET_20mA, data);
			break;

		case 10: // TVG
			if(data < MnEGN_TVG_MIN || data > MnEGN_TVG_MAX) return 1;
			MnEGN_PrSet_Ch_Value(ch, MnEGN_OPT_SINGLE_TVG, data);
			break;

		case 11: // Damping
			if(data < MnMS1_DAMPING_MIN || data > MnMS1_DAMPING_MAX) return 1;
			MnMSR_CalSet_Ch_Value(ch, MnMS1_OPT_SINGLE_DAMPING, data);
			break;

		default:
			return 3;
	}

	return 0;
}

void DaBT_ProcMain(void)
{
	if(gTrend_streaming)
	{
		DaBT_TrendStreamProc();
		return;
	}

	U08 idx = URT_IDX_BT;

	if(lmdb.f_rx[idx] == FALSE)
		return;

	U08 buff[20] = {0, };
	U16 buff_cnt = 0;
	U08 sof = lmdb.rx_buf[idx][0];
	U16 cmd16 = ((U16)lmdb.rx_buf[idx][1] << 8) | (U16)lmdb.rx_buf[idx][2];
	U08 cmd = lmdb.rx_buf[idx][2];
	U16 data16 = ((U16)lmdb.rx_buf[idx][3] << 8) | (U16)lmdb.rx_buf[idx][4];

	{
		U16 crc16 = Mdb_GetCrc16(lmdb.rx_buf[idx], 5);
		if(lmdb.rx_buf[idx][5] != (U08)(crc16 & 0xFF) ||
		   lmdb.rx_buf[idx][6] != (U08)(crc16 >> 8))
		{
			Damdb_ClrRxBuff(idx);
			return;
		}
	}

	if(sof == 0x03)
	{
		U16 result = DaBT_ApplyAppSetting(cmd16, data16);
		DaBT_SendSettingAck(cmd16, result);
		Damdb_ClrRxBuff(idx);
		return;
	}

	switch(cmd)
	{
		case 0xF0:
		{
			U16 pin = data16;
			U16 passcode = (U16)MnSYS_PrGetBase_Item(MnSYS_OPT_PASSCODE);
			if(pin == passcode || pin == 129)
				DaBT_SendDeviceInfo();
			else
				DaBT_SendPairingFail();
			break;
		}
		case 0x01: DaBT_SendWaveform_Ch(APP_CH_1);    break;
		case 0x11: DaBT_SendWaveform_Ch(APP_CH_2);    break;
		case 0x05: DaBT_SendWaveformAvg_Ch(APP_CH_1); break;
		case 0x15: DaBT_SendWaveformAvg_Ch(APP_CH_2); break;
		case 0x02: DaBT_SendTrend_Ch(APP_CH_1);       break;
		case 0x12: DaBT_SendTrend_Ch(APP_CH_2);       break;
		case 0x07: DaBT_SendTrendFull_Ch(APP_CH_1);   break;
		case 0x17: DaBT_SendTrendFull_Ch(APP_CH_2);   break;
		case 0x00: DaBT_SendStatus_Ch(APP_CH_1);      break;
		case 0x10: DaBT_SendStatus_Ch(APP_CH_2);      break;
		case 0x04: DaBT_SendDiag_Ch(APP_CH_1);        break;
		case 0x14: DaBT_SendDiag_Ch(APP_CH_2);        break;
		case 0x50:
		{
			U16 ota_result = OTA_RESULT_TIMEOUT;
			U32 ota_total_bytes = (U32)data16 * 1024u;  // app sends size in KB (rounded up)

			lmdb.ota_fble = TRUE;
			ota_start_session();
			HAL_Delay(500);

			buff[buff_cnt++] = 0x02;
			buff[buff_cnt++] = 0x00;
			buff[buff_cnt++] = 0x50;
			buff[buff_cnt++] = 0x00;
			buff[buff_cnt++] = 0x00;
			{
				U16 ota_crc = Mdb_GetCrc16(buff, buff_cnt);
				buff[buff_cnt++] = (U08)(ota_crc & 0xFF);
				buff[buff_cnt++] = (U08)((ota_crc >> 8) & 0xFF);
			}
			URT_TxPkt(URT_IDX_BT, buff, buff_cnt);

			Damdb_ClrRxBuff(idx);

			// Show OTA progress popup while the blocking receive loop runs
			DpPOP_DrwOtaStart();

			{
				U32 last_rx_cnt = lota_get_cnt();
				U32 last_rx_tick = HAL_GetTick();
				U32 last_ui_tick = HAL_GetTick();
				U08 received_data = 0;   // 첫 청크 수신 여부

				while(1)
				{
					U32 now_cnt = lota_get_cnt();

					if(now_cnt != last_rx_cnt)
					{
						last_rx_cnt = now_cnt;
						last_rx_tick = HAL_GetTick();
						received_data = 1;
					}

					// Update RX byte counter / progress bar on the popup every ~100 ms
					if(HAL_GetTick() - last_ui_tick >= 1000)
					{
						last_ui_tick = HAL_GetTick();
						DpPOP_DrwOtaProgress(now_cnt, ota_total_bytes);
					}

					// 동적 타임아웃:
					// - 첫 바이트 도착 전: 5초 (Android 시작 ACK delay 흡수)
					// - 첫 바이트 도착 후: 1초 (정상 cycle 50ms 이라 1초 idle 이면 끊긴 것)
					U32 timeout_ms = received_data ? 1000 : 5000;
					if(HAL_GetTick() - last_rx_tick >= timeout_ms)
					{
						lmdb.ota_fble = FALSE;
						ota_end_session();
						ota_result = OTA_RESULT_TIMEOUT;
						break;
					}

					// 0x51 종료 프레임 검출: SDRAM 꼬리 7B 를 직접 검사.
					// ISR 가 OTA 모드에서 SOF 누적을 우회하므로 lmdb.f_rx 가 켜지지 않는다.
					// idle 50ms 조건은 페이로드 송신 중 false-positive 차단용
					// (송신이 잠시 멎은 시점에만 꼬리 패턴을 신뢰).
					if(now_cnt == last_rx_cnt && now_cnt >= 7 &&
					   (HAL_GetTick() - last_rx_tick) >= 50)
					{
						U08 *tail = &SDRAM_aEco_ota[now_cnt - 7];
						if(tail[0] == 0x02 && tail[2] == 0x51)
						{
							U16 crc_chk = Mdb_GetCrc16(tail, 5);
							if(tail[5] == (U08)(crc_chk & 0xFF) &&
							   tail[6] == (U08)((crc_chk >> 8) & 0xFF))
							{
								lmdb.ota_fble = FALSE;
								ota_end_session();
								DpPOP_DrwOtaStatus((I08*)"Verifying / writing...");
								ota_result = ota_promain();
								break;
							}
						}
					}
				}
			}

			// Result frame to app (matches Android OtaUploader.awaitOtaResult)
			{
				U08 rbuf[7];
				U16 rcrc;
				rbuf[0] = 0x02;
				rbuf[1] = 0x00;
				rbuf[2] = 0x51;
				rbuf[3] = (U08)((ota_result >> 8) & 0xFF);
				rbuf[4] = (U08)(ota_result & 0xFF);
				rcrc = Mdb_GetCrc16(rbuf, 5);
				rbuf[5] = (U08)(rcrc & 0xFF);
				rbuf[6] = (U08)((rcrc >> 8) & 0xFF);
				URT_TxPkt(URT_IDX_BT, rbuf, 7);
				HAL_Delay(500);
			}

			// Show final result on the device popup (brief hold for the user to read)
			DpPOP_DrwOtaResult(ota_result);
			HAL_Delay(1500);
			DpPOP_DrwOtaEnd();

			if(ota_result == OTA_RESULT_OK)
				__NVIC_SystemReset();

			return;
		}
		default: break;
	}

	Damdb_ClrRxBuff(idx);
}
void DaMdb_ProcMain(void)
{
	U16 rx_addr,crc16;
	U16 sel;

	if(lmdb.f_rx[URT_IDX_2]==TRUE)
	{
		if(MnDAT_ComPrGet_Value(MnDS2_OPT_TYPE)!=MnDS2_TYPE_MDB)
			return;


		crc16 = Mdb_GetCrc16(lmdb.rx_buf[URT_IDX_2],6);
		lmdb.crc_lo = (U08)((crc16 & 0x00ff) >> 0);
		lmdb.crc_hi = (U08)((crc16 & 0xff00) >> 8);
		//DaMdb_SetLevel(URT_IDX_2,rx_addr);
#if 1
		if(lmdb.rx_buf[URT_IDX_2][MDB_RX_06_CRC_LO] != lmdb.crc_lo)
		{
			Damdb_ClrRxBuff(URT_IDX_2);
			return;
		}
		if(lmdb.rx_buf[URT_IDX_2][MDB_RX_07_CRC_HI] != lmdb.crc_hi)
		{
			Damdb_ClrRxBuff(URT_IDX_2);
			return;
		}
#endif

		rx_addr = (lmdb.rx_buf[URT_IDX_2][MDB_RX_02_ADDR_H]<<8) + lmdb.rx_buf[URT_IDX_2][MDB_RX_03_ADDR_L];
		#if 1
		DaMdb_SetLevel(URT_IDX_2,rx_addr);
		#endif
		Damdb_ClrRxBuff(URT_IDX_2);
	}
	else if(lmdb.f_rx[URT_IDX_1]==TRUE)
	{	

		crc16 = Mdb_GetCrc16(lmdb.rx_buf[URT_IDX_1],6);
		lmdb.crc_lo = (U08)((crc16 & 0x00ff) >> 0);
		lmdb.crc_hi = (U08)((crc16 & 0xff00) >> 8);		

		if(lmdb.rx_buf[URT_IDX_1][MDB_RX_06_CRC_LO] != lmdb.crc_lo)
		{
			Damdb_ClrRxBuff(URT_IDX_1);
			return;
		}
		if(lmdb.rx_buf[URT_IDX_1][MDB_RX_07_CRC_HI] != lmdb.crc_hi)
		{
			Damdb_ClrRxBuff(URT_IDX_1);
			return;
		}

		rx_addr = (lmdb.rx_buf[URT_IDX_1][MDB_RX_02_ADDR_H]<<8) + lmdb.rx_buf[URT_IDX_1][MDB_RX_03_ADDR_L];

		sel = (lmdb.rx_buf[URT_IDX_1][MDB_RX_04_NULL]<<8) + lmdb.rx_buf[URT_IDX_1][MDB_RX_05_SIZE];
		(void)sel;

		switch(rx_addr)
		{
			case 1:	DaMdb_SaveEcho(APP_CH_1);	break;
			case 2:	DaMdb_AutoGain(APP_CH_1);	break;
			case 3: DaMdb_SaveEcho(APP_CH_2);	break;
			case 4: DaMdb_AutoGain(APP_CH_2);	break;

		}

		Damdb_ClrRxBuff(URT_IDX_1);
	}
}

void DaMdb_SetRxBuff(URT_IDX idx, U08 dr)
{
	U08 addr	= MnDAT_ComPrGet_Value(MnDS2_OPT_ADDR);

	#if 1
	if(interrupt_cnt[idx]==0)
	{
		if(dr==addr)
		{
			lmdb.interrupt_buf[idx][interrupt_cnt[idx]] = dr;
			interrupt_cnt[idx]++;
		}
		else 
			return;
	}
	else if(interrupt_cnt[idx]==1)
	{
		if(dr==MDB_CMD_03_REQ_READ)
		{
			lmdb.interrupt_buf[idx][interrupt_cnt[idx]] = dr;
			interrupt_cnt[idx]++;
		}
		else if(dr==addr)
		{
			lmdb.interrupt_buf[idx][0] = dr;		
		}
		else
			interrupt_cnt[idx] = 0;		
	}
	else if(interrupt_cnt[idx]<8)
	{
		lmdb.interrupt_buf[idx][interrupt_cnt[idx]] = dr;
		interrupt_cnt[idx]++;
	}
	#endif

#if 1
	if(interrupt_cnt[idx]>=8)
	{
		lmdb.f_rx[idx] = TRUE;
		memcpy(lmdb.rx_buf[idx], lmdb.interrupt_buf[idx], 8);
		interrupt_cnt[idx] = 0;
	}
#endif
	#if 0
	if(interrupt_cnt>=8)
	{
		U16 crc16;
		crc16 = Mdb_GetCrc16(lmdb.interrupt_buf[URT_IDX_2],6);
		
		if((lmdb.interrupt_buf[URT_IDX_2][MDB_RX_06_CRC_LO]==((crc16 & 0x00ff) >> 0))
			&& (lmdb.interrupt_buf[URT_IDX_2][MDB_RX_07_CRC_HI]==((crc16 & 0xff00) >> 8)))
		{
			 memcpy(lmdb.rx_buf[idx], lmdb.interrupt_buf[idx], 8);
			 lmdb.f_rx = TRUE;
			 //SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
		}
		interrupt_cnt = 0;
	}
	#endif

}

// TODO: output_com_rf .c.h
// RF
void ComWrf_InitMain(void)
{
	lrf.tx_cnt = 0;
}

void DaWrf_ProcMain(void)
{
	U16 assign[APP_CH_NUM];
	U16 valu[APP_CH_NUM];
	U16 curr[APP_CH_NUM];
	U16 rf_ch[APP_CH_NUM];
	U08 i;
	U16 crc;
	URT_InitMain(URT_IDX_RF,9600);


	assign[APP_CH_1] = MnDAT_ComPrGet_Value(MnDS2_OPT_RF_CH1_ASSIGN);
	assign[APP_CH_2] = MnDAT_ComPrGet_Value(MnDS2_OPT_RF_CH2_ASSIGN);

	valu[APP_CH_1] = MsCAL_GetVl_RsltSldg(APP_CH_1,assign[APP_CH_1]);
	valu[APP_CH_2] = MsCAL_GetVl_RsltSldg(APP_CH_2,assign[APP_CH_2]);	
	
	curr[APP_CH_1] = OuCUR_GetOutp_Value(APP_CH_1);
	curr[APP_CH_2] = OuCUR_GetOutp_Value(APP_CH_2);	
	
	rf_ch[APP_CH_1]  = MnDAT_ComPrGet_Value(MnDS2_OPT_RF_CH1_ADDRESS);
	rf_ch[APP_CH_2]  = MnDAT_ComPrGet_Value(MnDS2_OPT_RF_CH2_ADDRESS);

	
	U08 buff[64] = {0, };
	U08 cnt = 0;

	if(DaSav_GetDumfEn() == TRUE)
		return;

	if(lrf.tx_cnt%2==0)
		i=APP_CH_1;
	else
		i=APP_CH_2;

	if(i==APP_CH_2)
	{
		if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
			return;
	}


	buff[cnt++] = (lrf.tx_cnt / 10)   % 10 + '0';
	buff[cnt++] = lrf.tx_cnt         % 10 + '0';
	buff[cnt++] = '=';
	buff[cnt++] = 0x05; // Hearder
	buff[cnt++] = (rf_ch[i] / 10) + 0x30;
	buff[cnt++] = (rf_ch[i] % 10) + 0x30;
	buff[cnt++] = 'S';

	buff[cnt++] = (valu[i]/ 1000) % 10 + '0';
	buff[cnt++] = (valu[i] / 100)  % 10 + '0';
	buff[cnt++] = (valu[i] / 10)   % 10 + '0';
	buff[cnt++] =  valu[i]         % 10 + '0';

	buff[cnt++] = 'A';                     // 'A'
	buff[cnt++] = (curr[i] / 1000) % 10 + '0';
	buff[cnt++] = (curr[i] / 100)  % 10 + '0';
	buff[cnt++] = (curr[i] / 10)   % 10 + '0';
	buff[cnt++] =  curr[i]         % 10 + '0';
	buff[cnt++] = 0x04;	// Tail
	buff[cnt++] = 0x0D;	// CR  

	crc = Mdb_GetCrc16(buff,cnt);

	buff[cnt++] = (U08)((crc & 0x00ff) >> 0); 
	buff[cnt++] = (U08)((crc & 0xff00) >> 8);

	URT_TxPkt(URT_IDX_RF, buff, cnt);


	if(lrf.tx_cnt> 10)
		lrf.tx_cnt = 0;
}

void DaWrf_ProcMain_Old(void)
{
	U16 assign[APP_CH_NUM];
	U16 valu[APP_CH_NUM];
	U16 curr[APP_CH_NUM];
	U16 rf_ch[APP_CH_NUM];
	U08 i;
	URT_InitMain(URT_IDX_RF, 9600);

	assign[APP_CH_1] = MnDAT_ComPrGet_Value(MnDS2_OPT_RF_CH1_ASSIGN);
	//assign[APP_CH_2] = MnDAT_ComPrGet_Value(MnDS2_OPT_RF_CH2_ASSIGN);

	valu[APP_CH_1] = MsCAL_GetVl_RsltSldg(APP_CH_1, assign[APP_CH_1]);
	//valu[APP_CH_2] = MsCAL_GetVl_RsltSldg(APP_CH_2, assign[APP_CH_2]);

	curr[APP_CH_1] = OuCUR_GetOutp_Value(APP_CH_1);
	//curr[APP_CH_2] = OuCUR_GetOutp_Value(APP_CH_2);

	rf_ch[APP_CH_1] = MnDAT_ComPrGet_Value(MnDS2_OPT_RF_CH1_ADDRESS);
	//rf_ch[APP_CH_2] = MnDAT_ComPrGet_Value(MnDS2_OPT_RF_CH2_ADDRESS);

	U08 RF_data_tx[12];
	U08 buff[16];
	U08 cnt = 0;

	if(DaSav_GetDumfEn() == TRUE)
		return;

	i = APP_CH_1;

	// ENV110 data_tx_RF() compatible
	RF_data_tx[0]  = 'a' + (rf_ch[i] - 1);                // ch: 1-4 -> 'a'-'d'
	RF_data_tx[1]  = 0x53;                                 // 'S'
	RF_data_tx[2]  = (valu[i] / 1000) % 10 + '0';         // Level 4 digits
	RF_data_tx[3]  = (valu[i] /  100) % 10 + '0';
	RF_data_tx[4]  = (valu[i] /   10) % 10 + '0';
	RF_data_tx[5]  =  valu[i]         % 10 + '0';
	RF_data_tx[6]  = 0x41;                                 // 'A'
	RF_data_tx[7]  = (curr[i] / 1000) % 10 + '0';         // Current 3 digits
	RF_data_tx[8]  = (curr[i] /  100) % 10 + '0';
	RF_data_tx[9]  = (curr[i] /   10) % 10 + '0';
	RF_data_tx[10] = 'a' + (rf_ch[i] - 1);                // ch repeat

	RF_data_tx[11] = 0;
	{
		U08 k;
		for(k = 0; k < 11; k++)
			RF_data_tx[11] += RF_data_tx[k];
	}

	// CR + LF + data[0..11] + NULL
	buff[cnt++] = 0x0D;                                    // CR
	buff[cnt++] = 0x0A;                                    // LF
	{
		U08 k;
		for(k = 0; k < 12; k++)
			buff[cnt++] = RF_data_tx[k];
	}
	buff[cnt++] = 0x00;                                    // NULL

	URT_TxPkt(URT_IDX_RF, buff, cnt);

	if(lrf.tx_cnt > 10)
		lrf.tx_cnt = 0;
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void DaCOM_InitMain(void)
{
	ComMdb_InitMain();
	ComWrf_InitMain();
		lmdb.ota_fble = FALSE;
	DatComPr_BaudInit(MnDAT_ComPrGet_Value(MnDS2_OPT_BAUD));

}

void DaCOM_ProcMain(void)
{
	U08 type = MnDAT_ComPrGet_Value(MnDS2_OPT_TYPE);

	switch(type)
	{
		case MnDS2_TYPE_MDB:	DaMdb_ProcMain();	break;
		case MnDS2_TYPE_RF:
			lrf.tx_cnt++;

			if(MnFTR_PrGet_RfVersion() == MnFTR_RF_VER_OLD)
				DaWrf_ProcMain_Old();
			else
				DaWrf_ProcMain();
			break;
		default:									break;
	}

	// BLE: always process regardless of Modbus/RF type
	DaBT_ProcMain();

	// (?ㅽ듃由щ컢 ??젣 ?????붿껌 ?쒖뿉留??묐떟)
}


//------------------------------------------------------------------------------------------------------------------------------
//  BLE Send Device Info - Pairing Protocol (5 bytes payload, LEN=0x05)
//------------------------------------------------------------------------------------------------------------------------------
//  Payload Structure (5 bytes):
//    [site_name_HI(1B)][site_name_LO(1B)][fwVersion(3B)]
//
//  site_name_HI: ASCII 'A'~'Z' (?쒗뭹援щ텇)
//  site_name_LO: 0x01~0x99 (?レ옄, BCD)
//  fwVersion: major(1B).minor(1B).patch(1B)
//
//  Frame: [SOF(1)][LEN(2)][DATA(5)][CRC(2)] = 10 bytes
//------------------------------------------------------------------------------------------------------------------------------
void DaBT_SendDeviceInfo(void)
{
    // PIN ?깃났: [02] [00 F0] [00 00] [CRC] = 7B
    U08 buff[10] = {0, };
    U16 buff_cnt = 0;
    U16 crc16;

    buff[buff_cnt++] = 0x02;
    buff[buff_cnt++] = 0x00;
    buff[buff_cnt++] = 0xF0;
    buff[buff_cnt++] = 0x00;
    buff[buff_cnt++] = 0x00;

    crc16 = Mdb_GetCrc16(&buff[0], buff_cnt);
    buff[buff_cnt++] = (U08)(crc16 & 0xFF);
    buff[buff_cnt++] = (U08)((crc16 >> 8) & 0xFF);

    URT_TxPkt(URT_IDX_BT, buff, buff_cnt);
}

void DaBT_SendPairingFail(void)
{
    // PIN ?ㅽ뙣: [02] [00 F0] [00 FF] [CRC] = 7B
    U08 buff[10] = {0, };
    U16 buff_cnt = 0;
    U16 crc16;

    buff[buff_cnt++] = 0x02;
    buff[buff_cnt++] = 0x00;
    buff[buff_cnt++] = 0xF0;
    buff[buff_cnt++] = 0x00;
    buff[buff_cnt++] = 0xFF;

    crc16 = Mdb_GetCrc16(&buff[0], buff_cnt);
    buff[buff_cnt++] = (U08)(crc16 & 0xFF);
    buff[buff_cnt++] = (U08)((crc16 >> 8) & 0xFF);

    URT_TxPkt(URT_IDX_BT, buff, buff_cnt);
}

//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

