#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Number {
    int value;
    int pointCnt; //2�� �ʰ��� �� ����
};

class Calculator {
    Number a, b;
public:
    void calculate(char*);
    void classify(vector<char>);
    //void setValue(int x, int y);
    Number add();
    Number sub();
    Number mul();
    Number div();
};

vector<char> makeValid(char*);
void Calculator::calculate(char* input) {
    vector<char> tmp = makeValid(input);
    puts("makeValid :");
    for (size_t i = 0; i < tmp.size(); i++) {
        cout << tmp[i];
    }
    classify(makeValid(input));
}

bool isOperator(char);
bool isNumber(char);
bool isEqual(char);
//��ȿ ������ �ٲٱ�(ex: 1.1.1.1.1+2. -> 1.11+2.0 ä��)
vector<char> makeValid(char* input) {
    queue<char> q;
    vector<char> output;

    int tmpNo = 0;
    bool containDot = false;

    for (size_t i = 0; i < strlen(input); ++i) {
        q.push(input[i]);
        switch (q.front()) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            if (tmpNo < 1000) {
                tmpNo = 10 * tmpNo + (q.front() - 48);
                output.push_back(q.front());
            }
            break;
        case '.':
            if (output.empty()) {
                output.push_back('0');
                tmpNo = 10;
                output.push_back(q.front());
            }
            else {
                if (!containDot) {
                    if (isNumber(output.back())) {
                        tmpNo *= 10;
                        output.push_back(q.front());
                    }
                    else if (isOperator(output.back()) || isEqual(output.back())) {
                        output.push_back('0');
                        tmpNo = 10;
                        output.push_back(q.front());
                    }
                }
            }
            containDot = true;
            break;
        case '+': case '-': case '*': case '/':
            containDot = false;
            tmpNo = 0;
            //��ȿ�� �� ó���� ���ڰ� �ƴ� ��ȣ�� �� ��� �׺��� �տ� 0 �߰�
            if (output.empty()) {
                if (q.front() != '-') {
                    output.push_back('0');
                }
                output.push_back(q.front());
            }
            else {
                //������ ���̾->�� ������ ������ ä��
                if (isOperator(output.back())) {
                    output.pop_back();
                }
                if (output.back() == '.') {
                    output.push_back('0');
                }
                output.push_back(q.front());
            }
            break;
        case 'C':
            tmpNo = 0;
            output.clear();
            break;
        case '=':
            tmpNo = 0;
            if (output.back() == '.') {
                output.push_back('0');
            }
            output.push_back('=');
        }
        q.pop();
    }
    return output;
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

//��ȿ�� ���� queue<Number>, queue<Operator>�� �и��Ѵ�.
void Calculator::classify(vector<char> validInput) {
    /*for (size_t i = 0; i < validInput.size(); ++i) {
        if () {

        }
    }*/
}
//a�� b�� �Ҽ��� �ڸ����� �� �� ������ ���� 0 �־��ֱ�
void adjustAB(Number, Number) {

}
//������ �������̵�
//Number Calculator::operator+(const Number no) {
//    
//}

//Number Calculator::sub() {
//    return a - b;
//}
//
//Number Calculator::mul() {
//    return a - b;
//}
//
//Number Calculator::div() {
//    return a / b;
//}

bool isValidInput(char*);
int main() {
    Calculator cal;
    char input[100];

    cin.getline(input, 100);
    if (isValidInput(input)) {
        cal.calculate(input);
    }

}

bool isValidInput(char* input) {
    for (size_t i = 0; i < strlen(input); ++i) {
        if (!isNumber(input[i]) && !isOperator(input[i]) && !isEqual(input[i]) && input[i] != 'C' && input[i] != '.') {
            cout << "��ȿ���� ���� �Է��Դϴ�." << endl;
            return false;
        }
    }
    return true;
}