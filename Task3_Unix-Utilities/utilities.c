/*------------------------------includes--------------------------------------*/
#include "utilities.h"
/*------------------------------functions definations-------------------------*/

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

/**
 *@about void function to print current directory
 *@param void
 *@return void function
 * */
void printDir(void){
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s\n", cwd);
}
