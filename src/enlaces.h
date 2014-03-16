/**
 *	PROYECTO: ESTRUCTURAS DIN�MICAS
 *	FUNDAMENTOS DE LA PROGRAMACI�N II
 *
 *	Archivo:		enlaces.h
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creaci�n:	17/02/2013 13:30
 *	�ltima modif.:	19/04/2013 13:45
 */

#ifndef	__DEF_ENL__
#define	__DEF_ENL__

/**
 * Declaraci�n de prototipos de funciones
 */
// Crea un enlace vac�o de datos
enlace * creaEnlace();

// Inserta un enlace en la lista de enlaces
void insertaEnlace(enlace * e, enlace ** pe);

// Configura un enlace, devuelve 1 si todo ha ido bien, 0 e.c.c.
int configuraEnlace(nodo * origen, nodo * destino, enlace ** h, enlace ** e);

// Devuelve el peso de un enlace
int consiguePesoDeEnlace(nodo * origen, nodo * destino, enlace * enlaces);

// Comprueba si existe un enlace
int existeEnlace(enlace * e, enlace * h);

// Comprueba si dos enlaces son los mismos
int mismoEnlace(enlace * e, enlace * h);

// Libera toda una lista de enlaces
void liberaEnlaces(enlace ** pe);

// Libera un enlace individual
void liberaEnlace(enlace ** pe);

#endif
