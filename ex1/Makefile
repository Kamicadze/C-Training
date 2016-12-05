CFLAGS = -Wall -g -isystem inc 
LDFLAGS = 
LIBS = 
SOURCES = src/main.c
NAME = bin/ex1
CC=gcc

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(NAME)
