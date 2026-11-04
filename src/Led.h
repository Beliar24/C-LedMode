//
// Created by Black on 04.11.2026.
//

#ifndef ESP_LED_H
#define ESP_LED_H

#include <esp32-hal-gpio.h>
#include "LedState.h"


class Led {
public:
    explicit Led(uint8_t pin) : pin_(pin) {}

    void init() {
        pinMode(pin_, OUTPUT);
    }

    void set(LedState state) const {
        state == LedState::Off ? digitalWrite(pin_, LOW) : digitalWrite(pin_, HIGH);
    }

private:
    const uint8_t pin_;
};


#endif //ESP_LED_H
