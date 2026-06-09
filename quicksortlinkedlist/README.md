# Quicksort en lista doblemente ligada

## Objetivo

Implementar quicksort de forma iterativa sobre una lista doblemente enlazada, usando una pila propia para evitar recursion.

## Archivos

- `quicksortlinkedlist.cpp`: implementacion de lista doble, pila auxiliar, particion y quicksort iterativo.
- `program`: ejecutable generado al compilar.

## Como compilar y ejecutar

Desde la carpeta `quicksortlinkedlist`:

```bash
g++ -std=c++11 quicksortlinkedlist.cpp -o program
./program
```

## Que hace el programa

El programa construye una lista doble con valores enteros, imprime la lista original, ejecuta quicksort iterativo e imprime la lista ordenada.

## Estructuras usadas

- `Node`: nodo de lista doble con `next` y `prev`.
- `DoublyLinkedList`: lista con `head`, `tail` y `size`.
- `StackNode` y `Stack`: pila para guardar rangos pendientes de ordenar.

## Algoritmo

La funcion `quickSortIterative` guarda rangos de nodos en una pila. Para cada rango aplica `partition`, que usa el ultimo nodo como pivote y reordena los valores con una particion estilo Lomuto. Despues agrega a la pila los subrangos izquierdo y derecho que faltan por ordenar.

## Complejidad

- Promedio: O(n log n).
- Peor caso: O(n^2), dependiendo de la seleccion del pivote.
- Espacio auxiliar: O(n) en el peor caso por la pila de rangos.

## Referencia base

```text
https://www.geeksforgeeks.org/dsa/quicksort-for-linked-list/
```
