#pragma once
#include <memory>
#include "virtual_piece.h"    

class Cell {
private:
    Coordinates coord;

public:
    Color color;
    std::unique_ptr<Piece> piece;
    bool is_empty;

    Cell(const Cell&) = delete;
    Cell& operator=(const Cell&) = delete;

    Cell(Cell&&) noexcept = default;
    Cell& operator=(Cell&&) noexcept = default;

    
    ~Cell();
    Cell(Color color, Coordinates coord);
    // Основные методы
    void set_piece(Piece_Type type, Color piece_color);
    void del_piece();

    Color get_color_cell() const {
        return this->color;
    }
    Coordinates get_coordinates_cell() const {
        return this->coord;
    }

};
