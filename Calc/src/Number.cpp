#include "Number.h"
#include <cmath>
#include <iostream>
using namespace std;

void Number::setNumber(int val, int cnt) {
    this->value = val;
    this->pointCnt = cnt;
}

void Number::setNumber(int val, int cnt, bool NaN) {
    this->value = val;
    this->pointCnt = cnt;
    this->NaN = NaN; 
}

int Number::getValue() {
    return this->value;
}

int Number::getPointCnt() {
    return this->pointCnt;
}

//value�� �ڸ��� ���ϱ�
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

bool Number::getNaN() {
    return this->NaN;
}

void adjustAB(Number&, Number&);
Number operator+(Number& no1, Number& no2) {
    if (no1.getPointCnt() != no2.getPointCnt()) {
        adjustAB(no1, no2);
    }
    Number no3;
    no3.setNumber(no1.getValue() + no2.getValue(), 
                  no1.getPointCnt(), 
                  no1.getNaN() || no2.getNaN());
    return no3;
}

Number operator-(Number& no1, Number& no2) {
    if (no1.getPointCnt() != no2.getPointCnt()) {
        adjustAB(no1, no2);
    }

    Number no3;
    no3.setNumber(no1.getValue() - no2.getValue(), 
                  no1.getPointCnt(),
                  no1.getNaN() || no2.getNaN());
    return no3;
}

Number operator*(Number& no1, Number& no2) {
    Number no3;
    no3.setNumber(no1.getValue() * no2.getValue(), 
                  no1.getPointCnt() + no2.getPointCnt(),
                  no1.getNaN() || no2.getNaN());
    return no3;
}

Number operator/(Number& no1, Number& no2) {
    Number no3;

    //������ ���� 0�� �� NaN ����� true�� Number�� ���⸮��
    if (no2.getValue() == 0) {
        no3.setNumber(0, 0, true);
        return no3;
    }

    double divResult = (double)no1.getValue() / (double)no2.getValue();
    divResult = (round(divResult * 1000)) / 1000.0; //�Ҽ��� ��°�ڸ������� ����
    int toInt = divResult;

    int additionalPointCnt = 0;
    no3.setNumber(no1.getValue() / no2.getValue(), no1.getPointCnt() - no2.getPointCnt());

    //������ ����������� ���� ��
    if (divResult != toInt) {
        while (divResult - (divResult - toInt) != divResult) {
            divResult *= 10;
            toInt = divResult;
            additionalPointCnt += 1;
        }
    }
    no3.setNumber(toInt, no3.getPointCnt() + additionalPointCnt);

    //Number(1, -4) -> Number(10000, 1)
    if (no3.getPointCnt() < 0) {
        for (int i = no3.getPointCnt(); i != 0; ++i) {
            no3.setNumber(no3.getValue() * 10, no3.getPointCnt() + 1);
        }
    }
    return no3;

}

//a�� b�� �Ҽ��� �ڸ����� �� �� ������ ���� 0 �־��ֱ�
void adjustAB(Number& no1, Number& no2) {
    if (no1.getPointCnt() > no2.getPointCnt()) {
        while (no2.getPointCnt() < no1.getPointCnt()) {
            no2.setNumber(no2.getValue() * 10, no2.getPointCnt() + 1);
        }
    }
    else {
        while (no1.getPointCnt() < no2.getPointCnt()) {
            no1.setNumber(no1.getValue() * 10, no1.getPointCnt() + 1);
        }
    }
}