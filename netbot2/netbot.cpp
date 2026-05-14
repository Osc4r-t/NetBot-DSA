#include "netbot.h"
#include <iostream>
#include <fstream>
#include <iomanip>
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


// nodo auxiliar para la pila usada por quicksort
class StackNode {
public:
    // puntero al nodo de la lista que se quiere guardar
    Node* data;
    // apuntador al siguiente nodo de la pila
    StackNode* next;

    // constructor del nodo auxiliar
    StackNode(Node* _data) : data(_data), next(nullptr) {}
};

// pila que guarda punteros a nodos de la lista doble
class Stack {
private:
    // nodo que queda en la parte superior de la pila
    StackNode* top;
    // cantidad de elementos almacenados
    int count;

public:
    // constructor de la pila
    Stack() : top(nullptr), count(0) {}

    // destructor de la pila
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // inserta un puntero a nodo en la pila
    void push(Node* x) {
        StackNode* temp = new StackNode(x);
        temp->next = top;
        top = temp;
        count++;
    }

    // elimina y devuelve el elemento superior
    Node* pop() {
        if (isEmpty()) {
            return nullptr;
        }

        StackNode* temp = top;
        top = top->next;
        Node* value = temp->data;
        delete temp;
        count--;
        return value;
    }

    // devuelve el elemento superior sin eliminarlo
    Node* peek() {
        if (isEmpty()) {
            return nullptr;
        }
        return top->data;
    }

    // indica si la pila esta vacia
    bool isEmpty() {
        return top == nullptr;
    }

