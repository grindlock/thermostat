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

#define ADDR_POWER1 (0x74)
#define ADDR_POWER2 (0x75)
#define ADDR_POWER3 (0x76)
#define REG_POWER_VERSION (0x04)

int interruptFlag= 0;
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
    int8 err_Power;
    int8 err_Temp;
    int8 err_Hum;
    int8 err_Acc;
    
}errorCode;

uint8 setTemperature = 0;

uint8 prevComp = 0;
uint8 prevLFan = 0;
uint8 prevHFan = 0;

// the address fro the temp sensor are 0x4C and 0x4D

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
    CYBLE_API_RESULT_T apiResult;
    CYBLE_GAP_BD_ADDR_T localAddr;
    
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
           
            // This handle the notofications
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

// function to read thermostat data on the phone
void send_Thermo_to_phone(){
    uint8 t[] = {thermo.compressor, thermo.fanLow, thermo.fanHigh, thermo.setTemperature, thermo.ambientTemp, thermo.power, thermo.test};
    CYBLE_GATT_HANDLE_VALUE_PAIR_T thermoRead;
    
     thermoRead.attrHandle = CYBLE_RVAC_THERMOSTAT_CHAR_HANDLE;
        thermoRead.value.val =  t;
        thermoRead.value.len = 7;
    
   CyBle_GattsWriteAttributeValue(&thermoRead, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
}

void SendDataNotify( uint8 len){
    CYBLE_GATTS_HANDLE_VALUE_NTF_T notiHandle;
    
      uint8 dataForBLE[] = {sensorData.localTemp, sensorData.remoteTemp1, sensorData.remoteTemp2, sensorData.remoteTemp3, sensorData.remoteTemp4, sensorData.accX, sensorData.accY, sensorData.accZ, sensorData.humidity};
    /*{sensorData.localTemp/10,sensorData.localTemp%10,sensorData.remoteTemp1/10, sensorData.remoteTemp1%10, sensorData.remoteTemp2/10, sensorData.remoteTemp2%10, 
        sensorData.remoteTemp3/10, sensorData.remoteTemp3%10, sensorData.humidity/10, sensorData.humidity%10, sensorData.voltCompressor/10, sensorData.voltCompressor%10, sensorData.voltFan/10,
        sensorData.voltFan%10, sensorData.volt/10, sensorData.volt%10, sensorData.currentCompressor/10, sensorData.currentCompressor%10, sensorData.currentFan/10, sensorData.currentFan%10, sensorData.current/10,
        sensorData.current%10, sensorData.lineFreqComp/10, sensorData.lineFreqComp%10, sensorData.lineFreqFan/10, sensorData.lineFreqFan%10, sensorData.lineFreq/10, sensorData.lineFreq%10, sensorData.airFlow/10, sensorData.airFlow%10,
        sensorData.accX/10, sensorData.accX%10, sensorData.accY/10, sensorData.accY%10, sensorData.accZ/10, sensorData.accZ%10};*/
    

     notiHandle.attrHandle = CYBLE_RVAC_SENSORS_CHAR_HANDLE;
     notiHandle.value.val = (uint8 *) &dataForBLE;     //(uint8 *) dataForBLE; // collectedData; //dataForBLE;
     notiHandle.value.len = 9; //36;
        
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
void read_Air_Flow(){
    uint16 airFlow = 0;
    for(int i =0; i < 500; i++){
        airFlow += (AF_Read() == 1)? 1 : 0;
    }
    sensorData.airFlow = airFlow;
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
    
     // call after I2C have been initiated
    configure_temperature_sensor2();
    configure_temperature_sensor1();
    initialized_input_gpioExp();
    
    CyBle_Start(bleStack);
    // 1sec interrupt
    CySysWdtEnable(CY_SYS_WDT_COUNTER2);
    int_1_StartEx(my_interrupt);

    
uint8 temp1 = 0;
uint8 tempR1 = 0;
uint8 tempR2 = 0;
uint8_t temp2 = 0;
uint8_t tempR12 = 0;    
uint8_t tempR22 = 0;
   // volatile thermostatData thermo;
   // volatile dataCollected sensorData;
    thermo.setTemperature = 0;
    thermo.ambientTemp = 0;
 int comp = 0u;
 int fanL = 0u;
 int fanH = 0u;
    
    int counter =0;
    
    for(;;){

if(interruptFlag == 1){
    
    MyADC_StartConvert();
    adcRead =  MyADC_GetResult16(0);
    MyADC_StopConvert();
    //MyADC_CountsTo_Volts(0, adcRead);
    
    if(adcRead > 498){
        if(adcRead > 510){
        CEPIN_Write(1);
   
       
    volatile uint8 read_buff[2] = {0,0};
        
    // -----------------------read temperatures--------------------------------------
    char str[50];
    uint8 wBuff[2] = {0x00, 0u};
    volatile uint8 rBuff[2] = {0u, 0u};
    
  
    
////   ID  
   I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 0);
if ((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_ERR_ADDR_NAK)==1){ MyUART_PutString("slave NACK address\n");}
   I2C_1_I2CMasterWriteByte(0xFD, 0); // check ID 
if ((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_WR_CMPLT)==1){ MyUART_PutString("writing error\n");}
   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 0);

   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &thermo.ambientTemp, 0);
if ((I2C_1_I2CMasterStatus() & I2C_1_I2C_MSTAT_RD_CMPLT)==1){ MyUART_PutString("reading error\n");}
   I2C_1_I2CMasterSendStop(0);


  sprintf(str, "counter: %d            ID: %x\n", counter, thermo.ambientTemp);
    MyUART_PutString(str);
    counter +=1;
//  READ local sensor 
    I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 0u);
   I2C_1_I2CMasterWriteByte(0x00, 0u);
   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 0u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.localTemp,0u);
   I2C_1_I2CMasterSendStop(0u);
    
////  READ remote sensor 1
  I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 0u);
   I2C_1_I2CMasterWriteByte(0x01, 0u);
   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 0u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.remoteTemp1,0u);
   I2C_1_I2CMasterSendStop(0u);
