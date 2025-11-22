CC = gcc
LINKERS = -lm -lGL -lglfw -Iinclude 

main:
	$(CC) -o client main.c glad.c $(LINKERS) 
