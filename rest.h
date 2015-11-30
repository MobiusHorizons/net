#include <string.h>
#include <string.h>
struct rest_get {
	char * headers;
	size_t headers_len;
	int body;
  int response_code;
};

struct rest_get rest_get (
	const char * url,
	const char * query_string,
	const char * headers,
	size_t header_len
	);
struct rest_get {
	char * headers;
	size_t headers_len;
	int body;
  int response_code;
};

struct rest_get rest_get (
	const char * url,
	const char * query_string,
	const char * headers,
	size_t header_len
	);
