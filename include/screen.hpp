#ifndef SCREEN_HPP 
#define SCREEN_HPP

#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

class Screen {
private:
    float _priceDayChange(float nowPrice, float firstPrice);
    void _drawGraph(float prices[], int count, int x, int y, int w, int h);

public:
    Screen();
    void init();
    void updatePrice(const char* symbol, float prices[24]);
    void showStatus(const char* title, const char* msg1, const char* msg2 = "");
    void showIP(IPAddress ip);
};

#endif