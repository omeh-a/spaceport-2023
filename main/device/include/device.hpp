// device.hpp
// Specifies the interface for devices. Device class is inherited
// by all devices. All devices must implement the methods specified

#ifndef DEVICE_H
#define DEVICE_H
#include <stdint.h>
#include <vector>
#include <iostream>

enum BusType {
    i2c, spi
};

class Device {
public:
    virtual std::vector<uint32_t> read() = 0;
    virtual void init() = 0;
    virtual bool checkReadings() = 0;
    uint8_t whoamiReg;
    uint8_t busAddress;


    bool checkConnected() {
        // Request read on  whoamiReg

    }
};