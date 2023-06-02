// BME280.cpp
// Implementation of BME280 barometer.
// [name] [GitHub Username]
// 05/2023

#include "BME280.hpp"
#include "i2c_cxx.hpp"

BME280::BME280() {
    // start at 0;
    _i2c_address = 0;
    _t_fine = 0;
    _temperature = 0;
    _pressure = 0;
    _humidity = 0;
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

/* begin takes in i2c address */
uint8_t BME280::begin(uint8_t i2cAddress) {
    _i2c_address = i2cAddress;
    if (readId()== BME280_ID) {
        clearCalibrationData();
        // will need to read data 
        // 
        return 0;
    }
    return (uint8_t)-1;
}

/*
    busWrite determines which interface to write to and chooses between I2C communication or spi
    communication.
    This function takes in 3 arguments which include p_data 
*/
void BME280::busWrite(uint8_t *p_data, uint8_t data_size, uint8_t repeated_start) {
    if (_i2c_address == BME280_I2C_ADDRESS1 || _i2c_address == BME280_I2C_ADDRESS2) {
        // yay! i2c worked :) 
        i2cWrite(_i2c_address, p_data, data_size, repeated_start);
    } else {
        // most likely wont use as we focus on SPI
        //This operation clears the most significant bit (MSB) of the first element
        p_data[0] &= 0x7f;
        spiWrite(p_data, data_size); 
    }
}

/* read ID returns the Register */
uint8_t BME280::readId(void)
{
    return readUint8(BME280_ID_REGISTER);
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
    // i2cRead(BME280_I2C_ADDRESS1, BME280_ID, &chip_ID, 1);
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