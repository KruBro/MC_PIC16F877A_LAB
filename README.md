# Embedded Systems Practice Projects

## Overview

This repository contains a collection of embedded systems practice assignments focused on core microcontroller concepts such as timers, interrupts, PWM, ADC, EEPROM, and display interfacing. These projects are implemented as part of hands-on training to build a strong foundation in low-level firmware development.

---

## Objectives

* Understand and configure microcontroller peripherals
* Develop interrupt-driven embedded applications
* Implement real-time input/output handling
* Work with memory modules such as EEPROM
* Design modular and maintainable embedded code

---

## Features Covered

* GPIO input/output handling
* Timer configuration and usage
* Interrupt Service Routines (ISR)
* Pulse Width Modulation (PWM)
* Analog-to-Digital Conversion (ADC)
* EEPROM read/write operations
* 7-Segment Display (SSD) interfacing
* Key press detection (short press / long press)

---

## Project Structure

Each assignment is organized into separate folders/modules:

```
/project-root
  ├── main.c
  ├── peripherals/
  │     ├── gpio.c / gpio.h
  │     ├── timer.c / timer.h
  │     ├── adc.c / adc.h
  │     ├── pwm.c / pwm.h
  │     ├── eeprom.c / eeprom.h
  │     └── display.c / display.h
  ├── config/
  └── README.md
```

> Note: Structure may vary slightly depending on the assignment.

---

## Hardware Requirements

* Microcontroller (e.g., PIC16F877A or similar)
* 7-Segment Display (SSD)
* Push Buttons / Digital Keypad (DKS)
* Power Supply
* Optional sensors (for ADC-based projects)

---

## Software & Tools

* Embedded C
* MPLAB / XC Compiler (or equivalent toolchain)
* Simulation tools (if applicable)

---

## Design Approach

* Modular programming with separation of concerns
* Use of interrupts for time-critical operations
* Avoidance of blocking delays where possible
* Efficient peripheral configuration using registers

---

## Working Principle

Each assignment focuses on a specific concept. Typical workflow:

1. Initialize peripherals (GPIO, Timer, ADC, etc.)
2. Continuously monitor inputs or rely on interrupts
3. Process input conditions (e.g., key press, sensor value)
4. Update outputs (display, PWM signal, stored values)
5. Handle special conditions (reset, overflow, persistence)

---

## Key Concepts Demonstrated

* Polling vs Interrupt-driven design
* Software debouncing techniques
* Timer-based event handling
* Persistent data storage using EEPROM
* Real-time embedded system behavior

---

## How to Build & Run

1. Open the project in your embedded IDE (e.g., MPLAB)
2. Configure the correct microcontroller
3. Compile the code using the appropriate compiler
4. Flash the firmware to the target hardware
5. Power the board and verify output

---

## Limitations

* Designed for learning purposes (not production-ready)
* Hardware-specific implementations
* Limited optimization in some modules

---

## Future Improvements

* Add RTOS-based task scheduling
* Improve EEPROM wear leveling
* Enhance modular abstraction layers
* Add unit testing for embedded modules
* Integrate multiple peripherals into a single advanced project

---

## Author

Embedded Systems Learner – Focused on building strong firmware fundamentals and transitioning towards real-world embedded development.

