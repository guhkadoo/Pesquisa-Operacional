#include "sei_la.hpp"

vector<string> vetorDeStrings;
int highlight = 0;

void menu(vector<string> menuOptions, string title, int numFunctions, ...) {
    int height, width;
    getmaxyx(stdscr, height, width);
    int choice;

    // Crie um vetor de ponteiros para função
    vector<FunctionPtr> functions;
    va_list args;
    va_start(args, numFunctions);
    for (int i = 0; i < numFunctions; i++) {
        FunctionPtr func = va_arg(args, FunctionPtr);
        functions.push_back(func);
    }
    va_end(args);

    while (1) {
        clear();
        mvprintw(1, (width - title.size()) / 2, title.c_str());

        // Imprime o menu
        for (int i = 0; i < menuOptions.size(); i++) {
            if (i == highlight)
                attron(A_REVERSE); // Destaca a opção selecionada
            mvprintw(height / 2 + i, (width - menuOptions[i].length()) / 2, menuOptions[i].c_str());
            attroff(A_REVERSE);
        }

        // Lê a entrada do usuário
        choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = menuOptions.size() - 1;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == menuOptions.size())
                    highlight = 0;
                break;
            case 10: // Enter
                if (highlight == menuOptions.size() - 1)
                    goto end;
                for (int i = 0; i < menuOptions.size() - 1; i++) {
                    if (highlight == i) {
                        // Chama a função correspondente
                        functions[i](highlight);
                    }
                }
                break;
        }
    }
end:
    highlight = 0;
    endwin();
}

void delete_line(WINDOW *win, int line) {
    wmove(win, line, 0);
    wclrtoeol(win);
    refresh();
}

void print_vector(vector<double> v, const char *n) {
    int width, height;
    getmaxyx(stdscr, height, width);
    clear();
    mvprintw(height/2 - 1, width/2 + 2, n);
    int tam = v.size();
    for(int i=0; i<tam; ++i){
        if(!i){
            move(height/2 + i, width/2 - 5); addch(ACS_ULCORNER); mvprintw(height/2 +i, width/2, "%.2lf", v[i]); move(height/2 + i, width/2 + 10); addch(ACS_URCORNER);
        }
        else if(i != tam-1){
            move(height/2 + i, width/2 - 5); addch(ACS_VLINE); mvprintw(height/2 +i, width/2, "%.2lf", v[i]); move(height/2 + i, width/2 + 10); addch(ACS_VLINE);
        }
        else{
            move(height/2 + i, width/2 - 5); addch(ACS_LLCORNER); mvprintw(height/2 +i, width/2, "%.2lf", v[i]); move(height/2 + i, width/2 + 10); addch(ACS_LRCORNER); 
        }
	   }
    getch();
    delete_line(stdscr, height/2);    
}
