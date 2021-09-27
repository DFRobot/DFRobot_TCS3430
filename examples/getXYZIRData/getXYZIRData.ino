/*!
 * @file getXYZIRData.ino
 * @brief Detection of XYZ tristimulus and infrared data
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
void setup() {
  Serial.begin(115200);

  while(!TCS3430.begin()){
    Serial.println("Please check that the IIC device is properly connected");
    delay(1000);
  }
}

void loop() {
  uint16_t XData = TCS3430.getXData();
  uint16_t YData = TCS3430.getYData();
  uint16_t ZData = TCS3430.getZData();
  uint16_t IR1Data = TCS3430.getIR1Data();
  uint16_t IR2Data = TCS3430.getIR2Data();
  String str = "X : " + String(XData) + "    Y : " + String(YData) + "    Z : " +  String(ZData) + "    IR1 : "+String(IR1Data) + "    IR2 : "+String(IR2Data);
  Serial.println(str);
  delay(1000);
}
