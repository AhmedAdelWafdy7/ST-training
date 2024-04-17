#include <unistd.h>
//#include <stdio.h>
//#include <stdlib.h>
#include "basic_mangement.h"
int main(int argc, char *argv[]){
	char* p;
	printf("\n\n");

	long initial_break = (long)sbrk(0);
	printf("Program initial break : %10p\n", (void*)initial_break);
		p = mymalloc(100*1000);	
		if(p == NULL){
			perror("malloc failed");
		}				//check that malloc succeeded 
	
	printf("Allocated %d bytes at %10p\n",100*1000,p);
	long current_break = (long)sbrk(0);
	printf("Program break after malloc(%d): %10p\n",100*1000,(void*)current_break);


	printf("Program initial break : %10p\n", (void*)initial_break);
                p = mymalloc(512*1000);       
                if(p == NULL){
                        perror("malloc failed");
                }                               //check that malloc succeeded

        printf("Allocated %d bytes at %10p\n",512*1000,p);
        current_break = (long)sbrk(0);
        printf("Program break after malloc(%d): %10p\n",512*1000,(void*)current_break);

	printf("Program break is now:           %10p\n", sbrk(0));

    	printf("Freeing blocks from %10p",p);
        myfree(p);
	printf("\nAfter free(), program break is: %10p\n", sbrk(0));

}
