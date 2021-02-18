/*!
 * @file DFRobot_TCS3430.cpp
 * @brief Implementation of DFRobot_TCS3430 class
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @SKU SEN0403
 * @licence The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version V1.0
 * @date 2021-01-26
 * @url  https://github.com/DFRobot/DFRobot_TCS3400
 */
#include <DFRobot_TCS3430.h>
DFRobot_TCS3430::DFRobot_TCS3430(TwoWire *pWire):
_pWire(pWire),_deviceAddr(DFRobot_TCS3430_ICC_ADDR)
{
  _atime = 0;
  _wtime = 0;
  _wlong = 0;
  _enableReg.pon = 0;
  _enableReg.aen = 0;
  _enableReg.reservedBit2 = 0;
  _enableReg.wen = 0;
  _enableReg.reservedBit4_7 = 0;
  
  _cfg1Reg.again = 0;
  _cfg1Reg.reservedBit2 = 0;
  _cfg1Reg.amux = 0;
  _cfg1Reg.reservedBit4_7 = 0;
  
  _cfg3Reg.reservedBit0_3 = 0;
  _cfg3Reg.sai = 0;
  _cfg3Reg.reservedBit5_6 = 0;
  _cfg3Reg.intReadClear = 0;
  
  _AZCfgReg.azNTHIteration = 0x7F;
  _AZCfgReg.azMode = 0;
  
  _intEnabReg.reservedBit0_3 = 0;
  _intEnabReg.aien = 0;
  _intEnabReg.reservedBit5_6 =0;
  _intEnabReg.asien = 0;
}

bool DFRobot_TCS3430::begin()
{
  _pWire->begin();
  softReset();
  setPowerALSADC();
  if((getDeviceID()!=TCS3430_ID) || (getRevisionID() != TCS3430_REVISION_ID)){
    disableALSADC();
    powerOFF();
    return false;
  }
  return true;
}

void DFRobot_TCS3430::setIntegrationTime(uint8_t aTime)
{
  _atime = aTime;
  write(eRegATIMEAddr,aTime);
}

void DFRobot_TCS3430::setWaitTime(uint8_t wTime)
{
  _wtime = wTime;
  write(eRegWTIMEAddr,wTime);
}

void DFRobot_TCS3430:: setPowerALSADC()
{
  _enableReg.pon = 1;
  _enableReg.aen = 1;
  write(eRegENABLEAddr,*((uint8_t*)(&_enableReg)));
}

void DFRobot_TCS3430:: powerOFF()
{
  _enableReg.pon = 0;
  write(eRegENABLEAddr,*((uint8_t*)(&_enableReg)));
}

void DFRobot_TCS3430:: disableALSADC()
{
  _enableReg.aen = 0;
  write(eRegENABLEAddr,*((uint8_t*)(&_enableReg)));
}

void DFRobot_TCS3430:: setWaitTimer(bool mode)
{
  if(mode = true){
    _enableReg.wen = 1;
    write(eRegENABLEAddr,*((uint8_t*)(&_enableReg)));
  }
  else{
    _enableReg.wen = 0;
    write(eRegENABLEAddr,*((uint8_t*)(&_enableReg)));
  }
}

void DFRobot_TCS3430:: setInterruptPersistence(uint8_t apers)
{
  write(eRegPERSAddr,apers);
}

void DFRobot_TCS3430:: setWaitLong(bool mode)
{
  if(mode){
    write(eRegCFG0Addr,DFRobot_TCS3430_CONFIG_WLONG);
    _wlong =1;

  }else{
    write(eRegCFG0Addr,DFRobot_TCS3430_CONFIG_NO_WLONG);
    _wlong =0;
  }
}


void DFRobot_TCS3430:: setALSGain(uint8_t aGain)
{
  _cfg1Reg.again=aGain;
  write(eRegCFG1Addr,*((uint8_t*)(&_cfg1Reg)));
}

void DFRobot_TCS3430:: setIR2Channel(bool mode)
{
  if(mode){
    _cfg1Reg.amux=1;
    write(eRegCFG1Addr,*((uint8_t*)(&_cfg1Reg)));
  }else{
    _cfg1Reg.amux=0;
    write(eRegCFG1Addr,*((uint8_t*)(&_cfg1Reg)));
  }
}


uint8_t DFRobot_TCS3430:: getRevisionID()
{
  return uint8_t(read(eRegREVIDAddr,1));
}

uint8_t DFRobot_TCS3430:: getDeviceID()
{
  return uint8_t(read(eRegIDAddr,1));
}

uint8_t DFRobot_TCS3430:: getDeviceStatus()
{
  return uint8_t(read(eRegSTATUSAddr,1));
}

uint16_t DFRobot_TCS3430:: getZData()
{
  return read(eRegCH0DATALAddr,TWO_BYTE);
}

uint16_t DFRobot_TCS3430:: getYData()
{
  return DFRobot_TCS3430:: read(eRegCH1DATALAddr,TWO_BYTE);
}

uint16_t DFRobot_TCS3430:: getIR1Data()
{
  return read(eRegCH2DATALAddr,TWO_BYTE);
}

