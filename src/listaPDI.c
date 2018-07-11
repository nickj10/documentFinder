/*************************************************************************************
*
* @Proposito: Crear una estructura lineal con el que se irá guardando los flags que
* el usuario coloque en una casilla. En caso de eliminarla, también se elimina de 
* la lista. Esta lista tiene un PDI o un Punto de Interés que apunta al nodo anterior
* respecto al nodo que estamos accediendo.
* @Fecha creacion: 2 de Junio de 2018
* @Fecha ultima modificacion: 4 de Junio de 2018
*
**************************************************************************************/

#include "../include/listaPDI.h"

/**************************************************************************************
*
* @Finalidad: Crear la estructura lineal
* @Parametros: No entran parámetros
* @Retorno: Devuelve la lista de palabras creada
*
***************************************************************************************/
ListaPDI LISTAPDI_crea () {
	ListaPDI l;
	l.pri = (Nodo*) malloc (sizeof(Nodo));
	if (l.pri == NULL) {
	    printf ("\nError al crear lista");
	}
	else {
	    l.pri -> sig = NULL;
	    l.ant = l.pri;
	}
	return l;
}

/**************************************************************************************
*
* @Finalidad: Inserir una palabra en la lista junto con el numero de veces
*			que aparece en el documento
* @Parametros:  in: l = la lista pasada por referencia porque vamos a añadir elementos
* 				in: e = el elemento que queremos añadir a la lista
* @Retorno: No devuelve nada.
*
***************************************************************************************/
void LISTAPDI_inserta (ListaPDI *l, Elemento e) {
	Nodo *aux;
	aux = (Nodo*) malloc (sizeof(Nodo)); 
	if (aux == NULL) {
		printf ("\nError al insertar.");
	}
	else {
		aux->e.palabra = (char*)malloc(sizeof(char) * MAXCAD);
		strcpy (aux->e.palabra, e.palabra);
		aux -> e.num_veces = e.num_veces;
		aux -> sig = l -> ant -> sig;
		l -> ant -> sig = aux;
		l -> ant = aux; 
	}
}

/**************************************************************************************
*
* @Finalidad: Indicar si la lista esta vacia.
* @Parametros: in: l = la lista
* @Retorno: Retorna 0 en caso de estar vacia.
*
***************************************************************************************/
int LISTAPDI_vacia (ListaPDI l) {
	return l.pri -> sig == NULL;
}

/**************************************************************************************
*
* @Finalidad: Apuntar al inicio de la lista (apuntará al fantasma) para ver si
*		hay un primer elemento o no.
* @Parametros: in: l = pasada por referencia porque cambiaremos la posicion de los 
* 				   punteros para volver al inicio de la lista.
* @Retorno: No devuelve nada.
*
***************************************************************************************/
void LISTAPDI_vesInicio (ListaPDI *l) {
	l->ant = l->pri;
}

/**************************************************************************************
*
* @Finalidad: Consultar el elemento que estamos accediendo con el PDI.
* @Parametros: in: l = la lista para consultar qué elemento hay.
* @Retorno: Devuelve el elemento que estamos accediendo con el PDI.
* 
***************************************************************************************/
Elemento LISTAPDI_consulta (ListaPDI l) {
	Elemento e;
	
	if (l.ant -> sig == NULL) {
		//e.palabra = NULL;
		e.num_veces = 0;
	}
	else {
		e.palabra = l.ant->sig->e.palabra;
		e.num_veces = l.ant->sig->e.num_veces;
	}
	return e;
}

/**************************************************************************************
*
* @Finalidad: Avanzar la posición del puntero.
* @Parametros: in: l =  la lista pasada por referencia porque avanzamos los punteros
* 				   para ir comprobando elemento por elemento (si hay).
* @Retorno: No devuelve nada.
*
***************************************************************************************/
void LISTAPDI_avanza (ListaPDI *l) {
	if (l->ant-> sig == NULL) {
		printf ("\nError al avanzar. Ya es el final o no hay nada ya en la Lista\n");
	}
	else {
		l->ant = l->ant->sig;
	}
}

