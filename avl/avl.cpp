#include <algorithm>
#include <iostream>
using namespace std;

// nodo del arbol AVL
class Node {
public:
    // valor almacenado
    int data;
    // hijo izquierdo
    Node* left;
    // hijo derecho
    Node* right;
    // altura del nodo
    int height;

    // crea un nodo sin hijos
    // complejidad: O(1)
    Node(int _data) : data(_data), left(nullptr), right(nullptr), height(1) {}

    // limpia los apuntadores del nodo
    // complejidad: O(1)
    ~Node() {
        left = nullptr;
        right = nullptr;
    }
};

class AVL {
private:
    // raiz del arbol
    Node* root;
    // total de rotaciones hechas por el arbol
    int rotations;

    // obtiene la altura de un nodo
    // complejidad: O(1)
    int height(Node* node) {
        // si el nodo esta vacio, su altura es 0
        if (node == nullptr) {
            return 0;
        }
        // devuelve la altura guardada
        return node->height;
    }

    // actualiza la altura de un nodo
    // complejidad: O(1)
    void updateHeight(Node* node) {
        // calcula la altura usando sus hijos
        node->height = 1 + max(height(node->left), height(node->right));
    }

    // calcula derecha menos izquierda
    // complejidad: O(1)
    int balanceFactor(Node* node) {
        // si el nodo esta vacio, el factor es 0
        if (node == nullptr) {
            return 0;
        }
        // regresa altura derecha menos altura izquierda
        return height(node->right) - height(node->left);
    }

    // busca un nodo por su valor
    // complejidad: O(h), donde h es la altura del arbol
    Node* findNode(Node* node, int value) {
        // si llega a vacio, no existe
        if (node == nullptr) {
            return nullptr;
        }
        // si encuentra el valor, devuelve el nodo
        if (value == node->data) {
            return node;
        }
        // si es menor, busca por la izquierda
        if (value < node->data) {
            return findNode(node->left, value);
        }
        // si es mayor, busca por la derecha
        return findNode(node->right, value);
    }

    // hace una rotacion derecha
    // complejidad: O(1)
    Node* rightRotate(Node* y) {
        // guarda el hijo izquierdo
        Node* x = y->left;
        // guarda el subarbol que cambia de lugar
        Node* temp = x->right;

        // mueve la raiz del subarbol
        x->right = y;
        // conecta el subarbol temporal
        y->left = temp;

        // actualiza las alturas
        updateHeight(y);
        // actualiza la nueva raiz
        updateHeight(x);

        // cuenta la rotacion
        rotations++;
        // devuelve la nueva raiz
        return x;
    }

    // hace una rotacion izquierda
    // complejidad: O(1)
    Node* leftRotate(Node* x) {
        // guarda el hijo derecho
        Node* y = x->right;
        // guarda el subarbol que cambia de lugar
        Node* temp = y->left;

        // mueve la raiz del subarbol
        y->left = x;
        // conecta el subarbol temporal
        x->right = temp;

        // actualiza las alturas
        updateHeight(x);
        // actualiza la nueva raiz
        updateHeight(y);

        // cuenta la rotacion
        rotations++;
        // devuelve la nueva raiz
        return y;
    }

