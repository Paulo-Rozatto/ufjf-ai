#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <queue>

#include "algorithms.h"

using namespace std;

struct CmpObjective
{
    bool operator()(const Puzzle *p1, const Puzzle *p2) const
    {
        return (p1->getWhiteLeft() + p1->getCost()) > (p2->getWhiteLeft() + p1->getCost());
    }
};

bool greed(Puzzle *p, priority_queue<Puzzle *, vector<Puzzle *>, CmpObjective> *minheap)
{
    Puzzle *top, *child;
    bool found = false;

    minheap->push(new Puzzle(p->getN()));
    minheap->top()->copy(p);

    while (minheap->size() > 0)
    {
        top = minheap->top();
        minheap->pop();

        if (top->heuristic() == 0)
        {
            found = true;
            top->show(cout);
            break;
        }

        child = new Puzzle(p->getN(), p->getCost() + 1);
        child->copy(top);

        for (int i = 0; i < top->getSize(); i++)
        {
            if (child->move(i))
            {
                minheap->push(child);
                child = new Puzzle(p->getN(), p->getCost() + 1);
                child->copy(top);
            }
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

    // cout << "Greed: " << greed(&p, &minheap) << endl;

    cout << "A*: " << greed(&p, &minheap) << endl;

    return 0;
}