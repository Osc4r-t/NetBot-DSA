#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Operacion Medianoche - Fase 3: Analisis con arboles BST.
// Nodo del arbol binario de busqueda.
// Guarda el par (numAccesos, IP). La llave de ordenamiento es numAccesos.
class BSTNode {
public:
    int numAccesos;
    string ip;
    BSTNode* left;
    BSTNode* right;

    // Complejidad: O(1).
    BSTNode(int _numAccesos, const string& _ip)
        : numAccesos(_numAccesos), ip(_ip), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    // Inserta por numero de accesos.
    // Si dos IPs tienen el mismo numero de accesos, se usa la IP como desempate
    // para no perder nodos con llaves repetidas.
    // Complejidad: O(h), donde h es la altura del arbol.
    BSTNode* insert(BSTNode* node, int numAccesos, const string& ip) {
        if (node == nullptr) {
            return new BSTNode(numAccesos, ip);
        }

        if (numAccesos < node->numAccesos ||
            (numAccesos == node->numAccesos && ip < node->ip)) {
            node->left = insert(node->left, numAccesos, ip);
        } else {
            node->right = insert(node->right, numAccesos, ip);
        }

        return node;
    }

    // Recorrido in-order inverso R-N-L: derecha, nodo, izquierda.
    // En un BST ordenado por numAccesos, esto visita primero los mayores
    // y permite extraer las IPs heavy hitters.
    // Complejidad: O(h + k), donde k es el limite de IPs a imprimir.
    void reverseInorder(BSTNode* node, int& printed, int limit) const {
        if (node == nullptr || printed >= limit) {
            return;
        }

        reverseInorder(node->right, printed, limit);

        if (printed < limit) {
            cout << printed + 1 << ". " << node->ip
                 << " - " << node->numAccesos << " accesos" << endl;
            printed++;
        }

        reverseInorder(node->left, printed, limit);
    }

    // Libera todos los nodos del arbol.
    // Complejidad: O(m), donde m es la cantidad de IPs unicas insertadas.
    void clear(BSTNode* node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    // Complejidad: O(1).
    BST() : root(nullptr) {}

    // Complejidad: O(m), donde m es la cantidad de IPs unicas insertadas.
    ~BST() {
        clear(root);
    }

    // Complejidad: O(h), donde h es la altura del arbol.
    void insert(int numAccesos, const string& ip) {
        root = insert(root, numAccesos, ip);
    }

    // Complejidad: O(h + k), donde k es el limite de IPs a imprimir.
    void printTop(int limit) const {
        int printed = 0;
        reverseInorder(root, printed, limit);

        if (printed == 0) {
            cout << "No hay IPs para mostrar." << endl;
        }
    }
};

// Extrae la IP de una linea con formato:
// Mes Dia Hora IP Mensaje...
// Complejidad: O(1) respecto al numero de registros.
bool extractIP(const string& line, string& ip) {
    string month, day, time;
    stringstream ss(line);

    return static_cast<bool>(ss >> month >> day >> time >> ip);
}

// resultado.txt ya esta ordenado por IP desde la Fase 2. Por eso las
// apariciones de la misma IP quedan juntas y se pueden contar en una sola
// pasada. Cada vez que cambia la IP se inserta el par (conteo, ip).
// Complejidad: O(n + m*h), donde n es el total de registros,
// m es la cantidad de IPs unicas y h es la altura del BST.
bool buildBSTFromResultFile(const string& filename, BST& tree, int& totalLogs, int& uniqueIPs) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: no se pudo abrir el archivo " << filename << endl;
        return false;
    }

    string line;
    string currentIP = "";
    int currentCount = 0;
    totalLogs = 0;
    uniqueIPs = 0;

    while (getline(file, line)) {
        string ip;

        if (!extractIP(line, ip)) {
            continue;
        }

        totalLogs++;

        if (currentIP == "") {
            currentIP = ip;
            currentCount = 1;
        } else if (ip == currentIP) {
            currentCount++;
        } else {
            tree.insert(currentCount, currentIP);
            uniqueIPs++;
            currentIP = ip;
            currentCount = 1;
        }
    }

    if (currentIP != "") {
        tree.insert(currentCount, currentIP);
        uniqueIPs++;
    }

    file.close();
    return true;
}

// Coordina la lectura, construccion del BST y reporte de heavy hitters.
// Complejidad: O(n + m*h + h + k).
int main() {
    BST accessTree;
    int totalLogs = 0;
    int uniqueIPs = 0;

    if (!buildBSTFromResultFile("resultado.txt", accessTree, totalLogs, uniqueIPs)) {
        return 1;
    }

    cout << "Operacion Medianoche - Fase 3: Analisis con BST" << endl;
    cout << "Archivo leido: resultado.txt" << endl;
    cout << "Total de registros: " << totalLogs << endl;
    cout << "Total de IPs unicas: " << uniqueIPs << endl;
    cout << endl;
    cout << "Top 5 IPs con mas accesos usando recorrido R-N-L:" << endl;
    accessTree.printTop(5);

    return 0;
}
