/*******************************************************************************
* File Name: RelayC_3.h  
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

#if !defined(CY_PINS_RelayC_3_ALIASES_H) /* Pins RelayC_3_ALIASES_H */
#define CY_PINS_RelayC_3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define RelayC_3_0			(RelayC_3__0__PC)
#define RelayC_3_0_PS		(RelayC_3__0__PS)
#define RelayC_3_0_PC		(RelayC_3__0__PC)
#define RelayC_3_0_DR		(RelayC_3__0__DR)
#define RelayC_3_0_SHIFT	(RelayC_3__0__SHIFT)
#define RelayC_3_0_INTR	((uint16)((uint16)0x0003u << (RelayC_3__0__SHIFT*2u)))

#define RelayC_3_INTR_ALL	 ((uint16)(RelayC_3_0_INTR))


#endif /* End Pins RelayC_3_ALIASES_H */


/* [] END OF FILE */
