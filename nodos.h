/**
 *	PROYECTO: ESTRUCTURAS DINÁMICAS
 *	FUNDAMENTOS DE LA PROGRAMACIÓN II
 *
 *	Archivo:		nodos.h
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creación:	17/02/2013 13:30
 *	Última modif.:	19/04/2013 13:50
 */

#ifndef __DEF_NODOS__
#define __DEF_NODOS__

/**
 * Declaración de prototipos de funciones
 */

// Crea un nodo vacío de datos
nodo * creaNodo();

// Comprueba si dos nodos son iguales (sus IPs coinciden)
int nodosSonIguales(nodo * p, nodo * q);

// Devuelve el puntero de un nodo encontrado
nodo * buscaNodo(direccion ip, nodo ** nodos);

// Inserta un nodo en el arbol
void insertaEnArbol(nodo * nuevoPadre, nodo * hijo);

// Inserta un nodo en la lista aditiva de elementos (lista de
// todos los nodos que existen)
void insertaEnLista(nodo * p, nodo ** pp);

// Libera toda una lista
void liberaLista(nodo ** pp);

// Inserta un paso de la solución final
void insertaPasoDeSolucion(nodo ** pp, nodo ** pq);

// Inserta un nodo o no en la lista de todos los nodos, según
// condiciones (p. ej., está duplicado: sus IPs coinciden)
void manejaNodo(nodo ** pp, nodo ** pq);

// Inserta una IP en un nodo
int insertaIPEnNodo(char * ip, int num, nodo ** p);

#endif
