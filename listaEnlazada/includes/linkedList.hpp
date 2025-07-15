#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "node.hpp"

template<typename T>
class LinkedList{
    private:
        int _size;
        Node<T> first;
        Node<T> last;

        Node<T>* getRecursive(Node<T>* node ,int currentIndex , int indexObjetive);

    public:
        LinkedList();

        ~LinkedList();

        void add(const T& date);

        void addFirst(const T& date);

        T* get(int index);

        T* getFirst();

        T* getLast();

        int size();
};
#endif
