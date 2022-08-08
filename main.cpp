#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <chrono>
#include <time.h>

#include "search.h"

using namespace std;

int main(int argc, char const *argv[])
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
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

        cin >> opt;
        // opt = '6';

        depth = cost = node_count = nonleaf_count = 0;
        has_solution = false;

        switch (opt)
        {
        case '1':
            start = std::chrono::system_clock::now();
            has_solution = backtracking(root.makeChildCopy(), &path);
            end = std::chrono::system_clock::now();
            break;
        case '2':
            start = std::chrono::system_clock::now();
            has_solution = bfs(&root, &path);
            end = std::chrono::system_clock::now();
            break;
        case '3':
            int max_depth;
            cout << "Profundidade maxima: ";
            cin >> max_depth;
            start = std::chrono::system_clock::now();
            has_solution = dfs(&root, &path, max_depth);
            end = std::chrono::system_clock::now();
            break;
        case '4':
            start = std::chrono::system_clock::now();
            has_solution = greed(&root, &path);
            end = std::chrono::system_clock::now();
            break;
        case '5':
            start = std::chrono::system_clock::now();
            has_solution = aStar(&root, &path);
            end = std::chrono::system_clock::now();
            break;
        case '6':
            start = std::chrono::system_clock::now();
            has_solution = idaStar(root.makeChildCopy(), &path);
            end = std::chrono::system_clock::now();
            break;
        case '0':
            cout << "Encerrando" << endl;
            continue;
        default:
            cout << "Opcao invalida" << endl;
            continue;
        }

        // opt = '0';

        if (has_solution)
            showPath(&path);
        else
            cout << "Sem solucao" << endl;

        elapsed_seconds = end - start;

        cout << "Custo: " << path.back()->cost << endl
             << "Profundidade: " << depth << endl
             << "Nos visitados: " << node_count << endl
             << "Ramificacao: " << ((node_count - 1) / (float)nonleaf_count) << endl
             << "Tempo: " << elapsed_seconds.count() << "s" << endl;

        freeList(&path);
    }

    return 0;
}