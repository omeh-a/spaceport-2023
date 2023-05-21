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
        log_msg(std::string("RTC found. Setting system time to RTC time.\n"));
    } else {
        // Otherwise, leave system time as is.
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        settimeofday(&tv, NULL);
        log_msg(std::string("RTC not found. Falling back to relative time.\n"));
    }
    // NOTE: We settimeofday inside of both branches of the if statement so
    //       our logging system can use the system time.

    

    // If offload mode is enabled, there is no more work to do. Return.
    if (mode == MODE_OFFLOAD) {
        return;
    }

    // Initialise devices
    

}

