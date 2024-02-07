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
 * @about Function to get input from user and store it in a dynamically allocated char array.
 * @param buf The input string.
 * @param argv Pointer to an array of strings where the tokens will be stored.
 * @return The number of tokens found.
 */
int getInput(char buf[100], char ***argv) {
    char *delim = " ";
    unsigned count = 0;
    char *token = strtok(buf, delim);

    // Allocate memory for argv dynamically
    *argv = (char **)malloc(sizeof(char *) * 100); // Allocating space for 100 pointers to char

    while (token != NULL && count < 100) {
        (*argv)[count] = strdup(token); // strdup allocates memory for the string and copies it
        token = strtok(NULL, delim);
        count++;
    }
    
    return count;
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


void listFiles(const char *dirpath){

	DIR *dirp;
	struct dirent *dp;
	bool isCurrent;	/* true if dirpath is "." */
	isCurrent = strcmp(dirpath,".") == 0;
	dirp = opendir(dirpath);
	if(dirp == NULL){
//	errMsg("opendir failed '%s'",dirpath);
		return;
	}
	for(;;){
		errno = 0;
		dp = readdir(dirp);
		if(dp == NULL ){
			break;
		}
		if(strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") == 0){
			continue;
		}
		if(!isCurrent){
			printf("%s/",dirpath);
		}
		printf("%s\n",dp->d_name);
	}
	if(errno != 0){
//		errExit("readdir");
	}
	if(closedir(dirp) == -1){
//		errMsg("closedir");
	}
}



void execute_command(char *args[]) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
    } else if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror("execvp"); // If execvp fails
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

int unsetenv(const char *name){
	extern char **environ;
	if (name == NULL || name[0] == '\0' || strchr(name,'=') != NULL){
		errno = EINVAL;
                return -1;
	}
	size_t len = strlen(name);
	for (char **ep = environ; *ep != NULL; ){
		if(strncmp(*ep,name,len) == 0 && (*ep)[len] == '='){ //remove found entry by shifting all succesive entries
			for (char **sp = ep;*sp != NULL; sp++){
				*sp = *(sp + 1);
		
			}
		
		}else{
		
			ep++;
		}
	}
	return 0;
}
        
int setenv(const char *name, const char *value, int overwrite)
{
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL ||
            value == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (getenv(name) != NULL && overwrite == 0)
        return 0;

    unsetenv(name);             /* Remove all occurrences */

    char *es = malloc(strlen(name) + strlen(value) + 2);
                                /* +2 for '=' and null terminator */
    if (es == NULL)
        return -1;

    strcpy(es, name);
    strcat(es, "=");
    strcat(es, value);

    return (putenv(es) != 0) ? -1 : 0;
}

void show_environment() {
    extern char **environ;
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

