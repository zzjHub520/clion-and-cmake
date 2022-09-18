#include <iostream>
#include "TutorialConfig.h"
using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Version " << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << std::endl;

    const double inputValue= stod("123");
    return 0;
}
