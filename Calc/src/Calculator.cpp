#include <cstring>
#include <iostream>
#include "Calculator.h"

bool isEqual(char);
bool isOperator(char);
bool isNumber(char);
int powerOfTen(int);

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

//Number���� char*�� ��ȯ (��¿�)
char* Calculator:: numToChar(Number no) {
    char ch[6]; //�ִ� 1.234 (��ȣ�� �������� ����� ���)
    int num = no.getValue();
    int chIter = 0;
    if (no.getPointCnt() == 0) {
        for (int i = no.getPositionalNum(); i > 0; --i) {
            int curInput = num / powerOfTen(i);
            num -= curInput * powerOfTen(i);

            ch[chIter] = curInput;
            ++chIter;
        }
    }
    else {
        int key = no.getPositionalNum() - no.getPointCnt();
        int powerNum = no.getPositionalNum();
        if (key > 0) { //1.234  12.34  123.4
            for (int i = 0; i < key; ++i) {
                int curInput = num / powerOfTen(powerNum);
                num -= curInput * powerOfTen(powerNum);
                --powerNum;

                ch[chIter] = curInput;
                ++chIter;
            }
            ch[chIter] = '.';
            ++chIter;
            for (int i = 0; i < no.getPointCnt(); ++i) {
                int curInput = num / powerOfTen(powerNum);
                num -= curInput * powerOfTen(powerNum);
                --powerNum;

                ch[chIter] = curInput;
                ++chIter;
            }
        }
        else if (key == 0) {  //0.123  0.12  0.1
            ch[0] = '0';
            ch[1] = '.';
            chIter = 2;
            for (int i = 0; i < no.getPointCnt(); ++i) {
                int curInput = num / powerOfTen(powerNum);
                num -= curInput * powerOfTen(powerNum);
                --powerNum;

                ch[chIter] = curInput;
                ++chIter;
            }
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
            for (int i = 0; i < no.getPointCnt(); ++i) {
                int curInput = num / powerOfTen(powerNum);
                num -= curInput * powerOfTen(powerNum);
                --powerNum;

                ch[chIter] = curInput;
                ++chIter;
            }
        }
    }

    return ch;
}

//10�� �� �ŵ��������� ��ȯ
int powerOfTen(int no) {
    int returnNo = 1;
    for (int i = 0; i < no; ++i) {
        returnNo *= 10;
    }
    return returnNo;
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