// DeviceManager.cpp
// Manages all device accesses and IO in a fault-resilient way.
// Failed devices are automatically brought offline and regularly
// retested. Active devices have their readings checked regularly.
// Matt Rossouw (omeh-a)
// 05/2023

#include "DeviceManager.hpp"
