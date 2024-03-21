#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char* p;
	int freeSTEP,freeMIN,freeMAX,blockSize=100,allocs =10,j;
	printf("\n\n");

	long initial_break = (long)sbrk(0);
	printf("Program initial break : %10p\n", (void*)initial_break);
	for(int i = 0;i < allocs;i++){
		p = malloc(blockSize);		// allocate block of bytes which specifies previously
		if(p == NULL){
			perror("malloc failed");
			break;
		}				//check that malloc succeeded 
	
	
	printf("Allocated %d bytes at %10p\n",blockSize,p);
	long current_break = (long)sbrk(0);
	printf("Program break after malloc(%d): %10p\n", blockSize,(void*)current_break);

	}
	for (int i = 0; i < allocs; i++) {
    		free(p);
  	}
}
