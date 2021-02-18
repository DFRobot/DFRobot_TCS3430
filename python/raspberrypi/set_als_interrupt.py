""" file set_atime_wtime_gain.py
  # @brief Turn on the ambient light sense interrupt function to obtain the ambient light data within the specified range
  # @n The experimental phenomena：The serial port will output a warning if the optical data exceeds the threshold
  # @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  # @licence     The MIT License (MIT)
  # @author      [yangfeng]<feng.yang@dfrobot.com> 
  # @version  V1.0
  # @date  2021-01-26
  # @get from https://www.dfrobot.com
  # @url https://github.com/DFRobot/DFRobot_TCS3430
"""
from DFRobot_TCS3430 import DFRobot_TCS3430
import time
import RPi.GPIO as GPIO

def int_callback(channel):
  print ('WARNING: The data obtained exceeds the threshold')
  TCS3430.get_device_status()
  
TCS3430 = DFRobot_TCS3430(bus = 1)
GPIO.setwarnings(False)
# Use GPIO port to monitor sensor interrupt
gpio_int = 7
GPIO.setmode(GPIO.BOARD)
GPIO.setup(gpio_int, GPIO.IN)
GPIO.add_event_detect(gpio_int, GPIO.FALLING, callback=int_callback) 

#Using GPIO port to control LED of sensor
gpio_led = 11
GPIO.setup(gpio_led, GPIO.OUT)
GPIO.output(gpio_led, GPIO.HIGH)

while(TCS3430.begin() == False ):
  print ('Please check that the IIC device is properly connected')

#Configure the sensor's ADC integration time, device waiting time, and gain
#TCS3430.set_wait_timer(mode = True)
#TCS3430.set_wait_long_time(mode = False)

'''
  #By asserting wlong, in register 0x8D the wait time is given in multiples of 33.4ms (12x).
  #----------------------------------------
  #| wtime | Wait Cycles | Wait Time      |
  #----------------------------------------
  #|  0x00 |      1      | 2.78ms/ 33.4ms |
  #----------------------------------------
  #|  0x01 |      2      | 5.56ms/ 66.7ms |
  #----------------------------------------
  #|  ...  |     ...     |      ...       |
  #----------------------------------------
  #|  0x23 |     36      | 100ms/ 1.20s   |
  #----------------------------------------
  #|  ...  |     ...     |       ...      |
  #----------------------------------------
  #|  0xff |     256     |  711ms/ 8.53s  |
  #----------------------------------------
'''
#TCS3430.set_wait_time(wtime = 0x00)

'''
  #Maximum ALS Value=  min [CYCLES * 1024, 65535]
  #---------------------------------------------------------------------
  #| aTime | Integration Cycles | Integration Time | Maximum ALS Value |
  #---------------------------------------------------------------------
  #|  0x00 |         1          |       2.78ms     |        1023       |
  #---------------------------------------------------------------------
  #|  0x01 |         2          |       5.56ms     |        2047       |
  #---------------------------------------------------------------------
  #|  ...  |        ...         |       ...        |        ...        |
  #---------------------------------------------------------------------
  #|  0x11 |         18         |       50ms       |        18431      |
  #---------------------------------------------------------------------
  #|  0x40 |         65         |       181ms      |        65535      |
  #---------------------------------------------------------------------
  #|  ...  |        ...         |       ...        |        ...        |
  #---------------------------------------------------------------------
  #|  0xff |        256         |       711ms      |        65535      |
  #---------------------------------------------------------------------
'''
TCS3430.set_integration_time(atime=0x23)

'''
  #AGAIN: ALS Gain Control. Sets the gain of the ALS DAC.
  #----------------------------------------------------------
  #| Field Value |            ALS GAIN VALUE                |
  #----------------------------------------------------------
  #|     0       |               1X Gain                    |
  #----------------------------------------------------------
  #|     1       |               4X Gain                    |
  #----------------------------------------------------------
  #|     2       |               16X Gain                   |
  #----------------------------------------------------------
  #|     3       |               64X Gain                   |
  #----------------------------------------------------------
'''
TCS3430.set_als_gain(gain=3)
#high_gain =128X Gain
#TCS3430.set_als_high_gain()

# enable als interrupt
TCS3430.set_als_interrupt(mode = True)
TCS3430.get_device_status()
'''
  #                      APERS                              
  #----------------------------------------------------------
  #| Field Value |            Persistence                   |
  #----------------------------------------------------------
  #|     0000    |   Every ALS cycle generates an interrupt |
  #----------------------------------------------------------
  #|     0001    |   Any value outside of threshold range   |
  #----------------------------------------------------------
  #|     0010    |   2 consecutive values out of range      |
  #----------------------------------------------------------
  #|     0011    |   3 consecutive values out of range      |
  #----------------------------------------------------------
  #|     0100    |   5 consecutive values out of range      |
  #----------------------------------------------------------
  #|     0101    |   10 consecutive values out of range     |
  #----------------------------------------------------------
  #|     0110    |   15 consecutive values out of range     |
  #----------------------------------------------------------
  #|     0111    |   20 consecutive values out of range     |
  #----------------------------------------------------------
  #|     1000    |   25 consecutive values out of range     |
  #----------------------------------------------------------
  #|     1001    |   30 consecutive values out of range     |
  #----------------------------------------------------------
  #|     1010    |   35 consecutive values out of range     |
  #----------------------------------------------------------
  #|     1011    |   40 consecutive values out of range     |
  #----------------------------------------------------------
  #|     1100    |   45 consecutive values out of range     |
  #----------------------------------------------------------
  #|     1101    |   50 consecutive values out of range     |
  #----------------------------------------------------------
  #|     1110    |   55 consecutive values out of range     |
  #----------------------------------------------------------
  #|     1111    |   60 consecutive values out of range     |
  #----------------------------------------------------------
'''
TCS3430.set_interrupt_persistence(apers=0x01)

#Set the threshold range(0-65535)
TCS3430.set_interrupt_threshold(ailt=0,aiht=10)
print ('If the light data exceeds the threshold, an interrupt is triggered and a warning is printed.\r\n')

try:
  while True :
    Z = TCS3430.get_z_data()
    X = TCS3430.get_x_data()
    Y = TCS3430.get_y_data()
    IR1 = TCS3430.get_ir1_data()
    IR2 = TCS3430.get_ir2_data()
    print ('X:%d'%X,'Y:%d'%Y,'Z:%d'%Z,'IR1:%d'%IR1,'IR2:%d'%IR2)
    time.sleep(1)
    
except KeyboardInterrupt:
  GPIO.cleanup()    
