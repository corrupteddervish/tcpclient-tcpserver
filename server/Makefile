PROG = tcp-server

SRCS = tcp-server.c main.c
OBJS = tcp-server.o main.o


CC = gcc
CFLAGS = -I.
LDFLAGS =
OPTS = -g -Wall 
RM = rm -rf 

all:$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROG) $(OBJS) $(OPTS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SRCS) $(OPTS)

clean: 
	$(RM) $(PROG) *.o 

