#include "pch.h"
#include "CppUnitTest.h"
#include "../aois1/DoubleToBinary.h"
#include "../aois1/IntToBinary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntToBinaryTests
{
    TEST_CLASS(IntToBinaryTest)
    {
    public:

        TEST_METHOD(TestBinaryConversion)
        {
            IntToBinary num1(10);
            Assert::AreEqual(num1.GetInt(), 10);
            bool expectedBinary[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0 };
            for (int i = 0; i < 16; i++)
            {
                Assert::AreEqual(num1.GetByIndex(i), expectedBinary[i]);
            }
        }

        TEST_METHOD(TestAncillaryCodeConversion)
        {
            IntToBinary num1(-10);
            num1.AncillaryCode();
            bool expectedAncillary[16] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0 };
            for (int i = 0; i < 16; i++)
            {
                Assert::AreEqual(num1.GetByIndexAncillary(i), expectedAncillary[i]);
            }
        }

        TEST_METHOD(TestDivision)
        {
            IntToBinary dividend(25);
            IntToBinary divisor(4);
            std::ostringstream oss;
            std::streambuf* pbuf = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            dividend.Divide(dividend, divisor);
            std::cout.rdbuf(pbuf);
            std::string result = oss.str();
            bool expectedResult[16] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0 };
            Assert::AreEqual(result, expectedResult);
        }
        TEST_METHOD(TestDoubleConversion)
        {
            DoubleToBinary num(10.25);
            double result = num.BinaryToDouble();
            Assert::AreEqual(result, 10.25, 0.00001);
        }

        TEST_METHOD(TestBinaryRepresentation)
        {
            DoubleToBinary num(10.25);
            bool expectedBinary[32] = {010000010010010000000000000000000};
            for (int i = 0; i < 32; i++)
            {
                Assert::AreEqual(num.GetByIndex(i), expectedBinary[i]);
            }
        }

        TEST_METHOD(TestSum)
        {
            DoubleToBinary num1(5.5);
            DoubleToBinary num2(4.75);
            DoubleToBinary result = num1.Sum(num2);
            double resultValue = result.BinaryToDouble();
            Assert::AreEqual(resultValue, 10.25);
        }

        TEST_METHOD(TestNegativeDoubleConversion)
        {
            DoubleToBinary num(-7.125);
            double result = num.BinaryToDouble();
            Assert::AreEqual(result, -7.125);
        }

        TEST_METHOD(TestExpToDouble)
        {
            DoubleToBinary num(32.0);
            double expResult = num.ExpToDouble();
            Assert::AreEqual(expResult, 32.0);
        }
    };

}
