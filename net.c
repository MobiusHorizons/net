#include "net.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <netinet/in.h>
#include <strings.h>

void error (char * msg){
	perror(msg);
	exit(0);
}

int net_get_socket(const char * host, int port, int tls){
	int sockfd;
	struct sockaddr_in serv_addr;
	struct hostent * h;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){ return sockfd; } 
	h = gethostbyname(host);
	if (h == NULL){
		fprintf(stderr, "ERROR, nslookup failed for '%s'\n", host);
		return -1;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy(
		(char *)h->h_addr,
		(char*)&serv_addr.sin_addr.s_addr,
		h->h_length
	);
	serv_addr.sin_port = htons(port);
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");
	
	return sockfd;
}

