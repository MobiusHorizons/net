#ifndef REST_URL_H
#define REST_URL_H
#include <string.h>

struct url {
	char * host;
	char * query_string;
	char * route;
	size_t route_len;
	int port;
	int tls;
};

struct url url_parse(const char * url, const char * query_string);

void url_clean(struct url u);

#endif
