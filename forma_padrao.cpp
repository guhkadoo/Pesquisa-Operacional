#include "forma_padrao.hpp"

extern vector<int> eq_igual;

vector<vector<double>> forma_padrao(pair<vector<vector<double>>, vector<double>> &m, int n){
    vector<vector<double>> padrao(m.second.size());
    cout << " FORMA PADRAO\n";
    int aux = 0;
    int n_variaveis = n;
    for(auto exps: m.first){

        for(auto value: exps){
            padrao[aux].push_back(value);
        }
        for(int i=0; i< n_variaveis-n; ++i){
            padrao[aux].push_back(0);
        }
        if(!is_exp_igual(aux)){
            padrao[aux].push_back(1);
            n_variaveis++;
        }

        aux++;
    } 

    int add = n_variaveis-n-1;
    for(auto &exps: padrao){
        for(int i=0; i<add; ++i){
            exps.push_back(0);
        }
        add--;
    }

    //inverter se b = 0
    aux = 0;
    for(auto &it: m.second){
        if(it < 0){
            it *= -1;
            for(auto &value: padrao[aux]){
                value *= -1;
            }
        }
        aux++;
    }

    //adicionar variaveis artificiais
    vector<int> va;
    int nn_variaveis = n_variaveis;
    for(auto &exps: padrao){
        for(int i=0; i< nn_variaveis-n_variaveis; ++i){
            exps.push_back(0);
        }
        if(!is_exp_igual(aux)){
            exps.push_back(1);
            nn_variaveis++;
        }
    }

    add = nn_variaveis-n_variaveis-1;
    for(auto &exps: padrao){
        for(int i=0; i<add; ++i){
            exps.push_back(0);
        }
        add--;
    }
    // printar teste
    for(auto i: padrao){
        for(auto j: i){
            cout << j << " ";
        }
        cout << "\n";
    }

    cout << "b:\n";
    for(auto it: m.second){
        cout << it << " ";
    }
    cout << "\n";
    return m.first;
}

bool is_exp_igual(int n){
    int l=0, r = eq_igual.size();

    while(l <= r){
        int m = (r+l)/2;
        cout << "BS: " << eq_igual[m] << "\n";
        if(eq_igual[m] == n){
            return true;
        }
        if(eq_igual[m] < n){
            l = m+1;
        }else{
            r = m-1;
        }
    }
    return false;
}