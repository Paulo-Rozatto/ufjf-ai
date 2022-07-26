#ifndef PUZZLE_SEARCH_H
#define PUZZLE_SEARCH_H

#include <iostream>
#include <fstream>
#include <list>
#include "util.h"
#include "queue.h"

#define INFINITY 2147483647
#define FOUND -1

using namespace std;

// Globais de estatistica
int depth, cost, node_count, nonleaf_count;

bool backtracking(Puzzle *p, list<Puzzle *> *path)
{
    node_count += 1;

    path->push_back(p);

    if (p->checkWin())
        return true;

    Puzzle *child = p->makeChildCopy();

    // Assume que algum filho sera visitado
    depth += 1;
    nonleaf_count += 1;

    int start, end;
    bool revert_depth = true; // reverte contagem de profundidade caso nao abrir algum filho

    p->possibleRange(&start, &end);

    for (int i = start; i < end; i++)
    {
        if (i != p->space_idx)
        {
            child->move(i);

            if (!exists(child, path))
            {
                revert_depth = false;
                child->cost = p->cost + abs(i - p->space_idx);
                if (backtracking(child, path))
                    return true;
            }

            child->move(p->space_idx); // volta estado se falhar
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
                {
                    aux->cost = p->cost + abs(i - p->space_idx);
                    open.push_back(aux->makeChildCopy());
                }
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

        while (counter.back() == 0)
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
                        aux->cost = p->cost + abs(i - p->space_idx);
                        open.push_back(aux->makeChildCopy());
                        count++;
                    }
                    aux->move(p->space_idx);
                }
            }

            if (count)
            {
                curr_depth++;
                nonleaf_count++;
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

bool ordered(Puzzle *root, list<Puzzle *> *path)
{
    MyQueue<Puzzle *, vector<Puzzle *>, CmpCost> min_heap;
    list<Puzzle *> closed;
    Puzzle *top, *aux;
    bool found = false, childFlag;
    int start, end, max_cost = -1;

    min_heap.push(root->makeChildCopy());
    aux = new Puzzle();

    while (min_heap.size() > 0)
    {
        top = min_heap.top();
        min_heap.pop();
        closed.push_back(top);
        node_count++;

        if (top->cost > max_cost)
        {
            max_cost = top->cost;
            depth++;
        }

        if (top->checkWin())
        {
            found = true;
            break;
        }

        top->possibleRange(&start, &end);
        aux->clone(top);
        childFlag = false;
        for (int i = start; i < end; i++)
        {
            if (i != top->space_idx)
            {
                aux->move(i);
                if (!exists(aux, &closed) && !exists(aux, &min_heap))
                {
                    childFlag = true;
                    aux->cost = top->cost + abs(i - top->space_idx);
                    min_heap.push(aux->makeChildCopy());
                }
                aux->move(top->space_idx);
            }
        }
        if (childFlag)
            nonleaf_count++;
    }

    if (found)
        buildPath(&closed, path);

    freeHeap(&min_heap);
    freeList(&closed);
    delete aux;

    return found;
}

bool greed(Puzzle *root, list<Puzzle *> *path)
{
    MyQueue<Puzzle *, vector<Puzzle *>, CmpHeuristc> min_heap;
    list<Puzzle *> closed;
    Puzzle *top, *aux;
    bool found = false, childFlag;
    int start, end, max_cost = -1;

    min_heap.push(root->makeChildCopy());
    aux = new Puzzle();

    while (min_heap.size() > 0)
    {
        top = min_heap.top();
        min_heap.pop();
        closed.push_back(top);
        node_count++;

        if (top->cost > max_cost)
        {
            max_cost = top->cost;
            depth++;
        }

        if (top->checkWin())
        {
            found = true;
            break;
        }

        top->possibleRange(&start, &end);
        aux->clone(top);
        childFlag = false;
        for (int i = start; i < end; i++)
        {
            if (i != top->space_idx)
            {
                aux->move(i);
                if (!exists(aux, &closed) && !exists(aux, &min_heap))
                {
                    childFlag = true;
                    aux->cost = top->cost + abs(i - top->space_idx);
                    min_heap.push(aux->makeChildCopy());
                }
                aux->move(top->space_idx);
            }
        }
        if (childFlag)
            nonleaf_count++;
    }

    if (found)
        buildPath(&closed, path);

    freeHeap(&min_heap);
    freeList(&closed);
    delete aux;

    return found;
}

bool aStar(Puzzle *root, list<Puzzle *> *path)
{
    MyQueue<Puzzle *, vector<Puzzle *>, CmpObjective> min_heap;
    list<Puzzle *> closed;
    Puzzle *top, *aux;
    bool found = false, childFlag;
    int start, end, max_cost = -1;

    min_heap.push(root->makeChildCopy());
    min_heap.top()->cost = 0;
    aux = new Puzzle();

    while (min_heap.size() > 0)
    {
        top = min_heap.top();
        min_heap.pop();
        closed.push_back(top);
        node_count++;

        if (top->cost > max_cost)
        {
            max_cost = top->cost;
            depth++;
        }

        if (top->checkWin())
        {
            found = true;
            break;
        }

        top->possibleRange(&start, &end);
        aux->clone(top);
        childFlag = false;
        for (int i = start; i < end; i++)
        {
            if (i != top->space_idx)
            {
                aux->move(i);
                if (!exists(aux, &min_heap) && !exists(aux, &closed))
                {
                    aux->cost = top->cost + abs(i - top->space_idx);
                    childFlag = true;
                    min_heap.push(aux->makeChildCopy());
                }
                aux->move(top->space_idx);
            }
        }

        if (childFlag)
            nonleaf_count++;
    }

    if (found)
        buildPath(&closed, path);

    freeHeap(&min_heap);
    freeList(&closed);
    delete aux;

    return found;
}

int search(list<Puzzle *> *path, int threshold)
{
    Puzzle *p = path->back();
    int objective = p->cost + p->heuristic();

    node_count++;

    if (objective > threshold)
        return objective;
    if (p->checkWin())
        return FOUND;

    int min = INFINITY, new_threshold;
    int start, end;
    bool hasChild = false;
    Puzzle *child = p->makeChildCopy();

    p->possibleRange(&start, &end);

    for (int i = start; i < end; i++)
    {
        if (i != p->space_idx)
        {
            child->move(i);
            if (!exists(child, path))
            {
                hasChild = true;
                path->push_back(child);
                child->cost = p->cost + abs(i - p->space_idx);
                new_threshold = search(path, threshold);
                if (new_threshold == FOUND)
                    return FOUND;
                if (new_threshold < min)
                    min = new_threshold;
                path->pop_back();
            }
            child->move(p->space_idx);
        }
    }
    if (hasChild)
    {
        depth++;
        nonleaf_count++;
    }

    return min;
}

bool idaStar(Puzzle *root, list<Puzzle *> *path)
{
    int threshold = root->objective();
    int new_threshold, max_depth = 0;
    path->push_back(root);

    while (1)
    {
        depth = 0;
        new_threshold = search(path, threshold);
        if (new_threshold == FOUND)
            return true;
        if (new_threshold == INFINITY)
            return false;
        threshold = new_threshold;
        if (depth > max_depth)
            max_depth = depth;
    }

    depth = max_depth;
}
#endif