# El 8-Puzzle

## Descripción del juego y aplicación
El `8-puzzle` es un juego de rompecabezas que consiste en un marco de 3x3 (nueve casillas) donde ocho de las casillas contienen un bloque numerado del 1 al 8, y una casilla está vacía. El objetivo del juego, y para lo que fue hecho este codigo, es mover los bloques alrededor de la casilla vacía para alcanzar una configuración específica, generalmente ordenando los números en un patrón secuencial.

## Ejemplo de uso de la aplicación
### Ejecución
Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar `repl.it` para una rápida configuración y ejecución. Sigue estos pasos para comenzar:
* Visita `repl.it`.
* Crea una nueva cuenta o inicia sesión si ya tienes una.
* Una vez en tu dashboard, selecciona `New Repl` y elige `Import from GitHub`.
* Pega la URL de este repositorio.
* repl.it clonará el repositorio y preparará un entorno de ejecución.
* Para ejecutar el main en `repl.it` primero debemos compilar (en la carpeta raíz):
````
gcc tdas/*.c tarea3.c -Wno-unused-result -o tarea3
````

* Y luego ejecutar:
````
./tarea3
````
### Uso de la aplicación
Al realizar la ejecución indicada se abrira el siguiente menu:
````
========================================
     Escoge método de búsqueda
========================================

1) Búsqueda en Profundidad
2) Búsqueda en Anchura
3) Buscar Mejor Primero
4) Salir

Ingrese su opción:
````
Se debera ingresar el numero que acompaña a la accion en el menu para realizar la función deaseada.

A continuación lo que se puede realizar en cada una de las opciones:
* `Búsqueda en Profundidad`: Busca segun el metodo de profundidad el puzzle en su estado final. Como en el ejemplo a continuación:
````
========================================
     Búsqueda en Profundidad
========================================

Estado Original:

Estado del tablero:
 -------------
|  x |  2 |  8 | 
 -------------
|  1 |  3 |  4 | 
 -------------
|  6 |  5 |  7 | 
 -------------

¡Puzzle resuelto!
Iteraciones: 119550

Paso 0:

Estado del tablero:
 -------------
|  x |  2 |  8 | 
 -------------
|  1 |  3 |  4 | 
 -------------
|  6 |  5 |  7 | 
 -------------

Paso 1:

Estado del tablero:
 -------------
|  1 |  2 |  8 | 
 -------------
|  x |  3 |  4 | 
 -------------
|  6 |  5 |  7 | 
 -------------
 ...
 ...
 Paso 14:

 Estado del tablero:
  -------------
 |  x |  1 |  2 | 
  -------------
 |  3 |  4 |  5 | 
  -------------
 |  6 |  7 |  8 | 
  -------------

 Presione una tecla para continuar...
````
* `Búsqueda en Anchura`: Busca segun el metodo de anchura el puzzle en su estado final. Como en el ejemplo a continuación:
````
========================================
     Búsqueda en Anchura
========================================

Initial State:

Estado del tablero:
 -------------
|  x |  2 |  8 | 
 -------------
|  1 |  3 |  4 | 
 -------------
|  6 |  5 |  7 | 
 -------------

¡Puzzle resuelto!
Iteraciones: 221143

Paso 0:

Estado del tablero:
 -------------
|  x |  2 |  8 | 
 -------------
|  1 |  3 |  4 | 
 -------------
|  6 |  5 |  7 | 
 -------------

Paso 1:

Estado del tablero:
 -------------
|  1 |  2 |  8 | 
 -------------
|  x |  3 |  4 | 
 -------------
|  6 |  5 |  7 | 
 -------------
 ...
 ...
 Paso 12:

 Estado del tablero:
  -------------
 |  x |  1 |  2 | 
  -------------
 |  3 |  4 |  5 | 
  -------------
 |  6 |  7 |  8 | 
  -------------

 Presione una tecla para continuar...
````
* `Buscar Mejor Primero`: Se muestra el puzzle resuelto por el programa con menor cantidad de iteraciónes. Como en el ejemplo a continuación:
````
========================================
     Buscar Mejor Primero
========================================

Initial State:

Estado del tablero:
 -------------
|  x |  2 |  8 | 
 -------------
|  1 |  3 |  4 | 
 -------------
|  6 |  5 |  7 | 
 -------------

¡Puzzle resuelto!
Iteraciones: 188085

Paso 0:

Estado del tablero:
 -------------
|  x |  2 |  8 | 
 -------------
|  1 |  3 |  4 | 
 -------------
|  6 |  5 |  7 | 
 -------------

Paso 1:

Estado del tablero:
 -------------
|  1 |  2 |  8 | 
 -------------
|  x |  3 |  4 | 
 -------------
|  6 |  5 |  7 | 
 -------------
 ...
 ...
 Paso 12:

 Estado del tablero:
  -------------
 |  x |  1 |  2 | 
  -------------
 |  3 |  4 |  5 | 
  -------------
 |  6 |  7 |  8 | 
  -------------

 Presione una tecla para continuar...
````
* `Salir`: Terminar el programa.

## Especificaciones de la aplicacion
### Funcionalidades de la aplicación
* `isValidMove`: Función que verifica si un movimiento es válido. Comprueba si las coordenadas dadas están dentro de los límites del tablero de 3x3, asegurando que el movimiento es posible dentro de la matriz.
* `imprimirEstado`: Función que imprime el estado del tablero. Muestra la disposición actual de los números en la matriz 3x3, reemplazando el espacio vacío con una "x" para facilitar la visualización del tablero.
* `isFinal`: Función que verifica si el estado actual es el estado final. Compara el estado actual del tablero con el estado objetivo, determinando si el rompecabezas ha sido resuelto correctamente.
* `copyState`: Función que copia el estado de un tablero a otro. Realiza una copia profunda de la matriz 3x3 y las posiciones del espacio vacío, asegurando que se mantengan todas las propiedades del estado original en el nuevo.
* `move`: Función que mueve el espacio vacío en el tablero según la elección. Realiza el movimiento del espacio vacío en una dirección específica (arriba, abajo, izquierda, derecha), actualizando las coordenadas del espacio vacío en consecuencia.
* `transition`: Función que realiza la transición de estado a un nuevo estado según la acción. Crea un nuevo estado a partir del estado actual y aplica el movimiento especificado, incrementando el contador de acciones realizadas.
* `getAdjNodes`: Función que obtiene los nodos adyacentes del nodo actual. Genera y retorna una lista de nuevos nodos que representan los posibles estados alcanzables desde el nodo actual, considerando todos los movimientos válidos del espacio vacío.
* `dfs`: Función de búsqueda en profundidad (DFS). Implementa el algoritmo DFS para explorar los posibles estados del tablero, buscando una solución al rompecabezas al profundizar en cada rama antes de retroceder.
* `bfs`: Función de búsqueda en anchura (BFS). Implementa el algoritmo BFS para explorar los posibles estados del tablero, buscando una solución al rompecabezas explorando todos los nodos a un mismo nivel antes de pasar al siguiente nivel.
* `manhattanDistance`: Función que calcula la distancia de Manhattan para un estado dado. Suma las distancias absolutas de cada número desde su posición actual hasta su posición objetivo, proporcionando una heurística para la búsqueda A*.
* `getMemoryUsage`: Función que obtiene el uso de memoria. Utiliza estructuras del sistema para obtener y devolver la cantidad de memoria máxima utilizada por el proceso, medida en bytes, para monitorear el consumo de recursos.
* `best_first`: Función de búsqueda en profundidad iterativa primero el mejor. Implementa una variación del algoritmo de búsqueda primero el mejor (best-first search) con profundidad iterativa, utilizando la distancia de Manhattan como heurística para guiar la búsqueda hacia la solución.

### Posibles errores en la aplicación
* Los principales errores que podrian ocurrir en la aplicación son `errores humanos`, ya que, si el usuario ingresa palabras/letras en las secciones donde se deben ingresar numeros  la aplicación se salta la seccion completa.
* Otro error, es si el puzzle a resolver es bastante complicado, se podrían realizar numerosas iteraciones lo que podria ocacionar un uso de memoria excesivo generando que no se encuentre solución logrando incumplir los objetivos de la aplicación.