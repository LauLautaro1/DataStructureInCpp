#include "../includes/linkedList.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(){
    
    LinkedList<int> lista;

    lista.add(20);
    lista.add(11);
    lista.add(33);
    lista.add(80);

    lista.removeAt(3);

    lista.addFirst(1);

    cout<<lista.toString()<<endl;

    lista.addFirst(2);

    lista.clear();

    cout<<lista.toString()<<endl;

}
