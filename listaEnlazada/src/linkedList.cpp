#include "../includes/linkedList.hpp"

template <typename T>
LinkedList<T>::LinkedList(){
    _size = 0;
    first = nullptr;
    last = nullptr;
}
template <typename T>
LinkedList<T>::~LinkedList(){
    Node<T>* current = first;
    while (current != nullptr) {
        Node<T>* following = current->following;
        delete current;
        current = following;
    }
}

template <typename T>
void LinkedList<T>::add(const T& date){
    Node<T> nodeNew = new Node<T>(date,nullptr,nullptr);
    if(last == nullptr){
        nodeNew.former = first;
        last = nodeNew;
        return;
    }
    nodeNew.former = last;
    last = nullptr;
    last = nodeNew;
    return;
}

