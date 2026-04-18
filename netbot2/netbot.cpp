#include "netbot.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// nodo de la lista doble
class Node {
public:
    // valor guardado en el nodo
    LogEntry value;
    // apuntador al siguiente nodo
    Node* next;
    // apuntador al nodo anterior
    Node* prev;

    // constructor del nodo
    Node(const LogEntry& _value) : value(_value), next(nullptr), prev(nullptr) {}

    // destructor del nodo
    ~Node() {
        next = nullptr;
        prev = nullptr;
    }
};


// Stack implementation using linked list
class Stack {
    Node* top;
    
    // To Store current size of stack
    int count;
    
public:
    Stack() {
        
        // initially stack is empty
        top = NULL;
        count = 0;
    }

    // push operation
    void push(LogEntry x) {
        Node* temp = new Node(x);
        temp->next = top;
        top = temp;
        
        count++;
    }

    // pop operation
    LogEntry pop() {
        if (isEmpty()) {
            throw out_of_range("stack underflow");
        }
        Node* temp = top;
        top = top->next;
        LogEntry val = temp->value;
        
        count--;
        delete temp;
        return val;
    }

    // peek operation
    LogEntry peek() {
        if (isEmpty()) {
            throw out_of_range("stack underflow");
        }
        return top->value;
    }

    // check if stack is empty
    bool isEmpty() {
        return top == NULL;
    }

    // size of stack
    int getSize() {
        return count;
    }
};


// clase de lista doblemente ligada
class DoublyLinkedList {
    private:
    // primer nodo de la lista
    Node* head;
    // ultimo nodo de la lista
    Node* tail;
    // cantidad de elementos
    int size;

    public:
    // constructor de la lista
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // destructor de la lista
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // inserta un valor al inicio
    void insertFirst(const LogEntry& value) {
        Node* auxNode = new Node(value);

        if (head == nullptr) {
            head = auxNode;
            tail = auxNode;
        } else {
            auxNode->next = head;
            head->prev = auxNode;
            head = auxNode;
        }
        size++;
    }

    // inserta un valor al final
    void insertLast(const LogEntry& value) {
        if (tail == nullptr) {
            insertFirst(value);
            return;
        }

        Node* auxNode = new Node(value);
        auxNode->prev = tail;
        tail->next = auxNode;
        tail = auxNode;
        size++;
    }

    // inserta un valor en una posicion especifica
    void insertAt(const LogEntry& value, int index, bool print = false) {
        if (index < 0 || index > size) {
            if (print) {
                cout << "Invalid index: " << index << ". Valid range is 0 to " << size << "." << endl;
            }
            return;
        }

        if (index == 0) {
            insertFirst(value);
            return;
        }

        if (index == size) {
            insertLast(value);
            return;
        }

        Node* current = head;
        int i = 0;
        while (i < index) {
            current = current->next;
            i++;
        }

        Node* auxNode = new Node(value);
        auxNode->next = current;
        auxNode->prev = current->prev;
        current->prev->next = auxNode;
        current->prev = auxNode;

        if (print) {
            cout << "Inserting node at index: " << index << endl;
        }

        size++;
    }

    // elimina el primer nodo
    void deleteFirst() {
        if (head == nullptr) {
            return;
        }

        Node* auxNode = head;

        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }

        delete auxNode;
        size--;
    }

    // elimina el ultimo nodo
    void deleteLast(bool print = false) {
        if (tail == nullptr) {
            return;
        }

        if (head == tail) {
            deleteFirst();
            return;
        }

        if (print) {
            cout << "Deleting last node." << endl;
        }

        Node* auxNode = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete auxNode;
        size--;
    }

    // elimina un nodo en una posicion especifica
    void deleteAt(int index, bool print = false) {
        if (index < 0 || index >= size) {
            throw out_of_range("invalid index in getAt");
        }

        if (index == 0) {
            deleteFirst();
            return;
        }

        if (index == size - 1) {
            deleteLast(print);
            return;
        }

        Node* current = head;
        int i = 0;
        while (i < index) {
            current = current->next;
            i++;
        }

        if (print) {
            cout << "Deleting node at index: " << index << endl;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        size--;
    }

    // busca si un valor existe en la lista
    bool find(const LogEntry& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // obtiene el valor en una posicion
    LogEntry getAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("invalid index in getAt");
        }

        Node* current = head;
        int i = 0;
        while (i < index) {
            current = current->next;
            i++;
        }

        return current->value;
    }

    // actualiza el valor en una posicion
    void updateAt(const LogEntry& value, int index, bool print = false) {
        if (index < 0 || index >= size) {
            cout << "Invalid index: " << index << ". Valid range is 0 to " << size - 1 << "." << endl;
            return;
        }

        Node* current = head;
        int i = 0;
        while (i < index) {
            current = current->next;
            i++;
        }

        if (print) {
            cout << "Updating node at index: " << index << endl;
        }

        current->value = value;
    }

    // regresa el tamaño actual de la lista
    int getSize() {
        return size;
    }

    // imprime la lista de inicio a fin
    void printForward() {

        Node* current = head;
        while (current != nullptr) {
            cout << current->value << " -> " << endl;
            current = current->next;
        }
        cout << "null" << endl;
    }

    // imprime la lista de fin a inicio
    void printBackward() {
        Node* current = tail;
        while (current != nullptr) {
            cout << current->value << " -> ";
            current = current->prev;
        }
        cout << "null" << endl;
    }

    Node* getHead() {
        return head;
    }

    Node* getTail() {
        return tail;
    }

};



