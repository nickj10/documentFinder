/*************************************************************************************
*
* @Proposito: Este pograma es blah blah buscador de palabras en documentos
* @Fecha creacion: 2 de Junio de 2018
* @Fecha ultima modificacion: 4 de Junio de 2018
*
**************************************************************************************/

#include <dirent.h>
#include <stdio.h> 
#include "../include/logica.h"

int main(void) {
  Cadena opcion, palabras;
  Fichero ficheros[MAXFICHEROS];
  int opcion_error;
  int tamano, i_fichero;
  int num_ficheros = 0;
  char id_doc[6];
  int doc_encontrado;
  char aux;
  int frase_encontrada = 0;
  char frase[MAXCAD];
  int ok = 0;
  
  ListaPDI lista_palabra;
  ListaPDI lista_frase;
  
  do {
    printf ("\nBUSCADOR DE DOCUMENTOS - MENU\n\n");
    printf ("1. Cargar documentos\n2. Buscar documentos por palabras\n3. Buscar documentos por frase\n");
    printf ("4. Mostrar palabras clave de un documento\n5. Salir\n\nOpcion: ");
    fgets (opcion,MAXCAD,stdin);
    opcion[strlen(opcion) - 1] = '\0';

    opcion_error = validarOpcion (opcion);  
    
    if (opcion_error != TRUE) {
      switch (opcion[strlen(opcion) - 1]) {
        case '1':
            num_ficheros = cargarDocumentos(ficheros);
            break;
          
        case '2':
            // Si no se ha cargado ningun fichero no podra usar esta opcion
            if (num_ficheros == 0) {
                printf ("No se ha indexado ningun documento.\n");
            }
            else {
                printf ("\nIntroduce las palabras separadas por (,): ");
                fgets (palabras,MAXCAD,stdin);
                palabras[strlen(palabras) -1] = '\0';
            
                //Extraemos las palabras del array
                lista_palabra = extraePalabras (palabras);
                
                //Buscamos para cada fichero si esta es palabra y lo printamos
                for (i_fichero = 0; i_fichero < num_ficheros; i_fichero++) {
                    printf ("i fichero: %d\n",i_fichero+1);
                    encontrarDocumento (lista_palabra, ficheros[i_fichero]);
                }
                LISTAPDI_destruye(&lista_palabra);
            }
            break;
          
        case '3':
            frase_encontrada = 0;
            ok = 0;
            
            // Si no se ha cargado ningun fichero no podra usar esta opcion
            if (num_ficheros == 0) {
                printf ("No se ha indexado ningun documento.\n");
            }
            else {
                printf ("\nIntroduce una frase: ");
                fgets (frase, MAXCAD, stdin);
                
                frase[strlen(frase) - 1] = '\0';
                
                for (i_fichero = 0; i_fichero < num_ficheros; i_fichero++) {
                    frase_encontrada = buscarFrase (frase, ficheros[i_fichero]);
                    if (frase_encontrada) {
                        printf ("La frase esta en el fichero %s.\n", ficheros[i_fichero].nombre_fichero);
                        frase_encontrada = 0;
                        ok = 1;
                    }
                }
                if (!ok) {
                    printf ("No se ha encontrado la frase en ningun documento.\n");
                }
            }
            
          break;
        case '4':
            // Si no se ha cargado ningun fichero no podra usar esta opcion
            if (num_ficheros == 0) {
                printf ("No se ha indexado ningun documento.\n");
            }
            else {
                printf ("Introduce la id del documento:\n");
                scanf ("%s", id_doc);
            
                // Buscamos en el array de ficheros la id
                i_fichero = 0;
                doc_encontrado = FALSE;
                strcat (id_doc, ".txt");
            
                while (i_fichero < num_ficheros && !doc_encontrado) {
                    if (strcmp (ficheros[i_fichero].nombre_fichero, id_doc) == 0) {
                        doc_encontrado = TRUE;
                    }
                    else {
                        i_fichero++;
                    }
                }
                if (doc_encontrado == TRUE) {
                    printf ("\nPalabras claves del documento %s:\n", ficheros[i_fichero].nombre_fichero);
                    LISTAPDI_mostrarMasRepetidas(&ficheros[i_fichero].palabras);
                }
                else {
                    printf ("No se ha encontrado el documento con id %s.\n", id_doc);
                }
                scanf ("%c", &aux);
            }
            break;
        case '5':
            printf ("Gracias por usar el programa.\n");
            
            // Liberar memoria creada dentro del array ficheros[MAXFICHEROS] si se han creado
            //if (num_ficheros > 0) {
              //  for (i_fichero = 0; i_fichero < num_ficheros; i_fichero++) {
                //    LISTAPDI_destruye(&ficheros[i_fichero].palabras);
                //}
            //}
            break;
        }
    }
    
  } while (opcion[strlen(opcion) - 1] != '5' || opcion_error != FALSE);
  return (0);
}
