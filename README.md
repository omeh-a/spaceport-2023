# spaceport-2023
OBC for our payload for Spaceport Cup 2023.

Payload:
* Zero G 3D mSLA printer based on https://github.com/Lite3DP/Lite3DP-S1.
* To monitor: resin temperature, resin pressure, microcontroller activity, pressure baffle movement.
* Triggers at start of microgravity -> approximately 50 seconds of microgravity to print in. 

Telemetry:
* GY91 - IMU based on MPU 9250
* HELIS100DLTR - automotive accelorometer
* Thermocouples
* Battery voltage

The system needs to sleep on the launchpad (where it will sit for at least an hour) and wake upon movement. Telemetry is collected at low speed until launch, where it is collected at max speed until zero G. after this time, telemetry is slowed and the payload activates and is monitored.

## Project structure

The entire project runs on an ESP32 which interfaces with an AVR based microcontroller for running the payload.

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