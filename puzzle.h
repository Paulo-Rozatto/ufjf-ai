#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>

#define blue 'b'  // azul
#define white 'w' // branco

class Puzzle
{
public:
    static int n;    // quantidade de blocos de cada cor
    static int size; // tamanho total da regua (2 * n + 1)

    char *puz;     // puzzle
    int space_idx; // posicao do espaco em branco
    int whiteLeft; // numero de brancas que ainda estao a direita de azuis
    int cost;      // quanto se andou ate chegar nessa configuracao
    int generator; // movimento que gerou estado atual

    Puzzle();
    ~Puzzle();
    void fill(std::istream &in);
    bool move(int idx);
    bool checkWin();
    int heuristic();
    int countWhite();
    bool equals(Puzzle *p);
    void show(std::ostream &out);
    Puzzle *makeCopy();

    bool operator>(Puzzle &p2)
    {
        return this->whiteLeft > p2.heuristic();
    };

    bool operator<(Puzzle &p2)
    {
        return this->whiteLeft < p2.heuristic();
    };

    // int getCost() const { return cost; }
protected:
    char *getPuz();
};

#endif