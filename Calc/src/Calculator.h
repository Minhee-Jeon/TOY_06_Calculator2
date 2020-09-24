#include "Number.h"


class Calculator {
public:
    void calculate(char*);
    Number charToNum(char*);
    char* numToChar(Number);

private:
    Number a, b;
};

// 테스트용
void __isValidNum_Number();
void __makeValidNum_Number();
void __isValidNum_char();
void __makeValidNum_char();