#pragma once
#include "cell.h"

class Chess_Board {
public:
    std::vector<std::vector<Cell>> matrix_pieces;

    Chess_Board();
    ~Chess_Board();

    Chess_Board(const Chess_Board&) = delete;
    Chess_Board& operator=(const Chess_Board&) = delete;

    void set_default_placement();
    void clear();
};
