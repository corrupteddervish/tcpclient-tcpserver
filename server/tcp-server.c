/*
 * tcp-server.c
 *
 *  Created on: Nov 9, 2016
 *      Author: dervis
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tcp-server.h"

#define MAX_CONNECTION 10
#define MAX_MESSAGE_SIZE 5

#define IS_BIGGER(a,b) ((a) > (b) ? (a) : (b))

static int bind_socket(int portno){
	int fd;
	struct sockaddr_in server;
	int option = 1;

	fd = socket(AF_INET,SOCK_STREAM,0);

	//hatanın ne olduğunu yaz...
	if(fd==-1){
		fprintf(stdout,"Error while opening port.");
		return -1;
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY; //accept connections everywhere
	server.sin_port = htons(portno);

	if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option))){
		perror("Error while opening port ");
		return -1;
	}

	if(bind(fd, (struct sockaddr *)&server,sizeof(server)) == -1){
		perror("Error while opening port ");
		return -1;
	}

	if(listen(fd,MAX_CONNECTION) == -1){
		perror("Error while opening port ");
		return -1;
	}

	fprintf(stdout,"Now listening port %d from fd %d \n",portno,fd);

	return fd;
}

static int read_from_client(int client_fd, char ** buff){
	char * buffer = NULL;
	int readed_bytes;

	buffer = malloc(MAX_MESSAGE_SIZE);
	memset(buffer,0,MAX_MESSAGE_SIZE);

	if(buffer == NULL){
		return -1;
	}

	readed_bytes = read(client_fd,buffer,MAX_MESSAGE_SIZE-1);


	*buff=buffer;

	return readed_bytes;
}

int receiveTcpPacket(int portno){
	int socket_fd;
	int max_fd;
	int fds;
	int client_fd;
	int message_byte;

	fd_set read_fd;

	socklen_t client_size;

	char * message = NULL;

    struct sockaddr_in client;

    socket_fd = bind_socket(portno);

    if(socket_fd <0){
    	return socket_fd;
    }

    FD_ZERO(&read_fd);
    FD_SET(socket_fd,&(read_fd));
    max_fd = socket_fd+1;

    while(1){
    	if(select(max_fd,&read_fd,NULL,NULL,NULL)<-1){
    		perror("Select error :");
    		return -1;
    	}

    	fprintf(stdout,"New message ! \n");

    	//fd 0 for keyboard, fd 1 is for mouse, fd 2 is for screen
    	for(fds = 3 ; fds<=max_fd ; fds++){

    		if(fds == socket_fd){
    			//hurray ! new connection
    			client_size = sizeof(client);
    			client_fd = accept(socket_fd, (struct sockaddr *)&client,&client_size);
    			if(client_fd < 0){
    				perror("Error: ");
    				return -1;
    			}
    			FD_SET(client_fd,&read_fd);
    			max_fd = IS_BIGGER(client_fd,max_fd);

    			fprintf(stdout,"Client with ip : %s port : %d connected on fd : %d \n" ,
    					inet_ntoa (client.sin_addr), ntohs(client.sin_port),client_fd);

    		}else{
    			message_byte = read_from_client(fds,&message);

    			fprintf(stdout,"Message completed. %d bytes received \n",message_byte);
    			strcat(message,"\n");
    			fprintf(stdout,"Message is :  \n%s\n",message);
    			free(message);
    			message = NULL;

    			FD_CLR(fds,&read_fd);
    			close(fds);
    		}

    	}

    }

    return 1;
}



