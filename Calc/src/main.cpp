#include <iostream>
#include "Number.h"
#include "Calculator.h"
using namespace std;


int main() {
    Calculator cal;
    char input[100] = { NULL, };

    while (strcmp(input, "end") != 0) {
        cin.getline(input, 100);
        if (isValidInput(input)) {
            Number answer = cal.calculate(input);
            cal.printOutput(answer);
            
        }
    }
    return 0;
}
