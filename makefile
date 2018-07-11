# Makefile
# Manualmente creado para:
#		make: Compilar los diferentes modulos y generar el ejecutable mediante 
#				los objetos creados
#		make clean: limpiar y borrar los archivos .o u objetos creados y el 
#				ejecutable

all:	ejecutable
main.o:	src/main.c include/logica.h include/listaPDI.h
	gcc -c src/main.c
	
logica.o: src/logica.c include/logica.h
	gcc -c src/logica.c

listaPDI.o:	src/listaPDI.c include/listaPDI.h
	gcc -c src/listaPDI.c
	
ejecutable:	main.o logica.o listaPDI.o 
	gcc main.o logica.o listaPDI.o -g -o ejecutable
	
clean:
	rm *.o ejecutable