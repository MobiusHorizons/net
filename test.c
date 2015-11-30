#include "rest.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
	const char * headers = "User-Agent: curl\r\n";
	struct rest_get r = rest_get(argv[1], "", headers, strlen(headers));
  fprintf(stderr, "server responded with %d\n", (int) r.response_code);
	fprintf(stderr, "%.*s\n", (int) r.headers_len, r.headers);
	char buf[2048];
	int len;
	while ((len = read(r.body, buf, 2048)) > 0){
		write(1, buf, len);
	}
}
