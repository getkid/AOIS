#pragma once
#include <iostream>

class IntToBinary
{
	int a_;
	bool binary_[16];
	bool reverse_[16];
	bool ancillary_[16];


public:

	IntToBinary() = default;
	IntToBinary(int a)
	{
		a_ = a;
		if (a_ > 0) binary_[0] = 0;
		else
		{
			binary_[0] = 1;
			a = -a;
		}
		int i = 15;
		while (a / 2 != 1)
		{
			binary_[i] = a % 2;
			i--;
			a /= 2;
		}
		binary_[i] = a % 2;
		binary_[i - 1] = a / 2;
		i -= 2;
		while (i > 0)
		{
			binary_[i] = 0;
			i--;
		}
	}

	void BinaryToInt()
	{
		int i = 14, decimal = 0, degree = 1;
		if (binary_[15] == 1) decimal += 1;
		while (i > 0)
		{
			if (binary_[i] == 1) decimal += pow(2, degree);
			degree++;
			i--;
		}
		if (binary_[0]) decimal = -decimal;
		std::cout << decimal << std::endl;
	}

	void AncillaryToInt()
	{
		int i = 14, decimal = 0, degree = 1;
		if (ancillary_[15] == 1) decimal += 1;
		while (i > 0)
		{
			if (ancillary_[i] == 1) decimal += pow(2, degree);
			degree++;
			i--;
		}
		if (ancillary_[0]) decimal = -decimal;
		std::cout << decimal << std::endl;
	}

	void AncillaryToBinary()
	{
		AncillaryCode();
		int i = 0;
		while (i < 16)
		{
			binary_[i] = ancillary_[i];
			i++;
		}
	}

	void ReverseCode()
	{
		int i = 0;
		if (a_ > 0) while (i < 16) { reverse_[i] = binary_[i]; i++; }
		else
		{
			reverse_[i] = binary_[i];
			i++;
			while (i < 16)
			{
				if (binary_[i] == 0) reverse_[i] = 1;
				else reverse_[i] = 0;
				i++;
			}
		}
	}

	void AncillaryToReverse()
	{
		int i = 0;
		reverse_[i] = ancillary_[i];
		i++;
		while (i < 16)
		{
			if (ancillary_[i] == 0) reverse_[i] = 1;
			else reverse_[i] = 0;
			i++;
		}
	}

	void ReverseToBinary()
	{
		int i = 15;
		binary_[0] = reverse_[0];
		while (reverse_[i])
		{
			binary_[i] = 0;
			i--;
		}
			binary_[i] = 1;
		i--;
		while (i >= 0)
		{
			binary_[i] = reverse_[i];
			i--;
		}
	}

	void AncillaryCode()
	{
		ReverseCode();
		int i = 15;
		if (a_ > 0) while (i >= 0) { ancillary_[i] = binary_[i]; i--; }
		else
		{
			ancillary_[0] = reverse_[0];
			while (reverse_[i])
			{
				ancillary_[i] = 0;
				i--;
			}
			ancillary_[i] = 1;
			i--;
			while (i >= 0)
			{
				ancillary_[i] = reverse_[i];
				i--;
			}
		}
	}

	IntToBinary SumInAncillary(IntToBinary& second)
	{
		IntToBinary res;
		int i = 15;
		int k = 0, overflow = 0;
		if (a_ < 0) AncillaryToBinary();
		if (second.GetInt() < 0) second.AncillaryToBinary();
			while (i >= 0)
			{
				if (overflow) {k = binary_[i] + second.GetByIndex(i) + 1; overflow = 0;}
				else k = binary_[i] + second.GetByIndex(i);
				if (k == 2)
				{
					res.SetByIndexAncillary(0, i);
					overflow = 1;
				}
				if (k == 3)
				{
					res.SetByIndexAncillary(1, i);
					overflow = 1;
				}
				if (k == 1) res.SetByIndexAncillary(1, i);
				if (!k) res.SetByIndexAncillary(0, i);
				i--;
			}
			res.PrintAncillary();
		if (res.GetByIndexAncillary(0) == true)
		{
			res.AncillaryToReverse();
			res.ReverseToBinary();
			res.PrintBinary();
		}
		return res;
	}
	
