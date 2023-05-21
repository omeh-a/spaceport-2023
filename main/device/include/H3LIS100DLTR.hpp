// H3LIS100DLTR.hpp
// Header file for the H3LIS100DLTR accelerometer
// Matt Rossouw (omeh-a)
// 05/2023

#ifndef H3LIS100DLTR_H
#define H3LIS100DLTR_H

#include "Device.hpp"

#define H3LIS100DLTR_I2C_ADDR 0x19

class H3LIS100DLTR : public Device {
public:
    H3LIS100DLTR();

    // Device methods
   
};

#endif