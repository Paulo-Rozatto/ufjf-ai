#ifndef PUZZLE_SEARCH_H
#define PUZZLE_SEARCH_H

#include <iostream>
#include <fstream>
#include <list>
#include "util.h"

#define INFINITY 2147483647
#define FOUND -1

using namespace std;

// Globais de estatistica
int depth, cost, node_count, nonleaf_count;

bool backtracking(Puzzle *parent, list<Puzzle *> *path)
{
    node_count += 1;

    path->push_back(parent);

    if (parent->checkWin())
        return true;

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
    int start, end;
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

        p->possibleRange(&start, &end);
        aux->clone(p);

        for (int i = start; i < end; i++)
        {
            if (i != p->space_idx)
            {
                aux->move(i);
                if (!exists(aux, &open) && !exists(aux, &closed))
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

bool dfs(Puzzle *root, list<Puzzle *> *path, int max_depth)
{
    list<Puzzle *> open, closed;
    vector<int> counter;
    Puzzle *p, *aux;
    int start, end, count;
    bool found = false;

    bool added = false;
    int curr_depth = 1;

    open.push_back(root->makeChildCopy());
    counter.push_back(1);

    aux = new Puzzle();

    while (open.size() > 0)
    {
        p = open.back();
        open.pop_back();
        closed.push_back(p);

        if (counter.back() == 0)
        {
            curr_depth -= 1;
            counter.pop_back();
        }

        counter.at(counter.size() - 1) -= 1;

        node_count++;

        if (p->checkWin())
        {
            found = true;
            break;
        }

        if (curr_depth < max_depth)
        {
            p->possibleRange(&start, &end);
            aux->clone(p);

            added = false;
            count = 0;
            for (int i = start; i < end; i++)
            {
                if (i != p->space_idx)
                {
                    aux->move(i);
                    if (!exists(aux, &open) && !exists(aux, &closed))
                    {
                        open.push_back(aux->makeChildCopy());
                        count++;
                    }
                    aux->move(p->space_idx);
                }
            }

            if (count)
            {
                curr_depth++;
                counter.push_back(count);
            }
        }

        if (curr_depth > depth)
            depth = curr_depth;
    }

    if (found)
        buildPath(&closed, path);

    freeList(&open);
    freeList(&closed);
    delete aux;

    return found;
}

struct CmpHeuristc
{
    bool operator()(const Puzzle *p1, const Puzzle *p2) const
    {
        return p1->whiteLeft > p2->whiteLeft;
    }
};

bool greed(Puzzle *root, list<Puzzle *> *path)
{
    priority_queue<Puzzle *, vector<Puzzle *>, CmpHeuristc> min_heap;
    list<Puzzle *> closed;
    Puzzle *top, *aux;
    bool found = false;
    int start, end;

    min_heap.push(root->makeChildCopy());
    aux = new Puzzle();

    while (min_heap.size() > 0)
    {
        top = min_heap.top();
        min_heap.pop();
        closed.push_back(top);
        node_count++;

        if (top->checkWin())
        {
            found = true;
            break;
        }

        top->possibleRange(&start, &end);
        aux->clone(top);

        for (int i = start; i < end; i++)
        {
            if (i != top->space_idx)
            {
                aux->move(i);
                if (!exists(aux, &closed))
                    min_heap.push(aux->makeChildCopy());
                aux->move(top->space_idx);
            }
        }
    }

    if (found)
        buildPath(&closed, path);

    // todo: free min_heap
    freeList(&closed);
    delete aux;

    return found;
}

struct CmpObjective
{
    bool operator()(const Puzzle *p1, const Puzzle *p2) const
    {
        return (p1->whiteLeft + p1->cost) > (p2->cost + p1->cost);
    }
};

bool aStar(Puzzle *root, list<Puzzle *> *path)
{
    priority_queue<Puzzle *, vector<Puzzle *>, CmpObjective> min_heap;
    list<Puzzle *> closed;
    Puzzle *top, *aux;
    bool found = false;
    int start, end;

    min_heap.push(root->makeChildCopy());
    min_heap.top()->cost = 0;
    aux = new Puzzle();

    while (min_heap.size() > 0)
    {
        top = min_heap.top();
        min_heap.pop();
        closed.push_back(top);
        node_count++;

        if (top->checkWin())
        {
            found = true;
            break;
        }

        top->possibleRange(&start, &end);
        aux->clone(top);

        for (int i = start; i < end; i++)
        {
            if (i != top->space_idx)
            {
                aux->move(i);
                if (!exists(aux, &closed))
                    min_heap.push(aux->makeChildCopy());
                aux->move(top->space_idx);
            }
        }
    }

    if (found)
        buildPath(&closed, path);

    // todo: free min_heap
    freeList(&closed);
    delete aux;

    return found;
}

bool idaRec(Puzzle *parent, list<Puzzle *> *path, int *threshold, int *old_threshold, priority_queue<Puzzle *, vector<Puzzle *>, CmpObjective> *discarded)
{
    node_count += 1;

    path->push_back(parent);

    if (parent->checkWin() && parent->objective() <= *threshold)
        return true;

    if (parent->objective() > *threshold)
    {
        discarded->push(parent);
        path->pop_back();
        return false;
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
                if (idaRec(child, path, threshold, old_threshold, discarded))
                    return true;
                child = parent->makeChildCopy();
            }
            else
                child->move(parent->space_idx); // volta estado se falhar
        }
    }

    if (revert_depth)
    {
        depth -= 1;
        nonleaf_count -= 1;
    }
    path->pop_back();
    // delete child;

    return false;
}

int search(list<Puzzle *> *path, int cost, int threshold)
{
    Puzzle *p = path->back();
    int f = cost + p->heuristic();

    if (f > threshold)
        return f;
    if (p->checkWin())
        return FOUND;

    int min = INFINITY;
    int start, end, t;
    Puzzle *child = p->makeChildCopy();

    p->possibleRange(&start, &end);

    for (int i = start; i < end; i++)
    {
        if (i != p->space_idx)
        {
            child->move(i);
            if (!exists(child, path))
            {
                path->push_back(child);
                t = search(path, cost + 1, threshold);
                if (t == FOUND)
                    return FOUND;
                if (t < min)
                    min = t;
                path->pop_back();
            }
            child->move(p->space_idx);
        }
    }

    return min;
}

bool idaStar(Puzzle *root, list<Puzzle *> *path)
{
    int threshold = root->objective();
    int t;
    path->push_back(root);

    while (1)
    {
        t = search(path, 0, threshold);
        if (t == FOUND)
            return true;
        if (t == INFINITY)
            return false;
        threshold = t;
    }
}
#endif