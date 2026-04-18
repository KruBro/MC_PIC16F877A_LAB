# 24-Hour Static Clock on SSD using Timer0

## Problem Statement
The objective of this project is to implement a non-configurable (static) 24-hour digital clock on a multiplexed Seven-Segment Display (SSD) using the **PIC16F877A** microcontroller. The system must initialize at `12:00` upon power-on and maintain accurate timekeeping using a hardware timer. A specific requirement is the implementation of a "seconds" indicator via a blinking decimal point (DP) on the hours-unit digit, toggling at a frequency of 0.5 Hz (every 1000ms).

---

## Features
* **24-Hour Format:** Tracks time from `00:00` to `23:59`.
* **Pre-set Initialization:** Automatically starts at exactly `12:00` after any reset or power cycle.
* **Hardware Time-Base:** Utilizes **Timer0** interrupts to generate a precise 1-second interval, ensuring accuracy independent of main loop execution.
* **Multiplexed Display Drive:** Efficiently manages four SSD digits using persistence of vision to show "HH.MM".
* **Blinking Time Separator:** The decimal point (DP) of the second digit serves as a visual seconds indicator, toggling every 1 second.

---

## System Overview
The firmware architecture is split into a foreground display task and a background timing task. The **Timer0 peripheral** is configured to trigger an interrupt at regular intervals. Within the **Interrupt Service Routine (ISR)**, a counter tracks these overflows to increment the global clock variables (`hours`, `minutes`, `seconds`). The main loop continuously passes the time data to the SSD driver, which multiplexes the four digits to display the current time and the blinking decimal point.

---

## Project Structure
```text
AS-08/
├── main.c              # Application entry point and time increment logic
├── isr.c               # Background timer management and 1-second tick generation
├── timer0.c            # Hardware configuration for the Timer0 peripheral
├── ssd.c               # SSD driver (segment patterns and digit switching)
├── ssd.h               # Digit lookup tables and pin mappings
├── config.h            # Oscillator frequency and MCU configuration bits
└── out/                # Compiled .hex production artifacts
```

---

## Hardware Requirements
* **Microcontroller:** PIC16F877A.
* **Clock Source:** 20MHz External Crystal (HS Oscillator).
* **Display:** 4-Digit Common Cathode Seven-Segment Display.
* **Board:** PicGenios (Simulator PICSIMLAB).

---

## Software Design

### Interrupts / ISR
The `isr.c` module handles the **Timer0 Overflow Interrupt**. Every time the timer overflows, it reloads a preset value to maintain a consistent frequency. A software counter accumulates these interrupts until it reaches the equivalent of one second, at which point it sets a flag for the main loop or directly updates the `seconds` variable.

### Timer Usage
**Timer0** is configured with a 1:256 prescaler. Given the 20MHz clock, the instruction cycle is 5MHz. The timer parameters are calculated to produce a 1ms or 5ms base interrupt, which is then scaled in software to achieve the 1000ms (1s) required for the clock increment and the 0.5 Hz DP blink.

### Decimal Point (DP) Logic
The decimal point on the second digit (one's place of hours) is toggled by modifying the segment bitmask before sending it to the SSD. When the `seconds` value is even, the DP bit is enabled; when odd, it is disabled, resulting in the required 0.5 Hz blink.

---

## Working Logic / Flow
1.  **Boot:** Initialize `hours = 12`, `minutes = 0`, `seconds = 0`.
2.  **Initialization:** Configure `PORTD` as output for segments and `PORTA` for digit enable pins. Initialize Timer0 and enable global interrupts.
3.  **Timekeeping (Background):**
    * Every 1000ms: `seconds++`.
    * If `seconds == 60`: `minutes++`, `seconds = 0`.
    * If `minutes == 60`: `hours++`, `minutes = 0`.
    * If `hours == 24`: `hours = 0`.
4.  **Display (Foreground):**
    * Decompose `hours` into `HH` and `minutes` into `MM`.
    * Apply blinking logic to the DP of the second digit.
    * Continuously refresh all 4 digits on the SSD.

---

## Edge Cases & Design Considerations
* **Precision:** The Timer0 reload value is carefully chosen to minimize time drift over long periods.
* **24-Hour Rollover:** The logic explicitly checks for the transition from `23:59` to `00:00` to prevent invalid hour displays.
* **Non-Blocking Refresh:** The SSD multiplexing is fast enough to ensure the display remains stable and bright while the MCU handles time calculations.

---

## How to Build and Run
1.  **Build:** Compile the project using **MPLAB X** and **XC8** or the provided **CMake** build tree.
2.  **Binary:** Locate `out/AS-08/production/default-production.hex`.
3.  **Simulate:**
    * Launch **PICSIMLAB** and select the **PicGenios** board.
    * Load the `.hex` file.
    * Observe the clock starting at `12.00` and the decimal point blinking every second.

---

## Future Improvements
* **Time Configuration:** Use external switches to allow the user to set the hours and minutes manually.
* **AM/PM Indicator:** Add an option to toggle between 12-hour and 24-hour formats with a dedicated LED for AM/PM status.
* **Buzzer Hourly Chime:** Activate the onboard buzzer for one second every time the hour increments.