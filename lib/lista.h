#ifndef LISTA_H
#define LISTA_H

typedef void * TElemento;

/**
 * Estructura de almacenamiento de informacion de la lista
 */
struct celda {

	TElemento elemento;
	struct celda *celda_anterior;
	struct celda *celda_siguiente;
};

typedef struct celda * TLista;
typedef struct celda * TPosicion;


/**
 * @brief Crea una nueva lista vacia
 * @return Lista vacia
 */
TLista crear_lista();

/**
 * @brief Elimina la lista elemento a elemento
 * @param lista Lista a destruir
 * @return Verdadero si pudo eliminarla, falso en caso contrario
 */
int l_destruir(TLista *lista);

/**
 * @brief Inserta el elemento en la posicion pos
 * @param lista Lista a insertarle el elemento
 * @param pos Posicion de referencia (Si es nula, insertamos al principio)
 * @elem ELemento a insertar
 * @return Verdadero si pudo  insertar, falso en caso contrario
 */
int l_insertar(TLista *lista, TPosicion pos, TElemento elem);

/**
 * @brief Elimina la posicion de la lista
 * @param lista Lista a eliminrle la posicion
 * @param pos Posicion a eliminar
 * @return Verdadero si pudo  insertar, falso en caso contrario
 */
int l_eliminar(TLista *lista, TPosicion pos);

/**
 * @brief Retorna la primer posicion de la lista
 * @param lista Lista a consultar su primer elemento
 * @return Posicion del primer elemento
 */
TPosicion l_primera(TLista lista);

/**
 * @brief Retorna la ultima posicion de la lista
 * @param lista Lista a consultar su primer elemento
 * @return Posicin del ultimo elemento
 */
TPosicion l_ultima(TLista lista);

/**
 * @brief Retorna el antecesor de la posicion pos
 * @param lista Lista contenedora
 * @param pos Posicion de referencia
 * @return Posicion del predecesor
 */
TPosicion l_anterior(TLista lista, TPosicion pos);

/**
 * @brief Retorna el sucesor de la posicion pos
 * @param lista Lista contenedora
 * @param pos Posicion de referencia
 * @return Posicion del sucesor
 */
TPosicion l_siguiente(TLista lista, TPosicion pos);

/**
 * @brief Retorna el elemento almacenado en pos
 * @param lista Lista contenedora
 * @param pos Posicion de referencia
 * @return Elemento almacenado en la posicion
 */
TElemento l_recuperar(TLista lista, TPosicion pos);


/**
 * @brief Consulta la cantidad de elementos en la lista
 * @param lista Lista de referencia
 * @return Cantidad de elementos de la lista
 */
int l_size(TLista lista);

#endif
