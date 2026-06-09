# Actividad 5.2 - Tabla hash por dominio

## Objetivo

Construir una tabla hash propia para agrupar accesos por dominio o destino, consultar un dominio en tiempo O(1) promedio y responder las preguntas de la tarjeta de mision.

## Archivos

- `bitacora.txt`: archivo base de accesos.
- `netbot.cpp`: solucion en C++ con tabla hash.
- `program`: ejecutable generado al compilar.

## Como compilar y ejecutar

Desde la carpeta `netbot5`:

```bash
g++ -std=c++11 netbot.cpp -o program
./program
```

## Que hace el programa

El programa lee `bitacora.txt`, toma cada registro con el formato:

```text
Mes Dia Hora IP_origen Dominio_o_IP_destino Mensaje...
```

En esta bitacora el campo de dominio aparece como una IP destino. Siguiendo la tarjeta de mision, la llave de la tabla hash se construye agrupando por los primeros dos octetos de la IP destino.

Ejemplo:

```text
192.168.10.25 -> 192.168
```

Cada llave guarda:

- Numero total de accesos al dominio/destino.
- Numero de IPs origen unicas.
- Lista de IPs origen que accedieron a ese dominio/destino.

Al iniciar, el programa muestra estadisticas generales y el top 5 de destinos con mas accesos. Despues abre un menu interactivo para consultar dominios, ver rankings, mostrar la tabla completa, consultar estadisticas y desplegar las respuestas de la tarjeta de mision.

## Estructura usada

Se implementa una tabla hash propia con:

- Funcion hash polinomial propia.
- Manejo de colisiones por encadenamiento.
- Metodo de consulta por dominio: `searchDomain`.
- Despliegue ordenado de la informacion con `displayDomain`.
- Vista de preguntas de la tarjeta de mision desde el menu del programa.

## Menu

- `1`: consultar dominio/destino.
- `2`: mostrar top dominios/destinos.
- `3`: mostrar tabla hash completa.
- `4`: mostrar estadisticas.
- `5`: ver preguntas de la tarjeta de mision.
- `0`: salir.

## Complejidad

- Lectura del archivo: O(r), donde r es el numero de registros.
- Insercion en tabla hash: O(1) promedio, O(n) peor caso.
- Consulta por dominio: O(1) promedio, O(n) peor caso.
- Impresion de IPs de un dominio: O(u log u), donde u es el numero de IPs unicas.
- Top dominios: O(n log n), donde n es el numero de dominios/destinos unicos.

## Datos requeridos

Debe existir `bitacora.txt` en la carpeta `netbot5`.

## Puntos para la reflexion individual

Las tablas hash son eficientes porque permiten agrupar grandes cantidades de accesos por llave con costo promedio constante. En este problema ayudan a consultar rapidamente el resumen de un dominio sin recorrer toda la bitacora.

Comparacion breve:

- Hash con encadenamiento: tolera colisiones guardando listas por cubeta; es simple y no se bloquea si el factor de carga crece.
- Hash con linear probing: evita listas externas, pero puede sufrir agrupamiento primario y requiere cuidar espacios vacios.
- Hash vs BST: hash tiene busqueda promedio O(1), BST tiene O(log n) si esta balanceado y permite ordenar por llave.
- Hash vs grafo: hash resume accesos por dominio; grafo modela relaciones entre origen y destino, pero consultar un resumen agregado puede ser mas costoso si no se indexa.
