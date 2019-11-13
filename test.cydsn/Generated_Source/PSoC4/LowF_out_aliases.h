/*******************************************************************************
* File Name: LowF_out.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LowF_out_ALIASES_H) /* Pins LowF_out_ALIASES_H */
#define CY_PINS_LowF_out_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LowF_out_0			(LowF_out__0__PC)
#define LowF_out_0_PS		(LowF_out__0__PS)
#define LowF_out_0_PC		(LowF_out__0__PC)
#define LowF_out_0_DR		(LowF_out__0__DR)
#define LowF_out_0_SHIFT	(LowF_out__0__SHIFT)
#define LowF_out_0_INTR	((uint16)((uint16)0x0003u << (LowF_out__0__SHIFT*2u)))

#define LowF_out_INTR_ALL	 ((uint16)(LowF_out_0_INTR))


#endif /* End Pins LowF_out_ALIASES_H */


/* [] END OF FILE */
