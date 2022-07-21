#include <iostream>
#include <fstream>
#include <list>

#include "puzzle.h"

using namespace std;

void showSolution(ostream& out, list<Puzzle *> *solution_states, list<int> *solution_moves)
{
    std::list<Puzzle *>::iterator it = solution_states->begin();
    std::list<int>::iterator it2 = solution_moves->begin();

    for (it; it != solution_states->end(); ++it)
    {
        out << "Move: " << *it2 << endl;
        (*it)->show(out);
        it2++;
    }
}

bool exists(Puzzle *p, list<Puzzle *> *s)
{
    for (std::list<Puzzle *>::iterator it = s->begin(); it != s->end(); ++it)
    {
        if ((*it)->equals(p))
            return true;
    }

    return false;
}

bool backtracking(Puzzle *p, list<Puzzle *> *parents, list<Puzzle *> *solution_states, list<int> *solution_moves)
{
    Puzzle *child;
    bool flag = false;
    parents->push_back(p);

    if (p->checkWin())
        return true;

    child = new Puzzle(p->getN());

    for (int i = 0; i < p->getSize(); i++)
    {
        child->copy(p);

        if (child->move(i))
        {
            if (exists(child, parents))
                continue;
            if (backtracking(child, parents, solution_states, solution_moves))
            {
                solution_states->push_front(child);
                solution_moves->push_front(i);
                return true;
            }
        }
    }
    delete child;
    parents->pop_back();

    return false;
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

    cout << "Backtracking: ";
    cout << backtracking(&p, &parents, &solutions, &moves) << endl;
    p.show(cout);

    showSolution(cout, &solutions, &moves);

    return 0;
}