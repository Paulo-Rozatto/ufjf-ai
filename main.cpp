#include <iostream>
#include <fstream>

#include "puzzle.h"

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream input("input.txt");
    int n;

    input >> n;

    Puzzle p(n);

    p.fill(input);
    p.show();
    p.move(0);

    cout << "State: " << endl;
    p.show();
    cout << (p.checkWin() ? "win" : "not win") << endl;
    return 0;
}