# Linked Lists

## Objetivo

Implementar una lista simplemente enlazada en C++ con operaciones basicas de insercion, eliminacion, busqueda, consulta, actualizacion, impresion y reversa.

## Archivos

- `linkedlist.cpp`: implementacion completa de `Node`, `LinkedList` y pruebas en `main`.
- `program`: ejecutable generado al compilar.

## Como compilar y ejecutar

Desde la carpeta `linkedlists`:

```bash
g++ -std=c++11 linkedlist.cpp -o program
./program
```

## Que hace el programa

El programa crea una lista enlazada y ejecuta operaciones de prueba:

- Inserta elementos al inicio y al final.
- Inserta elementos en una posicion.
- Intenta eliminar elementos con indices validos e invalidos.
- Imprime la lista usando los valores como letras.
- Invierte la lista mostrando el proceso intermedio.

## Estructuras usadas

- `Node`: guarda un valor entero y un apuntador al siguiente nodo.
- `LinkedList`: mantiene el apuntador `head` y un contador `size`.

## Funciones principales

- `insertFirst`: inserta al inicio, O(1).
- `insertLast`: inserta al final, O(n).
- `insertAt`: inserta en un indice, O(n).
- `deleteFirst`: elimina el primer nodo, O(1).
- `deleteLast`: elimina el ultimo nodo, O(n).
- `deleteAt`: elimina por indice, O(n).
- `find`: busca un valor, O(n).
- `getAt`: obtiene un valor por indice, O(n).
- `updateAt`: actualiza un valor por indice, O(n).
- `reverse`: invierte la lista, O(n).

## Salida esperada

La salida muestra la lista antes y despues de modificaciones, mensajes de indices invalidos y los pasos del proceso de reversa.

## Notas

El programa es demostrativo: los datos de prueba estan escritos directamente en `main`.
