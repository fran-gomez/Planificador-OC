
#include <stdio.h>
#include <stdlib.h>

#include "colacp.h"
#include "const.h"

static int (*comparar)(TEntrada e1, TEntrada e2);

TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)){
    comparar = f;
    TColaCP cola = malloc(sizeof(struct cola_con_prioridad));

    if (cola != NULL) {
		cola->cantidad_elementos = 0;
		cola->raiz = NULL;
    }

    return cola;
};

/**
 * @brief Ordena el nodo pasado por parametro en la cola/heap, desde desde su posicion ("abajo") hasta "arriba"
 * @param cola Cola en la cual se ordenara el nodo
 * @param nodo Nodo que se va a ordenar
 */
void ordenarHaciaArriba(TColaCP cola, TNodo nodo){
    if(nodo != cola->raiz){
        int comp = comparar(nodo->entrada, nodo->padre->entrada);
        if(comp == 1){
            TEntrada entradaAux = nodo->entrada;
            nodo->entrada = nodo->padre->entrada;
            nodo->padre->entrada = entradaAux;
            ordenarHaciaArriba(cola,nodo->padre);
        }
    }
}

/**
 * @brief Insera el nodo pasado por parametro en la ultima posicion n de la cola con prioridad
 * @param cola Cola en la cual se insertara el nodo
 * @param n posicion en la que se insertara el nodo
 * @return nodoNuevo retorna el nodo insertado
 */
TNodo insertarAux(TColaCP cola, TNodo nodoNuevo,int n){
    TNodo pos;
    if( n == 1){
        return cola->raiz;
    }else{
        pos = insertarAux(cola,nodoNuevo, n/2);
        if(n == cola->cantidad_elementos){
            if(n % 2 == 0){
                pos->hijo_izquierdo = nodoNuevo;
            }else{
                pos->hijo_derecho = nodoNuevo;
            }
            nodoNuevo->padre = pos;
        }else{
            if(n % 2 == 0){
                return pos->hijo_izquierdo;
            }else{
                return pos->hijo_derecho;
            }
        }
    }

    return nodoNuevo;
}

int cp_insertar(TColaCP cola, TEntrada entrada){
    cola->cantidad_elementos = cola->cantidad_elementos +1;

    //Se crea el nodo a insertar
    TNodo nodoNuevo = malloc(sizeof(struct nodo));
    nodoNuevo->entrada = entrada;
    nodoNuevo->hijo_derecho = NULL;
    nodoNuevo->hijo_izquierdo = NULL;
    nodoNuevo->padre = NULL;

    if(cola->cantidad_elementos == 1){
        cola->raiz = nodoNuevo;
    }else{
        insertarAux(cola, nodoNuevo, cola->cantidad_elementos);
        ordenarHaciaArriba(cola,nodoNuevo);
    }
    return TRUE;
};


/**
 * @brief Encuentra el ultimo nodo (el nodo de menor prioridad) de la cola con prioridad.
 * @param cola Cola en la cual se buscara el nodo.
 * @param n posicion del ultimo nodo en la cola.
 */
TNodo encontrarUltimoNodo(TColaCP cola, int n){
    TNodo pos;
    if( n == 1){
        pos = cola->raiz;
    }else{
        pos = encontrarUltimoNodo(cola, n/2);
        if(n == cola->cantidad_elementos){
            if(n % 2 == 0){
                pos = pos->hijo_izquierdo;
            }else{
                pos = pos->hijo_derecho;
            }
        }else{
            if(n % 2 == 0){
                pos = pos->hijo_izquierdo;
            }else{
                pos = pos->hijo_derecho;
            }
        }
    }
    return pos;
}

/**
 *@brief ordena el nodo pasado por parametro desde su posicion ("arriba") hacia "abajo" en la cola.
 *@param nodo Nodo que se va a ordenar.
 */
