//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DISP_BUTTON_H___
#define ___DISP_BUTTON_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
// Index
enum {
	DpBTN_I0_MENU = 0,
	DpBTN_I1_PREV,
	DpBTN_I2_NEXT,
	DpBTN_I3_ENTR,
	// Number Max
	DpBTN_IDX_NUM
};

// Status
enum {
	DpBTN_STT_IDLE = 0,
	DpBTN_STT_PUSH,
	DpBTN_STT_DISA,			// Disbale
	DpBTN_STT_HIDE,			// Hide
	DpBTN_STT_ACTV,			// Active
	// Number Max
	DpBTN_STT_NUM
};

// Active
enum {
	DpBTN_ATV_DISABLE = 0,
	DpBTN_ATV_ENABLE,
	// Number Max
	DpBTN_ATV_NUM
};

// Previous
enum {
	DpBTN_PREV_IDLE = 0,
	DpBTN_PREV_LEFT,
	DpBTN_PREV_DOWN,
	DpBTN_PREV_UP__,
	// Number Max
};

// Next
enum {
	DpBTN_NEXT_IDLE = 0,
	DpBTN_NEXT_RIGH,		// Right
	DpBTN_NEXT_UP__,		// Down
	DpBTN_NEXT_DOWN,		// Down
	// Number Max
};

// Enter
enum {
	DpBTN_ENTR_MENU = 0,
	DpBTN_ENTR_SET_,
	// Idle Index
	DpBTN_ENTR_IDLE = DpBTN_ENTR_MENU,
};

// Position
#define DpBTN_BOX_X0_		(20)
#define DpBTN_BOX_Y0_		(410)
#define DpBTN_BOX_GAP		(46)
#define DpBTN_BOX_WID		(90)		// width
#define DpBTN_BOX_HEI		(50)		// height


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------
#define DpBTN_I0_BACK		(DpBTN_I0_MENU)
#define DpBTN_I1_UP			(DpBTN_I1_PREV)
#define DpBTN_I2_DN			(DpBTN_I2_NEXT)
#define DpBTN_I3_SET		(DpBTN_I3_ENTR)
#define DpBTN_I3_FUNC		(DpBTN_I3_ENTR)


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get Local Variables
// Set Local Variables
// Operation
extern void DpBTN_InitVari(void);
extern void DpBTN_ClearBtn(U08 idx);
extern void DpBTN_UdtStrng(U08 idx, U08 stt, U08 list, I08 offs);
extern void DpBTN_UdtArrow(U08 idx, U08 opt);
extern void DpBTN_UdtEvent(U08 idx, U08 fPsh);



#endif // ___DISP_BUTTON_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

