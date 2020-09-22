#include <cxxtest/TestSuite.h>
#include <iostream>
#include "Number.h"
#include "Calculator.h"

class Test_Number: public CxxTest::TestSuite 
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

		//else
		//(key > 0)
		number.setNumber(1234, 3);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "1.234") == 0);

		number.setNumber(1234, 2);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "12.34") == 0);

		number.setNumber(1234, 1);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "123.4") == 0);

		//(key == 0)
		number.setNumber(123, 3);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "0.123") == 0);

		number.setNumber(12, 2);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "0.12") == 0);

		number.setNumber(1, 1);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "0.1") == 0);

		//(key < 0)
		number.setNumber(12, 3);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "0.012") == 0);

		number.setNumber(1, 3);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "0.001") == 0);

		number.setNumber(1, 2);
		ch = cal.numToChar(number);
		TS_ASSERT(strcmp(ch, "0.01") == 0);
	}
};
