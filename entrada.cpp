#include "entrada.hpp"

vector<int> eq_igual; 
string __formato_certo(string exp){
	string tmp;
	bool flag = false;
	for(int i=0; i<exp.length(); i++){
		if(exp[i] == '-' && flag == false){
			tmp.push_back('+');
			tmp.push_back('(');
			tmp.push_back('-');
			flag = true;
		}else if(exp[i] == '-' && flag == true){
			tmp.push_back(')');
			tmp.push_back('+');
			tmp.push_back('(');
			tmp.push_back('-');
			flag = true;
		}else if(exp[i] == '+' && flag == true){
			tmp.push_back(')');
			tmp.push_back('+');
			flag = false;
		}else{
			tmp.push_back(exp[i]);
		}
	}
	cout << tmp << '\n';
	return tmp;
}
pair<vector<vector<double>>, vector<double>> matriz_a_b(vector<string> exps, int n)
{
	// n: quantas variaveis tem o problema
	vector<vector<double>> A(exps.size());
	vector<double> b;
	int i = 0;

	for (auto it : exps)
	{
		vector<string> exp = tokenize(it, '=');
		char comp = exp[0][exp[0].length() - 1];
		exp[0][exp[0].length() - 1] = ' ';
		int cnt = 0;
		string copy_numbers = "";
		for (int j = 0; j < exp[1].length(); ++j)
		{
			if ((exp[1][j] >= '0' && exp[1][j] <= '9') || (exp[1][j] == '.') || (exp[1][j] == '-'))
			{
				copy_numbers.push_back(exp[1][j]);
			}
		}

		int mult;
		if(comp == '<'){
			b.push_back(str_to_double(copy_numbers));
			mult = 1;
		}else if(comp == '>'){
			//cout << "BBBBBBBBBBBBB: " << str_to_double(copy_numbers) << " : " << copy_numbers << "\n";
			b.push_back(-1 * str_to_double(copy_numbers));
			mult = -1;
		}else{
			b.push_back(str_to_double(copy_numbers));
			eq_igual.push_back(i);
			mult = 1;
		}
		//comp == '<' ? b.push_back(str_to_double(copy_numbers)) : b.push_back(-1 * str_to_double(copy_numbers));
		vector<double> aux = z_to_c(exp[0]);
		for (auto num : aux)
		{
			A[i].push_back(num * mult);
			cnt++;
		}
		if (cnt < n)
		{
			for (; cnt < n; ++cnt)
			{
				A[i].push_back(0);
			}
		}
		++i;
	}

	return {A, b};
}

vector<double> z_to_c(string exp)
{
	// adicionar 0 antes dos a*xi -> 0a*xi
	string new_exp = "0";

	bool primeiro_negativo = (exp[0] == '-');
	if(primeiro_negativo) exp[0] = ' ';

	exp = __formato_certo(exp);

	for (int i = 0; i < exp.length(); ++i)
	{
		if (exp[i] == ' ' || exp[i] == ')')
		{
			continue;
		}
		else if (exp[i] == '+')
		{
			new_exp.push_back('+');
			new_exp.push_back('0');
		}
		else if (exp[i] == '(' && exp[i + 1] == '-')
		{
			new_exp.pop_back();
			if (exp[i + 2] == 'x')
				new_exp += "-01";
			else
				new_exp += "-0";
			i++;
		}
		else
		{
			new_exp.push_back(exp[i]);
		}
	}
	vector<string> tokens = tokenize(new_exp, '+');
	map<int, double> mapa;
	for (auto it : tokens)
	{
		if(it == "") continue;
		vector<string> values = tokenize(it, 'x');
		// values[0] = a, values[1] = i
		vector<string> first = tokenize(values[0], '*');
		if (first[0].length() == 1 && first[0][0] == '0')
			first[0] += "1";
		mapa[(int)str_to_double(values[1])] += str_to_double(first[0]);
	}

	int _max = 0;
	for (auto it : mapa)
	{
		if (it.first > _max)
			_max = it.first;
	}

	vector<double> ans(_max, 0);
	for (int i = 1; i <= _max; ++i)
	{
		ans[i - 1] = mapa[i];
	}
	if(primeiro_negativo) ans[0] *= -1;
	return ans;
}

double str_to_double(string str)
{
	vector<string> parts = tokenize(str, '.');
	double ans = 0;
	bool decimal = false;
	bool negative;
	int cont;
	for (auto it : parts)
	{
		if (!decimal)
		{
			it[0] == '-' ? cont = 1 : cont = 0;
			cont == 1 ? negative = true : negative = false;
			for (cont; cont < it.length(); ++cont)
			{
				ans = 10 * ans + (it[cont] - '0');
			}
		}
		else
		{
			double qnt = 0, tmp = 0;
			for (int i = 0; i < it.length(); ++i)
			{
				tmp = 10 * tmp + (it[i] - '0');
				qnt++;
			}
			ans += (tmp / power(10, qnt));
		}
		decimal = true;
	}
	if (negative)
	{
		return -ans;
	}
	return ans;
}

double power(double val, int n)
{
	// deixar em O(logn)
	double ans = 1;
	for (int i = 0; i < n; ++i)
	{
		ans *= val;
	}
	return ans;
}

vector<string> tokenize(string str, char delim)
{
	vector<string> tokens;
	string tmp = "";
	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] == delim)
		{
			tokens.push_back(tmp);
			tmp = "";
		}
		else
		{
			tmp += str[i];
		}
	}
	tokens.push_back(tmp);
	return tokens;
}
