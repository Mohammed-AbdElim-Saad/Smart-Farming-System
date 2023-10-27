/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  Ov7670_Interface.h
 *		  Layer:  Hal
 *       Module:  Ov7670
 *		Version:  1.00
 *
 *  Description:  api of the Camera module
 *
 *********************************************************************************************************************/
#ifndef CAMERA_INTERFACE_H
#define CAMERA_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Ov7670_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define OV7670_IMG_COLUMNS 320
#define OV7670_IMG_ROWS 240
#define OV7670_FRAME_SIZE (OV7670_IMG_COLUMNS * OV7670_IMG_ROWS * 2)
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern volatile u8 OV7670_Frame[OV7670_FRAME_SIZE];
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
ErrorState_t Ov7670_Init(I2c_Id_t Copy_I2cId);
ErrorState_t OV7670_SnapShot(void (*Frame_Cplt)(void));

#endif /* CAMERA_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: Ov7670_Interface.h
 *********************************************************************************************************************/