	IntToBinary SumInMulti(IntToBinary& second)
	{
		IntToBinary res;
		int i = 15;
		int k = 0, overflow = 0;
		if (a_ < 0) AncillaryToBinary();
		if (second.GetInt() < 0) second.AncillaryToBinary();
		while (i >= 0)
		{
			if (overflow) { k = ancillary_[i] + second.GetByIndex(i) + 1; overflow = 0; }
			else k = ancillary_[i] + second.GetByIndex(i);
			if (k == 2)
			{
				res.SetByIndexAncillary(0, i);
				overflow = 1;
			}
			if (k == 3)
			{
				res.SetByIndexAncillary(1, i);
				overflow = 1;
			}
			if (k == 1) res.SetByIndexAncillary(1, i);
			if (!k) res.SetByIndexAncillary(0, i);
			i--;
		}
		/*res.PrintAncillary();*/
		if (res.GetByIndexAncillary(0) == true)
		{
			res.AncillaryToReverse();
			res.ReverseToBinary();
			res.PrintBinary();
		}
		return res;
	}

	void Multiplication(IntToBinary& first, IntToBinary& second)
	{
		int i = 0, k = 0, st = 0;
		IntToBinary acc_adder(first), multiplayer(second), multi(first);
		while (i < 16)
		{
			acc_adder.SetByIndex(0, i);
			i++;
		}
		i = 0;
		while (i < 16)
		{
			multi.SetByIndex(first.GetByIndex(i), i);
			multiplayer.SetByIndex(second.GetByIndex(i), i);
			i++;
		}
		acc_adder = acc_adder.SumInAncillary(multi);
		while (k < 15)
		{
			st = k;
			k = multiplayer.MultiplayerMinusOne();
			if (k > 70) break;
			multi.Sdvig(k - st);
			acc_adder = acc_adder.SumInMulti(multi);
		}
		acc_adder.PrintAncillary();
		acc_adder.AncillaryToInt();
	}

	int MultiplayerMinusOne()
	{
		int i = 15, k = 0;
		while (!binary_[i])
		{
			i--;
			if (i == -1) return true;
		}
		binary_[i] = 0;
		i = 15;
		while (!binary_[i] && k < 15) { k++; i--; }
		if (k == 15) return 100;
		return k;
	}
	
	void Divide(IntToBinary& dividend, IntToBinary& divisor)
	{
		if (divisor.GetInt() == 0)
		{
			std::cerr << "Error" << std::endl;
			return;
		}
		bool resultSign = (dividend.GetInt() < 0) ^ (divisor.GetInt() < 0);
		IntToBinary absDividend = dividend;
		IntToBinary absDivisor = divisor;
		if (dividend.GetInt() < 0)
			absDividend.SetByIndex(0, 0);
		if (divisor.GetInt() < 0)
			absDivisor.SetByIndex(0, 0);
		int dividendInt = absDividend.GetInt();
		int divisorInt = absDivisor.GetInt();
		int quotientInt = dividendInt / divisorInt;
		int remainderInt = dividendInt % divisorInt;
		IntToBinary quotient(quotientInt);
		IntToBinary remainder(remainderInt);
		std::cout << "Divi: ";
		quotient.PrintBinary();
		std::cout << "Ost: ";
		remainder.PrintBinary();
		double result = static_cast<double>(quotientInt) + static_cast<double>(remainderInt) / static_cast<double>(divisorInt);

		if (resultSign)
			result = -result;
		std::cout << std::fixed << std::setprecision(5) << "Res: " << result << std::endl;
	}

	void Sdvig(int k)
	{
		int i = 15;
		/*while (!binary_[i]) { k--; i--; }*/
		i = 0;
		while (i < 16 - k) 
		{
			binary_[i] = binary_[i + k]; 
			i++;
		} 
		while (i < 16)
		{
			binary_[i] = false;
			i++;
		}
	 }

	int GetInt()
	{
		return a_;
	}

	void SetByIndex(bool numb, int i)
	{
		binary_[i] = numb;
	}
	
	void SetByIndexAncillary(bool numb, int i)
	{
		ancillary_[i] = numb;
	}

	bool GetByIndex(int i)
	{
		return binary_[i];
	}

	bool GetByIndexAncillary(int i)
	{
		return ancillary_[i];
	}

	void PrintReverse()
	{
		int i = 0;
		while (i < 16)
		{
			std::cout << reverse_[i] << " ";
			i++;
		}
		std::cout << std::endl;
	}

	void PrintAncillary()
	{
		int i = 0;
		while (i < 16)
		{
			std::cout << ancillary_[i] << " ";
			i++;
		}
		std::cout << std::endl;
	}
	
	void PrintBinary()
	{
		int i = 0;
		while (i < 16)
		{
			std::cout << binary_[i] << " ";
			i++;
		}
		std::cout << std::endl;
	}
	
};

