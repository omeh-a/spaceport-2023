// BME280.cpp
// Implementation of BME280 barometer.
// [name] [GitHub Username]
// 05/2023

#include "BME280.hpp"

BME280::BME280() {
    // Placeholder
}

/**
 * Take a reading from this device.
 * @return A vector of readings from this device of type [TYPE]
*/
std::vector<baro_reading_t> BME280::read() {
    // Placeholder
    std::vector<baro_reading_t> readings = std::vector<baro_reading_t>({0});
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
status BME280::checkOK() {
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
status BME280::init(idf::I2CMaster i2c) {
    // Placeholder
    
    return STATUS_OK;
}



void BME280::stop()
{

}

void BME280::watchdog_task(void *parameters)
{

}

void BME280::watchdog_callback(TimerHandle_t xtimer)
{

}