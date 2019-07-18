#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    pid_t pid = fork();

    if (0 == pid)
    {
        printf("i am child process.\n");
    }else
    {
        printf("my child pid is: %d\n", pid);
        sleep(10);
    }

    if(0 == pid)
        printf("End child process.\n");
    else
        printf("End parent process.\n");

    return 0;
}
