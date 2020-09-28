#include "Number.h"


class Calculator {
public:
    Calculator() :op(' ')
    {}
    void calculatorInit();
    Number calculate(char*);
    Number charToNum(char*);
    char* numToChar(Number);
    void printOutput(Number);

private:
    Number a, b;
    char op;

    void putA(char, bool&);
    void putB(char, bool&);
};

bool isEqual(char);
bool isOperator(char);
bool isNumber(char);
bool isValidInput(char*);

// 테스트용
void __isValidNum_Number();
void __makeValidNum_Number();
void __isValidNum_char();
void __makeValidNum_char();
void __extractMinus();