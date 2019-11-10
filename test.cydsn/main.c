/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

#define ADDR (0x70)
#define REG_READ (0x00)
#define REG_WRITE (0x01)
#define REG_CONFIG (0x03)


uint8 read_buff[1] = {0};


int main (void)
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    
    I2C_1_Start();
    
    CEPIN_Write(1);
    
    uint8 write_buff[2] ={REG_READ, 0};
 
    
   
    
    
    for(;;)
    {
         I2C_1_I2CMasterWriteBuf(ADDR, write_buff, 1, I2C_1_I2C_MODE_COMPLETE_XFER);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT) == 0){}
    
         I2C_1_I2CMasterReadBuf(ADDR, read_buff, 1, I2C_1_I2C_MODE_REPEAT_START);
    while((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_RD_CMPLT) == 0){}
    
    
     if(read_buff[0] == 0){RED_Write(0);}
     
     else if ((read_buff[0] & 0x01)==1){BLUE_Write(0);}      //PIN 0
    
     else if((read_buff[0]&0x02)==1){GREEN_Write(0);}       // PIN 1
    
     else if((read_buff[0]&0x04)==1){GREEN_Write(0); BLUE_Write(0);} //Cyan    PIN 2
    
    else if((read_buff[0]&0x08)==1){GREEN_Write(0); RED_Write(0); } //yellow   PIN 3
    
    else if((read_buff[0]&00010000)==1){BLUE_Write(0); RED_Write(0); } //purple   PIN 4
    
    CyDelay(200);
    RED_Write(1);
    GREEN_Write(1);
    BLUE_Write(1);
    
    
    }
    
    
}

/* [] END OF FILE */
