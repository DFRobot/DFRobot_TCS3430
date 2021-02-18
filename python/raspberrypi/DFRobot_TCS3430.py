""" file DFRobot_TCS3430.py
  # DFRobot_TCS3430 Class infrastructure, implementation of underlying methods
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
  @author      [yangfeng]<feng.yang@dfrobot.com> 
  @version  V1.0
  @date  2021-01-26
  @get from https://www.dfrobot.com
  @url https://github.com/DFRobot/DFRobot_TCS3430
"""
import smbus
import time

class DFRobot_TCS3430:
  DFRobot_TCS3430_IIC_ADDR           = 0x39
  
  TCS3430_REG_ENABLE_ADDR            = 0x80
  TCS3430_REG_ATIME_ADDR             = 0x81
  TCS3430_REG_WTIME_ADDR             = 0x83
  TCS3430_REG_AILTL_ADDR             = 0x84
  TCS3430_REG_AILTH_ADDR             = 0x85
  TCS3430_REG_AIHTL_ADDR             = 0x86
  TCS3430_REG_AIHTH_ADDR             = 0x87
  TCS3430_REG_PERS_ADDR              = 0x8C
  TCS3430_REG_CFG0_ADDR              = 0x8D
  TCS3430_REG_CFG1_ADDR              = 0x90
  TCS3430_REG_REVID_ADDR             = 0x91
  TCS3430_REG_ID_ADDR                = 0x92
  TCS3430_REG_STATUS_ADDR            = 0x93
  TCS3430_REG_CH0DATAL_ADDR          = 0x94
  TCS3430_REG_CH0DATAH_ADDR          = 0x95
  TCS3430_REG_CH1DATAL_ADDR          = 0x96
  TCS3430_REG_CH1DATAH_ADDR          = 0x97
  TCS3430_REG_CH2DATAL_ADDR          = 0x98
  TCS3430_REG_CH2DATAH_ADDR          = 0x99
  TCS3430_REG_CH3DATAL_ADDR          = 0x9A
  TCS3430_REG_CH3DATAH_ADDR          = 0x9B
  TCS3430_REG_CFG2_ADDR              = 0x9F
  TCS3430_REG_CFG3_ADDR              = 0xAB
  TCS3430_REG_AZCONFIG_ADDR          = 0xD6
  TCS3430_REG_INTENAB_ADDR           = 0xDD
  
  ENABLEREG_POWER_ON                 = 0x01
  ENABLEREG_POWER_OFF                = 0xFE
  ENABLEREG_ALS_EN                   = 0x02
  ENABLEREG_ALS_DISEN                = 0xFD
  ENABLEREG_WAIT_EN                  = 0x08
  ENABLEREG_WAIT_DISEN               = 0xF7
  
  CONFIG_NO_WLONG                    = 0x80
  CONFIG_WLONG                       = 0x84
  
  CFG1_IR2_EN                        = 0x08
  CFG1_IR2_DISEN                     = 0xF7
  
  CFG2_HIGH_GAIN_EN                  = 0x14
  CFG2_HIGH_GAIN_DISEN               = 0x04
  
  CFG3_INT_READ_CLEAR_EN             = 0x80
  CFG3_INT_READ_CLEAR_DISEN          = 0x10
  CFG3_SAI_EN                        = 0x10
  CFG3_SAI_DISEN                     = 0x80

  AZ_MODE_0                          = 0x7F
  AZ_MODE_1                          = 0x80
  
  ENABLEREG_ALS_INT_EN               = 0x10
  ENABLEREG_ALS_INT_DISEN            = 0x80
  ALS_SATURATION_INTERRUPT_EN        = 0x80
  ALS_SATURATION_INTERRUPT_DISEN     = 0x10
  
  TCS3430_ID                         = 0xDC
  TCS3430_REVISION_ID                = 0x41
  
  ''' 
    @brief  Module init
    @param  bus  Set to IICBus
  '''
  def __init__(self,bus = 1):
    self.__i2cbus = smbus.SMBus(bus)
    self.__i2c_addr = self.DFRobot_TCS3430_IIC_ADDR
    self.__wlong = 0
    self.__atime = 0
    self.__wtime = 0

  ''' 
    @brief  Initialize the device and turn it on
    @return  Whether the device is on or not. True succeed, False failed 
  '''
  def begin(self):
    self.__soft_reset()
    self.__set_power_als_on()
    device_id = self.__get_device_id()
    revision_id =self.__get_revision_id()
    if device_id != self.TCS3430_ID and revision_id != self.TCS3430_REVISION_ID :
      self.__set_device_adc(False)
      self.__set_device_power(False)
      return False
    return True 

  ''' 
    @brief  Config the wait timer 
    @param  mode  set wait-timer,True enable False disenable
  '''
  def set_wait_timer(self,mode=True):
    if mode==True:
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR)|self.ENABLEREG_WAIT_EN)
    if mode==False:
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR)&self.ENABLEREG_WAIT_DISEN)

  ''' 
    @brief  Set the internal integration time
    @param  atime  the internal integration time(range: 0x00 -0xff)
  '''
  def set_integration_time(self,atime):
    atime = atime & 0xFF
    self.__atime = atime
    self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_ATIME_ADDR, atime)

  ''' 
    @brief  Set wait time 
    @param  wtime  wait time(range: 0x00 -0xff)
  '''
  def set_wait_time(self,wtime):
    wtime = wtime & 0xFF
    self.__wtime = wtime
    self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_WTIME_ADDR, wtime)

  ''' 
    @brief  Set the channel 0 interrupt threshold
    @param  ailt   the low 16 bit values(range: 0x0000 -0xffff)
    @param  aiht   the high 16 bit values(range: 0x0000 -0xffff)
  '''
  def set_interrupt_threshold(self,ailt,aiht):
    ailtl = ailt & 0xFF
    ailth = (ailt>>8) & 0xFF
    aihtl = aiht & 0xFF
    aihth = (aiht>>8) & 0xFF
    self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_AILTL_ADDR, ailtl)
    self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_AILTH_ADDR, ailth)
    self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_AIHTL_ADDR, aihtl)
    self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_AIHTH_ADDR, aihth)

  ''' 
    @brief  Set the channel 0 interrupt Persistence
    @param  apers  Interrupt Persistence(range: 0x00 -0x0f)
  '''
  def set_interrupt_persistence(self,apers):
    apers = apers & 0xFF
    self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_PERS_ADDR, apers)

  ''' 
    @brief  Set the wait long time
    @param  mode  True enable  False disenable
  '''
  def set_wait_long_time(self,mode=True):
    if mode == True:
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG0_ADDR, self.CONFIG_WLONG)
      self.__wlong = 1
    if mode == False:
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG0_ADDR, self.CONFIG_NO_WLONG)
      self.__wlong = 0

  ''' 
    @brief  Set the ALS gain 
    @param  gain  the value of gain(range: 0x00 -0x03)
  '''
  def set_als_gain(self,gain):
    gain = gain & 0xFF
    self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG1_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG1_ADDR)|gain)

  ''' 
    @brief get channel 0 value
    @return  the z data
  '''
  def get_z_data(self):
    vlaue = self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CH0DATAL_ADDR)
    data = vlaue | (self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CH0DATAH_ADDR)<<8)
    return data 

  ''' 
    @brief get channel 1 value
    @return  the y data
  '''
  def get_y_data(self):
    value = self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CH1DATAL_ADDR)
    value = value | (self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CH1DATAH_ADDR)<<8)
    return value 

  ''' 
    @brief get channel 2 value
    @return  the IR1 data
  '''
  def get_ir1_data(self):
    value = self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CH2DATAL_ADDR)
    value = value | (self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CH2DATAH_ADDR)<<8)
    return value 
    
  ''' 
    @brief get channel 3 value
    @return  the X data
  '''
  def get_x_data(self):
    value = self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CH3DATAL_ADDR)
    value = value | (self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CH3DATAH_ADDR)<<8)
    return value 

  ''' 
    @brief get channel 3 value
    @return  the IR2 data
  '''
  def get_ir2_data(self):
    self.__set_ir2_channel(True)
    if (self.__wlong):
      delaytime = ((self.__atime+1)*2.78 + (self.__wtime+1)*33.4)/1000
    else:
      delaytime =((self.__atime+1)*2.78 + (self.__wtime+1)*2.78)/1000
    time.sleep(delaytime)
    value = self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CH3DATAL_ADDR)
    value = value | (self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CH3DATAH_ADDR)<<8)
    self.__set_ir2_channel(False)
    time.sleep(delaytime)
    return value 

  ''' 
    @brief  Set the ALS  128x gain 
    @param  mode  True enable  False disenable
  '''
  def set_als_high_gain(self,mode=True):
    if mode == True:
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG2_ADDR, self.CFG2_HIGH_GAIN_EN)
    if mode == False:
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG2_ADDR, self.CFG2_HIGH_GAIN_DISEN)

  '''
    @brief  If this bit is set, all flag bits in the STATUS register will be reset whenever the STATUS register is read over I2C. 
    @param  mode  True enable  False disenable
  '''
  def set_int_read_clear(self,mode=True):
    if mode == True:
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG3_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG3_ADDR)|self.CFG3_INT_READ_CLEAR_EN)
    if mode == False:
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG3_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG3_ADDR)|self.CFG3_INT_READ_CLEAR_DISEN)

  '''
    @brief  Config the function of 'sleep after interruption'
    @param  mode  True enable  False disenable
  '''
  def set_sleep_after_interrupt(self,mode=True):
    if mode == True:
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG3_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG3_ADDR)|self.CFG3_SAI_EN)
    if mode == False:
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG3_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG3_ADDR)|self.CFG3_SAI_DISEN)

  '''
    @brief  set aotuzero mode
    @param  mode  0,Always start at zero when searching the best offset value  1,Always start at the previous (offset_c) with the auto-zero mechanism
  '''
  def set_auto_zero_mode(self,mode=0):
    if(mode==1):
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_AZCONFIG_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_AZCONFIG_ADDR)|self.AZ_MODE_1)
    if(mode==0):
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_AZCONFIG_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_AZCONFIG_ADDR)&self.AZ_MODE_0)

  ''' 
    @brief  set autozero automatically every nth ALS iteration)
    @param  iteration_type  0,never  7F,only at first ALS cycle  n, every nth time
  '''
  def set_auto_zero_nth_iteration(self,iteration_type):
    iteration_type = iteration_type & 0x7F
    self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_AZCONFIG_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_AZCONFIG_ADDR)|iteration_type)

  '''
    @brief  Config the ambient light sensing interruption
    @param  mode  True enable  False disenable
  '''
  def set_als_interrupt(self,mode=True):
    self.set_int_read_clear(True);
    if(mode==True):
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_INTENAB_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_INTENAB_ADDR)|self.ENABLEREG_ALS_INT_EN)
    if(mode==False):
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_INTENAB_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR)&self.ENABLEREG_ALS_INT_DISEN)

  '''
    @brief  Config the ALS saturation interription
    @param  mode  True enable  False disenable
  '''
  def set_als_saturation_interrupt(self,mode=True):
    self.set_int_read_clear(True);
    if(mode==True):
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_INTENAB_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_INTENAB_ADDR)|self.ALS_SATURATION_INTERRUPT_EN)
    if(mode==False):
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_INTENAB_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_INTENAB_ADDR)&self.ALS_SATURATION_INTERRUPT_DISEN)

  '''
    @brief  Get the status of the device
  '''
  def get_device_status(self):
    self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_STATUS_ADDR)

  '''
    @brief  Access to IR channel; allows mapping of IR channel on channel 3.
    @param  mode  True enable  False disenable
  '''
  def __set_ir2_channel(self,mode=True):
    if mode == True:
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG1_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG1_ADDR)|self.CFG1_IR2_EN)
    if mode == False:
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG1_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_CFG1_ADDR)&self.CFG1_IR2_DISEN)

  '''
    @brief  Activating the internal oscillator to permit the timers and ADC channels to operate ,and activing the ALS function
  '''
  def __set_power_als_on(self):

    self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR, self.ENABLEREG_ALS_EN|self.ENABLEREG_POWER_ON)

  '''
    @brief  Activating the internal oscillator to permit the timers and ADC channels to operate
    @param  mode  True enable  False disenable
  '''
  def __set_device_power(self,mode=True):
    if(mode==True):
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR)|self.ENABLEREG_POWER_ON)
    if(mode==False):
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR)&self.ENABLEREG_POWER_OFF)

  '''
    @brief  Activating the four-channel ADC
    @param  mode  True enable  False disenable
  '''
  def __set_device_adc(self,mode=True):
    if(mode==True):
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR)|self.ENABLEREG_ALS_EN)
    if(mode==False):
      self.__i2cbus.write_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR, self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_ENABLE_ADDR)&self.ENABLEREG_ALS_DISEN)

  '''
    @brief  get the revision id
    @return  the revision id
  '''
  def __get_revision_id(self):
    return self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_REVID_ADDR)

  '''
    @brief  get the device id
    @return  the device id
  '''
  def __get_device_id(self):
    a = self.__i2cbus.read_byte_data(self.__i2c_addr,self.TCS3430_REG_ID_ADDR)
    return a

  '''
    @brief  Initializes all registers of the device
  '''
  def __soft_reset(self):
    self.set_wait_timer(False)
    self.set_integration_time(0x23)
    self.set_wait_time(0)
    self.set_wait_long_time(False)
    self.set_als_gain(3)
    self.set_als_high_gain(False)
    self.set_int_read_clear(False)
    self.set_sleep_after_interrupt(False)
    self.set_auto_zero_mode(0)
    self.set_auto_zero_nth_iteration(0x7F)
    self.set_als_saturation_interrupt(False)
    self.set_als_interrupt(False)

    
