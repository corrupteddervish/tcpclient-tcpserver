PROG = tcp-client

SRCS = main.c tcp-client.c
OBJS = main.o tcp-client.o


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

