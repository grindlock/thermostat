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

CYBLE_GATT_HANDLE_VALUE_PAIR_T thermoHandle;

// These are for the gpio exp.
#define ADDR (0x70)
#define REG_READ (0x00)
#define REG_WRITE (0x01)
#define REG_CONFIG (0x03)

#define ADDR_POWER1 (0x74) // compressor
#define ADDR_POWER2 (0x75) // High Fan
#define ADDR_POWER3 (0x76) // Low Fan
#define REG_POWER_VERSION (0x04)

// the address fro the temp sensor are 0x4C for A model and 0x4D for B model.

int interruptFlag = 0;
uint8 isNotify = 0;
uint8 updateIsNotifyCCCDAttr = 0;
uint8 bleConnected = 0;
char uartStr[50];

uint8 gpioPins = 0u;
uint16 adcRead = 0u;


typedef struct{
    
    uint8 localTemp;
    uint8 humidity;
    uint8 remoteTemp1;
    uint8 remoteTemp2; 
    uint8 remoteTemp3;
    uint8 remoteTemp4;
    
    uint16 voltCompressor;
    uint16 voltFan;
    uint16 volt;
    
    uint32 currentCompressor;
    uint32 currentFan; 
    uint32 current;
    
    uint16 lineFreqComp;
    uint16 lineFreqFan;
    uint16 lineFreq;
    
    
    uint8 accX;
    uint8 accY;
    uint8 accZ;
    
    uint16 airFlow;
    
}dataCollected;

 dataCollected sensorData;
// 5 bytes
typedef struct{
    uint8 compressor;
    uint8 fanLow;
    uint8 fanHigh;
    uint8 setTemperature;
    uint8 ambientTemp;
    uint8 power;
    uint8 test;
} thermostatData ;



 thermostatData thermo;

typedef struct{
    int8 err_Comp_volt;
    int8 err_Comp_curr;
    int8 err_LFan_volt;
    int8 err_LFan_curr;
    int8 err_HFan_volt;
    int8 err_HFan_curr;
    
}errorCode;

errorCode errorPower;

uint8 setTemperature = 0;

uint8 prevComp = 0;
uint8 prevLFan = 0;
uint8 prevHFan = 0;



void updateThermostatData(void){
    
    
    uint8 thermoTemp[] = {thermo.compressor, thermo.fanLow, thermo.fanHigh,
    thermo.setTemperature, thermo.ambientTemp, thermo.power, thermo.test};
    thermoHandle.attrHandle = CYBLE_RVAC_THERMOSTAT_THERMOCCCD_DESC_HANDLE;
    thermoHandle.value.val = (uint8 *) thermoTemp;
    thermoHandle.value.len = 7; 
    thermoHandle.value.actualLen = 7; 
    
    CyBle_GattsWriteAttributeValue(&thermoHandle, 0, &cyBle_connHandle, 0);
}