void ordenarHaciaAbajo(TNodo nodo){
    //mayorPrioridad va a ser el nodo que tenga mas prioridad entre: nodo, el hijo hizquierdo de nodo y el hijo derecho de nodo.
    TNodo mayorPrioridad;

    //si nodo tiene hijo izquierdo:
    if(nodo->hijo_izquierdo != NULL){
        int comp1 = comparar(nodo->entrada, nodo->hijo_izquierdo->entrada);

        //si nodo tiene hijo izquierdo y derecho:
        if(nodo->hijo_derecho != NULL){
            int comp2 = comparar(nodo->entrada, nodo->hijo_derecho->entrada);

            //si el hijo izquierdo y el derecho tienen mas prioridad que "nodo":
            if(comp1 == -1 && comp2 == -1){
                //comparo cual es el hijo con mayor prioridad:
                int comp3 = comparar(nodo->hijo_izquierdo->entrada, nodo->hijo_derecho->entrada);
                if(comp3 != -1){
                    mayorPrioridad = nodo->hijo_izquierdo;
                }else{
                    mayorPrioridad = nodo->hijo_derecho;
                }
            }else{
                //si solo el hijo izquierdo tiene mas prioridad que nodo:
                if(comp1 == -1){
                    mayorPrioridad = nodo->hijo_izquierdo;
                }else{
                    //si solo el hijo derecho tiene mas prioridad que nodo:
                    if(comp2 == -1){
                        mayorPrioridad = nodo->hijo_derecho;
                    }else{//si ninguno de los hijos tiene mas prioridad que nodo:
                        mayorPrioridad = nodo;
                    }
                }
            }
        }else{//si solo tiene hijo izquierdo
            //si el hijo izquierdo de nodo tiene mas prioridad que nodo (si no tiene hijo izquierdo no puede tener derecho tampoco):
            if(comp1 == -1){
                    mayorPrioridad = nodo->hijo_izquierdo;
            }else{
                mayorPrioridad = nodo;
            }
        }
    }else{//si nodo no tiene hijos:
        mayorPrioridad = nodo;
    }

    if(mayorPrioridad != nodo){
        TEntrada entradaAux = nodo->entrada;
        nodo->entrada = mayorPrioridad->entrada;
        mayorPrioridad->entrada = entradaAux;
        ordenarHaciaAbajo(mayorPrioridad);
    }

}

TEntrada cp_eliminar(TColaCP cola) {
    if(cola->cantidad_elementos == 0){
        return ELE_NULO;
    }
    //encontramos el ultimo elemento de la cola
    TNodo nodo = encontrarUltimoNodo(cola,cola->cantidad_elementos);
    cola->cantidad_elementos--;
    TEntrada entradaEliminada;

    //reemplazamos el nodo por la raiz de la cola
    if(nodo != cola->raiz){
        //Ponemos el ultimo elemento en la posicion de la raiz
        entradaEliminada = cola->raiz->entrada;
        cola->raiz->entrada = nodo->entrada;

        //si nodo es hijo izquierdo
        if(nodo->padre->hijo_izquierdo == nodo){
            nodo->padre->hijo_izquierdo = NULL;

        }else{//si "nodo" es hijo derecho
            nodo->padre->hijo_derecho = NULL;
        }
        ordenarHaciaAbajo(cola->raiz);
    }else
        entradaEliminada = cola->raiz->entrada;


    free(nodo);
    return entradaEliminada;
}





int cp_size(TColaCP cola){
    return cola->cantidad_elementos;
};

void destruir(TNodo nodo){
    if(nodo->hijo_izquierdo != NULL){
        destruir(nodo->hijo_izquierdo);
        if(nodo->hijo_derecho != NULL){
            destruir(nodo->hijo_derecho);
        }
    }
    free(nodo);
};


int cp_destruir(TColaCP cola){
	if (cola != NULL)
		destruir(cola->raiz);
    free(cola);

    return TRUE;
};
