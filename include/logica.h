/*************************************************************************************
*
* @Proposito: Cabecera de logica.c que contiene los tipos necesarios para crear
* la lista y las cabeceras de las funciones que se van a usar.
* @Fecha creacion: 2 de Junio de 2018
* @Fecha ultima modificacion: 19 de Junio 2018
*
**************************************************************************************/

#ifndef _LOGICA_H_
#define _LOGICA_H_

#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "../include/listaPDI.h"

#define MAXCAD 100
#define MAXPALABRAS 40
#define MAXFICHEROS 50 

#define TRUE 1
#define FALSE 0

typedef char Cadena[MAXCAD];

typedef struct {
    Cadena nombre_fichero;
    ListaPDI palabras;
} Fichero;


void checkPunctuation (char *cad);
int checkNumber (char *c);
int cargarDocumentos (Fichero ficheros[MAXFICHEROS]);
int validarOpcion (Cadena opcion);
ListaPDI extraePalabras (Cadena palabras);
void encontrarDocumento (ListaPDI lista_palabra, Fichero ficheros);
int buscarFrase (char frase[MAXCAD], Fichero ficheros);

#endif
