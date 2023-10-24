#include "entrada.hpp"
#include "forma_padrao.hpp"
using namespace std;

extern vector<int> eq_igual; // indice de qual expressao do s.a tem igual
int main(){
	cout << "Test 1: \n";
	vector<double> t = z_to_c("-32.35x1 +2.23 x2 - 3* x3 +1x2 - 45.25 x6");	
	double compare[6] = {0, 3.23, 3, 0, 0, 4};
	bool pass = true;
	for(int i=0; i<t.size(); ++i){
		if(compare[i] != t[i]) pass = false;
		cout << t[i] << " \n";
	}
	cout << (pass ? "FUNCIONOU" : "NAO FUNCIONOU") << "\n";
	cout << "\n";

    cout << "Test 2:\n";
    const int n_variaveis = 4;
    vector<string> exps(3);
    exps[0] = "1x1 + 3x2<= 3";
    exps[1] = "-2x1 - 4x3 >= 4";
    exps[2] = "x1 + x2 + x3 + x4 = 2"; // BUG ARRUMAR: Se x1+x2+x3+x4=2 -> se o igual tiver colado ele some com a variavel
    va.clear();
    pair<vector<vector<double>>, vector<double>> test2 = matriz_a_b(exps, n_variaveis);
    for(auto it: test2.first){
        for(auto n: it){
            cout << n << " ";
        }
        cout << "\n";
    }

    for(auto it: test2.second){
        cout << it << "\n";
    }
    cout << "=\n";
    for(auto it: eq_igual){
        cout << it << "\n";
    }

    forma_padrao(test2, n_variaveis);

    cout << "novo teste: \n\n\n";
    va.clear();
    eq_igual.clear();

    vector<string> e(3);
    e[0] = "x1 + 2x2 + 3x3 >= 3";
    e[1] = "3x1 + 2x2 + x3 >= -2.3";
    e[2] = "-2x1 -2x2 - 2x3 <= 1";
    pair<vector<vector<double>>, vector<double>> test3 = matriz_a_b(e, 3);
    test3.first = forma_padrao(test3, 3);
    for(auto it: test3.second){
        cout << "SECOND:       " << it << "\n";
    }
    for(auto V: va){
        cout << "VARIAVLE ARTIFICIAL linha: " << V.first << " coluna: " << V.second << "\n";
    }

    cout << "\n\n\n";
    for(auto i: test3.first){
        for(auto j: i){
            cout << j << " ";
        }
        cout << "\n";
    }
    set<int> va = {};
    test3.first = add_variavel_artificial(test3.first, va);
    for(auto i: test3.first){
        for(auto j: i){
            cout << j << " ";
        }
        cout << "\n";
    }

    //eq_igual.push_back(10);
    //eq_igual.push_back(23);
    //for(int i=0; i<eq_igual.size(); ++i){
    //    cout << "EQ: " << eq_igual[i] << "\n";
    //}
    //cout << (is_exp_igual(12) ? "YES\n" : "NO\n");
	return 0;
}
