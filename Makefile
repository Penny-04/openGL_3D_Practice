CC = gcc
LINKERS = -lm -lGL -lglfw -lGLEW

main:
	$(CC) -o client main.c $(LINKERS) 
