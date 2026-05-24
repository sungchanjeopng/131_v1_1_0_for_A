//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------
#ifndef __FONTS_H
#define __FONTS_H

#ifdef __cplusplus
 extern "C" {
#endif

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include <stdint.h>


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	uint16_t Width;
	uint16_t Height;
	uint32_t pt;

} sFONT_INFO;

typedef struct _tFont {    
	const uint8_t *table;
	const sFONT_INFO *info;
} sFONT;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------
#define LINE(x) ((x) * (((sFONT *)LCD_GetFont())->info->Height))

// Source Han Sans
#if 1
#define _fE150HsB		Ft150_HanSansBold
#define _fE75HsB		Ft75_HanSansBold
#define _fE35HsB		Ft35_HanSansBold
#define _fE22HsN		Ft22_HanSansNormal
#define _fE22HsNKOR		Ft22_HanSansNormal_KOR
#define _fE22HsB		Ft22_HanSansBold
#define _fE22HsBKOR		Ft22_HanSansBold_KOR
#define _fE17HsB		Ft17_HanSansBold
#define _fE17HsBKOR		Ft17_HanSansBold_KOR
#define _fE12HsMKOR		Ft12_HanSansMedium_KOR
#define _fE12HsM		Ft12_HanSansMedium
#else	// TODO
#define _fE35HsB		Ft35_HanSansBold
#define _fE17HsB		Ft17_HanSansBold
#define _fE14HsE		Ft14_HanSansExtraLight
#define _fE14HsR		Ft14_HanSansRegular
#define _fE12HsL		Ft12_HanSansLight
#define _fE12HsM		Ft12_HanSansMedium
#endif


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------
//Source Han Sans
extern sFONT Ft150_HanSansBold;
extern sFONT Ft75_HanSansBold;
extern sFONT Ft75_HanSansBold_KOR;
extern sFONT Ft35_HanSansBold;
extern sFONT Ft22_HanSansBold;
extern sFONT Ft22_HanSansBold_KOR;
extern sFONT Ft22_HanSansNormal;
extern sFONT Ft22_HanSansNormal_KOR;
extern sFONT Ft17_HanSansBold;
extern sFONT Ft17_HanSansBold_KOR;
extern sFONT Ft12_HanSansMedium;
extern sFONT Ft12_HanSansMedium_KOR;


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------




#ifdef __cplusplus
}
#endif

  
#endif /* __FONTS_H */
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------
