/**
 *	PROYECTO: ESTRUCTURAS DIN�MICAS
 *	FUNDAMENTOS DE LA PROGRAMACI�N II
 *
 *	Archivo:		io.h
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creaci�n:	17/02/2013 20:50
 *	�ltima modif.:	19/04/2013 13:51
 */

#ifndef	__DEF_IO__
#define	__DEF_IO__

/**
 * Declaraci�n de prototipos de funciones
 */
// Procesa el fichero de entrada, estableciendo el nodo inicial (origen)
// y el final (destino)
void procesarFichEnt(FILE * fich, nodo * nodos, nodo ** inicial, nodo ** final, int * e);

// Comprueba si el fich. de configuraci�n es correcto y crea los nodos,
// es decir, las IPs que aparezcan en ellos si no se han creado ya
int procesarFichConf(FILE * fich, enlace ** enlaces, nodo ** nodos, int * e);

// Imprime el resultado final: La distancia m�nima entre dos nodos
void salidaFichSal(FILE * fich, nodo * inicial, nodo * final, enlace * enlaces);

// Imprime un error seg�n texto descriptivo e ID. Sigue una estructura b�sica
void imprimirError(int id);

#endif
