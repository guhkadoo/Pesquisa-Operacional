#include <ncurses.h>
#include <cstring>
#include <string>
#include <vector>

using namespace std; // Adicionando a diretiva
using FunctionPtr = void (*)(int);

vector<string> vetorDeStrings;
int highlight = 0;

void menu(vector<string> menuOptions, string title, int numFunctions, ...);
void max_min();
void forma_padrao();

int main() {
    initscr();
//    noecho();
    cbreak();
    curs_set(0); // Esconde o cursor
    keypad(stdscr, true);

    vector<string> menu_principal_options = {"Forma padrao", "Sair"};
    string titulo_menu_principal = "Trabalho de Pesquisa Operacional";
    menu(menu_principal_options, titulo_menu_principal, 1, forma_padrao);

    return 0;
}

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

void max_min() {
    echo(); int height, width;
    clear();
    getmaxyx(stdscr, height, width);
    char str[100], input[100];
    mvprintw(0, 0, "<ESC> para parar de inserir equacoes");
    if(highlight == 0) {
        mvprintw(2, 0, "max ");
    }
    else {
        mvprintw(2, 0, "min ");
    }
    mvscanw(2, 4, "%99[^\n]", str);
    mvprintw(3, 0, "sabendo que: ");
    int i=3;
    while(1) { 
        echo();
        mvscanw(i, 14, "%99[^\n]", input);
        noecho();
        mvprintw(i+1, 14, "<ESC> ? ");
        vetorDeStrings.push_back(input);
        int ch = getch();
        if(ch == 27) {
            break;
        }
        else {
            wmove(stdscr, i+1, 0);
            wclrtoeol(stdscr);
            refresh();
        }
        strcpy(input, "");
        i++;
    }
    // Apos ler as infos:
    clear();
    vector<vector<int>> matriz_A;
    // Colocar matriz A, vetor C, vetor B, vetor X.
}

void forma_padrao() {
    int height, width;
    getmaxyx(stdscr, height, width);
    clear();
    vector<string> options = {"max", "min", "sair"};
    string title = "";
    menu(options, title, 2, max_min);
    getch();
}
