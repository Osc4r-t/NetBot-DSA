# Graphs

## Objetivo

Representar un grafo dirigido con matriz de adyacencia y lista de adyacencia, y ejecutar recorridos DFS y BFS.

## Archivos

- `appGrafo.cpp`: implementacion completa del grafo, funciones de carga, impresion y recorridos.
- `appGrafo`: ejecutable generado al compilar.

## Como compilar y ejecutar

Desde la carpeta `graphs`:

```bash
g++ -std=c++11 appGrafo.cpp -o appGrafo
./appGrafo
```

## Que hace el programa

El programa ofrece dos opciones:

- Ver un grafo de ejemplo ya cargado.
- Capturar un grafo por consola indicando vertices, arcos y nodos iniciales para DFS/BFS.

Despues muestra:

- Matriz de adyacencia.
- Lista de adyacencia.
- Recorrido DFS desde el nodo indicado.
- Recorrido BFS desde el nodo indicado.

## Estructuras usadas

- `vector<vector<int>> matriz`: matriz de adyacencia de tamano `n x n`.
- `vector<vector<int>> lista`: lista de adyacencia.
- `queue<int>`: cola auxiliar para BFS.
- `vector<bool>`: arreglo de visitados.

## Complejidad

- Carga de grafo: O(n^2 + m).
- Impresion de matriz: O(n^2).
- Impresion de lista: O(n + m).
- DFS con matriz: O(n^2).
- BFS con lista: O(n + m).

## Notas

Los vertices se numeran desde `0` hasta `n - 1`. El programa valida que los arcos capturados esten dentro de ese rango.
