/*************************************************************************************
*
* @Proposito: 
* @Fecha creacion: 2 de Junio de 2018
* @Fecha ultima modificacion: 4 de Junio de 2018
*
**************************************************************************************/

#include "../include/logica.h"

/**************************************************************************************
*
* @Finalidad: Mirar si al final de una cadena o al principio hay un signo de puntuacion
* @Parametros: in:  cad = la cadena a consultar
* @Retorno: Devuelve 1 si es un signo de puntuacion
*
***************************************************************************************/
void checkPunctuation (char *cad) {
    int i = 0;
    int j = 0;
    if ((cad[0] >= 33 && cad[0] <= 47) || (cad[0] >= 58 && cad[0] <= 64) || (cad[0] >= 91 && cad[0] <= 96) || (cad[0] >= 123 && cad[0] <= 126)) {
        for (i = 0; i < strlen(cad); i++) {
            cad[i] = cad[i+1];
        }
        cad[i] = '\0';
    }
    j = strlen(cad) - 1;
    /*do {
        if ((cad[j] >= 33 && cad[j] <= 47) || (cad[j] >= 58 && cad[j] <= 64) || (cad[j] >= 91 && cad[j] <= 96) || (cad[j] >= 123 && cad[j] <= 126)) {
            cad[strlen(cad)-1] = '\0';
        }
        j--;
    } while ((cad[j] >= '!' && cad[j] <= '/') || (cad[j] >= ':' && cad[j] <= '@') || (cad[j] >= '[' && cad[j] <= 96) || (cad[j] >= '{' && cad[j] <= '~'));
	*/
}

/**************************************************************************************
*
* @Finalidad: Mirar si el caracter es un numero
* @Parametros: in:  c = el caracter
* @Retorno: Devuelve 0 si no es un caracter, un numero distinto de cero en caso contrario
*
***************************************************************************************/
int checkNumber (char *c) {
    int number = 0;
    if (c[0] >= '0' && c[0] <= '9') {
        number = 1;
    }
    return number;
}


/**************************************************************************************
*
* @Finalidad: Mirar si es un conector o no
* @Parametros: in: c = string a evaluar
* @Retorno: Devuelve un 1 si es un connector, 0 en caso contrario
*
***************************************************************************************/
int checkConnector (char *c) {
    int correcto = FALSE;
    int i = 0;
    char connectors[75][MAXCAD] = {"However", "In", "contrast", "Nevertheless", "Nonetheless", "yet", "on", "the", "other", "By",
    "comparison", "contrary", "instead", "in", "any", "all", "same", "likewise", "similarly", "correspondingly", "also",
    "as", "a", "an", "Therefore", "Thus", "This", "Those", "these", "those", "Firstly", "begin", "besides", "Besides",
    "Lastly", "lastly", "above", "below", "Above", "Basically", "Finally", "Moreover", "Example", "Instance", "Illustrate",
    "fact", "indeed", "actually", "regarding", "regards", "rather", "Rather", "then", "Then", "afterwards", "afterwards",
    "The", "later", "Later", "anyway", "Anyway", "Anyhow", "anyhow", "meanwhile", "Meanwhile"};
    
    for (i = 0; i < 75 && !correcto; i++) {
        if (strcmp(connectors[i], c) == 0) {
            correcto = TRUE;
        }
    }
    return correcto;
}

