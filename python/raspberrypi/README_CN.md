# DFRobot_TCS3430
- [English Version](./README.md)

TCS3430具有先进的数字环境光感测（ALS）和CIE 1931三刺激色彩感测（XYZ），CIE1931 XYZ三刺激模型是根据人眼中三种视锥细胞设立的XYZ标准，CIE1931 XYZ色彩空间包含普通视力的人可以看到的所有色彩感觉。TCS3430的光谱响应几乎和人眼一致，可以实现高精度的照度和色温测量，因此可以实现所测即所见。

![](../../resources/images/SEN0403.png)


## 产品链接 (https://www.dfrobot.com.cn/goods-3083.html)

    SKU:SEN0403

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性y)
* [历史](#历史)
* [创作者](#创作者)

## 概述

X/Y/Z三刺激光和红外数据的检测

## 库安装

要使用这个库，首先将库下载到Raspberry Pi，然后打开例程文件夹。要执行一个例程demox.py，请在命令行中输入python demox.py。例如，要执行get_xyz_ir_data.py例程，你需要输入:
```
python get_xyz_ir_data.py
```
## 方法

```Python
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

## 兼容性

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |     √     |            |          |         |
| RaspberryPi4 |           |            |    √     |         |

* Python 版本

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## 历史

- 日期 2021-9-26
- 版本 V1.0.0


## 创作者

Written by yangfeng(feng.yang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

