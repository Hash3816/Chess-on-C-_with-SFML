#pragma once
#include <vector>
#include "coordinates.h"
#include "piece_type.h"
#include "colors.h"

class Chess_Board;

class Piece {
protected:
    Color color;
public:
    Coordinates coord;

    virtual std::vector<Coordinates> get_possible_moves(Chess_Board& board) const = 0;
    virtual Piece_Type get_type() const = 0;
    virtual ~Piece() = default;

    Piece(Coordinates coord, Color color)
        : coord(coord), color(color) {

    }

    Color get_color_piece() const{
        return this->color;
    }
};