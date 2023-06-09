// System.cpp
// Manages all device accesses and IO in a fault-resilient way.
// Failed devices are automatically brought offline and regularly
// retested. Active devices have their readings checked regularly.
// Matt Rossouw (omeh-a)
// 05/2023

#include "System.hpp"

/**
 * Default constructor for the system class.
 * Encaspualtes all initialisation logic. This technically should be
 * a singleton class but I think nobody is going to go crazy with this.
 */
System::System() {
    // Initialise GPIO pins for system control
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL<<PIN_OFFLOAD) | (1ULL<<PIN_TESTMODE);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
    
    // Check jumpers to decide system mode.
    // This line of code is potentially nefarious because I'm not too sure
    // how C++ handles enum types
    mode = (system_mode)(gpio_get_level(PIN_OFFLOAD) | (gpio_get_level(PIN_TESTMODE) << 1));

    // Check if external flash is OK
    if (flash.checkOK()) {
        flashmode = FLASH_EXTERNAL;
        // flash.init(); 
    } else {
        // Switch to internal flash
        flashmode = FLASH_INTERNAL;
    }
    // Initialise logger
    log_init();
    
    // TODO: mount filesystem

    // Check if RTC is connected
    // Timezone is hardcoded to UTC because we don't really care about it.
    struct timeval tv;
    if (rtc.checkOK()) {
        // If OK, set system time to RTC time
        tv = rtc.getTime();
        settimeofday(&tv, NULL);
        log_internal(std::string("RTC found. Setting system time to RTC time.\n"), LOG_INFO);
    } else {
        // Otherwise, leave system time as is.
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        settimeofday(&tv, NULL);
        log_internal(std::string("RTC not found. Falling back to relative time.\n"), LOG_WARNING);
    }
    // NOTE: We settimeofday inside of both branches of the if statement so
    //       our logging system can use the system time.

    log_internal(std::string("Core initialisation complete.\n"), LOG_INFO);
}

/**
 * Initialises the I2c bus for devices to use.
 */
void System::i2c_init() {
    // Placeholder

    i2c = std::make_shared<idf::I2CMaster>(
        idf::I2CNumber::I2C0(), // I2C1() for second bus
        PIN_SCL, // the scl gpio pin
        PIN_SDA, // the sda gpio pin
        idf::Frequency::KHz(40)
    );
}

/**
 * Attempts to initialise all connected sensors.
 * Must be called before attempting to read sensors.
 * 
 * @note System::i2c_init must succeed before calling this.
 */
void System::sensor_init() {
    // Placeholder

    // init both IMUs
    imu0.init(this->i2c, false);
    imu1.init(this->i2c, true);
}

void System::sensor_update() {
    System::data_ready.acquire(); // block until data is ready

    imu0.update();
    imu1.update();
}

/**
 * Attempts to take a reading from each working accelerometer. 
 * 
 * @return std::vector<accel_reading_t> containing readings for each accelerometer
 */
std::vector<accel_reading_t> System::accelread(void) {
    // Placeholder
    return std::vector<accel_reading_t>({0});
}
/**
 * Attempts to take a reading for each working IMU.
 *
 * @return std::vector<imu_reading_t> containing readings for each imu
 */
std::vector<imu_reading_t> System::imuread(void) {
    // Placeholder

    return std::vector<imu_reading_t>({0});
}

/**
 * Attempts to take a reading for each working IMU.
 *
 * @return std::vector<baro_reading_t> containing readings for each barometer
 */
std::vector<baro_reading_t> System::baroread(void) {
    // Placeholder

    return std::vector<baro_reading_t>({0});
}

/**
 * Logs a message to the system log.
 * 
 * Automatically arbitrates between internal and external flash, and
 * will also output to serial if the system is in test mode or 
 * diagnostic mode.
 * 
 * @param msg The message to log.
*/
void System::log_msg(std::string msg, log_type type) {
    // Placeholder
    std::cout << msg;
}

/**
 * Logs a message to the system log. Same as `log_msg` but prepends
 * the source as coming from the System manager.
 * 
 * Automatically arbitrates between internal and external flash, and
 * will also output to serial if the system is in test mode or 
 * diagnostic mode.
 * 
 * @param msg The message to log.
*/
void System::log_internal(std::string msg, log_type type) {
    // Placeholder
    std::cout << "System: " << msg;
}

/**
 * Initialises the system logger.
 * 
 * Generates a new logfile if appropriate on the correct
 * device.
*/
void System::log_init() {
    // Placeholder
    std::cout << "Initialising logger...\n";
}

void System::interrupt_handler(void *param) {
    System::data_ready.release();
}



/**
 * Silently wait until launch is detected.
 * 
 * Launch is detected with a >1G vertical acceleration and a vertical velocity
 * in the appropriate direction. If the IMU is unavailable velocity is discarded.
 * If the high range accelerometer is unavailable the IMU takes over.
 * 
 */
void System::await_launch(void) {
    // Decide on which devices to use.


    uint8_t prev = 0;

    // Sit in loop
    for (;;) {
        auto acc_readings = accelread();
        uint8_t acc_out = 0;
        // Take average of accelerometer read
        for (int i = 0; i < acc_readings.size(); i++) {
            acc_out = (acc_out + acc_readings[i].acc_z) / 2;
        }

        auto imu_readings = imuread();
        // Take average of IMU read
        for (int i = 0; i < imu_readings.size(); i++) {
            // If accelerometer unavailable, overwrite acc reading
            if (acc_readings.size() == 0) {
                acc_out = (acc_out + imu_readings[i].acc_z) / 2;
            }
            out = (out + imu_readings[i].acc_z) / 2;
        }

        // Decide if rate of change sufficient for launch
        // TODO: increase sample size if needed, same as baro
        // Note: converting accel launch threshold to be for 50ms (50ms = 1/20 seconds)
        if (out - prev > (ACCEL_LAUNCH_THRESH/20)) {
            // Launch detected
            return;
        } else {
            prev = acc_out;
        }
    
        // Delay 50ms
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}