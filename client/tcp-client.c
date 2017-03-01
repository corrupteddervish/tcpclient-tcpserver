#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "tcp-client.h"

static int open_port(int dest_port, char * dest_ip){
	int conn;
	int fd;
	struct sockaddr_in server;

	fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd == -1){
		perror("Error opening socket : ");
		return(-1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(dest_port);
	inet_aton(dest_ip,&server.sin_addr);

	conn = connect(fd,(const struct sockaddr *)&server,sizeof(server));
	if(conn < 0){
		perror("Error connecting server : ");
		return(-1);
	}

	return fd;
}

static int send_packet(int fd, char * data){

	if(write(fd,data,strlen(data)) == -1){
		perror("Error while write : ");
		return (-1);
	}
	return 1;

}

int send_tcp_package(int dest_port, char * dest_ip, char * data){
	int fd;
	int is_success;

	fd = open_port(dest_port,dest_ip);

	if(fd == -1)
		return -1;

	is_success = send_packet(fd,data);

	if(is_success != 1){
		fprintf(stderr,"Error occured when sending the packet.");
	}else{
		fprintf(stdout,"Message sended succesfully\n");
	}

	close(fd);

	return is_success;
}
