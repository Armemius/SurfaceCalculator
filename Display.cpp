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
                if (x >= std::min(f1wf2, f1wf3) && x <= std::max(f1wf2, f1wf3) && func2 != NULL && func3 != NULL) {
                    graph[0].color = sf::Color::Blue;
                    graph[1].color = sf::Color::Blue;
                } else {
                    graph[0].color = sf::Color::Black;
                    graph[1].color = sf::Color::Black;
                }
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
                if (x >= std::min(f2wf3, f1wf2) && x <= std::max(f2wf3, f1wf2) && func3 != NULL) {
                    graph[0].color = sf::Color::Blue;
                    graph[1].color = sf::Color::Blue;
                }
                else {
                    graph[0].color = sf::Color::Black;
                    graph[1].color = sf::Color::Black;
                }
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
                if (x >= std::min(f1wf3, f2wf3) && x <= std::max(f1wf3, f2wf3)) {
                    graph[0].color = sf::Color::Blue;
                    graph[1].color = sf::Color::Blue;
                }
                else {
                    graph[0].color = sf::Color::Black;
                    graph[1].color = sf::Color::Black;
                }
                double firstPosY = zeroY - 1 - this->func3->result(x) * fieldSize;
                graph[0].position = sf::Vector2f(zeroX - 1 + x * fieldSize, firstPosY);
                x += 0.01;
                double secondPosY = zeroY - 1 - this->func3->result(x) * fieldSize;
                graph[1].position = sf::Vector2f(zeroX - 1 + x * fieldSize, secondPosY);
                if (std::abs(secondPosY - firstPosY) < 9999)
                    window.draw(graph);

                double lengthFunc1 = std::abs(f1wf2 - f1wf3);
                double lengthFunc2 = std::abs(f1wf2 - f2wf3);
                double lengthFunc3 = std::abs(f1wf3 - f2wf3);
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

        // Intersection points
        sf::CircleShape point1, point2, point3;
        point1.setFillColor(sf::Color(250, 150, 150, 125));
        point2.setFillColor(sf::Color(250, 150, 150, 125));
        point3.setFillColor(sf::Color(250, 150, 150, 125));
        point1.setOutlineColor(sf::Color(0, 0, 0, 175));
        point2.setOutlineColor(sf::Color(0, 0, 0, 175));
        point3.setOutlineColor(sf::Color(0, 0, 0, 175));
        point1.setOutlineThickness(2);
        point2.setOutlineThickness(2);
        point3.setOutlineThickness(2);
        point1.setRadius(2);
        point2.setRadius(2);
        point3.setRadius(2);

        point1.setPosition(zeroX + f1wf2 * fieldSize - 2, zeroY - func1->result(f1wf2) * fieldSize - 2);
        point2.setPosition(zeroX + f2wf3 * fieldSize - 2, zeroY - func2->result(f2wf3) * fieldSize - 2);
        point3.setPosition(zeroX + f1wf3 * fieldSize - 2, zeroY - func3->result(f1wf3) * fieldSize - 2);

        if (func1 != NULL && func2 != NULL)
            window.draw(point1);
        if (func2 != NULL && func3 != NULL)
            window.draw(point2);
        if (func3 != NULL)
            window.draw(point3);

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
                if (event.key.code == sf::Keyboard::E && scale > 12.5) {
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
    delete func1;
    this->func1 = func;
    this->f1wf2 = GraphicHandler::getIntersection(this->func1, this->func2);
    this->f1wf3 = GraphicHandler::getIntersection(this->func1, this->func3);
}

void Display::setFunc2(Function* func) {
    delete func2;
    this->func2 = func;
    this->f1wf2 = GraphicHandler::getIntersection(this->func2, this->func1);
    this->f2wf3 = GraphicHandler::getIntersection(this->func2, this->func3);
}

void Display::setFunc3(Function* func) {
    delete func3;
    this->func3 = func;
    this->f1wf3 = GraphicHandler::getIntersection(this->func3, this->func1);
    this->f2wf3 = GraphicHandler::getIntersection(this->func3, this->func2);
}