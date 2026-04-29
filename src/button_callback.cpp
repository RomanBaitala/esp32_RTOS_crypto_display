#include "button_callback.hpp"

void onNextShortPress() {
    currnetPairIndex = (currnetPairIndex + 1) % totalPairs;
    
    xTaskNotifyGive(binanceTaskHandle);
}

void onPrevShortPress() {
    currnetPairIndex = (currnetPairIndex + totalPairs - 1) % totalPairs;

    xTaskNotifyGive(binanceTaskHandle);
}

