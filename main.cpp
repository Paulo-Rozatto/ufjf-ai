#include <iostream>
#include <fstream>
#include <list>

#include "puzzle.h"

using namespace std;

bool exists(Puzzle *p, list<Puzzle *> *s)
{
    for (std::list<Puzzle *>::iterator it = s->begin(); it != s->end(); ++it)
    {
        if ((*(it))->equals(p))
            return true;
    }

    return false;
}

bool backtracking(Puzzle *p, list<Puzzle *> *s)
{
    Puzzle *child;
    bool flag = false;
    s->push_back(p);

    if (p->checkWin())
        return true;

    child = new Puzzle(p->getN());

    for (int i = 0; i < p->getSize(); i++)
    {
        child->copy(p);

        if (child->move(i))
        {
            if (exists(child, s))
                continue;
            if (backtracking(child, s))
                return true;
        }
    }
    delete child;

    return false;
}

int main(int argc, char const *argv[])
{
    ifstream input("input.txt");
    int n;

    input >> n;

    Puzzle p(n);
    list<Puzzle *> path;

    p.fill(input);
    cout << "Start: ";
    p.show();

    cout << "Backtracking: ";
    cout << backtracking(&p, &path) << endl;
    p.show();

    cout << (p.checkWin() ? "win" : "not win") << endl;
    return 0;
}