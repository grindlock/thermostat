// ======================================================================
// test.v generated from TopDesign.cysch
// 11/13/2019 at 19:00
// This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
// ======================================================================

`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_FAMILY_PSOC4 2
`define CYDEV_CHIP_FAMILY_PSOC5 3
`define CYDEV_CHIP_FAMILY_PSOC6 4
`define CYDEV_CHIP_FAMILY_FM0P 5
`define CYDEV_CHIP_FAMILY_FM3 6
`define CYDEV_CHIP_FAMILY_FM4 7
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_MEMBER_5B 2
`define CYDEV_CHIP_REVISION_5B_PRODUCTION 0
`define CYDEV_CHIP_REVISION_5B_ES0 0
`define CYDEV_CHIP_MEMBER_5A 3
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_MEMBER_4G 4
`define CYDEV_CHIP_REVISION_4G_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4G_ES 17
`define CYDEV_CHIP_REVISION_4G_ES2 33
`define CYDEV_CHIP_MEMBER_4U 5
`define CYDEV_CHIP_REVISION_4U_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4E 6
`define CYDEV_CHIP_REVISION_4E_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD 0
`define CYDEV_CHIP_MEMBER_4X 7
`define CYDEV_CHIP_REVISION_4X_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4O 8
`define CYDEV_CHIP_REVISION_4O_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4R 9
`define CYDEV_CHIP_REVISION_4R_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4T 10
`define CYDEV_CHIP_REVISION_4T_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4N 11
`define CYDEV_CHIP_REVISION_4N_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4S 12
`define CYDEV_CHIP_REVISION_4S_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4W 13
`define CYDEV_CHIP_REVISION_4W_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4Q 14
`define CYDEV_CHIP_REVISION_4Q_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4Y 15
`define CYDEV_CHIP_REVISION_4Y_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4D 16
`define CYDEV_CHIP_REVISION_4D_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4J 17
`define CYDEV_CHIP_REVISION_4J_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4K 18
`define CYDEV_CHIP_REVISION_4K_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4V 19
`define CYDEV_CHIP_REVISION_4V_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4H 20
`define CYDEV_CHIP_REVISION_4H_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4A 21
`define CYDEV_CHIP_REVISION_4A_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4A_ES0 17
`define CYDEV_CHIP_MEMBER_4F 22
`define CYDEV_CHIP_REVISION_4F_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0
`define CYDEV_CHIP_MEMBER_4P 23
`define CYDEV_CHIP_REVISION_4P_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4M 24
`define CYDEV_CHIP_REVISION_4M_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4L 25
`define CYDEV_CHIP_REVISION_4L_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4I 26
`define CYDEV_CHIP_REVISION_4I_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_6A 27
`define CYDEV_CHIP_REVISION_6A_ES 17
`define CYDEV_CHIP_REVISION_6A_PRODUCTION 33
`define CYDEV_CHIP_REVISION_6A_NO_UDB 33
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 28
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 29
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 30
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_FM3 31
`define CYDEV_CHIP_REVISION_FM3_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_FM4 32
`define CYDEV_CHIP_REVISION_FM4_PRODUCTION 0
`define CYDEV_CHIP_FAMILY_USED 2
`define CYDEV_CHIP_MEMBER_USED 22
`define CYDEV_CHIP_REVISION_USED 0
// SW_Tx_UART_v1_50(BaudRate=9600, PinAssignmentMethod=1, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=SW_Tx_UART_v1_50, CY_CONFIG_TITLE=MyUART, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=MyUART, CY_INSTANCE_SHORT_NAME=MyUART, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=50, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.2, INSTANCE_NAME=MyUART, )
module SW_Tx_UART_v1_50_0 ;



	wire [0:0] tmpOE__tx_net;
	wire [0:0] tmpFB_0__tx_net;
	wire [0:0] tmpIO_0__tx_net;
	wire [0:0] tmpINTERRUPT_0__tx_net;
	electrical [0:0] tmpSIOVREF__tx_net;

	cy_psoc3_pins_v1_10
		#(.id("c3d7048a-de48-4db2-8444-aa40dfe5a04f/52f31aa9-2f0a-497d-9a1f-1424095e13e6"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		tx
		 (.oe(tmpOE__tx_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__tx_net[0:0]}),
		  .io({tmpIO_0__tx_net[0:0]}),
		  .siovref(tmpSIOVREF__tx_net),
		  .interrupt({tmpINTERRUPT_0__tx_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__tx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};



endmodule

// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// Component: or_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0\or_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\4.2\PSoC Creator\psoc\content\CyPrimitives\cyprimitives.cylib\or_v1_0\or_v1_0.v"
`endif

