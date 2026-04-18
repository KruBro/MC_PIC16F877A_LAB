# LED Tunnel Pattern Controller

## Problem Statement
The goal of this project is to implement a high-speed LED animation sequence, specifically a "tunnel" or "filling" effect, using an 8-bit microcontroller. The system aims to manipulate a bank of LEDs connected to a single GPIO port to create a fluid, bi-directional visual pattern through precise bitwise shifting and non-blocking timing loops.

---

## Features
* **Bi-Directional Animation:** Sequences through four distinct phases: filling left-to-right, clearing left-to-right, filling right-to-left, and clearing right-to-left.
* **Bitwise Port Manipulation:** Uses efficient logical shifts and masking to control 8 LEDs simultaneously via PORTD.
* **Software-Based Timing:** Implements a non-blocking delay counter to manage animation speed without halting the CPU.
* **Automatic Reset:** The sequence continuously loops, resetting all displays to an idle state before restarting the animation.

---

## System Overview
The system operates as a finite state machine based on a cycle of 32 steps. The microcontroller initializes PORTD as a digital output and then enters a super-loop. Within this loop, a software counter increments until it reaches a predefined threshold, at which point it triggers a "frame update". During each update, the current value of PORTD is shifted and modified based on the current step index (`i`), creating the visual effect of a moving light tunnel.

---

## Project Structure
```text
AS-01/
├── main.c              # Core firmware logic containing the animation state machine and GPIO init
├── README.md           # Documentation of project structure and build paths
├── out/                # Directory containing final build artifacts (.hex, .elf)
├── cmake/              # Build system configuration files
└── _build/             # Temporary CMake build tree files
```

---

## Hardware Requirements
* **Microcontroller:** PIC16F877A.
* **Clock Source:** 20MHz High-Speed (HS) External Crystal.
* **Peripherals:** * **PORTD:** Connected to an 8-LED Bar Graph or individual LEDs.
* **Simulator:** PICSIMLAB with PicGenios board.

---

## Software Design

### Timer Usage
The project utilizes a **Software Delay Loop** rather than a hardware timer peripheral. An `unsigned long int` variable (`delay`) is incremented every clock cycle. When it reaches `50000`, the animation advances one step. This allows the main loop to remain responsive for other potential tasks compared to a blocking `__delay_ms()` call.

### Working Logic / Flow
1.  **Initialization:** `TRISD` is set to `0x00` to configure all 8 pins of Port D as outputs.
2.  **Phase 1 (i < 8):** Shifts PORTD left and injects a `1` at the LSB, filling the LEDs from right to left.
3.  **Phase 2 (i < 16):** Shifts PORTD left and injects a `0`, clearing the LEDs from right to left.
4.  **Phase 3 (i < 24):** Shifts PORTD right and injects a `1` at the MSB (`0x80`), filling the LEDs from left to right.
5.  **Phase 4 (i < 32):** Shifts PORTD right and injects a `0`, clearing the LEDs from left to right.
6.  **Reset:** Once `i` reaches 32, the index is zeroed and `PORTD` is cleared to restart the cycle.

---

## Edge Cases & Design Considerations
* **Overflow Conditions:** The `delay` variable is an `unsigned long int` to ensure it can reach the threshold of `50000` without overflowing prematurely.
* **Port Initialization:** PORTD is explicitly cleared at startup to ensure a known "All-OFF" state.
* **Animation Smoothness:** The threshold of `50000` is calibrated for a 20MHz clock frequency to provide a persistence-of-vision friendly transition speed.

---

## How to Build and Run
1.  **Compiler:** Use Microchip **XC8** compiler.
2.  **Build System:** The project is configured for **CMake**.
    * Navigate to the project root.
    * Run `cmake --build _build` to generate the `default.hex` file in the `out/` folder.
3.  **Flashing:**
    * Open **PICSIMLAB**.
    * Load the `PIC16F877A` on the `PicGenios` board.
    * Load `out/AS-01/default.hex` into the simulator.

---

## Future Improvements
* **Hardware Timer:** Replace the software delay loop with a Timer0 or Timer1 interrupt to achieve more precise timing and lower CPU utilization.
* **Variable Speed:** Integrate a potentiometer with the ADC (Analog-to-Digital Converter) to allow user-controlled animation speed.
* **Pattern Selection:** Use external switches to toggle between different animation patterns (e.g., bouncing ball, strobe, or breathing effect).