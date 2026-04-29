#ifndef BUTTONS_OPERATIONS_H
#define BUTTONS_OPERATIONS_H

#include <stdint.h>
#include <Arduino.h>

typedef void (*ButtonCallback)();

class Button {
private:
    uint8_t _pin;
    bool _lastState = LOW;
    bool _lastRawState = HIGH;
    bool _currentState = HIGH;
    bool _isLongPress = false;
    bool _internalPullup = true;
    uint32_t _timer = 0;
    uint32_t _longPressDuration = 2000;
    uint32_t _debounceDelay = 50;

    ButtonCallback _shortPressCallback = nullptr;
    ButtonCallback _longPressCallback = nullptr;

public:
    Button(uint8_t pin, bool internalPullup = true, uint32_t longPressDuration = 2000);

    void setShortPressCallback(ButtonCallback cb);
    void setLongPressCallback(ButtonCallback cb);
    
    void begin();

    /// @brief Function to check current button state and determine between short and long presses.
    /// @return 0 - not pressed, 1 - short press, 2 - long press 
    uint8_t check();
    void tick();
};

#endif