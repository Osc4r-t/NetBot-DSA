# Resumen de Netbots para presentacion

## Slide 1 - Titulo

**Proyecto Netbots: Analisis de bitacoras con estructuras de datos**

Este conjunto de actividades aplica estructuras de datos para procesar registros de red, ordenar informacion, buscar rangos, detectar patrones de acceso y proponer posibles IPs sospechosas.

## Slide 2 - Objetivo general

El objetivo general de los cinco Netbots es analizar bitacoras de red usando diferentes estructuras de datos:

- Arreglos y merge sort para ordenar por fecha.
- Listas doblemente ligadas y quicksort para ordenar por IP.
- Arboles BST para detectar IPs con mas accesos.
- Grafos dirigidos para analizar conexiones entre IPs.
- Tablas hash para agrupar accesos por dominio o destino.

## Slide 3 - Flujo general del proyecto

El proyecto avanza por fases:

1. `netbot1`: ordena la bitacora por fecha y busca eventos por rango.
2. `netbot2`: ordena registros por IP usando lista doble y quicksort.
3. `netbot3`: cuenta accesos por IP y obtiene las IPs mas frecuentes con BST.
4. `netbot4`: modela conexiones como grafo dirigido y analiza fan-out.
5. `netbot5`: agrupa accesos por dominio/destino usando tabla hash.

Cada fase usa una estructura diferente para resolver una parte del analisis.

## Slide 4 - Netbot 1: Ordenamiento por fecha

**Estructura principal:** arreglo de apuntadores a `LogEntry`.

**Algoritmos usados:**

- Merge sort para ordenar cronologicamente.
- Busqueda binaria para ubicar rangos de fecha.
- Ordenamiento adicional por numero de ataques en los resultados.

**Entrada:** `bitacora_junio.txt`.

**Salida:** `ordenado.txt` y, si el usuario lo decide, `busqueda.txt`.

## Slide 5 - Netbot 1: Funcionamiento

El programa lee la bitacora, separa cada registro en mes, dia, hora, minuto, segundo, IP, puerto y motivo. Despues convierte la fecha a valores numericos para poder comparar registros.

Una vez ordenados, el usuario ingresa una fecha inicial y una fecha final. El programa localiza el rango con busqueda binaria y muestra los registros encontrados.

**Importancia:** esta fase permite buscar eventos de red en intervalos especificos sin recorrer toda la bitacora cada vez.

## Slide 6 - Netbot 2: Ordenamiento por IP

**Estructura principal:** lista doblemente ligada.

**Algoritmos usados:**

- Conversion de IP a entero.
- Quicksort iterativo.
- Pila auxiliar para reemplazar recursion.

**Entrada:** `bitacora_noviembre.txt`.

**Salida:** `ordenado.txt` y `resultado.txt`.

## Slide 7 - Netbot 2: Funcionamiento

El programa convierte cada IP a un numero entero para compararla facilmente. Luego guarda los registros en una lista doblemente ligada y los ordena por IP con quicksort.

Tambien permite consultar un rango de IPs, imprimir los registros encontrados y guardar los resultados.

**Importancia:** ordenar por IP facilita agrupar conexiones y preparar datos para analisis posteriores.

## Slide 8 - Netbot 3: Analisis con BST

**Estructura principal:** arbol binario de busqueda.

**Archivo de entrada:** `resultado.txt`.

**Dato almacenado por nodo:**

- Numero de accesos.
- IP asociada.

El BST se ordena por cantidad de accesos. Si dos IPs tienen el mismo numero de accesos, usa la IP como criterio de desempate.

## Slide 9 - Netbot 3: Funcionamiento

El programa lee un archivo ya ordenado por IP. Como las IPs iguales aparecen juntas, puede contar sus apariciones en una sola pasada.

Cada IP unica se inserta en el BST junto con su numero de accesos. Despues se hace un recorrido in-order inverso para imprimir primero las IPs con mas accesos.

**Resultado principal:** top 5 de IPs con mayor numero de accesos.

## Slide 10 - Netbot 4: Analisis con grafos

**Estructura principal:** grafo dirigido con lista de adyacencia.

**Representacion:**

- Cada IP es un nodo.
- Cada conexion origen-destino es un arco dirigido.

**Entrada:** `bitacora.txt`.

**Analisis principal:** fan-out de cada nodo, es decir, cuantas conexiones salientes tiene una IP.

## Slide 11 - Netbot 4: Funcionamiento

