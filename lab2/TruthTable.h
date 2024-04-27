#include <iostream>
#include <vector>

using namespace std;

struct TNode
{
	char inf;
	TNode* a;
};

struct Node
{
	double inf;
	Node* a;
};

struct stack2
{
	Node* top = NULL;
	void push(double inf)
	{
		Node* spt = new Node;
		spt->inf = inf;
		spt->a = top;
		top = spt;
	}
	void del(Node* spt)
	{
		if (!spt->a || !spt->a->a)
		{
			pop();
			delete top;
			top = NULL;
			return;
		}
		for (int i = 0; i < 2; i++) pop();
	}
	void pop()
	{
		Node* spt = top;
		top = top->a;
		delete spt;
	}
	bool empty()
	{
		if (top) return false;
		return true;
	}
};


struct stack
{
	TNode* top = NULL;
	int l = 0, k = 0;
	bool empty()
	{
		if (top) return false;
		return true;
	}
	void push(int inf)
	{
		TNode* spt = new TNode;
		spt->inf = inf;
		spt->a = top;
		top = spt;
	}
	void pop()
	{
		TNode* spt = top;
		top = top->a;
		delete spt;
	}
};
void convert(stack, char[], char[], int&), NumericForms(vector<bool> resultat, int var1, int var0), IndexForm(vector<bool> resultat);
double result(char[], stack2, int, vector<bool>, int); bool prior2(bool, bool, char);
int menu(); double prior(char);
bool diz(bool a, bool b), kon(bool a, bool b), inverse(bool a), impl(bool a, bool b), equals(bool a, bool b);
int TruthTable(char vixod[], stack2 r, int l);
vector<bool> PlusOne(int, vector<bool>);

int sdnf(vector<vector<bool>> table, vector<bool> resultat, string vars, int var)
{
	string sdnf;
	int i = 0, j = 0;
	for (int i = 0; i < resultat.size(); i++)
	{
		if (resultat[i]) j++;
	}
	for (int k = 0; k < resultat.size(); k++)
	{
		if (resultat[k])
		{
			sdnf.append("(");
			for (int j = 0; j < var; j++)
			{
				if (!table[k][j]) 
				{
					sdnf.append("-");
					sdnf.push_back(vars[j]);
					sdnf.append("&");
				}
				else
				{
					sdnf.push_back(vars[j]);
					sdnf.append("&");
				}
			}
			i++;
			if (i != j) sdnf.append(")|");
			else sdnf.append(")");
		}
	}
	cout << sdnf << endl;
	return j;
}

int sknf(vector<vector<bool>> table, vector<bool> resultat, string vars, int var)
{
	string sknf;
	int i = 0, j = 0;
	for (int i = 0; i < resultat.size(); i++)
	{
		if (!resultat[i]) j++;
	}
	for (int k = 0; k < resultat.size(); k++)
	{
		if (!resultat[k])
		{
			sknf.append("(");
			for (int j = 0; j < var; j++)
			{
				if (table[k][j])
				{
					sknf.append("-");
					sknf.push_back(vars[j]);
					sknf.append("|");
				}
				else
				{
					sknf.push_back(vars[j]);
					sknf.append("|");
				}
			}
			i++;
			if (i != j) sknf.append(")&");
			else sknf.append(")");
		}
	}
	cout << sknf << endl;
	return j;
}

bool* CheckUni(bool univ_vars[5], int &ind)
{
	for (int i = 0; i < 5; i++)
	{
		if (univ_vars[i] == 1)
		{
			univ_vars[i] = 0;
			ind = i;
			return univ_vars;
		}
	}
	return univ_vars;
}


int main()
{
	char vxod[200], vixod[200];
	int l = 0, var = 0;
	stack s;
	stack2 r;
	/*vector<bool> push = { 1, 0, 1 };*/
	cout << "Enter the line: ";
	gets_s(vxod);
	/*while (true)
	{
		switch (menu())
		{
		case 1: convert(s, vxod, vixod, l);
			for (int i = 0; i < l; i++) cout << vixod[i];
			cout << endl;
			if (s.empty()) cout << "Pysto" << endl;
			var = TruthTable(vixod, r, l);
			break;
		case 2: cout << result(vixod, r, l, push, var) << endl;
			delete r.top;
			if (r.empty()) cout << "Pysto" << endl;
			break;
		case 3: return 0;
		}
	}*/
	convert(s, vxod, vixod, l);
	for (int i = 0; i < l; i++) cout << vixod[i];
	cout << endl;
	if (s.empty()) cout << "Pysto" << endl;
	var = TruthTable(vixod, r, l);
	return 0;
}


