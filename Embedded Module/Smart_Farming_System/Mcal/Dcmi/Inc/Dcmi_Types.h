/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud, Mazen and Musa
 *	   	   File:  Dcmi_Types.h
 *		  Layer:  Mcal
 *       Module:  Dcmi
 *		Version:  1.00
 *	
 *  Description:  -     
 *  
 *********************************************************************************************************************/
#ifndef DCMI_TYPE_H
#define DCMI_TYPE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
	DCMI_END_OF_FRAME=0,
	DCMI_OVERRUN_OF_DATA_RECEPTION=2,
	DCMI_ERROR_DETECTION=4,
	DCMI_SYNCHRONIZATION_FRAME=8,
	DCMI_END_OF_LINE=16
}Dcmi_InterruptId_t;

typedef enum
{
	DCMI_INT_ENABLE=0,
	DCMI_INT_DISABLE
}Dcmi_InterruptState_t;

#endif  /* DCMI_TYPE_H */

/**********************************************************************************************************************
 *  END OF FILE: Dcmi_Types.h
 *********************************************************************************************************************/
