#include <iostream>
#include "Number.h"
#include "Calculator.h"
using namespace std;


int main() {
    Calculator cal;
    char input[100] = { NULL, };

    cin.getline(input, 100);
    if (isValidInput(input)) {
        cal.printOutput(cal.calculate(input));
    }
    return 0;
}

