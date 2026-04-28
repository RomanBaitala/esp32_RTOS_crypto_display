#include <Arduino.h>
#include <wifi.hpp>
#include "freertos/task.h"
#include "binance.hpp"
#include "screen.hpp"
#include "controller.hpp"


void setup() {
    Serial.begin(115200);
    connectWiFi();

    priceQueue = xQueueCreate(1, sizeof(BinanceData));

    xTaskCreatePinnedToCore(
        BinanceTask,
        "BinanceT",
        12000,
        (void*) "BTCUSDT",
        1,
        NULL,
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

void loop() {}
