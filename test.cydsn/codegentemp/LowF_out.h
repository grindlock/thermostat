/*******************************************************************************
* File Name: LowF_out.h  
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

#if !defined(CY_PINS_LowF_out_H) /* Pins LowF_out_H */
#define CY_PINS_LowF_out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LowF_out_aliases.h"


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
} LowF_out_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   LowF_out_Read(void);
void    LowF_out_Write(uint8 value);
uint8   LowF_out_ReadDataReg(void);
#if defined(LowF_out__PC) || (CY_PSOC4_4200L) 
    void    LowF_out_SetDriveMode(uint8 mode);
#endif
void    LowF_out_SetInterruptMode(uint16 position, uint16 mode);
uint8   LowF_out_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void LowF_out_Sleep(void); 
void LowF_out_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(LowF_out__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define LowF_out_DRIVE_MODE_BITS        (3)
    #define LowF_out_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LowF_out_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the LowF_out_SetDriveMode() function.
         *  @{
         */
        #define LowF_out_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define LowF_out_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define LowF_out_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define LowF_out_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define LowF_out_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define LowF_out_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define LowF_out_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define LowF_out_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define LowF_out_MASK               LowF_out__MASK
#define LowF_out_SHIFT              LowF_out__SHIFT
#define LowF_out_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LowF_out_SetInterruptMode() function.
     *  @{
     */
        #define LowF_out_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define LowF_out_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define LowF_out_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define LowF_out_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(LowF_out__SIO)
    #define LowF_out_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(LowF_out__PC) && (CY_PSOC4_4200L)
    #define LowF_out_USBIO_ENABLE               ((uint32)0x80000000u)
    #define LowF_out_USBIO_DISABLE              ((uint32)(~LowF_out_USBIO_ENABLE))
    #define LowF_out_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define LowF_out_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define LowF_out_USBIO_ENTER_SLEEP          ((uint32)((1u << LowF_out_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << LowF_out_USBIO_SUSPEND_DEL_SHIFT)))
    #define LowF_out_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << LowF_out_USBIO_SUSPEND_SHIFT)))
    #define LowF_out_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << LowF_out_USBIO_SUSPEND_DEL_SHIFT)))
    #define LowF_out_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(LowF_out__PC)
    /* Port Configuration */
    #define LowF_out_PC                 (* (reg32 *) LowF_out__PC)
#endif
/* Pin State */
#define LowF_out_PS                     (* (reg32 *) LowF_out__PS)
/* Data Register */
#define LowF_out_DR                     (* (reg32 *) LowF_out__DR)
/* Input Buffer Disable Override */
#define LowF_out_INP_DIS                (* (reg32 *) LowF_out__PC2)

/* Interrupt configuration Registers */
#define LowF_out_INTCFG                 (* (reg32 *) LowF_out__INTCFG)
#define LowF_out_INTSTAT                (* (reg32 *) LowF_out__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define LowF_out_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(LowF_out__SIO)
    #define LowF_out_SIO_REG            (* (reg32 *) LowF_out__SIO)
#endif /* (LowF_out__SIO_CFG) */

/* USBIO registers */
#if !defined(LowF_out__PC) && (CY_PSOC4_4200L)
    #define LowF_out_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define LowF_out_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define LowF_out_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define LowF_out_DRIVE_MODE_SHIFT       (0x00u)
#define LowF_out_DRIVE_MODE_MASK        (0x07u << LowF_out_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins LowF_out_H */


/* [] END OF FILE */
