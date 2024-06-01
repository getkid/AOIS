#pragma once

#include <string>
#include <cmath>
#include "TruthTable.h"

class Bonding
{

private:
	int conjunctions_ = 0;
	int a = 0;
	int vars_ = 0;
	std::string sknf_;
	std::string sdnf_;
	std::string resultat;
	std::string resultat_1_1;
	string resultat2;
	string resultat_1_12;
	vector<vector<int>> quine_table_;
	vector<vector<int>> quine_table_1;
	vector<vector<bool>> karno_map;
	std::vector<std::vector<int>> num_sknf_;
	std::vector<std::vector<int>> num_sdnf_;
	std::vector<std::vector<int>> num_resultat;
	std::vector<std::vector<int>> quine_resultat;
	std::vector<std::vector<int>> num_resultat_1_1;
	std::vector<std::vector<int>> quine_resultat_1_1;

public:

	Bonding(std::string sknf, std::string sdnf)
	{
		sknf_ = sknf;
		sdnf_ = sdnf;
		for (int i = 0; sknf_[i] != ')'; i++)
		{
			if (sknf_[i] >= 'a' && sknf_[i] <= 'e') vars_++;
		}
		NumericalForm();
	}

	void NumericalForm()
	{
		std::vector<int> push_;
		num_sknf_.clear();
		num_sdnf_.clear();
		for (size_t i = 1; i < sknf_.size(); i++)
		{
			if (sknf_[i] >= 'a' && sknf_[i] <= 'e')
			{
				push_.push_back(1);
				continue;
			}
			if (sknf_[i] == '-')
			{
				push_.push_back(0);
				i++;
				continue;
			}
			else
			{
				i += 2;
				num_sknf_.push_back(push_);
				push_.clear();
			}
		}
		for (size_t i = 1; i < sdnf_.size(); i++)
		{
			if (sdnf_[i] >= 'a' && sdnf_[i] <= 'e')
			{
				push_.push_back(1);
				continue;
			}
			if (sdnf_[i] == '-')
			{
				push_.push_back(0);
				i++;
				continue;
			}
			else
			{
				i += 2;
				num_sdnf_.push_back(push_);
				push_.clear();
			}
		}
	}

	std::string BondingSKNF()
	{
		int i = 0;
		do {
			std::vector<bool> are_used_(num_sknf_.size());
			std::vector<int> push_;
			for (size_t i = 0; i < num_sknf_.size(); i++)
			{
				for (size_t j = 1; j + i < num_sknf_.size(); j++)
				{
					if (Comparison(num_sknf_[i], num_sknf_[i + j]))
					{
						are_used_[i] = 1; are_used_[i + j] = 1;
						for (size_t k = 0; k < num_sknf_[i].size(); k++)
						{
							if (num_sknf_[i][k] == num_sknf_[i + j][k]) push_.push_back(num_sknf_[i][k]);
							else push_.push_back(2);
						}
						num_resultat.push_back(push_);
						push_.clear();
					}
				}
			}
			for (size_t i = 0; i < are_used_.size(); i++)
			{
				if (!are_used_[i]) num_resultat.push_back(num_sknf_[i]);
			}
			conjunctions_ = num_sknf_.size();
			num_sknf_.clear();
			num_sknf_ = std::move(num_resultat);
			i++;
			if (i == num_sknf_.size())
			{
				NumSKNFToString();
				return resultat;
			}
		} while (conjunctions_ == num_sknf_.size());
		NumSKNFToString();
		return resultat;
	}

