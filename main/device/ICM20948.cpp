// ICM20948.cpp
// Implementation for the ICM20948 9-axis IMU
// [name] [github handle]
// 05/2023

#include "ICM20948.hpp"

ICM20948::ICM20948() {
    // Placeholder
}

/**
 * Take a reading from this device.
 * @return A vector of readings from this device of type [TYPE]
*/
std::vector<imu_reading_t> ICM20948::read() {
    // Placeholder
    imu_reading_t placeholder[] = {0};
    std::vector<imu_reading_t> readings = std::vector<imu_reading_t>(placeholder, placeholder + sizeof(imu_reading_t) / sizeof(placeholder[0]));
    return readings;
}

/**
 * Check if the device is working correctly.
 * 
 * Returns either STATUS_OK if normal, STATUS_MISBEHAVING if
 * accessible but readings out of range, or STATUS_FAILED otherwise.
 * 
 * @return status: device status
*/
status ICM20948::checkOK() {
    // Placeholder
    return STATUS_OK;
}

/**
 * Initialise the device.
 * 
 * Performs any setup required inc. calculating
 * magic numbers etc. - returns a STATUS the same way as checkOK. You can probably
 * just call checkOK at the end of this, but obviously there if you fail the setup steps
 * that's worth thinking about too.
 * 
 * @return status: device status
*/
status ICM20948::init() {
    // Placeholder
    return STATUS_OK;
}