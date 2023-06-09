// System.hpp
// System manager header files.
// Matt Rossouw (omeh-a)
// 05/2023

#ifndef SYSTEM_H
#define SYSTEM_H

// Standard dependencies
#include <stdint.h>
#include <iostream>
#include <vector>
#include <sys/time.h>
#include <memory>

// esp-idf dependencies
#include "driver/gpio.h"
#include <system_cxx.hpp>

#include <semaphore>

// Our dependencies
#include "types.hpp"
#include "DS3231.hpp"
#include "W25Q128.hpp"
#include "H3LIS100DLTR.hpp"
#include "BME280.hpp"
#include "ICM20948.hpp"

// ### Pins for system control ###

#define PIN_OFFLOAD (gpio_num_t) 2
#define PIN_TESTMODE (gpio_num_t) 3

// TODO: check these
#define PIN_SCL idf::SCL_GPIO(22)
#define PIN_SDA idf::SDA_GPIO(21)

// ### enums ###

enum system_mode {
    MODE_NORMAL,
    MODE_OFFLOAD,
    MODE_TEST,
    MODE_DIAGNOSTIC,
};


// ### Class prototype ### 
class System {
public:
    system_mode mode;

    // Default constructor
    System();

    // Readings
    std::vector<accel_reading_t> accelread(void);
    std::vector<imu_reading_t> imuread(void);
    std::vector<baro_reading_t> baroread(void);
    rtc_reading_t rtcread(void);

    // ioctl
    int flash_flush(void);
    void log_init(void);
    void log_msg(std::string msg, log_type type);
    void offload(void);
    void i2c_init(void);
    void sensor_init(void);
    void sensor_update(void); // block until all sensors have data

private:
    // Private variables
    flash_mode flashmode;

    // Devices
    DS3231 rtc;
    W25Q128 flash;
    H3LIS100DLTR acc0;
    H3LIS100DLTR acc1;
    BME280 baro0;
    BME280 baro1;
    ICM20948 imu0;
    ICM20948 imu1;

    std::shared_ptr<idf::I2CMaster> i2c;

    // Private methods
    void log_internal(std::string msg, log_type type);

    // Startup checks
    bool check_uart(void);
    bool check_power(void);
    bool check_payload(void);

    // Interrupt handler for I2C devices
    static void interrupt_handler(void *param);
    static std::binary_semaphore data_ready;
};

#endif
