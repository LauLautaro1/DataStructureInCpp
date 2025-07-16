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

    Node(T&& date, Node<T>* prev, Node<T>* next)
        : date(std::move(date)), prev(prev), next(next) {}
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

    LinkedList(LinkedList&& other) noexcept : _size(other._size) , head(other.head) , tail(other.tail){
        other._size = 0;
        other.head = nullptr;
        other.tail = nullptr;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            _size = other._size;
            head = other.head;
            tail = other.tail;

            other._size = 0;
            other.head = nullptr;
            other.tail = nullptr;
        }
        return *this;
    }

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

    void add(T&& date){
        Node<T>* newNode = new Node<T>(std::move(date) , tail , nullptr);
        _size++;

        if(tail == nullptr){
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

    void addFirst(T&& date){
        Node<T>* newNode = new Node<T>(std::move(date), nullptr , head);
        _size++;
        if(head == nullptr){
            head = tail = newNode;
            return;
        }
        head->prev = newNode;
        head = newNode;
    }

    void set(int index, T&& elem) {
        this->get(index) = elem;
    }

    void insertAt(int index , T&& elem){
        this->get(index) = elem;
    }

    void push_back(const T& elem){add(elem);}

    void push_back(T&& elem){add(std::move(elem));}

    void push_front(const T& elem){addFirst(elem);}

    void push_front(T&& elem){addFirst(std::move(elem));}

    //----- Obtener Elementos -----
    T& get(int index) const {
        if (index < 0 || index >= _size) throw std::out_of_range("Invalid index");
        Node<T>* current;

        if(index <= _size / 2){
            current = head;
            for (int i = 0; current != nullptr && i < index; ++i) {
                current = current->next;
            }
        }else{
            current = tail;
            for (int i = size()-1; current != nullptr && i > index; --i) {
                current = current->prev;
            }
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

    T&& extractFirst(){
        if (head == nullptr) throw std::out_of_range("Empty list: no head element");

        Node<T>* extract = head;
        T&& dateReturn = std::move(head->date);

        if(head == tail){
            head = nullptr;
            tail = nullptr;
        }
        else{
            head = head->next;
            head->prev = nullptr;
        }
        _size--;
        delete extract;
        return std::move(dateReturn);
    }

    T&& extract(const int index){ 
        if (index < 0 || index >= _size) throw std::out_of_range("Invalid index");

        Node<T>* current;

        if (index <= _size / 2) {
            current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = _size - 1; i > index; --i) {
                current = current->prev;
            }
        }

        T&& dateReturn = std::move(current->date);

        if(current == head && current == tail){
            head = nullptr;
            tail = nullptr;
        }if(current == head){
            head = head->next;
        }if(current == tail){
            tail = tail->next;
            tail->prev = nullptr;
        }else{
            current->next->prev = current->prev;
            current->prev->next = current->next;
        }

        _size--;
        delete current;
        return std::move(dateReturn);
    }

    T&& extractLast(){
        if (tail == nullptr) throw std::out_of_range("Empty list: no tail element");

        Node<T>* extract = tail;
        T&& dateReturn = std::move(tail->date);

        if(head == tail){
            head = nullptr;
            tail = nullptr;
        }
        else{
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        }

        _size--;
        delete extract;
        return std::move(dateReturn);
    }

    T& operator[](int index) {return get(index);}

    const T& operator[](int index) const{return get(index);}

    //----- Eliminar Elementos -----
    void removeAt(int index) {
        if (index < 0 || index >= _size) throw std::out_of_range("Invalid index");
        if (head == nullptr) throw std::out_of_range("Empty list");

        Node<T>* current;

        if(index <= _size / 2){
            current = head;
            for (int i = 0; current != nullptr && i < index; ++i) {
                current = current->next;
            }
        }else{
            current = tail;
            for (int i = _size-1;current != nullptr && i > index; --i){
                current = current->prev;
            }
        }

        // Caso 1: Único nodo
        if (head == tail) {
            --_size;
            delete current;
            head = nullptr;
            tail = nullptr;
            return;
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