    // inserta un valor y mantiene el balance
    // complejidad: O(log n)
    Node* insert(Node* node, int value) {
        // si llego a un espacio vacio, crea el nodo
        if (node == nullptr) {
            return new Node(value);
        }
        // si el valor es menor, baja por la izquierda
        if (value < node->data) {
            node->left = insert(node->left, value);
        // si el valor es mayor, baja por la derecha
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        // si es igual, no inserta duplicados
        } else {
            return node;
        }

        // actualiza la altura del nodo
        updateHeight(node);
        // calcula el factor de balance
        int balance = balanceFactor(node);

        // caso derecha derecha
        if (balance > 1 && value > node->right->data) {
            return leftRotate(node);
        }
        // caso derecha izquierda
        if (balance > 1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        // caso izquierda izquierda
        if (balance < -1 && value < node->left->data) {
            return rightRotate(node);
        }
        // caso izquierda derecha
        if (balance < -1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // devuelve el nodo sin cambios extra
        return node;
    }

    // busca el menor valor de un subarbol
    // complejidad: O(h), donde h es la altura del arbol
    Node* findMin(Node* node) {
        // baja por la izquierda hasta el menor
        while (node->left != nullptr) {
            node = node->left;
        }
        // devuelve el nodo menor
        return node;
    }

    // elimina un valor y mantiene el balance
    // complejidad: O(log n)
    Node* remove(Node* node, int value) {
        // si llega a vacio, no hay nada que borrar
        if (node == nullptr) {
            return nullptr;
        }

        // si el valor es menor, sigue por la izquierda
        if (value < node->data) {
            node->left = remove(node->left, value);
        // si el valor es mayor, sigue por la derecha
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            // si tiene cero o un hijo
            if (node->left == nullptr || node->right == nullptr) {
                // guarda el hijo que existe
                Node* temp = node->left != nullptr ? node->left : node->right;
                // borra hoja
                if (temp == nullptr) {
                    delete node;
                    return nullptr;
                }
                // sube el unico hijo
                Node* old = node;
                node = temp;
                delete old;
            } else {
                // toma el menor del subarbol derecho
                Node* temp = findMin(node->right);
                // copia el valor
                node->data = temp->data;
                // borra el valor repetido
                node->right = remove(node->right, temp->data);
            }
        }

        // si el arbol quedo vacio, termina
        if (node == nullptr) {
            return nullptr;
        }

        // actualiza la altura
        updateHeight(node);
        // calcula el factor de balance
        int balance = balanceFactor(node);

        // caso derecha derecha
        if (balance > 1 && balanceFactor(node->right) >= 0) {
            return leftRotate(node);
        }
        // caso derecha izquierda
        if (balance > 1 && balanceFactor(node->right) < 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        // caso izquierda izquierda
        if (balance < -1 && balanceFactor(node->left) <= 0) {
            return rightRotate(node);
        }
        // caso izquierda derecha
        if (balance < -1 && balanceFactor(node->left) > 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // devuelve el nodo balanceado
        return node;
    }

    // busca un valor siguiendo la regla del AVL
    // complejidad: O(log n)
    bool search(Node* node, int value) {
        // si llega a vacio, el valor no existe
        if (node == nullptr) {
            return false;
        }
        // si encuentra el valor, termina
        if (value == node->data) {
            return true;
        }
        // si es menor, busca por la izquierda
        if (value < node->data) {
            return search(node->left, value);
        }
        // si es mayor, busca por la derecha
        return search(node->right, value);
    }

    // revisa si todos los nodos cumplen la regla AVL
    // complejidad: O(n)
    bool isAVL(Node* node) {
        // si llega a vacio, ese camino es valido
        if (node == nullptr) {
            return true;
        }
        // calcula el factor del nodo actual
        int balance = balanceFactor(node);
        // si el factor no esta entre -1 y 1, no es AVL
        if (balance < -1 || balance > 1) {
            return false;
        }
        // revisa los dos subarboles
        return isAVL(node->left) && isAVL(node->right);
    }

    // recorre izquierda, raiz y derecha
    // complejidad: O(n)
    void inorder(Node* node) {
        // si llega a vacio, termina ese camino
        if (node == nullptr) {
            return;
        }
        // visita primero el subarbol izquierdo
        inorder(node->left);
        // luego imprime la raiz
        cout << node->data << " ";
        // al final visita el subarbol derecho
        inorder(node->right);
    }

public:
    // crea un arbol vacio
    // complejidad: O(1)
    AVL() : root(nullptr), rotations(0) {}

    // inserta el valor desde la raiz
    // complejidad: O(log n)
    void insert(int value) {
        root = insert(root, value);
    }

    // elimina el valor desde la raiz
    // complejidad: O(log n)
    void remove(int value) {
        root = remove(root, value);
    }

    // busca el valor desde la raiz
    // complejidad: O(log n)
    bool search(int value) {
        return search(root, value);
    }

    // calcula el factor de balance de un valor
    // complejidad: O(log n)
    int getBalanceFactor(int value) {
        // si el arbol esta vacio, regresa 0
        if (root == nullptr) {
            return 0;
        }
        // busca el nodo solicitado
        Node* node = findNode(root, value);
        // si no existe, regresa centinela
        if (node == nullptr) {
            return -999;
        }
        // regresa derecha menos izquierda
        return balanceFactor(node);
    }

    // muestra y devuelve el total de rotaciones
    // complejidad: O(1)
    int countRotations() {
        // imprime el total acumulado
        cout << "Total de rotaciones: " << rotations << endl;
        // devuelve el total acumulado
        return rotations;
    }

    // revisa si todo el arbol cumple AVL
    // complejidad: O(n)
    bool isAVL() {
        return isAVL(root);
    }

    // imprime el arbol en inorder
    // complejidad: O(n)
    void inorder() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    AVL avl;

    // inserta valores de prueba
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    // imprime el recorrido inorder
    cout << "Inorder: ";
    avl.inorder();

    // muestra el factor de balance de un nodo
    cout << "Balance de 30: " << avl.getBalanceFactor(30) << endl;

    // muestra si el arbol cumple AVL
    cout << "Es AVL: " << (avl.isAVL() ? "true" : "false") << endl;

    // muestra el total de rotaciones
    avl.countRotations();

    return 0;
}
