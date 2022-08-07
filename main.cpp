#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <queue>

#include "search.h"

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream input("input.txt");
    char opt = '\0';
    bool has_solution;
    int n;

    input >> n;

    Puzzle::n = n;
    Puzzle::size = 2 * n + 1;

    Puzzle root;
    root.fill(input);

    list<Puzzle *> path;

    while (opt != '0')
    {
        cout << "Opcoes: " << endl
             << "1 - Backtracking"
             << "\t4 - Greed" << endl
             << "2 - BFS"
             << "\t\t\t5 - A*" << endl
             << "3 - DFS"
             << "\t\t\t6 - IDA*" << endl
             << "--" << endl
             << "0 - Sair" << endl;

        // cin >> opt;
        opt = '6';

        depth = cost = node_count = nonleaf_count = 0;
        has_solution = false;

        switch (opt)
        {
        case '1':
            has_solution = backtracking(root.makeChildCopy(), &path);
            break;
        case '2':
            has_solution = bfs(&root, &path);
            break;
        case '3':
            has_solution = dfs(&root, &path, 6);
            break;
        case '4':
            has_solution = greed(&root, &path);
            break;
        case '5':
            has_solution = aStar(&root, &path);
            break;
        case '6':
            has_solution = idaStar(root.makeChildCopy(), &path);
            break;
        case '0':
            cout << "Encerrando" << endl;
            continue;
        default:
            cout << "Opcao invalida" << endl;
            continue;
        }

        opt = '0';

        if (has_solution)
            showPath(&path);
        else
            cout << "Sem solucao" << endl;

        cout << "Profundidade: " << depth << endl
             << "Nos visitados: " << node_count << endl
             << "Ramificacao: " << ((node_count - 1) / (float)nonleaf_count) << endl;

        freeList(&path);
    }

    return 0;
}