//int menu()
//{
//	cout << "Select: " << endl;
//	cout << "1.Veiw a rpr" << endl;
//	cout << "2.View a result" << endl;
//	cout << "3.Exit" << endl;
//	int ch; cin >> ch;
//	return ch;
//}

void convert(stack s, char vxod[], char vixod[], int& l)
	{
	double k = 0, p = 0;
	for (int i = 0; i < strlen(vxod); i++)
	{
		k = prior(vxod[i]);
		if (k == 10) continue;
		if (k == -2)
		{
			vixod[l] = vxod[i];
			vixod[l + 1] = ' ';
			l += 2;
			continue;
		}
		if (k > 0 && k < 4)
		{
			s.push(vxod[i]);
			/*if (!s.top->a || !s.top->a->a || s.top->a->inf == '(') continue;*/
			TNode* spt = s.top;
			while (spt->a)
			{
				if (spt->a->inf == '(') break;
				p = prior(spt->a->inf);
				if (p >= k)
				{
					vixod[l] = spt->a->inf;
					vixod[l + 1] = ' ';
					l += 2;
					TNode* t = spt->a;
					spt->a = spt->a->a;
					delete t;
					continue;
				}
				spt = spt->a;
			}
			continue;
		}
		if (k == 0)
		{
			s.push(vxod[i]);
			continue;
		}
		if (k == -1)
		{
			TNode* sp = s.top;
			while (sp->inf != '(')
			{
				vixod[l] = sp->inf;
				vixod[l + 1] = ' ';
				l += 2;
				TNode* t1 = sp;
				sp = sp->a;
				delete t1;
			}
			s.top = sp->a;
			delete sp;
			sp = s.top;
			if (sp)
			{
				while (sp)
				{
					vixod[l] = sp->inf;
					vixod[l + 1] = ' ';
					l += 2;
					TNode* t1 = sp;
					sp = sp->a;
					delete t1;
				}
			}
			s.top = NULL;
		}
	}
	while (s.top)
	{
		vixod[l] = s.top->inf;
		vixod[l + 1] = ' ';
		l += 2;
		TNode* t = s.top;
		s.top = s.top->a;
		delete t;
	}
}

double result(char vixod[], stack2 r, int l, vector<bool> push, int var)
{
	double k = 0, sch = 0;
	double p = 0, count = 0;
	for (int i = 0; i < l; i++)
	{
		k = prior(vixod[i]);
		if (k == 10) continue;
		if (k == -2)
		{
			sch++;
			if (sch > var) r.push(push[count - 1]);
			else r.push(push[count]);
			count++;
			continue;
		}
		if (k > 0 && k < 4)
		{
			Node* spt = r.top;
			if (k == 3)
			{
				p = inverse(spt->inf);
				r.push(p);
				continue;
			}
			else
			{
				if (spt->a->a) p = prior2(spt->a->a->inf, spt->inf, vixod[i]);
				else p = prior2(spt->a->inf, spt->inf, vixod[i]);
				r.del(spt);
				r.push(p);
				continue;
			}
		}
	}
	return r.top->inf;
}


double prior(char ch)
{
	switch (ch)
	{
	case ')': return -1;
	case '(': return 0;
	case '~': return 1;
	case '-': return 1.5;
	case '|': return 2;
	case '&': return 2.5;
	case '!': return 3;
	case ' ': return 10;
	}
	return -2;
}

bool prior2(bool a, bool b, char ch)
{
	switch (ch)
	{
	case '|': return diz(a, b);
	case '&': return kon(a, b);
	case '!': return inverse(a);
	case '~': return equals(a, b);
	case '-': return impl(a, b);
	}
}

bool diz(bool a, bool b)
{
	if (a == true || b == true) return true;
	return false;
}