// Function to partition the list and find pivot
Node* partition(Node* low, Node* high) {
    // Set pivot to the high node
    LogEntry pivot = high->value;

    // Pointer to place smaller elements
    Node* i = low->prev;

    // Traverse the list to rearrange nodes
    for (Node* j = low; j != high; j = j->next) {
        
        // If current node's value is less than or 
        // equal to the pivot
        if (j->value <= pivot) {
            
            // Move i forward and swap with j
            i = (i == nullptr) ? low : i->next;
            swap(i->value, j->value);
        }
    }

    // Move i to the correct pivot position
    i = (i == nullptr) ? low : i->next;
  
    // Swap pivot with i's value
    swap(i->value, high->value);

    return i;
}

// funcion auxiliar para convertir pilas a DLL's
DoublyLinkedList* stackToDLL(Stack* stack){
    DoublyLinkedList* list = new DoublyLinkedList();
    while(!stack->isEmpty()){
        LogEntry value = stack->pop();
        list->insertLast(value);
    }
    return list;
}

DoublyLinkedList* joinDLL(DoublyLinkedList* list1, DoublyLinkedList* list2, DoublyLinkedList* list3) {
    DoublyLinkedList* list = new DoublyLinkedList();
    Node* current = nullptr;

    // copy list1
    if (list1 != nullptr) {
        current = list1->getHead();
        while (current != nullptr) {
            list->insertLast(current->value);
            current = current->next;
        }
    }

    // copy list2
    if (list2 != nullptr) {
        current = list2->getHead();
        while (current != nullptr) {
            list->insertLast(current->value);
            current = current->next;
        }
    }

    // copy list3
    if (list3 != nullptr) {
        current = list3->getHead();
        while (current != nullptr) {
            list->insertLast(current->value);
            current = current->next;
        }
    }

    return list;
}




// Recursive function to apply quicksort
DoublyLinkedList* quickSortStack(DoublyLinkedList* list) {
  
    // definir cabeza y cola de la lista
    Node* low = list->getHead();
    Node* high = list->getTail();
    // solo ordenar si:
    // la cabeza no es null, 
    // la cola no es null, 
    // cola y cabeza no son iguales 
    // y cabeza es diferente del siguiente a la cola
    if (low != nullptr && high != nullptr 
        && low != high && low != high->next) {
        // se define el primer valor de la lista como el pivote
        // este valor se usará para ordenar dividir los elementos
        LogEntry pivot = high->value;

        // se crean tres pilas auxiliares, 
        // para guardar los datos menores, mayores e iguales que el pivote
        Stack* smallerStack = new Stack();
        Stack* equalStack = new Stack();
        Stack* biggerStack = new Stack();

        // se recorre la lista con un current (por ser iterativo)
        Node* current = low;

        // para recorrer la lista, mientras current sea dif de null
        while (current != nullptr){
            // si el valor es menor que el pivote a la smaller
            // si no, si es mayor a la bigger stack
            // sino a la equal stack
            if (current->value < pivot){
                smallerStack->push(current->value);
            } else if((current->value > pivot)){
                biggerStack->push(current->value);
            } else {
                equalStack->push(current->value);
            }
            // continua al siguiente nodo
            current = current->next;
        }

        // se convierten las stacks a DLL's
        DoublyLinkedList* smallerList = stackToDLL(smallerStack);
        DoublyLinkedList* biggerList = stackToDLL(biggerStack);
        DoublyLinkedList* equalList = stackToDLL(equalStack);

        // se vuelven a ordenar las menores y mayores que el pivot
        smallerList = quickSortStack(smallerList);
        biggerList = quickSortStack(biggerList);

        // se pegan las 3 listas

        DoublyLinkedList* newList = joinDLL(smallerList,equalList,biggerList);

        // devuelve la lista ordenada
        return newList;

    }
    else {
        // devuelve la lista original porque estaba vacía, para no
        // dejar comportamiento indefinido
        return list;
    }
}
//Convierte los strings de meses a int
int monthToInt(string m){
    if (m == "ene"){
        return 1;
    } else if (m == "Feb"){
        return 2;
    } else if (m == "Mar"){
        return 3;
    } else if (m == "Abr"){
        return 4;
    } else if (m == "May"){
        return 5;
    } else if (m == "Jun"){
        return 6;
    } else if (m == "Jul"){
        return 7;
    } else if (m == "Ago"){
        return 8;
    } else if (m == "Sep"){
        return 9;
    } else if (m == "Oct"){
        return 10;
    } else if (m == "Nov"){
        return 11;
    } else if (m == "Dic"){
        return 12;
    }
    return 0;
}

