#include "binance.hpp"

QueueHandle_t priceQueue; 

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

bool fetchBinancePrices(const char* symbol, float prices[24]) {
  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  String url = "https://api.binance.com/api/v3/klines?symbol=" + String(symbol) + "&interval=1h&limit=24";
  http.begin(client, url);
  http.addHeader("User-Agent", "ESP32");

  int httpCode = http.GET();
  if (httpCode != 200) {
    http.end();
    return false;
  }

  String payload = http.getString();
  http.end();

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    return false;
  }

  for (int i = 0; i < 24; i++) {
    prices[i] = doc[i][4].as<float>();
  }

  return true;
}
