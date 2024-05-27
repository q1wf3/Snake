// Snake.cpp

#include "Snake.h"

Snake::Snake(int width, int height, int maxLength) { // Инициализирует массивы координат и устанавливает начальную длину и позицию змейки
    max_length = maxLength; // Устанавливает максимальную длину змейки
    length = 1; // Начальная длина змейки 
    array_X = new int[max_length]; // Создание массива для хранения координат x сегментов змейки
    array_Y = new int[max_length];
    array_X[0] = width / 2; // Установка начальной координаты x головы змейки в центре поля
    array_Y[0] = height / 2;
}
// Деструктор класса Snake

// Освобождает память, выделенную для массивов координат змейки
Snake::~Snake() {
    delete[] array_X; // Удаление массива координат x
    delete[] array_Y;
}

int* Snake::getX() { // Метод для получения массива координат x сегментов змейки
    return array_X;
}

int* Snake::getY() { // Метод для получения текущей длины змейки
    return array_Y;
}

int Snake::getLength() {
    return length;
}

void Snake::increaseLength(int x, int y) { // Метод для увеличения длины змейки и добавления нового сегмента
    if (length < max_length) {
        length++;
        array_X[length - 1] = x;
        array_Y[length - 1] = y;
    }
}
