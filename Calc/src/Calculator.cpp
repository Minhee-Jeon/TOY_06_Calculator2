#include <cstring>
#include <cassert>
#include <iostream>
#include <string>
#include <queue>
#include "Calculator.h"

char* arrangeAnswer(char*);
bool isEqual(char);
bool isOperator(char);
bool isNumber(char);
char intToChar(int);
bool isValidNum(Number);
bool isValidNum(char*);
int powerOfTen(int);
Number makeValidNum(Number);
char* makeValidNum(char*);

//input 계산기
void Calculator::calculate(char* input) {
    
}

//연산 전 cal.a나 b에 들어갈 Number가 네자리(소수점 제외)를 초과하지 않았는지 확인
bool isValidNum(Number num) {
    if (num.getPositionalNum() <= 4 && num.getPointCnt() <= 3) {
        return true;
    }
    return false;
}
//유효범위 외의 수라면 네 자리에 맞춰주기
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

//출력 전 소수점 제외 네 자리의 유효한 숫자인지 확인
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

//출력을 위한 유효한 문자형으로 맞춰주기
char* makeValidNum(char* ch) {
    //12345.234 -> E
    //1234.56 -> 1234
    //12.3456 -> 12.34
    char input[100] = { 0, };
    for (int i = 0; ch[i]; ++i) {
        input[i] = ch[i];
    }

    int charNumCnt = 0;
    int zeroCnt = 0; //underflow의 경우 0이 4개 이상이면 0으로 변환
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
            input[i+1] = NULL; //버림. ch[i]였으나 segmentation fault로 스택인 char[] input에 담아 고쳐 리턴

            //20.00 -> 20.
            if (input[i] == '0') {
                while (input[i] == '0') {
                    input[i] = NULL;
                    --i;
                }
            }

            //1234.이면 1234로 리턴
            if (input[i] == '.') {
                input[i] = NULL;
            }
        }
    }
    return input;

}

//출력 시 네 자리 미만의 수라면 공백 추가하기 & 마지막 문자가 '.'일 시 삭제
char* arrangeAnswer(char* ch) {
    return NULL;
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

//Number형을 char*로 반환 (출력용)
char* Calculator:: numToChar(Number no) {
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

//10 이하의 int형을 char로 리턴
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

//10의 몇 거듭제곱인지 반환
int powerOfTen(int no) {
    int returnNo = 1;
    for (int i = 1; i < no; ++i) {
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

//입력과정에서 16개의 정해진 문자만 입력되었는지 확인
bool isValidInput(char* input) {
    for (size_t i = 0; i < strlen(input); ++i) {
        if (!isNumber(input[i]) && !isOperator(input[i]) && !isEqual(input[i]) && input[i] != 'C' && input[i] != '.') {
            std::cout << "유효하지 않은 입력입니다." << std::endl;
            return false;
        }
    }
    return true;
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
    assert(strcmp(makeValidNum("123.45678"), "123.4") == 0);
    assert(strcmp(makeValidNum("1234.1234"), "1234") == 0);

    assert(strcmp(makeValidNum("123456"), "E") == 0);
    assert(strcmp(makeValidNum("123456.789"), "E") == 0);

    assert(strcmp(makeValidNum("0.00099"), "0") == 0);

    assert(strcmp(makeValidNum("200.01"), "200") == 0);
    assert(strcmp(makeValidNum("0.10002"), "0.1") == 0);
    assert(strcmp(makeValidNum("1.2004"), "1.2") == 0);
}