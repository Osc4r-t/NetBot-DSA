# Binary Search Tree

## Objetivo

Implementar un arbol binario de busqueda en C++ con insercion, busqueda, eliminacion, recorridos y consultas adicionales.

## Archivos

- `bst.cpp`: implementacion de `Node`, clase `BST` y pruebas en `main`.
- `program`: ejecutable generado al compilar.
- `bst.zip`: paquete comprimido del proyecto.

## Como compilar y ejecutar

Desde la carpeta `bst`:

```bash
g++ -std=c++11 bst.cpp -o program
./program
```

## Que hace el programa

El programa inserta valores de prueba en un BST y muestra:

- Recorrido `inorder`.
- Recorrido `preorder`.
- Recorrido `postorder`.
- Ancestros de un valor.
- Nivel de diferentes valores con `whatLevelAmI`.
- Altura del arbol.

## Estructura usada

Cada nodo guarda:

- `data`: valor entero.
- `left`: hijo izquierdo.
- `right`: hijo derecho.

La clase `BST` mantiene un apuntador a la raiz y opera respetando la regla: valores menores a la izquierda, mayores a la derecha.

## Funciones principales

- `insert`: inserta sin duplicados, O(h).
- `search`: busca un valor, O(h).
- `remove`: elimina un valor y reacomoda el arbol, O(h).
- `findMin` y `findMax`: consultan extremos, O(h).
- `inorder`, `preorder`, `postorder`: recorridos, O(n).
- `height`: calcula altura, O(n).
- `whatLevelAmI`: devuelve el nivel de un valor o `-1` si no existe, O(h).
- `ancestors`: imprime los ancestros de un valor, O(h).

## Notas

`h` representa la altura del arbol. En un BST no balanceado, el peor caso puede llegar a O(n).
