#include "stdafx.h"

void scanner();
void displayThread();

Display display;
std::thread scan(scanner);
std::thread disp(displayThread);

int main() {
    scan.detach();
    disp.join();
    return 0;
}

void scanner() {
    for (;;) {
        try {
            std::string line;
            std::cout << "Enter function 1:";
            std::cin >> line;
            Function* func1 = new Function();
            func1->parse(line);
            func1->result(666);
            display.setFunc1(func1);

            std::cout << "Enter function 2:";
            std::cin >> line;
            Function* func2 = new Function();
            func2->parse(line);
            func2->result(666);
            display.setFunc2(func2);

            std::cout << "Enter function 3:";
            std::cin >> line;
            Function* func3 = new Function();
            func3->parse(line);
            func3->result(666);
            display.setFunc3(func3);
        } catch(std::exception e) {
            std::cout << e.what() << "\nResetting functions...\n";
            display = Display();
        }
        
        system("pause");
        system("cls");
    }
}

void displayThread() {
    display.process();
}