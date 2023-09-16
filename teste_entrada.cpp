#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <sstream>

using namespace std;
vector<double> z_to_c(string exp);
vector<string> tokenize(string str, char delim);
double str_to_double(string str);
double power(double val, int n);

int main(){
	cout << "Test 1: \n";
	vector<double> t = z_to_c("x1 + 2.23 x2 + 3* x3 +1x2 + 4x6");	
	double compare[6] = {0, 3.23, 3, 0, 0, 4};
	bool pass = true;
	for(int i=0; i<t.size(); ++i){
		if(compare[i] != t[i]) pass = false;
	}
	cout << (pass ? "FUNCIONOU" : "NAO FUNCIONOU") << "\n";
	cout << "\n";
	return 0;
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