	std::string BondingSDNF()
	{
		int i = 0;
				do {
					std::vector<bool> are_used_(num_sdnf_.size());
					std::vector<int> push_;
					for (size_t i = 0; i < num_sdnf_.size(); i++)
					{
						for (size_t j = 1; j + i < num_sdnf_.size(); j++)
						{
							if (Comparison_1(num_sdnf_[i], num_sdnf_[i + j]))
							{
								are_used_[i] = 1; are_used_[i + j] = 1;
								for (size_t k = 0; k < num_sdnf_[i].size(); k++)
								{
									if (num_sdnf_[i][k] == num_sdnf_[i + j][k]) push_.push_back(num_sdnf_[i][k]);
									else push_.push_back(2);
								}
								num_resultat_1_1.push_back(push_);
								push_.clear();
							}
						}
					}
					for (size_t i = 0; i < are_used_.size(); i++)
					{
						if (!are_used_[i]) num_resultat_1_1.push_back(num_sdnf_[i]);
					}
					conjunctions_ = num_sdnf_.size();
					num_sdnf_.clear();
					num_sdnf_ = std::move(num_resultat_1_1);
					i++;
					if (i == num_sknf_.size())
					{
						NumSKNFToString_1();
						return resultat_1_1;
					}
				} while (conjunctions_ == num_sdnf_.size() || (num_sdnf_.size() > conjunctions_));
				NumSKNFToString_1();
				return resultat_1_1;
	}
		
			string Delete_1(vector<bool> stakan1)
			{
				vector<int> deleting;
				for (int i = 0; i < num_sdnf_.size(); i++)
				{
					resultat_1_12.clear();
					num_resultat_1_1.clear();
					num_resultat_1_1.assign(num_sdnf_.begin(), num_sdnf_.end());
					if (num_resultat_1_1.size() == 1)
					{
						NumSKNFToString2_1();
						return resultat_1_1;
					}
					num_resultat_1_1.erase(num_resultat_1_1.begin() + i);
					NumSKNFToString2_1();
					char vxod[40], vixod[40];
					int l = 0;
					SKNFToString_1(vxod, resultat_1_12);
					stack s;
					stack2 r;
					convert(s, vxod, vixod, l);
					vector<bool> stakan2 = TruthTable(vixod, r, l);
					if (Comparison_1(stakan1, stakan2)) deleting.push_back(i);
				}
				for (size_t i = 0; i < deleting.size(); i++)
				{
					num_sdnf_.erase(num_sdnf_.begin() + deleting[i]);
				}
				NumSKNFToString_1();
				return resultat_1_1;
			}
		
			bool Comparison_1(vector<bool> resultat_1_11, vector<bool> resultat_1_12)
			{
				if (resultat_1_11.size() != resultat_1_12.size()) return false;
				else
				{
					for (size_t i = 0; i < resultat_1_11.size(); i++)
					{
						if (resultat_1_11[i] != resultat_1_12[i]) break;
						if (i == resultat_1_11.size() - 1 && (resultat_1_11[i] == resultat_1_12[i])) return true;
					}
					return false;
				}
			}
		
			void NumSKNFToString_1()
			{
				resultat_1_1.clear();
				for (size_t i = 0; i < num_sdnf_.size(); i++)
				{
					for (size_t j = 1; i + j < num_sdnf_.size(); j++)
					{
						for (size_t k = 0; k < num_sdnf_[i].size(); k++)
						{
							if (num_sdnf_[i][k] != num_sdnf_[i + j][k]) break;
							if ((num_sdnf_[i][k] == num_sdnf_[i + j][k]) && (k == num_sdnf_[i].size() - 1)) {
								num_sdnf_.erase(num_sdnf_.begin() + i); j--;
							}
						}
					}
				}
				for (size_t i = 0; i < num_sdnf_.size(); i++)
				{
					resultat_1_1.append("(");
					for (size_t j = 0; j < num_sdnf_[i].size(); j++)
					{
						if (num_sdnf_[i][j] == 2) continue;
						AddToString_1(num_sdnf_[i][j], j);
					}
					if (i != num_sdnf_.size() - 1) { resultat_1_1.append(")|"); continue; }
					else resultat_1_1.append(")");
				}
			}
		
			void NumSKNFToString2_1()
			{
				resultat_1_1.clear();
				for (size_t i = 0; i < num_sdnf_.size(); i++)
				{
					for (size_t j = 1; i + j < num_sdnf_.size(); j++)
					{
						for (size_t k = 0; k < num_sdnf_[i].size(); k++)
						{
							if (num_sdnf_[i][k] != num_sdnf_[i + j][k]) break;
							if ((num_sdnf_[i][k] == num_sdnf_[i + j][k]) && (k == num_sdnf_[i].size() - 1)) num_sdnf_.erase(num_sdnf_.begin() + i);
						}
					}
				}
				for (size_t i = 0; i < num_resultat_1_1.size(); i++)
				{
					resultat_1_12.append("(");
					for (size_t j = 0; j < num_resultat_1_1[i].size(); j++)
					{
						if (num_resultat_1_1[i][j] == 2) continue;
						AddToString2_1(num_resultat_1_1[i][j], j);
					}
					if (i != num_resultat_1_1.size() - 1) { resultat_1_12.append(")|"); continue; }
					else resultat_1_12.append(")");
				}
			}
		
