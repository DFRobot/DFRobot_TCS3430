# DFRobot_TCS3430

- [中文版](./README_CN.md)

The device featrues advanced digital Ambient Light Sensing (ALS) and CIE 1931 Tristimulus Color Sensing (XYZ). Each of the channels has a filter to control its optical response, which allows the device to accurately measure ambient light and sense color. These measurements are used to calculate chromaticity, illuminance and color temperatrue, all of which are used to support various potential applications.

![](../../resources/images/SEN0403.png)

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

To use this library, first download the library to Raspberry Pi, then open the routines folder. To execute one routine, demox.py, type python demox.py on the command line. To execute the get_xyz_ir_data.py routine, for example, you need to type:

```
python get_xyz_ir_data.py
```

## Methods

```python
  ''' 
    @brief  Set temperatrue and humidity
    @return  equipment condition, True succeed, False failed 
  '''
  begin(self)

  ''' 
    @brief  enable wait timer 
    @param  mode  set wait-timer,True enable False disenable
  '''
  set_wait_timer(self,mode=True)

  ''' 
    @brief  Set the internal integration time
    @param  atime  the internal integration time(range: 0x00 -0xff)
  '''
  set_integration_time(self,atime)

  ''' 
    @brief  Set wait time 
    @param  wtime  wait time(range: 0x00 -0xff)
  '''
  set_wait_time(self,wtime)

  ''' 
    @brief  Set the channel 0 interrupt threshold
    @param  ailt   the low 16 bit values(range: 0x0000 -0xffff)
    @param  aiht   the high 16 bit values(range: 0x0000 -0xffff)
  '''
  set_interrupt_threshold(self,ailt,aiht)

  ''' 
    @brief  Set the channel 0 interrupt Persistence
    @param  apers  Interrupt Persistence(range: 0x00 -0x0f)
  '''
  set_interrupt_persistence(self,apers)

  ''' 
    @brief  Set the wait long time
    @param  mode  True enable  False disenable
  '''
  set_wait_long_time(self,mode=True)

  ''' 
    @brief  Set the ALS gain 
    @param  gain  the value of gain(range: 0x00 -0x03)
  '''
  set_als_gain(self,gain)

  ''' 
    @brief get channel 0 value
    @return  the z data
  '''
  get_z_data(self)
        
  ''' 
    @brief get channel 1 value
    @return  the y data
  '''
  get_y_data(self)

  ''' 
    @brief get channel 2 value
    @return  the IR1 data
  '''
  get_ir1_data(self)
    
  ''' 
    @brief get channel 3 value
    @return  the X data
  '''
  get_x_data(self)
        
  ''' 
    @brief get channel 3 value
    @return  the IR2 data
  '''
  get_ir2_data(self)

  ''' 
    @brief  Set the ALS  128x gain 
    @param  mode  True enable  False disenable
  '''
  set_als_high_gain(self,mode=True)

  '''
    @brief  If this bit is set, all flag bits in the STATUS register will be reset whenever the STATUS register is read over I2C. 
    @param  mode  True enable  False disenable
  '''
  set_int_read_clear(self,mode=True)

  '''
    @brief  Turn on sleep after interruption
    @param  mode  True enable  False disenable
  '''
  set_sleep_after_interrupt(self,mode=True)

  '''
    @brief  set az mode
    @param  mode  0,Always start at zero when searching the best offset value  1,Always start at the previous (offset_c) with the auto-zero mechanism
  '''
  set_auto_zero_mode(self,mode=0)

  ''' 
    @brief  set az nth iteration type(Run autozero automatically every nth ALS iteration)
    @param  iteration_type  0,never  7F,only at first ALS cycle  n, every nth time
  '''
  set_auto_zero_nth_iteration(self,iteration_type)

  '''
    @brief  enable ambient light sensing interrupt
    @param  mode  True enable  False disenable
  '''
  set_als_interrupt(self,mode=True)

  '''
    @brief  enable ALS saturation interription
    @param  mode  True enable  False disenable
  '''
  set_als_saturation_interrupt(self,mode=True)

  '''
    @brief  Get the status of the device
  '''
  get_device_status(self)

```

## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## History

- data 2021-01-28
- version V1.0


## Credits

Written by [yangfeng]<feng.yang@dfrobot.com>,2021,(Welcome to our [website](https://www.dfrobot.com/))
