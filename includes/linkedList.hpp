#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <stdexcept>
#include <sstream>


template<typename T>
struct Node{
    T date;
    Node<T>* prev;
    Node<T>* next;

    Node(const T& date, Node<T>* prev, Node<T>* next)
        : date(date), prev(prev), next(next) {}
};


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

    bool empty()const{
        return _size == 0;
    }

    bool contains(T elem) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->date == elem) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int indexOf(T elem) const {
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
    void add(const T&& date) {
        Node<T>* newNode = new Node<T>(date, tail, nullptr);
        _size++;

        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void addFirst(const T&& date) {
        Node<T>* newNode = new Node<T>(date, nullptr, head);
        _size++;
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }
        head->prev = newNode;
        head = newNode;
    }

    void set(int index, const T&& elem) {
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

    T& getFirst() const {
        if (head == nullptr) throw std::out_of_range("Empty list: no head element");
        return head->date;
    }

    T& getLast() const {
        if (tail == nullptr) throw std::out_of_range("Empty list: no tail element");
        return tail->date;
    }

    T& operator[](int index) {return get(index);}

    const T& operator[](int index) const{return get(index);}

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

    void push_back(const T& elem){add(elem);}

    void push_front(const T& elem){addFirst(elem);}

    void pop_back(){removeAt(size() - 1);}

    void pop_front(){removeAt(0);}

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

    //----- Iterador -----
   
    class Iterador {
        private:
            Node<T>* currentNode;

        public:

            Iterador(Node<T>* node):currentNode(node){}
            
            //Operator sirve para definir el corpotamiento de por ejemplo cuando ponemos ++lista.

            T& operator*(){return currentNode->date;}

            Iterador& operator++(){currentNode = currentNode->next;return *this;}

            bool operator!=(const Iterador& other)const{return currentNode != other.currentNode;}
            
    };

    Iterador begin(){return Iterador(head);}

    Iterador end(){return Iterador(nullptr);}

    template<typename Predicate>
    const Iterador find_if(Predicate p){
        for(auto it = begin();it!=end();++it){
            if(p(*it))return it;
        }
        return end();
    }
};
#endif
