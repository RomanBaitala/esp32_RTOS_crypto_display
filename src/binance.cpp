#include "binance.hpp"

bool fetchBinancePrices(const char* symbol, float prices[24]) {
  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  String url = "https://api.binance.com/api/v3/klines?symbol=" + String(symbol) + "&interval=1h&limit=24";
  http.begin(client, url);
  http.addHeader("User-Agent", "ESP32");

  int httpCode = http.GET();
  if (httpCode != 200) {
    Serial.println("Failed to get data: " + String(httpCode));
    http.end();
    return false;
  }

  String payload = http.getString();
  http.end();

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    Serial.print("deserialize Json failed: ");
    Serial.println(error.c_str());
    return false;
  }

  for (int i = 0; i < 24; i++) {
    prices[i] = doc[i][4].as<float>();
  }

  return true;
}
