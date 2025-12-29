#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include<string>
#include<optional>
#include <ctime>
#include <unordered_map>
#include "chess_board.h"


static std::string textureName(Piece_Type type, Color color) {
    std::string color_name = (color == Color::White) ? "white" : "black";
    switch (type) {
    case Piece_Type::Pawn:   return color_name + "_pawn";
    case Piece_Type::Knight: return color_name + "_knight";
    case Piece_Type::Bishop: return color_name + "_bishop";
    case Piece_Type::Rook:   return color_name + "_rook";
    case Piece_Type::Queen:  return color_name + "_queen";
    case Piece_Type::King:   return color_name + "_king";

    default: return "error";
    }
};

static std::unordered_map<std::string, sf::Texture>& getTextures() {
    static std::unordered_map<std::string, sf::Texture> textures;
    static bool initialized = false;
    if (!initialized) {
        initialized = true;

        const std::string base = "assets/";

        std::vector<std::string> names = {
            "white_pawn","white_knight","white_bishop","white_rook","white_queen","white_king",
            "black_pawn","black_knight","black_bishop","black_rook","black_queen","black_king"
        };

        for (const auto& name : names) {
            sf::Texture texture;
            std::string path = base + name + ".png";
            if (!texture.loadFromFile(path)) {
                std::cerr << "Warning: cannot load texture: " << path << std::endl;
                texture.create(1, 1);
            }

            textures.emplace(name, std::move(texture));
        }
    }
    return textures;
};



class Game {
private:
    Color color_current_player;

    bool first_click;

    Coordinates cords_select_piece;
    std::vector<Coordinates> rendering_coordinates;

    Chess_Board board;

public:
    std::timespec time_last_click;
    std::unordered_map<std::string, sf::Texture> textures;