/**************************************************************************************
*
* @Finalidad: Indicar si se encuentra a la última posición de la lista.
* @Parametros: in: l = la lista
* @Retorno: Retorna un número distinto de cero si se está accediendo al final de la lista.
*
***************************************************************************************/
int LISTAPDI_final (ListaPDI l) {
	return l.ant -> sig == NULL;
}

/**************************************************************************************
*
* @Finalidad: Eliminar elementos en la lista.
* @Parametros: in: l = lista pasada por referencia porque se eliminaran elementos
* @Retorno: No devuelve nada.
*
***************************************************************************************/
void LISTAPDI_elimina (ListaPDI *l) {
	Nodo *aux;
	
	if (l->ant->sig == NULL) {
		printf ("\nError al eliminar.\n");
	}
	else {
		aux = l->ant->sig;
		l->ant->sig = aux->sig;
		free (aux);
	}
}

/**************************************************************************************
*
* @Finalidad: Destruir la estructura creada.
* @Parametros: in: l = lista pasada por referencia.
* @Retorno: No devuelve nada.
*
***************************************************************************************/
void LISTAPDI_destruye (ListaPDI *l) {
	Nodo *aux;
	while (l -> pri != NULL) {
		aux = l->pri;
		l -> pri = l -> pri -> sig;
		free (aux);
	}
	l->ant = NULL;
}

/**************************************************************************************
*
* @Finalidad: Mirar si existe un elemento dado en la lista.
* @Parametros: in: l = lista pasada por referencia.
*			   in: e_scanear = elemento a buscar en la lista.
* @Retorno: Devuelve un 1 si el elemento existe en la lista y un 0 en caso contrario.
*
***************************************************************************************/
int LISTAPDI_existeElemento (ListaPDI * l, Elemento e_scanear) {
	Elemento e_comparar;
	int encontrado = FALSE;
	if (!LISTAPDI_vacia(*l)) {
		LISTAPDI_vesInicio (l);
		// Irá avanzando hasta encontrar la palabra en la lista o que esté vacia
		while (!LISTAPDI_final(*l) && !encontrado) {
			e_comparar = LISTAPDI_consulta(*l);
			if (strstr(e_scanear.palabra,e_comparar.palabra) != NULL) {
				encontrado = TRUE;
				//printf ("\nElemento existente encontrado.\n");
			} else {
				LISTAPDI_avanza(l);
			}
		}
	}
	return encontrado;
}

void LISTAPDI_incrementaVeces (ListaPDI *l, Elemento e) {
	l->ant->e.num_veces++;
}

int LISTAPDI_cuantosElementos (ListaPDI l) {
	int cantidad = 0;
	if (!LISTAPDI_vacia(l)) {
		LISTAPDI_vesInicio(&l);
		while (!LISTAPDI_final(l)) {
			cantidad++;
			LISTAPDI_avanza(&l);
		}
	}
	return cantidad;
}

void LISTAPDI_mostrarMasRepetidas (ListaPDI *l) {
	Elemento mayor;
	Elemento e;
	Elemento repetidas[3];
	int i, j;

	for(i = 0; i < 3; i++) {
		LISTAPDI_vesInicio(l);
		mayor = LISTAPDI_consulta(*l);
		while (!LISTAPDI_final(*l)) {
			e = LISTAPDI_consulta(*l);
			if (e.num_veces > mayor.num_veces) {
				mayor.num_veces = e.num_veces;
				strcpy(mayor.palabra, e.palabra);
			}
			LISTAPDI_avanza(l);
		}
		repetidas[i].palabra = (char*)malloc(sizeof(char) * MAXCAD);
		repetidas[i].num_veces = mayor.num_veces;
		strcpy (repetidas[i].palabra, mayor.palabra);
		
		LISTAPDI_vesInicio(l);
		while (!LISTAPDI_final(*l)) {
			e = LISTAPDI_consulta(*l);
			if (strcmp(e.palabra, repetidas[i].palabra) == 0) {
				LISTAPDI_elimina(l);
			} else {
				LISTAPDI_avanza(l);
			}
		}
	}
	LISTAPDI_vesInicio(l);
	for (i = 0; i < 3; i++) {
		printf ("%s\n", repetidas[i].palabra);
		LISTAPDI_inserta(l, repetidas[i]);
	}
}