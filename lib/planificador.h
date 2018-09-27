#include <stdio.h>

#include "colacp.h"

/**
 * @attr x Coordenada x
 * @attr y Coordenada y
 */
struct punto {
	float x;
	float y;
};

/**
 * @attr nombre Nombre de la ciudad
 * @attr pos_x Coordenada X de la ciudad
 * @attr pos_y Coordenada Y de la ciudad
 */
typedef struct ciudad {
	char *nombre;
	float pos_x;
	float pos_y;
} * TCiudad;


/**
 * @brief Muestra el menu de opciones del planificador
 * @return Caracter identificador de la opcion elegida
 */
char mostrar_menu();

/**
 * @brief Muestra las ciudades en un orden determinado
 * @param fp Archivo con los destinos a visitar
 * @param comp Funcion de comparacion de entradas
 */
void mostrar(FILE *fp, int(*comp)(TEntrada, TEntrada));

/**
 * @brief Muestra el camino mas corto desde la posicion actual pasando
 * por todos los destinos
 * @param fp Archivo con los destinos a visitar
 */
float reducir_horas_manejo(FILE *fp);

/**
 * @brief Sale del programa
 */
void salir(void);
