#include "Number.h"
class Calculator {
    Number a, b;
public:
    void calculate(char*);
    Number charToNum(char*);
    char* numToChar(Number);
};