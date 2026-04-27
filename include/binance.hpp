#ifndef BINANCE_HPP
#define BINANCE_HPP

#include <Arduino.h>
#include <WiFi.h> 
#include <ArduinoJson.h>
#include <HTTPClient.h>

bool fetchBinancePrices(const char* symbol, float prices[24]);

#endif