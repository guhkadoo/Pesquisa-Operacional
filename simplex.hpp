#ifndef __SIMPLEX_H__
#define __SIMPLEX_H__

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

using namespace std;
vector<pair<double,double>> simplex(vector<vector<double>> matA, vector<double> b, vector<double> c, int qtd_variaveis);

#endif //__SIMPLEX_H__
