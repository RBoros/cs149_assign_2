/**
 * Description: This program creates multiple simultaneous processes for countnames.c
 * Author names: Ebsan Iqbal, Raymond Okolo
 * Author emails: ebsan.iqbal@sjsu.edu, raymond.okolo@sjsu.edu
 * Last modified date: 9/23/2026
 * Creation date: 9/20/2026
 **/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int children = 0;
    if(argc > 1) {
        children = 0;
        for(int i = 1; i < argc; i++){
            children++;
            pid_t pid = fork();

            if(pid < 0){
                printf("Fork failed");
            }
            else if(pid == 0){
                pid_t childPid = getpid();
                char childPidStr[16];
                snprintf(childPidStr, sizeof(childPidStr), "%d", childPid);

                execl("./countnames", "countnames", childPidStr, argv[i], NULL);
                fprintf(stderr,"error: cannot open file\n");
                exit(1);
            }
        }
    }else if (argc == 1){
        children = 1;
        pid_t pid = fork();

        if(pid < 0){
            printf("Fork failed");
        }
        if(pid == 0) {
            pid_t childPid = getpid();
            char childPidStr[16];
            snprintf(childPidStr, sizeof(childPidStr), "%d", childPid);

            execlp("./countnames", "countnames", childPidStr, "1", NULL);
            fprintf(stderr,"error: cannot open file\n");
            exit(1);
        }
    }
    int status;
    pid_t pid;

    while ((pid = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            fprintf(stderr,
                    "Child %d terminated normally with exit code: %d\n",
                    pid,
                    WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            fprintf(stderr,
                    "Child %d terminated abnormally with signal number: %d\n",
                    pid,
                    WTERMSIG(status));
        }
    }

    return 0;

}