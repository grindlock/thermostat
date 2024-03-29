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

#include <stdio.h>
#include <stdlib.h>

// These are for the gpio exp.
#define ADDR (0x70)
#define REG_READ (0x00)
#define REG_WRITE (0x01)
#define REG_CONFIG (0x03)


// the address fro the temp sensor are 0x4C and 0x4D




void initialized_input_gpioExp(){
   I2C_1_I2CMasterSendStart(ADDR,I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(REG_CONFIG, 100u);
   I2C_1_I2CMasterWriteByte(0xFF, 100u);
   I2C_1_I2CMasterSendStop(100u);
}

uint8 read_thermostat_pins(){
   
    uint8 pins = 0u;

   I2C_1_I2CMasterSendStart(ADDR, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(REG_READ, 100u);
   I2C_1_I2CMasterSendRestart(ADDR,I2C_1_I2C_READ_XFER_MODE, 100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &pins,100u);
   I2C_1_I2CMasterSendStop(100u);
    
    return pins;
}

void configure_temperature_sensor2(){
        // Config register 1
   I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x09, 100u);
   I2C_1_I2CMasterWriteByte(0x84, 100u);
   I2C_1_I2CMasterSendStop(100u);
   //Config register 2
   I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x3F, 100u);
   I2C_1_I2CMasterWriteByte(0x3C, 100u);
   I2C_1_I2CMasterSendStop(100u);   
}

void configure_temperature_sensor1(){
        // Config register 1
   I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x09, 100u);
   I2C_1_I2CMasterWriteByte(0x84, 100u);
   I2C_1_I2CMasterSendStop(100u);
   //Config register 2
   I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x3F, 100u);
   I2C_1_I2CMasterWriteByte(0x3C, 100u);
   I2C_1_I2CMasterSendStop(100u);   
}

int main (void)
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

     CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    
   // I2C_1_Start();
    
    
    
    
    CEPIN_Write(1);
    
    
    RED_Write(0);
    GREEN_Write(0);
    BLUE_Write(0);
    CyDelay(500);
    RED_Write(1);
    GREEN_Write(1);
    BLUE_Write(1);
    
    I2C_1_Init();
    I2C_1_Enable();
    
    MyUART_Start();

    // call after I2C have been initiated
    configure_temperature_sensor2();
    configure_temperature_sensor1();
    initialized_input_gpioExp();


    //N-Factor correction remote 1  0x4D
// I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
//   I2C_1_I2CMasterWriteByte(0x27, 100u);
//   I2C_1_I2CMasterWriteByte(0x00, 100u);
//   I2C_1_I2CMasterSendStop(100u);





//// channel 2 beta range selection   for 0x4C
// I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 100u);
//   I2C_1_I2CMasterWriteByte(0x26, 100u);
//   I2C_1_I2CMasterWriteByte(0x07, 100u);
//   I2C_1_I2CMasterSendStop(100u);
//
//    //N-Factor correction remote 2  0x4C
// I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 100u);
//   I2C_1_I2CMasterWriteByte(0x28, 100u);
//   I2C_1_I2CMasterWriteByte(0xFF, 100u);
//   I2C_1_I2CMasterSendStop(100u);
    
    
    
    
    //initialized_input_gpioExp();
    
