#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow win(sf::VideoMode(500, 500), L"Шашки ");
    sf::Image icon;
    if (!icon.loadFromFile("Image/chess.png"))
    {
        return 1;
    }
    win.setIcon(32, 32, icon.getPixelsPtr());

    const int size = 8; // Размер доски
    const float cellSize = 500.0f / size;
    sf::Color color;

    //текстуры белых и черных шашек 
    sf::Texture whiteCheckerTexture;
    if (!whiteCheckerTexture.loadFromFile("Image/cheker_white.png")) {
        return 1;
    }

    sf::Texture blackCheckerTexture;
    if (!blackCheckerTexture.loadFromFile("Image/black_check.png")) {
        return 1;
    }

    // текстура доски 
    sf::Texture boardTexture;
    if (!boardTexture.loadFromFile("Image/222.png")) { 
        return 1;
    }

    // текстура доски 
    sf::Sprite boardSprite(boardTexture);

    bool board[size][size] = { false };

    // Расстановка черных шашек
    for (int i = 0; i < size; i++) {
        for (int a = 0; a < 3; a++) { // Верхние три ряда
            if ((i + a) % 2 != 0) {
                board[i][a] = true;
            }
        }
    }
    // Расстановка белых шашек
    for (int i = 0; i < size; i++) {
        for (int a = size - 3; a < size; a++) { // Нижние три ряда
            if ((i + a) % 2 != 0) {
                board[i][a] = true;
            }
        }
    }
    bool isChecker = false;
    sf::Vector2i selectedCheker;

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();

            // Обработка события нажатия кнопки мыши
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(win);
                    int cellX = mousePos.x / cellSize;
                    int cellY = mousePos.y / cellSize;

                    // Проверка на клик 
                    if (cellX >= 0 && cellX < size && cellY >= 0 && cellY < size) {
                        // Проверка, что на этой клетке есть шашка
                        if (board[cellX][cellY]) {
                            isChecker = true;
                            selectedCheker = sf::Vector2i(cellX, cellY);
                            std::cout << "The checker is located  (" << cellX << ", " << cellY << ")" << std::endl;
                        }
                        else if ((cellX + cellY) % 2 != 0) {
                            board[cellX][cellY] = true;
                            board[selectedCheker.x][selectedCheker.y] = false;
                            isChecker = false;
                        }
                    }
                }
            }
        }

        win.clear();

        // Отрисовка доски
        win.draw(boardSprite);

        // Рисование шашек
        for (int i = 0; i < size; i++) {
            for (int a = 0; a < size; a++) {
                if (board[i][a]) {
                    sf::CircleShape checker(cellSize / 2);
                    checker.setOrigin(cellSize / 2, cellSize / 2);
                    checker.setPosition((i + 0.5f) * cellSize, (a + 0.5f) * cellSize);
                    if (a < 3)
                        checker.setTexture(&blackCheckerTexture);
                    else
                        checker.setTexture(&whiteCheckerTexture);
                    win.draw(checker);
                }
            }
        }

        win.display();
    }

    return 0;
}
