#include <iostream>
#include <algorithm>
using namespace std;

class Number {
public:
    Number() :value(0), pointCnt(0)
    {
    }

    void setNumber(int, int);
    int getValue();
    int getPointCnt();
    int getPositionalNum();

private:
    int value;
    int pointCnt; //3을 초과할 수 없다
};

void Number::setNumber(int val, int cnt) {
    this->value = val;
    this->pointCnt = cnt;
}

int Number::getValue() {
    return this->value;
}

int Number::getPointCnt() {
    return this->pointCnt;
}

//value의 자릿수 구하기
int Number::getPositionalNum() {
    int cnt = 0;
    int val = value;
    if (val < 0) val *= -1;
    while (val > 0) {
        val /= 10;
        ++cnt;
    }
    return cnt;
}

class Calculator {
    Number a, b;
public:
    void calculate(char*);
    Number* charToNum(char*);
};

char* numToChar(Number);
//input 계산기
void Calculator::calculate(char* input) {
    //input 받아와서 각각 a, operator, b에 저장

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

int powerOfTen(int);
//Number형을 char*로 반환 (출력용)
char* numToChar(Number no) {
    char ch[6]; //최댓값 1.234 (부호는 마지막에 고려해 출력)
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

//10의 몇 거듭제곱인지 반환
int powerOfTen(int no) {
    int returnNo = 1;
    for (int i = 0; i < no; ++i) {
        returnNo *= 10;
    }
    return returnNo;
}

bool isOperator(char);
bool isNumber(char);
bool isEqual(char);

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

void adjustAB(Number&, Number&);
//Number +연산자 오버라이딩: a,b 조작 후 더하기
Number operator+(Number& no1, Number& no2) {
    if (no1.getPointCnt() != no2.getPointCnt()) {
        adjustAB(no1, no2);
    }

    Number no3;
    no3.setNumber(no1.getValue() + no2.getValue(), no1.getPointCnt());
    return no3;
}

Number operator-(Number& no1, Number& no2) {
    if (no1.getPointCnt() != no2.getPointCnt()) {
        adjustAB(no1, no2);
    }

    Number no3;
    no3.setNumber(no1.getValue() - no2.getValue(), no1.getPointCnt());
    return no3;
}

Number operator*(Number& no1, Number& no2) {
    Number no3;
    no3.setNumber(no1.getValue() * no2.getValue(), no1.getPointCnt() + no2.getPointCnt());
    return no3;
}

Number operator/(Number& no1, Number& no2) {
    Number no3;
    no3.setNumber(no1.getValue() / no2.getValue(), no1.getPointCnt() + no2.getPointCnt());
    return no3;

    //1234/0.123 = 10032.52032520325 (overflow)
    //1234/123 = 10.0325203252
}

//a와 b의 소숫점 자리수가 더 긴 쪽으로 맞춰 0 넣어주기
void adjustAB(Number& no1, Number& no2) {
    if (no1.getPointCnt() > no2.getPointCnt()) {
        while(no2.getPointCnt() < no1.getPointCnt()){
            no2.setNumber(no2.getValue() * 10, no2.getPointCnt() + 1);
        }
    }
    else {
        while (no1.getPointCnt() < no2.getPointCnt()) {
            no1.setNumber(no1.getValue() * 10, no1.getPointCnt() + 1);
        }
    }
}

bool isValidInput(char*);
int main() {
    Calculator cal;
    char input[100];

    cin.getline(input, 100);
    if (isValidInput(input)) {
        cal.calculate(input);
    }

}

//입력과정에서 16개의 정해진 문자만 입력되었는지 확인
bool isValidInput(char* input) {
    for (size_t i = 0; i < strlen(input); ++i) {
        if (!isNumber(input[i]) && !isOperator(input[i]) && !isEqual(input[i]) && input[i] != 'C' && input[i] != '.') {
            cout << "유효하지 않은 입력입니다." << endl;
            return false;
        }
    }
    return true;
}