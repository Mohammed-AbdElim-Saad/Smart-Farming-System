/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  - Musa Mahmoud
 *	   	   File:  - Switch_Program.c
 *		  Layer:  - Hal
 *       Module:  - Switch
 *		Version:  - 1.0
 *	
 *  Description:  - A switch driver to get the switch state(pressed or not pressed) however the pulling type is
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

#include "Gpio_Interface.h"

#include "Switch_Config.h"
#include "Switch_Private.h"
#include "Switch_Interface.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static bool IsSwitchConfigValid(Switch_Config_t *Copy_SwitchConfig)
* \Description     : Check the switch configurations' values
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_SwitchConfig    Pointer to structure of switch configuration
* \Parameters (out): None
* \Return value:   : bool
*******************************************************************************/
static bool IsSwitchConfigValid(Switch_Config_t *Copy_SwitchConfig)
{
    if ((Copy_SwitchConfig->Port > GPIO_PORTH) || (Copy_SwitchConfig->Port < GPIO_PORTA) 
        || (Copy_SwitchConfig->Pin > GPIO_PIN15) || (Copy_SwitchConfig->Pin < GPIO_PIN0)
        || (Copy_SwitchConfig->SwitchType > SWITCH_TEMPORARY) || (Copy_SwitchConfig->SwitchType < SWITCH_PERMANENT)
        || (Copy_SwitchConfig->PullType > SWITCH_PULL_DOWN) || (Copy_SwitchConfig->PullType < SWITCH_PULL_UP))
    {
        return FALSE;
    }

    return TRUE;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if (SOFTWARE_DEBOUNCING == ENABLED) && (DEBOUNCING_TECHNIQUE == WAIT_AND_DOUBLE_CHECK)
/******************************************************************************
* \Syntax          : ErrorState_t Switch_GetStateDebounce(Switch_Config_t *Copy_SwitchConfig, Switch_State_t *Copy_SwitchState, Switch_Callback Delay, double Copy_DelayAmount)
* \Description     : Get the switch current state(pressed or not pressed) after debouncing it
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : - Copy_SwitchConfig    Pointer to structure of switch configuration
*                    - Delay                Pointer to function for the delay used to debounce the switch
*                    - Copy_DelayAmount     The delay amount needed for debouncing the switch
* \Parameters (out): Copy_SwitchState     Pointer to return the switch current state
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Switch_GetStateDebounce(Switch_Config_t *Copy_SwitchConfig, Switch_State_t *Copy_SwitchState, Switch_Callback Delay, double Copy_DelayAmount)
{
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_u8PinValue;

    /* Check the function arguments then early return */
    if ((NULL == Copy_SwitchConfig) || (NULL == Copy_SwitchState) || (NULL == Delay))
    {
        return E_NULL_POINTER;
    }
    else if (!IsSwitchConfigValid(Copy_SwitchConfig))
    {
        return E_WRONG_OPTION;
    }

    /* Applying software debouncing using wait and double check technique */
    /* Check if the button is temporary(not a self-locking) then debounce it */
    if (SWITCH_TEMPORARY == Copy_SwitchConfig->SwitchType)
    {   
        /* Get the pin value and debouncing using wait and double check technique */
        Local_ErrorState = DIO_u8GetPinValue(Copy_SwitchConfig->Port, Copy_SwitchConfig->Pin, &Local_u8PinValue);
        Delay(Copy_DelayAmount);
        Local_ErrorState = DIO_u8GetPinValue(Copy_SwitchConfig->Port, Copy_SwitchConfig->Pin, &Local_u8PinValue);
    }
    else if (SWITCH_PERMANENT == Copy_SwitchConfig->SwitchType)
    {
        /* Get the pin value */
        Local_ErrorState = DIO_u8GetPinValue(Copy_SwitchConfig->Port, Copy_SwitchConfig->Pin, &Local_u8PinValue);
    }

    if (SWITCH_PULL_UP == Copy_SwitchConfig->PullType)
    {
        if (GPIO_PIN_LOW == Local_u8PinValue)
        {
            *Copy_SwitchState = SWITCH_PRESSED;
        }
        else if (GPIO_PIN_HIGH == Local_u8PinValue)
        {
            *Copy_SwitchState = SWITCH_NOT_PRESSED;
        }
    }
    else if (SWITCH_PULL_DOWN == Copy_SwitchConfig->PullType)
    {
        if(GPIO_PIN_LOW == Local_u8PinValue)
        {
            *Copy_SwitchState = SWITCH_NOT_PRESSED;
        }
        else if (GPIO_PIN_HIGH == Local_u8PinValue)
        {
            *Copy_SwitchState = SWITCH_PRESSED;
        }
    }

    return Local_ErrorState;
}
#endif /* (SOFTWARE_DEBOUNCING == ENABLED) && (DEBOUNCING_TECHNIQUE == WAIT_AND_DOUBLE_CHECK) End */

#if IS_PERMANENT_SWITCH_USED == USED
/******************************************************************************
* \Syntax          : ErrorState_t Switch_GetState(Switch_Config_t *Copy_SwitchConfig, Switch_State_t *Copy_SwitchState)
* \Description     : Get the switch current state(pressed or not pressed)
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_SwitchConfig    Pointer to structure of switch configuration
* \Parameters (out): Copy_SwitchState     Pointer to return the switch current state
* \Return value:   : ErrorState_t
*******************************************************************************/
ErrorState_t Switch_GetState(Switch_Config_t *Copy_SwitchConfig, Switch_State_t *Copy_SwitchState)
{
    ErrorState_t Local_ErrorState = E_OK;
    u8 Local_u8PinValue;

    /* Check the function arguments then early return */
    if ((NULL == Copy_SwitchConfig) || (NULL == Copy_SwitchState))
    {
        return E_NULL_POINTER;
    }
    else if (!IsSwitchConfigValid(Copy_SwitchConfig))
    {
        return E_WRONG_OPTION;
    }

    /* Get the pin value */
    Local_ErrorState = DIO_u8GetPinValue(Copy_SwitchConfig->Port, Copy_SwitchConfig->Pin, &Local_u8PinValue);

    if (SWITCH_PULL_UP == Copy_SwitchConfig->PullType)
    {
        if (GPIO_PIN_LOW == Local_u8PinValue)
        {
            *Copy_SwitchState = SWITCH_PRESSED;
        }
        else if (GPIO_PIN_HIGH == Local_u8PinValue)
        {
            *Copy_SwitchState = SWITCH_NOT_PRESSED;
        }
    }
    else if (SWITCH_PULL_DOWN == Copy_SwitchConfig->PullType)
    {
        if(GPIO_PIN_LOW == Local_u8PinValue)
        {
            *Copy_SwitchState = SWITCH_NOT_PRESSED;
        }
        else if (GPIO_PIN_HIGH == Local_u8PinValue)
        {
            *Copy_SwitchState = SWITCH_PRESSED;
        }
    }

    return Local_ErrorState;
}
#endif /* IS_PERMANENT_SWITCH_USED == USED End */

/**********************************************************************************************************************
 *  END OF FILE: Switch_Interface.h
 *********************************************************************************************************************/
