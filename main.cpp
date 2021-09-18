#include "stdafx.h"

void scanner();
void displayThread();
void calculateSurface();

double surface = -1;
Display display;
Function* funcp1, * funcp2, * funcp3;

int main() {
    std::thread scan(scanner);
    std::thread disp(displayThread);
    scan.detach();
    disp.join();
    for (;;);
    return 0;
}

void scanner() {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    for (;;) {
        std::cout << "[WARN] Graphics must have ONE intersection between each pair!\n";
        try {
            std::string line;
            std::cout << "Enter function 1:";
            std::cin >> line;
            Function* func1 = new Function(line);
            func1->result(666);
            display.setFunc1(func1);

            std::cout << "Enter function 2:";
            std::cin >> line;
            Function* func2 = new Function(line);
            GraphicHandler::checkIntersects(func1, func2);
            func2->result(666);
            display.setFunc2(func2);

            std::cout << "Enter function 3:";
            std::cin >> line;
            Function* func3 = new Function(line);
            GraphicHandler::checkIntersects(func3, func1);
            GraphicHandler::checkIntersects(func3, func2);
            func3->result(666);
            display.setFunc3(func3);

            funcp1 = func1;
            funcp2 = func2;
            funcp3 = func3;
            surface = 0;
            std::cout << "Calculating surface";
            std::vector<std::string> progress{"|", "/", "-", "\\"};
            surface = -1;
            std::thread calc(calculateSurface);
            calc.detach();
            while (surface == -1) {
                static int i = 0;
                std::cout << "\rCalculating surface " + progress.at(i);
                i++;
                if (i > progress.size() - 1)
                    i = 0;
                std::this_thread::sleep_for(std::chrono::milliseconds(75));
            }
            std::cout << std::fixed << std::setprecision(4) << "\rSurface size: " << surface << "                      \n";
        } catch(std::exception e) {
            std::cout << e.what() << "\nResetting functions...\n";
            display = Display();
        }
        
        system("pause");
        display.setFunc1(NULL);
        display.setFunc2(NULL);
        display.setFunc3(NULL);
        system("cls");
    }
}

void displayThread() {
    try {
        display.process();
    } catch(std::exception e) {
        std::cout << "Runtime error: totally bruh\n";
    }
}

void calculateSurface() {
    double tmpSurface = 0;
    double f1wf2 = GraphicHandler::getIntersection(funcp1, funcp2);
    double f2wf3 = GraphicHandler::getIntersection(funcp2, funcp3);
    double f1wf3 = GraphicHandler::getIntersection(funcp1, funcp3);

    double activeSurfaceFunc1 = GraphicHandler::integral(funcp1, std::min(f1wf2, f1wf3), std::max(f1wf2, f1wf3));
    double activeSurfaceFunc2 = GraphicHandler::integral(funcp2, std::min(f1wf2, f2wf3), std::max(f1wf2, f2wf3));
    double activeSurfaceFunc3 = GraphicHandler::integral(funcp3, std::min(f1wf3, f2wf3), std::max(f1wf3, f2wf3));

    double lengthFunc1 = std::abs(f1wf2 - f1wf3);
    double lengthFunc2 = std::abs(f1wf2 - f2wf3);
    double lengthFunc3 = std::abs(f1wf3 - f2wf3);

    if (lengthFunc1 > lengthFunc2 && lengthFunc1 > lengthFunc3) {
        if (funcp1->result((f1wf2 + f1wf3) / 2) > funcp2->result((f1wf2 + f1wf3) / 2)) {
            tmpSurface = activeSurfaceFunc1 - activeSurfaceFunc2 - activeSurfaceFunc3;
        } else {
            tmpSurface = -activeSurfaceFunc1 + activeSurfaceFunc2 + activeSurfaceFunc3;
        }
    } else if (lengthFunc2 > lengthFunc1 && lengthFunc2 > lengthFunc3) {
        if (funcp2->result((f1wf2 + f2wf3) / 2) > funcp1->result((f1wf2 + f2wf3) / 2)) {
            tmpSurface = activeSurfaceFunc2 - activeSurfaceFunc1 - activeSurfaceFunc3;
        } else {
            tmpSurface = -activeSurfaceFunc2 + activeSurfaceFunc1 + activeSurfaceFunc3;
        }
    } else if (lengthFunc3 > lengthFunc1 && lengthFunc3 > lengthFunc2) {
        if (funcp3->result((f1wf3 + f2wf3) / 2) > funcp1->result((f1wf3 + f2wf3) / 2)) {
            tmpSurface = activeSurfaceFunc3 - activeSurfaceFunc2 - activeSurfaceFunc1;
        } else {
            tmpSurface = -activeSurfaceFunc3 + activeSurfaceFunc2 + activeSurfaceFunc1;
        }
    }
    surface = std::abs(tmpSurface);
}