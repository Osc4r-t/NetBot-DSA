#include "netbot.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Node {
public:
    LogEntry value;
    Node* next;
    Node* prev;

    Node(const LogEntry& _value) : value(_value), next(nullptr), prev(nullptr) {}

    ~Node() {
        next = nullptr;
        prev = nullptr;
    }
};

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

    LogEntry getAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index: " << index << ". Valid range is 0 to " << size - 1 << "." << endl;
            return LogEntry();
        }

        Node* current = head;
        int i = 0;
        while (i < index) {
            current = current->next;
            i++;
        }

        return current->value;
    }

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

    int getSize() {
        return size;
    }

    void printForward() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->value << endl;
            current = current->next;
        }
    }

    void printBackward() {
        Node* current = tail;
        while (current != nullptr) {
            cout << current->value << endl;
            current = current->prev;
        }
    }
};

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

void loadLogEntryData(const string& filename, DoublyLinkedList& list) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string s, min, hr, day, month, ip, port, reason;

        getline(ss, month, ' ');
        getline(ss, day, ' ');
        getline(ss, hr, ':');
        getline(ss, min, ':');
        getline(ss, s, ' ');
        getline(ss, ip, ':');
        getline(ss, port, ' ');
        getline(ss, reason);

        int _s = stoi(s);
        int _min = stoi(min);
        int _hr = stoi(hr);
        int _day = stoi(day);
        int _month = monthToInt(month);
        int _port = stoi(port);

        list.insertLast(LogEntry(_s, _min, _hr, _day, _month, _port, ip, reason));
    }

    file.close();
}

void loadLogEntryData(const string& filename, LogEntry** out, int capacity, int &loaded) {
    ifstream file(filename);
    string line;
    int i = 0;

    while (i < capacity && getline(file, line)){
        stringstream ss(line);
        string s, min, hr, day, month, ip, port, reason;

        // obtiene cada elemento del log
        getline(ss, month,' ');
        getline(ss, day,' ');
        getline(ss, hr, ':');
        getline(ss, min, ':');
        getline(ss, s,' ');
        getline(ss, ip, ':');
        getline(ss, port,' ');
        getline(ss, reason);

        // convierte strings a numeros
        int _s   = stoi(s);
        int _min = stoi(min);
        int _hr  = stoi(hr);
        int _day = stoi(day);
        int _month = monthToInt(month);
        int _port = stoi(port);

        // crea y guarda puntero
        out[i] = new LogEntry(_s,_min,_hr,_day,_month,_port,ip,reason);
        ++i;
    }

    file.close();
    loaded = i;

    // inicializa el resto a nullptr
    for (int j = loaded; j < capacity; ++j) out[j] = nullptr;
}

int main(){

    const int n = 3350;       // capacidad
    LogEntry* _orders[n];         // arreglo de PUNTEROS a LogEntry
    int loaded = 0;            // cuántos cargamos
    DoublyLinkedList logList;

    loadLogEntryData("bitacora_junio.txt", _orders, 50, loaded);
    loadLogEntryData("bitacora_junio.txt", logList);

    cout << "Registros en la lista doble: " << logList.getSize() << endl;

    return 0;
}
