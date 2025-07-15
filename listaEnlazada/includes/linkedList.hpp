#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "node.hpp"
#include <stdexcept>

template<typename T>
class LinkedList{
    private:
        int _size;
        Node<T>* first;
        Node<T>* last;

    public:
        
        LinkedList() : _size(0), first(nullptr), last(nullptr) {}

        ~LinkedList(){
            Node<T>* current = first;
            while (current != nullptr) {
            Node<T>* following = current->following;
            delete current;
            current = nullptr;
            current = following;
            }
        }

        void add(const T& date){
            Node<T>* nodeNew = new Node<T>(date,last,nullptr);
            _size +=1;

            if (last == nullptr) {
                first = last = nodeNew;
            } else {
                last->following = nodeNew;
                last = nodeNew;
            }

        }
        void addFirst(const T& date){
            Node<T>* nodeNew = new Node<T>(date , nullptr , first);
            _size +=1;
            if(first == nullptr){
                first = nodeNew;
                last = nodeNew;
                return;
            }
            first->former = nodeNew;
            first = nodeNew;
            return;
        }

        T& get(int index) const {
            if (index < 0 || index >= _size) throw std::out_of_range("el index no es el correcto.");
            Node<T>* current = first;
            for (int i = 0; current != nullptr && i < index; ++i) {
                current = current->following;
            }
            return current->date;
        }

        T& getFirst(){
            if (first == nullptr) throw std::out_of_range("Lista vacía: no hay primer elemento");
            return first->date;
        }

        T& getLast(){
            if (last == nullptr) throw std::out_of_range("Lista vacía: no hay último elemento");
            return last->date;
        }

        int size(){
            return _size;
        }

        void removeAt(int index){
            if (index < 0 || index >= _size) throw std::out_of_range("el index no es el correcto.");
            if(first == nullptr) throw std::out_of_range("No hay elementos en la lista.");

            Node<T>* current = first;

            for (int i=0;current != nullptr && i<index ;++i){
                current = current->following;
            }

            //Eliminar el unico nodo
            if(first == last){
                first = nullptr;
                last = nullptr;
            }
            //Eliminar primer nodo
            else if(current == first){
                first = first->following;
                first->former = nullptr;
            }
            //Eliminar ultimo nodo.
            
            else if (current == last) {
                last = last->former;
                if (last != nullptr) {
                    last->following = nullptr;
                    }
            }
            //eliminar nodo intermedio
            else{
                current->former->following = current->following;
                current->following->former = current->former;
            }
            _size -=1;
            delete current;
            return;
        }
};
#endif
