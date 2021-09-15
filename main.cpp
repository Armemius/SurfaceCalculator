#include "stdafx.h"

void scanner();
Display display;

int main() {
    std::thread scan(scanner);
    scan.detach();
    display.process();
    return 0;
}

void scanner() {
    for (;;) {
        std::string line;
        std::cout << "Enter function 1:";
        std::cin >> line;
        Function* func1 = new Function();
        func1->parse(line);
        display.setFunc1(func1);

        std::cout << "Enter function 2:";
        std::cin >> line;
        Function* func2 = new Function();
        func2->parse(line);
        display.setFunc2(func2);

        std::cout << "Enter function 3:";
        std::cin >> line;
        Function* func3 = new Function();
        func3->parse(line);
        display.setFunc3(func3);
        system("pause");
        system("cls");
    }
     
}