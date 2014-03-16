/**
 *	PROYECTO: ESTRUCTURAS DIN�MICAS
 *	FUNDAMENTOS DE LA PROGRAMACI�N II
 *
 *	Archivo:		calculo.c
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creaci�n:	17/02/2013 18:42
 *	�ltima modif.:	19/04/2013 13:45
 *	Explicaci�n:	Contiene todas las funciones relativas
 *					a las funciones de c�lculo de caminos
 */
/* Ficheros de inclusi�n del sistema */
#include <stdio.h>

/* Ficheros de inclusi�n locales */
#include "principal.h"
#include "calculo.h"
#include "nodos.h"

// Realiza el c�lculo de coste entre todos los caminos posibles
void calculoCaminos(nodo * inicial, nodo ** pp, enlace ** enlaces)
{
	// Declaraci�n de variables para el paso 1
	int recorrer = 1;
	int numNodos = 0;
	int i;
	enlace ** uv = NULL;

	
	// Declaraci�n de los nodos para el paso 2
	nodo * u = NULL;
	nodo * v = NULL;
	
	/*
	 * PASO 1: INICIALIZACI�N
	 */
	// Recorrer la lista de los nodos
	while(recorrer)
	{
		numNodos++;
		if(*pp == inicial)
			// Estamos ante el nodo inicial: Coste 0
			(*pp)->coste = 0;
		else
			// No es el primer nodo: Coste infinito
			(*pp)->coste = COSTE_INFINITO;
		
		(*pp)->pred = NULL;
		
		// No recorrer si hemos llegado al �ltimo nodo
		if((*pp)->sigEnganche == NULL)
			recorrer = 0;
		else
			pp = &((*pp)->sigEnganche);
	}
	
	/*
	 * PASO 2: ALGORITMO DE C�LCULO DE RUTAS
	 */
	
	// Recorrer n_nodos - 1 veces
	for(i = 1; i < numNodos; i++)
	{
		// Reasignamos el valor inicial de uv
		uv = enlaces;
		
		// Recorrer todos los enlaces
		while(*uv != NULL)
		{
			// Sea u un nodo origen que se encuentra en el
			// elemento j de la tabla de nodos como origen

			u = (*uv)->origen;
			
			// Sea v un nodo destino que se encuentra en el
			// elemento j de la tabla de nodos como destino
			v = (*uv)->destino;
			
			// Si el coste en v es mayor, actualizar:
			// Conseguimos as� el coste m�nimo

			if((u->coste + (*uv)->peso) < v->coste)
			{
				v->coste = u->coste + (*uv)->peso;
				v->pred = u;
			}

			uv = &((*uv)->sig);
		}
	}
}

// Calcula el camino �ptimo entre dos nodos
int caminoOptimo(nodo * inicial, nodo ** final)
{
	int haySolucion = 0;

	// Si hay soluci�n, seguimos
	if((*final)->pred != NULL)
	{
		// Recorrer la lista para conseguir el camino
		// El camino se conseguir� de forma inversa as� que
		// lo insertaremos inversamente
		while(final != NULL && ! haySolucion)
		{
			if(*final == inicial)
			{
				haySolucion = 1;
			}
			else
			{
				// Insertar el paso anterior de la solucion
				insertaPasoDeSolucion(final, &inicial);

				final = &((*final)->pred);
			}
		}
	}

	return haySolucion;
}
