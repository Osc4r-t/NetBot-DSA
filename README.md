# Estructuras de Datos 2

Repositorio con ejercicios y actividades integradoras de estructuras de datos en C++. Los proyectos avanzan desde estructuras lineales basicas hasta arboles, grafos y tablas hash aplicadas al analisis de bitacoras de red.

## Requisitos

- Compilador C++ compatible con C++11 o superior.
- Terminal ubicada en la carpeta del proyecto que se quiere ejecutar.

Ejemplo general de compilacion:

```bash
g++ -std=c++11 archivo.cpp -o program
./program
```

## Estructura del repositorio

| Carpeta | Tema principal | Archivo principal |
| --- | --- | --- |
| `linkedlists` | Lista simplemente enlazada | `linkedlist.cpp` |
| `quicksortlinkedlist` | Quicksort iterativo en lista doble | `quicksortlinkedlist.cpp` |
| `bst` | Arbol binario de busqueda | `bst.cpp` |
| `avl` | Arbol AVL | `avl.cpp` |
| `graphs` | Grafo con matriz/lista, DFS y BFS | `appGrafo.cpp` |
| `netbot1` | Fase inicial de bitacoras: ordenamiento y busqueda por fecha | `netbot.cpp`, `netbot.h` |
| `netbot2` | Ordenamiento de bitacora con lista doble y quicksort por IP | `netbot.cpp`, `netbot.h` |
| `netbot3` | Analisis de accesos por IP usando BST | `netbot.cpp` |
| `netbot4` | Analisis de conexiones con grafo dirigido | `netbot.cpp` |
| `netbot5` | Tabla hash por dominio/destino | `netbot.cpp` |

## Orden sugerido de revision

1. `linkedlists`: operaciones basicas de lista enlazada.
2. `quicksortlinkedlist`: lista doble, pila auxiliar y quicksort iterativo.
3. `bst`: insercion, busqueda, recorridos, ancestros y altura en BST.
4. `avl`: balanceo automatico con rotaciones.
5. `graphs`: representacion de grafos, matriz/lista de adyacencia, DFS y BFS.
6. `netbot1`: lectura de bitacora, ordenamiento por fecha y busqueda por rango.
7. `netbot2`: lectura de bitacora, conversion de IP a entero, ordenamiento por IP y guardado de resultados.
8. `netbot3`: conteo de IPs usando el archivo ordenado de la fase anterior y ranking con BST.
9. `netbot4`: construccion de grafo dirigido origen-destino y analisis de fan-out.
10. `netbot5`: agrupacion por dominio/destino con tabla hash y consultas O(1) promedio.

## Archivos generados

Algunos proyectos incluyen ejecutables llamados `program` o `appGrafo`, ademas de archivos de salida como `ordenado.txt`, `busqueda.txt` y `resultado.txt`. Esos archivos son productos de ejecucion y pueden regenerarse compilando y corriendo el proyecto correspondiente.

## Notas generales

- Los proyectos `netbot` dependen de archivos de bitacora locales. Antes de ejecutar cada fase, revisa el README de su carpeta para confirmar el archivo requerido.
- Las implementaciones estan escritas como programas independientes; no hay un sistema de build global.
- Cada carpeta tiene su propio `README.md` con objetivo, archivos, comandos y comportamiento esperado.
