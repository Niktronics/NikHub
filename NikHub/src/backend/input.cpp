#include "input.h"

bool Input::isTouched(int &x, int &y) {
    if (ts.touched()) {
        TS_Point p = ts.getPoint();
        x = map(p.x, 0, 3800, 0, 320);
        y = map(p.y, 0, 3800, 0, 240);
        return true;
    }
    return false;
}