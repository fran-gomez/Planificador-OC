

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
 * Crea una nueva lista vacia
 */
TLista crear_lista();

/**
 * Elimina la lista elemento a elemento
 * Retorna verdadero si pudo eliminarla, falso en caso contrario
 */
int l_destruir(TLista *lista);

/**
 * Inserta el elemento en la posicion pos (Si esta es nula, lo agrega al principio
 */
int l_insertar(TLista *lista, TPosicion pos, TElemento elem);

/**
 * Elimina la posicion de la lista
 */
int l_eliminar(TLista *lista, TPosicion pos);

/**
 * Retorna la primer posicion de la lista
 */
TPosicion l_primera(TLista lista);

/**
 * Retorna la ultima posicion de la lista
 */
TPosicion l_ultima(TLista lista);

/**
 * Retorna el antecesor de la posicion pos
 */
TPosicion l_anterior(TLista lista, TPosicion pos);

/**
 * Retorna el sucesor de la posicion pos
 */
TPosicion l_siguiente(TLista lista, TPosicion pos);

/**
 * Retorna el elemento almacenado en pos
 */
TElemento l_recuperar(TLista lista, TPosicion pos);


/**
 * Consulta la cantidad de elementos en la lista
 */
int l_size(TLista lista);

