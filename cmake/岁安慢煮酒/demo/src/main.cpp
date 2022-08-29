#include <iostream>
#include "config.h"
#include "addition.h"
#include "subtract.h"
#include "multiply.h"
#include "division.h"
using namespace std;

int main()
{
    cout << "Hello World" << endl;
    cout << "version " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << endl;
    #ifdef DATE
        cout << "date " << DATE << endl;
    #endif

    cout << "1 + 2 = " << add(1, 2) << endl;
    cout << "3 - 1 = " << sub(3, 1) << endl;
    cout << "2 * 3 = " << mult(2, 3) << endl;
    cout << "6 / 2 = " << divide(6, 2) << endl;

    return 0;
}