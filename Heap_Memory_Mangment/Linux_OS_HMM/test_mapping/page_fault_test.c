#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/resource.h>

#define BUFFER_SIZE 	(1024 * 1024)

void print_pgflt_info() {
	int ret;
	struct rusage usage;
	ret = getrusage(RUSAGE_SELF, &usage);
	if (ret == -1) {
		perror("getrusage");
		return;
	}else {
		printf("Major page faults: %ld\n", usage.ru_majflt);
		printf("Minor page faults: %ld\n", usage.ru_minflt);
	}
}

int main(int argc, char *argv[]) {
	unsigned char *p;
	printf("Initial page faults:\n");
	print_pgflt_info();
	p = malloc(BUFFER_SIZE);
	printf("After malloc:\n");
	print_pgflt_info();
	memset(p, 0x42, BUFFER_SIZE);
	printf("After memset:\n");
	print_pgflt_info();
	memset(p, 0x42, BUFFER_SIZE);
 	printf("After 2nd memset:\n");
	print_pgflt_info();
	return 0;
}

