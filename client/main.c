#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tcp-client.h"

int main (int argc, char * argv[]){

	char * ip;
	char * msg;

	int port;
	int read;
	int len;

	int counter;

	if(argc == 1){
		fprintf(stdout,"usage : \n./tcp-client [ip] [port] \nor \n./tcp-client [ip] [port] [message]\n");
		exit(-1);
	}else if(argc == 3){
		port = atoi(argv[2]);
		ip = strdup(argv[1]);
		fprintf(stdout,"tcp-client started. ip = %s , port = %d \n",ip,port);
		fprintf(stdout,"Please enter message that will be delivered : \n");
		read = getline(&msg,(size_t *)&len,stdin);
		if(read <= 0){
			perror("Error while reading : ");
			exit(-1);
		}else{
			fprintf(stdout,"Message is :  %s",msg);
		}
	}else if(argc > 3){
		port = atoi(argv[2]);
		ip = strdup(argv[1]);
		msg = strdup(argv[3]); //TODO and other argvs..
		if(argc >= 5){
			for(counter = 5; counter <= argc ; counter++){
				sprintf(msg,"%s %s",msg,argv[counter-1]);
			}
		}
		fprintf(stdout,"tcp-client started. ip = %s , port = %d \n",ip,port);
	}

	send_tcp_package(port,ip,msg);

	free(msg);
	free(ip);

	return 0 ;

}
