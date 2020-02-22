//
// Created by /u/frumperino
//

#include <Arduino.h>

#ifndef __simplebutton_h
#define __simplebutton_h

typedef void (*ButtonEH) (int, int); // id, state

class SimpleButton
{
private:
    unsigned short pin      : 8;
    unsigned short state    : 1;
    unsigned short invert   : 1;
    unsigned short changing : 1;
    unsigned short attached : 1;
    char id;
    ButtonEH handler = nullptr;
    unsigned short debounceMS;
    unsigned long tChange = 0;
public:
    SimpleButton(char id, char pin, char invert, unsigned short debounceMS)
    {
        this->id = id;
        this->invert = invert;
        this->pin = pin;
        this->changing = false;
        this->debounceMS = debounceMS;
        this->state = digitalRead(pin);
        this->attached = false;
    }

    void attachHandler(ButtonEH handler)
    {
        this->handler = handler;
        this->attached = true;
    }

    char getState()
    {
        return this->state;
    }

    void scan()
    {
        char newState = digitalRead(pin);
        if (newState == state)
        {
          changing = false;          
        }
        else
        {
            unsigned long tNow = millis();
            if (!changing)
            {
                changing = true;
                tChange = tNow;
            }
            else
            {
                unsigned long tD = tNow - tChange;
                if (tD >= debounceMS)
                {
                    state = newState;
                    changing = false;
                    if (attached)
                    {
                        handler(id, state ^ invert);
                    }
                }
            }
        }
    }

};

#endif //__simplebutton_h
