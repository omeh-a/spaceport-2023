// DeviceManager.hpp
// Device manager header files.
// Matt Rossouw (omeh-a)
// 05/2023

#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H
#endif

#include <stdint.h>
#include <iostream>
#include <vector>

#include "types.hpp"

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

// ### Function prototypes ###

// init
void dm_initialise();

// Startup checks
bool dm_check_ext_flash(void);
bool dm_check_rtc(void);
redundant_status dm_check_imus(void);
redundant_status dm_check_accs(void);
bool dm_check_uart(void);
bool dm_check_power(void);
bool dm_check_payload(void);

// Readings
uint32_t dm_gettime(void);
std::vector<accel_reading> dm_accelread(void);
std::vector<imu_reading> dm_imuread(void);
rtc_reading dm_rtcread(void);

// ioctl
int dm_flash_flush(void);
bool dm_log_msg(std::string msg);
void dm_offload(void);