			void AddToString_1(int a, int index)
			{
				if (a == 0) resultat_1_1.append("-");
				if (index == 0) { resultat_1_1.append("a"); return; }
				if (index == 1) { resultat_1_1.append("b"); return; }
				if (index == 2) { resultat_1_1.append("c"); return; }
				if (index == 3) { resultat_1_1.append("d"); return; }
				if (index == 4) { resultat_1_1.append("e"); return; }
			}
		
			void AddToString2_1(int a, int index)
			{
				if (a == 0) resultat_1_12.append("-");
				if (index == 0) { resultat_1_12.append("a"); return; }
				if (index == 1) { resultat_1_12.append("b"); return; }
				if (index == 2) { resultat_1_12.append("c"); return; }
				if (index == 3) { resultat_1_12.append("d"); return; }
				if (index == 4) { resultat_1_12.append("e"); return; }
			}
		
			bool Comparison_1(std::vector<int> first, std::vector<int> second)
			{
				size_t j = 0;
				for (size_t i = 0; i < first.size(); i++)
				{
					if (first[i] == second[i]) j++;
				}
				if (j == first.size() - 1) return true;
				else return false;
			}
		
			void SKNFToString_1(char* vixod, string resultat_1_1ik)
			{
				int j = 0;
				for (int i = 0; i < resultat_1_1ik.size(); i++)
				{
					if (resultat_1_1ik[i] == '-') { vixod[i + j] = '!'; if (i == resultat_1_1ik.size() - 1) vixod[i + j + 1] = '\0'; continue; }
					if ((resultat_1_1ik[i] >= 'a' && resultat_1_1ik[i] <= 'e') && (resultat_1_1ik[i + 1] >= 'a' && resultat_1_1ik[i + 1] <= 'e'))
					{
						vixod[i + j] = resultat_1_1ik[i];
						vixod[i + 1 + j] = '&';
						vixod[i + 2 + j] = resultat_1_1ik[i + 1];
						i++; j++;
						if (i == resultat_1_1ik.size() - 1) vixod[i + j + 1] = '\0';
						continue;
					}
					if ((resultat_1_1ik[i] >= 'a' && resultat_1_1ik[i] <= 'e') && (resultat_1_1ik[i + 1] == '-'))
					{
						vixod[i + j] = resultat_1_1ik[i];
						vixod[i + 1 + j] = '&';
						vixod[i + 2 + j] = '!';
						vixod[i + 3 + j] = resultat_1_1ik[i + 2];
						i += 2; j++;
						if (i == resultat_1_1ik.size() - 1) vixod[i + j + 1] = '\0';
						continue;
					}
					else vixod[i + j] = resultat_1_1ik[i];
					if (i == resultat_1_1ik.size() - 1) vixod[i + j + 1] = '\0';
				}
		
			}
		
			string QuineMethod_1()
			{
				int k = 0;
				vector<int> push;
				num_sdnf_.clear();
				num_resultat_1_1.clear();
				NumericalForm();
				quine_resultat_1_1 = move(num_sdnf_);
				NumericalForm();
				BondingSDNF();
				num_resultat_1_1.clear();
				num_resultat_1_1.assign(num_sdnf_.begin(), num_sdnf_.end());
				for (size_t i = 0; i < quine_resultat_1_1.size(); i++)
				{
					for (size_t j = 0; j < num_sdnf_.size(); j++)
					{
						if (FindSubstring_1(quine_resultat_1_1[i], num_sdnf_[j])) push.push_back(1);
						else push.push_back(0);
					}
					quine_table_1.push_back(push);
					push.clear();
				}
				num_sdnf_.clear();
				for (size_t i = 0; i < quine_table_1.size(); i++)
				{
					if (notSuperfluous_1(quine_table_1[i], k)) num_sdnf_.push_back(num_resultat_1_1[k]);
				}
		
				NumSKNFToString_1();
				for (size_t i = 0; i < quine_table_1[0].size(); i++)
				{
					for (size_t j = 0; j < quine_table_1.size(); j++)
					{
						cout << quine_table_1[j][i] << " ";
					}
					cout << endl;
				}
				return resultat_1_1;
			}
		