//    I2C_1_I2CMasterSendStart(ADDR,I2C_1_I2C_WRITE_XFER_MODE, 100u);
//   I2C_1_I2CMasterWriteByte(REG_CONFIG, 100u);
//    I2C_1_I2CMasterWriteByte(0xFF, 100u);
//   I2C_1_I2CMasterSendStop(100u);


    
//        GREEN_Write(0);
//       CyDelay(500);
//        GREEN_Write(1);
    
 
    
   
 
    int loop =  15;
    uint8_t nfacto = 0;
    
    for(;;)
    {
        
        
        
       //RED_Write(0);
      // BLUE_Write(0);
       //GREEN_Write(0);
        CyDelay(500);
        RED_Write(1);
       BLUE_Write(1);
       GREEN_Write(1);
        

   
//    GREEN_Write(0); 
//    BLUE_Write(0);
//    CyDelay(500);
//    GREEN_Write(1); 
//    BLUE_Write(1);
    
    volatile uint8 read_buff[2] = {0,0};

    
    //uint8 pins = 0u;
uint8_t temp = 0;
uint8_t tempR1 = 0;
uint8_t tempR2 = 0;
  
    
//    switch(loop){
//        case 15: 
//        nfacto = 0x7F;
//        loop-=1;
//        break;
//        
//        case 14:
//        nfacto = 0x0A;
//        loop-=1;
//        break;
//        
//        case 13:
//        nfacto = 0x08;
//        loop-=1;
//        break;
//        
//        case 12:
//        nfacto = 0x06;
//        loop-=1;
//        break;
//        
//        case 11:
//        nfacto = 0x04;
//        loop-=1;
//        break;
//        
//        case 10:
//        nfacto = 0x02;
//        loop-=1;
//        break;
//        
//        case 9:
//        nfacto = 0x01;
//        loop-=1;
//        break;
//        
//        case 8:
//        nfacto = 0x00;
//        loop-=1;
//        break;
//        
//        case 7:
//        nfacto = 0xFF;
//        loop-=1;
//        break;
//        
//        case 6:
//        nfacto = 0xFE;
//        loop-=1;
//        break;
//        
//        case 5:
//        nfacto = 0xFC;
//        loop-=1;
//        break;
//        
//        case 4:
//        nfacto = 0xFA;
//        loop-=1;
//        break;
//        
//        case 3:
//        nfacto = 0xF8;
//        loop-=1;
//        break;
//        
//        case 2:
//        nfacto = 0xF6;
//        loop-=1;
//        break;
//        
//        case 1:
//        nfacto = 0x80;
//        loop-=1;
//        break;
//        
//        case 0:
//        loop =15;
//        nfacto = 0;
//        break;
//        
//        default:
//        break;
//        
//    }
    
//    for(uint8_t x = 0; x < 15; x++){
//        
//        // channel 1 beta range selection   for 0x4D
// I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
//   I2C_1_I2CMasterWriteByte(0x25, 100u);
//   I2C_1_I2CMasterWriteByte(x, 100u);
//   I2C_1_I2CMasterSendStop(100u);
        
    
    

//  READ local sensor    
   I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x00, 100u);
   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &temp,100u);
   I2C_1_I2CMasterSendStop(100u);

//  READ remote sensor 1
  I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x01, 100u);
   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &tempR1,100u);
   I2C_1_I2CMasterSendStop(100u);


//  READ remote sensor 2
  I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x23, 100u);
   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &tempR2,100u);
   I2C_1_I2CMasterSendStop(100u);


char str[50];

sprintf(str, "Sensor 1 temperature is %d\n", (temp-64));
MyUART_PutString(str);

sprintf(str, "Sensor 1 Remote temperature 1 is %d \n", (tempR1-64));
MyUART_PutString(str);


sprintf(str, "Sensor 1 Remote temperature 2 is %d \n", (tempR2-64));
MyUART_PutString(str);

temp = tempR1 = tempR2 = 0;
//  READ local sensor  2  
   I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x00, 100u);
   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &temp,100u);
   I2C_1_I2CMasterSendStop(100u);

//  READ remote 2 sensor 1
  I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x01, 100u);
   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &tempR1,100u);
   I2C_1_I2CMasterSendStop(100u);


//  READ remote 2 sensor 2
  I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x23, 100u);
   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &tempR2,100u);
   I2C_1_I2CMasterSendStop(100u);




sprintf(str, "\n\nSensor 2 temperature is %d\n", (temp-64));
MyUART_PutString(str);

sprintf(str, "Sensor 2 Remote temperature 1 is %d \n", (tempR1-64));
MyUART_PutString(str);


sprintf(str, "Sensor 2 Remote temperature 2 is %d \n\n\n\n", (tempR2-64));
MyUART_PutString(str);



/*  ---------------------------- ACCELEROMETER -----------------------------------   */

uint8 xLSB;
uint8 xMSB;
uint8 yLSB;
uint8 yMSB;
uint8 zLSB;
uint8 zMSB;

I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x02, 100u);
I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &xLSB ,100u);
I2C_1_I2CMasterSendStop(100u);

I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x03, 100u);
I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &xMSB ,100u);
I2C_1_I2CMasterSendStop(100u);

