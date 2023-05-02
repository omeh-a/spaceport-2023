// device.hpp
// Specifies the interface for devices. Device class is inherited
// by all devices. All devices must implement the methods specified

#ifndef DEVICE_H
#define DEVICE_H

class Device {
public:
    virtual std::vector<uint32_t> read() = 0;
    virtual void init() = 0;
    virtual bool checkConnected() = 0;
    virtual bool checkReadings() = 0;
};