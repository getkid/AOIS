#include "pch.h"
#include "CppUnitTest.h"
#include "../aois7/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTests
{
    TEST_CLASS(MatrixTests)
    {
    public:

        TEST_METHOD(TestReadWord)
        {
            Matrix matrix;
            std::vector<bool> result = matrix.read_word(3);
            Assert::IsTrue(result.size() == 16);
            bool a;
            a = result[0];
            Assert::AreEqual(false, a);
            a = result[1];
            Assert::AreEqual(false, a);
            a = result[2];
            Assert::AreEqual(false, a);
        }

        TEST_METHOD(TestReadAddressableColumn)
        {
            Matrix matrix;
            std::vector<bool> result = matrix.read_addressable_column(2);

            bool a;
            a = result[0];
            Assert::AreEqual(false, a);
            a = result[1];
            Assert::AreEqual(false, a);
            a = result[2];
            Assert::AreEqual(false, a);
        }

        TEST_METHOD(TestDiz)
        {
            Matrix matrix;
            auto result = matrix.diz(1, 2, 2);

            bool a;
            a = result[0];
            Assert::AreEqual(false, a);
            a = result[1];
            Assert::AreEqual(true, a);
            a = result[2];
            Assert::AreEqual(true, a);
        }

        TEST_METHOD(TestPirs)
        {
            Matrix matrix;
            auto result = matrix.pirs(1, 2, 3);

            bool a;
            a = result[0];
            Assert::AreEqual(true, a);
            a = result[1];
            Assert::AreEqual(false, a);
            a = result[2];
            Assert::AreEqual(false, a);
        }

        TEST_METHOD(TestSum)
        {
            Matrix matrix;
            std::vector<bool> number = { 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0 };
            matrix.sum(number);
        }

        TEST_METHOD(TestSearch)
        {
            Matrix matrix;
            matrix.search(5, 10);
        }
    };
}
