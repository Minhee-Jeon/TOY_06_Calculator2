#include <iostream>
#include "Number.h"
#include "Calculator.h"
using namespace std;

bool isValidInput(char*);
int main() {
    Calculator cal;
    char input[100];

    cin.getline(input, 100);
    if (isValidInput(input)) {
        cal.calculate(input);
    }

}
