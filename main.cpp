#include "stdafx.h"

void scanner();
void displayThread();
void calculateSurface();

double surface = -1;
int mct = 1000000;
bool monteCarlo = false;
std::thread disp(displayThread);
Display display;
Function* funcp1, * funcp2, * funcp3;

int main() {
    try {
        std::thread scan(scanner);
        scan.detach();
        disp.join();
        for (;;);
        return 0;
    } catch (...) {
        main();
    }
    
}

void scanner() {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    static bool disp = false;
    static bool doSurface = true;
    for (;;) {
        std::cout << "[WARN] Graphics must have ONE intersection between each pair!\n";
        try {
            std::string line;
            std::cout << "Enter function 1:";
            std::cin >> line;
            if (line == "-arg") {
                system("cls");
                while (line != "-apply") {
                    std::cin >> line;
                    if (line == "-mc") {
                        std::cin >> line;
                        if (line == "true") {
                            monteCarlo = true;
                        }
                        else {
                            monteCarlo = false;
                        }
                    }
                    else if (line == "-mct") {
                        std::cin >> mct;
                    }
                    else if (line == "-surf") {
                        std::cin >> line;
                        if (line == "true") {
                            doSurface = true;
                        }
                        else {
                            doSurface = false;
                        }
                    }
                    else if (line == "-disp") {
                        std::cin >> line;
                        if (line == "true") {
                            if (display.inProcess == false) {
                                display.inProcess = true;
                                
                            }
                        }
                        else {
                            display.inProcess = false;
                        }
                    } else if (line != "-apply"){
                        std::cout << "not recognised\n";
                    }
                }
                continue;
            }
            Function* func1 = new Function(line);
            func1->result(666);

            std::cout << "Enter function 2:";
            std::cin >> line;
            Function* func2 = new Function(line);
            func2->result(666);

            std::cout << "Enter function 3:";
            std::cin >> line;
            Function* func3 = new Function(line);
            func3->result(666);
            display.setFunctions(func1, func2, func3);

            funcp1 = func1;
            funcp2 = func2;
            funcp3 = func3;
            if (doSurface) {
                surface = 0;
                std::cout << "Calculating surface";
                std::vector<std::string> progress{ "|", "/", "-", "\\" };
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
                std::cout << std::fixed << std::setprecision(5) << "\rSurface size: " << surface << "                      \n";
            }
        } catch(std::exception e) {
            std::cout << e.what() << "\nResetting functions...\n";
            system("pause");
            display = Display();
        }
        
        system("pause");
        display = Display();
        system("cls");
    }
}

void displayThread() {
    try {
        if (display.inProcess)
            display.process();
        while (!display.inProcess);
        
    } catch(std::exception e) {
        std::cout << "Runtime error: totally bruh\n";
    }
}

