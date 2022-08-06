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

    Puzzle *child = parent->makeChildCopy();

    // Assume que algum filho sera visitado
    depth += 1;
    nonleaf_count += 1;

    int start, end;
    bool revert_depth = true; // reverte contagem de profundidade caso nao abrir algum filho

    parent->possibleRange(&start, &end);

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

bool bfs(Puzzle *root, list<Puzzle *> *path)
{
    list<Puzzle *> open, closed;
    Puzzle *p, *aux;
    int start, end, idx;
    bool found = false;

    int aux_depth = 1, aux_level_size = 1;

    open.push_back(root->makeChildCopy());

    aux = new Puzzle();

    while (open.size() > 0)
    {
        p = open.front();
        open.pop_front();
        closed.push_back(p);
        node_count++;

        if (p->checkWin())
        {
            found = true;
            break;
        }

        idx = p->space_idx;
        p->possibleRange(&start, &end);
        aux->clone(p);

        for (int i = start; i < end; i++)
        {
            if (i != p->space_idx)
            {
                aux->move(i);
                if (!exists(aux, &open))
                    open.push_back(aux->makeChildCopy());
                aux->move(p->space_idx);
            }
        }

        --aux_depth;
        if (aux_depth == 0)
        {
            nonleaf_count += aux_level_size;
            aux_depth = open.size();
            aux_level_size = aux_depth;
            ++depth;
        }
    }

    if (found)
        buildPath(&closed, path);

    freeList(&open);
    freeList(&closed);
    delete aux;

    return found;
}
#endif