El programa construye el grafo a partir de la bitacora. Usa un mapa para asignar un indice interno a cada IP y una lista de adyacencia para guardar sus conexiones.

Despues muestra:

- Total de registros.
- Total de IPs unicas.
- Total de arcos.
- Muestra de lista de adyacencia.
- Fan-out por nodo.
- Top 5 de IPs con mayor fan-out.
- DFS y BFS desde la IP con mayor fan-out.

**Resultado principal:** propuesta de IP bot master.

## Slide 12 - Netbot 5: Tabla hash por dominio

**Estructura principal:** tabla hash con encadenamiento.

**Entrada:** `bitacora.txt`.

**Llave:** dominio o destino. En esta implementacion, el destino se agrupa por los primeros dos octetos de la IP.

**Valor almacenado:**

- Numero total de accesos.
- Numero de IPs origen unicas.
- Lista de IPs que accedieron a ese destino.

## Slide 13 - Netbot 5: Funcionamiento

El programa lee cada registro, obtiene la IP origen y el destino, calcula la llave del dominio/destino y la inserta en la tabla hash.

Despues ofrece un menu para:

- Consultar un dominio o destino.
- Mostrar top dominios/destinos.
- Ver la tabla hash completa.
- Mostrar estadisticas.
- Responder preguntas de la tarjeta de mision.

**Importancia:** permite consultas promedio O(1) por dominio o destino.

## Slide 14 - Comparacion de estructuras

| Netbot | Estructura | Uso principal |
| --- | --- | --- |
| `netbot1` | Arreglo + merge sort | Ordenar y buscar por fecha |
| `netbot2` | Lista doble + quicksort | Ordenar y filtrar por IP |
| `netbot3` | BST | Ranking de IPs por accesos |
| `netbot4` | Grafo dirigido | Analisis de conexiones y fan-out |
| `netbot5` | Tabla hash | Agrupacion y consulta por dominio/destino |

## Slide 15 - Complejidades principales

- `netbot1`: merge sort O(n log n), busqueda binaria O(log n).
- `netbot2`: quicksort promedio O(n log n), peor caso O(n^2).
- `netbot3`: insercion en BST O(h), ranking O(h + k).
- `netbot4`: construccion de grafo O(r log n), DFS/BFS O(n + m).
- `netbot5`: insercion y busqueda hash O(1) promedio, O(n) peor caso.

Donde `n` es la cantidad de elementos, `r` los registros, `m` los arcos y `h` la altura del arbol.

## Slide 16 - Resultados esperados

Al ejecutar los Netbots se obtienen diferentes vistas del mismo problema:

- Registros ordenados por fecha.
- Registros ordenados por IP.
- IPs con mas accesos.
- IPs con mas conexiones salientes.
- Dominios o destinos mas consultados.

Estas salidas ayudan a detectar patrones anormales dentro de la bitacora.

## Slide 17 - Interpretacion de seguridad

Los programas no solo procesan datos: tambien ayudan a interpretar comportamiento de red.

Una IP con muchos accesos puede indicar alta actividad o posible abuso. Una IP con fan-out alto puede ser sospechosa porque intenta conectarse con muchos destinos. Un dominio o destino con muchos accesos puede ser un punto central de comunicacion.

Por eso, las estructuras de datos permiten convertir una bitacora grande en informacion util para investigar actividad sospechosa.

## Slide 18 - Conclusion

El proyecto demuestra como elegir una estructura de datos adecuada cambia la forma de resolver un problema:

- Merge sort y busqueda binaria son utiles para ordenar y consultar fechas.
- Listas y quicksort permiten ordenar registros enlazados por IP.
- BST ayuda a obtener rankings por accesos.
- Grafos representan relaciones entre equipos.
- Hash tables permiten consultas rapidas por dominio o destino.

En conjunto, los cinco Netbots forman una cadena de analisis para detectar patrones importantes en registros de red.

## Slide 19 - Posibles puntos para explicar oralmente

- Por que se convierte una IP a entero en `netbot2`.
- Por que el BST de `netbot3` usa la IP como desempate.
- Por que el fan-out es importante para detectar una IP sospechosa.
- Por que una lista de adyacencia es mejor que una matriz cuando el grafo es disperso.
- Por que una tabla hash es eficiente para consultas exactas por dominio.

## Slide 20 - Cierre

**Idea final:** cada Netbot aplica una estructura de datos diferente para transformar una bitacora de red en informacion ordenada, consultable y util para detectar actividad sospechosa.
