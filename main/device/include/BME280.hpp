// BME280.hpp
// Header file for the BME280 pressure sensor
// Matt Rossouw (omeh-a)
// 05/2023

#ifndef BME280_H
#define BME280_H

#include "Device.hpp"


class BME280 : public Device {
public:
    BME280();

    // Device methods
    std::vector<baro_reading_t> read();
    status checkOK() override;
    status init(idf::I2CMaster);

    void stop() override;

protected: 
    void watchdog_task(void *parameters) override;
    void watchdog_callback(TimerHandle_t xtimer) override;

private:
    std::shared_ptr<idf::I2CAddress> addr;
    std::shared_ptr<idf::I2CMaster> i2c;
};
#endif