#include <iostream>
using namespace std;
#include <random>

// nodo de la lista doble
class Node {
public:
    int value;
    Node* next;
    Node* prev;

    Node(const int& _value) : value(_value), next(nullptr), prev(nullptr) {}

    ~Node() {
        next = nullptr;
        prev = nullptr;
    }
};

// nodo para la pila de punteros
class StackNode {
public:
    Node* data;
    StackNode* next;

    StackNode(Node* _data) : data(_data), next(nullptr) {}
};

// stack que guarda punteros a nodos
class Stack {
private:
    StackNode* top;
    int count;

public:
    Stack() {
        top = nullptr;
        count = 0;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(Node* x) {
        StackNode* temp = new StackNode(x);
        temp->next = top;
        top = temp;
        count++;
    }

    Node* pop() {
        if (top == nullptr) {
            return nullptr;
        }

        StackNode* temp = top;
        top = top->next;
        Node* val = temp->data;
        delete temp;
        count--;
        return val;
    }

    Node* peek() {
        if (top == nullptr) {
            return nullptr;
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    int getSize() {
        return count;
    }
};

// clase de lista doblemente ligada
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

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

    void insertFirst(const int& value) {
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

    void insertLast(const int& value) {
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

    int getSize() {
        return size;
    }

    Node* getHead() {
        return head;
    }

    Node* getTail() {
        return tail;
    }

    void printForward() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->value << " -> ";
            current = current->next;
        }
        cout << "null" << endl;
    }
};

// intercambia solo los valores de dos nodos
void swapValues(Node* a, Node* b) {
    int temp = a->value;
    a->value = b->value;
    b->value = temp;
}

// partición estilo Lomuto para lista doble
Node* partition(Node* L, Node* R) {
    // el pivote sera el ultimo valor del rango actual
    int pivot = R->value;

    // i va marcando hasta donde llegan los elementos
    // que ya quedaron del lado izquierdo
    Node* i = nullptr;

    // j recorre el rango desde L hasta antes del pivote
    // cuando encuentra un valor menor o igual al pivote,
    // ese valor se manda al lado izquierdo
    for (Node* j = L; j != R; j = j->next) {
        if (j->value <= pivot) {
            if (i == nullptr) {
                // el primer valor que cumple se pone al inicio del rango
                i = L;
            } else {
                // los siguientes se van acomodando consecutivamente
                i = i->next;
            }
            swapValues(i, j);
        }
    }

    // al terminar, i avanza una posicion para señalar
    // donde debe quedar el pivote ya ordenado
    if (i == nullptr) {
        i = L;
    } else {
        i = i->next;
    }

    // se intercambia el pivote con esa posicion final
    swapValues(i, R);
    return i;
}

// quicksort completamente iterativo
void quickSortIterative(DoublyLinkedList& list) {
    // L y R son los extremos del rango inicial a ordenar
    Node* L = list.getHead();
    Node* R = list.getTail();

    // si la lista esta vacia o tiene un solo elemento, no hay nada que hacer
    if (L == nullptr || R == nullptr || L == R) {
        return;
    }

    // la pila reemplaza la recursion:
    // guarda pares de nodos que representan subrangos pendientes
    Stack P;

    P.push(L);
    P.push(R);

    // mientras haya subrangos pendientes, se siguen procesando
    while (!P.isEmpty()) {
        Node* right = P.pop();
        Node* left = P.pop();

        // si el rango no es valido, se omite
        if (left == nullptr || right == nullptr) {
            continue;
        }

        // si el rango tiene un solo elemento, ya esta ordenado
        if (left == right) {
            continue;
        }

        // evita procesar un rango invertido o vacio
        if (left == right->next) {
            continue;
        }

        // partition deja el pivote en su lugar final
        // y divide implicitamente el rango en izquierda y derecha
        Node* p = partition(left, right);

        // si existe una parte izquierda, se guarda para ordenarla despues
        if (p->prev != nullptr && left != p) {
            P.push(left);
            P.push(p->prev);
        }

        // si existe una parte derecha, se guarda para ordenarla despues
        if (p->next != nullptr && right != p) {
            P.push(p->next);
            P.push(right);
        }
    }
}

int main() {
    DoublyLinkedList list;

    // random_device rd;
    // mt19937 gen(rd());
    // uniform_int_distribution<> dist(1, 1000);

    // for (int i = 0; i < 10; i++) {
    //     list.insertLast(dist(gen));
    // }
    list.insertFirst(1);
    list.insertFirst(3);
    list.insertFirst(2);
    list.insertFirst(4);
    list.insertFirst(5);

    list.printForward();

    cout << "-------Sorting-------" << endl;

    quickSortIterative(list);

    list.printForward();

    return 0;
}
