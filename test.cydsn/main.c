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

#define ADDR_POWER1 (0x74)
#define ADDR_POWER2 (0x75)
#define ADDR_POWER3 (0x76)
#define REG_POWER_VERSION (0x04)

typedef struct{
    
    uint8 localTemp;
    uint8 remoteTemp1;
    uint8 remoteTemp2; 
    uint8 remoteTemp3;
    uint8 remoteTemp4;
    uint16 humidity;
    uint16 voltCompressor;
    uint16 voltFan;
    uint16 volt;
    uint32 currentCompressor;
    uint32 currentFan; 
    uint32 current;
    uint16 lineFreqComp;
    uint16 lineFreqFan;
    uint16 lineFreq;
    uint16 airFlow;
    uint16 accX;
    uint16 accY;
    uint16 accZ;
    
}dataCollected;

dataCollected sensorData;
// 5 bytes
typedef struct{
    uint8 compressor;
    uint8 fanLow;
    uint8 fanHigh;
    uint8 setTemperature;
    uint8 ambientTemp;
} thermostatData ;

thermostatData thermo;

uint8 setTemperature = 0;


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

    
uint8_t temp1 = 0;
uint8_t tempR1 = 0;
uint8_t tempR2 = 0;
uint8_t temp2 = 0;
uint8_t tempR12 = 0;    
uint8_t tempR22 = 0;
    
thermo.setTemperature = 24;
    
    for(;;)
    {
        CyDelay(500);
        RED_Write(1);
       BLUE_Write(1);
       GREEN_Write(1);

    
    volatile uint8 read_buff[2] = {0,0};

//uint8 pins = 0u;

  
    

        
    // -----------------------read temperatures--------------------------------------
    

//  READ local sensor    
   I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x00, 100u);
   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.localTemp,100u);
   I2C_1_I2CMasterSendStop(100u);

//  READ remote sensor 1
  I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x01, 100u);
   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.remoteTemp1,100u);
   I2C_1_I2CMasterSendStop(100u);


//  READ remote sensor 2
  I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x23, 100u);
   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.remoteTemp2,100u);
   I2C_1_I2CMasterSendStop(100u);


char str[50];

sprintf(str, "Sensor 1 temperature is %d\n", (sensorData.localTemp-64));
MyUART_PutString(str);

sprintf(str, "Sensor 1 Remote temperature 1 is %d \n", (sensorData.remoteTemp1-64));
MyUART_PutString(str);


sprintf(str, "Sensor 1 Remote temperature 2 is %d \n", (sensorData.remoteTemp2-64));
MyUART_PutString(str);

//temp = tempR1 = tempR2 = 0;
//  READ local sensor  2  
   I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x00, 100u);
   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &temp2,100u);
   I2C_1_I2CMasterSendStop(100u);

//  READ remote 2 sensor 1
  I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x01, 100u);
   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.remoteTemp3,100u);
   I2C_1_I2CMasterSendStop(100u);


//  READ remote 2 sensor 2
  I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x23, 100u);
   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.remoteTemp4,100u);
   I2C_1_I2CMasterSendStop(100u);




sprintf(str, "\n\nSensor 2 temperature is %d\n", (temp2-64));
MyUART_PutString(str);

sprintf(str, "Sensor 2 Remote temperature 1 is %d \n", (sensorData.remoteTemp3-64));
MyUART_PutString(str);


sprintf(str, "Sensor 2 Remote temperature 2 is %d \n\n\n\n", (sensorData.remoteTemp4-64));
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

sensorData.accX = ((xMSB << 8)| (xLSB & 0xF0)) >> 4;
sensorData.accY = ((yMSB << 8)| (yLSB & 0xF0)) >> 4;
sensorData.accZ = ((zMSB << 8)| (zLSB & 0xF0)) >> 4;



