// telem.h
// Definitions for main spaceport telem module
// Matt Rossouw (04/2023)

#pragma once
#include <stdio.h>
#include <stdint.h>

// ## Function prototypes

// Check system memory, etc.
void chipCheck(void);

// Main loop function
void loop(void);

// Write an entry of data to the buffers
int bufferWrite(BufferEntry b);

// ## Constants
#define BUFFER_SZ 2000 // in-memory buffer size

// Device pins
#define GY91_PIN_SCA 0
#define GY91_PIN_SCL 0
#define GY91_PIN_CSB 0

#define SD_PIN_SCK 0
#define SD_PIN_MOSI 0
#define SD_PIN_MISO 0
#define SD_PIN_CSB 0

// this thing has no CSB for some reason??
#define ENV_PIN_SCL 0
#define ENV_PIN_SCK 0


// GY91 typedefs - gy91 combines an mp9250 IMU with a
//  bmp280 pressure sensor
typedef uint16_t mpu9250_acc_t;
typedef uint16_t mpu9250_gy_t;
typedef uint16_t mpu9250_mag_t;
typedef uint32_t bmp280_bar_t;  // Warning: bmp280 outputs 24 bit values. High order 8 are wasted
typedef uint16_t bmp280_temp_t; // need to make sure this is wide enough

// Si7021
typedef uint16_t si2071_temp_t;
typedef uint16_t si2071_rh_t;   // Relative humidity

// Structure of in-memory buffer
typedef struct bufferEntry {
    mpu9250_acc_t acc_x,acc_y,acc_z;
    mpu9250_gy_t gy_x, gy_y, gy_z;
    mpu9250_mag_t mag_x, mag_y, mag_z;
    bmp280_bar_t pressure;
    bmp280_temp_t obc_temp;
    si2071_rh_t rh;
    si2071_temp_t siTemp;
} BufferEntry;