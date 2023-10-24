#ifndef FORMA_PADRAO
#define FORMA_PADRAO

#include <cstring>
//#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

vector<vector<double>> forma_padrao(pair<vector<vector<double>>, vector<double>> &m, int n);
vector<vector<double>> add_variavel_artificial(vector<vector<double>> A, set<int> variaveis_livres);
// A = matrix retornada da forma padrao     variaveis_livres = [1, 3, 4] -> 1,3,4 sao variaveis livres
bool is_exp_igual(int n);
extern vector<pair<int, int>> va;

#endif