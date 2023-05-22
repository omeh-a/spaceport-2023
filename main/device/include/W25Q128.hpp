// W25Q128.hpp
// Header file for the W25Q128 flash chip
// Matt Rossouw (omeh-a)
// 05/2023

#ifndef W25Q128_H
#define W25Q128_H

#include "Device.hpp"

class W25Q128 : public Device {
public:
    W25Q128();

    // Device methods
    status checkOK() override;
    status init() override;

};

#endif