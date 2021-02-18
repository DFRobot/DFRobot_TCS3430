""" file set_atime_wtime_gain.py
  # @brief Detection of XYZ tristimulus and infrared data
  # @n The experimental phenomena：The serial port outputs the optical data obtained once a second
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

TCS3430 = DFRobot_TCS3430(bus = 1)
#Using GPIO port to control LED of sensor
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
gpio_led = 11
GPIO.setup(gpio_led, GPIO.OUT)
GPIO.output(gpio_led, GPIO.HIGH)

while(TCS3430.begin() == False ):
  print ('Please check that the IIC device is properly connected')

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
