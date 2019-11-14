/*******************************************************************************
* File Name: RelayC_3.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_RelayC_3_H) /* Pins RelayC_3_H */
#define CY_PINS_RelayC_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RelayC_3_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} RelayC_3_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   RelayC_3_Read(void);
void    RelayC_3_Write(uint8 value);
uint8   RelayC_3_ReadDataReg(void);
#if defined(RelayC_3__PC) || (CY_PSOC4_4200L) 
    void    RelayC_3_SetDriveMode(uint8 mode);
#endif
void    RelayC_3_SetInterruptMode(uint16 position, uint16 mode);
uint8   RelayC_3_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void RelayC_3_Sleep(void); 
void RelayC_3_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(RelayC_3__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define RelayC_3_DRIVE_MODE_BITS        (3)
    #define RelayC_3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RelayC_3_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the RelayC_3_SetDriveMode() function.
         *  @{
         */
        #define RelayC_3_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define RelayC_3_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define RelayC_3_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define RelayC_3_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define RelayC_3_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define RelayC_3_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define RelayC_3_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define RelayC_3_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define RelayC_3_MASK               RelayC_3__MASK
#define RelayC_3_SHIFT              RelayC_3__SHIFT
#define RelayC_3_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RelayC_3_SetInterruptMode() function.
     *  @{
     */
        #define RelayC_3_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define RelayC_3_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define RelayC_3_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define RelayC_3_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(RelayC_3__SIO)
    #define RelayC_3_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(RelayC_3__PC) && (CY_PSOC4_4200L)
    #define RelayC_3_USBIO_ENABLE               ((uint32)0x80000000u)
    #define RelayC_3_USBIO_DISABLE              ((uint32)(~RelayC_3_USBIO_ENABLE))
    #define RelayC_3_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define RelayC_3_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define RelayC_3_USBIO_ENTER_SLEEP          ((uint32)((1u << RelayC_3_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << RelayC_3_USBIO_SUSPEND_DEL_SHIFT)))
    #define RelayC_3_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << RelayC_3_USBIO_SUSPEND_SHIFT)))
    #define RelayC_3_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << RelayC_3_USBIO_SUSPEND_DEL_SHIFT)))
    #define RelayC_3_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(RelayC_3__PC)
    /* Port Configuration */
    #define RelayC_3_PC                 (* (reg32 *) RelayC_3__PC)
#endif
/* Pin State */
#define RelayC_3_PS                     (* (reg32 *) RelayC_3__PS)
/* Data Register */
#define RelayC_3_DR                     (* (reg32 *) RelayC_3__DR)
/* Input Buffer Disable Override */
#define RelayC_3_INP_DIS                (* (reg32 *) RelayC_3__PC2)

/* Interrupt configuration Registers */
#define RelayC_3_INTCFG                 (* (reg32 *) RelayC_3__INTCFG)
#define RelayC_3_INTSTAT                (* (reg32 *) RelayC_3__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define RelayC_3_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(RelayC_3__SIO)
    #define RelayC_3_SIO_REG            (* (reg32 *) RelayC_3__SIO)
#endif /* (RelayC_3__SIO_CFG) */

/* USBIO registers */
#if !defined(RelayC_3__PC) && (CY_PSOC4_4200L)
    #define RelayC_3_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define RelayC_3_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define RelayC_3_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define RelayC_3_DRIVE_MODE_SHIFT       (0x00u)
#define RelayC_3_DRIVE_MODE_MASK        (0x07u << RelayC_3_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins RelayC_3_H */


/* [] END OF FILE */
