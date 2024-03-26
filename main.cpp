#include <SFML/Graphics.hpp>

const int tileSize = 80; // –азмер одной клетки на доске
const int boardSize = 8; // –азмер доски (8x8)
const int windowWidth = tileSize * boardSize;
const int windowHeight = tileSize * boardSize;

enum class PieceType { None, White, Black };

struct Piece {
    PieceType type;
    sf::CircleShape shape;
    sf::Vector2i position;
};

class Game {
public:
    Game() : window(sf::VideoMode(windowWidth, windowHeight), "Checkers") {
        initializePieces();
        drawBoard();
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
        }
    }

private:
    sf::RenderWindow window;
    std::vector<std::vector<Piece>> board;
    bool isPieceSelected = false;
    sf::Vector2i selectedPiecePosition;

    void initializePieces() {
        // ррасстановка шашек
        board.resize(boardSize, std::vector<Piece>(boardSize, { PieceType::None, sf::CircleShape(tileSize / 2) }));
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                if ((i + j) % 2 != 0 && j < 3) {
                    board[i][j].type = PieceType::Black;
                    board[i][j].shape.setFillColor(sf::Color::Black);
                    board[i][j].shape.setPosition(i * tileSize + (tileSize - board[i][j].shape.getRadius() * 2) / 2,
                        j * tileSize + (tileSize - board[i][j].shape.getRadius() * 2) / 2);
                    board[i][j].position = { i, j };
                }
                else if ((i + j) % 2 != 0 && j > 4) {
                    board[i][j].type = PieceType::White;
                    board[i][j].shape.setFillColor(sf::Color::White);
                    board[i][j].shape.setPosition(i * tileSize + (tileSize - board[i][j].shape.getRadius() * 2) / 2,
                        j * tileSize + (tileSize - board[i][j].shape.getRadius() * 2) / 2);
                    board[i][j].position = { i, j };
                }
            }
        }
    }

    void drawBoard() {
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                sf::RectangleShape square(sf::Vector2f(tileSize, tileSize));
                if ((i + j) % 2 == 0) {
                    square.setFillColor(sf::Color(255, 206, 158)); // белый цвет 
                }
                else {
                    square.setFillColor(sf::Color(164, 98, 32)); // черный цвет 
                }
                square.setPosition(i * tileSize, j * tileSize);
                window.draw(square);
                if (board[i][j].type != PieceType::None) {
                    window.draw(board[i][j].shape);
                }
            }
        }
        window.display();
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    int tileX = mousePosition.x / tileSize;
                    int tileY = mousePosition.y / tileSize;
                    if (isPieceSelected) {
                        if (isValidMove(selectedPiecePosition, { tileX, tileY })) {
                            movePiece(selectedPiecePosition, { tileX, tileY });
                        }
                        isPieceSelected = false;
                    }
                    else {
                        if (board[tileX][tileY].type != PieceType::None) {
                            isPieceSelected = true;
                            selectedPiecePosition = { tileX, tileY };
                        }
                    }
                    drawBoard();
                }
            }
        }
    }

    bool isValidMove(const sf::Vector2i& from, const sf::Vector2i& to) {
        if (to.x < 0 || to.x >= boardSize || to.y < 0 || to.y >= boardSize) {
            // ѕроверка на выход за границы доски
            return false; 
        }

        // ѕровер€ем, что перемещаемс€ только на черные клетки
        if ((to.x + to.y) % 2 == 0) {
            return false;
        }

        // услови€ чтобы шашки не двигались назад(если они не дамка)
        if (board[from.x][from.y].type == PieceType::Black && to.y <= from.y) {
            return false;
        }
        if (board[from.x][from.y].type == PieceType::White && to.y >= from.y) {
            return false;
        }

        //проверка что ход делаетс€ только на одну клетку по диагонали
        if (board[to.x][to.y].type != PieceType::None) {
            return false;
        }

        //проверка что ход делаетс€ только на одну клетку по диагонали
        int dx = std::abs(to.x - from.x);
        int dy = std::abs(to.y - from.y);
        return dx == 1 && dy == 1;
    }

    void movePiece(const sf::Vector2i& from, const sf::Vector2i& to) {
        board[to.x][to.y] = board[from.x][from.y];
        board[from.x][from.y].type = PieceType::None;
        board[from.x][from.y].shape.setFillColor(sf::Color::Transparent);
        board[to.x][to.y].shape.setPosition(to.x * tileSize + (tileSize - board[to.x][to.y].shape.getRadius() * 2) / 2,
            to.y * tileSize + (tileSize - board[to.x][to.y].shape.getRadius() * 2) / 2);
        drawBoard();
    }
};

int main() {
    Game game;
    game.run();

    return 0;
}
