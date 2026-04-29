#include "config.hpp"

const uint8_t BTN_NEXT_PIN = 38;
const uint8_t BTN_PREV_PIN = 37;
const uint8_t BTN_LONG_PRESS_DURATION = 2000;
const bool BTN_INTERNAL_PULLUP = false;

Button btnNext(BTN_NEXT_PIN, BTN_INTERNAL_PULLUP, BTN_LONG_PRESS_DURATION);
Button btnPrev(BTN_PREV_PIN, BTN_INTERNAL_PULLUP, BTN_LONG_PRESS_DURATION);

volatile uint8_t currnetPairIndex = 0;

const char* cryptoPairs[] = {
    "BTCUSDT",
    "ETHUSDT",
    "BNBUSDT",
    "ADAUSDT",
    "XRPUSDT"
};

const uint8_t totalPairs = sizeof(cryptoPairs) / sizeof(cryptoPairs[0]);
