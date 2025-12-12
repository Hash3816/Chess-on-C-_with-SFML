#include "chess_board.h"
#include "pieces.h"


std::vector<Coordinates> Pawn::get_possible_moves(Chess_Board& board) const{
    std::vector<Coordinates> possible_moves;
    Coordinates coord_pawn = this->coord;

    if (this->color == Color::White) {
        if (coord_pawn.y == 1) { // Случай хода с начальной позиции
            for (int y = 2; y <= 3; y++) {
                if (board.matrix_pieces[y][coord_pawn.x].is_empty) {
                    possible_moves.push_back(Coordinates(y, coord_pawn.x));
                }
                else { //Вперёд пешка рубить не может
                    break;
                }
            }
            // Ходы по диагонали на 1 в случае встречи противника
            if (coord_pawn.x - 1 >= 0 && coord_pawn.y + 1 <= 7 && (!board.matrix_pieces[coord_pawn.y + 1][coord_pawn.x - 1].is_empty)
                && board.matrix_pieces[coord_pawn.y + 1][coord_pawn.x - 1].piece->get_color_piece() != this->color) {
                possible_moves.push_back(Coordinates(coord_pawn.y + 1, coord_pawn.x - 1));
            }

           if (coord_pawn.x + 1 <= 7 && coord_pawn.y + 1 <= 7 && (!board.matrix_pieces[coord_pawn.y + 1][coord_pawn.x + 1].is_empty)
                && board.matrix_pieces[coord_pawn.y + 1][coord_pawn.x + 1].piece->get_color_piece() != this->color) {
                possible_moves.push_back(Coordinates(coord_pawn.y + 1, coord_pawn.x + 1));
            }
        }
        //Обычные ходы
        else {
            if (coord_pawn.y + 1 <= 7 && board.matrix_pieces[coord_pawn.y + 1][coord_pawn.x].is_empty) { // Ход вперёд
                possible_moves.push_back(Coordinates(coord_pawn.y + 1, coord_pawn.x));
            }

            // Ходы по диагонали на 1 в случае встречи противника
            if (coord_pawn.x - 1 >= 0 && coord_pawn.y + 1 <= 7 && (!board.matrix_pieces[coord_pawn.y + 1][coord_pawn.x - 1].is_empty)
                && board.matrix_pieces[coord_pawn.y + 1][coord_pawn.x - 1].piece->get_color_piece() != this->color) {
                possible_moves.push_back(Coordinates(coord_pawn.y + 1, coord_pawn.x - 1));
            }

            if (coord_pawn.x + 1 <= 7 && coord_pawn.y + 1 <= 7 && (!board.matrix_pieces[coord_pawn.y + 1][coord_pawn.x + 1].is_empty)
                && board.matrix_pieces[coord_pawn.y + 1][coord_pawn.x + 1].piece->get_color_piece() != this->color) {
                possible_moves.push_back(Coordinates(coord_pawn.y + 1, coord_pawn.x + 1));
            }
        }
    }
    if (this->color == Color::Black) {
        if (coord_pawn.y == 6) { // Первый двойной ход чёрной пешки
            for (int y = 5; y >= 4; y--) {
                if (board.matrix_pieces[y][coord_pawn.x].is_empty) {
                    possible_moves.push_back(Coordinates(y, coord_pawn.x));
                }
                else {
                    break;
                }
            }
            // Ходы по диагонали на 1 в случае встречи противника
            if (coord_pawn.x - 1 >= 0 && coord_pawn.y - 1 >= 0 && !board.matrix_pieces[coord_pawn.y - 1][coord_pawn.x - 1].is_empty
                && board.matrix_pieces[coord_pawn.y - 1][coord_pawn.x - 1].piece->get_color_piece() == Color::White) {
                possible_moves.push_back(Coordinates(coord_pawn.y - 1, coord_pawn.x - 1));
            }
            if (coord_pawn.x + 1 <= 7 && coord_pawn.y - 1 >= 0 && !board.matrix_pieces[coord_pawn.y - 1][coord_pawn.x + 1].is_empty
                && board.matrix_pieces[coord_pawn.y - 1][coord_pawn.x + 1].piece->get_color_piece() == Color::White) {
                possible_moves.push_back(Coordinates(coord_pawn.y - 1, coord_pawn.x + 1));
            }
        }
        //Обычные ходы
        else {
            if (coord_pawn.y - 1 >= 0 && board.matrix_pieces[coord_pawn.y - 1][coord_pawn.x].is_empty) { // Ход вперёд
                possible_moves.push_back(Coordinates(coord_pawn.y - 1, coord_pawn.x));
            }

            // Ходы по диагонали на 1 в случае встречи противника
            if (coord_pawn.x - 1 >= 0 && coord_pawn.y - 1 >= 0 && !board.matrix_pieces[coord_pawn.y - 1][coord_pawn.x - 1].is_empty
                && board.matrix_pieces[coord_pawn.y - 1][coord_pawn.x - 1].piece->get_color_piece() == Color::White) {
                possible_moves.push_back(Coordinates(coord_pawn.y - 1, coord_pawn.x - 1));
            }
            if (coord_pawn.x + 1 <= 7 && coord_pawn.y - 1 >= 0 && !board.matrix_pieces[coord_pawn.y - 1][coord_pawn.x + 1].is_empty
                && board.matrix_pieces[coord_pawn.y - 1][coord_pawn.x + 1].piece->get_color_piece() == Color::White) {
                possible_moves.push_back(Coordinates(coord_pawn.y - 1, coord_pawn.x + 1));
            }
        }

    }

    return possible_moves;
};


