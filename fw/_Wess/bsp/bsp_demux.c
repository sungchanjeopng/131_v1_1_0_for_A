//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
// hal
#include "i2c.h"
// bsp
#include "bsp_gpio.h"
// self
#include "bsp_demux.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
U08 lGIO_I2C_1 = 0, lGIO_I2C_2 = 0, lGIO_I2C_3 = 0;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
void Dmx_CfgPorts(void)
{
	U08 dat0[3] = {DMX_CMD_CF_0, 0b11111111, 0b00000000};		// 0:output, 1:input
	U08 dat1[3] = {DMX_CMD_CF_0, 0b00000000, 0b11000000};
	
	HAL_I2C_Master_Transmit(&hi2c1, DMX_SLV_ADDR_0, dat0, 3, 10);
	HAL_I2C_Master_Transmit(&hi2c1, DMX_SLV_ADDR_1, dat1, 3, 10);
}
//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
U08 DMX_GetIo(U08 idx)
{
	U08 cmmd = 0;
	U08 addr = 0;
	U08 data = 0;
	U08 rtn = FALSE;

	switch(idx)
	{
		case DMX_INP_MBR_ENTER:
		case DMX_INP_MBR_RIGHT:
		case DMX_INP_MBR_LEFT_:
		case DMX_INP_MBR_BACK_:
		case DMX_INP_MBR_RSV_0:
		case DMX_INP_MBR_RSV_1:
		case DMX_INP_MBR_RSV_2:	cmmd = DMX_CMD_RD_0;	addr = DMX_SLV_ADDR_0;	break;

		case DMX_INP_EXT_IN_1:
		case DMX_INP_EXT_IN_2:	cmmd = DMX_CMD_RD_1;	addr = DMX_SLV_ADDR_1;	break;
		default:
			break;
	}

	HAL_I2C_Master_Transmit(&hi2c1, addr, &cmmd, 1, 10);
	HAL_I2C_Master_Receive (&hi2c1, addr, &data, 1, 10);

	switch(idx)
	{
		case DMX_INP_MBR_ENTER:		if(data & DMX_MSK_MBR_ENTER)	 	rtn = TRUE;		break;
		case DMX_INP_MBR_RIGHT:		if(data & DMX_MSK_MBR_RIGHT)		rtn = TRUE;		break;
		case DMX_INP_MBR_LEFT_:		if(data & DMX_MSK_MBR_LEFT_)		rtn = TRUE;		break;
		case DMX_INP_MBR_BACK_:		if(data & DMX_MSK_MBR_BACK_)		rtn = TRUE;		break;
		case DMX_INP_MBR_RSV_0:		if(data & DMX_MSK_MBR_RSV_0)		rtn = TRUE;		break;
		case DMX_INP_MBR_RSV_1:		if(data & DMX_MSK_MBR_RSV_1)		rtn = TRUE;		break;
		case DMX_INP_MBR_RSV_2:		if(data & DMX_MSK_MBR_RSV_2)		rtn = TRUE;		break;
			
		case DMX_INP_EXT_IN_1:		if(data & DMX_MSK_EXT_IN_1)			rtn = TRUE;		break;
		case DMX_INP_EXT_IN_2:		if(data & DMX_MSK_EXT_IN_2)			rtn = TRUE;		break;
	}

	return rtn;
}

