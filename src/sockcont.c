#include <myhdr.h>
#include <mystructure.h>
#include <func.h>

int sockConnection(char *argv) 
{
    int sockfd;
    struct sockaddr_in server_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, argv, &server_addr.sin_addr.s_addr) < 0) {
        perror("inet_pton");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        return -1;
    }

    return sockfd;
}