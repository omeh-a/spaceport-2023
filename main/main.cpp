// main.cpp
// Main entrypoint for the OBC firmware for Spaceport Cup 2023.
// Matt Rossouw (omeh-a), [name], [name] ...
// 05/2023

// Standard dependencies
#include <inttypes.h>

// Out of tree dependencies
// if you get compile errors on these check your esp-idf install.
// Your IDE will almost definitely be confused by these, but don't worry.
// #include "sdkconfig.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "esp_chip_info.h"
// #include "esp_flash.h"

// Our dependencies
#include "main.hpp"
#include "System.hpp"

// Globals
System dm;

// idf entrypoint
extern "C" void app_main()
{
    printf("Initialising Bluesat Rocket Telemetry system...\n");
    obc_main();
}

// Main function
void obc_main(void) {
    // Switch to appropriate mode
    switch (dm.mode) {
        case MODE_NORMAL:
            mission(false);
            break;
        case MODE_TEST:
            mission(true);
            break;
        case MODE_OFFLOAD:
            offload();
            break;
        // default to diagnostic, in case we somehow end up here
        default:
            diagnostic();
    }
}

/**
 * Main mission loop.
 * 
 * Encapsulates all logic for the spaceport mission.
 * 
 * @param test Whether or not to run in test mode. If true,
 *             all logging output will be outputted on serial.
*/
void mission(bool test) {
    for (;;) {
        // Placeholder
    }
}

/**
 * Offload loop.
 * 
 * Switches the system to act as a USB mass storage device for
 * accessing the data stored on the flash chip.
*/
void offload(void) {
    for (;;) {
        // Placeholder
    }
}

/**
 * Diagnostic loop.
 * 
 * Outputs all sensor output on serial for sanity checking.
*/
void diagnostic(void) {
    for (;;) {
        // Placeholder
    }
}
