#include <cstring>
#include <cassert>
#include <iostream>
#include <string>
#include <queue>
#include "Calculator.h"

#define FALSE 0
#define TRUE 1
#define PROGRESSING 2

char* arrangeAnswer(char*);
int charToInt(char);
char intToChar(int);
bool isValidNum(Number);
bool isValidNum(char*);
Number operate(Number, char, Number);
int powerOfTen(int);
void printMinus(Number);
Number makeValidNum(Number);
char* makeValidNum(char*);

//input ����
Number Calculator::calculate(char* input) {
    Number answer;

    std::queue<char> q;

    int tmpNo = 0;
    int isACompleted = FALSE;
    int isBCompleted = FALSE;
    bool hasDot = false;
    bool isLastOpEqual = false;
    char prevInput = ' ';

    //input : "1 + 2 + 3 + 4 ="�� ��� 
    // 1 : putA(1); / +: isACompleted = true; op = '+'; 
    // 2 : putB(2); / +: isBCompleted = true; a = operate(a, op, b); op = '+'; isBCompleted = false;
    // 3 : putB(3); / +: isBCompleted = true; a = operate(a, op, b); op = '+'; isBCompleted = false;
    // 4 : putB(4); / =: a = operate(a, op, b); 
    // answer = a; 
    // printOutput(answer);

    //input �޾ƿͼ� ���� a, op, b�� ����
    for (size_t i = 0; i < strlen(input); ++i) {
        q.push(input[i]);
        if ((isNumber(q.front()) == true || q.front() == '.')&& isACompleted == FALSE) {
            if (prevInput == '=') {
                a.setNumber(0, 0);
            }
            putA(q.front(), hasDot);
        }
        else if ((isNumber(q.front()) == true || q.front() == '.') && isACompleted == TRUE) {
            putB(q.front(), hasDot);
            isBCompleted = PROGRESSING;
        }
        else if (isOperator(q.front()) == true) {
            if (isBCompleted == PROGRESSING) {
                Number c = operate(a, op, b);
                a.setNumber(c.getValue(), c.getPointCnt());
                b.setNumber(0, 0);
                isBCompleted = FALSE;
            }
            op = q.front();
            if (isACompleted == FALSE) isACompleted = TRUE;
            hasDot = false;
            isLastOpEqual = false;

        }
        else if (q.front() == '=') {
            if (op != ' ') {
                Number c = operate(a, op, b);
                a.setNumber(c.getValue(), c.getPointCnt());
            }
            isACompleted = FALSE;
            hasDot = false;
            isLastOpEqual = true;
        }
        else if (q.front() == 'C') {
            a.setNumber(0, 0);
            isACompleted = FALSE;
            hasDot = false;
            isLastOpEqual = false;

            b.setNumber(0, 0);
            op = ' ';
        }

        //input ������ ���ڰ� ���ڸ� b ���, ������(+,-,*,/,=,C)�� a ���
        if (i == strlen(input) - 1) {
            answer = isNumber(q.front()) ? b : a;

            //������ ���ڰ� ���ڿ��� ������ ������(?)�� '='������ a ���
            answer = isLastOpEqual == true ? a : answer;
        }

        prevInput = q.front();
        q.pop();
    }
    return answer;
}

void Calculator::calculatorInit() {
    a.setNumber(0, 0);
    b.setNumber(0, 0);
    op = ' ';
}

Number Calculator::charToNum(char* ch) {
    int value = 0, pointCnt = 0;
    bool countUp = false;
    bool isNegative = false;

    for (size_t i = 0; i < strlen(ch); ++i) {
        if (ch[i] == '.') {
            countUp = true;
        }
        else if (i == 0 && ch[0] == '-') {
            isNegative = true;
        }
        else {
            value = 10 * value + (ch[i] - 48);
            if (countUp) ++pointCnt;
        }
    }

    if (isNegative == true) {
        value *= -1;
    }

    Number no;
    no.setNumber(value, pointCnt);
    return no;
}

