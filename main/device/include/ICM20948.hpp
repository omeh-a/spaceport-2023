// ICM20948.hpp
// Header file for the ICM20948 9-axis IMU
// [name] [github handle]
// 05/2023

#ifndef ICM20948_H
#define ICM20948_H

#include "Device.hpp"

class ICM20948 : public Device {
public:
    ICM20948();

    std::vector<imu_reading_t> read();

    // Device methods
    status checkOK() override;
    status init() override;
};

#endif
