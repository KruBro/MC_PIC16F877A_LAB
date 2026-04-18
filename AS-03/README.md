# Multiplexed Seven-Segment Display (SSD) Constant Clock

## Problem Statement
The goal of this firmware project is to implement a static visual counter on a multiplexed Seven-Segment Display (SSD). The system aims to demonstrate the fundamental principles of driving multi-digit displays using a single GPIO port for segments and separate control lines for digit enablement. The primary technical challenge is to maintain a steady, flicker-free display of a constant value ("1234") through rapid software-controlled multiplexing.

---

## Features
* **4-Digit Multiplexing:** Utilizes high-speed switching across four digits to simulate a continuous multi-digit output.
* **Persistence of Vision (POV):** Leverages a software-defined delay loop to refresh digits at a frequency that appears stable to the human eye.
* **Port-Based Segment Control:** Drives all eight segments (including the decimal point) through a shared 8-bit output port.
* **Resource Efficiency:** Minimizes GPIO usage by sharing segment lines across all display digits.

---

## System Overview
The firmware initializes the microcontroller's GPIO pins to serve as the display interface. The application operates in a continuous "super-loop" where it cycles through four distinct display states. In each state, the bit pattern for a specific digit is loaded onto the segment port, and the corresponding digit-enable pin is activated. A short temporal delay is inserted between digit transitions to ensure the segments have fully illuminated before the next transition occurs.

---

## Project Structure
```text
AS-03/
├── main.c              # Core application loop and digit-sequencing logic
├── ssd.c               # SSD peripheral driver for port and pin initialization
├── ssd.h               # Hardware abstraction layer: pin mappings and digit constants
├── out/                # Compiled binary artifacts (.hex, .elf) for the PIC16F877A
├── cmake/              # Build system configuration
└── _build/             # Intermediate object files and build logs
```

---

## Hardware Requirements
* **Microcontroller:** PIC16F877A.
* **Clock Source:** 20MHz External Crystal (HS Oscillator).
* **Display:** 4-Digit Common Cathode Seven-Segment Display (connected via PORTD for segments and PORTA for digit control).
* **Simulator:** PICSIMLAB with the PicGenios board profile.

---

## Software Design

### Multiplexing Strategy
The system uses a **Time-Division Multiplexing** approach. Since the PIC16F877A cannot drive all 32 segments (4 digits × 8 segments) simultaneously without excessive pin usage, the segments of all digits are tied in parallel. The firmware enables only one digit at a time in rapid succession.

### Timing and Refresh Rate
A non-interrupt software delay is implemented between each digit update. This delay is critical:
* **Too long:** Causes visible flickering as each digit turns off before the next turns on.
* **Too short:** Results in "ghosting," where remnants of the previous digit appear on the current one.

---

## Working Logic / Flow
1.  **Initialization:** The `init_ssd()` function configures `TRISD` and `TRISA` as output ports.
2.  **Pattern Loading:** The firmware defines a buffer containing the hexadecimal patterns for the digits '1', '2', '3', and '4'.
3.  **The Display Cycle:**
    * **Step 1:** Load pattern for Digit 0 to `PORTD`; Set `RA2` to enable Digit 0.
    * **Step 2:** Wait for a short duration.
    * **Step 3:** Disable `RA2`; Load pattern for Digit 1 to `PORTD`; Set `RA3` to enable Digit 1.
    * **Repeat:** Continue the sequence for Digit 2 (`RA4`) and Digit 3 (`RA5`).
4.  **Looping:** The process repeats indefinitely to maintain the "1234" display.

---

## Edge Cases & Design Considerations
* **Ghosting Prevention:** The firmware ensures that the segment port (`PORTD`) is updated before or simultaneously with the digit-enable pins to prevent data from one digit bleeding into the next.
* **Port Interference:** Since `PORTA` is used for digit control, the `ADCON1` register is configured to ensure pins `RA2-RA5` function as digital outputs rather than analog inputs.
* **Brightness Uniformity:** The identical delay between each digit ensures that all four digits appear to have the same luminosity.

---

## How to Build and Run
1.  **Compiler:** Requires the **Microchip XC8 Compiler**.
2.  **Build Execution:**
    * Use the provided **CMake** configuration or an MPLAB X project.
    * Compile to generate `out/AS-03/production/default-production.hex`.
3.  **Simulation:**
    * Launch **PICSIMLAB**.
    * Select **PicGenios** board and **PIC16F877A** MCU.
    * Load the `.hex` file to see the static "1234" on the SSD.

---

## Future Improvements
* **Interrupt-Driven Refresh:** Move the multiplexing logic into a Timer0 ISR to free up the main loop for other tasks.
* **Dynamic Counting:** Implement a real-time counter that increments at 1-second intervals.
* **Brightness Control:** Implement PWM on the digit-enable pins to allow adjustable display brightness.