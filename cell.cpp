#include "cell.h"
#include "pieces.h"





Cell::~Cell() {
}
Cell::Cell(Color color, Coordinates coord)
    : color(color), coord(coord), piece(nullptr), is_empty(true)
{
};
void Cell::set_piece(Piece_Type type, Color piece_color) {
    Coordinates piece_coord = this->coord;

    switch (type) {
    case Piece_Type::Pawn:
        piece = std::make_unique<Pawn>(piece_coord, piece_color);
        break;
    case Piece_Type::Knight:
        piece = std::make_unique<Knight>(piece_coord, piece_color);
        break;
    case Piece_Type::Bishop:
        piece = std::make_unique<Bishop>(piece_coord, piece_color);
        break;
    case Piece_Type::Rook:
        piece = std::make_unique<Rook>(piece_coord, piece_color);
        break;
    case Piece_Type::Queen:
        piece = std::make_unique<Queen>(piece_coord, piece_color);
        break;
    case Piece_Type::King:
        piece = std::make_unique<King>(piece_coord, piece_color);
        break;
    default:
        piece.reset();
        break;
    }

    is_empty = (piece == nullptr) ? true : false;
}

void Cell::del_piece() {
    piece.reset();
    is_empty = true;
}