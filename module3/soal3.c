#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>

void loop_pipe(char ***cmd) {
  int p[2];
  pid_t pid;
  int fd_in = 0;

  while (*cmd != NULL){
  	pipe(p);
    if ((pid = fork()) == -1){
    	exit(EXIT_FAILURE);
    }else if (pid == 0){
    	dup2(fd_in, 0); //change the input according to the old one
    	if (*(cmd + 1) != NULL)
    		dup2(p[1], 1);
    	close(p[0]);
    	execvp((*cmd)[0], *cmd);
    	exit(EXIT_FAILURE);
        }else{
        	wait(NULL);
        	close(p[1]);
        	fd_in = p[0]; //save the input for the next command
        	cmd++;
        }
    }
}

int main() {
	int p[2], i; 
	char *ls[] = {"ls", NULL};
	char *head[] = {"head", "-3", NULL};
	char *tail[] = {"tail", "-1", NULL};
	char **cmd[] = {ls, head, tail, NULL};

	loop_pipe(cmd);

	return 0; 
} 