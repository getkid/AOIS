#pragma once
#include "IntToBinary.h"

class DoubleToBinary
{
	double a_;
	bool binary_[32];

public:

	DoubleToBinary() = default;

	DoubleToBinary(double a)
	{
		a_ = a;
		if (a_ > 0) binary_[0] = 0;
		else
		{
			binary_[0] = 1;
			a = -a;
		}
		int i = 0, k = 8, j = 15;
		while (pow(2, i) < a_) i++;
		int st = i - 1;
		i += 126;
		IntToBinary exp(i);
		while (k > 0)
		{
			binary_[k] = exp.GetByIndex(j);
			k--;
			j--;
		}
		k = 31, j = 15;
		i = pow(2, 23) * ((a_ - pow(2, st)) / (pow(2, st + 1) - pow(2, st)));
			while (i / 2 != 1)
			{
				binary_[k] = i % 2;
				k--;
				i /= 2;
			}
			binary_[k] = i % 2;
			binary_[k - 1] = i / 2;
			k -= 2;
			while (k > 8)
			{
				binary_[k] = 0;
				k--;
			}
	}

	void PrintBinary()
	{
		int i = 0;
		while (i < 32)
		{
			std::cout << binary_[i] << " ";
			i++;
		}
		std::cout << std::endl;
	}

	double BinaryToDouble()
	{
		int i = 7, degree = 1, exp;
		double decimal = 0;
		if (binary_[8] == 1) decimal += 1;
		while (i > 0)
		{
			if (binary_[i] == 1) decimal += pow(2, degree);
			degree++;
			i--;
		}
		degree = decimal - 127;
		exp = pow(2, degree);
		i = 9, decimal = 0, degree = -1;
		while (i < 31)
		{
			if (binary_[i] == true) decimal += pow(2, degree);
			degree--;
			i++;
		}
		decimal += 1;
		decimal *= exp;
		std::cout << decimal << std::endl;
		if (binary_[0]) decimal = -decimal;
		return decimal;
	}
	
	double ExpToDouble()
	{
		int i = 7, degree = 1, exp;
		double decimal = 0;
		if (binary_[8] == 1) decimal += 1;
		while (i > 0)
		{
			if (binary_[i] == 1) decimal += pow(2, degree);
			degree++;
			i--;
		}
		degree = decimal - 127;
		exp = pow(2, degree);
		return exp;
	}

	DoubleToBinary Sum(DoubleToBinary& second)
	{
		DoubleToBinary res;
		if (ExpToDouble() == second.ExpToDouble())
		{
			int i = 1;
			res.binary_[0] = 0;
			while (i < 10)
			{
				res.binary_[i] = second.binary_[i];
				i++;
			}
			i = 31;
			int k = 0, overflow = 0;
			while (i >= 9)
			{
				if (overflow) { k = binary_[i] + second.GetByIndex(i) + 1; overflow = 0; }
				else k = binary_[i] + second.GetByIndex(i);
				if ((i == 9) && (k == 2 || k == 3)) { res.Sdvig(); res.PrintBinary(); return res; }
				if (k == 2)
				{
					res.SetByIndex(0, i);
					overflow = 1;
				}
				if (k == 3)
				{
					res.SetByIndex(1, i);
					overflow = 1;
				}
				if (k == 1) res.SetByIndex(1, i);
				if (!k) res.SetByIndex(0, i);
				i--;
			}
			res.PrintBinary();
			res.BinaryToDouble();
			return res;
		}
	}

	void SetByIndex(bool numb, int i)
	{
		binary_[i] = numb;
	}

	bool GetByIndex(int i)
	{
		return binary_[i];
	}

	void Sdvig()
	{
		/*while (!binary_[i]) { k--; i--; }*/
		int i = 9;
		while (i < 30)
		{
			binary_[i] = binary_[i + 1];
			i++;
		}
		binary_[9] = false;
	}
};

