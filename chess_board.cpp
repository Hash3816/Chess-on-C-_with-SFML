#include "chess_board.h"
#include "cell.h"
#include "pieces.h"

// Конструктор: создаём матрицу с базовой расстановкой фигур, и сохраняем начальные координаты королей
Chess_Board::Chess_Board() {
    {
        matrix_pieces.resize(8);

        for (int y = 0; y < 8; ++y)
        {
            matrix_pieces[y].reserve(8);

            for (int x = 0; x < 8; ++x)
            {
                Color cell_color = ((x + y) % 2 == 0)
                    ? Color::Black   // чётные поля — чёрные
                    : Color::White;  // нечётные — белые

                matrix_pieces[y].emplace_back(Cell(cell_color, Coordinates(y, x)));
            }
        }

        set_default_placement();

    }

    cords_white_king = Coordinates(0, 4);
    cords_black_king = Coordinates(7, 4);
    mate = false;
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

void Chess_Board::set_default() {
    for (int y = 0; y < 8; y++) { //Отчистка прошлого состояния доски
        for (int x = 0; x < 8; x++) {
            if (!matrix_pieces[y][x].is_empty) {
                matrix_pieces[y][x].del_piece();
            }
        }
    }

    this->set_default_placement();
    this->cords_white_king = Coordinates(0, 4);
    this->cords_black_king = Coordinates(7, 4);
    this->mate = false;
}

bool Chess_Board::is_check(Color color_current_player) {
    /// Проверка на шах

    Coordinates cords_king;

    if (color_current_player == Color::White) {
        cords_king = this->cords_white_king;
    }
    else {
        cords_king = this->cords_black_king;
    }

    Cell& cell_king = matrix_pieces[cords_king.y][cords_king.x];

    // Проверка всех направлений откуда может быть шах
    int x = cords_king.x;
    int y = cords_king.y;

    while (y + 1 <= 7) {// Спереди
        y++;

        if (this->matrix_pieces[y][x].is_empty) {

            continue;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() == cell_king.piece->get_color_piece()) {

            break;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() != cell_king.piece->get_color_piece()) {

            std::vector<Coordinates> cords_move_enemy = this->matrix_pieces[y][x].piece->get_possible_moves(*this);

            for (auto cord_move_enemy : cords_move_enemy) {

                if ((cord_move_enemy.x == cords_king.x) && (cord_move_enemy.y == cords_king.y)) {

                    return true;
                }
            }
            break;
        }
    }
    y = cords_king.y;

    while (y - 1 >= 0) {
        y--;

        if (this->matrix_pieces[y][x].is_empty) {
            continue;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() == cell_king.piece->get_color_piece()) {

            break;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() != cell_king.piece->get_color_piece()) {

            std::vector<Coordinates> cords_move_enemy = matrix_pieces[y][x].piece->get_possible_moves(*this);

            for (auto cord_move_enemy : cords_move_enemy) {

                if ((cord_move_enemy.x == cords_king.x) && (cord_move_enemy.y == cords_king.y)) {
                    return true;
                }
            }
            break;
        }
    }

    y = cords_king.y;

    while (x - 1 >= 0) {
        x--;

        if (this->matrix_pieces[y][x].is_empty) {
            continue;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() == cell_king.piece->get_color_piece()) {
            break;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() != cell_king.piece->get_color_piece()) {

            std::vector<Coordinates> cords_move_enemy = matrix_pieces[y][x].piece->get_possible_moves(*this);

            for (auto cord_move_enemy : cords_move_enemy) {

                if ((cord_move_enemy.x == cords_king.x) && (cord_move_enemy.y == cords_king.y)) {
                    return true;
                }
            }
            break;
        }

    }

    x = cords_king.x;

    while (x + 1 <= 7) {
        x++;

        if (this->matrix_pieces[y][x].is_empty) {
            continue;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() == cell_king.piece->get_color_piece()) {
            break;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() != cell_king.piece->get_color_piece()) {

            std::vector<Coordinates> cords_move_enemy = this->matrix_pieces[y][x].piece->get_possible_moves(*this);

            for (auto cord_move_enemy : cords_move_enemy) {

                if ((cord_move_enemy.x == cords_king.x) && (cord_move_enemy.y == cords_king.y)) {
                    return true;
                }
            }
            break;
        }

    }

    x = cords_king.x;

    while (x - 1 >= 0 && y + 1 <= 7) {
        x--;
        y++;

        if (this->matrix_pieces[y][x].is_empty) {
            continue;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() == cell_king.piece->get_color_piece()) {
            break;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() != cell_king.piece->get_color_piece()) {

            std::vector<Coordinates> cords_move_enemy = this->matrix_pieces[y][x].piece->get_possible_moves(*this);

            for (auto cord_move_enemy : cords_move_enemy) {

                if ((cord_move_enemy.x == cords_king.x) && (cord_move_enemy.y == cords_king.y)) {
                    return true;
                }
            }
            break;
        }
    }

    x = cords_king.x;
    y = cords_king.y;

    while (x + 1 <= 7 && y + 1 <= 7) { // Правая верхняя диагональ
        x++;
        y++;

        if (this->matrix_pieces[y][x].is_empty) {
            continue;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() == cell_king.piece->get_color_piece()) {
            break;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() != cell_king.piece->get_color_piece()) {

            std::vector<Coordinates> cords_move_enemy = this->matrix_pieces[y][x].piece->get_possible_moves(*this);

            for (auto cord_move_enemy : cords_move_enemy) {

                if ((cord_move_enemy.x == cords_king.x) && (cord_move_enemy.y == cords_king.y)) {
                    return true;
                }
            }
            break;
        }
    }

    x = cords_king.x;
    y = cords_king.y;

    while (x + 1 <= 7 && y - 1 >= 0) { // Правая нижняя диагональ
        x++;
        y--;

        if (this->matrix_pieces[y][x].is_empty) {
            continue;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() == cell_king.piece->get_color_piece()) {
            break;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() != cell_king.piece->get_color_piece()) {

            std::vector<Coordinates> cords_move_enemy = this->matrix_pieces[y][x].piece->get_possible_moves(*this);

            for (auto cord_move_enemy : cords_move_enemy) {

                if ((cord_move_enemy.x == cords_king.x) && (cord_move_enemy.y == cords_king.y)) {
                    return true;
                }
            }
            break;
        }
    }

    x = cords_king.x;
    y = cords_king.y;

    while (x - 1 >= 0 && y - 1 >= 0) { // Левая нижняя диагональ
        x--;
        y--;

        if (this->matrix_pieces[y][x].is_empty) {
            continue;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() == cell_king.piece->get_color_piece()) {
            break;
        }

        else if (this->matrix_pieces[y][x].piece->get_color_piece() != cell_king.piece->get_color_piece()) {

            std::vector<Coordinates> cords_move_enemy = this->matrix_pieces[y][x].piece->get_possible_moves(*this);

            for (auto cord_move_enemy : cords_move_enemy) {

                if ((cord_move_enemy.x == cords_king.x) && (cord_move_enemy.y == cords_king.y)) {
                    return true;
                }
            }
            break;
        }
    }

    x = cords_king.x;
    y = cords_king.y;

    //Конь
    if (cords_king.y + 2 <= 7 && cords_king.x - 1 >= 0) {
        if (this->matrix_pieces[cords_king.y + 2][cords_king.x - 1].is_empty) {
            //Ничего
        }
        else if (this->matrix_pieces[cords_king.y + 2][cords_king.x - 1].piece->get_color_piece() != cell_king.piece->get_color_piece()
            && this->matrix_pieces[cords_king.y + 2][cords_king.x - 1].piece->get_type() == Piece_Type::Knight) {
            return true;
        }
    }

    if (cords_king.y + 2 <= 7 && cords_king.x + 1 <= 7) {
        if (this->matrix_pieces[cords_king.y + 2][cords_king.x + 1].is_empty) {
            //Ничего
        }
        else if (this->matrix_pieces[cords_king.y + 2][cords_king.x + 1].piece->get_color_piece() != cell_king.piece->get_color_piece()
            && this->matrix_pieces[cords_king.y + 2][cords_king.x + 1].piece->get_type() == Piece_Type::Knight) {
            return true;
        }
    }


    if (cords_king.y - 2 >= 0 && cords_king.x - 1 >= 0) {
        if (this->matrix_pieces[cords_king.y - 2][cords_king.x - 1].is_empty) {
            //Ничего
        }
        else if (this->matrix_pieces[cords_king.y - 2][cords_king.x - 1].piece->get_color_piece() != cell_king.piece->get_color_piece()
            && this->matrix_pieces[cords_king.y - 2][cords_king.x - 1].piece->get_type() == Piece_Type::Knight) {
            return true;
        }
    }

    if (cords_king.y - 2 >= 0 && cords_king.x + 1 <= 7) {
        if (this->matrix_pieces[cords_king.y - 2][cords_king.x + 1].is_empty) {
            //Ничего
        }
        else if (this->matrix_pieces[cords_king.y - 2][cords_king.x + 1].piece->get_color_piece() != cell_king.piece->get_color_piece()
            && this->matrix_pieces[cords_king.y - 2][cords_king.x + 1].piece->get_type() == Piece_Type::Knight) {
            return true;
        }
    }

    if (cords_king.y + 1 <= 7 && cords_king.x + 2 <= 7) {
        if (this->matrix_pieces[cords_king.y + 1][cords_king.x + 2].is_empty) {
            //Ничего
        }
        else if (this->matrix_pieces[cords_king.y + 1][cords_king.x + 2].piece->get_color_piece() != cell_king.piece->get_color_piece()
            && this->matrix_pieces[cords_king.y + 1][cords_king.x + 2].piece->get_type() == Piece_Type::Knight) {
            return true;
        }
    }

    if (cords_king.y + 1 <= 7 && cords_king.x - 2 >= 0) {
        if (this->matrix_pieces[cords_king.y + 1][cords_king.x - 2].is_empty) {
            //Ничего
        }
        else if (this->matrix_pieces[cords_king.y + 1][cords_king.x - 2].piece->get_color_piece() != cell_king.piece->get_color_piece()
            && this->matrix_pieces[cords_king.y + 1][cords_king.x - 2].piece->get_type() == Piece_Type::Knight) {
            return true;
        }
    }

    if (cords_king.y - 1 >= 0 && cords_king.x - 2 >= 0) {
        if (this->matrix_pieces[cords_king.y - 1][cords_king.x - 2].is_empty) {
            //Ничего
        }
        else if (this->matrix_pieces[cords_king.y - 1][cords_king.x - 2].piece->get_color_piece() != cell_king.piece->get_color_piece()
            && this->matrix_pieces[cords_king.y - 1][cords_king.x - 2].piece->get_type() == Piece_Type::Knight) {
            return true;
        }
    }

    if (cords_king.y - 1 >= 0 && cords_king.x + 2 <= 7) {
        if (this->matrix_pieces[cords_king.y - 1][cords_king.x + 2].is_empty) {
            //Ничего
        }
        else if (this->matrix_pieces[cords_king.y - 1][cords_king.x + 2].piece->get_color_piece() != cell_king.piece->get_color_piece()
            && this->matrix_pieces[cords_king.y - 1][cords_king.x + 2].piece->get_type() == Piece_Type::Knight) {
            return true;
        }
    }

    return false; // Шах не найден
}