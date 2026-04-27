#include <Arduino.h>
#include <wifi.hpp>
#include "freertos/task.h"

void setup() {
    Serial.begin(115200);
    connectWiFi();
}

void loop() {
}
