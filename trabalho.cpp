#include "entrada.hpp"
#include "sei_la.hpp"
#include "forma_padrao.hpp"
#include "simplex.hpp"

using namespace std; // Adicionando a diretiva
                    
void max_min();
void minimizar_maximizar();

int main() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    curs_set(0); // Esconde o cursor
    keypad(stdscr, true);

    vector<string> menu_principal_options = {"Forma padrao", "Sair"};
    string titulo_menu_principal = "Trabalho de Pesquisa Operacional";
    menu(menu_principal_options, titulo_menu_principal, 1, minimizar_maximizar);
    return 0;
}

void max_min() {
    echo();
    clear();
    int height, width;
    getmaxyx(stdscr, height, width);
    char str[100], input[100];
    int variable_quantity;
    int max=0;
    mvprintw(0, 0, "<ESC> para parar de inserir equacoes");
    mvprintw(2, 0, "Digite a quantidade de variaveis (xn): ");
    mvscanw(2, 40, "%d", &variable_quantity); 
    delete_line(stdscr, 2);
    if(highlight == 0) {
        mvprintw(2, 0, "max ");
        max=1;
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
            delete_line(stdscr, i+1);
        }
        strcpy(input, "");
        i++;
    }
    vector<double> c_vector = z_to_c(str);	
    if(max) {
        for(int i=0; i<c_vector.size(); i++)
            c_vector[i] *= -1;
    }
    pair<vector<vector<double>>, vector<double>> matA_vetb = matriz_a_b(vetorDeStrings, variable_quantity);
    matA_vetb.first = forma_padrao(matA_vetb, variable_quantity);
    print_vector(c_vector, "C");
    print_matrix(matA_vetb.first, "Matriz A");
    print_vector(matA_vetb.second, "b");
    vector<pair<double, double>> solucao = simplex(matA_vetb.first, matA_vetb.second, c_vector, variable_quantity);
    clear();
    if(!solucao.empty()) {
        for(int i=0; i<solucao.size(); i++) {
            mvprintw(i, 0, "[x%lf] %lf", solucao[i].first, solucao[i].second);
        }
    } else {
        mvprintw(0, 0, "SEM SOLUCAO");
    }
    getch();
    vetorDeStrings.clear();
}

void minimizar_maximizar() {
    int height, width;
    getmaxyx(stdscr, height, width);
    clear();
    vector<string> options = {"max", "min", "sair"};
    string title = "";
    menu(options, title, 2, max_min, max_min);
    getch();
}
