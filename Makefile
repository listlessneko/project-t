CC = gcc
CFLAGS = -Wall -Wextra -g

project-t: main.c game.c
	$(CC) $(CFLAGS) -o project-t main.c game.c

clean:
	rm -f project-t
