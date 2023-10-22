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

    //print antes das va
    for(auto i: padrao){
        for(auto j: i){
            cout << j << " ";
        }
        cout << "\n";
    }
    //adicionar variaveis artificiais
    vector<pair<int, int>> va;
    int nn_variaveis = n_variaveis;
    int linha = 0, max_linhas = 0;
    for(auto exps: padrao) max_linhas++;

    int tam_atual = padrao[0].size();
    //cout << "tam atual: " <<  tam_atual << "\n";
    for(auto &exps: padrao){
        bool add_va = true;
        for(int i=0; i<tam_atual; ++i){
            if(exps[i] == 1){
                bool todos_sao_zero = true;
                for(int j=0; j<max_linhas; ++j){
                    if(j != linha){
                        if(padrao[j][i] != 0){
                            todos_sao_zero = false;
                        }
                    }
                }
                if(todos_sao_zero){
                    add_va = false;
                }
            }
            if(add_va == false) break;
        }

        for(int i=0; i< nn_variaveis-n_variaveis; ++i){
            exps.push_back(0);
        }
        cout << "linha : " << linha << " add_va : " << add_va << "\n";
        if(add_va){
            cout << "add_va na: " << linha << "\n";
            exps.push_back(1);
            va.push_back({linha, nn_variaveis});
            nn_variaveis++;
        }
        linha++;
    }

    add = nn_variaveis-n_variaveis;
    cout << "add : " << add << "\n";
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
    for(auto it: va){
        cout << "va: " << it.first << " " << it.second << "\n";
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