			bool notSuperfluous_1(vector<int> column, int& index)
			{
				int j = 0;
				for (size_t i = 0; i < column.size(); i++)
				{
					if (column[i])
					{
						j++;
						index = i;
					}
				}
				if (j == 1) return true;
				return false;
			}
		
			bool FindSubstring_1(vector<int> string, vector<int> substring)
			{
				for (size_t i = 0; i < string.size(); i++)
				{
					if ((substring[i] && string[i]) || (!substring[i] && !string[i]) || (substring[i] == 2))
					{
						if (i == string.size() - 1) return true;
						continue;
					}
					return false;
				}
			}

	string Delete(vector<bool> stakan1)
	{
		vector<int> deleting;
		for (int i = 0; i < num_sknf_.size(); i++)
		{
			resultat2.clear();
			num_resultat.clear();
			num_resultat.assign(num_sknf_.begin(), num_sknf_.end());
			if (num_resultat.size() == 1)
			{
				NumSKNFToString2();
				return resultat;
			}
			num_resultat.erase(num_resultat.begin() + i);
			NumSKNFToString2();
			char vxod[40], vixod[40];
			int l = 0;
			SKNFToString(vxod, resultat2);
			stack s;
			stack2 r;
			convert(s, vxod, vixod, l);
			vector<bool> stakan2 = TruthTable(vixod, r, l);
			if (Comparison(stakan1, stakan2)) deleting.push_back(i);
		}
		for (size_t i = 0; i < deleting.size(); i++)
		{
			num_sknf_.erase(num_sknf_.begin() + deleting[i]);
		}
		NumSKNFToString();
		return resultat;
	}

	bool Comparison(vector<bool> resultat1, vector<bool> resultat2)
	{
		if (resultat1.size() != resultat2.size()) return false;
		else
		{
			for (size_t i = 0; i < resultat1.size(); i++)
			{
				if (resultat1[i] != resultat2[i]) break;
				if (i == resultat1.size() - 1 && (resultat1[i] == resultat2[i])) return true;
			}
			return false;
		}
	}

	void NumSKNFToString()
	{
		resultat.clear();
		for (size_t i = 0; i < num_sknf_.size(); i++)
		{
			for (size_t j = 1; i + j < num_sknf_.size(); j++)
			{
				for (size_t k = 0; k < num_sknf_[i].size(); k++)
				{
					if (num_sknf_[i][k] != num_sknf_[i + j][k]) break;
					if ((num_sknf_[i][k] == num_sknf_[i + j][k]) && (k == num_sknf_[i].size() - 1)) {
						num_sknf_.erase(num_sknf_.begin() + i); j--;
					}
				}
			}
		}
		for (size_t i = 0; i < num_sknf_.size(); i++)
		{
			resultat.append("(");
			for (size_t j = 0; j < num_sknf_[i].size(); j++)
			{
				if (num_sknf_[i][j] == 2) continue;
				AddToString(num_sknf_[i][j], j);
			}
			if (i != num_sknf_.size() - 1) { resultat.append(")&"); continue; }
			else resultat.append(")");
		}
	}

	void NumSKNFToString2()
	{
		resultat.clear();
		for (size_t i = 0; i < num_sknf_.size(); i++)
		{
			for (size_t j = 1; i + j < num_sknf_.size(); j++)
			{
				for (size_t k = 0; k < num_sknf_[i].size(); k++)
				{
					if (num_sknf_[i][k] != num_sknf_[i + j][k]) break;
					if ((num_sknf_[i][k] == num_sknf_[i + j][k]) && (k == num_sknf_[i].size() - 1)) num_sknf_.erase(num_sknf_.begin() + i);
				}
			}
		}
		for (size_t i = 0; i < num_resultat.size(); i++)
		{
			resultat2.append("(");
			for (size_t j = 0; j < num_resultat[i].size(); j++)
			{
				if (num_resultat[i][j] == 2) continue;
				AddToString2(num_resultat[i][j], j);
			}
			if (i != num_resultat.size() - 1) { resultat2.append(")&"); continue; }
			else resultat2.append(")");
		}
	}

