## About the Project

This is a C++ firmware implementation for Ralph Hilton's C-Meter, adapted for the **NodeMCU (ESP-12E / ESP8266)** development board. The firmware is built strictly according to the specifications provided on [Ralph Hilton's official website](https://web.archive.org/web/20060808033709/http://www.ralphhilton.org/). 

The primary purpose of this repository is to provide a minimalist setup for **testing and verifying the C-Meter desktop application** using the ESP-12E's built-in ADC.

## ⚠️ Critical Warning & Limitations

> [!WARNING]
> **Not for Actual Auditing Use.**
> The built-in ADC of the ESP-12E is a **single-ended (non-differential), noisy 10-bit ADC**. It lacks the resolution and noise-suppression required for actual auditing sessions. This project is intended **strictly for software testing and demonstration purposes**.

### Hardware Upgrade Path
If you wish to build a production-grade device, you can adapt this firmware to work with an external, low-noise, **24-bit differential Sigma-Delta ADC** with a sampling rate of **at least 300 SPS (Samples Per Second)**.

## 🔌 Connection & Hardware Note (Endless Bootloop Fix)

If you use the onboard Micro-USB/Type-C port of the NodeMCU for communication, you will encounter a hardware conflict: 
When the PC-side `c-meter` application opens the COM port, it toggles the DTR/RTS lines. Due to the NodeMCU's built-in auto-reset/flashing circuit, this triggers the bootloader state, putting the board into an **endless restart loop**.

### **How to use it properly:**
1. Flash the NodeMCU board using the onboard USB port as usual.
2. Disconnect the onboard USB.
3. Connect the NodeMCU to your PC using an **external USB-to-UART (TTL) adapter** using only three wires: **TX, RX, and GND**. Bypassing the onboard USB chip prevents the desktop software from accidentally resetting the microcontroller.
