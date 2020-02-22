// by /u/frumperino
// goodwires.org

#ifndef __FREKVENSPANEL_H
#define __FREKVENSPANEL_H

#include <Arduino.h>
#include <Adafruit_GFX.h>

class FrekvensPanel : public Adafruit_GFX
{
private:
    unsigned short _numPanels : 4;
    unsigned short _numPages : 4;
    unsigned short _activePage : 4;
    unsigned short _bitDepth : 4;
    unsigned short _pLatch;
    unsigned short _pClock;
    unsigned short _pData;
    unsigned short* buf;
    unsigned short _pageMask;
    unsigned short _addressMask;
    unsigned short _numWords;
    unsigned short _pageStride;
    unsigned short _numPixels;
    unsigned short _width;
    unsigned short _height;

public:
    FrekvensPanel(int p_latch, int p_clock, int p_data, int bitDepth,
                  int numPanels);
    FrekvensPanel(int p_latch, int p_clock, int p_data);

    void init(int p_latch, int p_clock, int p_data, int bitDepth, int numPanels);
    void clear();
    void scan();
    void writeDeepPixel(unsigned short x, unsigned short y, unsigned short value);

    boolean getPixel(int16_t x, int16_t y);

    unsigned short width();
    unsigned short height();

    void drawPixel(int16_t x, int16_t y, uint16_t color) override;
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override;
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override;
    void fillScreen(uint16_t color) override;

private:

};


#endif //__FREKVENSPANEL_H
