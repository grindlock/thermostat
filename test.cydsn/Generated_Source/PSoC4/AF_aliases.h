/*******************************************************************************
* File Name: AF.h  
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

#if !defined(CY_PINS_AF_ALIASES_H) /* Pins AF_ALIASES_H */
#define CY_PINS_AF_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define AF_0			(AF__0__PC)
#define AF_0_PS		(AF__0__PS)
#define AF_0_PC		(AF__0__PC)
#define AF_0_DR		(AF__0__DR)
#define AF_0_SHIFT	(AF__0__SHIFT)
#define AF_0_INTR	((uint16)((uint16)0x0003u << (AF__0__SHIFT*2u)))

#define AF_INTR_ALL	 ((uint16)(AF_0_INTR))


#endif /* End Pins AF_ALIASES_H */


/* [] END OF FILE */
