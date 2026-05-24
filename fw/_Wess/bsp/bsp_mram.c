//--------------------------------------------------------------------
//
//  Copyright (C) 2020, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of
//  WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement
//  with WESS-Global Co.,LTD
//
//  $Id: templet_format.c 1 2020-07-13 12:00:00Z eddie $
//  $Date: 2020-07-13 12:00:00 +0900 
//  $Author: eddie $
//  $Rev: 1.0 $
//
//--------------------------------------------------------------------


//--------------------------------------------------------------------
//  Includes
//--------------------------------------------------------------------
#include "bsp_spi.h"
// self
#include "bsp_mram.h"


//--------------------------------------------------------------------
//  Local Macros
//--------------------------------------------------------------------
#define  MRAM_ENABLE()			HAL_GPIO_WritePin(CS_MRAM_GPIO_Port, CS_MRAM_Pin, GPIO_PIN_RESET)
#define  MRAM_DISABLE()			 HAL_GPIO_WritePin(CS_MRAM_GPIO_Port, CS_MRAM_Pin, GPIO_PIN_SET)


//--------------------------------------------------------------------
//  Local Type definitions
//--------------------------------------------------------------------


//--------------------------------------------------------------------
//  Global variables
//--------------------------------------------------------------------


//--------------------------------------------------------------------
//  Local variables
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Funtion Definitions
//--------------------------------------------------------------------
U08 MRAM_ReadByte(U32 addr)
{
	U08 rd_data = 0;
	U08 wr_data[4] = {0, };
	
	SPI_SetMram();

	MRAM_ENABLE();

	wr_data[0] = (U08)MRAM_CMD_READ;
	wr_data[1] = (U08)((addr & 0xff0000) >> 16);
	wr_data[2] = (U08)((addr & 0x00ff00) >>  8);
	wr_data[3] = (U08)((addr & 0x0000ff) >>  0);
	SPI_WrSize((U08*)wr_data, 4);

	rd_data = SPI_RdByte();

	MRAM_DISABLE();

	return rd_data;
}

U16 MRAM_ReadWord(U32 addr)
{
	U08 rd_data_h;
	U08 rd_data_l;
    U08 wr_data[4];
	
	SPI_SetMram();

    // Read Data
    MRAM_ENABLE();

    wr_data[0] = (U08)MRAM_CMD_READ;
    wr_data[1] = (U08) ((addr & 0xff0000) >> 16);
    wr_data[2] = (U08) ((addr & 0x00ff00) >>  8);
    wr_data[3] = (U08) ((addr & 0x0000ff) >>  0);
    SPI_WrSize((U08*) wr_data, 4);
    
    rd_data_h = SPI_RdByte();
    rd_data_l = SPI_RdByte();

    MRAM_DISABLE();

	return (U16)((rd_data_h<<8) | rd_data_l);
}

U32 MRAM_ReadLong(U32 addr)
{
	U08 rd_data[4] = {0, };
    U08 wr_data[4] = {0, };
	
	SPI_SetMram();

    MRAM_ENABLE();

    wr_data[0] = (U08)MRAM_CMD_READ;
    wr_data[1] = (U08)((addr & 0xff0000) >> 16);
    wr_data[2] = (U08)((addr & 0x00ff00) >>  8);
    wr_data[3] = (U08)((addr & 0x0000ff) >>  0);
    SPI_WrSize((U08*) wr_data, 4);
    
    rd_data[0] = (U32)SPI_RdByte();
    rd_data[1] = (U32)SPI_RdByte();
    rd_data[2] = (U32)SPI_RdByte();
    rd_data[3] = (U32)SPI_RdByte();

    MRAM_DISABLE();

	return (U32)( (rd_data[0]<<24) | (rd_data[1]<<16) | (rd_data[2]<<8) | rd_data[3] );
}

void MRAM_ReadBulk(U32 addr, U08* buf, U08 cnt)
{
	U08 i = 0;
	
	SPI_SetMram();
	
    // Read Data
    MRAM_ENABLE();

    U08 wr_data[4];
    wr_data[0] = (U08) MRAM_CMD_READ;
    wr_data[1] = (U08) ((addr & 0xff0000) >> 16);
    wr_data[2] = (U08) ((addr & 0x00ff00) >>  8);
    wr_data[3] = (U08) ((addr & 0x0000ff) >>  0);
    SPI_WrSize((U08*) wr_data, 4);

	for(i=0; i<cnt; i++)
    	buf[i] = SPI_RdByte();

    MRAM_DISABLE();
}