	void AddToString(int a, int index)
	{
		if (a == 0) resultat.append("-");
		if (index == 0) { resultat.append("a"); return; }
		if (index == 1) { resultat.append("b"); return; }
		if (index == 2) { resultat.append("c"); return; }
		if (index == 3) { resultat.append("d"); return; }
		if (index == 4) { resultat.append("e"); return; }
	}

	void AddToString2(int a, int index)
	{
		if (a == 0) resultat2.append("-");
		if (index == 0) { resultat2.append("a"); return; }
		if (index == 1) { resultat2.append("b"); return; }
		if (index == 2) { resultat2.append("c"); return; }
		if (index == 3) { resultat2.append("d"); return; }
		if (index == 4) { resultat2.append("e"); return; }
	}

	bool Comparison(std::vector<int> first, std::vector<int> second)
	{
		size_t j = 0;
		for (size_t i = 0; i < first.size(); i++)
		{
			if (first[i] == second[i]) j++;
		}
		if (j == first.size() - 1) return true;
		else return false;
	}

	void SKNFToString(char* vixod, string resultatik)
	{
		int j = 0;
		for (int i = 0; i < resultatik.size(); i++)
		{
			if (resultatik[i] == '-') { vixod[i + j] = '!'; if (i == resultatik.size() - 1) vixod[i + j + 1] = '\0'; continue; }
			if ((resultatik[i] >= 'a' && resultatik[i] <= 'e') && (resultatik[i + 1] >= 'a' && resultatik[i + 1] <= 'e'))
			{
				vixod[i + j] = resultatik[i];
				vixod[i + 1 + j] = '|';
				vixod[i + 2 + j] = resultatik[i + 1];
				i++; j++;
				if (i == resultatik.size() - 1) vixod[i + j + 1] = '\0';
				continue;
			}
			if ((resultatik[i] >= 'a' && resultatik[i] <= 'e') && (resultatik[i + 1] == '-'))
			{
				vixod[i + j] = resultatik[i];
				vixod[i + 1 + j] = '|';
				vixod[i + 2 + j] = '!';
				vixod[i + 3 + j] = resultatik[i + 2];
				i += 2; j++;
				if (i == resultatik.size() - 1) vixod[i + j + 1] = '\0';
				continue;
			}
			else vixod[i + j] = resultatik[i];
			if (i == resultatik.size() - 1) vixod[i + j + 1] = '\0';
		}

	}

	string QuineMethod()
	{
		int k = 0;
		vector<int> push;
		num_sknf_.clear();
		num_resultat.clear();
		NumericalForm();
		quine_resultat = move(num_sknf_);
		NumericalForm();
		BondingSKNF();
		num_resultat.clear();
		num_resultat.assign(num_sknf_.begin(), num_sknf_.end());
		for (size_t i = 0; i < quine_resultat.size(); i++)
		{
			for (size_t j = 0; j < num_sknf_.size(); j++)
			{
				if (FindSubstring(quine_resultat[i], num_sknf_[j])) push.push_back(1);
				else push.push_back(0);
			}
			quine_table_.push_back(push);
			push.clear();
		}
		num_sknf_.clear();
		for (size_t i = 0; i < quine_table_.size(); i++)
		{
			if (notSuperfluous(quine_table_[i], k)) num_sknf_.push_back(num_resultat[k]);
		}

		NumSKNFToString();
		for (size_t i = 0; i < quine_table_[0].size(); i++)
		{
			for (size_t j = 0; j < quine_table_.size(); j++)
			{
				cout << quine_table_[j][i] << " ";
			}
			cout << endl;
		}
		return resultat;
	}

	bool notSuperfluous(vector<int> column, int& index)
	{
		int j = 0;
		for (size_t i = 0; i < column.size(); i++)
		{
			if (column[i])
			{
				j++;
				index = i;
			}
		}
		if (j == 1) return true;
		return false;
	}

