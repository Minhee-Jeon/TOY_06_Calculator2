#ifndef NUMBER_H
#define NUMBER_H
class Number {
public:
    Number() :value(0), pointCnt(0), NaN(false)
    {
    }

    void setNumber(int, int);
    void setNumber(int, int, bool);
    int getValue();
    int getPointCnt();
    int getPositionalNum();
    bool getNaN();

private:
    int value;
    int pointCnt; 
    bool NaN;
};

//Number�� ��Ģ���� �������̵�
Number operator+(Number&, Number&);
Number operator-(Number&, Number&);
Number operator*(Number&, Number&);
Number operator/(Number&, Number&);



#endif