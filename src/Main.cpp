#include "../includes/linkedList.hpp"
#include <iostream>
#include <string>

void testBasicOperations() {
    std::cout << "=== TESTING BASIC OPERATIONS ===\n";
    LinkedList<int> list;

    // Test empty list
    std::cout << "List is empty? " << (list.empty() ? "Yes" : "No") << "\n";
    std::cout << "Size: " << list.size() << "\n";

    // Test adding elements
    list.add(10);
    list.add(20);
    list.add(30);
    list.addFirst(5);
    list.addFirst(1);

    std::cout << "List after adds: " << list.toString() << "\n";
    std::cout << "Size: " << list.size() << "\n";
    std::cout << "List is empty? " << (list.empty() ? "Yes" : "No") << "\n";

    // Test access operations
    std::cout << "First element: " << list.getFirst() << "\n";
    std::cout << "Last element: " << list.getLast() << "\n";
    std::cout << "Element at index 2: " << list.get(2) << "\n";
    std::cout << "Element at index 3 using []: " << list[3] << "\n";

    // Test contains and indexOf
    std::cout << "Contains 20? " << (list.contains(20) ? "Yes" : "No") << "\n";
    std::cout << "Contains 99? " << (list.contains(99) ? "Yes" : "No") << "\n";
    std::cout << "Index of 20: " << list.indexOf(20) << "\n";

    try {
        std::cout << "Index of 99: " << list.indexOf(99) << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Expected exception: " << e.what() << "\n";
    }
}

void testRemovalOperations() {
    std::cout << "\n=== TESTING REMOVAL OPERATIONS ===\n";
    LinkedList<std::string> list;

    list.add("Apple");
    list.add("Banana");
    list.add("Cherry");
    list.add("Date");
    list.addFirst("Apricot");

    std::cout << "Initial list: " << list.toString() << "\n";

    // Test removeAt
    list.removeAt(2); // Remove "Cherry"
    std::cout << "After removing index 2: " << list.toString() << "\n";

    // Test pop operations
    list.pop_front();
    std::cout << "After pop_front: " << list.toString() << "\n";

    list.pop_back();
    std::cout << "After pop_back: " << list.toString() << "\n";

    // Test clear
    list.clear();
    std::cout << "After clear: " << list.toString() << "\n";
    std::cout << "Size after clear: " << list.size() << "\n";
}

void testIterators() {
    std::cout << "\n=== TESTING ITERATORS ===\n";
    LinkedList<double> list;

    list.add(1.1);
    list.add(2.2);
    list.add(3.3);
    list.add(4.4);

    std::cout << "Using range-based for loop:\n";
    for (auto& item : list) {
        std::cout << item << " ";
    }
    std::cout << "\n";

    std::cout << "Using iterator manually:\n";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Test find_if
    auto result = list.find_if([](double x) { return x > 2.5; });
    if (result != list.end()) {
        std::cout << "First element > 2.5: " << *result << "\n";
    } else {
        std::cout << "No element > 2.5 found\n";
    }
}

void testStringList() {
    std::cout << "\n=== TESTING STRING LIST ===\n";
    LinkedList<std::string> list;

    list.push_back("Hello");
    list.push_back("World");
    list.push_front("C++");
    list.push_front("Modern");

    std::cout << "String list: " << list.toString() << "\n";

    // Test set operation
    list.set(2, "Universe");
    std::cout << "After set(2, \"Universe\"): " << list.toString() << "\n";

    // Test move semantics
    std::string temp = "Temporary";
    list.add(std::move(temp));
    std::cout << "After moving temp string: " << list.toString() << "\n";
    std::cout << "Original string is now: \"" << temp << "\" (empty due to move)\n";
}

void testEdgeCases() {
    std::cout << "\n=== TESTING EDGE CASES ===\n";
    LinkedList<int> list;

    try {
        std::cout << "Trying getFirst() on empty list: ";
        std::cout << list.getFirst() << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    try {
        std::cout << "Trying removeAt(0) on empty list: ";
        list.removeAt(0);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    list.add(42);
    std::cout << "Single element list: " << list.toString() << "\n";
    list.removeAt(0);
    std::cout << "After removing single element: " << list.toString() << "\n";
}
void testMoveSemantics() {
    std::cout << "\n=== TESTING MOVE SEMANTICS ===\n";

    // Test 1: Movimiento de un string temporal
    {
        LinkedList<std::string> list;
        list.push_back(std::string("Temporal"));
        std::cout << "Added temporary string, list size: " << list.size()
                  << ", content: " << list.toString() << "\n";
    }

    // Test 2: Movimiento de un objeto con recursos
    {
        LinkedList<std::string> list;
        std::string str = "RecursoImportante";
        const char* original_data = str.c_str(); // Guardamos el puntero a los datos

        std::cout << "Before move - str: \"" << str << "\" ("
                  << (str.empty() ? "empty" : "not empty") << ")\n";

        list.push_back(std::move(str));

        std::cout << "After move - str: \"" << str << "\" ("
                  << (str.empty() ? "empty" : "not empty") << ")\n";
        std::cout << "List content: " << list.toString() << "\n";

        // Verificamos que los datos se hayan movido
        const char* list_data = list.getLast().c_str();
        std::cout << "Data pointer comparison: "
                  << (original_data == list_data ? "SAME (move successful)"
                                               : "DIFFERENT (copy occurred)")
                  << "\n";
    }

    // Test 3: Movimiento entre listas
    {
        LinkedList<std::string> source;
        source.push_back("Elemento1");
        source.push_back("Elemento2");

        LinkedList<std::string> destination;
        destination.push_back(std::move(source.getFirst()));

        std::cout << "\nSource list after move: " << source.toString()
                  << " (size: " << source.size() << ")\n";
        std::cout << "Destination list: " << destination.toString()
                  << " (size: " << destination.size() << ")\n";
    }

    // Test 4: Movimiento de enteros (tipo trivial)
    {
        LinkedList<int> list;
        int x = 42;
        list.push_back(std::move(x));
        std::cout << "\nAfter moving int: x = " << x
                  << " (should still be 42, move doesn't affect trivial types)\n";
    }
}

int main() {
    testBasicOperations();
    testRemovalOperations();
    testIterators();
    testStringList();
    testEdgeCases();
    testMoveSemantics();
    return 0;
}