	bool FindSubstring(vector<int> string, vector<int> substring)
	{
		for (size_t i = 0; i < string.size(); i++)
		{
			if ((substring[i] && string[i]) || (!substring[i] && !string[i]) || (substring[i] == 2))
			{
				if (i == string.size() - 1) return true;
				continue;
			}
			return false;
		}
	}

	/*int GrayCode(int num)
	{
		return num ^ (num >> 1);
	}*/

	void GenerateKarno(string expr)
	{
		vector<bool> push;
		if (vars_ == 1)
		{
			push = { 0, 1 };
			karno_map.push_back(push);
			return;
		}
		if (vars_ == 2)
		{
			vector<bool> stakan1;
			stack s;
			stack2 r;
			char vxod[40], vixod[40];
			int l = 0;
			size_t i;
			for (i = 0; i < expr.size(); i++)
			{
				vxod[i] = expr[i];
			}
			vxod[i] = '\0';
			convert(s, vxod, vixod, l);
			stakan1 = TruthTable(vixod, r, l);
			int k = pow(2, vars_) / 2;
			for (size_t i = 0, p = 0; i < 2; i++, p++)
			{
				push.clear();
				for (size_t j = 0; j < k; j++, p++)
				{
					push.push_back(stakan1[p]);
				}
				karno_map.push_back(push);
			}
		}
		if (vars_ == 3 || vars_ == 4)
		{
			vector<bool> stakan1;
			stack s;
			stack2 r;
			char vxod[40], vixod[40];
			int l = 0;
			size_t i;
			for (i = 0; i < expr.size(); i++)
			{
				vxod[i] = expr[i];
			}
			vxod[i] = '\0';
			convert(s, vxod, vixod, l);
			stakan1 = TruthTable(vixod, r, l);
			int k = pow(2, vars_) / 2;
			push.push_back(stakan1[0]); push.push_back(stakan1[1]);
			push.push_back(stakan1[3]); push.push_back(stakan1[2]);
			karno_map.push_back(push);
			push.clear();
			push.push_back(stakan1[4]); push.push_back(stakan1[5]);
			push.push_back(stakan1[7]); push.push_back(stakan1[6]);
			karno_map.push_back(push);
			push.clear();
			if (vars_ == 3) return;
			push.push_back(stakan1[12]); push.push_back(stakan1[13]);
			push.push_back(stakan1[15]); push.push_back(stakan1[14]);
			karno_map.push_back(push);
			push.clear();
			push.push_back(stakan1[8]); push.push_back(stakan1[9]);
			push.push_back(stakan1[11]); push.push_back(stakan1[10]);
		}
	}

	void PrintKarno()
	{
		for (size_t i = 0; i < karno_map.size(); i++)
		{
			for (size_t j = 0; j < karno_map[i].size(); j++)
			{
				cout << karno_map[i][j] << " ";
			}
			cout << endl;
		}
	}

