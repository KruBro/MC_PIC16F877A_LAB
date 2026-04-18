# Multiple LED Patterns Controller

## Problem Statement
The objective of this firmware project is to design and implement a versatile LED pattern controller for the PIC16F877A microcontroller. The system must allow users to toggle between four distinct visual animations—ranging from directional shifts to sophisticated "breathing" and "ping-pong" effects—using a digital keypad for real-time input. The implementation focuses on non-blocking state management to ensure seamless transitions between patterns and responsive user interaction.

---

## Features
* **Interactive Pattern Switching:** Supports four unique LED animations selectable via a digital keypad.
* **Dynamic PWM Simulation:** Implements a software-based Pulse Width Modulation (PWM) technique to achieve a "breathing" or "dimming" effect on the LED bank.
* **Responsive State Machine:** Decouples keypad sensing from animation logic, allowing instant pattern changes without waiting for a sequence to complete.
* **Edge-Triggered Inputs:** Utilizes a state-based keypad reading strategy to detect new key presses while ignoring continuous holds.
* **Modular Pattern Architecture:** Each animation is encapsulated in a dedicated module, facilitating easy expansion of the visual library.

---

## System Overview
The system is built on a modular firmware architecture where the main loop acts as a supervisor. It continuously polls the digital keypad for input. Based on the detected key (SW1 through SW4), the supervisor updates the global state and invokes the corresponding pattern function. These functions manipulate the 8-bit PORTD register to drive the LED bar graph. The timing for each animation is managed through localized non-blocking software counters, ensuring that the keypad remains scannable at all times.

---

## Project Structure
```text
AS-02/
├── main.c                  # Supervisor logic and pattern selection state machine
├── main.h                  # Global definitions, function prototypes, and keypad macros
├── initconfig.c            # GPIO peripheral configuration for PORTD and PORTB
├── read_digital_keypad.c   # Driver for debounced digital keypad sensing
├── pattern1.c              # Logic for "Left-to-Right" and "Right-to-Left" shifting
├── pattern2.c              # Logic for "Nibble-wise" and "Blinking" sequences
├── pattern3.c              # Logic for "Ping-Pong" and "Caterpillar" effects
└── pattern4.c              # Logic for "Breathing/Dimming" effect using software PWM
```


---

## Hardware Requirements
* **Microcontroller:** PIC16F877A.
* **Clock Source:** 20MHz External Crystal.
* **Display Output:** 8-LED Bar Graph connected to PORTD.
* **Input Interface:** 4-Switch Digital Keypad connected to PORTB (RB0-RB3).
* **Simulator:** PICSIMLAB with the PicGenios board profile.

---

## Software Design

### Keypad Sensing & Debouncing
The system uses a non-blocking `read_digital_keypad` function. It samples the PORTB pins and implements a simple state check: a key press is only registered if the switch was previously in an `IDLE` state and is now `PRESSED`. This prevents multiple triggers from a single physical press and eliminates the need for processor-stalling `delay` loops.

### Software PWM (Breathing Effect)
In `pattern4.c`, the "breathing" effect is achieved by rapidly toggling the LEDs at varying duty cycles. By adjusting the ratio of "ON" time to "OFF" time within a tight loop, the firmware simulates varying brightness levels, creating a smooth fading effect despite the binary nature of digital GPIOs.

### Pattern Control Logic
Each pattern module (e.g., `pattern1.c`) utilizes static local counters to track its own progress. This "state memory" allows the function to be called repeatedly in the main loop, advancing the animation by only one "frame" per call when its internal timer expires.

---

## Working Logic / Flow
1.  **System Init:** PORTD is set as output for LEDs; PORTB is set as input for the keypad.
2.  **Default State:** The system starts with Pattern 1 active.
3.  **Polling Cycle:**
    * The `read_digital_keypad` function checks for a new switch press.
    * If **SW1** is pressed, the state changes to `PATTERN1`.
    * If **SW2** is pressed, it switches to `PATTERN2`, and so on.
4.  **Pattern Execution:** The main loop calls the active pattern function (e.g., `pattern3()`).
5.  **LED Update:** The pattern function calculates the next bit-mask, applies it to PORTD, and returns control to the main loop.

---

## Edge Cases & Design Considerations
* **Input Latency:** By avoiding blocking delays in the pattern functions, the system can switch patterns mid-animation with virtually zero perceived latency.
* **Port Initialization:** `ADCON1` is configured to ensure PORTB and PORTD function as digital I/O rather than analog inputs.
* **Static Variable Persistence:** Internal animation counters are declared as `static` to ensure they retain their values between function calls in the main super-loop.

---

## How to Build and Run
1.  **Setup:** Ensure **MPLAB X IDE** and the **XC8 Compiler** are installed.
2.  **Compilation:**
    * Create a new project for the PIC16F877A.
    * Add all `.c` and `.h` files from the `AS-02` directory.
    * Click `Build Project` to generate the `default.hex` file.
3.  **Simulation:**
    * Open **PICSIMLAB** and select the **PicGenios** board.
    * Load the generated `.hex` file.
    * Use the digital keypad switches to cycle through the four LED patterns.

---

## Future Improvements
* **EEPROM Pattern Memory:** Save the last selected pattern index to EEPROM so the system resumes the same animation after a power cycle.
* **Speed Control:** Dedicate two additional switches to increase or decrease the animation speed dynamically.
* **Interrupt-Driven Keypad:** Transition from polling to an "Interrupt-on-Change" (IOC) method on PORTB to further reduce CPU overhead.