#include <iostream>
using namespace std; 
#include <random>



// nodo de la lista doble
class Node {
public:
    // valor guardado en el nodo
    int value;
    // apuntador al siguiente nodo
    Node* next;
    // apuntador al nodo anterior
    Node* prev;

    // constructor del nodo
    Node(const int& _value) : value(_value), next(nullptr), prev(nullptr) {}

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
    void push(int x) {
        Node* temp = new Node(x);
        temp->next = top;
        top = temp;
        
        count++;
    }

    // pop operation
    int pop() {
        if (top == NULL) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        Node* temp = top;
        top = top->next;
        int val = temp->value;
        
        count--;
        delete temp;
        return val;
    }

    // peek operation
    int peek() {
        if (top == NULL) {
            cout << "Stack is Empty" << endl;
            return -1;
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

    // inserta un valor al final
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

    // inserta un valor en una posicion especifica
    void insertAt(const int& value, int index, bool print = false) {
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
            if (print) {
                cout << "Invalid index: " << index << ". Valid range is 0 to " << size - 1 << "." << endl;
            }
            return;
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
    bool find(const int& value) {
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
    int getAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index: " << index << ". Valid range is 0 to " << size - 1 << "." << endl;
            return int();
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
    void updateAt(const int& value, int index, bool print = false) {
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
            cout << current->value << " -> ";
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
    int pivot = high->value;

    // Pointer to place smaller elements
    Node* i = low->prev;

    // Traverse the list to rearrange nodes
    for (Node* j = low; j != high; j = j->next) {
        
        // If current node's value is less than or 
        // equal to the pivot
        if (j->value <= pivot) {
            
            // Move i forward and swap with j
            i = (i == nullptr) ? low : i->next;
            swap(i, j);
        }
    }

    // Move i to the correct pivot position
    i = (i == nullptr) ? low : i->next;
  
    // Swap pivot with i's value
    swap(i, high);

    return i;
}

// funcion auxiliar para convertir pilas a DLL's
DoublyLinkedList* stackToDLL(Stack* stack){
    DoublyLinkedList* list = new DoublyLinkedList();
    while(!stack->isEmpty()){
        int value = stack->pop();
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
        int pivot = high->value;

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

int main(){
    // se crea una mini DLL
    DoublyLinkedList* list = new DoublyLinkedList();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000);

    for (int i = 0; i < 100; i++) {
        list->insertLast(dist(gen));
    }


    list->printForward();
    // list->printBackward();

    cout << "-------Sorting-------" <<endl;
    list = quickSortStack(list);
    list->printForward();
}