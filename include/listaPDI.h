/*************************************************************************************
*
* @Proposito: Cabecera de listaPDI.c que contiene los tipos necesarios para crear
* la lista y las cabeceras de las funciones que se van a usar.
* @Fecha creacion: 2 de Junio de 2018
* @Fecha ultima modificacion: 2 de Junio 2018
*
**************************************************************************************/

#ifndef _LISTAPDI_H_
#define _LISTAPDI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAXCAD 100

typedef struct {
	char *palabra;
	int num_veces;
} Elemento;

typedef struct N {
	Elemento e;
	struct N *sig;
} Nodo;

typedef struct {
	Nodo *pri;
	Nodo *ant;
} ListaPDI;

//Cabecera de las funciones
ListaPDI LISTAPDI_crea ();
void LISTAPDI_inserta (ListaPDI *l, Elemento e);
Elemento LISTAPDI_consulta (ListaPDI l);
void LISTAPDI_avanza (ListaPDI *l);
void LISTAPDI_elimina (ListaPDI *l);
void LISTAPDI_vesInicio (ListaPDI *l);
int LISTAPDI_final (ListaPDI l);
int LISTAPDI_vacia (ListaPDI l);
void LISTAPDI_destruye (ListaPDI *l);
int LISTAPDI_existeElemento (ListaPDI *l, Elemento e);
void LISTAPDI_incrementaVeces (ListaPDI *l, Elemento e);
int LISTAPDI_cuantosElementos (ListaPDI l);
void LISTAPDI_ordenar (ListaPDI *l);
#endif
