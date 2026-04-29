#include "button.hpp"

uint8_t prev_res = 0;

Button::Button(
  uint8_t pin, 
  bool internalPullup, 
  uint32_t longPressDuration
) :
  _pin(pin), 
  _internalPullup(internalPullup), 
  _longPressDuration(longPressDuration) {}

void Button::setShortPressCallback(ButtonCallback cb) {
  _shortPressCallback = cb;
}

void Button::setLongPressCallback(ButtonCallback cb) {
  _longPressCallback = cb;
}

void Button::begin() {
  if (_internalPullup) {
    pinMode(_pin, INPUT_PULLUP);
  } else {
    pinMode(_pin, INPUT);
  }
}

uint8_t Button::check() {
  bool rawRead = digitalRead(_pin);
  uint8_t result = 0;

  if (rawRead != _lastRawState){
    _timer = millis();
  }

  _lastRawState = rawRead;

  if (millis() - _timer >= _debounceDelay){
      _currentState = (rawRead == LOW);
  }
  
  if (_currentState && !_lastState) {
    _timer = millis();
    _isLongPress = false;
  }
  
  if (_currentState && !_isLongPress){
    if (millis() - _timer >= _longPressDuration){
      _isLongPress = true;
      result = 2;
    }
  }

  if (!_currentState && _lastState) {
    if (!_isLongPress){
      result = 1;
    }
  }

  _lastState = _currentState;
  return result;
}

void Button::tick() {
  uint8_t res = check();
  if (res == 1 && _shortPressCallback) _shortPressCallback();
  if (res == 2 && _longPressCallback) _longPressCallback();
}