//Number���� char*�� ��ȯ (��¿�)
char* Calculator::numToChar(Number no) {
    char ch[100];
    int num = no.getValue();
    int chIter = 0;
    if (no.getPointCnt() == 0) {
        for (int i = no.getPositionalNum(); i > 0; --i) {
            int curInput = num / powerOfTen(i);
            num -= curInput * powerOfTen(i);

            ch[chIter] = intToChar(curInput);
            ++chIter;
        }
        ch[chIter] = NULL;
    }
    else {
        int key = no.getPositionalNum() - no.getPointCnt();
        int powerNum = no.getPositionalNum();
        if (key > 0) { //1.234  12.34  123.4
            for (int i = 0; i < key; ++i) {
                int curInput = num / powerOfTen(powerNum);
                num -= curInput * powerOfTen(powerNum);
                --powerNum;

                ch[chIter] = intToChar(curInput);
                ++chIter;
            }
            ch[chIter] = '.';
            ++chIter;
            for (int i = 0; i < no.getPointCnt(); ++i) {
                int curInput = num / powerOfTen(powerNum);
                num -= curInput * powerOfTen(powerNum);
                --powerNum;

                ch[chIter] = intToChar(curInput);
                ++chIter;
            }
            ch[chIter] = NULL;
        }
        else if (key == 0) {  //0.123  0.12  0.1
            ch[0] = '0';
            ch[1] = '.';
            chIter = 2;
            for (int i = 0; i < no.getPointCnt(); ++i) {
                int curInput = num / powerOfTen(powerNum);
                num -= curInput * powerOfTen(powerNum);
                --powerNum;

                ch[chIter] = intToChar(curInput);
                ++chIter;
            }
            ch[chIter] = NULL;
        }
        else {  //0.012  0.001  0.01
            ch[0] = '0';
            ch[1] = '.';
            chIter = 2;
            key *= -1;
            for (int i = 0; i < key; ++i) {
                ch[chIter] = '0';
                ++chIter;
            }
            for (int i = 0; i < no.getPositionalNum(); ++i) {
                int curInput = num / powerOfTen(powerNum);
                num -= curInput * powerOfTen(powerNum);
                --powerNum;

                ch[chIter] = intToChar(curInput);
                ++chIter;
            }
            ch[chIter] = NULL;
        }
    }

    return ch;
}

//input�� ��� ������� ���� ���Ŀ� ���� ���
void Calculator::printOutput(Number num) {
    char* output = numToChar(num);

    if (isValidNum(output) == false) {
        output = makeValidNum(output);
    }

    //printMinus(num);

    std::cout << arrangeAnswer(output) << std::endl;
}

void Calculator::putA(char input, bool& hasDot) {
    if (input == '.' && a.getPointCnt() == 0) {
        hasDot = true;
    }
    else {
        hasDot == true ?
            a.setNumber(a.getValue() * 10 + charToInt(input), a.getPointCnt() + 1) :
            a.setNumber(a.getValue() * 10 + charToInt(input), 0);
    }

    if (isValidNum(a) == false) {
        makeValidNum(a);
    }
}

void Calculator::putB(char input, bool& hasDot) {
    if (input == '.' && b.getPointCnt() == 0) {
        hasDot = true;
    }
    else {
        hasDot == true ?
            b.setNumber(b.getValue() * 10 + charToInt(input), b.getPointCnt() + 1) :
            b.setNumber(b.getValue() * 10 + charToInt(input), 0);
    }

    if (isValidNum(b) == false) {
        makeValidNum(b);
    }
}


//10 ������ ������ ���ڸ� int������ ����
int charToInt(char ch) {
    switch (ch) {
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case '0': return 0;
    defalut: return 0;
    }
}

//�Է°������� 16���� ������ ���ڸ� �ԷµǾ����� Ȯ��
bool isValidInput(char* input) {
    for (size_t i = 0; i < strlen(input); ++i) {
        if (!isNumber(input[i]) && !isOperator(input[i]) && !isEqual(input[i]) && input[i] != 'C' && input[i] != '.') {
            std::cout << "��ȿ���� ���� �Է��Դϴ�." << std::endl;
            return false;
        }
    }
    return true;
}

