all: 
	gcc -o snake food.c game.c obstacle.c rendering.c score.c snake.c main.c -Wall -ggdb -std=c11 -pedantic `pkg-config --cflags sdl2` `pkg-config --libs sdl2`