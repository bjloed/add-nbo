#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define SIZE 4

void error_handler(char *error) {
	puts(error);
	exit(1);
}

uint32_t bswap32(uint32_t bytes) {
	__asm__(
		"bswap %0\n;"
		:"=r"(bytes)
	);
	return bytes;
}

uint32_t get_uint32_from_file(char *path) {
	FILE *fp = fopen(path, "r");
	if(fp <= 0)
		error_handler("fopen");
	
	char *buf = (char *)malloc(SIZE);
	fread(buf, 1, SIZE, fp);
	uint32_t val = bswap32(*(int *)buf);
	
	buf = NULL;
	free(buf);
	fclose(fp);

	return val;
}

int main(int argc, char *argv[]) {
	if(argc != 3)
		error_handler("argc must be '3'");

	uint32_t x = get_uint32_from_file(argv[1]);
	uint32_t y = get_uint32_from_file(argv[2]);
	
	printf("%d(%#02x) + %d(%#02x) = %d(%#02x)\n", x, x, y, y, x + y, x + y);
	return 0;
}
