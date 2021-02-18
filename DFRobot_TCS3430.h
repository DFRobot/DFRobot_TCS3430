/*!
 * @file DFRobot_TCS3430.h
 * @brief Define the infrastructure for the DFRobot_TCS3430 class
 * @n This is a DFRobot_TCS3430 sensor that supports IIC communication. The IIC address cannot be changed, default to 0x39. The functions are as follows:
 * @n Function Detection of XYZ tristimulus and infrared data
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @SKU SEN0403
 * @licence The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version V1.0
 * @date 2021-01-26
 * @url  https://github.com/DFRobot/DFRobot_TCS3400
 */
#ifndef __DFRobot_TCS3430_H__
#define __DFRobot_TCS3430_H__
#include <Arduino.h>
#include <Wire.h>


#define DFRobot_TCS3430_ICC_ADDR            0x39

/*
   * Enable Register (ENABLE 0x80)
   * ------------------------------------------------------------------------------------------
   * |    b7    |    b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
   * ------------------------------------------------------------------------------------------
   * |                  reversed                 |   WEN    | reserved |    AEN    |   PON    |
   * ------------------------------------------------------------------------------------------
   *
   *
*/
typedef struct {
  uint8_t   pon: 1; /* Power ON. This field activates the internal oscillator to permit the timers and ADC channels to operate. 
                       Writing a one activates the oscillator. 
                       Writing a zero disables the oscillator. */
  uint8_t   aen: 1; /* ALS Enable. This bit actives the ALS function.
                      Set aen=1 and pon=1 in the same command to ensure autozero function is run prior to the first measurement.*/
  uint8_t   reservedBit2: 1; /* Reserved. */
  uint8_t   wen: 1; /* Wait Enable. This bit activates the wait feature. 
                       Writing a 1 activates the wait timer.
                       Writing a 0 disables the wait timer. */
  uint8_t   reservedBit4_7: 4; /* Reserved. */
} __attribute__ ((packed)) sEnableReg_t;

/*Integration Time Register (ATIME 0x81)*/

/*Wait Time Register (WTIME 0x83)*/

/*
   *  Channel 0 Interrupt Threshold Register (0x84 - 0x87)
   * --------------------------------------------------------------------------
   * |Register |  Address  |  Bits  |               Description               |
   * --------------------------------------------------------------------------
   * |  AILTL  |   0x84    |  7:0   |      Low Byte of the Low Threshold      |
   * --------------------------------------------------------------------------
   * |  AILTH  |   0x85    |  7:0   |      High Byte of the Low Threshold     |
   * --------------------------------------------------------------------------
   * |  AIHTL  |   0x86    |  7:0   |      Low Byte of the High Threshold     |
   * --------------------------------------------------------------------------
   * |  AIHTH  |   0x87    |  7:0   |      High Byte of the High Threshold    |
   * --------------------------------------------------------------------------
*/

