#include "controller.hpp"

TaskHandle_t binanceTaskHandle = NULL;
QueueHandle_t priceQueue;


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
    if (currentScreenMode == MODE_IP) {
      IPAddress ip = WiFi.localIP();
      screen.showIP(ip);

      vTaskDelay(5000 / portTICK_RATE_MS);
    } 
    else if (currentScreenMode == MODE_PRICE) {
      xQueueReceive(priceQueue, &data, 0);
        
      if (data.success) {
        const char* symbol = cryptoPairs[currnetPairIndex];

        screen.updatePrice(symbol, data.prices);
      } 
      else {
        screen.showStatus("Loading...", cryptoPairs[currnetPairIndex]);
      }

      vTaskDelay(200 / portTICK_PERIOD_MS);
    }
  }
}