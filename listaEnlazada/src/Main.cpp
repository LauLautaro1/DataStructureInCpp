#include "../includes/linkedList.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(){
    
    LinkedList<int> lista;

    lista.add(22);

    lista.add(3);
    lista.add(5);
    lista.add(222);
    lista.add(9000);
    lista.add(10);

    lista.removeAt(2);
    lista.removeAt(1);

    int a = lista.getFirst();

    lista.addFirst(1);

    int b = lista.get(lista.size() - 1);

    cout<<"Dato : "<<a<<endl;

    cout<<"Dato : "<<b<<endl;

    cout<<"Dato : "<<lista.getFirst()<<endl;

    cout<<"Dato : "<<lista.get(0)<<endl;

    LinkedList<string> l2;

    l2.add("Hola");

    cout<<"Dato : " << l2.getFirst()<<endl;



    return 0;
}
