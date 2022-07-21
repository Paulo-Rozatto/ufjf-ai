#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>

#define blue 'b'  // azul
#define white 'w' // branco

class Puzzle
{
private:
    static int id_count;

    int id;
    int n;     // quantidade de blocos de cada cor
    int size;  // tamanho total da regua (2 * n + 1)
    char *puz; // puzzle

public:
    Puzzle(int n);
    ~Puzzle();
    bool move(int idx);
    void fill(std::istream &in);
    bool checkWin();
    void show();
    int getSize();
    int getN() { return this->n; }
    void copy(Puzzle *p);
    bool equals(Puzzle *p);

protected:
    int space_idx;
    char *getPuz();
};

#endif