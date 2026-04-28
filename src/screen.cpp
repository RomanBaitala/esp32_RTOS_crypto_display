#include "screen.hpp"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

Screen::Screen(){}

void Screen::init() {
    u8g2.begin();
}

void Screen::showIP(IPAddress ip) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_7x14_tf);
    u8g2.drawStr(0, 15, "MY IP:");
    u8g2.setCursor(0, 40);
    u8g2.print(ip);
    u8g2.sendBuffer();
}

void Screen::showStatus(const char* title, const char* msg1, const char* msg2){
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(0, 12, title);
    u8g2.drawStr(0, 32, msg1);
    u8g2.drawStr(0, 52, msg2);
    u8g2.sendBuffer();
}

float Screen::_priceDayChange(float nowPrice, float firstPrice){
  return (nowPrice - firstPrice) / firstPrice * 100.0; 
}

void Screen::_drawGraph(float prices[], int count, int x, int y, int w, int h) {
  float minP = prices[0], maxP = prices[0];
  for (int i = 1; i < count; ++i) {
    if (prices[i] < minP) minP = prices[i];
    if (prices[i] > maxP) maxP = prices[i];
  }
  if (maxP == minP) maxP += 1;

  for (int i = 0; i < count - 1; ++i) {
    int x0 = x + (i * w) / (count - 1);
    int y0 = y - ((prices[i] - minP) / (maxP - minP)) * h;
    int x1 = x + ((i + 1) * w) / (count - 1);
    int y1 = y - ((prices[i + 1] - minP) / (maxP - minP)) * h;
    u8g2.drawLine(x0, y0, x1, y1);
  }
}

void Screen::updatePrice(const char* symbol, float prices[24]) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(0, 10, symbol);

  char priceStr[20];
  sprintf(priceStr, "$%.2f", prices[23]);
  u8g2.drawStr(0, 25, priceStr);

  float change = _priceDayChange(prices[23], prices[0]);
  char changeStr[20];
  sprintf(changeStr, "%+.2f%%", change);
  u8g2.drawStr(80, 25, changeStr);

  _drawGraph(prices, 24, 0, 63, 128, 30);
  u8g2.sendBuffer();
}
