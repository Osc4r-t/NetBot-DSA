# Netbot 4

## Objetivo

Construir un grafo dirigido a partir de una bitacora de conexiones y analizar el fan-out de cada IP para detectar una posible IP bot master.

## Archivos

- `netbot.cpp`: implementacion de grafo dirigido, lectura de bitacora, ranking de fan-out, DFS y BFS.
- `bitacora.txt`: bitacora de entrada.
- `program`: ejecutable generado al compilar.

## Como compilar y ejecutar

Desde la carpeta `netbot4`:

```bash
g++ -std=c++11 netbot.cpp -o program
./program
```

## Que hace el programa

El programa lee `bitacora.txt` con registros que contienen IP origen e IP destino. Cada IP se representa como nodo y cada conexion origen-destino se guarda como arco dirigido.

Despues muestra:

- Total de registros leidos.
- Total de nodos/IPs unicas.
- Total de arcos dirigidos.
- Muestra de lista de adyacencia.
- Fan-out por nodo.
- Top 5 de IPs con mayor fan-out.
- Respuestas de la tarjeta de mision.
- Recorridos DFS y BFS desde la IP con mayor fan-out.

## Estructuras y algoritmos

- `map<string, int>`: asigna indice interno a cada IP.
- `vector<string>`: recupera IP a partir del indice.
- `vector<vector<int>>`: lista de adyacencia.
- `set<int>`: cuenta destinos unicos.
- `sort`: ordena el ranking de fan-out.
- `queue<int>`: cola para BFS.

## Complejidad

- Construccion del grafo: O(r log n), donde `r` es registros y `n` IPs unicas.
- Calculo de ranking: O(n log n + suma(k log k)).
- DFS/BFS: O(n + m), donde `m` es el numero de arcos.

## Datos requeridos

Debe existir `bitacora.txt` en la carpeta `netbot4`.

## Notas

El programa identifica como sospechosa principal a la IP con mayor cantidad de conexiones salientes. En caso de empate, usa orden lexicografico para mantener un criterio consistente.
