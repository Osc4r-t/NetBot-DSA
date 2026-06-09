# Netbot 2

## Objetivo

Ordenar una bitacora por direccion IP usando una lista doblemente ligada y quicksort iterativo. Tambien permite consultar y guardar registros dentro de un rango de IPs.

## Archivos

- `netbot.cpp`: lista doble, pila auxiliar, quicksort iterativo, lectura de bitacora y busqueda por rango de IP.
- `netbot.h`: clase `LogEntry` con IP convertida a entero y operadores de comparacion por IP.
- `bitacora_noviembre.txt`: bitacora de entrada.
- `ordenado.txt`: archivo de salida con registros ordenados por IP.
- `resultado.txt`: archivo de salida para el rango consultado.
- `busqueda.txt`: archivo usado por versiones previas o ejecuciones de busqueda.
- `netbot2.zip`: paquete comprimido del proyecto.
- `Act 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia).pdf`: documento de la actividad.
- `Equipo 01 -Tarjeta de mision.png`: imagen de referencia de la mision.

## Como compilar y ejecutar

Desde la carpeta `netbot2`:

```bash
g++ -std=c++11 netbot.cpp -o program
./program
```

## Que hace el programa

El programa lee registros de `bitacora_noviembre.txt`, convierte cada IP en un entero de 32 bits para poder compararla facilmente, guarda los registros en una lista doble y la ordena con quicksort iterativo.

Luego permite capturar un rango de IPs y:

- Imprimir los registros que caen dentro del rango.
- Guardar los registros filtrados en un archivo de salida.
- Guardar la bitacora completa ordenada.

## Estructuras y algoritmos

- `DoublyLinkedList`: lista doblemente ligada.
- `Stack`: pila propia para rangos pendientes de quicksort.
- `quickSortIterative`: ordena la lista por IP, promedio O(n log n), peor caso O(n^2).
- `ipToInt`: convierte IP con puntos a entero.
- `printIPRange` y `saveIPRangeToFile`: recorren la lista para filtrar por IP, O(n).

## Archivos generados

- `ordenado.txt`: bitacora ordenada por IP.
- `resultado.txt`: registros filtrados por rango de IP.

## Datos requeridos

Debe existir `bitacora_noviembre.txt` en la carpeta `netbot2`.

## Notas

Esta fase prepara informacion que puede usarse en analisis posteriores, especialmente cuando se necesita contar accesos por IP.