/**************************************************************************************
*
* @Finalidad: Indexar todos los documentos en un directorio, es decir, guardar 
*       todas las palabras que hay en el documento en una lista
* @Parametros: in: ficheros = un array de Ficheros que contiene el nombre del
*       documento y la lista de palabras
* @Retorno: Devuelve el numero de documentos en el directorio especificado
*
***************************************************************************************/
int cargarDocumentos (Fichero ficheros[MAXFICHEROS]) {
    DIR *d;
    FILE *f;
    Cadena path, nombre_fichero, aux_cad, filename;
    Elemento e;
    int i_fichero = 0;
    int tamano = 0;
    int num_ficheros = 0;
    struct dirent *dir;
    
    // Pedimos al usuario la ruta o el directorio
    printf ("\nIntroduce el directorio: \n");
    fgets (path, MAXCAD, stdin);
    
    path[strlen(path) - 1] = '\0';
    
    strcpy (filename, path);
    
    // Abrimos el directorio para ver los documentos
    d = opendir(path);
    
    // Mostramos un error en caso de que no se encuentra el directorio
    if (!d) {
        printf ("Error, no se encuentra el directorio %s\n", path);
    } else {
        while ((dir = readdir(d)) != NULL) {
            
            // Un directorio contiene . y ..
            // Hay que saltar estos dos
            if (strcmp (dir->d_name, ".") != 0 && strcmp (dir->d_name, "..") != 0) {
                // Guardamos el nombre del fichero
                strcpy (ficheros[i_fichero].nombre_fichero, dir->d_name);
                
                // Concatenamos la ruta y el nombre del fichero para poder abrirlo
                strcat (filename, ficheros[i_fichero].nombre_fichero);
                
                // Abrimos el fichero
                f = fopen (filename, "r");
                if (!f) {
                    printf ("Error, no se ha podido abrir el fichero %s\n", ficheros[i_fichero].nombre_fichero);
                }
                else {
                    e.palabra = (char*) malloc(sizeof(char) * MAXCAD);
                    
                    // Creamos la lista de palabras para el fichero
                    ficheros[i_fichero].palabras = LISTAPDI_crea();
                    
                    // Leemos todo lo que hay dentro del fichero 
                    // Prelectura
                    fscanf (f, "%s", aux_cad);
                    while (!feof(f)) {
                        //checkPunctuation(aux_cad);
                        strcpy (e.palabra, aux_cad);
                        //sprintf(str, "%d", someInt);
                        // Limpiamos la cadena
                        aux_cad[0] = '\0';
                        
                        // Ponemos la palabra dentro de la lista si no exite
                        if (LISTAPDI_existeElemento(&ficheros[i_fichero].palabras, e)) {
                            LISTAPDI_incrementaVeces(&ficheros[i_fichero].palabras, e);
                        } else {
                            e.num_veces = 0;
                            //printf ("%s - %d\n", e.palabra, e.num_veces);
                            LISTAPDI_inserta (&ficheros[i_fichero].palabras, e);
                            e.palabra[0] = '\0';
                        }
                        fscanf (f, "%s", aux_cad);
                    }
                    fclose (f);
                    printf ("Se ha indexado el fichero %s correctamente!\n", ficheros[i_fichero].nombre_fichero);
                    
                    // Limpiamos la cadena del fichero a abrir
                    filename[0] = '\0';
                    strcpy (filename, path);
                    
                    num_ficheros++;
                }
            }
            i_fichero++;
        }
    }
    closedir(d);
    return num_ficheros;
}

/**************************************************************************************
*
* @Finalidad: Validar la opcion introducida por el usuario
* @Parametros: in: opcion = una cadena que contiene la opcion introducida
* @Retorno: Devuelve un 1 si la opcion introducida es valida y un 0 en caso contrario
*
***************************************************************************************/
int validarOpcion (Cadena opcion) {
    int error = FALSE;
    
	if (strlen(opcion) == 1) {
		if ((opcion[strlen(opcion) - 1] >= 32 && opcion[strlen(opcion) - 1] < '0') || (opcion[strlen(opcion) - 1] > '9' && opcion[strlen(opcion) - 1] <= 255)) {
			printf ("\nOpcion incorrecta! La opcion ha de ser un numero.\n");
			error = TRUE;
		}
		else {
			if (opcion[strlen(opcion) - 1] == '0' || (opcion[strlen(opcion) - 1] > '5' && opcion[strlen(opcion) - 1] <= '9')) {
				printf ("\nOpcion incorrecta!\n");
				error = TRUE;
			}
		}
	}
	else {
		printf ("\nOpcion incorrecta!\n");
		error = TRUE;
	}
	return error;
}


