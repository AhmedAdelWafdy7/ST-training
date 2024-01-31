#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define clear() printf("\033[H\033[J")

void intialize_shell(void);

char buf[100];

int main(){
	intialize_shell();
	while(1){
		printf("\nAna Gahez ya Basha > ");
		fgets(buf,100,stdin);
		int len = strlen(buf);
        	buf[len - 1] = 0;
	        if(strcmp(buf,"exit") == 0){
	       		printf("Good bye :)\n$");
			break;
		}
		else{
			printf("You said: %s \n",buf);
		}
       		       
	}
	return 0;
}

/**
 *
 *@about void function to intialize shell
 *@param void
 *@return void function
 */
void intialize_shell(void) {
        printf("$Welcome to WAFDUNIX shell..\n");
        sleep(2);
        printf("\n\n\n\n******************"
        "************************");
        printf("\n\n\n\t****WAFDUNIX SHELL****");
        printf("\n\n-  HAVE A NICE TIME WITH WAFDUNIX SHELL  -");
        printf("\n\n\n\n******************************************");
        sleep(4);
        clear();


}
