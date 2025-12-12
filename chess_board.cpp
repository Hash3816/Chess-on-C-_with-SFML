#include "chess_board.h"
#include "cell.h"
#include "pieces.h"

//  онструктор: создаЄм матрицу и заполн€ем клетками, затем ставим фигуры
Chess_Board::Chess_Board() {
    {
        matrix_pieces.resize(8);

        for (int y = 0; y < 8; ++y)
        {
            matrix_pieces[y].reserve(8);

            for (int x = 0; x < 8; ++x)
            {
                Color cell_color = ((x + y) % 2 == 0)
                    ? Color::Black   // чЄтные пол€ Ч чЄрные
                    : Color::White;  // нечЄтные Ч белые

                matrix_pieces[y].emplace_back(Cell(cell_color, Coordinates(y, x)));
            }
        }

        set_default_placement();

    }
};

    Chess_Board::~Chess_Board() {
    };

void Chess_Board::set_default_placement() {
    for (int x = 0; x < 8; x++) {
        matrix_pieces[1][x].set_piece(Piece_Type::Pawn, Color::White);
        matrix_pieces[6][x].set_piece(Piece_Type::Pawn, Color::Black);
    }

    matrix_pieces[0][0].set_piece(Piece_Type::Rook, Color::White);
    matrix_pieces[0][7].set_piece(Piece_Type::Rook, Color::White);
    matrix_pieces[7][0].set_piece(Piece_Type::Rook, Color::Black);
    matrix_pieces[7][7].set_piece(Piece_Type::Rook, Color::Black);

    matrix_pieces[0][1].set_piece(Piece_Type::Knight, Color::White);
    matrix_pieces[0][6].set_piece(Piece_Type::Knight, Color::White);
    matrix_pieces[7][1].set_piece(Piece_Type::Knight, Color::Black);
    matrix_pieces[7][6].set_piece(Piece_Type::Knight, Color::Black);

    matrix_pieces[0][2].set_piece(Piece_Type::Bishop, Color::White);
    matrix_pieces[0][5].set_piece(Piece_Type::Bishop, Color::White);
    matrix_pieces[7][2].set_piece(Piece_Type::Bishop, Color::Black);
    matrix_pieces[7][5].set_piece(Piece_Type::Bishop, Color::Black);

    matrix_pieces[0][3].set_piece(Piece_Type::Queen, Color::White);
    matrix_pieces[0][4].set_piece(Piece_Type::King, Color::White);

    matrix_pieces[7][3].set_piece(Piece_Type::Queen, Color::Black);
    matrix_pieces[7][4].set_piece(Piece_Type::King, Color::Black);
}

void Chess_Board::clear() {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (!matrix_pieces[y][x].is_empty) {
                matrix_pieces[y][x].del_piece();
            }
        }
    }
}