	std::string MinimizeUsingKMapSKNF(std::vector<std::vector<int>>& kmap)
	{
		std::vector<std::string> groups;
		int size = kmap.size();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (kmap[i][j] == 1)
				{
					std::string group = FindGroupSKNF(kmap, i, j);
					if (!group.empty())
					{
						groups.push_back(group);
					}
				}
			}
		}
		return CombineGroups(groups);
	}

	std::string FindGroupSKNF(std::vector<std::vector<int>>& kmap, int row, int col)
	{
		std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
		int size = kmap.size();
		std::vector<std::pair<int, int>> groupCells = { {row, col} };
		kmap[row][col] = -1;
		for (size_t i = 0; i < groupCells.size(); i++)
		{
			int r = groupCells[i].first;
			int c = groupCells[i].second;
			for (auto& dir : directions)
			{
				int newRow = (r + dir.first + size) % size;
				int newCol = (c + dir.second + size) % size;

				if (kmap[newRow][newCol] == 1)
				{
					groupCells.push_back({ newRow, newCol });
					kmap[newRow][newCol] = -1;
				}
			}
		}
		return ConvertGroupToExpression(groupCells);
	}

	std::string ConvertGroupToExpression(std::vector<std::pair<int, int>>& groupCells)
	{
		std::vector<int> rowBits(vars_ / 2, -1);
		std::vector<int> colBits(vars_ / 2, -1);
		for (auto& cell : groupCells)
		{
			int row = cell.first;
			int col = cell.second;

			for (int i = 0; i < vars_ / 2; i++)
			{
				int rowBit = (row >> i) & 1;
				int colBit = (col >> i) & 1;

				if (rowBits[i] == -1)
				{
					rowBits[i] = rowBit;
				}
				else if (rowBits[i] != rowBit)
				{
					rowBits[i] = 2;
				}
				if (colBits[i] == -1)
				{
					colBits[i] = colBit;
				}
				else if (colBits[i] != colBit)
				{
					colBits[i] = 2;
				}
			}
		}
		std::string expression;
		for (int i = 0; i < vars_ / 2; i++)
		{
			if (rowBits[i] != 2)
			{
				expression += (rowBits[i] == 1 ? "" : "-") + std::string(1, 'a' + i);
			}
		}
		for (int i = 0; i < vars_ / 2; i++)
		{
			if (colBits[i] != 2)
			{
				expression += (colBits[i] == 1 ? "" : "-") + std::string(1, 'a' + vars_ / 2 + i);
			}
		}
		return expression;
	}

	std::string CombineGroups(std::vector<std::string>& groups)
	{
		std::string result;
		for (size_t i = 0; i < groups.size(); i++)
		{
			if (i != 0)
			{
				result += " | ";
			}
			result += groups[i];
		}
		return result;
	}
	std::string MinimizeUsingKMapSDNF(std::vector<std::vector<int>>& kmap)
	{
		std::vector<std::string> groups;
		int size = kmap.size();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (kmap[i][j] == 1)
				{
					std::string group = FindGroupSKNF(kmap, i, j);
					if (!group.empty())
					{
						groups.push_back(group);
					}
				}
			}
		}
		return CombineGroups(groups);
	}

	std::string FindGroupSDNF(std::vector<std::vector<int>>& kmap, int row, int col)
	{
		std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
		int size = kmap.size();
		std::vector<std::pair<int, int>> groupCells = { {row, col} };
		kmap[row][col] = -1;
		for (size_t i = 0; i < groupCells.size(); i++)
		{
			int r = groupCells[i].first;
			int c = groupCells[i].second;
			for (auto& dir : directions)
			{
				int newRow = (r + dir.first + size) % size;
				int newCol = (c + dir.second + size) % size;

				if (kmap[newRow][newCol] == 1)
				{
					groupCells.push_back({ newRow, newCol });
					kmap[newRow][newCol] = -1;
				}
			}
		}
		return ConvertGroupToExpression(groupCells);
	}

	std::string ConvertGroupToExpression2(std::vector<std::pair<int, int>>& groupCells)
	{
		std::vector<int> rowBits(vars_ / 2, -1);
		std::vector<int> colBits(vars_ / 2, -1);
		for (auto& cell : groupCells)
		{
			int row = cell.first;
			int col = cell.second;

			for (int i = 0; i < vars_ / 2; i++)
			{
				int rowBit = (row >> i) & 1;
				int colBit = (col >> i) & 1;

				if (rowBits[i] == -1)
				{
					rowBits[i] = rowBit;
				}
				else if (rowBits[i] != rowBit)
				{
					rowBits[i] = 2;
				}
				if (colBits[i] == -1)
				{
					colBits[i] = colBit;
				}
				else if (colBits[i] != colBit)
				{
					colBits[i] = 2;
				}
			}
		}
		std::string expression;
		for (int i = 0; i < vars_ / 2; i++)
		{
			if (rowBits[i] != 2)
			{
				expression += (rowBits[i] == 1 ? "" : "-") + std::string(1, 'a' + i);
			}
		}
		for (int i = 0; i < vars_ / 2; i++)
		{
			if (colBits[i] != 2)
			{
				expression += (colBits[i] == 1 ? "" : "-") + std::string(1, 'a' + vars_ / 2 + i);
			}
		}
		return expression;
	}

	std::string CombineGroups2(std::vector<std::string>& groups)
	{
		std::string result;
		for (size_t i = 0; i < groups.size(); i++)
		{
			if (i != 0)
			{
				result += " | ";
			}
			result += groups[i];
		}
		return result;
	}
};
