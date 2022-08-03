#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <queue>

#include "puzzle.h"

using namespace std;

// Globai de estatistica
int depth, cost, node_count, branch_count;

bool exists(Puzzle *p, list<Puzzle *> *s)
{
    for (std::list<Puzzle *>::iterator it = s->begin(); it != s->end(); ++it)
    {
        if ((*it)->equals(p))
            return true;
    }

    return false;
}

void showPath(list<Puzzle *> *path)
{
    for (std::list<Puzzle *>::iterator it = path->begin(); it != path->end(); ++it)
        (*it)->show(cout);
}

bool backtracking(Puzzle *parent, list<Puzzle *> *path)
{
    node_count += 1;

    path->push_back(parent);

    if (parent->checkWin())
    {
        cout << "ei" << endl;
        return true;
    }

    int start, end;
    bool revert_depth = true;

    start = parent->space_idx - Puzzle::n;
    end = parent->space_idx + Puzzle::n;

    if (start < 0)
        start = 0;
    if (end >= Puzzle::size)
        end = Puzzle::size;

    Puzzle *child = parent->makeCopy();

    // Assume que algum filho sera visitado
    depth += 1;

    for (int i = start; i < end; i++)
    {
        if (i != parent->space_idx)
        {
            child->move(i);

            if (!exists(child, path))
            {
                revert_depth = false;
                if (backtracking(child, path))
                    return true;
            }

            child->move(parent->space_idx); // volta estado se falhar
        }
    }

    if (revert_depth)
        depth -= 1;
    path->pop_back();
    delete child;

    return false;
}

int main(int argc, char const *argv[])
{
    ifstream input("input.txt");
    int n;
    char opt = '\0';

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
             << "0 - Sair" << endl;

        cin >> opt;

        depth = cost = node_count = branch_count = 0;

        switch (opt)
        {
        case '1':
            if (backtracking(&root, &path))
            {
                showPath(&path);
                cout << "depth: " << depth << endl
                     << "visited: " << node_count << endl;
            }
            else
                cout << "Sem solucao" << endl;
            break;

        case '0':
            cout << "Encerrando" << endl;
            break;
        default:
            cout << "Opcao invalida";
            break;
        }
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