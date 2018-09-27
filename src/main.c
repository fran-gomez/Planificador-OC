/*
 * main.c
 *
 *  Created on: Sep 12, 2018
 *      Author: user
 */
#include <stdio.h>

#include "../lib/planificador.h"
#include "../lib/const.h"

int (*orden_ascendente)(TEntrada, TEntrada);
int (*orden_descendente)(TEntrada, TEntrada);

int main(int argc, char **argv) {

	char op;
	FILE *fp;

	if (argc != 2) {
		fprintf(stderr, "Error.Invocacion invalida.\n"
				"\t\tplanificador <archivo_texto>\n");
		return BAD_ARGS;
	}

	op = mostrar_menu();

	fp = fopen(*argv[1], 'r');
	if (!fp)
		return FILE_ERR;

	orden_ascendente = ascendente;
	orden_descendente = descendente;

	switch (op) {
	case '1': // Mostrar ascendente
		mostrar(fp, orden_ascendente);
		break;
	case '2': // Mostrar descendente
		mostrar(fp, orden_descendente);
		break;
	case '3': // Reducir horas de manejo
		reducir_horas_manejo(fp);
		break;
	case '4':
		salir();
		break;
	default:
		fprintf(stderr, "Error. Operacion invalida.\n");
		return BAD_ARGS;
	}

	fclose(fp);

	return 0;
}

int ascendente(TEntrada t1, TEntrada t2) {
	int val = 0;

	if (*t1->clave < *t2->clave)
		val = -1;
	else if (*t1->clave > *t2->clave)
		val = 1;

	return val;
}

int descendente(TEntrada t1, TEntrada t2) {
	return -ascendente(t1, t2);
}
