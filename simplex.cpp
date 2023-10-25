#include "simplex.hpp"
#define M 100000

vector<pair<double,double>> simplex(vector<vector<double>> matA, vector<double> b, vector<double> c, int qtd_variaveis) {
    int numLinhas = matA.size();
    int numCols = matA[0].size();
    for(int i=0; i<numCols-qtd_variaveis-numLinhas; i++) {
        c.push_back(0);
    }
    for(int i=0; i<numLinhas; i++) {
        c.push_back(M);
    }
    vector<double> cr(c.size());

    vector<int> base_c, base;
    vector<pair<double,double>> solucao; // X[0] = 3
    // cria o par(base, base_c) inicial   => (x3, x4, x5), (0, 0, 0).
    for(int i=numLinhas; i>=1; i--) {
        int j=numCols-i;
        base_c.push_back(c[j]);
        base.push_back(j);
    }
    for(int i=0; i<numCols; i++) {
        double prod=0;
        for(int j=0; j<numLinhas; j++) {
            prod += base_c[j] * matA[j][i]; 
        }
        cr[i] = c[i] - prod;
    }

    /* excluir
    for(int i=0; i<numLinhas; i++) {
        for(int j=0; j<numCols; j++)
            cout << matA[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
    for(int i=0; i<base_c.size(); i++) {
        cout << base_c[i] << ' ';
    }
    cout << '\n';
    */
    // acha o menor custo reduzido
    while(1) {
        pair<int, double> menor_cr = {0, cr[0]}; // acha o J 
        for(int i=1; i<numCols; i++) {
            if(cr[i] < menor_cr.second) {
                menor_cr = {i, cr[i]};
            } 
        }
        //cout << "MENOR CUSTO REDUZIDO: " << menor_cr.second << '\n'; //excluir
        if(menor_cr.second >= 0) {
            cout << "SOLUCAO\n";
            for(int i=0; i<qtd_variaveis; i++) {
                int esta_na_base = 0, pos;
                for(int j=0; j<numLinhas; j++) {
                    if(i == base[j]) {
                        esta_na_base = 1;
                        pos = j;
                        break;
                    }
                }
                if(esta_na_base) {
                    //cout << "[X" << base[pos] << "] = " << b[pos] << "\n"; 
                    solucao.push_back(make_pair(i+1, b[pos]));
                }
                else {
                    //cout << "[X" << base[pos] << "] = 0\n";
                    solucao.push_back(make_pair(i+1, 0));
                }
            }
            cout << "\n";
            break;
        }
        pair<int, double> menor_elemento = {-1, -1};
        for(int i=0; i<numLinhas; i++) {
            if(b[i]){
                double elemento = b[i]/matA[i][menor_cr.first];
                if(elemento >= 0) {
                    if(menor_elemento.second == -1 || elemento < menor_elemento.second) menor_elemento = {i, elemento};
                }
            }
        }
        if(menor_elemento.second == -1) {
            printf("Solucao Ilimitada\n");
            return solucao;
        }
        int linha = menor_elemento.first;
        int coluna = menor_cr.first;
        //excluir
        //cout << "MENOR ELEMENTO: " << matA[linha][coluna] << " [i][j] " << linha << ' ' << coluna << '\n';
        base_c[linha] = c[coluna];
        base[linha] = coluna;
        double multiplicador = (1/matA[linha][coluna]);
        //printf("MULTIPLICADOR: %lf\n", multiplicador);
        for(int i=0; i<numCols; i++) 
            matA[linha][i] *= multiplicador;
        b[linha] *= multiplicador;

        for(int i=0; i<numLinhas; i++) {
            if(i != linha) {
                double k = -matA[i][coluna]/matA[linha][coluna];
                for(int j=0; j<numCols; j++) {
                    matA[i][j] = matA[i][j] + matA[linha][j]*k;
                }
                b[i] = b[i] + b[linha]*k;
            }
        }
        for(int i=0; i<numCols; i++) {
            double prod=0;
            for(int j=0; j<numLinhas; j++) {
                prod += base_c[j] * matA[j][i]; 
            }
            cr[i] = c[i] - prod;
        }
        /*
        for(int i=0; i<numLinhas; i++) {
            for(int j=0; j<numCols; j++) {
                cout << matA[i][j] << ' ';
            }
            cout << '\n';
        }
        cout << "B[i]:  ";
        for(int i=0; i<numLinhas; i++) {
            cout << b[i] << ' ';
        }
        cout << "\nbase_c[i]:  ";
        for(int i=0; i<numLinhas; i++) {
            cout << base_c[i] << ' ';
        }
        cout << "\ncr[i]:  ";
        for(int i=0; i<numCols; i++) {
            cout << cr[i] << ' ';
        }
        cout << "\n\n";
        */
    }
        

    return solucao;
}