//
//
////  READ remote sensor 2
  I2C_1_I2CMasterSendStart(0x4C, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x23, 100u);
   I2C_1_I2CMasterSendRestart(0x4C,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.remoteTemp2,100u);
   I2C_1_I2CMasterSendStop(100u);
//
//
//
//
sprintf(str, "Sensor 1 temperature is %d\n", sensorData.localTemp-64);
MyUART_PutString(str);

sprintf(str, "Sensor 1 Remote temperature 1 is %d \n", (sensorData.remoteTemp1-64));
MyUART_PutString(str);


sprintf(str, "Sensor 1 Remote temperature 2 is %d \n", (sensorData.remoteTemp2-64));
MyUART_PutString(str);
//
//temp = tempR1 = tempR2 = 0;
  //READ local sensor  2  
   I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x00, 100u);
   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &temp2,100u);
   I2C_1_I2CMasterSendStop(100u);

//  READ remote 2 sensor 1
  I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x01, 100u);
   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 100u);
   //I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &read_buff[0],100u);
   I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &sensorData.remoteTemp3,100u);
   I2C_1_I2CMasterSendStop(100u);


//  READ remote 2 sensor 2
  I2C_1_I2CMasterSendStart(0x4D, I2C_1_I2C_WRITE_XFER_MODE, 100u);
   I2C_1_I2CMasterWriteByte(0x23, 100u);
   I2C_1_I2CMasterSendRestart(0x4D,I2C_1_I2C_READ_XFER_MODE, 100u);
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

sensorData.accX = (xMSB );
sensorData.accY = (yMSB );
sensorData.accZ = (zMSB );



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

// ---------------------  Read thermostat pins ---------------------

gpioPins = read_thermostat_pins();
 comp = (gpioPins & 0x04);
 fanL = (gpioPins & 0x08);
 fanH = (gpioPins & 0x10);


sprintf(str, "\nThermostast pins are 0x%x\n", gpioPins);
MyUART_PutString(str);


// ------------------------------- power sensors  -----------------------
uint8 ver[2] = {0,0};

