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
        current = nullptr;
        current = following;
    }
}

template <typename T>
void LinkedList<T>::add(const T& date){
    Node<T>* nodeNew = new Node<T>(date,nullptr,nullptr);
    _size +=1;
    if(last == nullptr){
        nodeNew->former = first;
        last = nodeNew;
        return;
    }
    nodeNew->former = last;
    last = nullptr;
    last = nodeNew;
    return;
}

template<typename T>
void LinkedList<T>::addFirst(const T& date){
    Node<T>* nodeNew = new Node<T>(date , nullptr , nullptr);
    _size +=1;
    if(first == nullptr){
        first = nodeNew;
        return;
    }
    Node<T>* firstCurrent = first;
    first = nullptr;
    first = nodeNew;
    nodeNew->following = firstCurrent;
    firstCurrent = nullptr;
    return;
}
template<typename T>
T* LinkedList<T>::get(int index){
    if(index < 0 || index >(_size - 1)){
        return nullptr;
    }
    return getRecursive(first , 0 , index)->date;
}
template<typename T>
Node<T>* LinkedList<T>::getRecursive(Node<T>* node , int currentIndex , int indexObjetive){
    if(node == nullptr){
        return nullptr;
    }
    if(currentIndex == indexObjetive){
        return node;
    }
    currentIndex +=1;
    return getRecursive(node->following ,currentIndex , indexObjetive);
}
