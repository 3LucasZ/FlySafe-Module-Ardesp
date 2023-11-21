/*------------------------------------------------------------------------------

  LIDARLite Arduino Library
  LIDARLite.h

  This library provides quick access to all the basic functions of LIDAR-Lite
  via the Arduino interface. Additionally, it can provide a user of any
  platform with a template for their own application code.

  Copyright (c) 2016 Garmin Ltd. or its subsidiaries.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

------------------------------------------------------------------------------*/
#ifndef LIDARLite_h
#define LIDARLite_h

#define LIDARLITE_ADDR_DEFAULT 0x62
typedef bitset<8> byte;

void begin(int configuration, bool fasti2c, char lidarliteAddress); // 0, false, ADDR_DEFAULT
void configure(int configuration, char lidarliteAddress); // 0, ADDR_DEFAULT
void setI2Caddr(char newAddress, char disableDefault, char lidarliteAddress); // _, _, ADDR_DEFAULT
void reset(char lidarliteAddress); // ADDR_DEFAULT
int distance(bool biasCorrection, char lidarliteAddress); // true, ADDR_DEFAULT
void write(char myAddress, char myValue, char lidarliteAddress); // _, _, ADDR_DEFAULT
void read(char myAddress, int numOfBytes, unsigned char arrayToSave[2], bool monitorBusyFlag, char lidarliteAddress); // _, _, _, _
void correlationRecordToSerial(char separator, int numberOfReadings, char lidarliteAddress); // '\n', 256, ADDR_DEFAULT


#endif