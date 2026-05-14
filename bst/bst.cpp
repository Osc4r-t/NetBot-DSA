#include <iostream>
using namespace std;

// nodo del arbol binario de busqueda
class Node {
public:
    // valor almacenado
    int data;
    // hijo izquierdo
    Node* left;
    // hijo derecho
    Node* right;

    // crea un nodo sin hijos
    // complejidad: O(1)
    Node(int _data) : data(_data), left(nullptr), right(nullptr) {}

    // limpia los apuntadores del nodo
    // complejidad: O(1)
    ~Node() {
        left = nullptr;
        right = nullptr;
    }
};

class BST {
    private:
    Node* root;

    // inserta un valor en la posicion correcta del arbol
    // complejidad: O(h), donde h es la altura del arbol
    Node* insert(Node* node, int value){
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
        }
        // si es igual, no inserta duplicados
        return node;
    }

    // busca un valor siguiendo la regla del BST
    // complejidad: O(h), donde h es la altura del arbol
    bool search(Node* node, int value){
        // si llega a vacio, el valor no existe
        if (node == nullptr){
            return false;
        }
        // si encuentra el valor, termina
        if (value == node->data){
            return true;
        }
        // si es menor, busca por la izquierda
        if (value < node->data) {
            return search(node->left,value);
        // si es mayor, busca por la derecha
        } else {
            return search(node->right,value);
        }

    }

    // elimina un nodo y reacomoda el arbol
    // complejidad: O(h), donde h es la altura del arbol
    Node* remove(Node* node, int value){
        // si llega a vacio, no hay nada que borrar
        if (node == nullptr){
            return nullptr;
        }

        // si el valor es menor, sigue por la izquierda
        if (value < node->data) {
            return remove(node->left,value);
        // si el valor es mayor, sigue por la derecha
        } else if (value > node->data) {
            return remove(node->right,value);
        }
        else {
            // si no tiene hijo izquierdo, sube el derecho
            if (node->left == nullptr) {
                Node* tmp = node->right;
                delete node; return tmp;
            }
            // si no tiene hijo derecho, sube el izquierdo
            if (node->right == nullptr) {
                Node* tmp = node->left;
                delete node; return tmp;
            }
            // si tiene dos hijos, toma el menor del subarbol derecho
            Node* succ = findMin(node->right);
            // copia el sucesor al nodo actual
            node->data = succ->data;
            // elimina el sucesor repetido del subarbol derecho
            node->right = remove(node->right, succ->data);
        }
        return node;
        

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

    // recorre raiz, izquierda y derecha
    // complejidad: O(n)
    void preorder(Node* node) {
        // si llega a vacio, termina ese camino
        if (node == nullptr){
            return;
        }
        // primero imprime la raiz
        cout << node->data << " ";
        // despues recorre izquierda y derecha
        preorder(node->left);
        preorder(node->right);
    }

    // recorre izquierda, derecha y raiz
    // complejidad: O(n)
    void postorder(Node* node) {
        // si llega a vacio, termina ese camino
        if (node == nullptr){
            return;
        }
        // primero recorre ambos subarboles
        postorder(node->left);
        postorder(node->right);
        // al final imprime la raiz
        cout << node->data << " ";
    }

    // findMin recorre todos los nodos izquierdos
    // hasta llegar al menor valor del subarbol
    // complejidad: O(h), donde h es la altura del arbol
    Node* findMin(Node* node){
        // sigue bajando mientras exista hijo izquierdo
        while(node->left != nullptr){
            node = node->left;
        }
        // devuelve el nodo con el valor minimo
        return node;
    }

    // findMax recorre todos los nodos derechos
    // hasta llegar al mayor valor del subarbol
    // complejidad: O(h), donde h es la altura del arbol
    Node* findMax(Node* node){
        // sigue bajando mientras exista hijo derecho
        while(node->right != nullptr){
            node = node->right;
        }
        // devuelve el nodo con el valor maximo
        return node;
    }
    int height(Node* node){
        if (node == nullptr){
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return 1 + (max(leftHeight,rightHeight));

    }

    // /////////////////////////////////////////////////////////////////////
    public:

    // crea un arbol vacio
    // complejidad: O(1)
    BST() : root(nullptr) {}

    // inserta el valor desde la raiz
    // complejidad: O(h), donde h es la altura del arbol
    void insert(int value){
        root = insert(root,value);
    };

    // busca el valor desde la raiz
    // complejidad: O(h), donde h es la altura del arbol
    bool search(int value){
        return search(root,value);
    }

    // elimina el valor desde la raiz
    // complejidad: O(h), donde h es la altura del arbol
    Node* remove(int value){
        return remove(root,value);
    }

    // imprime el arbol en inorder
    // complejidad: O(n)
    void inorder(){
        inorder(root);
    }

    // imprime el arbol en preorder
    // complejidad: O(n)
    void preorder(){
        preorder(root);
    }

    // imprime el arbol en postorder
    // complejidad: O(n)
    void postorder(){
        postorder(root);
    }

    // obtiene el minimo del arbol
    // complejidad: O(h), donde h es la altura del arbol
    Node* findMin(){
        return findMin(root);
    }

    // obtiene el maximo del arbol
    // complejidad: O(h), donde h es la altura del arbol
    Node* findMax(){
        return findMax(root);
    }

    int height(){
        return height(root);
    }

    int whatLevelAmI (int value){
        if (!search(value)){
            return -1;
        }
        Node* node = root;
        int i = 0;
        while (node->data != value){
            if (value < node->data){
                node = node->left;
            } else {
                node = node->right;
            }
            i++;
        }
        return i;
    }

    void ancestors(int value){
        if (!search(value)){
            cout << "No existe este valor!" << endl;
            return;
        }
        Node* node = root;
        while (node->data != value){
            if (value < node->data){
                cout << node->data << " ";
                node = node->left;
            } else {
                cout << node->data << " ";
                node = node->right;
            }
        }
    }
    
};

int main(){
    // crea el arbol de prueba
    BST myBst;

    // arreglo con valores de ejemplo
    const int n = 10;
    int A[n] = {5,7,4,8,10,3,6};
    // inserta los 7 valores en el arbol
    for (int i = 0; i < 7; i++){
        myBst.insert(A[i]);
    }

    // muestra el recorrido inorder
    cout << "inOrder";
    cout <<endl;
    myBst.inorder();
    cout <<endl;

    // muestra el recorrido preorder
    cout << "preOrder";
    cout <<endl;
    myBst.preorder();
    cout <<endl;

    // muestra el recorrido postorder
    cout << "postOrder";
    cout <<endl;
    myBst.postorder();
    cout <<endl;
    cout << "Ancestors";
    cout <<endl;
    myBst.ancestors(10);
    cout <<endl;
    cout << "What Level Am I?";
    cout <<endl;
    cout << myBst.whatLevelAmI(5) << endl;
    cout << myBst.whatLevelAmI(71)<< endl;
    cout << myBst.whatLevelAmI(33)<< endl;
    cout << myBst.whatLevelAmI(25)<< endl;
    cout << myBst.whatLevelAmI(1)<< endl;
    cout << myBst.whatLevelAmI(-1)<< endl;
    cout <<endl;
    cout << "Height";
    cout <<endl;
    cout << myBst.height();
}