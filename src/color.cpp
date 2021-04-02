
#include "defines.h"

float mapColor(float x, float y, int colorChanel) {
    if (colorChanel == RED) {
        return 0.8f;
    } else if (colorChanel == GREEN) {
        return 0.7f;
    } else if (colorChanel == BLUE) {
        return 0.5f;
    } else if (colorChanel == ALPHA) {
        return 1.0f;
    }
    return 0.0f;
}
