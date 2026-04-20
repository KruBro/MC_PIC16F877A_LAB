# Password-Protected Easter Egg Unlocker

## Problem Statement
The objective of this project is to implement a secure password access system using the **PIC16F877A** microcontroller and a Character LCD (CLCD). The system requires the user to enter a specific 8-field pattern using two digital keys (Key1 and Key2) to unlock a hidden "Easter egg" message. To ensure security, the system enforces a maximum of five attempts; successive failures are penalized with increasingly rapid LED blinking, culminating in a total system lockout after the fifth failed attempt.

---

## Features
* **8-Character Password Validation:** Compares user input against a hardcoded pattern of 8 key presses.
* **Visual Feedback:** * Displays a blinking underscore (`_`) at 0.5Hz to indicate the active input field.
    * Masks password entry with asterisks (`*`) for security.
* **Progressive Failure Penalty:** * On each wrong attempt, an LED blinks at a specific rate.
    * The blink frequency doubles with every subsequent failure.
* **Lockout Mechanism:** After 5 failed attempts, the LED remains constantly ON, and a failure message is displayed, requiring a hardware reset to retry.
* **Secret Message Unlock:** Displays a custom "Embedded message" upon successful pattern entry.

---

## System Overview
The firmware initializes the CLCD in 4-bit mode and configures the digital keypad for input sensing. The main application tracks three primary states: **Input Entry**, **Validation**, and **Failure Handling**. During input, a non-blocking timer logic handles the 0.5Hz cursor blinking. Once 8 keys are pressed, the `mystrcmp` utility compares the entered buffer with the stored password. If they match, the system enters the "Unlocked" state; otherwise, it increments the failure counter and adjusts the LED blinking PWM/delay parameters.

---

## Project Structure
```text
AS-10/
├── main.c                  # Main state machine and password logic
├── digital_keypad.c        # Driver for sensing Key1 and Key2 presses
├── digital_keypad.h        # Key definitions and function prototypes
├── clcd.c                  # Character LCD driver (4-bit mode)
├── clcd.h                  # CLCD commands and pin mapping
├── mystrcmp.c              # Custom string comparison for password validation
├── my_string.h             # Header for custom string utilities
├── config.c                # MCU configuration bits (FOSC, WDTE, etc.)
├── config.h                # System clock and global config header
└── README.md               # Project requirements and documentation
```

---

## Hardware Requirements
* **Microcontroller:** PIC16F877A.
* **Input Interface:** Digital Keypad (using Switch 1 and Switch 2).
* **Display:** 16x2 Character LCD (CLCD).
* **Indicators:** 1x LED (e.g., connected to PORTB or PORTD) for failure signaling.
* **Clock:** 20MHz External Crystal.

---

## Software Design

### Input & Masking Logic
The system maintains a character buffer of size 9 (8 characters + null terminator). For every valid key press detected from `digital_keypad.c`, an asterisk is printed to the current CLCD cursor position, and the actual key identity (Key1 or Key2) is stored in the buffer.

### String Comparison
Instead of standard library functions, the project uses a custom `my_strcmp` implementation found in `mystrcmp.c`. This function iterates through the user buffer and the hardcoded password, returning zero only if every field matches exactly.

### Progressive Blink Rate
A software counter or a hardware timer is used to manage the LED. The delay threshold for toggling the LED is halved (frequency doubled) after each `Validation == Failure` event.
* **Attempt 1 Failure:** $f$ Hz.
* **Attempt 2 Failure:** $2f$ Hz.
* **Attempt 3 Failure:** $4f$ Hz.
* **Attempt 4 Failure:** $8f$ Hz.
* **Attempt 5 Failure:** Constant High (100% Duty).

---

## Working Logic / Flow
1.  **Start:** System displays "Enter Password" on CLCD Line 1.
2.  **Input Phase:** * User presses Key1 or Key2.
    * CLCD shows `*` and shifts the blinking `_` cursor.
3.  **Validation:** * After 8 characters, the system calls `my_strcmp`.
    * **Success:** Display the secret message (e.g., "Access Granted").
    * **Failure:** Increment `attempts`. If `attempts < 5`, clear screen and restart input with faster LED blinking.
4.  **Lockout:** On the 5th failure, display "System Locked" and halt execution with LED ON.

---

## Edge Cases & Design Considerations
* **Debouncing:** The digital keypad driver must ensure that one physical press doesn't result in multiple asterisks being entered into the 8-field buffer.
* **Cursor Blink:** The 0.5Hz blink must be non-blocking so that the system remains responsive to user key presses at all times.
* **Reset Requirement:** The firmware does not provide a software "Retry" after 5 failures; a physical MCLR reset is required to clear the failure counter and LED state.

---

## How to Build and Run
1.  **Build:** Use **XC8** to compile the project. Ensure all source files (`main.c`, `clcd.c`, `digital_keypad.c`, `mystrcmp.c`, `config.c`) are included in the build tree.
2.  **Hex Generation:** The process produces a `default-production.hex` file.
3.  **Simulation:**
    * Open **PICSIMLAB** (PicGenios board).
    * Load the `.hex` file.
    * Use Key1 and Key2 to enter the pattern. Observe the asterisk masking and blinking underscore.

---

## Future Improvements
* **EEPROM Failure Logging:** Store the number of failed attempts in EEPROM so that a simple reset cannot bypass the lockout.
* **Password Change Mode:** Allow the user to define a new 8-digit pattern once the system is successfully unlocked.
* **Buzzer Feedback:** Add a short beep for valid key presses and a long tone for incorrect password entries.