// ICM20948.cpp
// Implementation for the ICM20948 9-axis IMU
// [name] [github handle]
// 05/2023

#include "ICM20948.hpp"
#include "i2c_cxx.hpp"
#include "types.hpp"
#include <memory>
#include <sys/_stdint.h>

ICM20948::ICM20948() {
    // Placeholder
}

/**
 * Take a reading from this device.
 * @return A vector of readings from this device of type [TYPE]
*/
std::vector<imu_reading_t> ICM20948::read() {
    // Placeholder

    // imu_reading_t placeholder[] = {0};
    // std::vector<imu_reading_t> readings = std::vector<imu_reading_t>(placeholder, placeholder + sizeof(imu_reading_t) / sizeof(placeholder[0]));

    // the swap is so that the internal measuremnets are earased, and are handed to the caller
    auto readings = std::vector<imu_reading_t>{};
    measurements.swap(readings);

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

#define USER_CTRL 0x03
#define INT_ENABLE 0x10

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
status ICM20948::init(std::shared_ptr<idf::I2CMaster> i2c, bool alt_address) {
    this->addr = std::make_unique<idf::I2CAddress>(BASE_ADDRESS & alt_address);
    this->i2c = i2c;

    // check if device is available
    try {
      this->i2c->sync_read(*this->addr, 0); // send nothing
                                            // should still recieve ACK
    } catch (idf::I2CException& e) {
      // something went wrong with the i2c communication
      return STATUS_FAILED;
    }

    // Setup user settings.
    try {
      // Do a full reset.
      const std::vector<uint8_t> data {USER_CTRL, 0x00};
      this->i2c->sync_write(*this->addr, data);
    } catch (idf::I2CException& e) {
      return STATUS_FAILED;
    }

    // Setup interrupts.
    try {
      // enable the raw data ready interrupt
      const std::vector<uint8_t> data {INT_ENABLE + 3, 0x01};
      this->i2c->sync_write(*this->addr, data);
    } catch (idf::I2CException& e) {
      return STATUS_FAILED;
    }

    return STATUS_OK;
}

#define SENS_START 0x2D // ACCEL_XOUT_H on datasheet
#define SENS_LEN   14   // number of sensor registers

void ICM20948::update() {
    try {
      const std::vector<uint8_t> data {SENS_START};
      auto data_vec = this->i2c->sync_transfer(*this->addr, data, SENS_LEN);

      typedef union {
        imu_reading_t r;
        uint8_t d[sizeof(imu_reading_t)];
      } imu_reading_ser_t;

      // convert byte stream to actual value
      imu_reading_ser_t reading;
      *reading.d = *data_vec.data(); 
      measurements.push_back(reading.r);
      
      // i'm not sure how correct the above is. If the endian-ness matches and
      // if the struct is packed correctly
      // could easily change to the more direct assignment approach.

    } catch (idf::I2CException& e) {
      this->alive = false;
      return;
    }

}

// watchdog stuff

void ICM20948::stop()
{

}

void ICM20948::watchdog_task(void *parameters)
{

}

void ICM20948::watchdog_callback(TimerHandle_t xtimer)
{

}
