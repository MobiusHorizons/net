/*****
 * Simple Restful Get request in c.
 * ****************/


#include "net.h"
#include "url.h"
#include "common.h"
#include "rest.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


struct rest_get rest_get(
	const char * url, 
	const char * query_string, 
	const char * headers,
	size_t h_len    ){

	struct rest_get r;
	r.headers_len = 0;
	r.headers = NULL;

	struct url u = url_parse(url, query_string);
	int s = net_get_socket(u.host, u.port, u.tls);
	// SEND 'GET ${route} HTTP/1.0\r\n'
	send(s, "GET ", 4, 0);
	send(s, u.route, u.route_len, 0);
	if (query_string != NULL){
		send(s, "?", 1, 0);
		send(s, query_string, strlen(query_string), 0);
	}
	send(s, " HTTP/1.0\r\n", 11, 0);
	send(s, "Host: ", 6, 0);
	send(s,  u.host, strlen(u.host),0);
	send(s, "\r\n", 2, 0); 

	if ( headers != 0 && h_len > 0) send(s, headers, h_len, 0); 
	send(s, "\r\n", 2, 0); // end the headers
	
	char buf[4096];
	int done = 0;
	while (done == 0){
		ssize_t len = recv(s, buf, 4096, MSG_PEEK);
		char * body = memmem(buf, len, "\r\n\r\n", 4);
		if (body){
			len = body - buf + 4;
			done = 1;
		}
		r.headers_len += len;
		r.headers = realloc(r.headers, r.headers_len);
		read(s, r.headers, len);
	}		
//HTTP/1.1 200 OK
  r.response_code = atol(index(r.headers, ' '));
	r.body = s;
	return r;
}