void pause(){
    cout << "Press enter to continue.";
    cin.ignore();
    cin.get();
}

void loadLogEntryData(const string& filename, DoublyLinkedList& list, int n = 50, bool print = false) {
    ifstream file(filename);
    string line;
    int i = 0;

    while (getline(file, line) && i < n) {
        stringstream ss(line);
        string s, min, hr, day, month, ip1, ip2, ip3, ip4, port, reason;

        getline(ss, month, ' ');
        getline(ss, day, ' ');
        getline(ss, hr, ':');
        getline(ss, min, ':');
        getline(ss, s, ' ');
        getline(ss, ip1, '.');
        getline(ss, ip2, '.');
        getline(ss, ip3, '.');
        getline(ss, ip4, ' ');
        // getline(ss, port, ' ');
        getline(ss, reason);
        if (print){
            cout << "month: " << month << " " << endl
            << "day: " << day << " " << endl
            << "hour: " << hr << " " << endl
            << "minute: " << min << " " << endl
            << "second: " << s << " " << endl
            << "ip1: " << ip1 << " " << endl
            << "ip2: " << ip2 << " " << endl
            << "ip3: " << ip3 << " " << endl
            << "ip4: " << ip4 << " " << endl
            << "port: " << port << " " << endl
            << "reason: " << reason << endl;
        }
        
        int _ip = stoi(ip1) * 255 * 255 * 255 + stoi(ip2) * 255 * 255 + stoi(ip3) * 255 + stoi(ip4);
        int _s = stoi(s);
        int _min = stoi(min);
        int _hr = stoi(hr);
        int _day = stoi(day);
        int _month = monthToInt(month);
        // int _port = stoi(port);
        ++i;
        list.insertLast(LogEntry(_s, _min, _hr, _day, _month, _ip, reason));
    }

    file.close();
}

// convierte una ip en string a entero
int ipToInt(const string& ip) {
    stringstream ss(ip);
    string ip1, ip2, ip3, ip4;

    getline(ss, ip1, '.');
    getline(ss, ip2, '.');
    getline(ss, ip3, '.');
    getline(ss, ip4, '.');

    return stoi(ip1) * 255 * 255 * 255 + stoi(ip2) * 255 * 255 + stoi(ip3) * 255 + stoi(ip4);
}

// imprime los registros dentro de un rango de ips
void printIPRange(DoublyLinkedList* list, int initialIP, int finalIP) {
    Node* current = list->getHead();

    while (current != nullptr) {
        if (current->value.getIp() >= initialIP && current->value.getIp() <= finalIP) {
            cout << current->value << endl;
        }
        current = current->next;
    }
}

// guarda una lista en un archivo de texto
void saveToFile(DoublyLinkedList* list, const string& filename) {
    ofstream file(filename);
    Node* current = list->getHead();

    while (current != nullptr) {
        file << current->value << endl;
        current = current->next;
    }

    file.close();
}




int main(){
    // cantidad maxima de registros a cargar del archivo
    const int n = 2846;
    // ip inicial y final para buscar en la lista
    string initialIPString, finalIPString;
    int initialIP, finalIP;

    // lista doblemente ligada donde se guardaran los logs
    DoublyLinkedList logsList;

    // loadLogEntryData usa una referencia, por eso se pasa la lista directamente
    // porque la funcion modifica la lista original sin hacer una copia
    loadLogEntryData("bitacora_noviembre.txt", logsList, n);

    // imprime la lista original en el orden en que fue leida
    // logsList.printForward();

    // quickSortStack usa un puntero, por eso se pasa la direccion de la lista
    // porque la funcion espera la ubicacion de la lista en memoria
    DoublyLinkedList* sortedList = quickSortStack(&logsList);

    // solicita al usuario la ip inicial del rango
    cout << "Ingresa la IP inicial: ";
    cin >> initialIPString;

    // solicita al usuario la ip final del rango
    cout << "Ingresa la IP final: ";
    cin >> finalIPString;

    // convierte las ips del usuario a enteros para compararlas
    initialIP = ipToInt(initialIPString);
    finalIP = ipToInt(finalIPString);

    // acomoda el rango si el usuario lo dio al reves
    if (initialIP > finalIP) {
        swap(initialIP, finalIP);
    }

    // imprime los registros que estan dentro del rango dado
    printIPRange(sortedList, initialIP, finalIP);

    // guarda el resultado del ordenamiento en un archivo
    saveToFile(sortedList, "resultado.txt");

    return 0;
}