    // devuelve el tamaño actual de la pila
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



// intercambia solamente los valores entre dos nodos
void swapValues(Node* a, Node* b) {
    LogEntry temp = a->value;
    a->value = b->value;
    b->value = temp;
}

// particion estilo Lomuto para lista doblemente ligada
Node* partition(Node* low, Node* high) {
    // se toma como pivote el ultimo nodo del rango actual
    LogEntry pivot = high->value;

    // i marca la frontera entre:
    // 1. los elementos que ya quedaron acomodados a la izquierda
    // 2. los elementos que aun no se han acomodado
    // empieza en nullptr porque todavia no se ha encontrado ningun valor
    // menor o igual al pivote dentro del rango
    Node* i = nullptr;

    // j recorre todo el rango desde low hasta el nodo anterior a high
    // cada vez que encuentra un elemento menor o igual al pivote:
    // 1. avanza i a la siguiente posicion disponible de la parte izquierda
    // 2. intercambia el valor de j con el de i
    // asi, todos los menores o iguales al pivote van quedando al inicio
    for (Node* j = low; j != high; j = j->next) {
        // si el valor actual es menor o igual al pivote, se manda a la izquierda
        if (j->value <= pivot) {
            if (i == nullptr) {
                // el primer elemento menor o igual al pivote debe quedar
                // exactamente al inicio del rango
                i = low;
            } else {
                // los siguientes menores o iguales se colocan despues del anterior
                i = i->next;
            }
            swapValues(i, j);
        }
    }

    // al terminar el recorrido, i debe avanzar una posicion mas:
    // ahi es donde debe colocarse el pivote para que:
    // a la izquierda queden los menores o iguales
    // y a la derecha queden los mayores
    if (i == nullptr) {
        // si nunca hubo elementos menores o iguales, el pivote va al inicio
        i = low;
    } else {
        // si si hubo, el pivote va justo despues del ultimo acomodado
        i = i->next;
    }

    // se coloca el pivote en su sitio correcto
    // despues de este swap, i apunta a la posicion definitiva del pivote
    swapValues(i, high);
    return i;
}

// quicksort completamente iterativo para la lista doble
void quickSortIterative(DoublyLinkedList& list) {
    // definir cabeza y cola de la lista completa
    Node* low = list.getHead();
    Node* high = list.getTail();

    // no hace nada si la lista esta vacia o tiene un solo elemento
    if (low == nullptr || high == nullptr || low == high) {
        return;
    }

    // pila auxiliar donde se guardan pares de limites: izquierda y derecha
    // cada par representa un subrango de la lista que aun falta ordenar
    Stack pendingRanges;
    pendingRanges.push(low);
    pendingRanges.push(high);

    // se sigue procesando mientras existan rangos pendientes por ordenar
    // esto reemplaza las llamadas recursivas de quicksort tradicional
    while (!pendingRanges.isEmpty()) {
        // primero sale el extremo derecho y despues el izquierdo
        Node* right = pendingRanges.pop();
        Node* left = pendingRanges.pop();

        // si el rango no es valido, se ignora
        if (left == nullptr || right == nullptr) {
            continue;
        }

        // si el rango ya esta ordenado por tener un solo nodo, se salta
        if (left == right) {
            continue;
        }

        // este caso evita intentar ordenar un rango invertido
        if (left == right->next) {
            continue;
        }

        // se particiona el rango actual:
        // 1. partition mueve menores o iguales a la izquierda
        // 2. deja el pivote en su posicion final
        // 3. regresa un apuntador a ese pivote ya acomodado
        Node* pivot = partition(left, right);

        // si hay elementos a la izquierda del pivote, se agrega ese subarreglo
        // a la pila para ordenarlo despues
        if (pivot->prev != nullptr && left != pivot) {
            pendingRanges.push(left);
            pendingRanges.push(pivot->prev);
        }

        // si hay elementos a la derecha del pivote, se agrega ese subarreglo
        // a la pila para ordenarlo despues
        if (pivot->next != nullptr && right != pivot) {
            pendingRanges.push(pivot->next);
            pendingRanges.push(right);
        }
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
        
        int _ip = stoi(ip1) * 256 * 256 * 256 + stoi(ip2) * 256 * 256 + stoi(ip3) * 256 + stoi(ip4);
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

    return stoi(ip1) * 256 * 256 * 256 + stoi(ip2) * 256 * 256 + stoi(ip3) * 256 + stoi(ip4);
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

// guarda en archivo los registros que caen dentro de un rango de ips
void saveIPRangeToFile(DoublyLinkedList* list, int initialIP, int finalIP, const string& filename) {
    ofstream file(filename);
    Node* current = list->getHead();

    while (current != nullptr) {
        if (current->value.getIp() >= initialIP && current->value.getIp() <= finalIP) {
            file << current->value << endl;
        }
        current = current->next;
    }

    file.close();
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

// convierte una ip entera al formato con puntos para mostrar resultados
string intToIpString(int ip) {
    int ip1 = abs(ip / (256 * 256 * 256));
    int ip2 = abs((ip / (256 * 256)) % 256);
    int ip3 = abs((ip / 256) % 256);
    int ip4 = abs(ip % 256);

    return to_string(ip1) + "." + to_string(ip2) + "." +
           to_string(ip3) + "." + to_string(ip4);
}

// cuenta cuantas ips unicas hay recorriendo la lista ya ordenada por ip
int countUniqueIPs(DoublyLinkedList* list) {
    Node* current = list->getHead();

    if (current == nullptr) {
        return 0;
    }

    int uniqueIPs = 0;

    while (current != nullptr) {
        int currentIP = current->value.getIp();
        uniqueIPs++;

        // avanza mientras sigan apareciendo registros de la misma ip
        while (current != nullptr && current->value.getIp() == currentIP) {
            current = current->next;
        }
    }

    return uniqueIPs;
}

// calcula el promedio de intentos por ip
double averageAttemptsPerIP(DoublyLinkedList* list) {
    int uniqueIPs = countUniqueIPs(list);

    if (uniqueIPs == 0) {
        return 0.0;
    }

    return static_cast<double>(list->getSize()) / uniqueIPs;
}

// cuenta cuantas ips tienen mas de cierta cantidad de intentos
int countIPsOverThreshold(DoublyLinkedList* list, int threshold) {
    Node* current = list->getHead();
    int total = 0;

    while (current != nullptr) {
        int currentIP = current->value.getIp();
        int attempts = 0;

        // cuenta cuantas veces aparece la misma ip de forma consecutiva
        while (current != nullptr && current->value.getIp() == currentIP) {
            attempts++;
            current = current->next;
        }

        if (attempts > threshold) {
            total++;
        }
    }

    return total;
}

// imprime las top n ips con mas intentos
void printTopNIPs(DoublyLinkedList* list, int n = 5) {
    int topIPs[5] = {0, 0, 0, 0, 0};
    int topCounts[5] = {0, 0, 0, 0, 0};
    Node* current = list->getHead();

    while (current != nullptr) {
        int currentIP = current->value.getIp();
        int attempts = 0;

        // como la lista ya esta ordenada, todas las repeticiones quedan juntas
        while (current != nullptr && current->value.getIp() == currentIP) {
            attempts++;
            current = current->next;
        }

        // inserta la ip en la posicion correcta del top si supera alguno actual
        for (int i = 0; i < n; i++) {
            if (attempts > topCounts[i]) {
                for (int j = n - 1; j > i; j--) {
                    topCounts[j] = topCounts[j - 1];
                    topIPs[j] = topIPs[j - 1];
                }
                topCounts[i] = attempts;
                topIPs[i] = currentIP;
                break;
            }
        }
    }

    cout << "Top " << n << " IPs con mas intentos:" << endl;
    for (int i = 0; i < n; i++) {
        if (topCounts[i] > 0) {
            cout << i + 1 << ". " << intToIpString(topIPs[i])
                 << " con " << topCounts[i] << " intentos" << endl;
        }
    }
}

// imprime el reporte completo de heavy hitters
void printHeavyHitterReport(DoublyLinkedList* list) {
    int uniqueIPs = countUniqueIPs(list);
    double average = averageAttemptsPerIP(list);
    int over10 = countIPsOverThreshold(list, 10);
    int over20 = countIPsOverThreshold(list, 20);

    cout << endl;
    cout << "========== REPORTE DE HEAVY HITTERS ==========" << endl;
    cout << "Total de registros: " << list->getSize() << endl;
    cout << "IPs unicas: " << uniqueIPs << endl;
    cout << fixed << setprecision(2);
    cout << "Promedio de intentos por IP: " << average << endl;
    printTopNIPs(list, 5);
    cout << "IPs con mas de 10 intentos: " << over10 << endl;
    cout << "IPs con mas de 20 intentos: " << over20 << endl;
    cout << "Diferencia con la fase 1: ahora una misma IP puede repetirse varias veces," << endl;
    cout << "lo que permite detectar heavy hitters y priorizar las IPs mas agresivas." << endl;
    cout << "==============================================" << endl;
    cout << endl;
}




int main(){
    // cantidad maxima de registros a cargar del archivo
    const int n = 10000;
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

    // se ordena la misma lista con quicksort iterativo, como en la carpeta quicksort
    quickSortIterative(logsList);

    // genera el reporte de actividad por ip usando la lista ya ordenada
    printHeavyHitterReport(&logsList);

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
    printIPRange(&logsList, initialIP, finalIP);

    // guarda toda la lista ordenada en un archivo
    saveToFile(&logsList, "ordenado.txt");

    // guarda los resultados de la busqueda por rango en otro archivo
    saveIPRangeToFile(&logsList, initialIP, finalIP, "busqueda.txt");

    cout << endl;
    cout << "Se guardo la lista completa ordenada en ordenado.txt" << endl;
    cout << "Se guardo la busqueda por rango en busqueda.txt" << endl;

    return 0;
}
