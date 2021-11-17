#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "string"
#define ERROR_FORK 1
#define ERROR_EXEC 2
#define ERROR_PIPE 3
#define OK 0
bool sendSig = 0;
void empty(int sig)
{
}
void sendSigSwitch(int sig)
{
    sendSig = 1;
}
int main()
{
    signal(SIGINT, empty);
    int fd[2];
    const char *messages[2] = { "msg\n", "msg msg\n"};
    if (pipe(fd) == -1) {
        return ERROR_PIPE;
    }
    int childpids[2];
    for (int i = 0; i < 2; i++)
    {
        int pid = fork();

        if (pid == -1)
        {
            return ERROR_FORK;
        }

        if (pid == 0)
        {
            signal(SIGINT, sendSigSwitch);
            sleep(6);

            if (sendSig) {
                close(fd[0]);
                write(fd[1], messages[i], strlen(messages[i]));
                printf("CHILD №%d: (pid: %d, ppid: %d, grp: %d) sent message to parent\n", i + 1, getpid(), getppid(), getpgrp());
            }
            else {
                printf("CHILD №%d: didn't send a message\n", i + 1);
            }

            return OK;
        }
        childpids[i] = pid;
    }
    printf("PARENT: pid: %d grp: %d, child's pids: %d, %d\n", getpid(), getpgrp(), childpids[0], childpids[1]);
    for (int i = 0; i < 2; i++)
    {
        int status;
        pid_t childpid = wait(&status);
        if (WIFEXITED(status))
        {
            printf("PARENT: child №%d (PID = %d) has finished with code: %d\n", i + 1, childpid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("PARENT: child №%d (PID = %d) has finished because of signal: %d\n", i + 1, childpid, WTERMSIG(status));
        }
        else if (WIFSTOPPED(status))
        {
            printf("PARENT: child №%d (PID = %d) has been stopped because of signal: %d\n", i + 1, childpid, WSTOPSIG(status));
        }
    }
    char buf[15];
    close(fd[1]);
    read(fd[0], buf, 15);
    printf("PARENT: received messages:\n%s", buf);
    return OK;
}