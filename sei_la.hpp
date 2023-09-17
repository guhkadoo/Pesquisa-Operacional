#ifndef __SEI_LA_H__
#define __SEI_LA_H__

#include <cstring>
#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using FunctionPtr = void (*)(int);

extern vector<string> vetorDeStrings;
extern int highlight;

void menu(vector<string> menuOptions, string title, int numFunctions, ...);
void delete_line(WINDOW *win, int line);
void print_vector(vector<double> v, const char *n);
void print_matrix(vector<vector<double>> M, const char *n);


#endif //__SEI_LA_H__