void calculateSurface() {
    double tmpSurface = 0;
    double f1wf2 = GraphicHandler::getIntersection(funcp1, funcp2);
    double f2wf3 = GraphicHandler::getIntersection(funcp2, funcp3);
    double f1wf3 = GraphicHandler::getIntersection(funcp1, funcp3);
    double lengthFunc1 = std::abs(f1wf2 - f1wf3);
    double lengthFunc2 = std::abs(f1wf2 - f2wf3);
    double lengthFunc3 = std::abs(f1wf3 - f2wf3);
    if (!monteCarlo) {
        double activeSurfaceFunc1 = GraphicHandler::integral(funcp1, std::min(f1wf2, f1wf3), std::max(f1wf2, f1wf3));
        double activeSurfaceFunc2 = GraphicHandler::integral(funcp2, std::min(f1wf2, f2wf3), std::max(f1wf2, f2wf3));
        double activeSurfaceFunc3 = GraphicHandler::integral(funcp3, std::min(f1wf3, f2wf3), std::max(f1wf3, f2wf3));

        if (lengthFunc1 > lengthFunc2 && lengthFunc1 > lengthFunc3) {
            if (funcp1->result((f1wf2 + f1wf3) / 2) > funcp2->result((f1wf2 + f1wf3) / 2)) {
                tmpSurface = activeSurfaceFunc1 - activeSurfaceFunc2 - activeSurfaceFunc3;
            }
            else {
                tmpSurface = -activeSurfaceFunc1 + activeSurfaceFunc2 + activeSurfaceFunc3;
            }
        }
        else if (lengthFunc2 > lengthFunc1 && lengthFunc2 > lengthFunc3) {
            if (funcp2->result((f1wf2 + f2wf3) / 2) > funcp1->result((f1wf2 + f2wf3) / 2)) {
                tmpSurface = activeSurfaceFunc2 - activeSurfaceFunc1 - activeSurfaceFunc3;
            }
            else {
                tmpSurface = -activeSurfaceFunc2 + activeSurfaceFunc1 + activeSurfaceFunc3;
            }
        }
        else if (lengthFunc3 > lengthFunc1 && lengthFunc3 > lengthFunc2) {
            if (funcp3->result((f1wf3 + f2wf3) / 2) > funcp1->result((f1wf3 + f2wf3) / 2)) {
                tmpSurface = activeSurfaceFunc3 - activeSurfaceFunc2 - activeSurfaceFunc1;
            }
            else {
                tmpSurface = -activeSurfaceFunc3 + activeSurfaceFunc2 + activeSurfaceFunc1;
            }
        }
        surface = std::abs(tmpSurface);
    }
    else {
        int aimed = 0, count = 0;
        double from = std::min(f1wf2, std::min(f1wf3, f2wf3)) - 0.1,
            to = std::max(f1wf2, std::max(f1wf3, f2wf3)) + 0.1;
        double minY = 666,
            maxY = -666;

        for (double i = from; i < to; i += (to - from) / 1000.0) {
            double minYTmp = (std::min(funcp1->result(i), std::min(funcp2->result(i), funcp3->result(i))));
            double maxYTmp = (std::max(funcp1->result(i), std::max(funcp2->result(i), funcp3->result(i))));
            if (minYTmp < minY)
                minY = minYTmp;
            if (maxYTmp > maxY)
                maxY = maxYTmp;
        }

        for (int i = 0; i < mct; ++i, ++count) {
            std::uniform_real_distribution<double> unifx(from, to);
            std::uniform_real_distribution<double> unify(minY, maxY);
            std::random_device rand_dev;
            std::mt19937 rand_engine(rand_dev());
            double x = unifx(rand_engine), y = unify(rand_engine);
            if (lengthFunc1 > lengthFunc2 && lengthFunc1 > lengthFunc3) {
                // std::cout << 1 << " " << x << " " << y << "\n";
                if (funcp1->result((f1wf2 + f1wf3) / 2) > funcp2->result((f1wf2 + f1wf3) / 2)) {
                    if (funcp1->result(x) > y && funcp2->result(x) < y && funcp3->result(x) < y)
                        aimed++;
                } else {
                    if (funcp1->result(x) < y && funcp2->result(x) > y && funcp3->result(x) > y)
                        aimed++;
                }
            }
            else if (lengthFunc2 > lengthFunc1 && lengthFunc2 > lengthFunc3) {
                if (funcp2->result((f1wf2 + f2wf3) / 2) > funcp1->result((f1wf2 + f2wf3) / 2)) {
                    if (funcp2->result(x) > y && funcp1->result(x) < y && funcp3->result(x) < y)
                        aimed++;
                } else {
                    if (funcp2->result(x) < y && funcp1->result(x) > y && funcp3->result(x) > y)
                        aimed++;
                }
            }
        else if (lengthFunc3 > lengthFunc1 && lengthFunc3 > lengthFunc2) {
        if (funcp3->result((f1wf3 + f2wf3) / 2) > funcp1->result((f1wf3 + f2wf3) / 2)) {
            if (funcp3->result(x) > y && funcp1->result(x) < y && funcp2->result(x) < y) {
                aimed += 1;
            }
        } else {
            if (funcp1->result(x) < y && funcp1->result(x) > y && funcp2->result(x) > y)
                aimed += 1;
        }
            }
    }
    surface = (to - from) * (maxY - minY) * (aimed * 1.0 / count);
    }
}