void bleStack(uint32 event, void *eventParam){
    
    CYBLE_GATTS_WRITE_REQ_PARAM_T wrReq;

    
    switch(event){
    
     
        case CYBLE_EVT_STACK_ON:
          CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
//            if(apiResult != CYBLE_ERROR_OK){
//            // DBG_PRINTF("Start Advertisement API Error: %d \r\n",apiResult);   
//            }
            //DBG_PRINTF("Bluetooth On, StartAdvertisement with addr: ");
//            localAddr.type = 0u;
//            CyBle_GetDeviceAddress(&localAddr);
//            for(uint i = CYBLE_GAP_BD_ADDR_SIZE; i > 0u; i--)
//            {
//                DBG_PRINTF("%2.2x", localAddr.bdAddr[i-1]);
//            }
//            DBG_PRINTF("\r\n");
            break; //(Claudio Modified) Is there a reason why we didn't have a break expression in this case? 
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            CyBle_GappStopAdvertisement(); 
            break;
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            isNotify = 0;
            bleConnected = 0; // test this
            break;
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
             if(CyBle_GetState() == CYBLE_STATE_DISCONNECTED){
                 CyBle_GappStartAdvertisement(CYBLE_SCANNING_FAST);
            }
            break;
        case CYBLE_EVT_GATT_CONNECT_IND:
            bleConnected = 1;
            CyBle_GappStopAdvertisement();
            break;
        case CYBLE_EVT_GATT_DISCONNECT_IND:
            isNotify = 0;
            bleConnected = 0;
            // Update the notifications CCCD
            updateIsNotifyCCCDAttr = 1;
            
            // update the thermostat array with the thermosstat info.
            // ex. themostat[0] = readSensor();
            // update the data in the thermostat attibute
            updateThermostatData();
            
           break;
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReq = *(CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam; //CYBLE_DAC_SERVICE_VOLT_VOLTCCCD_DESC_HANDLE
           
            // This handle the notifications
            if(wrReq.handleValPair.attrHandle == CYBLE_RVAC_SENSORS_SENSORCCCD_DESC_HANDLE){
                
               // CyBle_GattsWriteAttributeValue( &wrReq->handleValPair, 0, &connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                isNotify = wrReq.handleValPair.value.val[0];//CYBLE_RVAC_SENSOR_SENSORCCCD_DESC_INDEX];
                
                updateIsNotifyCCCDAttr = 1;
            }
            
            // This handle data incoming
            if(wrReq.handleValPair.attrHandle == CYBLE_RVAC_THERMOSTAT_CHAR_HANDLE){
            
                thermo.compressor = wrReq.handleValPair.value.val[0];
                thermo.fanLow= wrReq.handleValPair.value.val[1];
                thermo.fanHigh = wrReq.handleValPair.value.val[2];
                thermo.setTemperature = wrReq.handleValPair.value.val[3];
                thermo.power = wrReq.handleValPair.value.val[5];
                thermo.test = wrReq.handleValPair.value.val[6];
                
                sprintf(uartStr, "-----------------    comp %d   flow %d   dhigh %d power %d\n", thermo.compressor,thermo.fanLow, thermo.fanHigh, thermo.power);
                MyUART_PutString(uartStr);
               // thermostat[0] = thermo.compressor;
               
                updateThermostatData();
                
            }

            CyBle_GattsWriteRsp(cyBle_connHandle);
            
            break; 
        
     default:
        break;
    }
    
}
// function to read error data on the phone
void send_Error_Power_to_Phone(){
    CYBLE_GATT_HANDLE_VALUE_PAIR_T errorRead;
    
    uint8 err[] = {errorPower.err_Comp_volt, errorPower.err_Comp_curr, errorPower.err_LFan_volt,
        errorPower.err_LFan_curr, errorPower.err_HFan_volt, errorPower.err_HFan_curr};
    
    errorRead.attrHandle = CYBLE_RVAC_ERROR_CODES_CHAR_HANDLE;
    errorRead.value.val = (uint8 *) &err;
    errorRead.value.len = 6;
    
    CyBle_GattsWriteAttributeValue(&errorRead, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
}

// function to read thermostat data on the phone
void send_Thermo_to_phone(){
    CYBLE_GATT_HANDLE_VALUE_PAIR_T thermoRead;
    
    uint8 readThermo[7]; 
    readThermo[0] = thermo.compressor;
    readThermo[1] = thermo.fanLow;
    readThermo[2] = thermo.fanHigh;
    readThermo[3] = thermo.setTemperature;
    readThermo[4] = thermo.ambientTemp;
    readThermo[5] = thermo.power;
    readThermo[6] = thermo.test;
   
    
     thermoRead.attrHandle = CYBLE_RVAC_THERMOSTAT_CHAR_HANDLE;
        thermoRead.value.val = (uint8 *) &readThermo;
        thermoRead.value.len = 7;
    
   CyBle_GattsWriteAttributeValue(&thermoRead, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
}

void SendDataNotify( ){
    CYBLE_GATTS_HANDLE_VALUE_NTF_T notiHandle;
    
      uint8 dataForBLE[] = {sensorData.localTemp, sensorData.humidity, sensorData.remoteTemp1, sensorData.remoteTemp2, sensorData.remoteTemp3, sensorData.remoteTemp4,
        (sensorData.voltCompressor/10), (sensorData.voltCompressor%10), (sensorData.voltFan/10), (sensorData.voltFan%10),
        (sensorData.volt/10), (sensorData.volt%10), (sensorData.currentCompressor/1000), (sensorData.currentCompressor/100),
        (sensorData.currentCompressor/10), (sensorData.currentCompressor%10), (sensorData.currentFan/1000), (sensorData.currentFan/100),
        (sensorData.currentFan/10),(sensorData.currentFan%10),(sensorData.current/1000), (sensorData.current/100), (sensorData.current/10),
        (sensorData.current%10),(sensorData.lineFreqComp/10), (sensorData.lineFreqComp%10), (sensorData.lineFreqFan/10),
        (sensorData.lineFreqFan%10), (sensorData.lineFreq/10), (sensorData.lineFreq%10), sensorData.accX, sensorData.accY, sensorData.accZ, sensorData.airFlow};
    

     notiHandle.attrHandle = CYBLE_RVAC_SENSORS_CHAR_HANDLE;
     notiHandle.value.val = (uint8 *) &dataForBLE;     //(uint8 *) dataForBLE; // collectedData; //dataForBLE;
     notiHandle.value.len = 34;
        
        CyBle_GattsNotification(cyBle_connHandle, &notiHandle);

}

void updateNotificationCCCD(void){
    CYBLE_GATT_HANDLE_VALUE_PAIR_T sensorNotCCCDHandle;
    
    uint8 sensorCCCDVal[2];
    
    if(updateIsNotifyCCCDAttr == 1){
        
     updateIsNotifyCCCDAttr = 0;
        sensorCCCDVal[0] = isNotify;
        sensorCCCDVal[1] = 0x00;
        
        sensorNotCCCDHandle.attrHandle = CYBLE_RVAC_SENSORS_SENSORCCCD_DESC_HANDLE;
        sensorNotCCCDHandle.value.val = sensorCCCDVal;
        sensorNotCCCDHandle.value.len = 2;
        
        CyBle_GattsWriteAttributeValue(&sensorNotCCCDHandle, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
        CyBle_ProcessEvents();
    }
}


void initialized_input_gpioExp(){
   I2C_1_I2CMasterSendStart(ADDR,I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(REG_CONFIG, 100u);
   I2C_1_I2CMasterWriteByte(0xFF, 100u);
   I2C_1_I2CMasterSendStop(100u);
    I2C_1_Sleep();
    I2C_1_Wakeup();

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

// fnc to calibrate the power chips
void auto_calibrate_gain(uint32 address){
    //current target
    I2C_1_I2CMasterSendStart(address, I2C_1_I2C_WRITE_XFER_MODE, 2);
    I2C_1_I2CMasterWriteByte(0xA5, 10);
    I2C_1_I2CMasterWriteByte(0x09, 10);
    I2C_1_I2CMasterWriteByte(0x41, 10);
    I2C_1_I2CMasterWriteByte(0x00, 10);
    I2C_1_I2CMasterWriteByte(0x86, 10);
    I2C_1_I2CMasterWriteByte(0x4D, 10);
    I2C_1_I2CMasterWriteByte(0x01, 10);
    I2C_1_I2CMasterWriteByte(0x4B, 10);
    I2C_1_I2CMasterWriteByte(0x0E, 10);
    I2C_1_I2CMasterSendStop(10);
    I2C_1_Sleep();
    I2C_1_Wakeup();
    
    // target voltage
    I2C_1_I2CMasterSendStart(address, I2C_1_I2C_WRITE_XFER_MODE, 2);
    I2C_1_I2CMasterWriteByte(0xA5, 10);
    I2C_1_I2CMasterWriteByte(0x09, 10);
    I2C_1_I2CMasterWriteByte(0x41, 10);
    I2C_1_I2CMasterWriteByte(0x00, 10);
    I2C_1_I2CMasterWriteByte(0x8A, 10);
    I2C_1_I2CMasterWriteByte(0x4D, 10);
    I2C_1_I2CMasterWriteByte(0x01, 10);
    I2C_1_I2CMasterWriteByte(0x23, 10);
    I2C_1_I2CMasterWriteByte(0xEA, 10);
    I2C_1_I2CMasterSendStop(10);
    I2C_1_Sleep();
    I2C_1_Wakeup();
    
    // target line freq
    I2C_1_I2CMasterSendStart(address, I2C_1_I2C_WRITE_XFER_MODE, 2);
    I2C_1_I2CMasterWriteByte(0xA5, 10);
    I2C_1_I2CMasterWriteByte(0x0A, 10);
    I2C_1_I2CMasterWriteByte(0x41, 10);
    I2C_1_I2CMasterWriteByte(0x00, 10);
    I2C_1_I2CMasterWriteByte(0x94, 10);
    I2C_1_I2CMasterWriteByte(0x4D, 10);
    I2C_1_I2CMasterWriteByte(0x02, 10);
    I2C_1_I2CMasterWriteByte(0xEA, 10);
    I2C_1_I2CMasterWriteByte(0x60, 10);
    I2C_1_I2CMasterWriteByte(0x1D, 10);
    I2C_1_I2CMasterSendStop(10);
    I2C_1_Sleep();
    I2C_1_Wakeup();
    
    I2C_1_I2CMasterSendStart(address, I2C_1_I2C_WRITE_XFER_MODE, 2);
    I2C_1_I2CMasterWriteByte(0xA5, 10);
    I2C_1_I2CMasterWriteByte(0xA4, 10);
    I2C_1_I2CMasterWriteByte(0x5A, 10);
    I2C_1_I2CMasterWriteByte(0x03, 10);
    I2C_1_I2CMasterSendStop(10);
    I2C_1_Sleep();
    I2C_1_Wakeup();
    
}

void read_power_chips(uint32 address){
    
    uint8 rBuff[35];
    
        I2C_1_I2CMasterSendStart(address,I2C_1_I2C_WRITE_XFER_MODE, 100u);
        I2C_1_I2CMasterWriteByte(0xA5, 10u);
        I2C_1_I2CMasterWriteByte(0x08, 10u);
        I2C_1_I2CMasterWriteByte(0x41, 10u);
        I2C_1_I2CMasterWriteByte(0x00, 10u);
        I2C_1_I2CMasterWriteByte(0x02, 10u);
        I2C_1_I2CMasterWriteByte(0x4E, 10u);
        I2C_1_I2CMasterWriteByte(0x20, 10u);
        I2C_1_I2CMasterWriteByte(0x5E, 10u);
        I2C_1_I2CMasterSendStop(0u);
        
        I2C_1_Sleep();
        I2C_1_Wakeup();
  
        I2C_1_I2CMasterSendStart(address, I2C_1_I2C_READ_XFER_MODE, 10u);
        for(int i =0; i<34; i++){
          I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,&rBuff[i],10u);
        }
        I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,&rBuff[34],10u);
        I2C_1_I2CMasterSendStop(100u);
        
        switch(address){
            case 0x74:
                sensorData.voltCompressor = (rBuff[7] << 8) | rBuff[6];
                sensorData.lineFreqComp = (rBuff[9] << 8) | rBuff[8];
                sensorData.currentCompressor = (rBuff[17] << 24) | (rBuff[16] << 16) | (rBuff[15] << 8) | rBuff[14];
            break;
            
            case 0x75:
                sensorData.volt = (rBuff[7] << 8) | rBuff[6];
                sensorData.lineFreq = (rBuff[9] << 8) | rBuff[8];
                sensorData.current = (rBuff[17] << 24) | (rBuff[16] << 16) | (rBuff[15] << 8) | rBuff[14];
            break;
            
            case 0x76:
                sensorData.voltFan = (rBuff[7] << 8) | rBuff[6];
                sensorData.lineFreqFan = (rBuff[9] << 8) | rBuff[8];
                sensorData.currentFan = (rBuff[17] << 24) | (rBuff[16] << 16) | (rBuff[15] << 8) | rBuff[14];
            break;
            
            default:
            break;
        }
}

void read_Air_Flow(){
    uint16 airFlow = 0;
    for(int i =0; i < 500; i++){
        airFlow += (AF_Read() == 1)? 1 : 0;
    }
    sensorData.airFlow = airFlow;
}

void delay(int d){
    for(;d>0; d--);
}


void my_interrupt(){
    
    interruptFlag = 1;
   
     CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER2_INT);
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
    
    I2C_1_Start();
    
    MyUART_Start();
    
    MyADC_Start();
    
    MyADC_StartConvert();
    
    // call after I2C have been initiated
//    configure_temperature_sensor2();
//    configure_temperature_sensor1();
    initialized_input_gpioExp();
    
    // only need to calibrate the firt time the board is ever used
//   auto_calibrate_gain(ADDR_POWER1);
//    auto_calibrate_gain(ADDR_POWER2);
//    auto_calibrate_gain(ADDR_POWER3);
    
    // start BLE
   // CyBle_Start(bleStack);
    
    // 1sec interrupt
    CySysWdtEnable(CY_SYS_WDT_COUNTER2);
    int_1_StartEx(my_interrupt);

    
//uint8 temp1 = 0;
//uint8 tempR1 = 0;
//uint8 tempR2 = 0;
 uint8_t temp2 = 0;
//uint8_t tempR12 = 0;    
//uint8_t tempR22 = 0;
   // volatile thermostatData thermo;
   // volatile dataCollected sensorData;
thermo.setTemperature = 0;
thermo.ambientTemp = 0;
 uint8 comp = 0u;
 uint8 fanL = 0u;
 uint8 fanH = 0u;
    
    int counter =0;
    
    for(;;){

 if(interruptFlag == 1){
    
    if(MyADC_IsEndConversion(MyADC_RETURN_STATUS)){
        adcRead = MyADC_GetResult16(0);
//    
    sprintf(uartStr, "*-*-*-*-*-*-*-*-  ADC is: %d -*-*-*-*-*-*-*-*-\n", adcRead);
    MyUART_PutString(uartStr);
    }
//    
  // if(adcRead < 1300){
   // if(adcRead < 1501){
       //CEPIN_Write(0);
    // }
  // }
    //else if(adcRead > 1500){
     //  CEPIN_Write(1);
       
    volatile uint8 read_buff[2] = {0,0};
    
        int statusStart = 0;

        
    // -----------------------read temperatures--------------------------------------
    char str[50];
    
//   ID  TMP432A

//  I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 0);
//if ((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_ERR_ADDR_NAK)==1){ MyUART_PutString("slave NACK address\n");}
//   I2C_1_I2CMasterWriteByte(0xFD, 0); // check ID 
//if ((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT)==1){ MyUART_PutString("writing error\n");}
//   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 0);
//
//   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &thermo.ambientTemp, 0);
//if ((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_RD_CMPLT)==1){ MyUART_PutString("reading error\n");}
//   I2C_1_I2CMasterSendStop(0);
//
//
//  sprintf(str, "counter: %d\n\n status start: %d\n ID: %x\n", counter,statusStart, thermo.ambientTemp);
//    MyUART_PutString(str);
//    counter +=1;
//    
////  READ local sensor  TMP432A
//    I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 0u);
//   I2C_1_I2CMasterWriteByte(0x00, 0u);
//   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 0u);
//   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
//   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.localTemp,0u);
//   I2C_1_I2CMasterSendStop(0u);
//    
//////  READ remote sensor 1 TMP432A
//  I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 0u);
//   I2C_1_I2CMasterWriteByte(0x01, 0u);
//   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 0u);
//   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
//   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.remoteTemp1,0u);
//   I2C_1_I2CMasterSendStop(0u);
////
////
//////  READ remote sensor 2   TMP432A
//  I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 0u);
//   I2C_1_I2CMasterWriteByte(0x23, 0u);
//   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 0u);
//   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
//   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.remoteTemp2,0u);
//   I2C_1_I2CMasterSendStop(0u);
////
////
////
////
//sprintf(str, "Sensor 1 temperature is %d\n", sensorData.localTemp-64);
//MyUART_PutString(str);
//
//sprintf(str, "Sensor 1 Remote temperature 1 is %d \n", (sensorData.remoteTemp1-64));
//MyUART_PutString(str);
//
//
//sprintf(str, "Sensor 1 Remote temperature 2 is %d \n", (sensorData.remoteTemp2-64));
//MyUART_PutString(str);
//
//
////
//////   ID  TMP432B
//   I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 0u);
//if ((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_ERR_ADDR_NAK)==1){ MyUART_PutString("slave NACK address\n");}
//   I2C_1_I2CMasterWriteByte(0xFD, 0u); // check ID 
//if ((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT)==1){ MyUART_PutString("writing error\n");}
//   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 0u);
//temp2 =0;
//   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &temp2, 0u);
//if ((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_RD_CMPLT)==1){ MyUART_PutString("reading error\n");}
//   I2C_1_I2CMasterSendStop(0);
//
//
//  sprintf(str, "\n\nTMP432B           ID: %x\n", temp2);
//    MyUART_PutString(str);
//
////temp = tempR1 = tempR2 = 0;
//  //READ local sensor  2  TMP432B
//   I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 0u);
//   I2C_1_I2CMasterWriteByte(0x00, 0u);
//   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 0u);
//   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
//   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &temp2,0u);
//   I2C_1_I2CMasterSendStop(0u);
//
////  READ remote 2 sensor 1 TMP432B
//  I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 0u);
//   I2C_1_I2CMasterWriteByte(0x01, 0u);
//   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 0u);
//   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
//   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.remoteTemp3,0u);
//   I2C_1_I2CMasterSendStop(0u);
//
//
////  READ remote 2 sensor 2  TMP432B
//  I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 0u);
//   I2C_1_I2CMasterWriteByte(0x23, 0u);
//   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 0u);
//   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
//   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.remoteTemp4,0u);
//   I2C_1_I2CMasterSendStop(0u);
//
//
////sensorData.localTemp = (sensorData.localTemp+temp2)/2;
//
//sprintf(str, "Sensor 2 temperature is %d\n", (temp2-64));
//MyUART_PutString(str);
//
//sprintf(str, "Sensor 2 Remote temperature 1 is %d \n", (sensorData.remoteTemp3-64));
//MyUART_PutString(str);
//
//
//sprintf(str, "Sensor 2 Remote temperature 2 is %d \n\n\n\n", (sensorData.remoteTemp4-64));
//MyUART_PutString(str);
//
//
//
///*  ---------------------------- ACCELEROMETER -----------------------------------   */
//
//uint8 xLSB;
//uint8 xMSB;
//uint8 yLSB;
//uint8 yMSB;
//uint8 zLSB;
//uint8 zMSB;
//
//I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
//I2C_1_I2CMasterWriteByte(0x02, 100u);
//I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
//I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &xLSB ,100u);
//I2C_1_I2CMasterSendStop(100u);
//
//I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
//I2C_1_I2CMasterWriteByte(0x03, 100u);
//I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
//I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &xMSB ,100u);
//I2C_1_I2CMasterSendStop(100u);
//
//I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
//I2C_1_I2CMasterWriteByte(0x04, 100u);
//I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
//I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &yLSB ,100u);
//I2C_1_I2CMasterSendStop(100u);
//
//I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
//I2C_1_I2CMasterWriteByte(0x05, 100u);
//I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
//I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &yMSB ,100u);
//I2C_1_I2CMasterSendStop(100u);
//
//I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
//I2C_1_I2CMasterWriteByte(0x06, 100u);
//I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
//I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &zLSB ,100u);
//I2C_1_I2CMasterSendStop(100u);
//
//I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 100u);
//I2C_1_I2CMasterWriteByte(0x07, 100u);
//I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 100u);
//I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &zMSB ,100u);
//I2C_1_I2CMasterSendStop(100u);
//
//sensorData.accX = (xMSB );
//sensorData.accY = (yMSB );
//sensorData.accZ = (zMSB );
//
//
//
//sprintf(str,"\nX: %d %d    12 bit x: %d\n", xMSB, xLSB, sensorData.accX);
//MyUART_PutString(str);
//sprintf(str,"y: %d %d      12 bit y: %d\n", yMSB, yLSB, sensorData.accY);
//MyUART_PutString(str);
//sprintf(str,"Z: %d %d      12 bit z: %d\n\n\n", zMSB, zLSB, sensorData.accZ);
//MyUART_PutString(str);
//
//// ---------------  Read humidity ---------------
//read_buff[0]=0;
//read_buff[1]=0;
//I2C_1_I2CMasterSendStart(0x18,I2C_1_I2C_WRITE_XFER_MODE, 0u);
//I2C_1_I2CMasterWriteByte(0x07, 0u);
//I2C_1_I2CMasterSendRestart(0x18, I2C_1_I2C_READ_XFER_MODE, 0u);
//I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0] ,0u);
//I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &read_buff[1] ,0u);
//I2C_1_I2CMasterSendStop(0u);
//
//uint16 rh = ((read_buff[0] << 8) | read_buff[1]);
//
//sensorData.humidity = ((125 * rh)/65536)-6; 
//
//sprintf(str, "\nThe humidity is %d\n", sensorData.humidity);
//MyUART_PutString(str);

// ---------------------  Read thermostat pins ---------------------

 gpioPins = read_thermostat_pins();
 comp = (gpioPins & 0x04)== 0x04? 1:0;
 fanH = (gpioPins & 0x08) == 0x08? 1:0;
 fanL = (gpioPins & 0x10) == 0x10? 1:0;


sprintf(str, "\nThermostast pins are 0x%x com%x, Lf%x, Hf%x\n", gpioPins, comp, fanL, fanH);
MyUART_PutString(str);


//// ------------------------------- power sensors check version  -----------------------

//        read_power_chips(ADDR_POWER1);
//        sprintf(str, "\nComp volt: %d  freq: %d  current: %lu\n", sensorData.voltCompressor, sensorData.lineFreqComp, sensorData.currentCompressor);
//        MyUART_PutString(str);
//        
//        read_power_chips(ADDR_POWER2);
//        sprintf(str, "\nLow Fan volt: %d  freq: %d  current: %lu\n", sensorData.volt, sensorData.lineFreq, sensorData.current);
//        MyUART_PutString(str);
//        
//        read_power_chips(ADDR_POWER3);
//        sprintf(str, "\nLow Fan volt: %d  freq: %d  current: %lu\n", sensorData.voltFan, sensorData.lineFreqFan, sensorData.currentFan);
//        MyUART_PutString(str);

  // } //end of  if adc result is > 1500 turn regulator

// --------------- AIR FLOW ------------

    //read_Air_Flow();

// ----- BLE CODE ----------


     if(bleConnected == 1){ ///
                RED_Write(1);
                
            updateNotificationCCCD();
            
            if(isNotify == 1){
                GREEN_Write(1);
                if(CyBle_GattGetBusStatus() == CYBLE_STACK_STATE_FREE){
                 BLUE_Write(!BLUE_Read());
                    SendDataNotify();
                 //BLUE_Write(1);
               }
            } // end of notification
            else{
                thermo.ambientTemp = sensorData.localTemp;
                
                GREEN_Write(0);
                
            } //end of read/write 
        } // end ble connected if  
    else{
        RED_Write(!RED_Read());
        GREEN_Write(1);
        BLUE_Write(1);
    }
    interruptFlag = 0;
    }// end if int flag

// --------------------   control relays and high switch  -----------------
//  0x04 comp  0x08 low fan   0x10 high  fan  gipo masks for checking pins

if (bleConnected == 1){

        if(thermo.power == 1){
            if(thermo.compressor == 1){
                //if the temperature of ambient is higher than the temprature set turn on the compressor.
                if(sensorData.localTemp > (thermo.setTemperature+2)){
                    if(sensorData.localTemp > thermo.setTemperature){
                       RelayC_3_Write(0);
                       Comp_out_Write(1);
                    }
                }
                // if the ambient temperature is equal or less to the set temperature turn off the compressor.
                else if(sensorData.localTemp <= (thermo.setTemperature-2)){
                    if(sensorData.localTemp <= thermo.setTemperature){
                      RelayC_3_Write(1);
                      Comp_out_Write(0);
                    }
                }
             } // end comp on
           else{
             RelayC_3_Write(1);
             Comp_out_Write(0);
           }
            
            RelayLF_1_Write(!thermo.fanLow);
            LowF_out_Write(thermo.fanLow);
            
            RelayHF_2_Write(!thermo.fanHigh);
            LowF_out_Write(thermo.fanHigh);
        }
        else if(thermo.power == 0){
            RelayC_3_Write(1);
            Comp_out_Write(0);
            
            RelayLF_1_Write(1);
            LowF_out_Write(0);
            
            RelayHF_2_Write(1);
            LowF_out_Write(0);
        }
        
        else if(thermo.test ==1){
            if(thermo.power == 0){
                 RelayC_3_Write(1);
                 Comp_out_Write(0);
                
                 RelayLF_1_Write(1);
                 LowF_out_Write(0);
            
                 RelayHF_2_Write(1);
                 LowF_out_Write(0);
            }
                
            else if(thermo.power == 1){
                if(thermo.compressor == 1){
                    if(sensorData.voltCompressor < 2){
                        if(sensorData.currentCompressor < 1000){
                            RelayC_3_Write(!thermo.compressor);
                            Comp_out_Write(thermo.compressor);
                        }
                        else{
                            errorPower.err_Comp_curr = 1;
                        }
                    }
                    else{
                        errorPower.err_Comp_volt = 1; 
                    }
                }
                else if(thermo.compressor == 0){
                       RelayC_3_Write(1);
                       Comp_out_Write(0);
                }
                
                 if(thermo.fanLow == 1){
                    if(sensorData.volt < 2){
                        if(sensorData.current < 1000){
              
                            RelayLF_1_Write(!thermo.fanLow);
                            LowF_out_Write(thermo.fanLow);
                        }
                        else{
                            errorPower.err_LFan_curr = 1;
                        }
                    }
                    else{
                        errorPower.err_LFan_volt = 1; 
                    }
                }
                else if(thermo.fanLow == 0){
                    RelayLF_1_Write(1);
                    LowF_out_Write(0);
                }
                
                if(thermo.fanHigh == 1){
                 if(sensorData.voltFan < 2){
                    if(sensorData.currentFan < 1000){
                    
                    RelayHF_2_Write(!thermo.fanHigh);
                    HighF_out_Write(thermo.fanHigh);
                    }
                    else{
                            errorPower.err_HFan_curr = 1;
                        }
                 }
                  else{
                     errorPower.err_HFan_volt = 1;
                  }
                }
                 else if(thermo.fanHigh == 0){
                    RelayHF_2_Write(1);
                    HighF_out_Write(0);
                }
                
            } // end of power on
        } // end of test
  
} // end of ble connected 
else{
   
    
    RelayC_3_Write(0);
    Comp_out_Write(1);
    thermo.compressor = comp;
    sprintf(uartStr,"read pin switch comp: %d\n", Comp_out_Read());
    MyUART_PutString(uartStr);
    
    if((fanL == 1) && (fanH == 0)){
        RelayLF_1_Write(0);
        LowF_out_Write(0);
        thermo.fanLow = fanL;
        sprintf(uartStr,"read pin switch low F: %d\n", LowF_out_Read());
        MyUART_PutString(uartStr);
    }
    else if((fanL ==0) && (fanH == 1)){
        RelayHF_2_Write(0);
        HighF_out_Write(1);//fanH);
        thermo.fanHigh = fanH;
        sprintf(uartStr,"read pin switch high F: %d\n", HighF_out_Read());
        MyUART_PutString(uartStr);
    }
   }

//        send_Error_Power_to_Phone();
//        send_Thermo_to_phone();
//        CyBle_ProcessEvents();
   
    } // end for loop
    
} //end of main

/* [] END OF FILE */


//checklist
//uncomment configuration functions for i2c
