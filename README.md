# Hilton C-Meter for ESP8266

A simple C++ firmware for Ralph Hilton's C-Meter, adapted for the **NodeMCU (ESP-12E)** board based on the specs from [his website]([URL_HERE](https://web.archive.org/web/20060102021322/http://www.cmeter.org/) (web archive). 

It is made purely to test the C-Meter desktop app using the board's internal ADC.

## Important: Internal ADC is for testing only!
The built-in ADC on the ESP-12E is only 10-bit, single-ended, and quite noisy. It is **not suitable for actual auditing**. 
If you want to build a real working device, you should adapt this code to use an external low-noise **24-bit differential Sigma-Delta ADC** (with a sampling rate of at least 300 SPS).

## The Bootloop Issue (and how to fix it)
If you connect the NodeMCU via its onboard USB port, the `c-meter` app will trigger the DTR/RTS lines upon connection. This triggers the auto-flash circuit and puts the NodeMCU into an **endless reset loop**.

**How to use it:**
1. Flash the NodeMCU via the onboard USB port as usual.
2. Unplug that cable.
3. Connect to the PC using an **external USB-to-UART adapter** with just 3 wires: **TX, RX, and GND**. This bypasses the auto-reset circuit and works perfectly.
