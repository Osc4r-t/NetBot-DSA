# Netbot 1

## Objetivo

Leer una bitacora de accesos, ordenar los registros por fecha y hora con merge sort, y permitir busquedas por rango usando busqueda binaria.

## Archivos

- `netbot.cpp`: lectura de archivo, ordenamiento, busqueda por rango y escritura de resultados.
- `netbot.h`: clase `LogEntry` y operadores de comparacion por fecha.
- `bitacora_junio.txt`: bitacora de entrada requerida.
- `netbot1.zip`: paquete comprimido del proyecto.

## Como compilar y ejecutar

Desde la carpeta `netbot1`:

```bash
g++ -std=c++11 netbot.cpp -o program
./program
```

## Que hace el programa

El programa carga hasta 3350 registros de `bitacora_junio.txt`, convierte los campos de fecha y hora a una clase `LogEntry`, ordena los registros cronologicamente con merge sort y escribe el archivo `ordenado.txt`.

Despues pide al usuario:

- Fecha inicial en formato `M D H Min S`.
- Fecha final en formato `M D H Min S`.

Con esas fechas calcula el rango mediante busqueda binaria, ordena los resultados por numero de ataques y los muestra en consola. Tambien pregunta si se desea guardar la busqueda en `busqueda.txt`.

## Estructuras y algoritmos

- Arreglo de apuntadores `LogEntry*`.
- `mergeSort`: ordenamiento por fecha, O(n log n).
- `binarySearch`: localizacion de posicion por fecha, O(log n).
- `mergeSortByAttacks`: ordenamiento de resultados por ataques, O(k log k).

## Archivos generados

- `ordenado.txt`: registros ordenados cronologicamente.
- `busqueda.txt`: registros dentro del rango consultado, si el usuario elige guardarlos.

## Datos requeridos

Debe existir `bitacora_junio.txt` en la misma carpeta desde donde se ejecuta el programa.

## Notas

El formato esperado de cada registro es:

```text
Mes Dia Hora:Min:Seg IP:Puerto Motivo...
```
