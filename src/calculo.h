/**
 *	PROYECTO: ESTRUCTURAS DIN�MICAS
 *	FUNDAMENTOS DE LA PROGRAMACI�N II
 *
 *	Archivo:		calculo.h
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creaci�n:	17/02/2013 18:42
 *	�ltima modif.:	19/04/2013 13:45
 */
 
#ifndef __DEF_CALC__
#define __DEF_CALC__

/**
 * Declaraci�n de prototipos de funciones
 */
// Realiza el c�lculo de coste entre todos los caminos posibles
void calculoCaminos(nodo * inicial, nodo ** pp, enlace ** uv);

// Calcula el camino �ptima entre dos nodos
int caminoOptimo(nodo * inicial, nodo ** final);

#endif
