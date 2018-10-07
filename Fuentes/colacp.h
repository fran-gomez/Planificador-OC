

#ifndef COLACP_H
#define COLACP_H
typedef void * TClave;
typedef void * TValor;

typedef struct entrada {
	TClave clave;
	TValor valor;
} *TEntrada;

typedef struct nodo {
	TEntrada entrada;
	struct nodo * padre;
	struct nodo * hijo_izquierdo;
	struct nodo * hijo_derecho;
} *TNodo;

typedef struct cola_con_prioridad {
	unsigned int cantidad_elementos;
	TNodo raiz;
} *TColaCP;

/**
 * @brief Crea una cola con prioridad vacia
 * @param f Funcion de comparcion de entradas
 * @return Heap vacio
 */
TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada));

/**
 * @brief Elimina la cola con prioridad
 * @param cola Cola con prioridad a eliminar
 * @return Verdadero si pudo eliminarla, falso en caso contrario
 */
int cp_destruir(TColaCP cola);

/**
 * @brief Agrega un elemento a la cola con prioridad
 * @param cola Cola a insertar el elemento
 * @param entrada Entrada a agregar
 * @return Verdadero si pudo eliminar, falso en caso contrario
 */
int cp_insertar(TColaCP cola, TEntrada entrada);

/**
 * @brief Elimina el primer elemento de la cola con prioridad
 * @param cola Cola a eliminar su primer elemento
 * @return Entrada en la primer posicion
 */
TEntrada cp_eliminar(TColaCP cola);

/**
 * @brief Consulta la cantidad de elementos de la cola con prioridad
 * @param cola Cola a consultar
 * @return Cantidad de elementos
 */
int cp_size(TColaCP cola);

#endif
