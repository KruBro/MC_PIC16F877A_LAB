# 4-Digit Key Press Counter with Persistence

## Problem Statement
The objective of this project is to implement a robust 4-digit key press counter using a **PIC16F877A** microcontroller. The system is designed to track user interactions via a digital keypad and provide real-time visual feedback on a multiplexed seven-segment display (SSD). A critical requirement is the implementation of dual-mode input sensing: a short press increments the count, while a **long press (2 seconds)** resets the system to zero.

---

## Features
* **Persistent Counting:** Automatically saves the current count to the internal EEPROM (256 bytes available) to ensure the value is retained after power cycles.
* **Intelligent Input Detection:** Distinguishes between standard click events (increment) and 2-second hold events (reset).
* **Multiplexed 4-Digit SSD:** Efficiently drives a 4-digit display using persistence of vision (POV) to minimize GPIO pin usage.
* **Non-Blocking Debouncing:** Utilizes a state-based sampling strategy to filter mechanical switch noise without stalling the main execution loop.
* **Automatic Wrap-around:** Manages counts from `0000` to `9999` with logical overflow handling.

---

## System Overview
The firmware follows a modular design pattern. A background task, driven by a **Timer0 interrupt**, handles the rapid multiplexing of the 4-digit SSD and the periodic sampling of the keypad. The main application loop (foreground) processes these inputs. When a valid press is detected on **DKS1**, the system updates the count variable, converts it to a 4-digit BCD (Binary Coded Decimal) format for the display driver, and synchronizes the value with the non-volatile EEPROM.

---

## Project Structure
```text
AS-04/
├── main.c                  # State machine for long-press logic and EEPROM sync
├── ssd.c                   # Driver for multiplexed digit selection and segment patterns
├── ssd.h                   # SSD pin definitions and lookup table for 0-9 patterns
├── read_digital_keypad.c   # Input driver with debouncing and state change detection
├── eeprom.c                # Low-level R/W functions for the PIC16F877A data EEPROM
├── timers.c                # Timer0 configuration for the 1ms refresh rate
└── out/                    # Production hex files for flashing the PicGenios board
```

---

## Hardware Requirements
* **Microcontroller:** PIC16F877A.
* **Input:** Digital Keypad Switch 1 (DKS1).
* **Display:** 4-Digit Common Cathode Seven-Segment Display.
* **Clock:** 20MHz External Crystal Oscillator.
* **Platform:** PICSIMLAB Simulator (PicGenios Board).

---

## Software Design

### Interrupts / ISR
The system uses a **Timer0 interrupt** firing every 1ms to 5ms. This ISR is responsible for:
1.  **Multiplexing:** Switching the common pin of each SSD digit sequentially.
2.  **Timing:** Incrementing a global counter used to calculate the 2-second duration for the reset function.

### Long Press Detection
The firmware implements a software timer that starts when DKS1 is first pressed. If the switch is released before 2 seconds, the `count` increments by 1. If the switch remains closed for the full 2-second threshold, the system triggers a reset event, clearing the `count` and updating the EEPROM.

### EEPROM Handling
To preserve memory longevity, the firmware uses a **check-before-write** approach. The count is written to EEPROM address `0x00` only after an increment or reset has occurred, ensuring the value survives power-off states.

---

## Working Logic / Flow
1.  **Startup:** Initialize Ports D (segments), A (digit control), and B (keypad). Load the last count from EEPROM.
2.  **Display Loop:** The ISR continuously refreshes the 4-digit SSD with the current `count`.
3.  **Input Monitoring:**
    * **State 1 (Pressed):** Start a millisecond timer.
    * **State 2 (Released < 2s):** Increment `count`; write to EEPROM.
    * **State 3 (Held >= 2s):** Clear `count` to `0000`; write to EEPROM.
4.  **Formatting:** The `count` is divided into units, tens, hundreds, and thousands for the SSD lookup table.

---

## Edge Cases & Design Considerations
* **Debounce Handling:** The sampling rate in the timer ISR ensures that mechanical bouncing does not cause multiple increments per single press.
* **EEPROM Write Limits:** Writes are restricted to valid state changes to stay well within the 1,000,000-cycle limit of the PIC silicon.
* **Roll-over:** The counter is capped at `9999`. A subsequent increment wraps the count back to `0000`.

---

## How to Build and Run
1.  **Build:** Use the **XC8 Compiler** to compile the source code and generate the `.hex` file.
2.  **Simulator:**
    * Open **PICSIMLAB** and select the **PicGenios** board.
    * Load the generated `default-production.hex`.
3.  **Operation:** Tap **DKS1** to count up. Hold **DKS1** for 2 seconds to see the display reset to `0000`.

---

## Future Improvements
* **Multiple Counter Slots:** Use other keypad switches (DKS2-4) to store and recall different count values from different EEPROM addresses.
* **Alert System:** Activate the onboard buzzer when the counter reaches a user-defined limit.
* **Low Power Storage:** Implement a "Sleep" mode where the MCU only wakes on a change-of-state on the keypad pins to conserve energy.