// SCB_P4_v4_0(ApplySbClockParam=false, BitWidthReplacementStringRx=uint8, BitWidthReplacementStringTx=uint8, BufNum=1, Cond=#, DBGW_SCB_IP_V0=false, DBGW_SCB_IP_V1=false, DBGW_SCB_IP_V2=true, DW_Hide_i2c=false, DW_Hide_Scbv0Feature=true, DW_Hide_Scbv2Feature=false, DW_Hide_Spi=true, DW_Hide_Uart=true, DW_Hide_UartFlowControl=true, DW_INTR_SPI_EC=, DW_INTR_SPI_EC_MASK=, DW_INTR_SPI_EC_MASKED=, DW_SPI_CTRL=, DW_SPI_STATUS=, DW_UART_CTRL=, DW_UART_FLOW_CTRL=, DW_UART_RX_CTRL=, DW_UART_TX_CTRL=, EndCond=#endif, EzI2cBitWidthReplacementString=uint16, EzI2cBusVoltage=3.3, EzI2cByteModeEnable=false, EzI2cClkFreqDes=1550, EzI2cClockFromTerm=false, EzI2cClockStretching=true, EzI2cDataRate=100, EzI2cIsPrimarySlaveAddressHex=true, EzI2cIsSecondarySlaveAddressHex=true, EzI2cMedianFilterEnable=true, EzI2cNumberOfAddresses=0, EzI2cOvsFactor=16, EzI2cPrimarySlaveAddress=8, EzI2cSecondarySlaveAddress=9, EzI2cShowTerminals=false, EzI2cSlaveAddressMask=254, EzI2cSlewRate=0, EzI2cSubAddressSize=0, EzI2cWakeEnable=false, I2cAcceptAddress=false, I2cAcceptGeneralCall=false, I2cBusVoltage=3.3, I2cBusVoltageLevel=, I2cByteModeEnable=false, I2cClkFreqDes=2000, I2cClockFromTerm=false, I2cDataRate=100, I2cExternIntrHandler=false, I2cIsSlaveAddressHex=true, I2cIsSlaveAddressMaskHex=true, I2cManualOversampleControl=true, I2cMedianFilterEnable=true, I2cMode=2, I2cOvsFactor=20, I2cOvsFactorHigh=13, I2cOvsFactorLow=7, I2cShowTerminals=false, I2cSlaveAddress=8, I2cSlaveAddressMask=254, I2cSlewRate=1, I2cSlewRateSettings=1, I2cTermsEnable=false, I2cWakeEnable=false, PinLocationP4A=false, PinName0Unconfig=uart_rx_i2c_sda_spi_mosi, PinName0UnconfigWake=uart_rx_wake_i2c_sda_spi_mosi, PinName1Unconfig=uart_tx_i2c_scl_spi_miso, PinName2Unconfig=uart_cts_spi_sclk, PinName3Unconfig=uart_rts_spi_ss0, Pn0Unconfig=RX_SDA_MOSI, Pn0UnconfigWake=RX_WAKE_SDA_MOSI, Pn1Unconfig=TX_SCL_MISO, Pn2Unconfig=CTS_SCLK, Pn3Unconfig=RTS_SS0, RemoveI2cPins=false, RemoveMisoSdaTx=true, RemoveMosiSclRx=true, RemoveMosiSclRxWake=true, RemoveScbClk=false, RemoveScbIrq=false, RemoveSpiMasterMiso=true, RemoveSpiMasterMosi=true, RemoveSpiMasterPins=true, RemoveSpiMasterSclk=true, RemoveSpiMasterSs0Pin=true, RemoveSpiMasterSs1Pin=true, RemoveSpiMasterSs2Pin=true, RemoveSpiMasterSs3Pin=true, RemoveSpiSclk=true, RemoveSpiSlaveMiso=true, RemoveSpiSlaveMosi=true, RemoveSpiSlavePins=true, RemoveSpiSs0=true, RemoveSpiSs1=true, RemoveSpiSs2=true, RemoveSpiSs3=true, RemoveUartCtsPin=true, RemoveUartRtsPin=true, RemoveUartRxPin=true, RemoveUartRxTxPin=true, RemoveUartRxWake=true, RemoveUartRxWakeupIrq=true, RemoveUartTxPin=true, RxTriggerOutputEnable=false, ScbClkFreqDes=2000, ScbClkMinusTolerance=100, ScbClkPlusTolerance=2, ScbClockSelect=1, ScbClockTermEnable=false, ScbCustomIntrHandlerEnable=true, ScbInterruptTermEnable=false, ScbMisoSdaTxEnable=true, ScbMode=1, ScbModeHw=0, ScbMosiSclRxEnable=true, ScbRxWakeIrqEnable=false, ScbSclkEnable=false, ScbSs0Enable=false, ScbSs1Enable=false, ScbSs2Enable=false, ScbSs3Enable=false, ScbSymbolVisibility=0, SpiBitRate=1000, SpiBitsOrder=1, SpiByteModeEnable=false, SpiClkFreqDes=16000, SpiClockFromTerm=false, SpiFreeRunningSclk=false, SpiInterruptMode=0, SpiIntrMasterSpiDone=false, SpiIntrRxFull=false, SpiIntrRxNotEmpty=false, SpiIntrRxOverflow=false, SpiIntrRxTrigger=false, SpiIntrRxUnderflow=false, SpiIntrSlaveBusError=false, SpiIntrTxEmpty=false, SpiIntrTxNotFull=false, SpiIntrTxOverflow=false, SpiIntrTxTrigger=false, SpiIntrTxUnderflow=false, SpiLateMisoSampleEnable=false, SpiManualOversampleControl=true, SpiMasterMode=false, SpiMedianFilterEnable=false, SpimMisoTermEnable=false, SpimMosiTermEnable=false, SpiMode=0, SpimSclkTermEnable=false, SpimSs0TermEnable=false, SpimSs1TermEnable=false, SpimSs2TermEnable=false, SpimSs3TermEnable=false, SpiNumberOfRxDataBits=8, SpiNumberOfSelectLines=1, SpiNumberOfTxDataBits=8, SpiOvsFactor=16, SpiRemoveMiso=false, SpiRemoveMosi=false, SpiRemoveSclk=false, SpiRxBufferSize=8, SpiRxIntrMask=0, SpiRxOutputEnable=false, SpiRxTriggerLevel=7, SpiSclkMode=0, SpiSlaveMode=false, SpiSmartioEnable=false, SpisMisoTermEnable=false, SpisMosiTermEnable=false, SpiSs0Polarity=0, SpiSs1Polarity=0, SpiSs2Polarity=0, SpiSs3Polarity=0, SpisSclkTermEnable=false, SpisSsTermEnable=false, SpiSubMode=0, SpiTransferSeparation=1, SpiTxBufferSize=8, SpiTxIntrMask=0, SpiTxOutputEnable=false, SpiTxTriggerLevel=0, SpiWakeEnable=false, TriggerOutputEnable=false, TxTriggerOutputEnable=false, UartByteModeEnable=false, UartClkFreqDes=1382.4, UartClockFromTerm=false, UartCtsEnable=false, UartCtsPolarity=0, UartCtsTermEnable=false, UartDataRate=115200, UartDirection=3, UartDropOnFrameErr=false, UartDropOnParityErr=false, UartInterruptMode=0, UartIntrRxBreakDetected=false, UartIntrRxFrameErr=false, UartIntrRxFull=false, UartIntrRxNotEmpty=false, UartIntrRxOverflow=false, UartIntrRxParityErr=false, UartIntrRxTrigger=false, UartIntrRxUnderflow=false, UartIntrTxEmpty=false, UartIntrTxNotFull=false, UartIntrTxOverflow=false, UartIntrTxTrigger=false, UartIntrTxUartDone=false, UartIntrTxUartLostArb=false, UartIntrTxUartNack=false, UartIntrTxUnderflow=false, UartIrdaLowPower=false, UartIrdaPolarity=0, UartMedianFilterEnable=false, UartMpEnable=false, UartMpRxAcceptAddress=false, UartMpRxAddress=2, UartMpRxAddressMask=255, UartNumberOfDataBits=8, UartNumberOfStopBits=2, UartOvsFactor=12, UartParityType=2, UartRtsEnable=false, UartRtsPolarity=0, UartRtsTermEnable=false, UartRtsTriggerLevel=4, UartRxBreakWidth=11, UartRxBufferSize=8, UartRxEnable=false, UartRxIntrMask=0, UartRxOutputEnable=false, UartRxTermEnable=false, UartRxTriggerLevel=7, UartRxTxTermEnable=false, UartSmartioEnable=false, UartSmCardRetryOnNack=false, UartSubMode=0, UartTxBufferSize=8, UartTxEnable=false, UartTxIntrMask=0, UartTxOutputEnable=false, UartTxTermEnable=false, UartTxTriggerLevel=0, UartWakeEnable=false, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=SCB_P4_v4_0, CY_CONFIG_TITLE=I2C_1, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=I2C_1, CY_INSTANCE_SHORT_NAME=I2C_1, CY_MAJOR_VERSION=4, CY_MINOR_VERSION=0, CY_PDL_DRIVER_NAME=, CY_PDL_DRIVER_REQ_VERSION=, CY_PDL_DRIVER_SUBGROUP=, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.2, INSTANCE_NAME=I2C_1, )
module SCB_P4_v4_0_1 (
    cts_in,
    rts_out,
    interrupt,
    clock,
    rx_dma_out,
    tx_dma_out,
    s_mosi,
    s_sclk,
    s_ss,
    m_miso,
    m_mosi,
    m_sclk,
    m_ss0,
    m_ss1,
    m_ss2,
    m_ss3,
    s_miso,
    rx_in,
    tx_out,
    scl_b,
    sda_b,
    rx_tx_out);
    input       cts_in;
    output      rts_out;
    output      interrupt;
    input       clock;
    output      rx_dma_out;
    output      tx_dma_out;
    input       s_mosi;
    input       s_sclk;
    input       s_ss;
    input       m_miso;
    output      m_mosi;
    output      m_sclk;
    output      m_ss0;
    output      m_ss1;
    output      m_ss2;
    output      m_ss3;
    output      s_miso;
    input       rx_in;
    output      tx_out;
    inout       scl_b;
    inout       sda_b;
    output      rx_tx_out;


          wire  uncfg_rx_irq;
          wire  sclk_m_wire;
          wire  Net_1264;
          wire  Net_1258;
          wire  rx_irq;
          wire [3:0] select_m_wire;
          wire  Net_1099;
          wire  Net_1090;
          wire  Net_467;
          wire  Net_1316;
          wire  Net_252;
          wire  Net_1089;
          wire  Net_1320;
          wire  Net_1257;
          wire  sclk_s_wire;
          wire  Net_1268;
          wire  Net_1297;
          wire  Net_547;
          wire  Net_1001;
          wire  mosi_s_wire;
          wire  rts_wire;
          wire  mosi_m_wire;
          wire  Net_891;
          wire  Net_1263;
          wire  miso_s_wire;
          wire  cts_wire;
          wire  Net_899;
          wire  tx_wire;
          wire  Net_1028;
          wire  rx_wire;
          wire  Net_916;
          wire  Net_1000;
          wire  miso_m_wire;
          wire  Net_1172;
          wire  Net_1170;
          wire  select_s_wire;
          wire  Net_847;


	cy_clock_v1_0
		#(.id("7ca9760e-6931-4b43-a74b-782f631c6518/2dc2d7a8-ce2b-43c7-af4a-821c8cd73ccf"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("500000000"),
		  .is_direct(0),
		  .is_digital(0))
		SCBCLK
		 (.clock_out(Net_847));


	// select_s_VM (cy_virtualmux_v1_0)
	assign select_s_wire = s_ss;

	// rx_VM (cy_virtualmux_v1_0)
	assign rx_wire = rx_in;

	// rx_wake_VM (cy_virtualmux_v1_0)
	assign Net_1257 = uncfg_rx_irq;

	// clock_VM (cy_virtualmux_v1_0)
	assign Net_1170 = Net_847;

	// sclk_s_VM (cy_virtualmux_v1_0)
	assign sclk_s_wire = s_sclk;

	// mosi_s_VM (cy_virtualmux_v1_0)
	assign mosi_s_wire = s_mosi;

	// miso_m_VM (cy_virtualmux_v1_0)
	assign miso_m_wire = m_miso;

	wire [0:0] tmpOE__sda_net;
	wire [0:0] tmpFB_0__sda_net;
	wire [0:0] tmpINTERRUPT_0__sda_net;
	electrical [0:0] tmpSIOVREF__sda_net;

	cy_psoc3_pins_v1_10
		#(.id("7ca9760e-6931-4b43-a74b-782f631c6518/5382e105-1382-4a2e-b9f4-3bb2feba71e0"),
		  .drive_mode(3'b100),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b0),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("B"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b1),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		sda
		 (.oe(tmpOE__sda_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__sda_net[0:0]}),
		  .io({sda_b}),
		  .siovref(tmpSIOVREF__sda_net),
		  .interrupt({tmpINTERRUPT_0__sda_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__sda_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__scl_net;
	wire [0:0] tmpFB_0__scl_net;
	wire [0:0] tmpINTERRUPT_0__scl_net;
	electrical [0:0] tmpSIOVREF__scl_net;

	cy_psoc3_pins_v1_10
		#(.id("7ca9760e-6931-4b43-a74b-782f631c6518/22863ebe-a37b-476f-b252-6e49a8c00b12"),
		  .drive_mode(3'b100),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b0),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("B"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b1),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		scl
		 (.oe(tmpOE__scl_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__scl_net[0:0]}),
		  .io({scl_b}),
		  .siovref(tmpSIOVREF__scl_net),
		  .interrupt({tmpINTERRUPT_0__scl_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__scl_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    ZeroTerminal ZeroTerminal_7 (
        .z(Net_1099));


    assign Net_1258 = Net_1099 | Net_847;


	cy_isr_v1_0
		#(.int_type(2'b10))
		SCB_IRQ
		 (.int_signal(interrupt));


	// cts_VM (cy_virtualmux_v1_0)
	assign cts_wire = cts_in;

    cy_m0s8_scb_v2_0 SCB (
        .rx(rx_wire),
        .miso_m(miso_m_wire),
        .select_m(select_m_wire[3:0]),
        .sclk_m(sclk_m_wire),
        .mosi_s(mosi_s_wire),
        .select_s(select_s_wire),
        .sclk_s(sclk_s_wire),
        .mosi_m(mosi_m_wire),
        .scl(scl_b),
        .sda(sda_b),
        .tx(tx_wire),
        .miso_s(miso_s_wire),
        .interrupt(interrupt),
        .cts(cts_wire),
        .rts(rts_wire),
        .tx_req(tx_dma_out),
        .rx_req(rx_dma_out),
        .clock(Net_1170));
    defparam SCB.scb_mode = 0;

	// Device_VM4 (cy_virtualmux_v1_0)
	assign uncfg_rx_irq = Net_1000;


    assign rts_out = rts_wire;

    assign m_mosi = mosi_m_wire;

    assign m_sclk = sclk_m_wire;

    assign m_ss0 = select_m_wire[0];

    assign m_ss1 = select_m_wire[1];

    assign m_ss2 = select_m_wire[2];

    assign m_ss3 = select_m_wire[3];

    assign s_miso = miso_s_wire;

    assign tx_out = tx_wire;

    assign rx_tx_out = tx_wire;


endmodule

// top
module top ;

          wire  Net_240;
          wire  Net_332;
          wire  Net_331;
          wire  Net_237;
          wire  Net_236;
          wire  Net_235;
          wire  Net_234;
          wire  Net_233;
          wire  Net_232;
          wire  Net_231;
          wire  Net_230;
          wire  Net_229;
          wire  Net_228;
          wire  Net_227;
          wire  Net_226;
          wire  Net_225;
          wire  Net_224;
          wire  Net_223;
          wire  Net_335;
          wire  Net_221;
          wire  Net_220;
          wire  Net_219;

	wire [0:0] tmpOE__CEPIN_net;
	wire [0:0] tmpFB_0__CEPIN_net;
	wire [0:0] tmpIO_0__CEPIN_net;
	wire [0:0] tmpINTERRUPT_0__CEPIN_net;
	electrical [0:0] tmpSIOVREF__CEPIN_net;

	cy_psoc3_pins_v1_10
		#(.id("9c416bdb-3b4f-4952-8e71-c07cb13cfb6f"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		CEPIN
		 (.oe(tmpOE__CEPIN_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__CEPIN_net[0:0]}),
		  .io({tmpIO_0__CEPIN_net[0:0]}),
		  .siovref(tmpSIOVREF__CEPIN_net),
		  .interrupt({tmpINTERRUPT_0__CEPIN_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__CEPIN_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__GREEN_net;
	wire [0:0] tmpFB_0__GREEN_net;
	wire [0:0] tmpIO_0__GREEN_net;
	wire [0:0] tmpINTERRUPT_0__GREEN_net;
	electrical [0:0] tmpSIOVREF__GREEN_net;

	cy_psoc3_pins_v1_10
		#(.id("5b20c758-a7eb-47d9-a93e-7774ecdc6c6e"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		GREEN
		 (.oe(tmpOE__GREEN_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__GREEN_net[0:0]}),
		  .io({tmpIO_0__GREEN_net[0:0]}),
		  .siovref(tmpSIOVREF__GREEN_net),
		  .interrupt({tmpINTERRUPT_0__GREEN_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__GREEN_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__BLUE_net;
	wire [0:0] tmpFB_0__BLUE_net;
	wire [0:0] tmpIO_0__BLUE_net;
	wire [0:0] tmpINTERRUPT_0__BLUE_net;
	electrical [0:0] tmpSIOVREF__BLUE_net;

	cy_psoc3_pins_v1_10
		#(.id("4309abf7-5637-4b04-bbfc-ab55aefd7283"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		BLUE
		 (.oe(tmpOE__BLUE_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__BLUE_net[0:0]}),
		  .io({tmpIO_0__BLUE_net[0:0]}),
		  .siovref(tmpSIOVREF__BLUE_net),
		  .interrupt({tmpINTERRUPT_0__BLUE_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__BLUE_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    SW_Tx_UART_v1_50_0 MyUART ();

	wire [0:0] tmpOE__RED_net;
	wire [0:0] tmpFB_0__RED_net;
	wire [0:0] tmpIO_0__RED_net;
	wire [0:0] tmpINTERRUPT_0__RED_net;
	electrical [0:0] tmpSIOVREF__RED_net;

	cy_psoc3_pins_v1_10
		#(.id("e851a3b9-efb8-48be-bbb8-b303b216c393"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		RED
		 (.oe(tmpOE__RED_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__RED_net[0:0]}),
		  .io({tmpIO_0__RED_net[0:0]}),
		  .siovref(tmpSIOVREF__RED_net),
		  .interrupt({tmpINTERRUPT_0__RED_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__RED_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    SCB_P4_v4_0_1 I2C_1 (
        .cts_in(1'b0),
        .rts_out(Net_220),
        .interrupt(Net_221),
        .clock(1'b0),
        .rx_dma_out(Net_223),
        .tx_dma_out(Net_224),
        .s_mosi(1'b0),
        .s_sclk(1'b0),
        .s_ss(1'b0),
        .m_miso(1'b0),
        .m_mosi(Net_229),
        .m_sclk(Net_230),
        .m_ss0(Net_231),
        .m_ss1(Net_232),
        .m_ss2(Net_233),
        .m_ss3(Net_234),
        .s_miso(Net_235),
        .rx_in(1'b0),
        .tx_out(Net_237),
        .scl_b(Net_331),
        .sda_b(Net_332),
        .rx_tx_out(Net_240));

	wire [0:0] tmpOE__Comp_out_net;
	wire [0:0] tmpFB_0__Comp_out_net;
	wire [0:0] tmpIO_0__Comp_out_net;
	wire [0:0] tmpINTERRUPT_0__Comp_out_net;
	electrical [0:0] tmpSIOVREF__Comp_out_net;

	cy_psoc3_pins_v1_10
		#(.id("13b39836-a6a1-4674-bba1-e488ee9ab587"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		Comp_out
		 (.oe(tmpOE__Comp_out_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__Comp_out_net[0:0]}),
		  .io({tmpIO_0__Comp_out_net[0:0]}),
		  .siovref(tmpSIOVREF__Comp_out_net),
		  .interrupt({tmpINTERRUPT_0__Comp_out_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__Comp_out_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__HighF_out_net;
	wire [0:0] tmpFB_0__HighF_out_net;
	wire [0:0] tmpIO_0__HighF_out_net;
	wire [0:0] tmpINTERRUPT_0__HighF_out_net;
	electrical [0:0] tmpSIOVREF__HighF_out_net;

	cy_psoc3_pins_v1_10
		#(.id("e09d4f55-9840-4185-8142-84ae2640bc14"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		HighF_out
		 (.oe(tmpOE__HighF_out_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__HighF_out_net[0:0]}),
		  .io({tmpIO_0__HighF_out_net[0:0]}),
		  .siovref(tmpSIOVREF__HighF_out_net),
		  .interrupt({tmpINTERRUPT_0__HighF_out_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__HighF_out_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__LowF_out_net;
	wire [0:0] tmpFB_0__LowF_out_net;
	wire [0:0] tmpIO_0__LowF_out_net;
	wire [0:0] tmpINTERRUPT_0__LowF_out_net;
	electrical [0:0] tmpSIOVREF__LowF_out_net;

	cy_psoc3_pins_v1_10
		#(.id("e46d3c79-c6cd-44df-8599-5da98eb70303"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		LowF_out
		 (.oe(tmpOE__LowF_out_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__LowF_out_net[0:0]}),
		  .io({tmpIO_0__LowF_out_net[0:0]}),
		  .siovref(tmpSIOVREF__LowF_out_net),
		  .interrupt({tmpINTERRUPT_0__LowF_out_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__LowF_out_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__RelayLF_1_net;
	wire [0:0] tmpFB_0__RelayLF_1_net;
	wire [0:0] tmpIO_0__RelayLF_1_net;
	wire [0:0] tmpINTERRUPT_0__RelayLF_1_net;
	electrical [0:0] tmpSIOVREF__RelayLF_1_net;

	cy_psoc3_pins_v1_10
		#(.id("5bc56c93-b310-44cb-b946-0287f4f975c4"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		RelayLF_1
		 (.oe(tmpOE__RelayLF_1_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__RelayLF_1_net[0:0]}),
		  .io({tmpIO_0__RelayLF_1_net[0:0]}),
		  .siovref(tmpSIOVREF__RelayLF_1_net),
		  .interrupt({tmpINTERRUPT_0__RelayLF_1_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__RelayLF_1_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__RelayHF_2_net;
	wire [0:0] tmpFB_0__RelayHF_2_net;
	wire [0:0] tmpIO_0__RelayHF_2_net;
	wire [0:0] tmpINTERRUPT_0__RelayHF_2_net;
	electrical [0:0] tmpSIOVREF__RelayHF_2_net;

	cy_psoc3_pins_v1_10
		#(.id("9d908906-84b3-4320-a8f7-672796303a63"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		RelayHF_2
		 (.oe(tmpOE__RelayHF_2_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__RelayHF_2_net[0:0]}),
		  .io({tmpIO_0__RelayHF_2_net[0:0]}),
		  .siovref(tmpSIOVREF__RelayHF_2_net),
		  .interrupt({tmpINTERRUPT_0__RelayHF_2_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__RelayHF_2_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__RelayC_3_net;
	wire [0:0] tmpFB_0__RelayC_3_net;
	wire [0:0] tmpIO_0__RelayC_3_net;
	wire [0:0] tmpINTERRUPT_0__RelayC_3_net;
	electrical [0:0] tmpSIOVREF__RelayC_3_net;

	cy_psoc3_pins_v1_10
		#(.id("3eb3be75-347a-425a-bd2a-15f12a7995cc"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .sio_hifreq(""),
		  .sio_vohsel(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		RelayC_3
		 (.oe(tmpOE__RelayC_3_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__RelayC_3_net[0:0]}),
		  .io({tmpIO_0__RelayC_3_net[0:0]}),
		  .siovref(tmpSIOVREF__RelayC_3_net),
		  .interrupt({tmpINTERRUPT_0__RelayC_3_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__RelayC_3_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};



endmodule

