#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
struct Node{
    T date;
    Node<T>* former;
    Node<T>* following;

    Node(const T& val, Node<T>* prev, Node<T>* next)
        : date(val), former(prev), following(next) {}
};

#endif
