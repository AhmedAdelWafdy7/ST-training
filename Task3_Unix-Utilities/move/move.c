#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define clear() printf("\033[H\033[J")

void intialize_shell(void);
void getInput(char buf[100]);

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
                else if(strcmp(argv[0],"mv")==0)
                {

                                int dest_fd = open(argv[2], O_CREAT | O_WRONLY ,0644);
                                int src_fd = open(argv[1],O_RDONLY );
                                int read_count;
                                while( (read_count = read(src_fd, buf,100 )) >0 ){
                                        write(dest_fd,buf,read_count);


                                }

                                close(src_fd);
                                close(dest_fd); 
				int rm = remove(argv[1]);
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


