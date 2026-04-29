#include "controller.hpp"

TaskHandle_t binanceTaskHandle = NULL;
QueueHandle_t priceQueue;
Screen screen;

void BinanceTask(void* parameters) {
  BinanceData data;

  while (true) {
    ulTaskNotifyTake(pdTRUE, (60000 / portTICK_PERIOD_MS));

    const char* symbol = cryptoPairs[currnetPairIndex];

    data.success = fetchBinancePrices(symbol, data.prices);

    if (data.success) {
      xQueueOverwrite(priceQueue, &data);
      Serial.println("Binance prices updated.");
    } else {
      Serial.println("Failed to fetch Binance prices.");
    }
  }
}

void DisplayTask(void* parameters) {
  screen.init();

  BinanceData data;

  while(true) {
    

    xQueueReceive(priceQueue, &data, 0);
        
    if (data.success) {
      const char* symbol = cryptoPairs[currnetPairIndex];

      screen.updatePrice(symbol, data.prices);
    }
    
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}