#ifndef TREE_H
#define TREE_H

#include <stdexcept>
#include <sstream>
#include <vector>
template<typename T>
struct Node{
    T date;
    std::vector<Node<T>*> children;
    Node<T>* parent;


    Node(const T& date):date()




};

template<typename T>
class Tree{
    private:
        int _amount;
        int _level;
        Node<T>* root;

    public:

        Tree(){
            root = nullptr;
            _amount = 0;
            _level = 0;
        }

        Tree(const T& date){
            root = new Node<T>(date);
            _amount = 0;
            _level = 0;
        }

        Tree(Tree&& other)noexcept:_amount(other._amount) , _level(other._level),root(other.root){
            other._amount = nullptr;
            other._level = nullptr;
            other.root = nullptr;
        }




};
#endif