void MRAM_WriteByte(U32 addr, U08 data)
{
	U08 wr_data[5];
	
	SPI_SetMram();
    
    // Write Enable
    MRAM_ENABLE();
    wr_data[0] = (U08) (MRAM_CMD_WREN);
    SPI_WrSize((U08*) wr_data, 1);    
    MRAM_DISABLE();

    HAL_Delay(1);
    
    // Write Data
    MRAM_ENABLE();
    wr_data[0] = (U08)MRAM_CMD_WRITE;
    wr_data[1] = (U08) ((addr & 0xff0000) >> 16);
    wr_data[2] = (U08) ((addr & 0x00ff00) >>  8);
    wr_data[3] = (U08) ((addr & 0x0000ff) >>  0);
    wr_data[4] = data;
    SPI_WrSize((U08*) wr_data, 5);
    
    MRAM_DISABLE();
}

void MRAM_WriteWord(U32 addr, U16 data)
{
	U08 wr_data[6];
	
	SPI_SetMram();
    
    // Write Enable
    MRAM_ENABLE();
    wr_data[0] = (U08) (MRAM_CMD_WREN);
    SPI_WrSize((U08*) wr_data, 1);    
    MRAM_DISABLE();

    HAL_Delay(1);
    
    // Write Data
    MRAM_ENABLE();
    wr_data[0] = (U08) MRAM_CMD_WRITE;
    wr_data[1] = (U08) ((addr & 0xff0000) >> 16);
    wr_data[2] = (U08) ((addr & 0x00ff00) >>  8);
    wr_data[3] = (U08) ((addr & 0x0000ff) >>  0);
    wr_data[4] = (U08) ((data & 0xff00) >> 8);
    wr_data[5] = (U08) ((data & 0x00ff) >> 0);
    SPI_WrSize((U08*) wr_data, 6);
    
    MRAM_DISABLE();
}

void MRAM_Write_3Byte(U32 addr, U32 data)
{
	U08 wr_data[7];
	
	SPI_SetMram();
    
    // Write Enable
    MRAM_ENABLE();
    wr_data[0] = (U08) (MRAM_CMD_WREN);
    SPI_WrSize((U08*) wr_data, 1);    
    MRAM_DISABLE();

    HAL_Delay(1);
    
    // Write Data
    MRAM_ENABLE();
    wr_data[0] = (U08)MRAM_CMD_WRITE;
    wr_data[1] = (U08) ((addr & 0xff0000) >> 16);
    wr_data[2] = (U08) ((addr & 0x00ff00) >>  8);
    wr_data[3] = (U08) ((addr & 0x0000ff) >>  0);
    wr_data[4] = (U08) ((data & 0xff0000) >> 16);
    wr_data[5] = (U08) ((data & 0x00ff00) >>  8);
    wr_data[6] = (U08) ((data & 0x0000ff) >>  0);
    SPI_WrSize((U08*) wr_data, 7);
    
    MRAM_DISABLE();
}

void MRAM_WriteLong(U32 addr, U32 data)
{
	U08 wr_data[9];
	
	SPI_SetMram();
    
    // Write Enable
    MRAM_ENABLE();
    wr_data[0] = (U08) (MRAM_CMD_WREN);
    SPI_WrSize((U08*) wr_data, 1);    
    MRAM_DISABLE();

    HAL_Delay(1);
    
    // Write Data
    MRAM_ENABLE();
    wr_data[0] = (U08)MRAM_CMD_WRITE;
    wr_data[1] = (U08) ((addr & 0xff0000) >> 16);
    wr_data[2] = (U08) ((addr & 0x00ff00) >>  8);
    wr_data[3] = (U08) ((addr & 0x0000ff) >>  0);
    wr_data[4] = (U08) ((data & 0xff000000) >> 24);
    wr_data[5] = (U08) ((data & 0x00ff0000) >> 16);
    wr_data[6] = (U08) ((data & 0x0000ff00) >>  8);
    wr_data[7] = (U08) ((data & 0x000000ff) >>  0);
    SPI_WrSize((U08*) wr_data, 8);
    
    MRAM_DISABLE();
}

void MRAM_WriteBulk(U32 addr, U08* buf, U08 cnt)
{
	U08 i = 0;
	U08 *wr_data = malloc(sizeof(U08)*(cnt+4));
	
	SPI_SetMram();
    
    // Write Enable
    MRAM_ENABLE();
    wr_data[0] = (U08) (MRAM_CMD_WREN);
    SPI_WrSize((U08*) wr_data, 1);    
    MRAM_DISABLE();

    HAL_Delay(1);
    
    // Write Data
    MRAM_ENABLE();
    wr_data[0] = (U08)MRAM_CMD_WRITE;
    wr_data[1] = (U08) ((addr & 0xff0000) >> 16);
    wr_data[2] = (U08) ((addr & 0x00ff00) >>  8);
    wr_data[3] = (U08) ((addr & 0x0000ff) >>  0);

	for(i=0; i<cnt; i++)
		wr_data[4+i] = buf[i];
	
    SPI_WrSize((U08*) wr_data, cnt+4);
    
    MRAM_DISABLE();

	free(wr_data);
}

// EOF

