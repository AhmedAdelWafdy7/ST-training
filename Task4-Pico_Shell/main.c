#include "utilities.h"

int argc=0;
char buf[100];
int main(){
        intialize_shell();
        while(1){
                printf("\nAhmedfandes shell>>> ");
                fgets(buf,100,stdin);
                int len =strlen(buf);
                buf[len-1]=0;
                getInput(buf);
                if(strcmp(argv[0],"exit")==0)
                        {
                                printf("Good bye :)\n$");
                                break;     //breaking the shell
                        }
                else if(strcmp(argv[0] ,"cd")==0){
			chdir(argv[1]);
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

        }
}

