#include "pch.h"
#include "CppUnitTest.h"
#include "../aois3/Bonding.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BondingTests
{
	TEST_CLASS(BondingTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			vector<bool> stakan1;
			std::string resultat;
			std::string resultat2;
			std::string sknf = "(-a-bc)|(-ab-c)|(-abc)|(ab-c)";
			std::string sdnf = "(-abc)|(a-b-c)|(a-bc)|(ab-c)|(abc)";
			resultat2 = "(-ac)&(-ab)&(b-c)";
			cout << sknf << endl;
			Bonding d(sknf, sdnf);
			resultat = d.BondingSKNF();
			Assert::AreEqual(resultat, resultat2);
			cout << resultat << endl;
			char vxod[40], vixod[40];
			int l = 0;
			d.SKNFToString(vxod, resultat);
			stack s;
			stack2 r;
			convert(s, vxod, vixod, l);
			stakan1 = TruthTable(vixod, r, l);
			resultat = d.Delete(stakan1);
			cout << resultat << endl;
			resultat2 = d.QuineMethod();
			cout << resultat2;
			cout << endl;
			d.GenerateKarnaughMap();
			cout << resultat;
		}
		TEST_METHOD(TestMethod2)
		{
			vector<bool> stakan1;
			std::string resultat;
			std::string resultat2;
			std::string sknf = "(-a-bc)|(-ab-c)|(-abc)|(ab-c)";
			std::string sdnf = "(-abc)|(a-b-c)|(a-bc)|(ab-c)|(abc)";
			resultat2 = "(-ac)&(b-c)";
			cout << sknf << endl;
			Bonding d(sknf, sdnf);
			resultat = d.BondingSKNF();
			cout << resultat << endl;
			char vxod[40], vixod[40];
			int l = 0;
			d.SKNFToString(vxod, resultat);
			stack s;
			stack2 r;
			convert(s, vxod, vixod, l);
			stakan1 = TruthTable(vixod, r, l);
			resultat = d.Delete(stakan1);
			Assert::AreEqual(resultat, resultat2);
			cout << resultat << endl;
			resultat2 = d.QuineMethod();
			cout << resultat2;
			cout << endl;
			d.GenerateKarnaughMap();
			cout << resultat;
		}
		TEST_METHOD(TestMethod3)
		{
			vector<bool> stakan1;
			std::string resultat;
			std::string resultat2;
			std::string resultat3;
			std::string sknf = "(-a-bc)|(-ab-c)|(-abc)|(ab-c)";
			std::string sdnf = "(-abc)|(a-b-c)|(a-bc)|(ab-c)|(abc)";
			resultat3 = "(-ac)&(b-c)";
			cout << sknf << endl;
			Bonding d(sknf, sdnf);
			resultat = d.BondingSKNF();
			cout << resultat << endl;
			char vxod[40], vixod[40];
			int l = 0;
			d.SKNFToString(vxod, resultat);
			stack s;
			stack2 r;
			convert(s, vxod, vixod, l);
			stakan1 = TruthTable(vixod, r, l);
			resultat = d.Delete(stakan1);
			cout << resultat << endl;
			resultat = d.QuineMethod();
			Assert::AreEqual(resultat, resultat3);
			cout << resultat2;
			cout << endl;
			d.GenerateKarnaughMap();
			cout << resultat;
		}
	};
}
