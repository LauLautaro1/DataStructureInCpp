#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "node.hpp"
#include <stdexcept>
#include <sstream>

template<typename T>
class LinkedList {
private:
    int _size;
    Node<T>* head;
    Node<T>* tail;

public:

    //----- Constructor y Destructor -----
    LinkedList() : _size(0), head(nullptr), tail(nullptr) {}

    ~LinkedList() {
        clear();
    }

    //----- Operaciones Básicas -----
    int size() const {
        return _size;
    }

    bool contains(T elem) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->date == elem) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int indexOf(T elem) {
        Node<T>* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->date == elem) {
                return index;
            }
            current = current->next;
            index++;
        }
        throw std::out_of_range("Element not found in the list");
    }

    //----- Añadir Elementos -----
    void add(const T& date) {
        Node<T>* newNode = new Node<T>(date, tail, nullptr);
        _size++;

        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void addFirst(const T& date) {
        Node<T>* newNode = new Node<T>(date, nullptr, head);
        _size++;
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }
        head->prev = newNode;
        head = newNode;
    }

    void set(int index, const T& elem) {
        this->get(index) = elem;
    }

    //----- Obtener Elementos -----
    T& get(int index) const {
        if (index < 0 || index >= _size) throw std::out_of_range("Invalid index");
        Node<T>* current = head;
        for (int i = 0; current != nullptr && i < index; ++i) {
            current = current->next;
        }
        return current->date;
    }

    T& getFirst() {
        if (head == nullptr) throw std::out_of_range("Empty list: no head element");
        return head->date;
    }

    T& getLast() {
        if (tail == nullptr) throw std::out_of_range("Empty list: no tail element");
        return tail->date;
    }

    //----- Eliminar Elementos -----
    void removeAt(int index) {
        if (index < 0 || index >= _size) throw std::out_of_range("Invalid index");
        if (head == nullptr) throw std::out_of_range("Empty list");

        Node<T>* current = head;
        for (int i = 0; current != nullptr && i < index; ++i) {
            current = current->next;
        }

        // Caso 1: Único nodo
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        }
        // Caso 2: Eliminar head
        else if (current == head) {
            head = head->next;
            head->prev = nullptr;
        }
        // Caso 3: Eliminar tail
        else if (current == tail) {
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
        }
        // Caso 4: Nodo intermedio
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        _size--;
        delete current;
    }

    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        _size = 0;
    }

    //----- Representación en String -----
    std::string toString() const {
        std::ostringstream txt;
        Node<T>* current = head;
        bool firstElement = true;

        while (current != nullptr) {
            if (!firstElement) {
                txt << " <-> ";
            }  
            txt << "[" << current->date << "]";
            current = current->next;
            firstElement = false;
        }
        return txt.str();
    }
};
#endif
