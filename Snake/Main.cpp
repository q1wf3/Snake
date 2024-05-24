#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include "Apple.h"
#include "Snake.h"

using namespace std;

int main() {
    srand(time(0)); // ������ ���������� ��������� �����
    system("title Snake Game");
    system("mode con cols=70 lines=31"); // ��������� �������� ���� �������
    MoveWindow(GetConsoleWindow(), 50, 50, 2000, 2000, true);
    const int width = 50, height = 30; // ������� ����, �� �������� ������ ������
    const int max_length = 50; // ��������� ������������ ����� "������"

    Apple apple(width, height);
    Snake snake(width, height, max_length);

    int length = snake.getLength();
    int* array_X = snake.getX();
    int* array_Y = snake.getY();

    int dx = 1, dy = 0; // �������� �������� �� ���� ��� �������� "������"
    int X_apple = apple.getX();
    int Y_apple = apple.getY();
    int score = 0; // ������� �����
    int sleep_time = 100; // ���������� ������� ������ 
    time_t startTime; // ���������� ��� ������ ������� ������ ����

    char snakeSymbol = '*';
    char appleSymbol = 'o';
    char headSymbol = 1;
    COORD c; // ������ ��� �������� ���������
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci = { sizeof(cci), false };
    SetConsoleCursorInfo(h, &cci);
    SetConsoleTextAttribute(h, 4); // ��������� �����, ������� �������� ����� ����
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char s;
            if (x == 0 && y == 0)
                s = '|';
            else if (x == 0 && y == height - 1) // ������ ����� ����
                s = '|';
            else if (y == 0 && x == width - 1) // ������� ������ ����
                s = '|';
            else if (y == height - 1 && x == width - 1) // ������ ������ ����
                s = '|';
            else if (y == 0 || y == height - 1) // ������� � ������ ������� ����
                s = '_';
            else if (x == 0 || x == width - 1) // ����� � ������ ������� ����
                s = '|';
            else s = ' '; //�������� ������ ������� ����
            std::cout << s; // ������� ������
        }
        std::cout << "\n";
    }

    c.X = X_apple;
    c.Y = Y_apple;
    SetConsoleCursorPosition(h, c);
    SetConsoleTextAttribute(h, 12); // ������������� ������� ���� ��� ��������� "������"
    std::cout << appleSymbol; // ����������� ������� "������"

    c.X = array_X[0]; // ��������� ������ ��������� �� ��������� �������� "������"
    c.Y = array_Y[0];
    SetConsoleCursorPosition(h, c);
    SetConsoleTextAttribute(h, 10); // ������������� ������� ���� ��� ��������� "������"
    std::cout << headSymbol; // ���������� ������ ������ "������"

    bool flag = true; // ���������� ��� ���������� ����� �����

    time(&startTime); // ���������� ����� ������ ����

    do // ���������� ���� ����
    {
        Sleep(sleep_time);

        if (_kbhit()) // ���������, ���� �� ������ �����-���� ������� � ��������� � ��������� � ������ ������
        {
            int k = _getch(); // ��������� ��� ������� �� ������
            if (k == 0 || k == 224) // ���� ������ ��� - ���������������, ��������� ������ ���
                k = _getch();
            switch (k) // ���������� ��� ������� ������� ������ ��������� ������
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

        int X = array_X[length - 1] + dx; // ���������� �������� �������� ������ "������" ����� ��������
        int Y = array_Y[length - 1] + dy;
        if (X == 0 || X == width - 1 || Y == 0 || Y == height - 1) // �������� �� ���������� ������ ����
        {
            flag = false;
        }
        else if (X == X_apple && Y == Y_apple) // �������� �� ���������� "������"
        {
            score += 10; // ���������� �����
            snake.increaseLength(X, Y); // ���������� ����� "������"
            length = snake.getLength(); // ��������� ����� ������
            array_X = snake.getX(); // ��������� ������� ��������� X � Y ������

            Apple newApple(width, height); // ������� ����� ������
            X_apple = newApple.getX();
            Y_apple = newApple.getY();
            c.X = X_apple;
            c.Y = Y_apple;
            SetConsoleCursorPosition(h, c);
            SetConsoleTextAttribute(h, 12); // ��������� ����� � �������
            std::cout << appleSymbol; // ����������� ������� "������"
            SetConsoleTextAttribute(h, 10); // �������� ��������� ����� � ������� - ��� ����������� ����������� "������"
        }
        else // ������, ����� ������ "������" ��������� �� ����� ������ �������
        {
            int i = 1;
            for (; i < length; i++)
                if (X == array_X[i] && Y == array_Y[i]) // ���� ���������� ������� � ����� - �����������
                    break;
            if (i < length)
                break;
            else
            {
                c.X = array_X[0];
                c.Y = array_Y[0];
                SetConsoleCursorPosition(h, c);
                std::cout << ' ';

                if (length > 1) // ���� ����� ������ ������ 
                {
                    c.X = array_X[length - 1];
                    c.Y = array_Y[length - 1];
                    SetConsoleCursorPosition(h, c);
                    putchar(snakeSymbol); // ������� ������ ���� "������"
                }

                for (int i = 0; i < length - 1; i++)
                {
                    array_X[i] = array_X[i + 1];
                    array_Y[i] = array_Y[i + 1];
                }

                array_X[length - 1] = X; // ������������� ����� ������� ������ "������"
                array_Y[length - 1] = Y;
                c.X = X;
                c.Y = Y;
                SetConsoleCursorPosition(h, c);
                std::cout << headSymbol; // ���������� ������ ������ "������"
            }
        }
        // ������� ���� �� �����
        c.X = 0;
        c.Y = height;
        SetConsoleCursorPosition(h, c);
        std::cout << "Score: " << score;
    } while (flag); // ������� �� �����, ���� �������� ����������� ����������
    time_t endTime; // ���������� ��� ������ ������� ��������� ����
    time(&endTime); // ���������� ����� ��������� ����
    double timePlayed = difftime(endTime, startTime); // ��������� ����� ����

    system("cls"); // ������� �����
    std::cout << "GAME OVER\n"; // ��������� � ����� ����
    std::cout << "Final Score: " << score << "\n"; // ����� ��������� �����
    std::cout << "Time Played: " << timePlayed << " seconds\n"; // ����� ������� ����

    return 0;
}