#include <Arduino.h>
#include "LedState.h"
#include "Led.h"
#include "LedMode.h"

struct Config {
    static constexpr uint8_t LED_PIN = LED_BUILTIN;
    static constexpr unsigned long BLINK_INTERVAL = 1000;
    static constexpr uint8_t BUTTON_PIN = 0;
    static constexpr unsigned long DEBOUNCE_MS = 50;
};

Led led(Config::LED_PIN);
volatile bool button_pressed = false;

void IRAM_ATTR onButton() {
    button_pressed = true;
}

void setup() {
    led.init();
    pinMode(Config::BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(Config::BUTTON_PIN), onButton, FALLING);

    Serial.begin(115200);
}

void loop() {
    static unsigned long start_time = millis();
    static LedState state = LedState::Off;
    static LedMode current_mode = LedMode::Blink;
    static unsigned long last_click = millis();


    if (button_pressed) {
        button_pressed = false;
        if (millis() - last_click >= Config::DEBOUNCE_MS) {
            last_click = millis();
            switch (current_mode) {
                case LedMode::Blink:     current_mode = LedMode::AlwaysOn;  break;
                case LedMode::AlwaysOn:  current_mode = LedMode::AlwaysOff; break;
                case LedMode::AlwaysOff: current_mode = LedMode::Blink; break;
            }
        }
    }

    if (current_mode == LedMode::Blink) {
        if (millis() - start_time >= Config::BLINK_INTERVAL && state == LedState::Off) {
            start_time = millis();
            state = LedState::On;
            led.set(state);
        }
        if (millis() - start_time >= Config::BLINK_INTERVAL && state == LedState::On) {
            start_time = millis();
            state = LedState::Off;
            led.set(state);
        }
    } else if (current_mode == LedMode::AlwaysOff) {
        state = LedState::Off;
        led.set(state);
    } else if (current_mode == LedMode::AlwaysOn) {
        state = LedState::On;
        led.set(state);
    }

}