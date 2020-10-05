#include <cxxtest/TestSuite.h>
#include <iostream>
#include <Number.h>

#include <Calculator.h>


class Test_Calculator: public CxxTest::TestSuite 
{
public:
	void test_charToNum() {
		Calculator cal;
		char* ch = NULL;
		Number number;

		ch = "2.141592";
		number = cal.charToNum(ch);
		TS_ASSERT_EQUALS(number.getValue(), 2141592);
		TS_ASSERT_EQUALS(number.getPointCnt(), 6);

		ch = "-123456";
		number = cal.charToNum(ch);
		TS_ASSERT_EQUALS(number.getValue(), -123456);
		TS_ASSERT_EQUALS(number.getPointCnt(), 0);
	}

	void test_numToChar() {
		Calculator cal;
		Number number;

		char* ch = NULL;
		//if (no.getPointCnt() == 0)
		number.setNumber(1234, 0);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "1234") == 0);
		delete[] ch;

		//else
		//(key > 0)
		ch = NULL;
		number.setNumber(1234, 3);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "1.234") == 0);
		delete[] ch;

		ch = NULL;
		number.setNumber(1234, 2);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "12.34") == 0);
		delete[] ch;

		ch = NULL;
		number.setNumber(1234, 1);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "123.4") == 0);
		delete[] ch;

		//(key == 0)
		ch = NULL;
		number.setNumber(123, 3);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "0.123") == 0);
		delete[] ch;

		ch = NULL;
		number.setNumber(12, 2);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "0.12") == 0);
		delete[] ch;

		ch = NULL;
		number.setNumber(1, 1);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "0.1") == 0);
		delete[] ch;

		//(key < 0)
		ch = NULL;
		number.setNumber(12, 3);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "0.012") == 0);
		delete[] ch;

		ch = NULL;
		number.setNumber(1, 3);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "0.001") == 0);
		delete[] ch;

		ch = NULL;
		number.setNumber(1, 2);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "0.01") == 0); 
		delete[] ch;
	}

	void test_isValidNum_Number() {
		__isValidNum_Number();
	}

	void test_makeValidNum_Number() {
		__makeValidNum_Number();
	}

	void test_isValidNum_char() {
		__isValidNum_char();
	}

	void test_makeValidNum_char() {
		__makeValidNum_char();
	}

	void test_calculate() {
		Calculator cal;
		Number answer;

		answer = cal.calculate("1*2-34");
		TS_ASSERT_EQUALS(answer.getValue(), 34);
		TS_ASSERT_EQUALS(answer.getPointCnt(), 0);
		cal.calculatorInit();
		
		answer = cal.calculate("1*2-34=");
		TS_ASSERT_EQUALS(answer.getValue(), -32);
		TS_ASSERT_EQUALS(answer.getPointCnt(), 0);
		cal.calculatorInit();

		answer = cal.calculate("1+2*.3=");
		TS_ASSERT_EQUALS(answer.getValue(), 9);
		TS_ASSERT_EQUALS(answer.getPointCnt(), 1);
		cal.calculatorInit();

		answer = cal.calculate("1+2*C.3=");
		TS_ASSERT_EQUALS(answer.getValue(), 3);
		TS_ASSERT_EQUALS(answer.getPointCnt(), 1);
		cal.calculatorInit();

		answer = cal.calculate("1+2*C.3=-0.8=");
		TS_ASSERT_EQUALS(answer.getValue(), -5);
		TS_ASSERT_EQUALS(answer.getPointCnt(), 1);
		cal.calculatorInit();

		answer = cal.calculate("1+2*C.3=-0.8");
		TS_ASSERT_EQUALS(answer.getValue(), 8);
		TS_ASSERT_EQUALS(answer.getPointCnt(), 1);
		cal.calculatorInit();

		answer = cal.calculate("1+2*.3==");
		TS_ASSERT_EQUALS(answer.getValue(), 27);
		TS_ASSERT_EQUALS(answer.getPointCnt(), 2);
		cal.calculatorInit();

		answer = cal.calculate("1+2*.3==.12345");
		TS_ASSERT_EQUALS(answer.getValue(), 12345);
		TS_ASSERT_EQUALS(answer.getPointCnt(), 5);
		cal.calculatorInit();

		answer = cal.calculate("0.02/3");
		TS_ASSERT_EQUALS(answer.getValue(), 3);
		TS_ASSERT_EQUALS(answer.getPointCnt(), 0);
		cal.calculatorInit();

	}

	void test_extractMinus() {
		__extractMinus();
	}
};
