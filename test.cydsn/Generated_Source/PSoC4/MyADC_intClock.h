/*******************************************************************************
* File Name: MyADC_intClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_MyADC_intClock_H)
#define CY_CLOCK_MyADC_intClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void MyADC_intClock_StartEx(uint32 alignClkDiv);
#define MyADC_intClock_Start() \
    MyADC_intClock_StartEx(MyADC_intClock__PA_DIV_ID)

#else

void MyADC_intClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void MyADC_intClock_Stop(void);

void MyADC_intClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 MyADC_intClock_GetDividerRegister(void);
uint8  MyADC_intClock_GetFractionalDividerRegister(void);

#define MyADC_intClock_Enable()                         MyADC_intClock_Start()
#define MyADC_intClock_Disable()                        MyADC_intClock_Stop()
#define MyADC_intClock_SetDividerRegister(clkDivider, reset)  \
    MyADC_intClock_SetFractionalDividerRegister((clkDivider), 0u)
#define MyADC_intClock_SetDivider(clkDivider)           MyADC_intClock_SetDividerRegister((clkDivider), 1u)
#define MyADC_intClock_SetDividerValue(clkDivider)      MyADC_intClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define MyADC_intClock_DIV_ID     MyADC_intClock__DIV_ID

#define MyADC_intClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define MyADC_intClock_CTRL_REG   (*(reg32 *)MyADC_intClock__CTRL_REGISTER)
#define MyADC_intClock_DIV_REG    (*(reg32 *)MyADC_intClock__DIV_REGISTER)

#define MyADC_intClock_CMD_DIV_SHIFT          (0u)
#define MyADC_intClock_CMD_PA_DIV_SHIFT       (8u)
#define MyADC_intClock_CMD_DISABLE_SHIFT      (30u)
#define MyADC_intClock_CMD_ENABLE_SHIFT       (31u)

#define MyADC_intClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << MyADC_intClock_CMD_DISABLE_SHIFT))
#define MyADC_intClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << MyADC_intClock_CMD_ENABLE_SHIFT))

#define MyADC_intClock_DIV_FRAC_MASK  (0x000000F8u)
#define MyADC_intClock_DIV_FRAC_SHIFT (3u)
#define MyADC_intClock_DIV_INT_MASK   (0xFFFFFF00u)
#define MyADC_intClock_DIV_INT_SHIFT  (8u)

#else 

#define MyADC_intClock_DIV_REG        (*(reg32 *)MyADC_intClock__REGISTER)
#define MyADC_intClock_ENABLE_REG     MyADC_intClock_DIV_REG
#define MyADC_intClock_DIV_FRAC_MASK  MyADC_intClock__FRAC_MASK
#define MyADC_intClock_DIV_FRAC_SHIFT (16u)
#define MyADC_intClock_DIV_INT_MASK   MyADC_intClock__DIVIDER_MASK
#define MyADC_intClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_MyADC_intClock_H) */

/* [] END OF FILE */
