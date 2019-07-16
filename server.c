#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/*

struct sockaddr_in
{
    sa_family   sin_family;  //地址族（Address Family）
    uint16_t    sin_port;   //端口
    struct in_addr  sin_addr;   //ip地址
    char    sin_zero[8] //不使用
};

struct in_addr
{
    in_addr_t s_addr;   //ip地址
};

struct sockaddr
{
    sa_family_t sin_family;
    char    sa_data[14];
};

*/

#define BUF_SIZE 1024
void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(-1);
}

int main(int argc, char const *argv[])
{
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(-1);
    }

    //分配socket
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);    //指定协议族和套接字类型(面向连接的，TCP)
    if(serv_sock == -1)
        error_handling("socket() error!");

    //设置serv_adr参数，ip&&端口
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htol(INADDR_ANY);//获取本机IP，并且转换成大端保存
    serv_adr.sin_port = htos(atoi(argv[1]));

    //绑定套接字
    if (bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind error!");

    //监听端口
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error!");

    clnt_adr_sz = sizeof(clnt_adr);
    for (int i = 0; i < 5; ++i)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_adr, &clnt_adr_sz);
        if (clnt_sock == -1)
            error_handling("accept() error!");
        else
            printf("Connected client %d\n", i+1);

        while((str_len=read(clnt_sock, message, BUF_SIZE)) != 0)
            write(clnt_sock, message, str_len);

        close(clnt_sock);
    }

    close(serv_sock);

    return 0;
}