#pragma once
#include <vector>
#include <iostream>

class Matrix {
	bool matrix[16][16] = {
		{1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0},
		{0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0},
		{0,0,1,0,0,1,0,0,0,0,0,0,0,1,1,0},
		{0,0,1,0,1,0,1,1,0,0,0,1,0,1,0,0},
		{0,0,0,0,0,0,1,1,1,0,0,1,1,0,1,0},
		{0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0},
		{0,1,1,0,0,0,0,0,1,0,0,1,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,1,0,0,1,0},
		{0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0},
		{0,0,1,0,1,0,1,0,0,0,0,1,0,0,1,0},
		{0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0}
	};
	std::vector<bool> first;
	std::vector<bool> second;
	std::vector<bool> result;
	std::vector<bool> g;
	std::vector<bool> l;
	std::vector<bool> mix;
	bool s[5] = { 0,0,0,0,0 };
	int	des = 0;

public:
	std::vector<bool> read_word(int index) {
		result.clear();
		result.push_back(matrix[index][index]);
		for (int i = index + 1; i != index; i++)
		{
			if (i == 16) i = 0;
			result.push_back(matrix[i][index]);
			if (index == 0 && i == 0) break;
		}
		return result;
	}

	std::vector<bool> read_addressable_column(int index) {
		result.clear();
		result.push_back(matrix[index][index]);
		for (int i = index + 1, j = 0; i != index; i++, j++)
		{
			if (i == 16) i = 0;
			result.push_back(matrix[index][j]);
		}
		return result;
	}

	void insert(int index) {
		matrix[index][index] = result[0];
		for (int i = index + 1, j = 1; i != index; i++, j++)
		{
			if (i == 16) i = 0;
			matrix[i][index] = result[j];
		}
	}

	std::vector<bool> diz(int index1, int index2, int result_index) {
		first.clear();
		second.clear();
		read_word(index1);
		first.assign(result.begin(), result.end());
		read_word(index2);
		second.assign(result.begin(), result.end());
		result.clear();
		for (int i = 0; i < first.size(); i++)
		{
			if (first[i] == 1 || second[i] == 1) result.push_back(1);
			else result.push_back(0);
		}
		insert(result_index);
		return result;
	}

	std::vector<bool> pirs(int index1, int index2, int result_index) {
		first.clear();
		second.clear();
		read_word(index1);
		first.assign(result.begin(), result.end());
		read_word(index2);
		second.assign(result.begin(), result.end());
		result.clear();
		for (int i = 0; i < first.size(); i++)
		{
			if (first[i] == 1 || second[i] == 1) result.push_back(0);
			else result.push_back(1);
		}
		insert(result_index);
		return result;
	}

	std::vector<bool> zapret(int index1, int index2, int result_index) {
		first.clear();
		second.clear();
		read_word(index1);
		first.assign(result.begin(), result.end());
		read_word(index2);
		second.assign(result.begin(), result.end());
		result.clear();
		for (int i = 0; i < first.size(); i++)
		{
			if (first[i] == 1 && (!second[i]) == 1) result.push_back(1);
			else result.push_back(0);
		}
		insert(result_index);
		return result;
	}

	std::vector<bool> otriz(int index1, int index2, int result_index) {
		first.clear();
		second.clear();
		read_word(index1);
		first.assign(result.begin(), result.end());
		read_word(index2);
		second.assign(result.begin(), result.end());
		result.clear();
		for (int i = 0; i < first.size(); i++)
		{
			if (first[i] == 1 && (!second[i]) == 1) result.push_back(0);
			else result.push_back(1);
		}
		insert(result_index);
		return result;
	}

	void print()
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void sum(std::vector<bool> number) {
		result.clear();
		std::vector<bool> first;
		std::vector<bool> second;
		int j = 0;
		for (int i = 0; i < 16; i++)
		{
			j = 0;
			read_word(i);
			for (; j < number.size(); j++)
			{
				if (number[j] != result[j]) break;
				if (j == number.size() - 1 && number[j] == result[j])
				{
					j++;
					for (int k = 0; k < 4; k++, j++)
					{
						if (j + 8 > 15) j -= 16;
						first.push_back(result[j]);
						second.push_back(result[j + 4]);
					}
					for (int k = 3, l = 4; k >= 0; k--, l--)
					{
						plus(first[k], second[k], l);
					}
					j = 15;
					for (int l = 4; j > 10; j--, l--)
					{
						result[j] = s[l];
					}
					insert(i);
				}
			}
		}
	}

	void plus(bool first, bool second, int index) {
		if ((first == 1 && second == 0) || (first == 0 && second == 1))
		{
			if (!s[index]) s[index] = 1;
			else
			{
				s[index] = 0;
				s[index - 1] = 1;
			}
		}
		if (first == 0 && second == 0)
		{
			if (!s[index]) s[index] = 0;
			else s[index] = 1;
		}
		if (first == 1 && second == 1)
		{
			if (!s[index])
			{
				s[index] = 0;
				s[index - 1] = 1;
			}
			else 
			{
				s[index] = 1;
				s[index - 1] = 1;
			}
		}
	}

	int convert() {
		des = 0;
		for (int i = 15, j = 0; i > 0; i--, j++)
		{
			if (result[i]) des += pow(2, j);
		}
		return des;
	}

	void search(int first, int second) {
		for (int i = 0; i < 16; i++)
		{
			read_word(i);
			if (convert() >= first) g.push_back(1);
			else g.push_back(0);
			if (convert() <= second) l.push_back(1);
			else l.push_back(0);
		}
		for (int i = 0; i < g.size(); i++)
		{
			if (g[i] == 1 && l[i] == 1) mix.push_back(1);
			else mix.push_back(0);
		}
		for (int i = 0; i < mix.size(); i++)
		{
			if (mix[i])
			{
				read_word(i);
				for (int i = 0; i < result.size(); i++)
				{
					std::cout << result[i];
				}
				std::cout << std::endl;
			}
		}
	}
};