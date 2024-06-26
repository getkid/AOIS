#include "pch.h"
#include "CppUnitTest.h"
#include "../5.3(2)/TruthTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TruthTableTests
{
	TEST_CLASS(TruthTableTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char vxod[9] = {"(a|b)&!c"}, vixod[200];
			int l = 0, var = 0;
			stack s;
			stack2 r;
			convert(s, vxod, vixod, l);
			var = TruthTable(vixod, r, l);
			Assert::IsTrue(var == 3);
		}
		TEST_METHOD(TestMethod2)
		{
			char vxod[7] = { "(a&!a)" }, vixod[200];
			int l = 0;
			stack s;
			stack2 r;
			convert(s, vxod, vixod, l);
			Assert::IsTrue(TruthTable(vixod, r, l) == 1);
		}
		TEST_METHOD(TestMethod3)
		{
			char vxod[11] = { "(a~d)&e|!b" }, vixod[200];
			int l = 0;
			stack s;
			stack2 r;
			convert(s, vxod, vixod, l);
			Assert::IsTrue(TruthTable(vixod, r, l) == 4);
		}
	};
}
