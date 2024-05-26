// Estructura que representa un heap (montículo) con prioridades
typedef struct {
  void **data;     // Arreglo de punteros a los datos almacenados en el heap
  int *priorities; // Arreglo de prioridades correspondientes a los datos
  int capacity;    // Capacidad máxima del heap
  int size;        // Tamaño actual del heap (número de elementos almacenados)
} Heap;

// Función que crea un nuevo heap y retorna un puntero a él
Heap *heap_create();

// Función que inserta un nuevo elemento en el heap con una prioridad dada
void heap_push(Heap *pq, void *data, int priority);

// Función que obtiene el elemento de mayor prioridad en el heap sin eliminarlo
void *heap_top(Heap *pq);

// Función que elimina el elemento de mayor prioridad en el heap
void heap_pop(Heap *pq);

// Función que limpia el heap, eliminando todos sus elementos
void heap_clean(Heap *pq);