/*
   * PERS Register (0x8C)
   * ------------------------------------------------------------------------------------------
   * |    b7    |    b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
   * ------------------------------------------------------------------------------------------
   * |                  reversed                 |                   APERS                    |
   * ------------------------------------------------------------------------------------------
   *
   *
   *                      APERS                              
   *----------------------------------------------------------
   *| Field Value |            Persistence                   |
   *----------------------------------------------------------
   *|     0000    |   Every ALS cycle generates an interrupt |
   *----------------------------------------------------------
   *|     0001    |   Any value outside of threshold range   |
   *----------------------------------------------------------
   *|     0010    |   2 consecutive values out of range      |
   *----------------------------------------------------------
   *|     0011    |   3 consecutive values out of range      |
   *----------------------------------------------------------
   *|     0100    |   5 consecutive values out of range      |
   *----------------------------------------------------------
   *|     0101    |   10 consecutive values out of range     |
   *----------------------------------------------------------
   *|     0110    |   15 consecutive values out of range     |
   *----------------------------------------------------------
   *|     0111    |   20 consecutive values out of range     |
   *----------------------------------------------------------
   *|     1000    |   25 consecutive values out of range     |
   *----------------------------------------------------------
   *|     1001    |   30 consecutive values out of range     |
   *----------------------------------------------------------
   *|     1010    |   35 consecutive values out of range     |
   *----------------------------------------------------------
   *|     1011    |   40 consecutive values out of range     |
   *----------------------------------------------------------
   *|     1100    |   45 consecutive values out of range     |
   *----------------------------------------------------------
   *|     1101    |   50 consecutive values out of range     |
   *----------------------------------------------------------
   *|     1110    |   55 consecutive values out of range     |
   *----------------------------------------------------------
   *|     1111    |   60 consecutive values out of range     |
   *----------------------------------------------------------
*/
#define DFRobot_TCS3430_PERS_0                      0x00
#define DFRobot_TCS3430_PERS_1                      0x01
#define DFRobot_TCS3430_PERS_2                      0x02
#define DFRobot_TCS3430_PERS_3                      0x03
#define DFRobot_TCS3430_PERS_4                      0x04
#define DFRobot_TCS3430_PERS_5                      0x05
#define DFRobot_TCS3430_PERS_6                      0x06
#define DFRobot_TCS3430_PERS_7                      0x07
#define DFRobot_TCS3430_PERS_8                      0x08
#define DFRobot_TCS3430_PERS_9                      0x09
#define DFRobot_TCS3430_PERS_A                      0x0A
#define DFRobot_TCS3430_PERS_B                      0x0B
#define DFRobot_TCS3430_PERS_C                      0x0C
#define DFRobot_TCS3430_PERS_D                      0x0D
#define DFRobot_TCS3430_PERS_E                      0x0E
#define DFRobot_TCS3430_PERS_F                      0x0F


/* 
   * CFG0 Register (0x8D)
   * ------------------------------------------------------------------------------------------------
   * |    b7       |       b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
   * ------------------------------------------------------------------------------------------------
   * | reversed<1> |                  reversed                    |   WLONG  |       reversed       |
   * ------------------------------------------------------------------------------------------------
   * Reserved: Write as 0.
   * Reserved<1>: Write as 1.
   * Wait Long: When asserted, the wait cycles are increased by a factor 12× from that programmed in the WTIME register.
*/
#define DFRobot_TCS3430_CONFIG_NO_WLONG             0x80
#define DFRobot_TCS3430_CONFIG_WLONG                0x84

/* 
   * CFG1 Register (0x90) 
   * ---------------------------------------------------------------------------------------------
   * |    b7    |       b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
   * ---------------------------------------------------------------------------------------------
   * |                  reversed                    |   AMUX   | reversed |         AGAIN        |
   * ---------------------------------------------------------------------------------------------
   * Reserved: Write as 0.
   * AMUX:ALS Multiplexer. Sets the CH3 input. Default = 0 (X Channel). Set to 1 to read IR2.
   * AGAIN: ALS Gain Control. Sets the gain of the ALS DAC.
   * ----------------------------------------------------------
   * | Field Value |            ALS GAIN VALUE                |
   * ----------------------------------------------------------
   * |     00      |               1X Gain                    |
   * ----------------------------------------------------------
   * |     01      |               4X Gain                    |
   * ----------------------------------------------------------
   * |     10      |               16X Gain                   |
   * ----------------------------------------------------------
   * |     11      |               64X Gain                   |
   * ----------------------------------------------------------
*/
typedef struct { 
  uint8_t   again: 2; 
  uint8_t   reservedBit2: 1; 
  uint8_t   amux: 1;
  uint8_t   reservedBit4_7: 4; 
} __attribute__ ((packed)) sCFG1Reg_t;

/*
   * Revision ID Register (REVID 0x91)
   * ------------------------------------------------------------------------------------------
   * |    b7    |    b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
   * ------------------------------------------------------------------------------------------
   * |                  reversed                 |                   RevID                    |
   * ------------------------------------------------------------------------------------------
   * Reserved: Write as 0.
   * RevID:  Revision Number Identification
   * value:0x41
*/