bool kon(bool a, bool b)
{
	if (a && b) return true;
	return false;
}

bool inverse(bool a)
{
	if (a) return false;
	return true;
}

bool impl(bool a, bool b)
{
	if (a == 1 && b == 0) return false;
	return true;
}

bool equals(bool a, bool b)
{
	if (a == b) return true;
	return false;
}

int TruthTable(char vixod[], stack2 r, int l)
{
	bool univ_var[5] = { 0, 0, 0, 0, 0 };
	int i = -1, var = 0, n = 20, j = 0, var1 = 0, var0 = 0;
	vector<vector<bool>> table;
	vector<bool> push, resultat;
	while (i < n - 1)
	{
		i++;
		if (vixod[i] == 'a') { univ_var[0] = 1; continue; }
		if (vixod[i] == 'b') { univ_var[1] = 1; continue; }
		if (vixod[i] == 'c') { univ_var[2] = 1; continue; }
		if (vixod[i] == 'd') { univ_var[3] = 1; continue; }
		if (vixod[i] == 'e') { univ_var[4] = 1; continue; }
	}
	for (int k = 0; k < 5; k++) {if (univ_var[k]) var++;}
	string vars;
	i = 0;
	univ_var[0];
	univ_var[1];
	univ_var[2];
	univ_var[3];
	univ_var[4];
	if (univ_var[0]) { vars.append("a"); i++; }
 	if (univ_var[1]) { vars.append("b"); i++; }
	if (univ_var[2]) { vars.append("c"); i++; }
	if (univ_var[3]) { vars.append("d"); i++; }
	if (univ_var[4]) { vars.append("e"); i++; }
	for (int i = 0; i < var; i++) push.push_back(0);
	resultat.push_back(result(vixod, r, l, push, var));
	std::copy(push.begin(), push.end(), std::ostream_iterator<int>(std::cout, " ")); cout << resultat[j] << endl; j++;
	table.push_back(push);
	for (int i = 1; i < pow(2, var); i++)
	{
		push = PlusOne(var, push);
		table.push_back(push);
		resultat.push_back(result(vixod, r, l, push, var));
		std::copy(push.begin(), push.end(), std::ostream_iterator<int>(std::cout, " ")); cout << resultat[j] << endl; j++;
	}
	var1 = sdnf(table, resultat, vars, var);
	var0 = sknf(table, resultat, vars, var);
	NumericForms(resultat, var1, var0);
	IndexForm(resultat);
	return var;
}

vector<bool> PlusOne(int var, vector<bool> push)
{
	if (!push[var - 1]) {
		push[var - 1] = 1; return push;
	}
	if (push[var - 1])
	{
		if (!push[var - 2]) {
			push[var - 2] = 1;
			push[var - 1] = 0;
			return push;
		}
		if (push[var - 2])
		{
			if (!push[var - 3])
			{
				push[var - 3] = 1;
				push[var - 2] = 0;
				push[var - 1] = 0;
				return push;
			}
			if (push[var - 3])
			{
				if (!push[var - 4])
				{
					push[var - 4] = 1;
					push[var - 3] = 0;
					push[var - 2] = 0;
					push[var - 1] = 0;
					return push;
				}
			}
		}
	}
}

void NumericForms(vector<bool> resultat, int var1, int var0)
{
	vector<int> kon, diz;
	for (int i = 0; i < resultat.size(); i++)
	{
		if (resultat[i]) diz.push_back(i);
		else kon.push_back(i);
	}
	cout << '(';
	for (int i = 0; i < kon.size(); i++)
	{
		cout << kon[i];
		if (i != var0 - 1) cout << ',';
	}
	cout << ")&" << endl;
	cout << '(';
	for (int i = 0; i < diz.size(); i++)
	{
		cout << diz[i];
		if (i != var1 - 1) cout << ',';
	}
	cout << ")|" << endl;
}

void IndexForm(vector<bool> resultat)
{
	int des = 0;
	for (int i = resultat.size() - 1, k = 0; i > 0; i--, k++)
	{
		if (resultat[i]) des += pow(2, k);
	}
	cout << des << " - ";
	for (int i = 0; i < resultat.size(); i++)
	{
		cout << resultat[i];
	}
	cout << endl;
}