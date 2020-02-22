// By /u/frumperino
// goodwires.org

#include "FrekvensPanel.h"

void init(int p_latch, int p_clock, int p_data, int p_enable);

FrekvensPanel::FrekvensPanel(int p_latch, int p_clock, int p_data, int bitDepth,
                             int numPanels) : Adafruit_GFX(16, numPanels * 16)
{
    init(p_latch, p_clock, p_data, bitDepth, numPanels);
}

FrekvensPanel::FrekvensPanel(int p_latch, int p_clock, int p_data) :
FrekvensPanel(p_latch, p_clock, p_data, 0, 1) { }

void FrekvensPanel::init(int p_latch, int p_clock, int p_data, int bitDepth, int numPanels)
{
    _pLatch = p_latch;
    _pClock = p_clock;
    _pData = p_data;
    pinMode(_pLatch, OUTPUT);
    pinMode(_pClock, OUTPUT);
    pinMode(_pData, OUTPUT);
    _bitDepth = bitDepth;
    _numPages = (1 << bitDepth);
    _pageMask = _numPages - 1;
    _numPanels = numPanels;
    _pageStride = 16 * numPanels;
    _numWords = _numPages * _pageStride;
    _numPixels = 16 * 16 * numPanels;
    _addressMask = _numPixels-1;
    _width = 16;
    _height = 16 * _numPanels;
    buf = (unsigned short*) malloc(_numWords * sizeof(unsigned short));
}

void FrekvensPanel::clear()
{
    for (int i=0;i<_numWords;i++)
    {
        buf[i] = 0;
    }
}

void FrekvensPanel::writeDeepPixel(unsigned short x, unsigned short y, unsigned short value)
{
    if (x > 7) { y += 0x10; x &= 0x07; }
    unsigned int address = (x + (y << 3)) & _addressMask;
    unsigned short ba = address >> 4;
    unsigned short br = address & 0x0F;
    unsigned short ms = (1 << br);
    unsigned short mc = 0xFFFF ^ ms;
    unsigned short* wp = &buf[ba];
    unsigned short ofs = (x+y) & _pageMask;
    for (unsigned int i=0;i<_numPages;i++)
    {
        ofs++;
        ofs &= _pageMask;
        char b = ((value >> ofs) & 0x01);
        if (b)
        {
            *wp |= ms;
        }
        else
        {
            *wp &= mc;
        }
        wp+=_pageStride;
    }
}

void FrekvensPanel::scan()
{
    if (_numPages == 1)
    {
        // single bit plane
        unsigned short* p = &buf[0];
        for (int i=0;i<_pageStride;i++)
        {
            unsigned short w = *p++;
            for (int j=0;j<16;j++)
            {
                digitalWrite(_pData, w & 0x01);
                w >>= 1;
                digitalWrite(_pClock, HIGH);
                delayMicroseconds(1);
                digitalWrite(_pClock, LOW);
            }
        }
        digitalWrite(_pLatch,HIGH);
        delayMicroseconds(1);
        digitalWrite(_pLatch,LOW);
    }
    else
    {
        // multiple bit planes
        unsigned short* p = &buf[_pageStride * _activePage];
        for (int i=0;i<_pageStride;i++)
        {
            unsigned short w = *p++;
            for (int j=0;j<16;j++)
            {
                digitalWrite(_pData, w & 0x01);
                w >>= 1;
                digitalWrite(_pClock, HIGH);
                delayMicroseconds(1);
                digitalWrite(_pClock, LOW);
            }
        }
        digitalWrite(_pLatch,HIGH);
        delayMicroseconds(1);
        digitalWrite(_pLatch,LOW);
        _activePage++;
        _activePage %= _numPages;
    }
}

unsigned short FrekvensPanel::width()
{
    return this->_width;
}

unsigned short FrekvensPanel::height()
{
    return this->_height;
}

boolean FrekvensPanel::getPixel(int16_t x, int16_t y)
{
    if (x > 7) { y += 0x10; x &= 0x07; }
    unsigned short address = (x + (y << 3)) & _addressMask;
    unsigned short ba = address >> 4;
    unsigned short br = address & 0x0F;
    unsigned short* wp = &buf[ba];
    return ((*wp) >> br) & 0x01;
}

void FrekvensPanel::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if ((x >= 0) && (y >= 0) && (x < _width) && ( y < _height))
    {
        if (x > 7) { y += 0x10; x &= 0x07; }
        unsigned short address = (x + (y << 3)) & _addressMask;
        unsigned short ba = address >> 4;
        unsigned short br = address & 0x0F;
        unsigned short ms = (1 << br);
        unsigned short* wp = &buf[ba];
        if (color & 0x01)
        {
            *wp |= ms;
        }
        else
        {
            *wp &= (0xFFFF ^ ms);
        }
    }
}

void FrekvensPanel::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
    for (int i=0;i<h;i++)
    {
        drawPixel(x,y+i,color);
    }

}

void FrekvensPanel::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
    for (int i=0;i<w;i++)
    {
        drawPixel(x+i,y,color);
    }
}

void FrekvensPanel::fillScreen(uint16_t color)
{
    for (int i=0;i<_numPages;i++)
    {
        unsigned short w = color & 0x01 ? 0xFFFF : 0x0000;
        color >>= 1;
        unsigned short* p = &buf[i * _pageStride];
        for (int j=0;j<_pageStride;j++)
        {
            *p++ = w;
        }
    }
}





