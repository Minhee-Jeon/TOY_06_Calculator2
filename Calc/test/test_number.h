#include <cxxtest/TestSuite.h>
#include <Number.h>

class Test_Number: public CxxTest::TestSuite 
{
public:

	void test_getPositionalNum() {
		Number n;

		n.setNumber(0, 1);
		TS_ASSERT_EQUALS(n.getPositionalNum(), 0);

		n.setNumber(1, 1);
		TS_ASSERT_EQUALS(n.getPositionalNum(), 1);
		n.setNumber(-1, 1);
		TS_ASSERT_EQUALS(n.getPositionalNum(), 1);

		n.setNumber(11, 1);
		TS_ASSERT_EQUALS(n.getPositionalNum(), 2);
		n.setNumber(-11, 1);
		TS_ASSERT_EQUALS(n.getPositionalNum(), 2);

		n.setNumber(111, 1);
		TS_ASSERT_EQUALS(n.getPositionalNum(), 3);
		n.setNumber(-111, 1);
		TS_ASSERT_EQUALS(n.getPositionalNum(), 3);

		n.setNumber(1111, 1);
		TS_ASSERT_EQUALS(n.getPositionalNum(), 4);
		n.setNumber(-1111, 1);
		TS_ASSERT_EQUALS(n.getPositionalNum(), 4);
	}

	void test_addNum() {
		Number n1, n2;

		//2 + 0.2 = 2.2
		n1.setNumber(20, 1);
		n2.setNumber(20, 2);
		TS_ASSERT_EQUALS((n1 + n2).getValue(), 220);
		TS_ASSERT_EQUALS((n1 + n2).getPointCnt(), 2);

		//1234 + 0.1234 = 1234.1234
		n1.setNumber(1234, 0);
		n2.setNumber(1234, 4);
		TS_ASSERT_EQUALS((n1 + n2).getValue(), 12341234);
		TS_ASSERT_EQUALS((n1 + n2).getPointCnt(), 4);
	}

	void test_subtractNum() {
		Number n1, n2;

		//3.002 - 5 = -1.998
		n1.setNumber(3002, 3);
		n2.setNumber(5, 0);
		TS_ASSERT_EQUALS((n1 - n2).getValue(), -1998);
		TS_ASSERT_EQUALS((n1 - n2).getPointCnt(), 3);
	}

	void test_mulNum() {
		Number n1, n2;

		//1234 * 0.1234 = 152.2756
		n1.setNumber(1234, 0);
		n2.setNumber(1234, 4);
		TS_ASSERT_EQUALS((n1 * n2).getValue(), 1522756);
		TS_ASSERT_EQUALS((n1 * n2).getPointCnt(), 4);
	}

	void test_divNum() {
		Number n1, n2;

		//1234 / 0.1234 = 10000
		n1.setNumber(1234, 0);
		n2.setNumber(1234, 4);
		TS_ASSERT_EQUALS((n1 / n2).getValue(), 10000);
		TS_ASSERT_EQUALS((n1 / n2).getPointCnt(), 0);

		//1234/0.123 = 10032.52032520325 
		n1.setNumber(1234, 0);
		n2.setNumber(123, 4);
		TS_ASSERT_EQUALS((n1 / n2).getValue(), 100330);
		TS_ASSERT_EQUALS((n1 / n2).getPointCnt(), 0);

		//1234/123 = 10.0325203252
		n1.setNumber(1234, 0);
		n2.setNumber(123, 0);
		TS_ASSERT_EQUALS((n1 / n2).getValue(), 10033);
		TS_ASSERT_EQUALS((n1 / n2).getPointCnt(), 3);
	}

};
