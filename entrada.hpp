#ifndef ENTRADA
#define ENTRADA

#include <cstring>
//#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
vector<double> z_to_c(string exp);
vector<string> tokenize(string str, char delim);
double str_to_double(string str);
double power(double val, int n);
pair<vector<vector<double>>, vector<double>> matriz_a_b(vector<string> exps, int n);


#endif
