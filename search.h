#ifndef PUZZLE_SEARCH_H
#define PUZZLE_SEARCH_H

#include <iostream>
#include <fstream>
#include <list>
#include "util.h"

using namespace std;

// Globais de estatistica
int depth, cost, node_count, nonleaf_count;

bool backtracking(Puzzle *parent, list<Puzzle *> *path)
{
    node_count += 1;

    path->push_back(parent);

    if (parent->checkWin())
    {
        cout << "ei" << endl;
        return true;
    }

    int start, end;
    bool revert_depth = true;

    start = parent->space_idx - Puzzle::n;
    end = parent->space_idx + Puzzle::n;

    if (start < 0)
        start = 0;
    if (end >= Puzzle::size)
        end = Puzzle::size;

    Puzzle *child = parent->makeCopy();

    // Assume que algum filho sera visitado
    depth += 1;
    nonleaf_count += 1;

    for (int i = start; i < end; i++)
    {
        if (i != parent->space_idx)
        {
            child->move(i);

            if (!exists(child, path))
            {
                revert_depth = false;
                if (backtracking(child, path))
                    return true;
            }

            child->move(parent->space_idx); // volta estado se falhar
        }
    }

    if (revert_depth)
    {
        depth -= 1;
        nonleaf_count -= 1;
    }
    path->pop_back();
    delete child;

    return false;
}

#endif