//���� �� cal.a�� b�� �� Number�� ���ڸ�(�Ҽ��� ����)�� �ʰ����� �ʾҴ��� Ȯ��
bool isValidNum(Number num) {
    if (num.getPositionalNum() <= 4 && num.getPointCnt() <= 3) {
        return true;
    }
    return false;
}

//��� �� �Ҽ��� ���� �� �ڸ��� ��ȿ�� �������� Ȯ��
bool isValidNum(char* ch) {
    int charNumCnt = 0;
    bool ret = false;

    for (int i = 0; ch[i]; ++i) {
        if (isNumber(ch[i])) {
            charNumCnt += 1;
        }
    }

    if (charNumCnt <= 4) {
        ret = true;
    }
    return ret;
}

//��� �� �� �ڸ� �̸��� ����� ���� �߰��ϱ� & ������ ���ڰ� '.'�� �� ����
char* arrangeAnswer(char* ch) {
    char* output = ch;
    if (*ch == '-') {
        
    }
    return output;
}

//10 ������ int���� char�� ����
char intToChar(int no) {
    switch (no) {
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    case 0: return '0';
    default: return '0';
    }
}

bool isOperator(char ch) {
    switch (ch) {
    case '+': case '-': case '*': case '/':
        return true;
    default:
        return false;
    }
}

bool isNumber(char ch) {
    if ('0' <= ch && ch <= '9') {
        return true;
    }
    return false;
}

bool isEqual(char ch) {
    if (ch == '=') {
        return true;
    }
    return false;
}


//����� ���� ��ȿ�� ���������� �����ֱ�
char* makeValidNum(char* ch) {
    //12345.234 -> E
    //1234.56 -> 1234
    //12.3456 -> 12.34
    char input[100] = { 0, };
    for (int i = 0; ch[i]; ++i) {
        input[i] = ch[i];
    }

    int charNumCnt = 0;
    int zeroCnt = 0; //underflow�� ��� 0�� 4�� �̻��̸� 0���� ��ȯ
    bool haveDot = false;
    int i;

    for (i = 0; input[i]; ++i) {
        if (isNumber(input[i])) {
            charNumCnt += 1;
            if (input[i] == '0') zeroCnt += 1;
        }
        else if (input[i] == '.') {
            haveDot = true;
        }

        //overflow
        if (charNumCnt >= 5 && haveDot == false) {
            return "E";
        }
        //underflow
        else if (charNumCnt == 4 && zeroCnt == 4) {
            return "0";
        }
        else if (charNumCnt == 4 && haveDot == true) { //0.123 12.34 123.4 1234. 
            input[i + 1] = NULL; //����. ch[i]������ segmentation fault�� ������ char[] input�� ��� ���� ����

            //20.00 -> 20.
            if (input[i] == '0') {
                while (input[i] == '0') {
                    input[i] = NULL;
                    --i;
                }
            }

            //1234.�̸� 1234�� ����
            if (input[i] == '.') {
                input[i] = NULL;
            }
        }
    }
    return input;

}

//��ȿ���� ���� ����� �� �ڸ��� �����ֱ�
Number makeValidNum(Number num) {
    //100000.234 -> 1000
    //1234.56 -> 1234
    //12.3456 -> 12.34
    if (num.getPointCnt() > 3) {
        while (num.getPointCnt() > 3) {
            for (int i = num.getPointCnt(); i > 3; --i) {
                num.setNumber(num.getValue() / 10, num.getPointCnt() - 1);
            }
        }
    }
    if (num.getPointCnt() > 0) {
        for (int i = num.getPointCnt(); num.getPositionalNum() > 4; --i) {
            if (num.getPointCnt() == 0) break;
            num.setNumber(num.getValue() / 10, num.getPointCnt() - 1);
        }
    }
    while (num.getPositionalNum() > 4) {
        num.setNumber(num.getValue() / 10, num.getPointCnt());
    }
    //0.0001 -> 0
    if (num.getValue() == 0) {
        num.setNumber(0, 0);
    }
    return num;
}

Number operate(Number a, char op, Number b) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: 
        Number defaultNum;
        return defaultNum;
    }
}

