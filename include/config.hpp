#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <Arduino.h>
#include <button.hpp>

extern const uint8_t BTN_NEXT_PIN;
extern const uint8_t BTN_PREV_PIN;
extern const uint8_t BTN_LONG_PRESS_DURATION;
extern const bool BTN_INTERNAL_PULLUP;

extern Button btnNext;
extern Button btnPrev;

extern const uint8_t totalPairs;
extern const char* cryptoPairs[];

extern volatile uint8_t currnetPairIndex;

#endif