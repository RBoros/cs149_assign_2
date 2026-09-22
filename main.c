#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current working directory: %s\n", cwd);
    if(argc > 1){
        int children = 0;
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
                perror("execl failed");
                exit(1);
            }
        }
        for (int i = 0; i < children; i++) {
            wait(NULL);
        }
    }else if (argc == 1){
        //children++;
        pid_t pid = fork();
        if(pid < 0){
            printf("Fork failed");
        }
        if(pid == 0)
        {
            pid_t childPid = getpid();
            char childPidStr[16];
            snprintf(childPidStr, sizeof(childPidStr), "%d", childPid);

            //execlp("./countnames", "countnames", childPidStr, "1", NULL);
            //perror("execl failed");
            //exit(1);
        }
        if(pid > 0){
            wait(NULL);
        }

    }

}