//10�� �� �ŵ��������� ��ȯ
int powerOfTen(int no) {
    int returnNo = 1;
    for (int i = 1; i < no; ++i) {
        returnNo *= 10;
    }
    return returnNo;
}

//Number�� value�� ������ -���
void printMinus(Number num) {
    if (num.getValue() < 0) {
        std::cout << "-";
    }
}


/////////////////////////////////////// for Tests //////////////////////////////////////

void __isValidNum_Number() {
    Number num;

    num.setNumber(1, 0);
    assert(isValidNum(num) == true);
    num.setNumber(1, 1);
    assert(isValidNum(num) == true);
    num.setNumber(1, 2);
    assert(isValidNum(num) == true);
    num.setNumber(1, 3);
    assert(isValidNum(num) == true);
    num.setNumber(1, 4);
    assert(isValidNum(num) == false);

    num.setNumber(12345, 0);
    assert(isValidNum(num) == false);
    num.setNumber(12345, 1);
    assert(isValidNum(num) == false);
    num.setNumber(12345, 2);
    assert(isValidNum(num) == false);
    num.setNumber(12345, 3);
    assert(isValidNum(num) == false);
    num.setNumber(12345, 4);
    assert(isValidNum(num) == false);
}

void __makeValidNum_Number() {
    Number num;

    num.setNumber(12345, 0);
    assert(makeValidNum(num).getValue() == 1234);
    assert(makeValidNum(num).getPointCnt() == 0);
    num.setNumber(12345, 1);
    assert(makeValidNum(num).getValue() == 1234);
    assert(makeValidNum(num).getPointCnt() == 0);
    num.setNumber(12345, 2);
    assert(makeValidNum(num).getValue() == 1234);
    assert(makeValidNum(num).getPointCnt() == 1);
    num.setNumber(12345, 3);
    assert(makeValidNum(num).getValue() == 1234);
    assert(makeValidNum(num).getPointCnt() == 2);
    num.setNumber(12345, 4);
    assert(makeValidNum(num).getValue() == 1234);
    assert(makeValidNum(num).getPointCnt() == 3);
    //12345.6789 -> 1234
    num.setNumber(123456789, 4);
    assert(makeValidNum(num).getValue() == 1234);
    assert(makeValidNum(num).getPointCnt() == 0);
    //0.0001 -> 0
    num.setNumber(1, 4);
    assert(makeValidNum(num).getValue() == 0);
    assert(makeValidNum(num).getPointCnt() == 0);
    //12.3456789 -> 12.34
    num.setNumber(123456789, 7);
    assert(makeValidNum(num).getValue() == 1234);
    assert(makeValidNum(num).getPointCnt() == 2);
}

void __isValidNum_char() {
    assert(isValidNum("1234.") == true);
    assert(isValidNum("123.4") == true);
    assert(isValidNum("12.34") == true);
    assert(isValidNum("1.234") == true);

    assert(isValidNum("-123.") == true);
    assert(isValidNum("-12.3") == true);
    assert(isValidNum("-1.23") == true);
    assert(isValidNum("-0.123") == true);

    assert(isValidNum("0.1234") == false);
    assert(isValidNum("12.345") == false);
    assert(isValidNum("1234.12") == false);
}

void __makeValidNum_char() {
    assert(strcmp(makeValidNum("0.1234"), "0.123") == 0);
    assert(strcmp(makeValidNum("12.345678"), "12.34") == 0);
    assert(strcmp(makeValidNum("-123.45678"), "-123.4") == 0);
    assert(strcmp(makeValidNum("1234.1234"), "1234") == 0);

    assert(strcmp(makeValidNum("123456"), "E") == 0);
    assert(strcmp(makeValidNum("123456.789"), "E") == 0);

    assert(strcmp(makeValidNum("0.00099"), "0") == 0);

    assert(strcmp(makeValidNum("200.01"), "200") == 0);
    assert(strcmp(makeValidNum("0.10002"), "0.1") == 0);
    assert(strcmp(makeValidNum("1.2004"), "1.2") == 0);
}