/* 
   * ID Register (ID 0x92) ;
   * ---------------------------------------------------------------------------------------------
   * |    b7    |       b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
   * ---------------------------------------------------------------------------------------------
   * |                                ID                                  |       RESERVED       |
   * ---------------------------------------------------------------------------------------------
   * ID: Device Identification = 110111
   * value:0xDC
*/
  #define  TCS3430_ID                         0xDC
  #define  TCS3430_REVISION_ID                0x41
/*

   * Status Register (STATUS 0x93)
   * ------------------------------------------------------------------------------------------
   * |    b7    |    b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
   * ------------------------------------------------------------------------------------------
   * |   ASAT   |       Reserved      |    AINT  |                  Reserved                  |
   * ------------------------------------------------------------------------------------------
   * ASAT: ALS Saturation. This flag is set for analog saturation writing a 1 will clear this status flag.
   * Reserved:Reserved.
   * AINT:ALS Interrupt. Indicates that the device is asserting an ALS interrupt. writing a 1 will clear this status flag.
*/

/*
   * RGBC Data Registers (0x94 - 0x9B)
   * ------------------------------------------------------------------------------------------------
   * |  Register  |  Address  |  Bits  |               Description                                  |
   * ------------------------------------------------------------------------------------------------
   * |  CH0DATAL  |   0x94    |  7:0   |         Low Byte of CH0 ADC data. Contains Z data.         |
   * ------------------------------------------------------------------------------------------------
   * |  CH0DATAH  |   0x95    |  7:0   |         High Byte of CH0 ADC data. Contains Z data.        |
   * ------------------------------------------------------------------------------------------------
   * |  CH1DATAL  |   0x96    |  7:0   |         Low Byte of CH1 ADC data. Contains Y data          |
   * ------------------------------------------------------------------------------------------------
   * |  CH1DATAH  |   0x97    |  7:0   |         High Byte of CH1 ADC data. Contains Y data.        |
   * ------------------------------------------------------------------------------------------------
   * |  CH2DATAL  |   0x98    |  7:0   |         Low Byte of CH2 ADC data. Contains IR1 data.       |
   * ------------------------------------------------------------------------------------------------
   * |  CH2DATAH  |   0x99    |  7:0   |         High Byte of CH2 ADC data. Contains IR1 data.      |
   * ------------------------------------------------------------------------------------------------
   * |  CH3DATAL  |   0x9A    |  7:0   |         Low Byte of CH3 ADC data. contains X\IR2 data      |(If AMUX = 0 contains X data.If AMUX = 1 contains IR2 data.Default = X data.)
   * ------------------------------------------------------------------------------------------------
   * |  CH3DATAH  |   0x9B    |  7:0   |         High Byte of CH3 ADC data. contains X\IR2 data     |(If AMUX = 0 contains X data.If AMUX = 1 contains IR2 data.Default = X data.)
   * ------------------------------------------------------------------------------------------------
*/

/* 
   * CFG2 Register (0x9F)
   * ---------------------------------------------------------------------------------------------
   * |    b7    |       b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
   * ---------------------------------------------------------------------------------------------
   * |           Reserved(000)           |   HGAIN  |             Reserved(0100)                 |
   * ---------------------------------------------------------------------------------------------
   * HGAIN:High 128x gain. If this bit is set and AGAIN in the CFG1 register is set to 11, then the 128x gain mode will be enabled.
*/
#define DFRobot_TCS3430_HGAIN_DISABLE                 0x04
#define DFRobot_TCS3430_HGAIN_ENABLE                  0x14

/*
   * CFG3 Register (0xAB)
   * ----------------------------------------------------------------------------------------------------
   * |        b7          |    b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
   * ----------------------------------------------------------------------------------------------------
   * |   INT_READ_CLEAR   |     Reserved(0)     |    SAI   |           Reserved(any value)              |
   * ----------------------------------------------------------------------------------------------------
   * INT_READ_CLEAR:If this bit is set, all flag bits in the STATUS register will be reset whenever the STATUS register is read over I2C.
   * SAI:Sleep After Interrupt. Power down the device at the end of the ALS cycle if an interrupt has been generated.
*/
typedef struct { 
  uint8_t   reservedBit0_3: 4; 
  uint8_t   sai: 1; 
  uint8_t   reservedBit5_6: 2;
  uint8_t   intReadClear: 1; 
} __attribute__ ((packed)) sCFG3Reg_t;

