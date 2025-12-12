#pragma once
#include "chess_board.h"

class Pawn : public Piece {
public:
    using Piece::Piece;
    Piece_Type get_type() const{ return Piece_Type::Pawn; }
    std::vector<Coordinates> get_possible_moves(Chess_Board& board) const override;
};

class Knight : public Piece {
public:
    using Piece::Piece;
    Piece_Type get_type() const{ return Piece_Type::Knight; }
    std::vector<Coordinates> get_possible_moves(Chess_Board& board) const override;
};

class Bishop : public Piece {
public:
    using Piece::Piece;
    Piece_Type get_type() const{ return Piece_Type::Bishop; }
    std::vector<Coordinates> get_possible_moves(Chess_Board& board) const override;
};

class Rook : public Piece {
public:
    using Piece::Piece;
    Piece_Type get_type() const{ return Piece_Type::Rook; }
    std::vector<Coordinates> get_possible_moves(Chess_Board& board) const override;
};

class Queen : public Piece {
public:
    using Piece::Piece;
    Piece_Type get_type() const{ return Piece_Type::Queen; }
    std::vector<Coordinates> get_possible_moves(Chess_Board& board) const override;
};

class King : public Piece {
public:
    using Piece::Piece;
    Piece_Type get_type() const{ return Piece_Type::King; }
    std::vector<Coordinates> get_possible_moves(Chess_Board& board) const override;
};
