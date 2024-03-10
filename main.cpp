
//Шашки
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow win(sf::VideoMode(400, 400), L"Шашки ");
    sf::Image icon;
    if (!icon.loadFromFile("Image/chess.png"))
    {
        return 1;
    }
    win.setIcon(32, 32, icon.getPixelsPtr());

    const int size = 8; // Размер доски
    const float cellSize = 400.0f / size;
    sf::Color color;

    sf::Texture whiteCheckerTexture;
    if (!whiteCheckerTexture.loadFromFile("Image/white_checker.png")) {
        return 1;
    }

    sf::Texture blackCheckerTexture;
    if (!blackCheckerTexture.loadFromFile("Image/black_checker.png")) {
        return 1;
    }

    /*sf::CircleShape checker(cellSize / 2);
    checker.setOrigin(cellSize / 2, cellSize / 2);*/


    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
        }

        win.clear();

        // Рисование игрового поля
        for (int i = 0; i < size; i++) {
            for (int a = 0; a < size; a++) {
                if ((i + a) % 2 == 0) {
                    color = sf::Color(245, 222, 179);
                }
                else {
                    color = sf::Color(139, 69, 19);
                }
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(i * cellSize, a * cellSize);
                cell.setFillColor(color);
                win.draw(cell);
            }
        }

        // Расстановка белых шашек


        for (int i = 0; i < size; i++) {
            for (int a = size - 3; a < size; a++) { // Нижние три ряда
                if ((i + a) % 2 != 0) {
                    sf::CircleShape checker(cellSize / 2);
                    checker.setOrigin(cellSize / 2, cellSize / 2);
                    checker.setPosition((i + 0.5f) * cellSize, (a + 0.5f) * cellSize);
                    checker.setTexture(&whiteCheckerTexture);
                    win.draw(checker);
                }
            }
        }

        // Расстановка черных шашек
        ;
        for (int i = 0; i < size; i++) {
            for (int a = 0; a < 3; a++) { // Верхние три ряда
                if ((i + a) % 2 != 0) {

                    sf::CircleShape checker(cellSize / 2);
                    checker.setOrigin(cellSize / 2, cellSize / 2);
                    checker.setPosition((i + 0.5f) * cellSize, (a + 0.5f) * cellSize);
                    checker.setTexture(&blackCheckerTexture);
                    win.draw(checker);
                }
            }
        }
        win.display();
    }
    return 0;
}
