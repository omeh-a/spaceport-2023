// ESPFlash.cpp
// Functions controlling the ESP32's internal flash.
// [name] [github usernmae]
// 05/2023

#include "ESPFlash.hpp"

ESPFlash::ESPFlash() {
    // Placeholder    
}

// bool ESPFlash::checkOK() {
//     if (esp_flash_get_size(NULL, &flash_size) != ESP_OK)
//     {
//         printf("Get flash size failed");
//         return;
//     }

//     printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
//            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

//     printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());
// }