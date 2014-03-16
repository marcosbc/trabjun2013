/**
 *	PROYECTO: ESTRUCTURAS DINÁMICAS
 *	FUNDAMENTOS DE LA PROGRAMACIÓN II
 *
 *	Archivo:		nodos.c
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creación:	17/02/2013 13:30
 *	Última modif.:	19/04/2013 13:50
 *	Explicación:	Contiene todas las funciones
 *					relativas al manejo de nodos
 */
/* Ficheros de inclusión del sistema */
#include <stdio.h>
#include <stdlib.h>

/* Ficheros de inclusión locales */
#include "principal.h"
#include "nodos.h"
#include "miscelaneos.h"

// Crea un nodo vacío de datos
nodo * creaNodo()
{
	nodo * p = NULL;
	
	// Reservamos la memoria
	p = (nodo *) malloc(sizeof(nodo));
	
	if(p != NULL)
	{
		// Asignamos valores por defecto
		// p->coste no se asigna pues lo será en calculoCamino
		p->pred = NULL;
		p->sigEnganche = NULL;
		p->sig = NULL;
	}
	
	return p;
}

// Comprueba si dos nodos son iguales
int nodosSonIguales(nodo * p, nodo * q)
{
	// Sus IPs deben coincidir
	return mismaIP(p->ip, q->ip);
}

// Devuelve el puntero de un nodo encontrado según la IP
nodo * buscaNodo(direccion ip, nodo ** nodos)
{
	int encontrado = 0;
	
	// Recorrer hasta encontrar el nodo
	while(*nodos != NULL && ! encontrado)
	{
		// Parar si hemos encontrado el nodo
		if(mismaIP(ip, (*nodos)->ip))
			encontrado = 1;
		// Pasar al siguiente elemento si no
		else
			nodos = &((*nodos)->sigEnganche);
	}
	
	return *nodos;
}

// Inserta un nodo en el arbol (nodo->pred)
void insertaEnArbol(nodo * h, nodo * p)
{
	if (h != NULL)
	{
		h->pred = p;
	}
}

// Inserta un nodo en la lista de enganches
void insertaEnganche(nodo * p, nodo ** pp)
{
	// Recorrer hasta llegar al último elemento
	while(*pp != NULL)
	{
		pp = &((*pp)->sigEnganche);
	}
	
	// Asignar
	*pp = p;
}

// Libera toda una lista de enganches
void liberaLista(nodo ** pp)
{
	nodo *paux = NULL;
	
	while (*pp != NULL)
	{
		paux = *pp;
		*pp = paux->sigEnganche;
		
		liberaNodo(&paux);
	}
}

// Libera un nodo individual
void liberaNodo(nodo ** pp)
{
	free(*pp);
	pp = NULL;
}

// Inserta un paso de la solución final (teniendo en cuenta que
// inserta el paso tal que el siguiente paso es el inicial)
void insertaPasoDeSolucion(nodo ** pp, nodo ** pq)
{
	if(*pq != NULL)
	{
		(*pp)->sig = (*pq)->sig;

		(*pq)->sig = *pp;
	}
}

// Inserta un nodo o no en la lista de todos los nodos, según
// condiciones (p. ej., está duplicado: sus IPs coinciden)
void manejaNodo(nodo ** pp, nodo ** pq)
{
	int encontrado = 0;

	// Recorrer hasta encontrar el nodo
	while(*pq != NULL && ! encontrado)
	{
		if(nodosSonIguales(*pp, *pq))
		{
			encontrado = 1;
		}
		else
		{
			pq = &((*pq)->sigEnganche);
		}
	}
	
	// Si se ha encontrado, liberar de la memoria y cambiar
	// el puntero del nodo recientemente creado
	if(encontrado)
	{
		// Lo liberamos de la memoria
		liberaNodo(pp);
		
		// Cambiamos el puntero a que sea el del nodo encontrado
		*pp = *pq;
	}
	
	// Si no se ha encontrado, enlazar en la lista completa
	else
	{
		insertaEnganche(*pp, pq);
	}
}

// Inserta una IP en un nodo, si la IP es correcta
int insertaIPEnNodo(char * ip, int tam, nodo ** p)
{
	int correctas = 0;
	
	if(*p != NULL)
	{
		// Comprobar si se puede usar con sscanf
		correctas = ipStringComprobable(ip, tam);
		
		if(correctas)
		{
			correctas =
				4 == sscanf(ip, "%d.%d.%d.%d",
						// Para el primer nodo (la IP origen)
						&((*p)->ip[0]), &((*p)->ip[1]),
						&((*p)->ip[2]), &((*p)->ip[3]));
		}
	}
	
	return correctas;
}