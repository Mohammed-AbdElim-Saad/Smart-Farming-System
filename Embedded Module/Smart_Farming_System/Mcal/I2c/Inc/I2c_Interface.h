/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Fahim
 *	   	   File:  I2c_Interface.h
 *		  Layer:  Mcal
 *       Module:  I2c
 *		Version:  1.00
 *	
 *  Description:  I2c Driver API.
 *  
 *********************************************************************************************************************/
#ifndef I2C_INTERFACE_H 
#define I2C_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "I2c_Types.h"
#include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/* Initilization */
ErrorState_t I2c_Init(I2c_Handle_t *hi2c);

/* I/O */
ErrorState_t I2c_Master_Transmit(I2c_Handle_t *hi2c, u16 Copy_DevAddress, u8 *pData, u16 Copy_Size, u32 Copy_Timeout);
ErrorState_t I2c_Master_Receive(I2c_Handle_t *hi2c, u16 Copy_DevAddress, u8 *pData, u16 Copy_Size, u32 Copy_Timeout);
ErrorState_t I2C_Mem_Write(I2c_Handle_t *hi2c, u16 Copy_DevAddress, u16 Copy_MemAddress, u16 Copy_MemAddSize, u8 *pData, u16 Copy_Size, u32 Copy_Timeout);
ErrorState_t I2c_Mem_Read(I2c_Handle_t *hi2c, u16 Copy_DevAddress, u16 Copy_MemAddress, u16 Copy_MemAddSize, u8 *pData, u16 Copy_Size, u16 Copy_Timeout);

/* Control */
u8 I2c_GetFlag(I2c_Handle_t *hi2c, I2c_Flag_t Copy_Flag);
void I2c_Enable(I2c_Handle_t *hi2c);
void I2c_Disable(I2c_Handle_t *hi2c);

#endif  /* I2C_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: I2c_Interface.h
 *********************************************************************************************************************/