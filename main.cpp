#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <queue>

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