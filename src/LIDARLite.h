#ifndef LIDARLite_h
#define LIDARLite_h

#define LIDARLITE_ADDR_DEFAULT 0x62
#define LEGACY_I2C

#include <Arduino.h>

// void lidar_begin(int = 0, bool = false, char = LIDARLITE_ADDR_DEFAULT);
// void lidar_configure(int = 0, char = LIDARLITE_ADDR_DEFAULT);
// void lidar_setI2Caddr(char, char, char = LIDARLITE_ADDR_DEFAULT);
// void lidar_reset(char = LIDARLITE_ADDR_DEFAULT);

#ifdef __cplusplus
extern "C" 
{
#endif

void lidar_begin(int configuration, bool fasti2c, char lidarliteAddress);
void lidar_configure(int configuration, char lidarliteAddress);
int lidar_distance(bool biasCorrection, char lidarliteAddress);

#ifdef __cplusplus
}
#endif

// void lidar_write(char, char, char = LIDARLITE_ADDR_DEFAULT);
// void lidar_read(char, int, byte*, bool, char);
// void lidar_correlationRecordToSerial(char = '\n', int = 256, char = LIDARLITE_ADDR_DEFAULT);

#endif