# AVL Tree

## Objetivo

Implementar un arbol AVL en C++ que mantenga el balance despues de inserciones y eliminaciones mediante rotaciones.

## Archivos

- `avl.cpp`: implementacion de `Node`, clase `AVL` y pruebas en `main`.
- `program`: ejecutable generado al compilar.

## Como compilar y ejecutar

Desde la carpeta `avl`:

```bash
g++ -std=c++11 avl.cpp -o program
./program
```

## Que hace el programa

El programa inserta valores de prueba, imprime el recorrido `inorder`, consulta el factor de balance de un nodo, valida si el arbol cumple la propiedad AVL y muestra el total de rotaciones realizadas.

## Estructura usada

Cada nodo contiene:

- `data`: valor entero.
- `left`: hijo izquierdo.
- `right`: hijo derecho.
- `height`: altura del nodo.

La clase `AVL` guarda la raiz y un contador de rotaciones.

## Operaciones principales

- `insert`: inserta y rebalancea, O(log n).
- `remove`: elimina y rebalancea, O(log n).
- `search`: busca un valor, O(log n).
- `getBalanceFactor`: calcula altura derecha menos altura izquierda, O(log n).
- `countRotations`: muestra el total de rotaciones, O(1).
- `isAVL`: valida que todos los factores de balance esten entre -1 y 1, O(n).
- `inorder`: imprime los valores ordenados, O(n).

## Rotaciones implementadas

- Rotacion derecha.
- Rotacion izquierda.
- Caso izquierda-derecha.
- Caso derecha-izquierda.

## Notas

El AVL evita el peor caso lineal de un BST comun porque mantiene la altura en O(log n).
