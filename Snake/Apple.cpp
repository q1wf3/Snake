// Apple.cpp

#include "Apple.h"
#include <cstdlib>

Apple::Apple(int width, int height) { // Инициализирует координаты яблока случайными значениями внутри границ игрового поля
    x = rand() % (width - 2) + 1;
    y = rand() % (height - 2) + 1;
}

int Apple::getX() { // Метод для получения координаты x яблока
    return x;
}

int Apple::getY() { // Метод для получения координаты y яблока
    return y;
}