/* 
   * AZ_CONFIG Register (0xD6)
   * ---------------------------------------------------------------------------------------------
   * |     b7    |       b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0   |
   * ---------------------------------------------------------------------------------------------
   * |  AZ_MODE  |                                 AZ_NTH_ITERATION                              |
   * ---------------------------------------------------------------------------------------------
   * AZ_MODE: 0, Always start at zero when searching the best offset value
              1, Always start at the previous (offset_c) with the auto-zero mechanism
   * AZ_NTH_ITERATION : Run autozero automatically every nth ALS iteration(0=never, 7Fh=only at first ALS cycle, n=every nth time)
*/
typedef struct { 
  uint8_t   azNTHIteration: 7;
  uint8_t   azMode: 1; 
} __attribute__ ((packed)) sAZCFGReg_t;

/*
   * INTENAB Register (0xDD)
   * ------------------------------------------------------------------------------------------
   * |    b7    |    b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
   * ------------------------------------------------------------------------------------------
   * |  ASIEN   |     Reserved(0)     |   AIEN   |                 Reserved(0)                |
   * ------------------------------------------------------------------------------------------
   * ASIEN: Writing '1' to this bit enables ASAT interrupt.
   * AIEN: Writing '1' to this bit enables ALS interrupt.
*/
typedef struct { 
  uint8_t   reservedBit0_3: 4; 
  uint8_t   aien: 1; 
  uint8_t   reservedBit5_6: 2;
  uint8_t   asien: 1; 
} __attribute__ ((packed)) sINTENABReg_t;

class DFRobot_TCS3430{
public:
  #define  TWO_BYTE     2/* the set of register address*/
  typedef enum {
    eRegENABLEAddr = 0x80,
    eRegATIMEAddr,
    eRegWTIMEAddr = 0x83,
    eRegAILTLAddr,
    eRegAILTHAddr,
    eRegAIHTLAddr,
    eRegAIHTHAddr,
    eRegPERSAddr = 0x8C,
    eRegCFG0Addr,
    eRegCFG1Addr = 0x90,
    eRegREVIDAddr,
    eRegIDAddr,
    eRegSTATUSAddr,
    eRegCH0DATALAddr,
    eRegCH0DATAHAddr,
    eRegCH1DATALAddr,
    eRegCH1DATAHAddr,
    eRegCH2DATALAddr,
    eRegCH2DATAHAddr,
    eRegCH3DATALAddr,
    eRegCH3DATAHAddr,
    eRegCFG2Addr = 0x9F,
    eRegCFG3Addr = 0xAB,
    eRegAZCONFIGAddr = 0xD6,
    eRegINTENABAddr = 0xDD,
  } eTCS3430RegisterAddress_t;
public:
  /**
   * @brief  constructed function
   * @param  pWire  When instantiate this class, you can specify its twowire
   */
  DFRobot_TCS3430(TwoWire *pWire=&Wire);
  
  /**
   * @brief  Destructor
   */
  ~DFRobot_TCS3430(){
  };
  
  /**
   * @brief  Initialization function
   * @return Whether the device is on or not. return true succeed ;return false failed.
   */
  bool begin();

  /**
   * @brief  Config the wait timer 
   * @param  mode  ture : enable ; false : disenable
   */
  void setWaitTimer(bool mode = true);

  /**
   * @brief  Set the function of wait long time
   * @param  mode  ture : enable ; false : disenable
   */
  void setWaitLong(bool mode = true);

  /**
   * @brief  Set the internal integration time of the  four-channel ADCs
   * @param  aTIme  integration time
   */
  void setIntegrationTime(uint8_t aTime);

  /**
   * @brief  set wait time 
   * @param  wTime  wait time 
   */
  void setWaitTime(uint8_t wTime);

  /**
   * @brief  Set the ALS gain 
   * @param  aGain  the value of gain
   */
  void setALSGain(uint8_t aGain);

  /**
   * @brief  Set ALS interrupt Persistence
   * @param  apers :ALS Interrupt Persistence
   */
  void setInterruptPersistence(uint8_t apers);

