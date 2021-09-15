#include "stdafx.h"

void Display::process() {
#ifdef DISPLAY
    double shiftX = 0, shiftY = 0;
    double scale = 100.0;
    sf::RenderWindow window(sf::VideoMode(horizontalPx, verticalPx), "Surface calculator", sf::Style::Fullscreen);
    while (window.isOpen())
    {
        static bool doFill = true;
        // Main(thick) lines
        window.clear(sf::Color(245, 245, 250));
        for (int i = -2; i < 2; ++i) {
            sf::VertexArray lineX(sf::LinesStrip, 2);
            lineX[0].position = sf::Vector2f(0, verticalPx / 2 + shiftY * scale / 100.0 + i);
            lineX[1].position = sf::Vector2f(horizontalPx, verticalPx / 2 + shiftY * scale / 100.0 + i);
            lineX[0].color = sf::Color::Black;
            lineX[1].color = sf::Color::Black;
            window.draw(lineX);
        }
        for (int i = -2; i < 2; ++i) {
            sf::VertexArray lineX(sf::LinesStrip, 2);
            lineX[0].position = sf::Vector2f(horizontalPx / 2 + shiftX * scale / 100.0 + i, 0);
            lineX[1].position = sf::Vector2f(horizontalPx / 2 + shiftX * scale / 100.0 + i, verticalPx);
            lineX[0].color = sf::Color::Black;
            lineX[1].color = sf::Color::Black;
            window.draw(lineX);
        }

        // Zero/zero point relative to window
        double zeroX = horizontalPx / 2 + shiftX * scale / 100.0,
            zeroY = verticalPx / 2 + shiftY * scale / 100.0;
        const int fieldSize = 200 * scale / 100;

        // Graphics
        if (func1 != NULL)
            for (double x = -50; x < 49;) {
                sf::VertexArray graph(sf::LinesStrip, 2);
                graph[0].color = sf::Color::Black;
                graph[1].color = sf::Color::Black;
                double firstPosY = zeroY - 1 - this->func1->result(x) * fieldSize;
                graph[0].position = sf::Vector2f(zeroX - 1 + x * fieldSize, firstPosY);
                x += 0.01;
                double secondPosY = zeroY - 1 - this->func1->result(x) * fieldSize;
                graph[1].position = sf::Vector2f(zeroX - 1 + x * fieldSize, secondPosY);
                if (std::abs(secondPosY - firstPosY) < 9999)
                    window.draw(graph);
            }

        if (func2 != NULL)
            for (double x = -50; x < 49;) {
                sf::VertexArray graph(sf::LinesStrip, 2);
                graph[0].color = sf::Color::Black;
                graph[1].color = sf::Color::Black;
                double firstPosY = zeroY - 1 - this->func2->result(x) * fieldSize;
                graph[0].position = sf::Vector2f(zeroX - 1 + x * fieldSize, firstPosY);
                x += 0.01;
                double secondPosY = zeroY - 1 - this->func2->result(x) * fieldSize;
                graph[1].position = sf::Vector2f(zeroX - 1 + x * fieldSize, secondPosY);
                if (std::abs(secondPosY - firstPosY) < 9999)
                    window.draw(graph);
            }

        if (func3 != NULL)
            for (double x = -50; x < 49;) {
                sf::VertexArray graph(sf::LinesStrip, 2);
                graph[0].color = sf::Color::Black;
                graph[1].color = sf::Color::Black;
                double firstPosY = zeroY - 1 - this->func3->result(x) * fieldSize;
                graph[0].position = sf::Vector2f(zeroX - 1 + x * fieldSize, firstPosY);
                x += 0.01;
                double secondPosY = zeroY - 1 - this->func3->result(x) * fieldSize;
                graph[1].position = sf::Vector2f(zeroX - 1 + x * fieldSize, secondPosY);
                if (std::abs(secondPosY - firstPosY) < 9999)
                    window.draw(graph);
            }

        // Utility lines
        for (int i = -50; i < 50; ++i) {
            for (int j = 0; j < 1; j++) {
                sf::VertexArray lineX(sf::LinesStrip, 2);
                lineX[0].position = sf::Vector2f(horizontalPx / 2 + shiftX * scale / 100.0 + i * fieldSize + j, 0);
                lineX[1].position = sf::Vector2f(horizontalPx / 2 + shiftX * scale / 100.0 + i * fieldSize + j, verticalPx);
                lineX[0].color = sf::Color(0, 0, 0, 75);
                lineX[1].color = sf::Color(0, 0, 0, 75);
                window.draw(lineX);

                sf::VertexArray lineY(sf::LinesStrip, 2);
                lineY[0].position = sf::Vector2f(0, verticalPx / 2 + shiftY * scale / 100.0 + i * fieldSize + j);
                lineY[1].position = sf::Vector2f(horizontalPx, verticalPx / 2 + shiftY * scale / 100.0 + i * fieldSize + j);
                lineY[0].color = sf::Color(0, 0, 0, 75);
                lineY[1].color = sf::Color(0, 0, 0, 75);
                window.draw(lineY);
            }
        }
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Key input handler
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q && scale < 1600) {
                    scale *= 2;
                    shiftX *= 2;
                    shiftY *= 2;
                }
                if (event.key.code == sf::Keyboard::E && scale > 50) {
                    scale /= 2;
                    shiftX /= 2;
                    shiftY /= 2;
                }
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::A)
                    shiftX += 25 * 100.0 / scale;
                if (event.key.code == sf::Keyboard::D)
                    shiftX -= 25 * 100.0 / scale;
                if (event.key.code == sf::Keyboard::W)
                    shiftY += 25 * 100.0 / scale;
                if (event.key.code == sf::Keyboard::S)
                    shiftY -= 25 * 100.0 / scale;
                if (event.key.code == sf::Keyboard::Space) {
                    scale = 100.0;
                    shiftX = 0;
                    shiftY = 0;
                }
            }
        }
    }
#else
    std::cout << "Display disabled, define 'DISPLAY' to enable\n";
#endif
    return;
}

void Display::setFunc1(Function* func) {
    this->func1 = func;
}

void Display::setFunc2(Function* func) {
    this->func2 = func;
}

void Display::setFunc3(Function* func) {
    this->func3 = func;
}