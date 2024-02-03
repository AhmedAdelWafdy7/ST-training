#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define clear() printf("\033[H\033[J")

void intialize_shell(void);
int argc=0;
char buf[100];
int x,result;
char buf[100];
int read_count;
char *argv[]={ NULL };

int main(){
        intialize_shell();
        while(1){
                printf("\nAna Gahez ya Basha > ");
                fgets(buf,100,stdin);
                int len = strlen(buf);
                buf[len - 1] = 0;
                getInput(buf);
                if(strcmp(argv[0],"exit") == 0){
                        printf("Good bye :)\n$");
                        break;
                }
                else if(strcmp(argv[0],"echo")==0){
                        int i;
                        for(i=1;i<20;i++){
                                if(argv[i]==NULL){
                                        break;
                                }

                                printf("%s ",argv[i]);

                        }
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

/**
 *@about int function to get input from user and store it in a char array
 *@param str
 *@return 1 if string stored and success
 *      
 */
void getInput(char buf[100]){
        char *delim = " ";
        unsigned count = 0;
        char *token = strtok(buf,delim);
        while(token != NULL)
        {
                argv[count]=token;
                token = strtok(NULL,delim);
                count++;

        }
}


void echo(char buf[100]){
         char *token = strtok(buf, " ");
   // loop through the string to extract all other tokens
   token = strtok(NULL, " ");

         while( token != NULL ) {
      printf( " %s", token ); //printing each token
      token = strtok(NULL, " ");
   }
}

