
#include <stdio.h>
#include <stdlib.h>

#include <signal.h>

#include "tcp-server.h"


int main(int argc,char * argv[]){
	int port;
	int x;
	if(argc == 1 || argc >= 3){
		fprintf(stdout,"usage : \n./tcp-server [port number] \n");
		exit(-1);
	}else{
		port = atoi(argv[1]);
		if(port == 0){
			fprintf(stdout,"usage : \n./tcp-server [port WITH number] \n");
			exit(-1);
		}
	}

	x = receiveTcpPacket(port);

	return x;
}
