#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>

using namespace std;

#define blue 'b'  // azul
#define white 'w' // branco

class Puzzle
{
private:
    int n;     // quantidade de blocos de cada cor
    int size;  // tamanho total da regua (2 * n + 1)
    char *puz; // puzzle
public:
    Puzzle(int n);
    ~Puzzle();
    bool checkWin();
    void fill(istream& in);
    void show();
};

#endif