  /**
   * @brief  get device status
   * @return  status
   */
  uint8_t getDeviceStatus();
  
  /**
   * @brief  get channel 0 value
   * @return  the z data
   */
  uint16_t getZData();

  /**
   * @brief  get channel 1 value
   * @return  the y data
   */
  uint16_t getYData();

  /**
   * @brief  get channel 2 value
   * @return  the IR1 data 
   */
  uint16_t getIR1Data();
  
  /**
   * @brief  get channel 3 value
   * @return  the x data
   */
  uint16_t getXData();
  
  /**
   * @brief  get channel 3 value
   * @return  the IR2 data
   */
  uint16_t getIR2Data();
  /**
   * @brief  Set the ALS High gain 
   * @param  mode  ture : enable ; false : disenable
   */
  void setHighGAIN(bool mode);

  /**
   * @brief  If this bit is set, all flag bits in the STATUS register will be reset whenever the STATUS register is read over I2C.
   * @param  mode  ture : enable ; false : disenable
   */
  void setIntReadClear(bool mode = true);

  /**
   * @brief  Config the function of 'sleep after interruption'
   * @param  mode  ture : enable ; false : disenable
   */
  void setSleepAfterInterrupt(bool mode = true);

  /**
   * @brief  set az mode
   * @param  mode  :0,Always start at zero when searching the best offset value
                   :1,Always start at the previous (offset_c) with the auto-zero mechanism
   */
  void setAutoZeroMode(uint8_t mode);
  
  /**
   * @brief  set az nth iteration type(Run autozero automatically every nth ALS iteration)
   * @param  value :0,never
                   :7,only at first ALS cycle
                   :n, every nth time
   */
  void setAutoZeroNTHIteration(uint8_t value);

  /**
   * @brief  Config the ALS saturation interruption
   * @param  mode  ture : enable ; false : disenable
   */
  void setALSSaturationInterrupt(bool mode = true);

  /**
   * @brief  Config the ALS interruption
   * @param  mode  ture : enable ; false : disenable
   */
  void setALSInterrupt(bool mode = true);

  /**
   * @brief  Set the channel 0 interrupt threshold
   * @param  thresholdL :the low 16 bit values
   * @param  thresholdH :the high 16 bit values
   */
  void setCH0IntThreshold(uint16_t thresholdL,uint16_t thresholdH);

private:

  /**
   * @brief  Access to IR channel; allows mapping of IR channel on channel 3.
   * @param  mode  ture : enable ; false : disenable
   */
  void setIR2Channel(bool mode = true);
  
  /**
   * @brief  get the revision id
   * @return the revision id
   */
  uint8_t getRevisionID();
  
  /**
   * @brief  get the device id
   * @return  the device id
   */
  uint8_t getDeviceID();
  
  /**
   * @brief  Activating the internal oscillator to permit the timers and ADC channels to operate ,and activing the ALS function
   */
  void setPowerALSADC();

  /**
   * @brief  disables the oscillator and puts the part into a low power sleep mode
   */
  void powerOFF();

  /**
   * @brief  Disable the four-channel ADC
   */
  void disableALSADC();

  /**
   * @brief  Initializes all registers of the device
   */
  void softReset();

  /**
   * @brief  config register
   * @param  regAddr : register address
   * @param  value : Writes the value of the register
   */
  void write(uint8_t regAddr,uint8_t value);

  /**
   * @brief  read register
   * @param  regAddr : register address
   * @param  readNum : Number of bytes read
   * @return Read data from a register
   */
  uint16_t read(uint8_t regAddr,uint8_t readNum);


private:
  eTCS3430RegisterAddress_t _TCS3430Register;
  sEnableReg_t _enableReg;
  TwoWire* _pWire;
  uint8_t _deviceAddr;
  sCFG1Reg_t _cfg1Reg;
  sCFG3Reg_t _cfg3Reg;
  sAZCFGReg_t _AZCfgReg;
  sINTENABReg_t _intEnabReg;
  uint16_t _atime;
  uint16_t _wtime;
  uint8_t _wlong;
};

#endif
