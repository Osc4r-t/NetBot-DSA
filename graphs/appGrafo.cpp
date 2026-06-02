// Oscar Olivares
//Victor Sanchez
//Hania Rodriguez
// programa para representar un grafo con matriz y lista de adyacencia, y recorrerlo
// incluye la libreria para entrada y salida.
#include <iostream>
// incluye la libreria para usar queue.
#include <queue>
// incluye la libreria para usar vector.
#include <vector>
// usa el espacio de nombres estandar.
using namespace std;

/*
    descripcion: carga el grafo en matriz y lista.
    complejidad: tiempo o(n^2 + m), espacio o(n^2 + n + m).
*/
// declara la funcion para cargar el grafo.
void loadGraph(int n, int m, vector<vector<int> >& matriz, vector<vector<int> >& lista) {
    // limpia la matriz.
    matriz.clear();
    // limpia la lista.
    lista.clear();
    // cambia el tamano de la matriz.
    matriz.resize(n);
    // cambia el tamano de la lista.
    lista.resize(n);

    // inicia un ciclo para los renglones.
    for (int i = 0; i < n; i++) {
        // cambia el tamano del renglon.
        matriz[i].resize(n);
        // inicia un ciclo para las columnas.
        for (int j = 0; j < n; j++) {
            // pone cero en la matriz.
            matriz[i][j] = 0;
        // cierra el ciclo de columnas.
        }
    // cierra el ciclo de renglones.
    }

    // declara el vertice de origen.
    int origen;
    // declara el vertice de destino.
    int destino;

    // inicia un ciclo para leer los arcos.
    for (int i = 0; i < m; i++) {
        // muestra el numero de arco.
        cout << "arco " << i + 1 << endl;
        // pide el vertice origen.
        cout << "vertice origen (0 a " << n - 1 << "): ";
        // lee el vertice origen.
        cin >> origen;
        // pide el vertice destino.
        cout << "vertice destino (0 a " << n - 1 << "): ";
        // lee el vertice destino.
        cin >> destino;

        // repite si el arco no es valido.
        while (origen < 0 || origen >= n || destino < 0 || destino >= n) {
            // muestra un mensaje de error.
            cout << "arco invalido." << endl;
            // muestra el rango valido.
            cout << "los vertices deben estar entre 0 y " << n - 1 << endl;
            // pide el origen otra vez.
            cout << "vertice origen (0 a " << n - 1 << "): ";
            // lee el origen otra vez.
            cin >> origen;
            // pide el destino otra vez.
            cout << "vertice destino (0 a " << n - 1 << "): ";
            // lee el destino otra vez.
            cin >> destino;
        // cierra el ciclo de validacion.
        }

        // guarda el arco en la matriz.
        matriz[origen][destino] = 1;
        // guarda el arco en la lista.
        lista[origen].push_back(destino);
    // cierra el ciclo de arcos.
    }
// cierra la funcion loadGraph.
}

/*
    descripcion: carga un grafo de ejemplo ya definido.
    complejidad: tiempo o(n^2 + m), espacio o(n^2 + n + m).
*/
// declara la funcion para cargar el ejemplo.
void cargarEjemplo(int& n, int& m, vector<vector<int> >& matriz, vector<vector<int> >& lista) {
    // guarda la cantidad de vertices del ejemplo.
    n = 5;
    // guarda la cantidad de arcos del ejemplo.
    m = 6;
    // limpia la matriz.
    matriz.clear();
    // limpia la lista.
    lista.clear();
    // cambia el tamano de la matriz.
    matriz.resize(n);
    // cambia el tamano de la lista.
    lista.resize(n);

    // inicia un ciclo para los renglones.
    for (int i = 0; i < n; i++) {
        // cambia el tamano del renglon.
        matriz[i].resize(n);
        // inicia un ciclo para las columnas.
        for (int j = 0; j < n; j++) {
            // pone cero en la matriz.
            matriz[i][j] = 0;
        // cierra el ciclo de columnas.
        }
    // cierra el ciclo de renglones.
    }

    // crea los origenes del ejemplo.
    int origenes[6] = {0, 0, 1, 2, 3, 1};
    // crea los destinos del ejemplo.
    int destinos[6] = {1, 2, 3, 3, 4, 4};

    // inicia un ciclo para cargar los arcos del ejemplo.
    for (int i = 0; i < m; i++) {
        // guarda el origen actual.
        int origen = origenes[i];
        // guarda el destino actual.
        int destino = destinos[i];
        // guarda el arco en la matriz.
        matriz[origen][destino] = 1;
        // guarda el arco en la lista.
        lista[origen].push_back(destino);
    // cierra el ciclo de arcos.
    }

    // muestra que se cargo el ejemplo.
    cout << "se cargo el grafo de ejemplo." << endl;
    // muestra los arcos del ejemplo.
    cout << "arcos: 0->1, 0->2, 1->3, 2->3, 3->4, 1->4" << endl;
// cierra la funcion cargarEjemplo.
}