/**************************************************************************************
*
* @Finalidad: Extraer las palabras separadas por comas y guardarlas en la lista
* @Parametros: in: palabras = un string que contiene las palabras a consultar separadas por comas
* @Retorno: Devuelve la lista de palabras que queremos consultar
*
***************************************************************************************/
ListaPDI extraePalabras (char * palabras) {
    int i, j = 0;
    ListaPDI l;
    Elemento aux_elem;

    l = LISTAPDI_crea();
    
    // Dividir la cadena que contiene las palabras separadas por , en cadenas
    // diferentes e inserirla en la lista de palabras a buscar
    aux_elem.palabra = strtok(palabras, ",");
    while (aux_elem.palabra != NULL) {
        LISTAPDI_inserta (&l, aux_elem);
        aux_elem.palabra = strtok(NULL, ",");
    }
    return l;
}

/**************************************************************************************
*
* @Finalidad: Encontrar en un fichero si aparece las palabras introducidas
* @Parametros: in:  lista_palabra = la lista de palabras a buscar
*              in:  ficheros = un registro que contiene el nombre de fichero y la lista
*                               de palabras que contiene
* @Retorno: Devuelve la lista de palabras que queremos consultar
*
***************************************************************************************/
void encontrarDocumento (ListaPDI lista_palabra, Fichero ficheros) {
    int palabra_encontrada = FALSE;
    int error = FALSE;
    int num_elementos, i = 0;
    Elemento palabra_buscar;
    Elemento palabra_documento;

    // Vamos al inicio de la lista de palabras a buscar
    LISTAPDI_vesInicio(&lista_palabra);
    while (!LISTAPDI_final(lista_palabra) && !error) {
        // Vamos al inicio de las palabras que contiene el documento
        LISTAPDI_vesInicio(&ficheros.palabras);
        palabra_buscar = LISTAPDI_consulta(lista_palabra);
        palabra_encontrada = FALSE;
        
        while (!LISTAPDI_final(ficheros.palabras) && !palabra_encontrada) {
            // Recorremos la lista de las palabras que contiene el fichero, si lo ha encontrado,
            // vamos a la siguiente palabra de la lista a buscar
            palabra_documento = LISTAPDI_consulta(ficheros.palabras);
            if (strstr (palabra_documento.palabra,palabra_buscar.palabra) != NULL) { //si son iguales
                palabra_encontrada = TRUE;
                //printf ("Encontrada.\n");
            }
            else {
                LISTAPDI_avanza(&ficheros.palabras);
            }
        }
        
        // Si ha encontrado la palabra en el documento, vamos a mirar la siguiente palabra a buscar
        if (palabra_encontrada == TRUE) {
            LISTAPDI_avanza(&lista_palabra);
        }
        else {
            error = TRUE;
        }
    }
    if (!error) {
        printf ("%s\n", ficheros.nombre_fichero);
    }
}

/**************************************************************************************
*
* @Finalidad: Encontrar en un fichero si aparece la frase introducida
* @Parametros: in:  frase = la frase a buscar
*              in:  ficheros = el fichero donde buscamos la frase
* @Retorno: Devuelve un 1 si se encuentra la frase, 0 en caso contrario
*
***************************************************************************************/
int buscarFrase (char frase[MAXCAD], Fichero ficheros) {
    FILE *f;
    char aux[MAXCAD];
    int encontrada = 0;
    Cadena dest = "texts/";
    
    // Abrir cada fichero para mirar lo que hay dentro
    if (ficheros.nombre_fichero != NULL) {
        strcat (dest, ficheros.nombre_fichero);
        f = fopen (dest, "r");
        if (f) {
            fgets (aux, MAXCAD, f);
            
            // Miramos cada linea si esta la frase introducida
            while (!feof(f) && !encontrada) {
                aux[strlen(aux) - 1] = '\0';
                if (strstr(aux, frase) != NULL) {
                    encontrada = 1;
                }
                fgets (aux, MAXCAD, f);
            }
            fclose (f);
        }
    }
    return encontrada;
}