I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x04, 100u);
I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &yLSB ,100u);
I2C_1_I2CMasterSendStop(100u);

I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x05, 100u);
I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &yMSB ,100u);
I2C_1_I2CMasterSendStop(100u);

I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x06, 100u);
I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &zLSB ,100u);
I2C_1_I2CMasterSendStop(100u);

I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x07, 100u);
I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &zMSB ,100u);
I2C_1_I2CMasterSendStop(100u);

uint16 xACC = ((xMSB << 8)| (xLSB & 0xF0)) >> 4;
uint16 yACC = ((yMSB << 8)| (yLSB & 0xF0)) >> 4;
uint16 zACC = ((zMSB << 8)| (zLSB & 0xF0)) >> 4;



sprintf(str,"\nX: %d %d    12 bit x: %d\n", xMSB, xLSB, xACC);
MyUART_PutString(str);
sprintf(str,"y: %d %d      12 bit y: %d\n", yMSB, yLSB, yACC);
MyUART_PutString(str);
sprintf(str,"Z: %d %d      12 bit z: %d\n\n\n", zMSB, zLSB, zACC);
MyUART_PutString(str);

//RelayHF_2_Write(0);
//RelayLF_1_Write(0);
//RelayC_3_Write(1);
//CyDelay(5000);
//RelayHF_2_Write(1);
//RelayC_3_Write(0);
//CyDelay(5000);
//RelayLF_1_Write(1);
//RelayHF_2_Write(0);
//CyDelay(5000);
//RelayC_3_Write(0);
//RelayHF_2_Write(0);
//RelayLF_1_Write(0);
//CyDelay(5000);




//uint16 rh = ((read_buff[0] << 8) | read_buff[1]);




//int tp = ((125 * rh)/65536)-6; //((175.72 * rh)/65536) - 46.85;//((125 * rh)/65536)-6;


    //}

 //CyDelay(1000);   
   // BLUE_Write(0); 
    //RED_Write(0);
//    CyDelay(500);
//    BLUE_Write(1); 
//    RED_Write(1);
//    read_buff[0] = pins;

read_buff[0] = read_thermostat_pins();
//
sprintf(str, "\ntemperature is 0x%x\n", read_buff[0]);
MyUART_PutString(str);
//
     if(read_buff[0] == 0){RED_Write(0); GREEN_Write(1);
    BLUE_Write(1); CyDelay(500);}
     
       if ((read_buff[0] & 0x01)){BLUE_Write(0);  RED_Write(1); GREEN_Write(1);CyDelay(500);} //Blue   PIN 0
      else{BLUE_Write(1);}
    
      if((read_buff[0] & 0x02)){GREEN_Write(0); RED_Write(1);BLUE_Write(1);CyDelay(500);} //Green    PIN 1
    else{GREEN_Write(1);}
    
       if((read_buff[0]&0x04)){GREEN_Write(0); BLUE_Write(0);RED_Write(1);
       RelayC_3_Write(1); Comp_out_Write(1);CyDelay(500);} //Cyan    PIN 2
    else{RelayC_3_Write(0); Comp_out_Write(0);GREEN_Write(1); BLUE_Write(1);}
    
      if((read_buff[0] & 0x08)){GREEN_Write(0); RED_Write(0); BLUE_Write(1); 
       RelayHF_2_Write(1);  HighF_out_Write(1);CyDelay(500);} //yellow   PIN 3
    else{RelayHF_2_Write(0);  HighF_out_Write(0);GREEN_Write(1); RED_Write(1);}
    
     if((read_buff[0] & 0x10))
    {BLUE_Write(0); 
        RED_Write(0); 
        GREEN_Write(1);
        LowF_out_Write(1);
        RelayLF_1_Write(1);
        CyDelay(500);}
    else{RelayLF_1_Write(0); LowF_out_Write(0);BLUE_Write(1); RED_Write(1);}//purple   PIN 4
//    
//    CyDelay(1000);
//    Comp_out_Write(0);
//    HighF_out_Write(0);
//    LowF_out_Write(0);
//    RED_Write(1);
//    GREEN_Write(1);
//    BLUE_Write(1);
      read_buff[0] = 0u;
    
    //CyDelay(2000);
    
    }
    
    
}

/* [] END OF FILE */
