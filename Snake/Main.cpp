#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include "Apple.h"
#include "Snake.h"

using namespace std;

int main() {
    srand(time(0)); // запуск генератора случайных чисел
    system("title Snake Game");
    system("mode con cols=70 lines=31"); // установка размеров окна консоли
    MoveWindow(GetConsoleWindow(), 50, 50, 2000, 2000, true);
    const int width = 50, height = 30; // размеры поля, по которому бегает змейка
    const int max_length = 50; // установка максимальной длины "змейки"

    Apple apple(width, height);
    Snake snake(width, height, max_length);

    int length = snake.getLength();
    int* array_X = snake.getX();
    int* array_Y = snake.getY();

    int dx = 1, dy = 0; // создание смещений по осям для движения "змейки"
    int X_apple = apple.getX();
    int Y_apple = apple.getY();
    int score = 0; // счетчик очков
    int sleep_time = 100; // переменная частоты кадров 
    time_t startTime; // переменная для записи времени начала игры

    char snakeSymbol = '*';
    char appleSymbol = 'o';
    char headSymbol = 1;
    COORD c; // объект для хранения координат
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci = { sizeof(cci), false };
    SetConsoleCursorInfo(h, &cci);
    SetConsoleTextAttribute(h, 4); // установка цвета, которым рисуется рамка поля
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char s;
            if (x == 0 && y == 0)
                s = '|';
            else if (x == 0 && y == height - 1) // нижний левый угол
                s = '|';
            else if (y == 0 && x == width - 1) // верхний правый угол
                s = '|';
            else if (y == height - 1 && x == width - 1) // нижний правый угол
                s = '|';
            else if (y == 0 || y == height - 1) // верхняя и нижняя граница поля
                s = '_';
            else if (x == 0 || x == width - 1) // левая и правая граница поля
                s = '|';
            else s = ' '; //означает пустую область поля
            std::cout << s; // выводим символ
        }
        std::cout << "\n";
    }

    c.X = X_apple;
    c.Y = Y_apple;
    SetConsoleCursorPosition(h, c);
    SetConsoleTextAttribute(h, 12); // устанавливаем красный цвет для отрисовки "яблока"
    std::cout << appleSymbol; // отображение символа "яблока"

    c.X = array_X[0]; // связываем объект координат со стартовой позицией "змейки"
    c.Y = array_Y[0];
    SetConsoleCursorPosition(h, c);
    SetConsoleTextAttribute(h, 10); // устанавливаем зеленый цвет для отрисовки "змейки"
    std::cout << headSymbol; // отображаем символ головы "змейки"

    bool flag = true; // переменная для управления ходом цикла

    time(&startTime); // записываем время начала игры

    do // собственно цикл игры
    {
        Sleep(sleep_time);

        if (_kbhit()) // проверяем, была ли нажата какая-либо клавиша и запускаем её обработку в случае ИСТИНЫ
        {
            int k = _getch(); // считываем код клавиши из буфера
            if (k == 0 || k == 224) // если первый код - вспомогательный, считываем второй код
                k = _getch();
            switch (k) // пропускаем код нажатой клавиши внутрь оператора выбора
            {
            case 80:
                dy = 1;
                dx = 0;
                break;
            case 72:
                dy = -1;
                dx = 0;
                break;
            case 75:
                dy = 0;
                dx = -1;
                break;
            case 77:
                dy = 0;
                dx = 1;
                break;
            case 27:
                flag = false;
                break;
            }
        }

        int X = array_X[length - 1] + dx; // определяем значение абсциссы головы "змейки" после смещения
        int Y = array_Y[length - 1] + dy;
        if (X == 0 || X == width - 1 || Y == 0 || Y == height - 1) // проверка на достижение границ поля
        {
            flag = false;
        }
        else if (X == X_apple && Y == Y_apple) // проверка на достижение "яблока"
        {
            score += 10; // увеличение счета
            snake.increaseLength(X, Y); // увеличение длины "змейки"
            length = snake.getLength(); // обновляем длину змейки
            array_X = snake.getX(); // обновляем массивы координат X и Y змейки

            Apple newApple(width, height); // создаем новое яблоко
            X_apple = newApple.getX();
            Y_apple = newApple.getY();
            c.X = X_apple;
            c.Y = Y_apple;
            SetConsoleCursorPosition(h, c);
            SetConsoleTextAttribute(h, 12); // установка цвета в красный
            std::cout << appleSymbol; // отображение символа "яблока"
            SetConsoleTextAttribute(h, 10); // обратная установка цвета в зеленый - для дальнейшего отображения "змейки"
        }
        else // случай, когда голова "змейки" оказалась на новой пустой позиции
        {
            int i = 1;
            for (; i < length; i++)
                if (X == array_X[i] && Y == array_Y[i]) // если совпадение найдено в цикле - прерываемся
                    break;
            if (i < length)
                break;
            else
            {
                c.X = array_X[0];
                c.Y = array_Y[0];
                SetConsoleCursorPosition(h, c);
                std::cout << ' ';

                if (length > 1) // если длина змейки больше 
                {
                    c.X = array_X[length - 1];
                    c.Y = array_Y[length - 1];
                    SetConsoleCursorPosition(h, c);
                    putchar(snakeSymbol); // выводим символ тела "змейки"
                }

                for (int i = 0; i < length - 1; i++)
                {
                    array_X[i] = array_X[i + 1];
                    array_Y[i] = array_Y[i + 1];
                }

                array_X[length - 1] = X; // устанавливаем новую позицию головы "змейки"
                array_Y[length - 1] = Y;
                c.X = X;
                c.Y = Y;
                SetConsoleCursorPosition(h, c);
                std::cout << headSymbol; // отображаем символ головы "змейки"
            }
        }
        // Выводим счет на экран
        c.X = 0;
        c.Y = height;
        SetConsoleCursorPosition(h, c);
        std::cout << "Score: " << score;
    } while (flag); // выходим из цикла, если сброшена управляющая переменная
    time_t endTime; // переменная для записи времени окончания игры
    time(&endTime); // записываем время окончания игры
    double timePlayed = difftime(endTime, startTime); // вычисляем время игры

    system("cls"); // очищаем экран
    std::cout << "GAME OVER\n"; // сообщение о конце игры
    std::cout << "Final Score: " << score << "\n"; // вывод итогового счета
    std::cout << "Time Played: " << timePlayed << " seconds\n"; // вывод времени игры

    return 0;
}