void DMX_SetIo(U08 idx, U08 out)
{
	U08 addr = 0;
	U08 mask = 0;
	U08 wr_dat[2];

#if 1
	switch(idx)
	{
		case DMX_OUT_LCD_DISP:
		case DMX_OUT_LCD_BL:			addr = DMX_SLV_ADDR_0;	break;
		
		case DMX_OUT_RX_Con_0:
		case DMX_OUT_RX_Con_1:
		case DMX_OUT_SEL_CH:
		case DMX_OUT_CS_CURRENT:
			
		case DMX_OUT_RELAY_4:
		case DMX_OUT_RELAY_3:
		case DMX_OUT_RELAY_2:
		case DMX_OUT_RELAY_1:	
		case DMX_OUT_RF_RESETIN:	
		case DMX_OUT_CLEAN:					addr = DMX_SLV_ADDR_1;	break;
		default:
			return;
	}

	switch(idx)
	{
		case DMX_OUT_LCD_DISP:		mask = DMX0_P1_MSK_LCD_DISP;	break;
		case DMX_OUT_LCD_BL:			mask = DMX0_P1_MSK_LCD_BL_CTRL;	break;
		
		case DMX_OUT_RX_Con_0:		mask = DMX1_P0_MSK_RX_Con_0;		break;
		case DMX_OUT_RX_Con_1:		mask = DMX1_P0_MSK_RX_Con_1;		break;
		case DMX_OUT_SEL_CH:			mask = DMX1_P0_MSK_SEL_CH;		break;
		case DMX_OUT_CS_CURRENT:	mask = DMX1_P0_MSK_CS_CURRENT;		break;
			
		case DMX_OUT_RELAY_4:			mask = DMX1_P1_MSK_RELAY_4;		break;
		case DMX_OUT_RELAY_3:			mask = DMX1_P1_MSK_RELAY_3;		break;
		case DMX_OUT_RELAY_2:			mask = DMX1_P1_MSK_RELAY_2;		break;
		case DMX_OUT_RELAY_1:			mask = DMX1_P1_MSK_RELAY_1;		break;
		case DMX_OUT_RF_RESETIN:	mask = DMX1_P1_MSK_RF_RESETIN;		break;
		case DMX_OUT_CLEAN:				mask = DMX1_P1_MSK_CLEAN;		break;

		default:
			return;
	}

	switch(idx)
	{
		case DMX_OUT_LCD_DISP:
		case DMX_OUT_LCD_BL:
			if		(out == GIO_LV_HI) 	lGIO_I2C_1 |=  (1 << mask);
			else if	(out == GIO_LV_LO) 	lGIO_I2C_1 &= ~(1 << mask);

			wr_dat[0] = DMX_CMD_WR_1;
			wr_dat[1] = lGIO_I2C_1;			
			break;

		case DMX_OUT_RX_Con_0:
		case DMX_OUT_RX_Con_1:
		case DMX_OUT_SEL_CH: 
		case DMX_OUT_CS_CURRENT:
			//if(idx == DMX_OUT_SEL_CH) { if(out == 1) {out = 0;} else {out = 1;} }
			
			if		(out == GIO_LV_HI) 	lGIO_I2C_2 |=  (1 << mask);
			else if	(out == GIO_LV_LO) 	lGIO_I2C_2 &= ~(1 << mask);

			wr_dat[0] = DMX_CMD_WR_0;
			wr_dat[1] = lGIO_I2C_2;
			break;

		case DMX_OUT_RELAY_4:
		case DMX_OUT_RELAY_3:
		case DMX_OUT_RELAY_2:
		case DMX_OUT_RELAY_1:
			
		case DMX_OUT_RF_RESETIN:
		case DMX_OUT_CLEAN:
			if		(out == GIO_LV_HI) 	lGIO_I2C_3 |=  (1 << mask);
			else if	(out == GIO_LV_LO) 	lGIO_I2C_3 &= ~(1 << mask);

			wr_dat[0] = DMX_CMD_WR_1;
			wr_dat[1] = lGIO_I2C_3;
			break;
		default:
			return;
	}

	HAL_I2C_Master_Transmit(&hi2c1, addr, wr_dat, 2, 10);
#else
	wr_dat[0] = DMX_CMD_WR_1;

	switch(idx)
	{
		case DMX_OUT_CS_P1:
			if		(out == GIO_LV_HI)	 {	wr_dat[1] = lGIO_I2C_1 |   GIO_I2C_CS_DIGIT_POT1;	}
			else if	(out == GIO_LV_LO)	 {	wr_dat[1] = lGIO_I2C_1 & ~(GIO_I2C_CS_DIGIT_POT1);	}
			
			lGIO_I2C_1 = wr_dat[1];
			HAL_I2C_Master_Transmit(&hi2c1,0x42,wr_dat,2,10);
			break;
			
		case DMX_OUT_CS_P2:
			if		(out == GIO_LV_HI) 	{ 	wr_dat[1] = lGIO_I2C_1 | GIO_I2C_CS_DIGIT_POT2;		}
			else if	(out == GIO_LV_LO) 	{	wr_dat[1] = lGIO_I2C_1 & ~(GIO_I2C_CS_DIGIT_POT2); 	}
			
			lGIO_I2C_1 = wr_dat[1];
			HAL_I2C_Master_Transmit(&hi2c1,0x42,wr_dat,2,10);
			break;
			
		case DMX_OUT_CS_CURRENT:
			if		(out == GIO_LV_HI)	{	wr_dat[1] = lGIO_I2C_1 | GIO_I2C_CS_CURRENT; }
			else if	(out == GIO_LV_LO) 	{	wr_dat[1] = lGIO_I2C_1 & ~(GIO_I2C_CS_CURRENT); }
			
			lGIO_I2C_1 = wr_dat[1];
			HAL_I2C_Master_Transmit(&hi2c1,0x42,wr_dat,2,10);
			break;
			
		case DMX_OUT_SEL_CH:
			if(out == GIO_LV_HI) { wr_dat[1] = lGIO_I2C_1 | GIO_I2C_SEL_CH; }
			else if(out == GIO_LV_LO) {	wr_dat[1] = lGIO_I2C_1 & ~(GIO_I2C_SEL_CH); }
			
			lGIO_I2C_1 = wr_dat[1];
			HAL_I2C_Master_Transmit(&hi2c1,0x42,wr_dat,2,10);
			break;
			
		case DMX_OUT_SEL_G:
			if(out == GIO_LV_HI) { wr_dat[1] = lGIO_I2C_1 | GIO_I2C_SEL_G; }
			else if(out == GIO_LV_LO) {	wr_dat[1] = lGIO_I2C_1 & ~(GIO_I2C_SEL_G); }
			
			lGIO_I2C_1 = wr_dat[1];
			HAL_I2C_Master_Transmit(&hi2c1,0x42,wr_dat,2,10);
			break;
			
		case DMX_OUT_SEL_FREQ:
			if(out == GIO_LV_HI) { wr_dat[1] = lGIO_I2C_1 | GIO_I2C_SEL_FREQ; }
			else if(out == GIO_LV_LO) {	wr_dat[1] = lGIO_I2C_1 & ~(GIO_I2C_SEL_FREQ); }
			
			lGIO_I2C_1 = wr_dat[1];
			HAL_I2C_Master_Transmit(&hi2c1,0x42,wr_dat,2,10);
			break;
			
		case DMX_OUT_LCD_DISP:
			if(out == GIO_LV_HI) { wr_dat[1] = lGIO_I2C_2 | GIO_I2C_LCD_DISP; }
			else if(out == GIO_LV_LO) {	wr_dat[1] = lGIO_I2C_2 & ~(GIO_I2C_LCD_DISP); }
			
			lGIO_I2C_2 = wr_dat[1];
			HAL_I2C_Master_Transmit(&hi2c1,0x44,wr_dat,2,10);
			break;
			
		case DMX_OUT_LCD_BL:
			if(out == GIO_LV_HI) { wr_dat[1] = lGIO_I2C_2 | GIO_I2C_LCD_BL_CTRL; }
			else if(out == GIO_LV_LO) {	wr_dat[1] = lGIO_I2C_2 & ~(GIO_I2C_LCD_BL_CTRL); }
			
			lGIO_I2C_2 = wr_dat[1];
			HAL_I2C_Master_Transmit(&hi2c1,0x44,wr_dat,2,10);
			break;
			
		case DMX_OUT_BUZZER:
			if(out == GIO_LV_HI) { wr_dat[1] = lGIO_I2C_2 | GIO_I2C_BUZZER; }
			else if(out == GIO_LV_LO) {	wr_dat[1] = lGIO_I2C_2 & ~(GIO_I2C_BUZZER); }
			
			lGIO_I2C_2 = wr_dat[1];
			HAL_I2C_Master_Transmit(&hi2c1,0x44,wr_dat,2,10);
			break;
			
		case DMX_OUT_RELAY:
			if(out == GIO_LV_HI) { wr_dat[1] = lGIO_I2C_2 | GIO_I2C_RELAY; }
			else if(out == GIO_LV_LO) {	wr_dat[1] = lGIO_I2C_2 & ~(GIO_I2C_RELAY); }
			
			lGIO_I2C_2 = wr_dat[1];
			HAL_I2C_Master_Transmit(&hi2c1,0x44,wr_dat,2,10);
			break;
			
		case DMX_OUT_PCD:
			if(out == GIO_LV_HI) { wr_dat[1] = lGIO_I2C_2 | GIO_I2C_CLEAN; }
			else if(out == GIO_LV_LO) {	wr_dat[1] = lGIO_I2C_2 & ~(GIO_I2C_CLEAN); }
			
			lGIO_I2C_2 = wr_dat[1];
			HAL_I2C_Master_Transmit(&hi2c1,0x44,wr_dat,2,10);
			break;
			
		case DMX_OUT_RF_RESETIN:
			if(out == GIO_LV_HI) { wr_dat[1] = lGIO_I2C_2 | GIO_I2C_RF_RESETIN; }
			else if(out == GIO_LV_LO) {	wr_dat[1] = lGIO_I2C_2 & ~(GIO_I2C_RF_RESETIN); }
			
			lGIO_I2C_2 = wr_dat[1];
			HAL_I2C_Master_Transmit(&hi2c1,0x44,wr_dat,2,10);
			break;
	}
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void DMX_InitMain(void)
{
#if 1	
	Dmx_CfgPorts();

	//lDmx.out_0 = 0;
	//lDmx.out_1 = 0;

#else
	U08 dat0[3] = {DMX_CMD_CF_0, 0b11111111, 0b00000000};		// 0:output, 1:input
	U08 dat1[3] = {DMX_CMD_CF_0, 0b11111111, 0b00000000};
	
	HAL_I2C_Master_Transmit(&hi2c1, DMX_SLV_ADDR_0, dat0, 3, 10);
	HAL_I2C_Master_Transmit(&hi2c1, DMX_SLV_ADDR_1, dat1, 3, 10);
#endif
}

void DMX_ProcMain(void)
{

}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

