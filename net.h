#ifndef REST_NET_H
#define REST_NET_H

#include <sys/socket.h>


int net_get_socket(const char * host, int port, int tls);
#endif //REST_NET_H