I2C_1_I2CMasterSendStart(ADDR_POWER1,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(REG_POWER_VERSION, 100u);
I2C_1_I2CMasterSendStop(100u);
I2C_1_I2CMasterSendStart(ADDR_POWER1, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &ver[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &ver[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

sprintf(str, "power 1 ver: %d %d\n", ver[0], ver[1]);
MyUART_PutString(str);

I2C_1_I2CMasterSendStart(ADDR_POWER2,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(REG_POWER_VERSION, 100u);
I2C_1_I2CMasterSendStop(100u);
I2C_1_I2CMasterSendStart(ADDR_POWER2, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &ver[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &ver[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

sprintf(str, "power 2 ver: %d %d\n", ver[0], ver[1]);
MyUART_PutString(str);

I2C_1_I2CMasterSendStart(ADDR_POWER3,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(REG_POWER_VERSION, 100u);
I2C_1_I2CMasterSendStop(100u);
I2C_1_I2CMasterSendStart(ADDR_POWER3, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &ver[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &ver[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

sprintf(str, "power 3 ver: %d %d\n", ver[0], ver[1]);
MyUART_PutString(str);

read_buff[0] =0u;
// --------------------- VOLT -----------------------------------------------
I2C_1_I2CMasterSendStart(ADDR_POWER1,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x06, 100u);
I2C_1_I2CMasterSendStop(100u);
I2C_1_I2CMasterSendStart(ADDR_POWER1, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &ver[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &ver[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

sensorData.voltCompressor = ((ver[0] << 8) || ver[1]);

sprintf(str, "power 1 volt: %d %d    volt 16: %d\n", ver[0], ver[1],sensorData.voltCompressor);
MyUART_PutString(str);

I2C_1_I2CMasterSendStart(ADDR_POWER2,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x06, 100u);
I2C_1_I2CMasterSendStop(100u);
I2C_1_I2CMasterSendStart(ADDR_POWER2, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &ver[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &ver[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

sprintf(str, "power 2 volt: %d %d    volt 16: %d\n", ver[0], ver[1],sensorData.voltFan);
MyUART_PutString(str);

I2C_1_I2CMasterSendStart(ADDR_POWER3,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x06, 100u);
I2C_1_I2CMasterSendStop(100u);
I2C_1_I2CMasterSendStart(ADDR_POWER3, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &ver[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &ver[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

sprintf(str, "power 3 volt: %d %d    volt 16: %d\n", ver[0], ver[1],sensorData.volt);
MyUART_PutString(str);
// -------   FREQ ---------------------------------------------------------------
I2C_1_I2CMasterSendStart(ADDR_POWER1,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x08, 100u);
I2C_1_I2CMasterSendStop(100u);
I2C_1_I2CMasterSendStart(ADDR_POWER1, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &ver[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &ver[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

sensorData.lineFreqComp = ((ver[0] << 8) || ver[1]);

sprintf(str, "power 1 freq: %d %d    freq 16: %d\n", ver[0], ver[1],sensorData.lineFreqComp);
MyUART_PutString(str);

I2C_1_I2CMasterSendStart(ADDR_POWER2,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x08, 100u);
I2C_1_I2CMasterSendStop(100u);
I2C_1_I2CMasterSendStart(ADDR_POWER2, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &ver[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &ver[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

sensorData.lineFreqFan = ((ver[0] << 8) || ver[1]);

sprintf(str, "power 2 freq: %d %d    freq 16: %d\n", ver[0], ver[1],sensorData.lineFreqFan);
MyUART_PutString(str);

I2C_1_I2CMasterSendStart(ADDR_POWER3,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x08, 100u);
I2C_1_I2CMasterSendStop(100u);
I2C_1_I2CMasterSendStart(ADDR_POWER3, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &ver[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &ver[1] ,100u);
I2C_1_I2CMasterSendStop(100u);

sensorData.lineFreq = ((ver[0] << 8) | ver[1]);

sprintf(str, "power 3 freq: %d %d    freq 16: %d\n", ver[0], ver[1],sensorData.lineFreq);
MyUART_PutString(str);

// -------------   current ---------------
uint8 currentRead[4] = {0,0,0,0};

I2C_1_I2CMasterSendStart(ADDR_POWER1,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x0E, 100u);
I2C_1_I2CMasterSendStop(100u);
I2C_1_I2CMasterSendStart(ADDR_POWER1, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &currentRead[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &currentRead[1] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &currentRead[2] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &currentRead[3] ,100u);
I2C_1_I2CMasterSendStop(100u);

sensorData.currentCompressor = (currentRead[0] << 24);
sensorData.currentCompressor = (currentRead[1] << 16);
sensorData.currentCompressor = (currentRead[2] << 8);
sensorData.currentCompressor |= (currentRead[3]);


sprintf(str, "power 1 volt: %d %d    volt 16: %lu\n", ver[0], ver[1],sensorData.currentCompressor);
MyUART_PutString(str);

I2C_1_I2CMasterSendStart(ADDR_POWER2,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x0E, 100u);
I2C_1_I2CMasterSendStop(100u);
I2C_1_I2CMasterSendStart(ADDR_POWER2, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &currentRead[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &currentRead[1] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &currentRead[2] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &currentRead[3] ,100u);
I2C_1_I2CMasterSendStop(100u);

sensorData.currentFan = (currentRead[0] << 24);
sensorData.currentFan = (currentRead[1] << 16);
sensorData.currentFan = (currentRead[2] << 8);
sensorData.currentFan |= (currentRead[3]);

sprintf(str, "power 2 current %lu\n", sensorData.currentFan);
MyUART_PutString(str);

I2C_1_I2CMasterSendStart(ADDR_POWER3,I2C_1_I2C_WRITE_XFER_MODE, 100u);
I2C_1_I2CMasterWriteByte(0x0E, 100u);
I2C_1_I2CMasterSendStop(100u);
I2C_1_I2CMasterSendStart(ADDR_POWER3, I2C_1_I2C_READ_XFER_MODE, 100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &currentRead[0] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &currentRead[1] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_ACK_DATA,(uint8 *) &currentRead[2] ,100u);
I2C_1_I2CMasterReadByte(I2C_1_I2C_NAK_DATA,(uint8 *) &currentRead[3] ,100u);
I2C_1_I2CMasterSendStop(100u);

sensorData.current = (currentRead[0] << 24);
sensorData.current = (currentRead[1] << 16);
sensorData.current = (currentRead[2] << 8);
sensorData.current |= (currentRead[3]);

sprintf(str, "power 3 current %lu\n", sensorData.current);
MyUART_PutString(str);
        }
    }// end of adc
    else if(adcRead < 400) {
        if(adcRead <395){
            CEPIN_Write(0);
        }
    }

// --------------- AIR FLOW -------------

    read_Air_Flow();

// ----- BLE CODE ----------


     if(bleConnected == 1){ ///
                RED_Write(1);
                
            updateNotificationCCCD();
            
            if(isNotify == 1){
                GREEN_Write(1);
                if(CyBle_GattGetBusStatus() == CYBLE_STACK_STATE_FREE){
                 BLUE_Write(!BLUE_Read());
                    SendDataNotify(4);
                 //BLUE_Write(1);
               }
            } // end of notification
            else{
                thermo.ambientTemp = sensorData.localTemp;
                send_Thermo_to_phone();
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
            
            if(thermo.compressor == 1){
                if(sensorData.voltCompressor > 0){
                    if(sensorData.currentCompressor > 0){
                        RelayC_3_Write(!thermo.compressor);
                        Comp_out_Write(thermo.compressor);
                    }
                }
                    else{
                    }
            }
                       
     
                
            
            RelayLF_1_Write(!thermo.fanLow);
            LowF_out_Write(thermo.fanLow);
            
            RelayHF_2_Write(!thermo.fanHigh);
            LowF_out_Write(thermo.fanHigh);
        }
  
} // end of ble connected 
else{
   
    
    RelayC_3_Write( !comp);
    Comp_out_Write(comp);
    thermo.compressor = comp;
    
    
    RelayLF_1_Write(!fanL);
    LowF_out_Write(fanL);
    thermo.fanLow = fanL;
    
    RelayHF_2_Write(!fanH);
    LowF_out_Write(fanH);
    thermo.fanHigh = fanH;
   }

   

CyBle_ProcessEvents();
   
    } // end for loop
    
    

    
} //end of main

/* [] END OF FILE */
