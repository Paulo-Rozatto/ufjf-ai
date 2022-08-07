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
             << "1 - Backtracking" << endl
             << "2 - BFS" << endl
             << "3 - DFS" << endl
             << "0 - Sair" << endl;

        cin >> opt;
        // opt = '3';

        depth = cost = node_count = nonleaf_count = 0;
        has_solution = false;

        switch (opt)
        {
        case '1':
            has_solution = backtracking(&root, &path);
            break;
        case '2':
            has_solution = bfs(&root, &path);
            break;
        case '3':
            has_solution = dfs(&root, &path, 30000);
            break;
        case '0':
            cout << "Encerrando" << endl;
            break;
        default:
            cout << "Opcao invalida" << endl;
            continue;
        }

        // opt = '0';

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

// int main(int argc, char const *argv[])
// {
//     ifstream input("input.txt");
//     int n;

//     input >> n;

//     Puzzle p(n);
//     list<Puzzle *> parents, solutions;
//     list<int> moves;
//     priority_queue<Puzzle *, vector<Puzzle *>, CmpPuzzles> minheap;
//     priority_queue<Puzzle *, vector<Puzzle *>, CmpObjective> minheap2;

//     p.fill(input);
//     cout << "Start: ";
//     p.show(cout);

//     // cout << "Backtracking: ";
//     // cout << backtracking(&p, &parents, &solutions, &moves) << endl;
//     // p.show(cout);
//     // showSolution(cout, &solutions, &moves);

//     // cout << "BFS: " << bfs(&p);

//     // cout << "DFS:" << dfs(&p, 4) << endl;

//     // cout << "Greed: " << greed(&p, &minheap) << endl;

//     cout << "A*: " << astar(&p, &minheap2) << endl;

//     // cout << "IDA*: " << backtracking(&p, &parents, &solutions, &moves) << endl;
//     return 0;
// }