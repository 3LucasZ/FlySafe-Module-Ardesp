#ifndef LIDARLite_h
#define LIDARLite_h

#define LIDARLITE_ADDR_DEFAULT 0x62
#define LEGACY_I2C

#include <Arduino.h>

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

#endif