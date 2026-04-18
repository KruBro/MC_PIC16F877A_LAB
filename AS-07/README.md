# Synchronized Multi-Timer Time Separator

## Problem Statement
The objective of this project is to implement a synchronized time separator (0.5 Hz blink) using three independent hardware timers—**Timer0, Timer1, and Timer2**—on the **PIC16F877A** microcontroller. The system must drive three dedicated LEDs, each toggling precisely every 500ms without drift over long durations. This requires precise peripheral configuration and a unified interrupt handling strategy to ensure all three time-bases remain phase-locked.

---

## Features
* **Multi-Timer Implementation:** Simultaneous utilization of all three 8-bit and 16-bit hardware timers available on the PIC16F877A.
* **Zero-Drift Synchronization:** Precise calculations for timer pre-loading and prescalers to maintain frequency stability over hours of operation.
* **Concurrent Toggling:** Three independent LED indicators (one per timer) operating at a 500ms toggle frequency (0.5 Hz).
* **Interrupt-Driven Logic:** High-efficiency Interrupt Service Routine (ISR) that processes overflow flags for all three timers without blocking the main execution loop.
* **Modular Configuration:** Dedicated drivers for each timer peripheral, ensuring clean code separation.

---

## System Overview
The firmware initializes the microcontroller’s GPIO and hardware timers. Each timer is configured with specific prescalers and postscalers to trigger an interrupt at a sub-multiple of the 500ms target. Inside the global ISR, software counters track these overflows. When a counter reaches the 500ms threshold, the corresponding LED state is toggled. This architecture ensures that even though the timers have different bit-widths and capabilities, their outputs remain perfectly synchronized to the system clock.

---

## Project Structure
```text
AS-07/
├── main.c              # System initialization and main super-loop
├── main.h              # Global definitions and macro configurations
├── isr.c               # Central ISR handling overflow flags for Timers 0, 1, and 2
├── timer0.c            # Configuration for the 8-bit Timer0 peripheral
├── timer1.c            # Configuration for the 16-bit Timer1 peripheral
├── timer2.c            # Configuration for the 8-bit Timer2 with Postscaler
└── README.md           # Technical project documentation
```

---

## Hardware Requirements
* **Microcontroller:** PIC16F877A.
* **Clock Source:** 20MHz External Crystal (Fosc).
* **Indicators:** 3x LEDs connected to PORTB (e.g., RB0, RB1, RB2).
* **Platform:** PicGenios Board (PICSIMLAB Simulator).

---

## Software Design

### Timer Configuration Strategy
To achieve a 500ms (0.5 Hz) toggle without drift using a 20MHz clock ($F_{cy} = 5MHz$), the timers are configured as follows:
* **Timer0:** Configured as an 8-bit timer with a 1:256 prescaler. It requires software counting of overflows to reach the 500ms mark.
* **Timer1:** Configured as a 16-bit timer. It leverages its larger capacity to reach longer intervals with fewer software increments.
* **Timer2:** An 8-bit timer with a Period Register (PR2). It uses a combination of hardware prescaler and postscaler to generate precise periodic interrupts.

### Interrupt Service Routine (ISR)
The ISR acts as the synchronization hub. It checks the `TMR0IF`, `TMR1IF`, and `TMR2IF` flags. Upon an overflow:
1.  The timer register is re-loaded (for TMR0/TMR1) to maintain constant timing intervals.
2.  An associated software counter is incremented.
3.  When the counter matches the 500ms constant, the specific LED bit is inverted.

---

## Working Logic / Flow
1.  **Init Phase:** Configure `TRISB` for LED outputs. Set all LED pins to `LOW`.
2.  **Peripheral Setup:** Call `init_timer0()`, `init_timer1()`, and `init_timer2()`.
3.  **Global Interrupts:** Enable `GIE` and `PEIE` bits to allow the timers to trigger the ISR.
4.  **Runtime:** The CPU enters an empty `while(1)` loop. All work is handled in the background by the hardware timers and the ISR.
5.  **Synchronization:** Since all timers derive their clock from the same 20MHz crystal, the 0.5 Hz outputs remain phase-accurate indefinitely.

---

## Edge Cases & Design Considerations
* **Interrupt Latency:** The ISR is kept lean to ensure that the time taken to clear flags and reload registers does not introduce cumulative error.
* **Timer2 Period Matching:** Unlike TMR0/1, TMR2 resets automatically when it matches `PR2`, making it the most naturally precise for periodic tasks.
* **Long-term Stability:** By using integer divisions of the 5MHz instruction clock, the 500ms interval is exact, preventing the "drifts" mentioned in the requirements.

---

## How to Build and Run
1.  **Compile:** Use the **XC8 Compiler** with **MPLAB X** or the **CMake** build scripts.
2.  **Binary:** Locate the `default-production.hex` file in the `out/` directory.
3.  **Simulate:**
    * Launch **PICSIMLAB** and select the **PicGenios** board.
    * Load the `.hex` file.
    * Observe three LEDs toggling in perfect unison every half-second.

---

## Future Improvements
* **Low Power Toggling:** Use Timer1 in asynchronous counter mode with a 32.768kHz watch crystal for even higher precision and lower power consumption.
* **Phase Offsetting:** Modify the counters to stagger the LED toggles (e.g., LED1 at 0ms, LED2 at 100ms, LED3 at 200ms) for visual sequencing.
* **UART Telemetry:** Output the drift status or interrupt counts to a serial terminal for real-time validation of synchronization.