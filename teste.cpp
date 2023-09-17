#include "entrada.hpp"
using namespace std;

int main(){
	cout << "Test 1: \n";
	vector<double> t = z_to_c("x1 + 2.23 x2 + 3* x3 +1x2 + 4x6");	
	double compare[6] = {0, 3.23, 3, 0, 0, 4};
	bool pass = true;
	for(int i=0; i<t.size(); ++i){
		if(compare[i] != t[i]) pass = false;
		cout << t[i] << " \n";
	}
	cout << (pass ? "FUNCIONOU" : "NAO FUNCIONOU") << "\n";
	cout << "\n";

    cout << "Test 2:\n";
    vector<string> exps(2);
    exps[0] = "1x1 + 3x2 <= 3";
    exps[1] = "2x1 + 4x3 >= 4";
    pair<vector<vector<double>>, vector<double>> test2 = matriz_a_b(exps, 3);
    for(auto it: test2.first){
        for(auto n: it){
            cout << n << " ";
        }
        cout << "\n";
    }

    for(auto it: test2.second){
        cout << it << "\n";
    }
	return 0;
}