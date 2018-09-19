
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

TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada));
int cp_destruir(TColaCP cola);

int cp_insertar(TColaCP cola, TEntrada entr);
TEntrada cp_eliminar(TColaCP cola);

int cp_size(TColaCP cola);

