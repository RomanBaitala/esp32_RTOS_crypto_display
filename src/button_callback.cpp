#include "button_callback.hpp"

void onNextShortPress() {
    currentScreenMode = MODE_PRICE;
    currnetPairIndex = (currnetPairIndex + 1) % totalPairs;
    
    xTaskNotifyGive(binanceTaskHandle);
}

void onPrevShortPress() {
    currentScreenMode = MODE_PRICE;
    currnetPairIndex = (currnetPairIndex + totalPairs - 1) % totalPairs;

    xTaskNotifyGive(binanceTaskHandle);
}

void onNextLongPress() {
    currentScreenMode = MODE_IP;
}
