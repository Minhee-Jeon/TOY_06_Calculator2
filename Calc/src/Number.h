#ifndef NUMBER_H
#define NUMBER_H
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
    int pointCnt; 
};

//Number형 사칙연산 오버라이딩
Number operator+(Number&, Number&);
Number operator-(Number&, Number&);
Number operator*(Number&, Number&);
Number operator/(Number&, Number&);



#endif