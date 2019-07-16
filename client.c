#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

void error_handling(char* message)
{
    fputs(message, stderr);
    exit(-1);
}

int main(int argc, char const *argv[])
{

    int clnt_sock;
    char message[BUF_SIZE];
    int str_len, recv_len, recv_cnt;
    struct sockaddr_in serv_adr;

    if (argc != 3)
    {
        printf("Usage : %s  <ip> <port>\n", argv[0]);
        exit(-1);
    }

    //设置socket连接
    clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(clnt_sock == -1)
        error_handling("socket() error!");
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error!");
    else
        puts("Connected......");
    
    while (1)
    {
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        
        str_len = write(clnt_sock, message, strlen(message));

        recv_len = 0;
        while(recv_len < str_len)
        {
            recv_cnt = read(clnt_sock, &message[recv_len], BUF_SIZE-1);
            if(recv_cnt == -1)
                error_handling("read() error");
            recv_len += recv_cnt;
        }
        message[recv_len] = 0;
        printf("Message from server: %s", message);  
    }

    close(clnt_sock);
    
    return 0;
}
