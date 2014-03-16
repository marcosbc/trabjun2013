/**
 *	PROYECTO: ESTRUCTURAS DINÁMICAS
 *	FUNDAMENTOS DE LA PROGRAMACIÓN II
 *
 *	Archivo:		enlaces.c
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creación:	17/02/2013 13:30
 *	Última modif.:	19/04/2013 13:45
 *	Explicación:	Contiene todas las funciones
 *					relativas al manejo de enlaces
 */

/* Ficheros de inclusión del sistema */
#include <stdio.h>
#include <stdlib.h>

/* Ficheros de inclusión locales */
#include "principal.h"
#include "nodos.h"
#include "enlaces.h"
#include "miscelaneos.h"

// Crea un enlace vacío de datos
enlace * creaEnlace()
{
	enlace * e = NULL;
	
	// Reservamos la memoria
	e = (enlace *) malloc(sizeof(enlace));
	
	if(e != NULL)
	{
		// Asignamos valores por defecto
		e->origen = NULL;
		e->destino = NULL;
		
		// El enlace siguiente para recorrer se inicia a NULL
		e->sig = NULL;
	}

	return e;
}

// Inserta un enlace en la lista de enlaces
void insertaEnlace(enlace * e, enlace ** pe)
{
	// Recorrer hasta llegar al último elemento
	while(*pe != NULL)
	{
		pe = &((*pe)->sig);
	}
	
	// Asignar
	*pe = e;
}


// Configura un enlace, devuelve 1 si todo ha ido bien, 0 e.c.c.
int configuraEnlace(nodo * origen, nodo * destino,
					enlace ** h, enlace ** e)
{
	// Se activa si el enlace es válido
	int enlaceOK = 0;
	
	// Comprueba si ya existe un enlace con las mismas IPs
	// y que estas y el coste son correctos
	if(ipCorrecta(origen->ip) && ipCorrecta(destino->ip)
	   && ! menorOMayor(MIN_COSTE, MAX_COSTE, (*e)->peso))
	{
		// Asignar el origen y destino
		(*e)->origen = origen;
		(*e)->destino = destino;
	
		// Comprobar si el enlace existe
		if(! existeEnlace(*e, *h))
		{
			// No existe: Procederemos a insertarlo
			insertaEnlace(*e, h);

			// Si no existe, todo va bien, si se diese el caso
			// de existir, ERROR
			enlaceOK = 1;
		}
	}
	
	return enlaceOK;
}

// Devuelve el peso de un enlace
int consiguePesoDeEnlace(nodo * origen, nodo * destino, enlace * enlaces)
{
	// Iniciamos con un peso infinito
	int peso = -1;
	
	// Si estamos en el primer nodo, peso 0
	if(origen == NULL && destino != NULL)
		peso = 0;

	while(enlaces != NULL && peso < 0)
	{
		if(mismaIP(enlaces->origen->ip, origen->ip)
		   && mismaIP(enlaces->destino->ip, destino->ip))
			peso = enlaces->peso;
		else
			enlaces = enlaces->sig;
	}

	return peso;
}

// Comprueba si existe un enlace (sus nodos origen-destino coinciden)
int existeEnlace(enlace * e, enlace * h)
{
	int existe = 0;
	
	// Recorrer hasta encontrar el enlace
	while(h != NULL && ! existe)
	{
		// Si lo hemos encontrado, paramos: Existe el enlace
		if(mismoEnlace(e, h))
		{
			existe = 1;
		}
		else
		{
			h = h->sig;
		}
	}
	
	return existe;
}

// Comprueba si dos enlaces son los mismos (sus nodos
// origen-destino coinciden)
int mismoEnlace(enlace * e, enlace * h)
{
	int res = 1;

	if(e == NULL || h == NULL)
		res = 0;
	else
		res = (mismaIP(e->origen->ip, h->origen->ip)
			   && mismaIP(e->destino->ip, h->destino->ip));

	return res;
}

// Libera toda una lista de enlaces
void liberaEnlaces(enlace ** pe)
{
	enlace * eaux = NULL;
	
	while(*pe != NULL)
	{
		eaux = *pe;
		*pe = eaux->sig;
		free(eaux);
	}
}