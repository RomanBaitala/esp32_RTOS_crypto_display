#include "button_callback.hpp"

void onNextShortPress() {
    currentScreenMode = MODE_PRICE;
    currnetPairIndex = (currnetPairIndex + 1) % totalPairs;

    BinanceData data;
    data.success = false;
    xQueueOverwrite(priceQueue, &data);
    
    xTaskNotifyGive(binanceTaskHandle);
}

void onPrevShortPress() {
    currentScreenMode = MODE_PRICE;
    currnetPairIndex = (currnetPairIndex + totalPairs - 1) % totalPairs;

    BinanceData data;
    data.success = false;
    xQueueOverwrite(priceQueue, &data);

    xTaskNotifyGive(binanceTaskHandle);
}

void onNextLongPress() {
    currentScreenMode = MODE_IP;
}
