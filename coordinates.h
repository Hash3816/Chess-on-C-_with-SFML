#pragma once

class Coordinates {
public:
    int y;
    int x;
    Coordinates() : y(-1), x(-1) {}
    Coordinates(int y_value, int x_value) : y(y_value), x(x_value) {
    };
};