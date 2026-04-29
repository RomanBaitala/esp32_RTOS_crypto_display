#include <Arduino.h>
#include <wifi.hpp>
#include "config.hpp"
#include "freertos/task.h"
#include "binance.hpp"
#include "screen.hpp"
#include "controller.hpp"
#include "button.hpp"
#include "button_callback.hpp"


void setup() {
    Serial.begin(115200);
    connectWiFi();
    btnNext.setShortPressCallback(onNextShortPress);
    btnPrev.setShortPressCallback(onPrevShortPress);

    priceQueue = xQueueCreate(1, sizeof(BinanceData));

    xTaskCreatePinnedToCore(
        BinanceTask,
        "BinanceT",
        12000,
        NULL,
        1,
        &binanceTaskHandle,
        1
    );

    xTaskCreatePinnedToCore(
        DisplayTask,
        "DisplayT",
        6000,
        NULL, 
        1,
        NULL,
        1
    );
}

void loop() {
    btnNext.tick();
    btnPrev.tick();
}