    std::optional<Coordinates> getClickedCell(sf::RenderWindow& window, int cellSize)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.key.code == sf::Mouse::Left) {
                auto cords_click_mouse_x = event.mouseButton.x;
                auto cords_click_mouse_y = event.mouseButton.y;

                int x = cords_click_mouse_x / cellSize;
                int y = (640 - cords_click_mouse_y) / cellSize;

                if (x >= 0 && x < 8 && y >= 0 && y < 8)
                    while (window.pollEvent(event)) { //Отчистка буфера событий

                    }

                    return Coordinates(y, x);

            }
        }

        return std::nullopt;
    }
    bool can_click() {
        //Проверка промежутка времени между текущем событием и прошлым
        //если прошло достаточно времени, то обрабатываем событие

        std::timespec time_now;
        std::timespec_get(&time_now, TIME_UTC);

        // Преобразуем в наносекунды (секунды * 1e9 + наносекунды)
        long long current_click = static_cast<long long>(time_now.tv_sec) * 1000000000LL + time_now.tv_nsec;
        long long last_click = static_cast<long long>(this->time_last_click.tv_sec) * 1000000000LL + this->time_last_click.tv_nsec;
        // Проверяем прошло ли достаточно времени с последнего клика
        return (current_click - last_click) >= 50000000;
    }

    void draw_board(sf::RenderWindow& window, sf::Event &event) {
        const int windowSize = 640;
        const int tiles = 8;
        const float tileSize = static_cast<float>(windowSize) / tiles;

        static sf::Font font;
        font.loadFromFile("assets/DejaVuSans.ttf");

        sf::RectangleShape square(sf::Vector2f(tileSize, tileSize));

        for (int y = 0; y < tiles; ++y) {
            for (int x = 0; x < tiles; ++x) {
                Cell& cell = this->board.matrix_pieces[y][x];

                if (cell.get_color_cell() == Color::White) {
                    square.setFillColor(sf::Color(240, 217, 181));
                }
                else if (cell.get_color_cell() == Color::Black) {
                    square.setFillColor(sf::Color(181, 136, 99));
                }
                else if (cell.get_color_cell() == Color::Green) {
                    square.setFillColor(sf::Color(167, 255, 167));
                }
                else if (cell.get_color_cell() == Color::Red) {
                    square.setFillColor(sf::Color(200, 100, 100));
                }
                else {
                    square.setFillColor(sf::Color::Magenta);
                }

                square.setPosition(x * tileSize, (7 - y) * tileSize);
                window.draw(square); // отрисовка клетки

                // Отрисовка фигуры
                if (!cell.is_empty && cell.piece) {
                    Piece_Type type_piece = cell.piece->get_type();
                    Color piece_color = cell.piece->get_color_piece();
                    std::string key = textureName(type_piece, piece_color);

                    auto it = textures.find(key);
                    if (it != textures.end()) {
                        const sf::Texture& tex = it->second;

                        sf::Sprite sprite;
                        sprite.setTexture(tex, true);

                        sf::Vector2u texSize = tex.getSize();
                        if (texSize.x > 0 && texSize.y > 0) {
                            float scaleX = tileSize / static_cast<float>(texSize.x);
                            float scaleY = tileSize / static_cast<float>(texSize.y);
                            float scale = std::min(scaleX, scaleY) * 0.9f;
                            sprite.setScale(scale, scale);

                            float spriteW = texSize.x * sprite.getScale().x;
                            float spriteH = texSize.y * sprite.getScale().y;
                            float posX = x * tileSize + (tileSize - spriteW) / 2.0f;
                            float posY = (7 - y) * tileSize + (tileSize - spriteH) / 2.0f;
                            sprite.setPosition(posX, posY);

                            window.draw(sprite);
                        }
                    }
                }
            }
        }

        
        if (this->board.mate) {

            Color winner = (this->color_current_player == Color::White) ? Color::Black : Color::White;
            std::string winnerText = (winner == Color::White) ? "White wins!\nPress R to restart" : "Black wins!\nPress R to restart";

            sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(windowSize) * 0.8f, static_cast<float>(windowSize) * 0.3f));
            overlay.setFillColor(sf::Color(0, 0, 0, 160));
            overlay.setOutlineColor(sf::Color::White);
            overlay.setOutlineThickness(2.f);
            overlay.setPosition(windowSize * 0.1f, windowSize * 0.35f);


            sf::Text text;
            text.setFont(font);
            text.setString(winnerText);
            text.setCharacterSize(40);
            text.setStyle(sf::Text::Bold);

            sf::FloatRect txtRect = text.getLocalBounds();
            text.setOrigin(txtRect.left + txtRect.width / 2.0f, txtRect.top + txtRect.height / 2.0f);
            text.setPosition(windowSize / 2.0f, windowSize * 0.5f);

            window.draw(overlay);
            window.draw(text);

            if (event.key.code == sf::Keyboard::R) {
                board.set_default();
                window.clear();
                window.close();

                start_Game();
            }
        }
    }


    void start_Game() {
        this->color_current_player = Color::White;
        this->first_click = true;
        this->time_last_click.tv_sec = 0;
        this->textures = getTextures();

        sf::RenderWindow window(sf::VideoMode(640, 640), L"Шахматы", sf::Style::Default);
        window.setFramerateLimit(5);

        while (window.isOpen()) {
            sf::Event event;


            while (window.pollEvent(event)) { // Обработка пула событий

                if (!can_click()) { // Если прошло недостаточно времени между событиями, то выходим из обработки
                    clear_events(window);
                    break;
                }

                std::timespec_get(&this->time_last_click, TIME_UTC); // Сохраняем время последнего обработанного события

                if (this->board.mate) {
                    draw_board(window, event);
                    clear_events(window);
                    break;
                }

                if (event.type == sf::Event::Closed) window.close();

                if (first_click){
                    std::vector<Coordinates> possible_moves;

                    auto cords_click_1 = getClickedCell(window, 80);


                    if (!cords_click_1.has_value()) { // Клика не было
                        break;
                    }

                    // Отрисовка ходов (1 клик)
                    Cell& cell = this->board.matrix_pieces[cords_click_1->y][cords_click_1->x];

                    if (!cell.is_empty && (cell.piece->get_color_piece() == color_current_player)) {
                        possible_moves = board.matrix_pieces[cords_click_1->y][cords_click_1->x].piece->get_possible_moves(board);

                        for (Coordinates possible_cord : possible_moves) {

                            if (board.matrix_pieces[possible_cord.y][possible_cord.x].is_empty) {
                                board.matrix_pieces[possible_cord.y][possible_cord.x].color = Color::Green; // Обычный ход
                            }

                            else {
                                board.matrix_pieces[possible_cord.y][possible_cord.x].color = Color::Red; // Взятие
                            }

                        }

                    }
                    // Если есть возможные ходы
                    if (!possible_moves.empty()) {
                        this->rendering_coordinates = possible_moves;
                        this->first_click = false;
                        this->cords_select_piece = Coordinates(cords_click_1->y, cords_click_1->x);
                        break;
                    }

                }
                if (!first_click) {
                    auto cord_click_2 = getClickedCell(window, 80);

                    if (!cord_click_2.has_value()) { // Клика не было
                        break;
                    }

                    if (is_valid_move(cord_click_2)) {
                        make_move(cord_click_2);
                        clear_render_cells();
                    }
                    else {
                        // Если игрок после перового клика сделал клик не туда то он заново проводит выбор и ход
                        clear_render_cells();
                        this->first_click = true;
                        this->rendering_coordinates.clear();
                    }
                }
            }
            draw_board(window, event);
            window.display();
        }
    };


    void make_move(std::optional<Coordinates> cord_move) {

        if (board.matrix_pieces[this->cords_select_piece.y][this->cords_select_piece.x].piece->get_type() == Piece_Type::King) {

            if (board.matrix_pieces[cords_select_piece.y][cords_select_piece.x].piece->get_color_piece() == Color::White) {
                this->board.cords_white_king = Coordinates(cord_move->y, cord_move->x);
            }
            else {
                this->board.cords_black_king = Coordinates(cord_move->y, cord_move->x);
            }
        }

        // Ход на пустую клетку
        if (board.matrix_pieces[cord_move->y][cord_move->x].is_empty) {

            Color color = board.matrix_pieces[this->cords_select_piece.y][this->cords_select_piece.x].piece->get_color_piece();
            Piece_Type type_piece = board.matrix_pieces[this->cords_select_piece.y][this->cords_select_piece.x].piece->get_type();

            board.matrix_pieces[this->cords_select_piece.y][this->cords_select_piece.x].del_piece();

            board.matrix_pieces[cord_move->y][cord_move->x].set_piece(type_piece, color);
        }
        // Ход на вражескую фигуру(Т.к возможные ходы предобработатны условие того что клетка не пуста достаточно)
        else if (!board.matrix_pieces[cord_move->y][cord_move->x].is_empty) {

            Color color = board.matrix_pieces[this->cords_select_piece.y][this->cords_select_piece.x].piece->get_color_piece();
            Piece_Type type_piece = board.matrix_pieces[this->cords_select_piece.y][this->cords_select_piece.x].piece->get_type();

            board.matrix_pieces[this->cords_select_piece.y][this->cords_select_piece.x].del_piece(); // Удаляем выбранную фигуру
            board.matrix_pieces[cord_move->y][cord_move->x].del_piece(); // Удаляем  фигуру на которую будет ход

            board.matrix_pieces[cord_move->y][cord_move->x].set_piece(type_piece, color);
        }

        if (board.is_check(this->color_current_player)) { // Если игрок походил но при этом его король всё ещё находится под шахом, то он проиграл
            board.mate = true;
            return;
        }
        // Смена игрока
        this->change_player();
        this->first_click = true;
    }

    void change_player() {
        if (color_current_player == Color::White) {
            color_current_player = Color::Black;
        }
        else {
            color_current_player = Color::White;
        }
    }

    void clear_render_cells() {
        for (auto cord_cell : this->rendering_coordinates) {
            board.matrix_pieces[cord_cell.y][cord_cell.x].color = ((cord_cell.x + cord_cell.y) % 2 == 0)
                ? Color::Black   // чётные поля — чёрные
                : Color::White;  // нечётные — белые
        }

        this->rendering_coordinates.clear();
    }
    
    void clear_events(sf::Window& window) {
        sf::Event event;
        while (window.pollEvent(event)) {}
    };

    bool is_valid_move(std::optional<Coordinates> cord_2_click) {
        if (cord_2_click.has_value()) {
            for (auto possible_cord : this->rendering_coordinates) {
                if ((cord_2_click->x == possible_cord.x) && (cord_2_click->y == possible_cord.y)) {
                    return true;
                }
            }

        }
        return false;
    }
};


int main()
{
    HWND hConsole = GetConsoleWindow();//Если компилятор старый заменить на GetForegroundWindow()
    ShowWindow(hConsole, SW_HIDE);//собственно прячем оконо консоли

    Game chess_game;
    chess_game.start_Game();
}