#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/heap.h"
#include "tdas/extra.h"
#include "tdas/stack.h"
#include "tdas/queue.h"
#include <string.h>
#include <sys/resource.h> // Biblioteca para obtener el uso de recursos del sistema (memoria, CPU, etc.)

// Estructura que representa el estado del tablero del juego
typedef struct{
  int square[3][3]; // Matriz 3x3 que representa el tablero
  int x;    // Posición x del espacio vacío
  int y;    // Posición y del espacio vacío
  int numActions;
} State;
// Nodo que representa un estado en la búsqueda
typedef struct Node{
  State state;
  struct Node* parent;
} Node;

// Función que muestra el menú principal
void mostrarMenuPrincipal(){
  limpiarPantalla();
  puts("========================================");
  puts("     Escoge método de búsqueda");
  puts("========================================");
  puts("");
  puts("1) Búsqueda en Profundidad");
  puts("2) Búsqueda en Anchura");
  puts("3) Buscar Mejor Primero");
  puts("4) Salir");
  puts("");
}
// Función que verifica si un movimiento es válido
int isValidMove(int x, int y){
  return (x >= 0 && x < 3 && y >= 0 && y < 3);}
// Función que imprime el estado del tablero
void imprimirEstado(const State *estado) {
  printf("Estado del tablero:\n");
  printf(" -------------\n");
  for (int i = 0; i < 3; i++) {
    printf("| ");
    for (int j = 0; j < 3; j++) {
      if (estado->square[i][j] == 0)
        printf(" x | ");
      else
        printf(" %d | ", estado->square[i][j]);
    }
    printf("\n -------------\n");
  }
}
// Función que verifica si el estado actual es el estado final
int isFinal(const State* estado){
  State finalState = {
    {{0, 1, 2},
    {3, 4, 5},  
    {6, 7, 8}},
    0,0
  };
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (estado->square[i][j] != finalState.square[i][j]) return 0;
  return 1;
}
// Función que copia el estado de un tablero a otro
void copyState(State original, State* new){
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      new->square[i][j] = original.square[i][j];

  new->x = original.x;
  new->y = original.y;
  new->numActions = original.numActions;
}
// Función que mueve el espacio vacío en el tablero según la elección
void move(State* current, int choice){
  int x = current->x;
  int y = current->y;
  int temp;
  switch (choice){
    case 1: // Mover espacio vacío hacia arriba
      if (isValidMove(x , y - 1)){
        temp = current->square[x][y - 1];
        current->square[x][y - 1] = current->square[x][y];
        current->square[x][y] = temp;
        current->y = y - 1;
      }
      break;

    case 2: // Mover espacio vacío hacia abajo
      if (isValidMove(x , y + 1)){
        temp = current->square[x][y + 1];
        current->square[x][y + 1] = current->square[x][y];
        current->square[x][y] = temp;
        current->y = y + 1;
      }
      break;

    case 3: // Mover espacio vacío hacia la izquierda
      if (isValidMove(x - 1, y)){
        temp = current->square[x - 1][y];
        current->square[x - 1][y] = current->square[x][y];
        current->square[x][y] = temp;
        current->x = x - 1;
      }
      break;

    case 4: // Mover espacio vacío hacia la derecha
      if (isValidMove(x + 1, y)){
        temp = current->square[x + 1][y];
        current->square[x + 1][y] = current->square[x][y];
        current->square[x][y] = temp;
        current->x = x + 1;
      }
      break;
  }
}
// Función que realiza la transición de estado a un nuevo estado según la acción
State* transition(State* oldState, int action){
  State *newState = (State*) malloc(sizeof(State));
  copyState(*oldState, newState);
  move(newState, action);
  newState->numActions++;
  return newState;
}
// Función que obtiene los nodos adyacentes del nodo actual
List *getAdjNodes(Node* parentNode){
  List *adjList = list_create();
  int x = parentNode->state.x;
  int y = parentNode->state.y;

  // Generar nodos adyacentes para cada movimiento posible
  for (int i = 1; i <= 4; i++){
    State *newState = transition(&parentNode->state, i);

    // Si se realizó un movimiento válido, agregar el nuevo nodo a la lista
    if(newState->x != x || newState->y != y){
      Node *newNode = (Node*) malloc(sizeof(Node));
      newNode->state = *newState;
      newNode->parent = parentNode;
      list_pushBack(adjList, newNode);
    } 
    else
      free(newState);
  }
  return adjList;
}
// Función de búsqueda en profundidad (DFS)
void dfs(State initialState, int count){
  limpiarPantalla();
  Stack* stack = stack_create(stack);
  puts("========================================");
  puts("     Búsqueda en Profundidad");
  puts("========================================");
  puts("");
  printf("Estado Original:\n\n");
  imprimirEstado(&initialState);
  printf("\n");

  Node *root = (Node *) malloc(sizeof(Node ));
  root->parent = NULL;
  root->state = initialState;

  stack_push(stack, root);
  // Bucle de búsqueda en profundidad
  while (list_size(stack) > 0){
    Node *currentNode = (Node *) stack_top(stack);
    stack_pop(stack);

    // Limitar la profundidad de la búsqueda
    if(currentNode->state.numActions >= 15)
        continue;

    // Verificar si el estado actual es el estado final
    if(isFinal(&currentNode->state)){
      printf("¡Puzzle resuelto!\n");
      printf("Iteraciones: %d\n\n", count);
      Node *node = currentNode;
      int steps = currentNode->state.numActions;
      
      // Después de encontrar la solución
      List *stepsList = list_create(); // Crear una lista para almacenar los pasos
      Node *currentStep = currentNode;
      while (currentStep != NULL) {
          list_pushFront(stepsList, &currentStep->state);
          currentStep = currentStep->parent;
      }

      // Imprime los pasos en orden inverso
      Node *stepToPrint = list_first(stepsList);
      int stepCount = 0;
      while (stepToPrint != NULL) {
          printf("Paso %d:\n\n", stepCount);
          imprimirEstado(&stepToPrint->state);
          printf("\n");
          stepToPrint = list_next(stepsList);
          stepCount++;
      }

      // Limpiar la lista de pasos
      list_clean(stepsList);
      
      stack_clean(stack);
      free(node);
      return;
    }

    // Obtener nodos adyacentes y agregarlos a la pila
    List *adjNodes = getAdjNodes(currentNode);
    void *aux = list_first(adjNodes);
    while(aux != NULL){
      stack_push(stack, aux);
      aux = list_next(adjNodes);
    }
    list_clean(adjNodes);
    count++;
  }
  printf("No se encontró la solución dentro del rango limitado.\n");
  stack_clean(stack);
}
// Función de búsqueda en anchura (BFS)
void bfs(State initialState, int count){
  limpiarPantalla();
  Queue* queue = queue_create(queue);
  puts("========================================");
  puts("     Búsqueda en Anchura");
  puts("========================================");
  puts("");
  printf("Initial State:\n\n");
  imprimirEstado(&initialState);
  printf("\n");

  Node *root = (Node *) malloc(sizeof(Node ));
  root->parent = NULL;
  root->state = initialState;
  queue_insert(queue, root);

  // Bucle de búsqueda en anchura
  while(list_size(queue) > 0){
    Node *currentNode = (Node *) queue_front(queue);
    queue_remove(queue);

    // Limitar el número de iteraciones
    if(count >= 15000000){
      printf("Process terminated: Iteration limit reached (15.000.000)\n");
      return;
    }

    // Verificar si el estado actual es el estado final
    if(isFinal(&currentNode->state)){
      printf("¡Puzzle resuelto!\n");
      printf("Iteraciones: %d\n\n", count);
      Node *node = currentNode;
      int steps = currentNode->state.numActions;

      List *stepsList = list_create();
      Node *currentStep = currentNode;
      while (currentStep != NULL) {
          list_pushFront(stepsList, &currentStep->state);
          currentStep = currentStep->parent;
      }

      // Imprime los pasos en orden inverso
      Node *stepToPrint = list_first(stepsList);
      int stepCount = 0;
      while (stepToPrint != NULL) {
          printf("Paso %d:\n\n", stepCount);
          imprimirEstado(&stepToPrint->state);
          printf("\n");
          stepToPrint = list_next(stepsList);
          stepCount++;
      }

      // Limpia la lista de pasos
      list_clean(stepsList);

      queue_clean(queue);
      free(node);
      return;
    }

    List *adjNodes = getAdjNodes(currentNode);
    void *aux = list_first(adjNodes);
    while(aux != NULL){
      queue_insert(queue, aux);
      aux = list_next(adjNodes);
    }
    list_clean(adjNodes);
    count++;
  }
  printf("La solucion no fue encontrada.\n");
  queue_clean(queue);
}
// Función que calcula la distancia de Manhattan para un estado dado
int manhattanDistance(State *state) {
  int distance = 0;
  for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
          int value = state->square[i][j];
          if (value != 0) {
              int targetRow = (value - 1) / 3;
              int targetCol = (value - 1) % 3;
              distance += abs(i - targetRow) + abs(j - targetCol);
          }
      }
  }
  return distance;
}
// Función que obtiene el uso de memoria
long getMemoryUsage() {
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  return usage.ru_maxrss * 1024; // Devuelve la memoria máxima utilizada en bytes
}
// Función de búsqueda en profundidad iterativa primero el mejor
void best_first(State initialState){
  limpiarPantalla();
  puts("========================================");
  puts("     Buscar Mejor Primero");
  puts("========================================");
  puts("");
  printf("Initial State:\n\n");
  imprimirEstado(&initialState);
  printf("\n");
  int depth_limit = 1;
  int count = 0;
  List *stateList = list_create(); // Lista para almacenar los estados en orden inverso

  while(1){
    Heap *pq = heap_create();
    Node *root = (Node *)malloc(sizeof(Node));
    root->parent = NULL;
    root->state = initialState;
    heap_push(pq, root, manhattanDistance(&root->state));

    while(pq->size > 0){
      Node *currentNode = (Node *)heap_top(pq);
      heap_pop(pq);

      if(getMemoryUsage() > 1024 * 1024 * 1024){ // 1 GB de límite de memoria
        printf("No se pudo encontrar la solución dentro de los límites de memoria.\n");
        heap_clean(pq);
        free(currentNode);
        list_clean(stateList); // Limpiar la lista antes de salir
        return;
      }

      if(isFinal(&currentNode->state)){
        printf("¡Puzzle resuelto!\n");
        printf("Iteraciones: %d\n\n", count);
        Node *node = currentNode;

        // Almacena los estados en orden inverso en la lista
        while(node != NULL){
          list_pushFront(stateList, &node->state);
          node = node->parent;
        }

        // Imprime los estados en orden inverso desde el estado final hasta el estado inicial
        node = list_first(stateList);
        while(node != NULL){
          printf("Paso %d:\n\n", node->state.numActions);
          imprimirEstado(&node->state);
          printf("\n");
          node = list_next(stateList);
        }

        heap_clean(pq);
        free(node);
        list_clean(stateList); // Limpiar la lista antes de salir
        return;
      }

      if(currentNode->state.numActions < depth_limit){
        List *adjNodes = getAdjNodes(currentNode);
        void *aux = list_first(adjNodes);
        while(aux != NULL){
          Node *adjNode = (Node *)aux;
          heap_push(pq, adjNode, manhattanDistance(&adjNode->state) + adjNode->state.numActions);
          aux = list_next(adjNodes);
        }
        list_clean(adjNodes);
      }
      else
        free(currentNode);
      count++;
    }
    depth_limit++;
  }
}

int main(){
  State estado_inicial = {
    {{0, 2, 8}, // Primera fila (0 representa espacio vacío)
    {1, 3, 4}, // Segunda fila
    {6, 5, 7}, // Tercera fila
    },
    0, 0   // Posición del espacio vacío (fila 0, columna 1)
  };

  estado_inicial.numActions = 0;

  int opcion;
  int cont = 0;
  do{
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %d", &opcion);

    switch(opcion){
      case 1:
        dfs(estado_inicial, cont); // funcion para busqueda por profundidad
        break;
      case 2:
        bfs(estado_inicial, cont); // funcion para busqueda por anchura
        break;
      case 3:
        best_first(estado_inicial); // funcion para busqueda por profundidad iterativa
        break;
      case 4:
        printf("Saliendo del programa...\n");
        break;
    }
    presioneTeclaParaContinuar();
    limpiarPantalla();
  } while (opcion != 4);
  return 0;
}