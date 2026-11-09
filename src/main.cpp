#include <Arduino.h>

constexpr uint8_t LED_PINS[3]       = {8, 9, 10};
constexpr unsigned long PERIODS[3]  = {200, 500, 1000};
static unsigned long lastToggle[3]     = {0, 0, 0};
static bool ledState[3]                = {false, false, false};

static void select_mode_for_led(const unsigned long mill, unsigned long &lastTog, const uint8_t led, const unsigned long interval, bool &state) {
    if (mill - lastTog >= interval) {
        lastTog = mill;
        state = !state;
        digitalWrite(led, state);
    }
}


void setup() {
    for (const unsigned char led_position : LED_PINS) {
        pinMode(led_position, OUTPUT);
    }
}

void loop() {
    const unsigned long now = millis();

    select_mode_for_led(now, lastToggle[0], LED_PINS[0], PERIODS[0], ledState[0]);
    select_mode_for_led(now, lastToggle[1], LED_PINS[1], PERIODS[1], ledState[1]);
    select_mode_for_led(now, lastToggle[2], LED_PINS[2], PERIODS[2], ledState[2]);

}