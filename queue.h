#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <queue>

template <
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>>
class MyQueue : public std::priority_queue<T, Container, Compare>
{
public:
    typedef typename std::priority_queue<
        T,
        Container,
        Compare>::container_type::const_iterator const_iterator;

    const_iterator find(const T &val) const
    {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first != last)
        {
            if (*first == val)
                return first;
            ++first;
        }
        return last;
    }

    const_iterator begin()
    {
        auto first = this->c.cbegin();
        return first;
    }

    const_iterator end()
    {
        auto last = this->c.cend();
        return last;
    }
};

#endif