// Snake.cpp

#include "Snake.h"

Snake::Snake(int width, int height, int maxLength) {
    max_length = maxLength;
    length = 1;
    array_X = new int[max_length];
    array_Y = new int[max_length];
    array_X[0] = width / 2;
    array_Y[0] = height / 2;
}

Snake::~Snake() {
    delete[] array_X;
    delete[] array_Y;
}

int* Snake::getX() {
    return array_X;
}

int* Snake::getY() {
    return array_Y;
}

int Snake::getLength() {
    return length;
}

void Snake::increaseLength(int x, int y) {
    if (length < max_length) {
        length++;
        array_X[length - 1] = x;
        array_Y[length - 1] = y;
    }
}
