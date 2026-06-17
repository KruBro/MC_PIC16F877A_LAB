# Right Scrolling Message Marquee on CLCD

## Problem Statement
The goal of this firmware project is to implement a right-scrolling message marquee on a Character Liquid Crystal Display (CLCD) using the **PIC16F877A** microcontroller. The system is designed to display a hardcoded static string that moves continuously from left to right across the display area. The implementation utilizes software-based timing (non-timer) to achieve a scroll frequency of approximately 0.5 Hz, ensuring the message repeats indefinitely for consistent visual output.

---

## Features
* **Continuous Right Scroll:** The message enters from the left and shifts toward the right boundary of the CLCD.
* **Infinite Looping:** Once the message clears the display or reaches a defined boundary, the sequence restarts to provide an endless marquee effect.
* **Software-Defined Timing:** Animation speed is controlled via calibrated software delay loops to approximate a 0.5 Hz (2-second) full-cycle or step frequency.
* **4-Bit Initialization:** Configures the CLCD in 4-bit mode to optimize GPIO pin usage while maintaining full command and data functionality.
* **Static Message Integration:** Supports hardcoded strings directly within the firmware's data memory.

---

## System Overview
The system operates by manipulating the DDRAM (Display Data RAM) addresses of the CLCD. Upon power-up, the MCU initializes the CLCD and clears the display. In the main execution loop, the firmware calculates the starting position of the string. By incrementally adjusting the cursor position before writing the string, the "scrolling" effect is achieved. Between each positional update, the processor enters a non-blocking or blocking software delay to regulate the scroll speed to the target 0.5 Hz.

---

## Project Structure
```text
AS-09/
├── main.c              # Main loop containing the scrolling algorithm and message string
├── clcd.c              # CLCD driver implementation (Instructions, Data, and Init)
├── clcd.h              # CLCD pin definitions, commands, and function prototypes
├── config.h            # Configuration bits and oscillator frequency (20MHz)
├── README.md           # Project documentation and problem definition
└── out/                # Compiled .hex and .elf production files
```

---

## Hardware Requirements
* **Microcontroller:** PIC16F877A.
* **Display:** 16x2 Character LCD (Hitachi HD44780 compatible).
* **Clock Source:** 20MHz External Crystal.
* **Interface:** 4-bit Data Bus (RD4-RD7), RS (RE2), and EN (RE1) pins.
* **Platform:** PicGenios Board (PICSIMLAB Simulator).

---

## Software Design

### CLCD Initialization
The `clcd.c` module performs a 4-bit initialization sequence. This involves sending specific nibbles to set the function mode (2 lines, 5x8 dots), turning on the display, and clearing any existing characters.

### Scrolling Logic
The scrolling effect is implemented by varying the column index in the `clcd_print()` or `clcd_putch()` commands.
1.  A loop iterates through possible start positions (0 to 15).
2.  In each iteration, the display is cleared.
3.  The cursor is set to the current index.
4.  The static message is printed.
5.  If the index exceeds the screen width, the logic handles wrapping the string back to the start.

### Non-Timer Delay
Since the requirement specifies a non-timer-based approach, the firmware uses the `__delay_ms()` macro. The delay is calculated based on the `_XTAL_FREQ` defined in `config.h` (20MHz) to ensure that each shift in the message happens at a human-readable pace.

---

## Working Logic / Flow
1.  **Start:** Initialize `PORTD` and `PORTE` as digital outputs.
2.  **Display Setup:** Call `init_clcd()` to prepare the 16x2 screen.
3.  **Scroll Loop:**
    * Start at Column 0.
    * Print the message: "   Embedded System   ".
    * Wait for ~500ms using a software loop.
    * Clear the row or the entire display.
    * Increment the starting column and repeat.
4.  **Reset:** When the column index reaches 16, reset the index to 0 to restart the scroll from the left.

---

## Edge Cases & Design Considerations
* **String Length:** The algorithm ensures that if the message is longer than the display width, it is truncated or correctly offset to prevent memory corruption.
* **Flicker Reduction:** Instead of clearing the whole screen (which causes flickering), the firmware may overwrite previous characters with spaces or only update the necessary DDRAM addresses.
* **Blocking Nature:** Because this implementation uses software delays, the CPU is unable to process other tasks during the wait period. For complex systems, a timer-based approach is usually preferred.

---

## How to Build and Run
1.  **Build:** Compile the project using the **XC8 Compiler** within **MPLAB X**.
2.  **Binary:** Locate the `default-production.hex` in the `out/` directory.
3.  **Simulate:**
    * Open **PICSIMLAB** and select the **PicGenios** board.
    * Load the `.hex` file.
    * Observe the message moving across the top row of the CLCD from left to right.

---

## Future Improvements
* **Bidirectional Scrolling:** Add a switch input to toggle between left-to-right and right-to-left scrolling.
* **Speed Control:** Use a potentiometer with the ADC to dynamically adjust the scroll frequency.
* **Dual-Line Marquee:** Implement independent scrolling messages on both Row 1 and Row 2 of the CLCD.