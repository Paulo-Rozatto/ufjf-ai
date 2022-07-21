#include <iostream>
#include <fstream>

#include "puzzle.h"

using namespace std;

int main(int argc, char const *argv[])
{

    Puzzle p(2);
    ifstream input("input.txt");

    p.fill(input);

    cout << "State: " << endl;
    p.show();
    cout << (p.checkWin() ? "win" : "not win") << endl;
    return 0;
}