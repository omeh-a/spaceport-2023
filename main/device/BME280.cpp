// BME280.cpp
// Implementation of BME280 barometer.
// [name] [GitHub Username]
// 05/2023

#include "BME280.hpp"

BME280::BME280() {
    // start at 0;
    _i2c_address = 0;
    // _t_fine = 0;
    temp_t = 0;
    press_t = 0;
    humid_t = 0;
    clearCalibrationData();

}



// clears data
void BME280::clearCalibrationData(void)
{
   // set everything to 0 >:(
   _dig_T1 = 0;
   _dig_T2 = 0;
   _dig_T3 = 0;
   _dig_P1 = 0;
   _dig_P2 = 0;
   _dig_P3 = 0;
   _dig_P4 = 0;
   _dig_P5 = 0;
   _dig_P6 = 0;
   _dig_P7 = 0;
   _dig_P8 = 0;
   _dig_P9 = 0;
   _dig_H1 = 0;
   _dig_H2 = 0;
   _dig_H3 = 0;
   _dig_H4 = 0;
   _dig_H5 = 0;
   _dig_H6 = 0;
}


/**
* Prints everything out from the readings
* For debugging purposes
*/
void printReadings(const std::vector<baro_reading_t>& readings) {
   for (const auto& reading : readings) {
       printf("Temperature: %d °C\n", reading.temp);
       printf("Pressure: %d \n", reading.pressure);
       printf("Humidity: %d \n", reading.humidity);
      
   }
}


/**
 * Take a reading from this device.
 * @return A vector of readings from this device of type [TYPE]
*/
std::vector<baro_reading_t> BME280::read() {
    // Placeholder
    // std::vector<baro_reading_t> readings = std::vector<baro_reading_t>({0});
    // return readings;

    // making the vector
    std::vector<baro_reading_t> readings;
    // reading type
    baro_reading_t reading;
    // want to loop to grab the data of readings
    for (;;) {
        // populating the reading vector
        reading.temp = BME280_TEMPERATURE;
        reading.humidity = BME280_HUMIDITY;
        reading.pressure = BME280_PRESSURE;
        // shoving stuff into vector :)
        readings.push_back(reading);
    }
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
    // creating a chip ID
    uint16_t chip_ID;


    // want to check if the BME280 chip is present
    i2c.read(BME280_I2C_ADDRESS1, BME280_ID, &chip_ID, 1);
    // if chip is not present
    if (chip_ID != BME280_ID ) {
        // not found the bme280 chip :(
        return STATUS_FAILED;
    }

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