#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
struct Node{
    T date;
    Node<T>* prev;
    Node<T>* next;

    Node(const T& date, Node<T>* prev, Node<T>* next)
        : date(date), prev(prev), next(next) {}
};

#endif
