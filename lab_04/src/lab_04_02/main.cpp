#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define ERROR_FORK 1
#define OK 0
int main()
{
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
            sleep(2);
            printf("CHILD №%d LOG pid: %d, ppid: %d, grp: %d\n", i + 1, getpid(), getppid(), getpgrp());
            return OK;
        }

        childpids[i] = pid;
    }
    printf("PARENT LOG pid: %d grp: %d, child's pids: %d, %d\n", getpid(), getpgrp(), childpids[0], childpids[1]);
    for (int i = 0; i < 2; i++)
    {
        int status;
        pid_t childpid = wait(&status);
        if (WIFEXITED(status))
        {
            printf("PARENT LOG child №%d (PID = %d) has finished with code: %d\n", i + 1, childpid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("PARENT LOG child №%d (PID = %d) has finished because of signal: %d\n", i + 1, childpid, WTERMSIG(status));
        }
        else if (WIFSTOPPED(status))
        {
            printf("PARENT LOG child №%d (PID = %d) has been stopped because of signal: %d\n", i + 1, childpid, WSTOPSIG(status));
        }
    }
    return OK;
}