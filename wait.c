#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
子进程如果是return或者exit退出，而主进程又没有结束，则子进程成为僵尸进程。需要在主进程中对其进行捕捉、销毁
pid_t wait(int *statloc)
wait函数捕捉任意子进程
调用wait 函数时，如果没有已经终止的子进程，则主进程将一直处于阻塞状态。
如果，子进程终止时返回值，则改值将会保存到statloc所在的地址空间。
 */


int main(int argc, char const *argv[])
{
    int status;
    pid_t  pid;
    pid = fork();

    if (0 == pid)
    {
        sleep(10);
        return 3;
    }else
    {
        printf("child pid: %d\n", pid);
        pid = fork();
        if (0 == pid)
        {
            sleep(10);
            exit(7);
        }else
        {
            printf("child pid: %d\n", pid);

            //两个子进程，调用两次wait, wait函数会阻塞主进程
            wait(&status);
            if (WIFEXITED(status))
            {
                printf("Normal termination!\n");
                printf("child pass num: %d\n", WEXITSTATUS(status));
            }

            wait(&status);
            if (WIFEXITED(status))
            {
                printf("Normal termination!\n");
                printf("child pass num: %d\n", WEXITSTATUS(status));
            }
            
            sleep(30);
        }
        
    }
    
    return 0;
}
