#ifndef SNAKE_H
#define SNAKE_H

class Snake {
private:
    int* array_X;
    int* array_Y;
    int length;
    int max_length;
public:
    Snake(int width, int height, int maxLength);
    ~Snake();
    int* getX();
    int* getY();
    int getLength();
    void increaseLength(int x, int y);
};

#endif