std::vector<Coordinates> Knight::get_possible_moves(Chess_Board& board) const{
    std::vector<Coordinates> possible_moves;
    Coordinates coord_knight = this->coord;

    if (coord_knight.y + 2 <= 7 && coord_knight.x - 1 >= 0 
        && board.matrix_pieces[coord_knight.y + 2][coord_knight.x - 1].is_empty) { // Вперёд влево
        possible_moves.push_back(Coordinates(coord_knight.y + 2, coord_knight.x - 1));
    }
    else if (coord_knight.y + 2 <= 7 && coord_knight.x - 1 >= 0 
        && board.matrix_pieces[coord_knight.y + 2][coord_knight.x - 1].piece->get_color_piece() != this->color) {
        possible_moves.push_back(Coordinates(coord_knight.y + 2, coord_knight.x - 1));
    }

    if (coord_knight.y + 2 <= 7 && coord_knight.x + 1 <= 7 
        && board.matrix_pieces[coord_knight.y + 2][coord_knight.x + 1].is_empty) { // Вперёд вправо
        possible_moves.push_back(Coordinates(coord_knight.y + 2, coord_knight.x + 1));
    }
    else if (coord_knight.y + 2 <= 7 && coord_knight.x + 1 <= 7 
        && board.matrix_pieces[coord_knight.y + 2][coord_knight.x + 1].piece->get_color_piece() != this->color) {
        possible_moves.push_back(Coordinates(coord_knight.y + 2, coord_knight.x + 1));
    }

    if (coord_knight.y - 2 >= 0 && coord_knight.x - 1 >= 0 
        && board.matrix_pieces[coord_knight.y - 2][coord_knight.x - 1].is_empty) { // Назад влево
        possible_moves.push_back(Coordinates(coord_knight.y - 2, coord_knight.x - 1));
    }
    else if (coord_knight.y - 2 >= 0 && coord_knight.x - 1 >= 0 
        && board.matrix_pieces[coord_knight.y - 2][coord_knight.x - 1].piece->get_color_piece() != this->color) {
        possible_moves.push_back(Coordinates(coord_knight.y - 2, coord_knight.x - 1));
    }

    if (coord_knight.y - 2 >= 0 && coord_knight.x + 1 <= 7 
        && board.matrix_pieces[coord_knight.y - 2][coord_knight.x + 1].is_empty) { // Назад вправо
        possible_moves.push_back(Coordinates(coord_knight.y - 2, coord_knight.x + 1));
    }
    else if (coord_knight.y - 2 >= 0 && coord_knight.x + 1 <= 7 
        && board.matrix_pieces[coord_knight.y - 2][coord_knight.x + 1].piece->get_color_piece() != this->color) {
        possible_moves.push_back(Coordinates(coord_knight.y - 2, coord_knight.x + 1));
    }

    if (coord_knight.y - 1 >= 0 && coord_knight.x + 2 <= 7
        && board.matrix_pieces[coord_knight.y - 1][coord_knight.x + 2].is_empty) { // Влево вверх
        possible_moves.push_back(Coordinates(coord_knight.y - 1, coord_knight.x + 2));
    }
    else if (coord_knight.y - 1 >= 0 && coord_knight.x + 2 <= 7
        && board.matrix_pieces[coord_knight.y - 1][coord_knight.x + 2].piece->get_color_piece() != this->color) {
        possible_moves.push_back(Coordinates(coord_knight.y - 1, coord_knight.x + 2));
    }

    if (coord_knight.y - 1 >= 0 && coord_knight.x - 2 >= 0
        && board.matrix_pieces[coord_knight.y - 1][coord_knight.x - 2].is_empty) { // Влево вниз
        possible_moves.push_back(Coordinates(coord_knight.y - 1, coord_knight.x - 2));
    }
    else if (coord_knight.y - 1 >= 0 && coord_knight.x - 2 >= 0
        && board.matrix_pieces[coord_knight.y - 1][coord_knight.x - 2].piece->get_color_piece() != this->color) {
        possible_moves.push_back(Coordinates(coord_knight.y - 1, coord_knight.x - 2));
    }

    if (coord_knight.y + 1 <= 7 && coord_knight.x - 2 >= 0
        && board.matrix_pieces[coord_knight.y + 1][coord_knight.x - 2].is_empty) { // Вправо вниз
        possible_moves.push_back(Coordinates(coord_knight.y + 1, coord_knight.x - 2));
    }
    else if (coord_knight.y + 1 <= 7 && coord_knight.x - 2 >= 0
        && board.matrix_pieces[coord_knight.y + 1][coord_knight.x - 2].piece->get_color_piece() != this->color) {
        possible_moves.push_back(Coordinates(coord_knight.y + 1, coord_knight.x - 2));
    }

    if (coord_knight.y + 1 <= 7 && coord_knight.x + 2 <= 7
        && board.matrix_pieces[coord_knight.y + 1][coord_knight.x + 2].is_empty) { // Вправо вверх
        possible_moves.push_back(Coordinates(coord_knight.y + 1, coord_knight.x + 2));
    }
    else if (coord_knight.y + 1 <= 7 && coord_knight.x + 2 <= 7
        && board.matrix_pieces[coord_knight.y + 1][coord_knight.x + 2].piece->get_color_piece() != this->color) {
        possible_moves.push_back(Coordinates(coord_knight.y + 1, coord_knight.x + 2));
    }

    return possible_moves;
};


