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

// esp-idf dependencies
#include "driver/gpio.h"


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



// ### enums ###
enum redundant_status {
    RSTATUS_BOTH_OK,
    RSTATUS_I2C0_OK,
    RSTATUS_I2C1_OK,
    RSTATUS_FAILED,
};

enum status {
    STATUS_OK,
    STATUS_MISBEHAVING,
    STATUS_FAILED,
};

enum system_mode {
    MODE_NORMAL,
    MODE_OFFLOAD,
    MODE_TEST,
    MODE_DIAGNOSTIC,
};

enum flash_mode {
    FLASH_INTERNAL,
    FLASH_EXTERNAL
};

enum log_type {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL
};

// ### Class prototype ### 
class System {
public:
    system_mode mode;

    // Default constructor
    System();

    // Readings
    std::vector<accel_reading> accelread(void);
    std::vector<imu_reading> imuread(void);
    rtc_reading rtcread(void);

    // ioctl
    int flash_flush(void);
    void log_init(void);
    void log_msg(std::string msg, log_type type);
    void offload(void);
    void i2c_init(void);

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
    

    // Private methods
    void log_internal(std::string msg, log_type type);

    // Startup checks
    redundant_status check_imus(void);
    redundant_status check_accs(void);
    bool check_uart(void);
    bool check_power(void);
    bool check_payload(void);
};

#endif