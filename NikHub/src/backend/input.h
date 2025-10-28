#pragma once
#include <XPT2046_Touchscreen.h>

#define TEST_BUTTON_UP 0 // TEST
#define TEST_BUTTON_DOWN 0 // TEST

class Input {
    public:
        Input(XPT2046_Touchscreen &tsRef) : ts(tsRef) {}
        bool isTouched(int &x, int &y);
        bool isButtonPressed(int pin);
    private:
        XPT2046_Touchscreen &ts;
};