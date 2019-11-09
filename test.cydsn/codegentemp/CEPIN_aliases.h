/*******************************************************************************
* File Name: CEPIN.h  
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

#if !defined(CY_PINS_CEPIN_ALIASES_H) /* Pins CEPIN_ALIASES_H */
#define CY_PINS_CEPIN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CEPIN_0			(CEPIN__0__PC)
#define CEPIN_0_PS		(CEPIN__0__PS)
#define CEPIN_0_PC		(CEPIN__0__PC)
#define CEPIN_0_DR		(CEPIN__0__DR)
#define CEPIN_0_SHIFT	(CEPIN__0__SHIFT)
#define CEPIN_0_INTR	((uint16)((uint16)0x0003u << (CEPIN__0__SHIFT*2u)))

#define CEPIN_INTR_ALL	 ((uint16)(CEPIN_0_INTR))


#endif /* End Pins CEPIN_ALIASES_H */


/* [] END OF FILE */
