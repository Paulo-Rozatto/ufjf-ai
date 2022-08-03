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
    int n;         // quantidade de blocos de cada cor
    int size;      // tamanho total da regua (2 * n + 1)
    char *puz;     // puzzle
    int whiteLeft; // numero de brancas que ainda estao a direita de azuis
    int cost;      // quanto se andou ate chegar nessa configuracao

public:
    Puzzle(int n);
    Puzzle(int n, int cost);
    ~Puzzle();
    bool move(int idx);
    void fill(std::istream &in);
    bool checkWin();
    int heuristic();
    void show(std::ostream &out);
    int getSize();
    int getN() { return this->n; }
    void copy(Puzzle *p);
    bool equals(Puzzle *p);
    int countWhite();
    int getCost();

    bool operator>(Puzzle &p2)
    {
        return this->whiteLeft > p2.heuristic();
    };

    bool operator<(Puzzle &p2)
    {
        return this->whiteLeft < p2.heuristic();
    };

    int getWhiteLeft() const { return whiteLeft; }
    int getCost() const { return cost; }

protected:
    int space_idx;
    char *getPuz();
};

#endif