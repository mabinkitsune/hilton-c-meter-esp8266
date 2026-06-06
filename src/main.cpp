#include <Arduino.h>
#include <ESP8266WiFi.h>

const int PIN_SENS_PLUS   = 5;  // NodeMCU D1
const int PIN_SENS_MINUS  = 4;  // NodeMCU D2
const int PIN_LOW_BATTERY = 14; // NodeMCU D5

const unsigned long TICK_INTERVAL_MICROS = 3333; // 300 Гц
unsigned long previousMicros = 0;

uint32_t adcSum = 0;
uint32_t adcCount = 0;

void setup() {
    WiFi.persistent(false);
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    delay(1);

    Serial.begin(19200, SERIAL_8N1);

    pinMode(PIN_SENS_PLUS, INPUT_PULLUP);
    pinMode(PIN_SENS_MINUS, INPUT_PULLUP);
    pinMode(PIN_LOW_BATTERY, INPUT_PULLUP); 

    previousMicros = micros();
}

void loop() {
    unsigned long currentMicros = micros();

    if (currentMicros - previousMicros < TICK_INTERVAL_MICROS) {
        adcSum += (1023 - analogRead(A0));
        adcCount++;
    } 

    else {
        previousMicros += TICK_INTERVAL_MICROS;

        uint32_t ltc_val = 0;

        if (adcCount > 0) {
            ltc_val = (uint32_t)(((uint64_t)adcSum << 19) / adcCount);
        }

        adcSum = 0;
        adcCount = 0;

        // ltc_val |= (1UL << 29);

        bool sens_plus   = (digitalRead(PIN_SENS_PLUS) == LOW);
        bool sens_minus  = (digitalRead(PIN_SENS_MINUS) == LOW);
        bool low_battery = (digitalRead(PIN_LOW_BATTERY) == LOW);

        uint8_t packet[4];
        packet[0] = 0x80 | ((ltc_val >> 23) & 0x7F);
        packet[1] = 0x00 | ((ltc_val >> 16) & 0x7F);
        packet[2] = 0x00 | ((ltc_val >> 9) & 0x7F);
        packet[3] = 0x00 | 
                    ((sens_plus ? 1 : 0) << 6)   |
                    ((sens_minus ? 1 : 0) << 5)  |
                    ((low_battery ? 1 : 0) << 4) |
                    ((ltc_val >> 5) & 0x0F);

        Serial.write(packet, 4);
    }
}