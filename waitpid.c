#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
相比于wait函数，waitpid函数能够防止主进程进入阻塞状态。
pid_t waitpid(pid_t pid, int *statloc, int options);
waitpid可以指定要捕捉的子进程，通过pid指定，如果pid=-1，则可以捕捉任意子进程。
options是常量，传递<sys/wait.h>中的常量WNOHANG可以保证即使没有终止的子进程，则主进程也不会阻塞。
 */

int main(int argc, char const *argv[])
{
    int status;
    pid_t pid;
    pid = fork();

    if (0 == pid)
    {
        sleep(15);
        return 24;
    }else
    {
        while (!waitpid(-1, status, WNOHANG))
        {
            sleep(3);
            puts("parent sleep 3 seconds.\n");
        }

        if (WIFEXITED(status))
        {
            printf("child pass num: %d\n", WEXITSTATUS(status));
        }
        
    }

    return 0;
}
