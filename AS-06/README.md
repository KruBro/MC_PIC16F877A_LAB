# System Sleep and Wake-up via External Interrupt

## Problem Statement
The objective of this firmware project is to implement power management features on the **PIC16F877A** microcontroller, specifically utilizing the **Sleep mode** and **External Interrupt (INT0)** for wake-up functionality. The system must maintain a visual status via a 4-digit Seven-Segment Display (SSD) and an activity LED, transitioning into a low-power state when inactive and resuming full operation upon detecting a hardware interrupt.

---

## Features
* **Power Management:** Automatically transitions the MCU into Sleep mode to conserve power during periods of inactivity.
* **External Wake-up:** Uses the `INT0` pin (RB0) as an edge-triggered external interrupt source to wake the processor from Sleep.
* **Visual Status:** Displays a static identifier ("1234") on a multiplexed 4-digit SSD upon system boot and resume.
* **Activity Heartbeat:** Toggles an LED every second during active execution to indicate system status.
* **Interrupt-Driven Architecture:** Leverages an Interrupt Service Routine (ISR) to handle the transition from power-down to active execution.

---

## System Overview
The system starts by initializing the GPIO ports for the SSD and LED, followed by configuring the External Interrupt on the RB0 pin. In the main execution loop, the system manages a 1-second heartbeat LED while refreshing the SSD digits. After a period of no activity, the firmware executes the `SLEEP` instruction. In this state, the CPU clock is halted, and the SSD turns off. Only a transition on the `INT0` pin can trigger the hardware wake-up, returning the system to its active state to resume pattern display and LED toggling.

---

## Project Structure
```text
AS-06/
├── main.c                  # Core state machine and sleep/wake-up logic
├── main.h                  # Peripheral macros and hardware abstraction
├── isr.c                   # Interrupt Service Routine for INT0 wake-up event
├── ext_interrupt_init.c    # Configuration for external interrupt (INTEDG, INTE)
├── ssd.c                   # SSD driver for port initialization and display refresh
└── out/                    # Final .hex and build artifacts for the PicGenios board
```

---

## Hardware Requirements
* **Microcontroller:** PIC16F877A.
* **Interrupt Source:** Tactile switch connected to RB0 (INT0).
* **Display:** 4-Digit Common Cathode Seven-Segment Display (SSD).
* **Indicator:** Activity LED connected to a specific GPIO (e.g., RD0).
* **Board:** PicGenios (Simulator PICSIMLAB).

---

## Software Design

### Interrupts / ISR
The `isr.c` file contains the logic to handle the `INT0` event. When the switch is pressed, the `INTF` (Interrupt Flag) is cleared, and the system exits the Sleep state. Since the `SLEEP` instruction is followed by the ISR execution (if global interrupts are enabled), the ISR serves as the bridge to resume the main loop.

### System Sleep Logic
The system uses the `SLEEP` assembly instruction wrapper provided by the XC8 compiler. Before entering sleep:
1.  All output peripherals (like the SSD) are typically disabled to maximize power savings.
2.  The External Interrupt Enable (`INTE`) bit is set to ensure the hardware can listen for the wake-up trigger.

### Timer Usage
A timer (Timer0) is used to track the 1-second interval required for the heartbeat LED. This timer facilitates non-blocking delays, ensuring the SSD multiplexing remains responsive while counting toward the next LED toggle.

---

## Working Logic / Flow
1.  **Initial State:** System powers on and displays "1234" on the SSD. LED starts toggling every second.
2.  **Inactivity Detection:** After a set period of execution, the firmware prepares for power-down.
3.  **Sleep Mode:** The `SLEEP` instruction is called. The display turns off, and the LED stops toggling.
4.  **Wake-up Event:** The user presses the INT0 switch (RB0).
5.  **ISR Handling:** The CPU wakes up, enters the ISR to clear the interrupt flag, and then returns to the main loop.
6.  **Resumption:** The message "1234" reappears on the SSD, and the heartbeat LED resumes its 1-second toggling cycle.

---

## Edge Cases & Design Considerations
* **Interrupt Edge Selection:** The `INTEDG` bit is configured to determine if the wake-up occurs on the rising or falling edge of the switch press.
* **Switch Debouncing:** Since the system is in Sleep, traditional software debouncing isn't active; the first valid edge triggers the wake-up immediately.
* **Port State Retention:** The MCU retains the last state of its latches during sleep; therefore, the firmware explicitly clears the SSD pins before sleep to ensure the display truly turns off.

---

## How to Build and Run
1.  **Build:** Compile the source files using the **Microchip XC8 Compiler** to generate the `default-production.hex` file.
2.  **Simulator Setup:**
    * Launch **PICSIMLAB** and select the **PicGenios** board.
    * Load the generated `.hex` file.
3.  **Observation:**
    * Observe the LED toggling and "1234" on the display.
    * Wait for the system to enter Sleep (display/LED turns off).
    * Press the **RB0/INT0** button to wake the system and see the display resume.

---

## Future Improvements
* **Watchdog Timer (WDT) Wake-up:** Implement a periodic wake-up using the WDT to check sensors without user interaction.
* **Deep Sleep Configurations:** Configure unused GPIO pins to high-impedance or specific levels to further reduce leakage current during sleep.
* **Dynamic Messages:** Display different status codes depending on the source of the wake-up (e.g., INT0 vs. Port Change).