/*
    descripcion: recorre el grafo con dfs recursivo.
    complejidad: tiempo o(n^2), espacio o(n).
*/
// declara la funcion auxiliar de dfs.
void DFSRecursivo(vector<vector<int> >& matriz, vector<bool>& visitado, int n, int nodo) {
    // marca el nodo como visitado.
    visitado[nodo] = true;
    // imprime el nodo actual.
    cout << nodo << " ";

    // revisa todos los posibles vecinos.
    for (int vecino = 0; vecino < n; vecino++) {
        // revisa si hay arco y si no fue visitado.
        if (matriz[nodo][vecino] == 1 && !visitado[vecino]) {
            // visita el vecino con recursion.
            DFSRecursivo(matriz, visitado, n, vecino);
        // cierra la condicion.
        }
    // cierra el ciclo de vecinos.
    }
// cierra la funcion DFSRecursivo.
}

/*
    descripcion: imprime dfs desde un nodo inicial.
    complejidad: tiempo o(n^2), espacio o(n).
*/
// declara la funcion dfs.
void DFS(vector<vector<int> >& matriz, int n, int nodoInicial) {
    // revisa si el nodo inicial no existe.
    if (nodoInicial < 0 || nodoInicial >= n) {
        // muestra un mensaje de error.
        cout << "nodo inicial invalido para dfs." << endl;
        // termina la funcion.
        return;
    // cierra la condicion.
    }

    // crea el arreglo de visitados.
    vector<bool> visitado(n, false);
    // muestra el titulo del recorrido.
    cout << "recorrido dfs desde el nodo " << nodoInicial << ": ";
    // inicia el dfs recursivo.
    DFSRecursivo(matriz, visitado, n, nodoInicial);
    // baja una linea.
    cout << endl;
// cierra la funcion DFS.
}

/*
    descripcion: imprime bfs desde un nodo inicial.
    complejidad: tiempo o(n + m), espacio o(n).
*/
// declara la funcion bfs.
void BFS(vector<vector<int> >& lista, int nodoInicial) {
    // guarda la cantidad de vertices.
    int n = lista.size();
    // revisa si el nodo inicial no existe.
    if (nodoInicial < 0 || nodoInicial >= n) {
        // muestra un mensaje de error.
        cout << "nodo inicial invalido para bfs." << endl;
        // termina la funcion.
        return;
    // cierra la condicion.
    }

    // crea el arreglo de visitados.
    vector<bool> visitado(n, false);
    // crea la fila para bfs.
    queue<int> fila;
    // marca el nodo inicial como visitado.
    visitado[nodoInicial] = true;
    // mete el nodo inicial a la fila.
    fila.push(nodoInicial);
    // muestra el titulo del recorrido.
    cout << "recorrido bfs desde el nodo " << nodoInicial << ": ";

    // repite mientras la fila tenga datos.
    while (!fila.empty()) {
        // toma el primer nodo de la fila.
        int nodo = fila.front();
        // saca el primer nodo de la fila.
        fila.pop();
        // imprime el nodo actual.
        cout << nodo << " ";

        // recorre los vecinos del nodo.
        for (int i = 0; i < lista[nodo].size(); i++) {
            // guarda un vecino.
            int vecino = lista[nodo][i];
            // revisa si el vecino no fue visitado.
            if (!visitado[vecino]) {
                // marca el vecino como visitado.
                visitado[vecino] = true;
                // mete el vecino a la fila.
                fila.push(vecino);
            // cierra la condicion.
            }
        // cierra el ciclo de vecinos.
        }
    // cierra el ciclo de bfs.
    }

    // baja una linea.
    cout << endl;
// cierra la funcion BFS.
}

/*
    descripcion: imprime la matriz de adyacencia.
    complejidad: tiempo o(n^2), espacio o(1).
*/
// declara la funcion para imprimir la matriz.
void imprimirMatriz(vector<vector<int> >& matriz, int n) {
    // muestra el titulo de la matriz.
    cout << "matriz de adyacencia (" << n << "x" << n << "):" << endl;
    // imprime espacio para los encabezados.
    cout << "   ";
    // recorre los encabezados de columna.
    for (int j = 0; j < n; j++) {
        // imprime el numero de columna.
        cout << j << " ";
    // cierra el ciclo de encabezados.
    }
    // baja una linea.
    cout << endl;
    // imprime espacio para separar.
    cout << "   ";
    // recorre las columnas para imprimir guiones.
    for (int j = 0; j < n; j++) {
        // imprime un guion.
        cout << "- ";
    // cierra el ciclo de guiones.
    }
    // baja una linea.
    cout << endl;
    // recorre los renglones.
    for (int i = 0; i < n; i++) {
        // imprime el numero de renglon.
        cout << i << "| ";
        // recorre las columnas.
        for (int j = 0; j < n; j++) {
            // imprime un valor de la matriz.
            cout << matriz[i][j] << " ";
        // cierra el ciclo de columnas.
        }
        // baja una linea.
        cout << endl;
    // cierra el ciclo de renglones.
    }
// cierra la funcion imprimirMatriz.
}

