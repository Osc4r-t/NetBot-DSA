#include <iostream>
using namespace std;

// clase de nodo para la lista
class Node {
    // publicos para poder acceder a ellos desde el linked list
    public: 
    int value;
    Node* next;

    // constructor
    Node(int _value){
        value = _value;
        next = nullptr;
    }


    // destructor
    ~Node(){
        next = nullptr;
    }

};

// lista enlazada
class LinkedList{
    private:
    Node* head;
    int size;


    public:
    // constructor
    LinkedList(){
        head = nullptr;
        size = 0;
    }
    // destructor 
    // complejidad O(n) porque se recorre toda la lista para eliminar cada nodo
    ~LinkedList(){
        Node* current = head;
        while(current != nullptr){
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    // inserciones
    // complejidad O(1) porque solo se modifica el head y el nuevo nodo apunta al antiguo head
    void insertFirst(int value){
        Node* auxNode = new Node(value);
        auxNode->next = head;
        head = auxNode;
        size++;
    }
    // complejidad O(n) porque se recorre toda la lista para llegar al final y agregar el nuevo nodo
    void insertLast(int value){
        if (head == nullptr){
            insertFirst(value);
            return;
        }

        Node* current = head;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = new Node(value);
        size++;
    }

    // complejidad O(n) porque se recorre la lista hasta el indice para insertar el nuevo nodo
    void insertAt(int value, int index, bool print = false){
        if (index < 0 || index >= size){
            if (print){
                cout << "Invalid index: " << index << ". Valid range is 0 to " << size - 1 << "." << endl;
            }
            return;
        }
        if (index == 0){
            insertFirst(value);
            return;
        }
        Node* current = head;
        int i = 0;
        while(i < index){
            current = current->next;
            i++;
        }
        if (print){
            cout << "Inserting node with value: " << value << " at index: " << index << endl;
        }
        Node* auxNode = new Node(value);
        auxNode->next = current->next;
        current->next = auxNode;
        size++;
    }

    // eliminaciones
    // complejidad O(1) porque solo se modifica el head y el nodo eliminado es el antiguo head
    void deleteFirst(){
        if (head == nullptr){
            return;
        }
        Node* auxNode = head;
        
        head = head->next;
        delete auxNode;
        size--;
    }
    // complejidad O(n) porque se recorre toda la lista para llegar al final y eliminar el ultimo nodo
    void deleteLast(bool print = false){
        if (head == nullptr){
            return;
        } 
        if (head->next == nullptr){
            deleteFirst();
            return;
        }
        if (print){
            cout << "Deleting last node with value: " << head->value << endl;
        }
        Node* current = head;
        while(current->next->next != nullptr){
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
        size--;
    }

    // complejidad O(n) porque se recorre la lista hasta el indice para eliminar el nodo en ese indice
    void deleteAt(int index, bool print = false){
        if (index < 0 || index >= size){
            if (print){
                cout << "Invalid index: " << index << ". Valid range is 0 to " << size - 1 << "." << endl;
            }
            return;
        }

        if (index == 0){
            deleteFirst();
            return;
        }
        Node* current = head;
        int i = index-1;
        while(i > 0){
            current = current->next;
            i--;
        }
        if (print){
            int value = current->next->value;
            cout << "Deleting node at index: " << index << " with value: " << value << endl;
        }

        Node* next = current->next->next;
        delete current->next;
        current->next = next;
        
        size--;
    }

    // busqueda
    // complejidad O(n) porque se recorre toda la lista para encontrar el valor buscado
    bool find(int value){
        Node* current = head;
        while(current != nullptr) {
            if (current->value == value){
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // obtener valor en indice
    // complejidad O(n) porque se recorre la lista hasta el indice para obtener el valor en ese indice
    int getAt(int index){
        if (index < 0 || index >= size){
            cout << "Invalid index: " << index << ". Valid range is 0 to " << size - 1 << "." << endl;
            return -1; // Return -1 to indicate an error
        }
        Node* current = head;
        int i = index;
        while(i > 0){
            current = current->next;
            i--;
        }
        return current->value;
    }
    // complejidad O(n) porque se recorre la lista hasta el indice para actualizar el valor en ese indice
    void updateAt(int value, int index, bool print = false){
        if (index < 0 || index >= size){
            cout << "Invalid index: " << index << ". Valid range is 0 to " << size - 1 << "." << endl;
            return; // Return -1 to indicate an error
        }
        Node* current = head;
        int i = index;
        while(i > 0){
            current = current->next;
            i--;
        }
        if (print){
            cout << "Updating node at index: " << index << " from value: " << current->value << " to value: " << value << endl;
        }
        current->value = value;

    }

    // obtener tamaño
    // complejidad O(1) porque se mantiene un contador de tamaño que se actualiza en cada inserción y eliminación
    int getSize(){
        return size;
    }

    // imprimir
    // complejidad O(n) porque se recorre toda la lista para imprimir cada nodo
    void printList(Node* node = nullptr, bool text = false){
        // si se pasa un nodo, imprimir desde ese nodo, sino imprimir desde el head
        Node* current = node ? node : head;
        while(current != nullptr){
            if (text){
                cout << char(current->value + 64) << " -> ";
            } else {
                cout << current->value << " -> ";
            }
            current = current->next;
        }
        cout << "nullptr" << endl;
    }

    // cambiar el orden de la lista
    // complejidad O(n) porque se recorre toda la lista para cambiar el orden de cada nodo
    void reverse(bool print = false, bool text = false){
        Node* prev = nullptr;
        Node* current = head;
        Node* auxNext = nullptr;
        if (print){
            cout << "Starting list reversal..." << endl;
        }
        while(current != nullptr){
            auxNext = current->next;
            current-> next = prev;
            prev = current;
            current = auxNext;
            if (print){
                cout << "Prev list:";
                printList(prev, text);
                cout << "Current list:";
                printList(current, text);
                cout << endl;
            }
        }
        head = prev;
    }
};

// uso de la linked list
int main(){
    LinkedList list;
    list.insertFirst(1);
    list.insertLast(2);
    list.insertAt(3, 2);
    list.deleteAt(4,true);
    list.deleteAt(2,true);
    list.insertAt(3,1);
    list.printList(nullptr, true);
    list.insertLast(4);
    list.insertLast(5);
    list.insertAt(4, 8);
    list.printList(nullptr, true);
    list.reverse(true, true);
    list.printList(nullptr, true);
    return 0;
}