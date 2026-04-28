#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "binance.hpp"
#include "screen.hpp"

extern QueueHandle_t priceQueue;

void BinanceTask(void* parameters);
void DisplayTask(void* parameters);

#endif 