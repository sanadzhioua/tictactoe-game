prog:fonction.o main.o
	gcc fonction.o main.o -o prog -L/usr/local/lib -lSDL_gfx -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer
main.o:main.c
	gcc -c main.c 
fonctions.o:fonction.c
	gcc -c fonction.c 
