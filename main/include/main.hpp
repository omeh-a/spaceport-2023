// telem.h
// Definitions for main spaceport telem module
// Matt Rossouw (04/2023)

#pragma once
#include <stdio.h>
#include <stdint.h>

// ## Function prototypes

// Check system memory, etc.
void chipCheck(void);

// Main function
void obc_main(void);

// Device pins
#define I2C0_SDA 21
#define I2C0_SCL 22
#define I2C1_SDA 23
#define I2C1_SCL 24
#define VSPI_MISO 25
#define VSPI_MOSI 26
#define VSPI_CLK 27
#define PAYLOAD_CS 28
