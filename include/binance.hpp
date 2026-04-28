#ifndef BINANCE_HPP
#define BINANCE_HPP

#include <Arduino.h>
#include <WiFi.h> 
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

struct BinanceData { 
    float prices[24];
    bool success;
};

bool fetchBinancePrices(const char* symbol, float prices[24]);

#endif