# DFRobot_TCS3430

- [中文版](./README_CN.md)

The device featrues advanced digital Ambient Light Sensing (ALS) and CIE 1931 Tristimulus Color Sensing (XYZ). Each of the channels has a filter to control its optical response, which allows the device to accurately measure ambient light and sense color. These measurements are used to calculate chromaticity, illuminance and color temperatrue, all of which are used to support various potential applications.

![](./resources/images/SEN0403.png)

## Product Link (https://www.dfrobot.com/product-2257.html)
    SKU:SEN0403

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary
Detection of XYZ tristimulus and infrared data

## Installation

To use this library, download the library file first, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
 /**
   * @brief  Initialization function
   * @return Whether the device is on or not. return true succeed ;return false failed.
   */
  bool begin();

  /**
   * @brief  Config the wait timer 
   * @param  mode  true : enable ; false : disenable
   */
  void setWaitTimer(bool mode = true);

  /**
   * @brief  Set the function of wait long time
   * @param  mode  true : enable ; false : disenable
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
   * @param  mode  true : enable ; false : disenable
   */
  void setHighGAIN(bool mode);

  /**
   * @brief  If this bit is set, all flag bits in the STATUS register will be reset whenever the STATUS register is read over I2C.
   * @param  mode  true : enable ; false : disenable
   */
  void setIntReadClear(bool mode = true);

  /**
   * @brief  Config the function of 'sleep after interruption'
   * @param  mode  true : enable ; false : disenable
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
   * @param  mode  true : enable ; false : disenable
   */
  void setALSSaturationInterrupt(bool mode = true);

  /**
   * @brief  Config the ALS interruption
   * @param  mode  true : enable ; false : disenable
   */
  void setALSInterrupt(bool mode = true);

  /**
   * @brief  Set the channel 0 interrupt threshold
   * @param  thresholdL :the low 16 bit values
   * @param  thresholdH :the high 16 bit values
   */
  void setCH0IntThreshold(uint16_t thresholdL,uint16_t thresholdH);

```


## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno |       √      |             |            | 
FireBeetle esp32 |       √      |             |            | 
FireBeetle esp8266 |       √      |             |            | 
FireBeetle m0 |       √      |             |            | 
Leonardo |       √      |             |            | 
Microbit |       √      |             |            | 
Arduino MEGA2560 | √ | | | 


## History

- data 2023-02-24
- version V1.0


## Credits

Written by [yangfeng]<feng.yang@dfrobot.com>,2021,(Welcome to our [website](https://www.dfrobot.com/))
