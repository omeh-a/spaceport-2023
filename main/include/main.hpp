// telem.h
// Definitions for main spaceport telem module
// Matt Rossouw (04/2023)

#pragma once
#include <stdio.h>
#include <stdint.h>

// ## Function prototypes

// Check system memory, etc.
void chipCheck(void);

// Main function
// Note cursed preprocessor directives here to force
// the function to be have C linkage.

#ifdef __cplusplus
extern "C" {
#endif

void obc_main(void);

#ifdef __cplusplus
}
#endif