std::vector<Coordinates> Bishop::get_possible_moves(Chess_Board& board) const{
    std::vector<Coordinates> possible_moves;
    Coordinates coord_bishop = this->coord;

    int y = coord_bishop.y;
    int x = coord_bishop.x;

    while (y + 1 <= 7 && x - 1 >= 0) { // Левая верхняя линия
        y++;
        x--;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    y = coord_bishop.y;
    x = coord_bishop.x;

    while (y + 1 <= 7 && x + 1 <= 7) { // Правая верхняя линия
        y++;
        x++;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    y = coord_bishop.y;
    x = coord_bishop.x;

    while (y - 1 >= 0 && x + 1 <= 7) { // Правая нижняя линия
        y--;
        x++;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    y = coord_bishop.y;
    x = coord_bishop.x;

    while (y - 1 >= 0 && x - 1 >= 0) { // Левая нижняя линия
        y--;
        x--;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    return possible_moves;
};


std::vector<Coordinates> Rook::get_possible_moves(Chess_Board& board) const{
    std::vector<Coordinates> possible_moves;
    Coordinates coord_rook = this->coord;

    int y = coord_rook.y;
    int x = coord_rook.x;

    while (y + 1 <= 7) { //Вверх
        y++;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    y = coord_rook.y;

    while (y - 1 >= 0) { //Вниз
        y--;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    y = coord_rook.y;

    while (x - 1 >= 0) { //Влево
        x--;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    x = coord_rook.x;

    while (x + 1 <= 7) { //Вправо
        x++;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    return possible_moves;
};


std::vector<Coordinates> Queen::get_possible_moves(Chess_Board& board) const{
    std::vector<Coordinates> possible_moves;
    Coordinates coord_queen = this->coord;

    

    int y = coord_queen.y;
    int x = coord_queen.x;

    while (y + 1 <= 7) { //Вверх
        y++;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    y = coord_queen.y;

    while (y - 1 >= 0) { //Вниз
        y--;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    y = coord_queen.y;

    while (x - 1 >= 0) { //Влево
        x--;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    x = coord_queen.x;

    while (x + 1 <= 7) { //Вправо
        x++;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    // Ходы слона

    y = coord_queen.y;
    x = coord_queen.x;

    while (y + 1 <= 7 && x - 1 >= 0) { // Левая верхняя линия
        y++;
        x--;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    y = coord_queen.y;
    x = coord_queen.x;

    while (y + 1 <= 7 && x + 1 <= 7) { // Правая верхняя линия
        y++;
        x++;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    y = coord_queen.y;
    x = coord_queen.x;

    while (y - 1 >= 0 && x + 1 <= 7) { // Правая нижняя линия
        y--;
        x++;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    y = coord_queen.y;
    x = coord_queen.x;

    while (y - 1 >= 0 && x - 1 >= 0) { // Левая нижняя линия
        y--;
        x--;

        if (board.matrix_pieces[y][x].is_empty) {
            possible_moves.push_back(Coordinates(y, x));
        }
        else if (board.matrix_pieces[y][x].piece->get_color_piece() != this->color) {
            possible_moves.push_back(Coordinates(y, x));
            break;
        }
        else {
            break;
        }
    }

    return possible_moves;
};

std::vector<Coordinates> King::get_possible_moves(Chess_Board& board) const{
    std::vector<Coordinates> possible_moves;

    Coordinates coord_king = this->coord;

    if (coord_king.y + 1 <= 7) { // Ходы спереди
        for (int x = coord_king.x - 1; x <= coord_king.x + 1; x++) {
            if ((x >= 0 && x <= 7) &&
                (board.matrix_pieces[coord_king.y + 1][x].is_empty || board.matrix_pieces[coord_king.y + 1][x].piece->get_color_piece() != this->color)) {
                possible_moves.push_back(Coordinates(coord_king.y + 1, x));
            }
        }
    }

    if (coord_king.y - 1 >= 0) { // Ходы сзади
        for (int x = coord_king.x - 1; x <= coord_king.x + 1; x++) {
            if ((x >= 0 && x <= 7) && (board.matrix_pieces[coord_king.y - 1][x].is_empty
                || board.matrix_pieces[coord_king.y - 1][x].piece->get_color_piece() != this->color)) {

                possible_moves.push_back(Coordinates(coord_king.y - 1, x));
            }
        }
    }

    if ((coord_king.x - 1 >= 0) && (board.matrix_pieces[coord_king.y][coord_king.x - 1].is_empty // Ход слева
        || board.matrix_pieces[coord_king.y][coord_king.x - 1].piece->get_color_piece() != this->color)) {

        possible_moves.push_back(Coordinates(coord_king.y, coord_king.x - 1));
    }

    if ((coord_king.x + 1 <= 7) && (board.matrix_pieces[coord_king.y][coord_king.x + 1].is_empty // Ход справа
        || board.matrix_pieces[coord_king.y][coord_king.x + 1].piece->get_color_piece() != this->color)) {

        possible_moves.push_back(Coordinates(coord_king.y, coord_king.x + 1));
    }

    return possible_moves;
};