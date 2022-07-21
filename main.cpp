#include <iostream>
#include <fstream>
#include <list>

#include "algorithms.h"

using namespace std;

void freeList(list<Puzzle *> *l) {
    for (std::list<Puzzle *>::iterator it = l->begin(); it != l->end(); ++it)
        delete (*it);
}

bool bfs(Puzzle *start)
{
    list<Puzzle *> queue, closeds;
    Puzzle *p, *child;
    bool win = false;

    queue.push_back(start);
    int cont = 0;

    while (queue.size() > 0)
    {
        cont++;
        p = queue.front();
        queue.pop_front();

        if (p->checkWin())
        {
            cout << "Solution: ";
            p->show(cout);
            win = true;
            break;
        }

        for (int i = 0; i < p->getSize(); i++)
        {
            child = new Puzzle(p->getN());
            child->copy(p);

            if (child->move(i))
            {
                if (exists(child, &closeds))
                {
                    delete child;
                    continue;
                }
                queue.push_back(child);
            }
            else
                delete child;
        }

        closeds.push_back(p);
    }

    freeList(&queue);
    // closeds.pop_front(); // primeiro elemento tem referencia na main
    // freeList(&closeds);

    return win;
}

int main(int argc, char const *argv[])
{
    ifstream input("input.txt");
    int n;

    input >> n;

    Puzzle p(n);
    list<Puzzle *> parents, solutions;
    list<int> moves;

    p.fill(input);
    cout << "Start: ";
    p.show(cout);

    // cout << "Backtracking: ";
    // cout << backtracking(&p, &parents, &solutions, &moves) << endl;
    // p.show(cout);
    // showSolution(cout, &solutions, &moves);

    cout << "BFS: " << bfs(&p);

    return 0;
}