#include <cstring>
#include "Calculator.h"

char* numToChar(Number);
//input ����
void Calculator::calculate(char* input) {
    //input �޾ƿͼ� ���� a, operator, b�� ����

}

Number* Calculator::charToNum(char* ch) {
    int value = 0, pointCnt = 0;
    bool countUp = false;

    for (size_t i = 0; i < strlen(ch); ++i) {
        if (ch[i] == '.') {
            countUp = true;
        }
        else {
            value = 10 * value + (ch[i] - 48);
            if (countUp) ++pointCnt;
        }
    }

    Number* no = NULL;
    no->setNumber(value, pointCnt);
    return no;
}