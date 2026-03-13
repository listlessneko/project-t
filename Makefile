CC = gcc
CFLAGS = -Wall -Wextra -g

project-t: main.c game.c utils.c
	$(CC) $(CFLAGS) -o project-t main.c game.c utils.c rooms.c

clean:
	rm -f project-t
