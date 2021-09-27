/*!
 * @file setALSInterrupt.ino
 * @brief Turn on the ambient light sense interrupt function to obtain the ambient light data within the specified range
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version  V1.0
 * @date  2021-01-26
 * @get from https://www.dfrobot.com
 * @url  https://github.com/DFRobot/DFRobot_TCS3430
 */
#include <DFRobot_TCS3430.h>


DFRobot_TCS3430 TCS3430;

int LEDpin = 12;
int interruptPin = 2;

volatile int state = 0;

void handleInterrupt(){

  Serial.println("WARNING:The data obtained exceeds the threshold");
  state = 1;
}

void setup() {
  Serial.begin(115200);

  pinMode(interruptPin, INPUT_PULLUP);

  while(!TCS3430.begin()){
    Serial.println("Please check that the IIC device is properly connected");
    delay(1000);
  }

// Configure the sensor's ADC integration time, device waiting time, and gain

  //TCS3430.setWaitTimer(true);
  //TCS3430.setWaitLong(false);
    /*
   * By asserting wlong, in register 0x8D the wait time is given in multiples of 33.4ms (12x).
   * ----------------------------------------
   * | wtime | Wait Cycles | Wait Time      |
   * ----------------------------------------
   * |  0x00 |      1      | 2.78ms/ 33.4ms |
   * ----------------------------------------
   * |  0x01 |      2      | 5.56ms/ 66.7ms |
   * ----------------------------------------
   * |  ...  |     ...     |      ...       |
   * ----------------------------------------
   * |  0x23 |     36      | 100ms/ 1.20s   |
   * ----------------------------------------
   * |  ...  |     ...     |       ...      |
   * ----------------------------------------
   * |  0xff |     256     |  711ms/ 8.53s  |
   * ----------------------------------------
   */
  //TCS3430.setWaitTime(/*wTime=*/0x00);
  /*
   * Maximum ALS Value=  min [CYCLES * 1024, 65535]
   * ---------------------------------------------------------------------
   * | aTime | Integration Cycles | Integration Time | Maximum ALS Value |
   * ---------------------------------------------------------------------
   * |  0x00 |         1          |       2.78ms     |        1023       |
   * ---------------------------------------------------------------------
   * |  0x01 |         2          |       5.56ms     |        2047       |
   * ---------------------------------------------------------------------
   * |  ...  |        ...         |       ...        |        ...        |
   * ---------------------------------------------------------------------
   * |  0x11 |         18         |       50ms       |        18431      |
   * ---------------------------------------------------------------------
   * |  0x40 |         65         |       181ms      |        65535      |
   * ---------------------------------------------------------------------
   * |  ...  |        ...         |       ...        |        ...        |
   * ---------------------------------------------------------------------
   * |  0xff |        256         |       711ms      |        65535      |
   * ---------------------------------------------------------------------
   */
  TCS3430.setIntegrationTime(/*aTime=*/0x23);
  /*
   * AGAIN: ALS Gain Control. Sets the gain of the ALS DAC.
   * ----------------------------------------------------------
   * | Field Value |            ALS GAIN VALUE                |
   * ----------------------------------------------------------
   * |     0       |               1X Gain                    |
   * ----------------------------------------------------------
   * |     1       |               4X Gain                    |
   * ----------------------------------------------------------
   * |     2       |               16X Gain                   |
   * ----------------------------------------------------------
   * |     3       |               64X Gain                   |
   * ----------------------------------------------------------
   */
  TCS3430.setALSGain(/*aGian=*/3);
  //128X high gain
  //TCS3430.setHighGAIN()

/* Turn on the ALS interrupt function of the device */

  //mode = true : enable ALS Interrupt
  TCS3430.setALSInterrupt(/*mode*/true);

  /*
   *                       APERS                              
   * ----------------------------------------------------------
   * | Field Value |            Persistence                   |
   * ----------------------------------------------------------
   * |     0x00    |   Every ALS cycle generates an interrupt |
   * ----------------------------------------------------------
   * |     0x01    |   Any value outside of threshold range   |
   * ----------------------------------------------------------
   * |     0x02    |   2 consecutive values out of range      |
   * ----------------------------------------------------------
   * |     0x03    |   3 consecutive values out of range      |
   * ----------------------------------------------------------
   * |     0x04    |   5 consecutive values out of range      |
   * ----------------------------------------------------------
   * |     0x05    |   10 consecutive values out of range     |
   * ----------------------------------------------------------
   * |     0x06    |   15 consecutive values out of range     |
   * ----------------------------------------------------------
   * |     0x07    |   20 consecutive values out of range     |
   * ----------------------------------------------------------
   * |     0x08    |   25 consecutive values out of range     |
   * ----------------------------------------------------------
   * |     0x09    |   30 consecutive values out of range     |
   * ----------------------------------------------------------
   * |     0x0A    |   35 consecutive values out of range     |
   * ----------------------------------------------------------
   * |     0x0B    |   40 consecutive values out of range     |
   * ----------------------------------------------------------
   * |     0x0C    |   45 consecutive values out of range     |
   * ----------------------------------------------------------
   * |     0x0D    |   50 consecutive values out of range     |
   * ----------------------------------------------------------
   * |     0x0E    |   55 consecutive values out of range     |
   * ----------------------------------------------------------
   * |     0x0F    |   60 consecutive values out of range     |
   * ----------------------------------------------------------
   */
  TCS3430.setInterruptPersistence(/*apers=*/0x05);

  // Set the threshold range(0-65535)
  TCS3430.setCH0IntThreshold(/*thresholdL=*/50,/*thresholdH=*/100);

  Serial.println("If the light data exceeds the threshold, an interrupt is triggered and a warning is printed.");

  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

}
void loop() {
  if (state == 1){
    state =0;
    TCS3430.getDeviceStatus(); 
  }else{
    Serial.println(TCS3430.getZData());
    delay(100);
  }
}