/*
    descripcion: imprime la lista de adyacencia.
    complejidad: tiempo o(n + m), espacio o(1).
*/
// declara la funcion para imprimir la lista.
void imprimirLista(vector<vector<int> >& lista) {
    // muestra el titulo de la lista.
    cout << "lista de adyacencia:" << endl;
    // recorre cada vertice.
    for (int i = 0; i < lista.size(); i++) {
        // imprime el numero del vertice.
        cout << i << " -> ";
        // recorre los vecinos del vertice.
        for (int j = 0; j < lista[i].size(); j++) {
            // imprime un vecino.
            cout << lista[i][j];
            // revisa si todavia hay otro vecino.
            if (j + 1 < lista[i].size()) {
                // imprime una flecha entre vecinos.
                cout << " -> ";
            // cierra la condicion.
            }
        // cierra el ciclo de vecinos.
        }
        // marca el fin de la lista del vertice.
        cout << " /" << endl;
    // cierra el ciclo de vertices.
    }
// cierra la funcion imprimirLista.
}

/*
    descripcion: muestra matriz, lista, dfs y bfs.
    complejidad: tiempo o(n^2 + m), espacio o(n).
*/
// declara la funcion para mostrar resultados.
void mostrarResultados(vector<vector<int> >& matriz, vector<vector<int> >& lista, int n,
                       int nodoDFS, int nodoBFS) {
    // baja una linea.
    cout << endl;
    // imprime la matriz.
    imprimirMatriz(matriz, n);
    // baja una linea.
    cout << endl;
    // imprime la lista.
    imprimirLista(lista);
    // baja una linea.
    cout << endl;
    // ejecuta dfs.
    DFS(matriz, n, nodoDFS);
    // ejecuta bfs.
    BFS(lista, nodoBFS);
// cierra la funcion mostrarResultados.
}

/*
    descripcion: pide datos y muestra el grafo y recorridos.
    complejidad: tiempo o(n^2 + m), espacio o(n^2 + n + m).
*/
// declara la funcion principal.
int main() {
    // declara la opcion del menu.
    int opcion;
    // declara la cantidad de vertices.
    int n;
    // declara la cantidad de arcos.
    int m;
    // declara el nodo inicial para dfs.
    int nodoDFS;
    // declara el nodo inicial para bfs.
    int nodoBFS;
    // crea la matriz de adyacencia.
    vector<vector<int> > matriz;
    // crea la lista de adyacencia.
    vector<vector<int> > lista;

    // muestra el titulo del programa.
    cout << "programa de grafos" << endl;
    // muestra la primera opcion.
    cout << "1. ver ejemplo" << endl;
    // muestra la segunda opcion.
    cout << "2. ejecutar rutina por consola" << endl;
    // pide una opcion.
    cout << "elige una opcion: ";
    // lee la opcion.
    cin >> opcion;
    // explica como se numeran los vertices.
    cout << "los vertices se numeran desde 0 hasta n - 1." << endl;
    // revisa si se eligio el ejemplo.
    if (opcion == 1) {
        // carga el grafo de ejemplo.
        cargarEjemplo(n, m, matriz, lista);
        // guarda el nodo inicial para dfs del ejemplo.
        nodoDFS = 0;
        // guarda el nodo inicial para bfs del ejemplo.
        nodoBFS = 0;
        // muestra los resultados del ejemplo.
        mostrarResultados(matriz, lista, n, nodoDFS, nodoBFS);
        // termina el programa.
        return 0;
    // cierra la condicion.
    }
    // revisa si la opcion no es valida.
    if (opcion != 2) {
        // muestra un mensaje de error.
        cout << "opcion invalida." << endl;
        // termina el programa con error.
        return 1;
    // cierra la condicion.
    }
    // pide la cantidad de vertices.
    cout << "cantidad de vertices: ";
    // lee la cantidad de vertices.
    cin >> n;
    // valida que la cantidad de vertices sea positiva.
    if (n <= 0) {
        // muestra un mensaje de error.
        cout << "la cantidad de vertices debe ser positiva." << endl;
        // termina el programa con error.
        return 1;
    // cierra la condicion.
    }
    // pide la cantidad de arcos.
    cout << "cantidad de arcos: ";
    // lee la cantidad de arcos.
    cin >> m;
    // valida que la cantidad de arcos sea positiva.
    if (m <= 0) {
        // muestra un mensaje de error.
        cout << "la cantidad de arcos debe ser positiva." << endl;
        // termina el programa con error.
        return 1;
    // cierra la condicion.
    }

    // carga el grafo.
    loadGraph(n, m, matriz, lista);
    // pide el nodo inicial para dfs.
    cout << "nodo inicial para dfs (0 a " << n - 1 << "): ";
    // lee el nodo inicial para dfs.
    cin >> nodoDFS;
    // pide el nodo inicial para bfs.
    cout << "nodo inicial para bfs (0 a " << n - 1 << "): ";
    // lee el nodo inicial para bfs.
    cin >> nodoBFS;

    // muestra los resultados del grafo del usuario.
    mostrarResultados(matriz, lista, n, nodoDFS, nodoBFS);

    // termina el programa.
    return 0;
// cierra la funcion main.
}
