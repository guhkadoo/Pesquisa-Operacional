#include "entrada.hpp"

pair<vector<vector<double>>, vector<double>> matriz_a_b(vector<string> exps, int n){
	// n: quantas variaveis tem o problema
	vector<vector<double>> A(exps.size());
	vector<double> b;
	int i = 0;

	for(auto it: exps){
		vector<string> exp = tokenize(it, '=');
		char comp = exp[0][exp[0].length()-1];
		exp[0][exp[0].length()-1] = ' ';
		cout << comp << "\n";
		if(comp == '<'){
			int cnt = 0;
			string copy_numbers = "";
			for(int j=0; j<exp[1].length(); ++j){
				if(exp[1][j] >= '0' && exp[1][j] <= '9'){
					copy_numbers.push_back(exp[1][j]);
				}
			}
			b.push_back(str_to_double(copy_numbers));
			vector<double> aux = z_to_c(exp[0]);
			for(auto num: aux){
				A[i].push_back(num);
				cnt++;
			}
			if(cnt < n){
				for(; cnt<n; ++cnt){
					A[i].push_back(0);
				}
			}
		}else{
			int cnt = 0;
			string copy_numbers = "";
			for(int j=0; j<exp[1].length(); ++j){
				if(exp[1][j] >= '0' && exp[1][j] <= '9'){
					copy_numbers.push_back(exp[1][j]);
				}
			}
			b.push_back(-1 * str_to_double(copy_numbers));
			vector<double> aux = z_to_c(exp[0]);
			for(auto num: aux){
				A[i].push_back(-num);
				cnt++;
			}
			if(cnt < n){
				for(; cnt<n; ++cnt){
					A[i].push_back(0);
				}
			}
		}
		++i;
	}
	return {A, b};
}

vector<double> z_to_c(string exp){
	//adicionar 0 antes dos a*xi -> 0a*xi
	string new_exp = "0";
	for(int i=0; i<exp.length(); ++i){
		if(exp[i] == ' '){
			continue;
		}
		else if(exp[i] == '+'){
			new_exp.push_back('+');
			new_exp.push_back('0');
		}else{
			new_exp.push_back(exp[i]);
		}
	}
	vector<string> tokens = tokenize(new_exp, '+');
	map<int, double> mapa;
	for(auto it: tokens){
		vector<string> values = tokenize(it, 'x');
		//values[0] = a, values[1] = i
		vector<string> first = tokenize(values[0], '*');
		mapa[(int)str_to_double(values[1])] += str_to_double(first[0]);
	}

	int _max = 0;
	for(auto it: mapa){
		if(it.first > _max) _max = it.first;
	}

	vector<double> ans(_max, 0);
	for(int i=1; i<=_max; ++i){
		ans[i-1] = mapa[i]; 
	}
	return ans;
}

double str_to_double(string str){
	vector<string> parts = tokenize(str, '.');
	double ans = 0;
	bool decimal = false;
	for(auto it: parts){
		if(!decimal){
			for(int i=0; i<it.length(); ++i){
				ans = 10 * ans + (it[i] - '0');
			}
		}else{
			double qnt = 0, tmp = 0;
			for(int i=0; i<it.length(); ++i){
				tmp = 10 * tmp + (it[i] - '0');
				qnt++;
			}
			ans += (tmp/power(10, qnt));
		}
		decimal = true;
	}
	return ans;
}

double power(double val, int n){
	//deixar em O(logn)
	double ans = 1;
	for(int i=0; i<n; ++i){
		ans *= val;
	}
	return ans;
}

vector<string> tokenize(string str, char delim){
	vector<string> tokens;
	string tmp = "";
	for(int i=0; i<str.length(); ++i){
		if(str[i] == delim){
			tokens.push_back(tmp);
			tmp = "";
		}else{
			tmp += str[i];
		}
	}
	tokens.push_back(tmp);
	return tokens;
}
