#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
struct Node{
    T* date;
    Node<T>* former;
    Node<T>* following;
};

#endif
