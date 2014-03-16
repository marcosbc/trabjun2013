/**
 *	PROYECTO: ESTRUCTURAS DIN�MICAS
 *	FUNDAMENTOS DE LA PROGRAMACI�N II
 *
 *	Archivo:		miscelaneos.c
 *	Autor:			Marcos Bjorkelund (login: marbjo1)
 *	Fecha creaci�n:	17/04/2013 19:31
 *	�ltima modif.:	19/04/2013 13:52
 *	Explicaci�n:	Contiene funciones miscel�neas
 */
#include <stdio.h>

/* Ficheros de inclusi�n locales */
#include "principal.h"
#include "miscelaneos.h"


// Comprueba si una IP es correcta (seg�n el rango de cada �ndice)
int ipCorrecta(direccion ip)
{
	return (! menorOMayor(MIN_IP, MAX_IP, ip[0])
			&& ! menorOMayor(MIN_IP, MAX_IP, ip[1])
			&& ! menorOMayor(MIN_IP, MAX_IP, ip[2])
			&& ! menorOMayor(MIN_IP, MAX_IP, ip[3]));
}

// Comprueba si una IP en formato cadena se puede comprobar,
// es decir, si no tiene errores que, en nuestro programa, podr�an
// entrar en conflicto con sscanf
int ipStringComprobable(char * ip, int tam)
{
	int ret = 0;				// Valor de retorno
	int i = 0;					// El iterador, comienza en 1
	int contadorPuntos = 0;		// Contador de puntos ('.')
	int error = 0;				// Bandera de error
	int anteriorEsPunto = 0;	// Si el anterior char fue punto ('.')
	int carDespuesDePunto = 0;	// N�mero de chars despu�s de punto
	
	if(ip != NULL)
	{
		// Comprobar que el primer n�mero es un n�mero entero
		// de 1 a 9
		if(! menorOMayor('1', '9', ip[i++]))
		{
			// La recorremos comprobando que no hay ning�n caracter
			// extra�o (como un espacio, letra, etc.)
			while((i < (tam - 1)) && ! error && ip[i] != '\0')
			{
				// Comprobar si es un caracter inv�lido
				if(ip[i] != '.' && menorOMayor('0', '9', ip[i]))
				{
					error = 1;
				}
				
				// Si estamos en un punto, actualizar los contadores de
				// puntos y dar error si el anterior fue uno
				if(! error && ip[i] == '.')
				{
					if(anteriorEsPunto)
					{
						error = 1;
					}
					
					else
					{
						contadorPuntos++;
					}
				}
				
				// Si no hay error, actualizar contadores de caracteres
				// y comprobar si el actual es punto
				if(! error)
				{
					if(anteriorEsPunto)
					{
						anteriorEsPunto = 0;
						carDespuesDePunto = 1;
					}
				
					else
					{
						if(ip[i] == '.')
						{
							anteriorEsPunto = 1;
						}
					
						carDespuesDePunto++;
					}
				
					if(carDespuesDePunto > 3)
					{
						error = 1;
					}
					i++;
				}
			}
			
			// �ltimas comprobaciones para ver si es correcto
			if(i < tam && ! error)
			{
				if(contadorPuntos == 3 && carDespuesDePunto <= 3)
				{
					ret = 1;
				}
			}
		}
	}
	
	return ret;
}

// Comprueba si dos IPs son las mismas
int mismaIP(direccion ip1, direccion ip2)
{
	return (ip1[0] == ip2[0] && ip1[1] == ip2[1]
			&& ip1[2] == ip2[2] && ip1[3] == ip2[3]);
}

// Devuelve 0 si se encuentra en el rango: n es menor que min o mayor
// que max, 1 en caso contrario
int menorOMayor(int min, int max, int n)
{
	return (n < min || n > max);
}
