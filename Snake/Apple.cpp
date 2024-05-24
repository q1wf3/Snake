// Apple.cpp

#include "Apple.h"
#include <cstdlib>

Apple::Apple(int width, int height) {
    x = rand() % (width - 2) + 1;
    y = rand() % (height - 2) + 1;
}

int Apple::getX() {
    return x;
}

int Apple::getY() {
    return y;
}
