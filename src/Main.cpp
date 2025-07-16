#include "../includes/linkedList.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(){
    
    LinkedList<int> lista;

    lista.add(20);

    lista.add(30);

    lista.add(40);

    auto it = lista.find_if([](int x) { return x % 2 == 0; });

    if(it != lista.end()){
        std::cout<<"Encotrado : " << *it <<endl;
    }

    std::cout<<"Accediendo como un array a la lista : " << lista[2]<<endl;



}
