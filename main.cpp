#include <iostream>

#include "puzzle.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Puzzle p(2);
    p.fill(cin);


    cout << "State: " << endl;
    p.show();
    cout << (p.checkWin() ? "win": "not win") << endl;
    return 0;
}