sprintf(str,"\nX: %d %d    12 bit x: %d\n", xMSB, xLSB, sensorData.accX);
MyUART_PutString(str);
sprintf(str,"y: %d %d      12 bit y: %d\n", yMSB, yLSB, sensorData.accY);
MyUART_PutString(str);
sprintf(str,"Z: %d %d      12 bit z: %d\n\n\n", zMSB, zLSB, sensorData.accZ);
MyUART_PutString(str);

// ---------------  Read humidity ---------------

I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x07, 100u);
I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &read_buff[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

uint16 rh = ((read_buff[0] << 8) | read_buff[1]);

sensorData.humidity = ((125 * rh)/65536)-6; 

sprintf(str, "\nThe humidity is %d\n", sensorData.humidity);
MyUART_PutString(str);

// ---------------------  Read thermostat---------------------

uint8 pins = read_thermostat_pins();


sprintf(str, "\nThermostast pins are 0x%x\n", pins);
MyUART_PutString(str);


// ------------------------------- power sensors-----------------------
uint8 ver[2] = {0,0};

I2C_1_I2CMasterSendStart(ADDR_POWER1,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(REG_POWER_VERSION, 100u);
I2C_1_I2CMasterSendRestart(ADDR_POWER1, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &ver[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &ver[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

sprintf(str, "power 1 ver: %d %d\n", ver[0], ver[1]);
MyUART_PutString(str);

I2C_1_I2CMasterSendStart(ADDR_POWER2,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(REG_POWER_VERSION, 100u);
I2C_1_I2CMasterSendRestart(ADDR_POWER2, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &ver[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &ver[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

sprintf(str, "power 2 ver: %d %d\n", ver[0], ver[1]);
MyUART_PutString(str);

I2C_1_I2CMasterSendStart(ADDR_POWER3,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(REG_POWER_VERSION, 100u);
I2C_1_I2CMasterSendRestart(ADDR_POWER3, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &ver[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &ver[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

sprintf(str, "power 3 ver: %d %d\n", ver[0], ver[1]);
MyUART_PutString(str);


// --- runs relays ---------


     if(pins == 0){
        
        if(temp1 > setTemperature){
            RED_Write(0); 
            GREEN_Write(1);
            BLUE_Write(1);
            RelayC_3_Write(1);
            Comp_out_Write(1);
            thermo.compressor = 1;
        }
        else if(temp1 <= setTemperature){
            RelayC_3_Write(0);
            Comp_out_Write(0);
            thermo.compressor = 0;
        }
    }
     
       if ((pins & 0x01)){
        BLUE_Write(0);  
        RED_Write(1); 
        GREEN_Write(1);
       } //Blue   PIN 0
      else{BLUE_Write(1);}
    
      if((pins & 0x02)){
        GREEN_Write(0); 
        RED_Write(1);
        BLUE_Write(1);
      } //Green    PIN 1
    else{
        GREEN_Write(1);
        }
    
       if((pins&0x04)){ //Comp pin
        GREEN_Write(0); 
        BLUE_Write(0);
        RED_Write(1);
        RelayC_3_Write(1); 
        Comp_out_Write(1);
        CyDelay(500);
       } //Cyan    PIN 2
    else{
        RelayC_3_Write(0);
        Comp_out_Write(0);
        GREEN_Write(1); 
        BLUE_Write(1);
    }
    
      if((pins & 0x08)){  // High Fan 
        GREEN_Write(0); 
        RED_Write(0); 
        BLUE_Write(1); 
        RelayHF_2_Write(1);  
        HighF_out_Write(1);
    } //yellow   PIN 3
    else{
        RelayHF_2_Write(0);  
        HighF_out_Write(0);
        GREEN_Write(1); 
        RED_Write(1);
    }
    
     if((pins & 0x10)){  // Low Fan
        BLUE_Write(0); 
        RED_Write(0); 
        GREEN_Write(1);
        LowF_out_Write(1);
        RelayLF_1_Write(1);
     }
    else{
        RelayLF_1_Write(0); 
        LowF_out_Write(0);
        BLUE_Write(1); 
        RED_Write(1);
    }//purple   PIN 4

      read_buff[0] = 0u;
   
    }
    
    
}

/* [] END OF FILE */
