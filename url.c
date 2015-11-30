#include <string.h>
#include <stdlib.h>
#include "url.h"

struct url url_parse(const char * url, const char * query_string){
	struct url u;
	const char * host;
	const char * end = url + strlen(url);
	
	const char * prot = strstr( url, "://");
	if (prot == NULL){
		u.tls = 0;
		u.port = 80;
		host = url;
	} else {
		host = prot + 3;
		if ( prot - url == 4 ) {
			u.tls = 0;
			u.port = 80;
		} else {
			// assume https 
			u.tls = 1;
			u.port = 430;
		}
	}
	const char * port = index(host, ':');
	const char * route = index(host, '/');
	if (route == NULL) {
		route = end;
		u.route = strdup("/");
		u.route_len = 1;
	} else {
		size_t len = end - route;
		u.route = (char *) malloc(len + 1);
		memcpy(u.route, route, len);
		u.route[len] = 0;
		u.route_len = len;
	}

	if (port && port < route){
		int len = port - host;
		u.host = (char *) malloc(len + 1);
		memcpy(u.host, host, len);
		u.host[len] = 0;
		u.port = strtoul(port, NULL, 10);
	} else {
		port = route;
	}

	u.host = malloc(route - host + 1);
	strncpy(u.host, host, route-host);
	u.host[route-host] = '\0';

	u.query_string = strdup(query_string);
	return u;
}



