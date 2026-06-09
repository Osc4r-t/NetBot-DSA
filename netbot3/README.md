# Netbot 3

## Objetivo

Analizar una bitacora ya ordenada por IP y construir un arbol binario de busqueda para identificar las IPs con mas accesos.

## Archivos

- `netbot.cpp`: lectura de `resultado.txt`, conteo de IPs y ranking con BST.
- `resultado.txt`: archivo de entrada esperado, ordenado por IP.
- `program`: ejecutable generado al compilar.

## Como compilar y ejecutar

Desde la carpeta `netbot3`:

```bash
g++ -std=c++11 netbot.cpp -o program
./program
```

## Que hace el programa

El programa lee `resultado.txt`, extrae la IP de cada linea y cuenta cuantas veces aparece cada IP. Como el archivo debe estar ordenado por IP, puede contar apariciones consecutivas en una sola pasada.

Cada par `(numAccesos, IP)` se inserta en un BST. Despues el programa imprime el top 5 de IPs con mas accesos usando un recorrido in-order inverso.

## Estructura usada

Cada nodo del BST guarda:

- `numAccesos`: cantidad de accesos asociados a una IP.
- `ip`: direccion IP.
- `left` y `right`: hijos del arbol.

El arbol se ordena primero por `numAccesos` y usa la IP como desempate para no perder nodos con conteos repetidos.

## Complejidad

- Lectura y conteo: O(n), donde `n` es el numero de registros.
- Insercion en BST: O(h) por IP unica.
- Ranking top k: O(h + k).

## Datos requeridos

Debe existir `resultado.txt` en la carpeta `netbot3`. Si falta o no esta ordenado por IP, el conteo puede ser incorrecto.

## Notas

Esta fase asume que el archivo de entrada viene de una fase previa donde los registros quedaron agrupados por IP.
