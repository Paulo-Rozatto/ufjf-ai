#include <iostream>
#include <fstream>
#include <list>

#include "algorithms.h"

using namespace std;

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