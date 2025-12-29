#pragma once
#include "cell.h"

class Chess_Board {
public:
    std::vector<std::vector<Cell>> matrix_pieces;

    Coordinates cords_white_king;
    Coordinates cords_black_king;
    bool mate;

    bool is_check(Color color_current_player);

    Chess_Board();
    ~Chess_Board();

    Chess_Board(const Chess_Board&) = delete;
    Chess_Board& operator=(const Chess_Board&) = delete;

    void set_default_placement();
    void set_default();
};
