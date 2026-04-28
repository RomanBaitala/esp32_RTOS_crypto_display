#include "controller.hpp"

QueueHandle_t priceQueue;
Screen screen;

void BinanceTask(void* parameters) {
  const char* symbol = (const char*) parameters;

  BinanceData data;

  while (true) {
    data.success = fetchBinancePrices(symbol, data.prices);

    if (data.success) {
      xQueueOverwrite(priceQueue, &data);
      Serial.println("Binance prices updated.");
    } else {
      Serial.println("Failed to fetch Binance prices.");
    }

    vTaskDelay(60000 / portTICK_PERIOD_MS);
  }
}

void DisplayTask(void* parameters) {
    screen.init();

    BinanceData data;

    while(true) {
        xQueueReceive(priceQueue, &data, 0);
            
        if (data.success) {
            screen.updatePrice("BTCUSDT", data.prices);
        }
        
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}