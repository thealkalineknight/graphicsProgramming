#include "settings.h"

Settings::Settings() {
    prevTime = GetTime();
}

bool Settings::EventTrigger(double interval) {
    currTime = GetTime();
    if (currTime - prevTime >= interval) {
        prevTime = currTime;
        return true;
    }
    return false;
}
