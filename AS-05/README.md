# 4-Digit Key Press Counter with EEPROM Persistence

## Problem Statement
The objective of this firmware project is to implement a 4-digit key press counter on the **PIC16F877A** microcontroller with non-volatile data persistence. The system must accurately track user increments via a digital keypad, support a long-press reset mechanism, and allow the user to manually "Store" the current count to the internal EEPROM. This stored value must be retrieved upon subsequent power cycles or system resets to ensure continuity.

---

## Features
* **Manual Persistence:** Integrated functionality to save the current counter value to internal EEPROM upon pressing a dedicated "Store" switch.
* **Auto-Recovery:** On system boot or reset, the firmware automatically reads the previously saved value from EEPROM and initializes the counter.
* **Dual-Action Input (DKS1):**
    * **Short Press:** Increments the counter value by 1.
    * **Long Press (2s):** Resets the counter value to `0000`.
* **Multiplexed 4-Digit Display:** Real-time visual feedback on a 4-digit seven-segment display (SSD) using persistence of vision.
* **Hardware Abstraction:** Modular drivers for EEPROM, SSD, and Digital Keypad peripherals.

---

## System Overview
The system architecture utilizes a foreground/background model. The **background** (Timer-driven) task manages the multiplexing of the SSD to maintain a flicker-free display. The **foreground** (Main Loop) manages the application state by polling the digital keypad. It tracks the duration of DKS1 presses to distinguish between an increment and a reset. When DKS2 is triggered, the main loop initiates a write operation to the internal EEPROM, committing the current count to non-volatile memory.

---

## Project Structure
```text
AS-05/
├── main.c                  # Core state machine, long-press logic, and EEPROM synchronization
├── main.h                  # Global definitions, function prototypes, and keypad macros
├── ssd.c                   # SSD driver for digit multiplexing and segment control
├── read_digital_keypad.c   # Non-blocking keypad driver with state change detection
├── out/                    # Build artifacts including the production .hex file
├── cmake/                  # Build system configuration files
└── _build/                 # Intermediate compilation objects and dependency logs
```

---

## Hardware Requirements
* **Microcontroller:** PIC16F877A.
* **Board:** PicGenios (Simulator PICSIMLAB).
* **Input 1 (DKS1):** RB0 for Count/Reset.
* **Input 2 (DKS2):** RB1 for Store.
* **Display:** 4-Digit Common Cathode Seven-Segment Display.
* **Storage:** 256-byte Internal Data EEPROM.

---

## Software Design

### Interrupts / Timer Usage
The system uses a hardware timer to generate periodic interrupts. This ensures that the 4-digit SSD is refreshed at a constant rate, regardless of how long the EEPROM write operation takes or how the user interacts with the switches.

### EEPROM Handling
The firmware leverages the built-in EEPROM of the PIC16F877A.
* **Read Operation:** Executed once during `initConfig()` to retrieve the counter's "last saved state".
* **Write Operation:** Executed only when DKS2 is pressed to minimize wear on the silicon (Manual Persistence).

### Debouncing & Long Press Strategy
Keypad sensing is performed in a non-blocking manner. A counter increments while DKS1 is held. If the button is released before the counter reaches a value corresponding to 2 seconds, an increment occurs. If the counter exceeds the 2-second threshold, the reset logic is triggered.

---

## Working Logic / Flow
1.  **Boot:** Read EEPROM address `0x00` and `0x01` (to support 4 digits/16-bit value) and load into the local `count` variable.
2.  **Idle State:** SSD continuously displays the current `count`.
3.  **Process DKS1:**
    * **Short Press:** `count++`.
    * **2s Hold:** `count = 0`.
4.  **Process DKS2:**
    * **Store Press:** Write high and low bytes of `count` to EEPROM.
5.  **Loop:** Repeat the polling and display refresh.

---

## Edge Cases & Design Considerations
* **EEPROM Endurance:** By requiring a manual "Store" press (DKS2) instead of auto-saving on every increment, the firmware significantly extends the functional life of the EEPROM.
* **Display Stability:** Refreshing is decoupled from the main loop to prevent the display from dimming or flickering during the EEPROM write cycle (which requires several milliseconds per byte).
* **Overflow:** The counter logic ensures that after `9999`, the value wraps back to `0000` to maintain display consistency.

---

## How to Build and Run
1.  **Build:** Use **MPLAB X IDE** with **XC8** or the provided **CMake** build tree.
2.  **Loading:** In **PICSIMLAB**, select the **PicGenios** board and load `out/AS-05/production/default-production.hex`.
3.  **Test Persistence:** * Increment the counter.
    * Press **DKS2** (Store).
    * Reset the simulator; the counter will resume from the stored value instead of `0000`.

---

## Future Improvements
* **Automatic Write-Leveling:** Implement a mechanism to store the count in different EEPROM sectors to distribute wear.
* **Visual Confirmation:** Flash the SSD briefly when a "Store" operation is successfully completed.
* **Power-Fail Detection:** Use the PIC's LVD (Low Voltage Detect) or an external interrupt to auto-save the count only when power loss is imminent.