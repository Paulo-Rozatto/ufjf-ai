#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <queue>

#include "algorithms.h"

using namespace std;

struct CmpPuzzles
{
    bool operator()(const Puzzle *p1, const Puzzle *p2) const
    {
        return p1->getWhiteLeft() > p2->getWhiteLeft();
    }
};

bool greed(Puzzle *p, priority_queue<Puzzle *, vector<Puzzle *>, CmpPuzzles> *minheap)
{
    Puzzle *child;
    bool found = false;

    if (p->heuristic() == 0)
    {
        p->show(cout);
        return true;
    }

    child = new Puzzle(p->getN());
    child->copy(p);
    for (int i = 0; i < p->getSize(); i++)
    {

        if (child->move(i))
        {
            // if (!exists(child, opened))
            // {
            minheap->push(child);
            // opened->push_back(child);
            child = new Puzzle(p->getN());
            // }
            child->copy(p);
        }
    }
    delete child;

    while (minheap->size() > 0)
    {
        child = minheap->top();
        minheap->pop();
        if (!found && greed(child, minheap))
        {
            found = true;
            break;
        }
        delete child;
    }

    return found;
}

int main(int argc, char const *argv[])
{
    ifstream input("input.txt");
    int n;

    input >> n;

    Puzzle p(n);
    list<Puzzle *> parents, solutions;
    list<int> moves;
    priority_queue<Puzzle *, vector<Puzzle *>, CmpPuzzles> minheap;

    p.fill(input);
    cout << "Start: ";
    p.show(cout);

    // cout << "Backtracking: ";
    // cout << backtracking(&p, &parents, &solutions, &moves) << endl;
    // p.show(cout);
    // showSolution(cout, &solutions, &moves);

    // cout << "BFS: " << bfs(&p);

    // cout << "DFS:" << dfs(&p, 4) << endl;

    cout << "Greed: " << greed(&p, &minheap) << endl;

    return 0;
}