uint16_t DFRobot_TCS3430:: getXData()
{
  return read(eRegCH3DATALAddr,TWO_BYTE);
}

uint16_t DFRobot_TCS3430:: getIR2Data()
{
  disableALSADC();
  setIR2Channel(true);
  _enableReg.aen = 1;
  write(eRegENABLEAddr,*((uint8_t*)(&_enableReg)));
  uint16_t delayTime = 0;
  if(_wlong){
    delayTime = (_atime+1)*2.78 + (_wtime+1)*33.4;
  }else{
    delayTime = (_atime+1)*2.78 + (_wtime+1)*2.78; 
  }
  delay(delayTime);
  uint16_t value = read(eRegCH3DATALAddr,TWO_BYTE);
  disableALSADC();
  setIR2Channel(false);
  _enableReg.aen = 1;
  write(eRegENABLEAddr,*((uint8_t*)(&_enableReg)));
  delay(delayTime);
  return value;
}

void DFRobot_TCS3430:: setHighGAIN(bool mode)
{
  if (mode){
    write(eRegCFG2Addr,DFRobot_TCS3430_HGAIN_ENABLE);
  }else{
    write(eRegCFG2Addr,DFRobot_TCS3430_HGAIN_DISABLE);
  }
}

void DFRobot_TCS3430:: setIntReadClear(bool mode)
{
  if (mode){
    _cfg3Reg.intReadClear = 1;
    write(eRegCFG3Addr,*((uint8_t*)(&_cfg3Reg)));
  }else{
    _cfg3Reg.intReadClear = 0;
    write(eRegCFG3Addr,*((uint8_t*)(&_cfg3Reg)));
  }
}

void DFRobot_TCS3430:: setSleepAfterInterrupt(bool mode )
{

  if (mode){
    _cfg3Reg.sai = 1;
    write(eRegCFG3Addr,*((uint8_t*)(&_cfg3Reg)));
  }else{
    _cfg3Reg.sai = 0;
    write(eRegCFG3Addr,*((uint8_t*)(&_cfg3Reg)));
  }
}

void DFRobot_TCS3430:: setAutoZeroMode(uint8_t mode)
{
  if(mode == 0){
    _AZCfgReg.azMode = 0;
  }
  if(mode == 1){
    _AZCfgReg.azMode = 1;
  }
  write(eRegAZCONFIGAddr,*((uint8_t*)(&_AZCfgReg)));
}

void DFRobot_TCS3430:: setAutoZeroNTHIteration(uint8_t value)
{
  _AZCfgReg.azNTHIteration = value &0x7F;
  write(eRegAZCONFIGAddr,*((uint8_t*)(&_AZCfgReg)));
}

void DFRobot_TCS3430:: setALSSaturationInterrupt(bool mode )
{
  setIntReadClear(true);
  if(mode){
    _intEnabReg.asien = 1;
    write(eRegINTENABAddr,*((uint8_t*)(&_intEnabReg)));
  }else{
    _intEnabReg.asien = 0;
    write(eRegINTENABAddr,*((uint8_t*)(&_intEnabReg)));
  }
}

void DFRobot_TCS3430:: setALSInterrupt(bool mode )
{
  setIntReadClear(true);
  if(mode){
    _intEnabReg.aien = 1;
    write(eRegINTENABAddr,*((uint8_t*)(&_intEnabReg)));
  }else{
    _intEnabReg.aien = 0;
    write(eRegINTENABAddr,*((uint8_t*)(&_intEnabReg)));
  }
}


void DFRobot_TCS3430:: setCH0IntThreshold(uint16_t thresholdL,uint16_t thresholdH)
{
  uint8_t ailtl = thresholdL&0x00FF;
  uint8_t ailth = (thresholdL&0xFF00)>>8;
  uint8_t aihtl = thresholdH&0x00FF;
  uint8_t aihth = (thresholdH&0xFF00)>>8;
  write(eRegAILTLAddr,ailtl);
  write(eRegAILTHAddr,ailth);
  write(eRegAIHTLAddr,aihtl);
  write(eRegAIHTHAddr,aihth);
}

void DFRobot_TCS3430:: softReset()
{
  setWaitTimer(false);
  setIntegrationTime(0x23);
  setWaitTime(0);
  setWaitLong(false);
  setALSGain(3);
  setHighGAIN(false);
  setIntReadClear(false);
  setSleepAfterInterrupt(false);
  setAutoZeroMode(0);
  setAutoZeroNTHIteration(0x7f);
  setALSInterrupt(false);
  setALSSaturationInterrupt(false);
}

void DFRobot_TCS3430:: write(uint8_t regAddr,uint8_t value)
{
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(regAddr);
  _pWire->write(value);
  _pWire->endTransmission();
}

uint16_t DFRobot_TCS3430:: read(uint8_t regAddr,uint8_t readNum)
{
  uint16_t value=0;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(regAddr);
  _pWire->endTransmission();
  _pWire->requestFrom(_deviceAddr, readNum);
  if(readNum==1){
    value = _pWire->read();
  }else if(readNum == 2){
    value = _pWire->read();
    value |= _pWire->read()<<8;
  }
  return value;
}
