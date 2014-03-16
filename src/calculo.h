/**
 *	PROYECTO: ESTRUCTURAS DINÁMICAS
 *	FUNDAMENTOS DE LA PROGRAMACIÓN II
 *
 *	Archivo:		calculo.h
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creación:	17/02/2013 18:42
 *	Última modif.:	19/04/2013 13:45
 */
 
#ifndef __DEF_CALC__
#define __DEF_CALC__

/**
 * Declaración de prototipos de funciones
 */
// Realiza el cálculo de coste entre todos los caminos posibles
void calculoCaminos(nodo * inicial, nodo ** pp, enlace ** uv);

// Calcula el camino óptima entre dos nodos
int caminoOptimo(nodo * inicial, nodo ** final);

#endif
