#include "utilities.h"
int argc = 0;
char buf[100];
void free_argv();
int main(){
        intialize_shell();
        while(1){
                printf("\nWafdunix shell>>> ");
                fgets(buf,100,stdin);
                int len =strlen(buf);
                buf[len-1]=0;
                argc = getInput(buf,&argv);
		pid_t pid;

		for (int i = 0; i < argc; i++) {
        		if (argc > 2 && (strcmp(argv[i], ">") == 0 || strcmp(argv[i], ">>") == 0) ) {
				redirection(argv[i + 1]);
				argv[i] = NULL;
			}
			int pid = fork();
  		if (pid == -1) {
    			perror("fork");
    			exit(EXIT_FAILURE);
  		}

  			if (pid == 0) {
    		// Child process (executes ls)
    		//	execvp("ls", argv);
    		//	perror("execvp");
    			exit(EXIT_FAILURE);
  		} else {
    // Parent process
    			wait(NULL);
  		}
		}
		if(strcmp(argv[0],"exit")==0)
                {
                                printf("Good bye :)\n$");
                                break;     //breaking the shell
                }
		else if(strcmp(argv[0],"mkdir")==0){
			if (mkdir(argv[1], 0755) == -1) {
    				perror("mkdir");
  			}
		}
		else if (strcmp(argv[0],"rm")==0){
			if(strcmp(argv[1],"-r")==0){
				if (rmdir(argv[2]) == -1) {
                                	perror("rmdir");
                        	}
			}
			else{
				if (remove(argv[1]) == -1) {
                                        perror("rm");
                                }
			}	
		}
                else if(strcmp(argv[0] ,"cd")==0){
			if(argc > 1){
				chdir(argv[1]);
			}else{
				printf("use : cd <DIR>\n");
			}
		}
		else if(strcmp(argv[0] ,"ls") == 0){
			if(argc == 1)
				listFiles(".");		//use current dir
			else
				for (argv++; *argv; argv++)
					listFiles(*argv);
		}
		else if (strcmp(argv[0], "set") == 0) {
                	if (argc < 2) {
                    		printf("Use: set <name> <value>\n");
                	} else {
                    		int overwrite = (argc > 3 && strcmp(argv[3], "1") == 0) ? 1 : 0;
                    		if (setenv(argv[1], (argc > 2) ? argv[3] : "", overwrite) == -1) {
                        		perror("setenv");
                    		}
                	}
            	} else if (strcmp(argv[0], "unset") == 0) {
                	if (argc < 2) {
                    		printf("Use: unsetenv <name>\n");
                	} else {
                    		if (unsetenv(argv[1]) == -1) {
                        		perror("unsetenv");
                    		}	
			}	
		}else if (strcmp(argv[0], "env") == 0) {
			show_environment();
		}
                else if(strcmp(argv[0],"cp")==0)
                        {

                                int dest_fd = open(argv[2], O_CREAT | O_WRONLY ,0644);
                                int src_fd = open(argv[1],O_RDONLY );
                                int read_count;
                                while( (read_count = read(src_fd, buf,100 )) >0 ){
                                        write(dest_fd,buf,read_count);


                                }
                                close(src_fd);
                                close(dest_fd);


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
                else if(strcmp(argv[0],"echo")==0){
                        int i;
                        for(i=1;i<20;i++){
                                if(argv[i]==NULL){
                                        break;
                                }

                                printf("%s ",argv[i]);

                        }
                       }

                else if(strcmp(argv[0] ,"pwd")==0)
                        {
                                printDir();

                        }

                else
                        {
                               execute_command(argv);
                        }

	       for (int i = 0; i < argc; i++) {
            		free(argv[i]);
        	}
        	free(argv);
        	argv = NULL;

	}
}	

void free_argv() {
    if (argv != NULL) {
        for (int i = 0; argv[i] != NULL; i++) {
            free(argv[i]);
        }
        free(argv);
        argv = NULL;
    }
}
