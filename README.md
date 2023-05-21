# spaceport-2023
OBC for our payload for Spaceport Cup 2023, targeting an ESP32-WROOM on our custom OBC board.

[See our Confluence page here for the software design, electrical bill of materials and list of datasheets](https://bluesat.atlassian.net/wiki/spaces/SP/pages/1998127146/Rocket+OBC+V2)

## Dependencies:
* [ESP-IDF CXX](https://github.com/espressif/esp-idf-cxx) -> Make sure you add it as a managed component to your `idf.py` from the directory where you wish to build this project!

## System overview
Payload:
* Zero G 3D DLP resin printer based on our own design with a TI DLPDLCR2000EVM.
* To monitor: resin temperature, resin pressure, microcontroller activity.
* Triggers at start of microgravity -> approximately 30 seconds of microgravity to print in. 

Telemetry:
* 9 Axis IMUs - ICM 20948. Double redundant
* High-range accelerometers - HELIS100DLTR. Double redundant
* Barometer - BME280. Double redundant
* DS3231 RTC module
* Thermocouples
* Battery voltage

Other peripherals:
* ESP32-WROOM
* RP2040 for USB/UART bridge and I2C IO expansion
* W25Q128 flash - one for primary storage and one as buffer for RP2040

The system needs to sleep on the launchpad (where it will sit for at least an hour) and wake upon movement. Telemetry is collected at low speed until launch, where it is collected at max speed until zero G. after this time, telemetry is slowed and the payload activates and is monitored.

## Project structure

The entire project runs on an ESP32 which interfaces with another RP2040 onboard the payload. The payload is interfaced over SPI through the main rocket bus.

## Git Hygiene guide

For this project we will be using standard software engineering principles for our version control.

### Branches and forks

The most important of these is to **make sure to make a fresh pull request for every new feature**. If you want to work on the main repo, this also means a new branch for every feature. If you are using forks, you can branch as you please.

In this case a "feature" is any atomic piece of work you might be contributing, i.e. small enough that you are the only one likely to be working on it. For example, if you are working in /hardware you might implement the module to translate celestial coordinates to motor positions as a feature.

In the case that you are working on a bigger part with another person (or people) you can make a branch with sub-branches for each feature.

### Code review and pull requests

**Never commit directly to main**. The only exception to this is for making administrative changes like editing the readme, .gitignore, .codeowners and so on.
Whenever you finish a feature on a branch like described above, you should submit a **pull request** to get it merged back into a parent branch. Pull requests are also known as "merge requests" on GitLab and some other services (far clearer name frankly) because they basically give you a chance to write up what you've done and documents all the changes you are going to make. It also lets you safely specify how you are going to handle any conflicts between your branch and the parent.

Once you have made your pull request you should ideally get somebody else who didn't contribute to do a **code review** for you. This is mostly important on larger features or things where a lot can go wrong. While this project doesn't have critical stakes or a deployment to risk, it's a very important habit and will often catch a lot of mistakes that are very hard to find on your own (especially when they are errors in design rather than in code).

## Programming style and toolchain

### C / C++ / Rust

For C-based languages we will use the Google Style guide <https://google.github.io/styleguide/cppguide.html>.
#### Microcontrollers

The OBC is based on an ESP32-mini. 


