#include <myhdr.h>
#include <mystructure.h>
#include <func.h>

int main(int argc, char **argv) 
{

    if (argc > 2 || argc < 2) {
        fprintf(stderr, "number of arguments wrong!\n");
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct Msgbuf msgbuf = {101, "410921236"};

    if ((sockfd = sockConnection(argv[1])) < 0) {
        exit(EXIT_FAILURE);
    }

    
    if (write(sockfd, &msgbuf, sizeof(struct Msgbuf)) < 0) {
        perror("write");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    if (read(sockfd, &msgbuf, sizeof(struct Msgbuf)) < 0) {
        perror("read");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (msgbuf.mtype == 401) {
        fprintf(stderr, "failed: %ld\n", msgbuf.mtype);
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    else if (msgbuf.mtype != 201) {
        fprintf(stderr, "unexpected type: %ld\n", msgbuf.mtype);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    msgbuf.mtype = 300;
    XOR(&msgbuf, "10921236");
    if (write(sockfd, &msgbuf, sizeof(struct Msgbuf)) < 0) {
        perror("write");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    if (read(sockfd, &msgbuf, sizeof(struct Msgbuf)) < 0) {
        perror("read");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (msgbuf.mtype == 203) {
        printf("passed\n");
        close(sockfd);
        exit(EXIT_SUCCESS);
    }
    if (msgbuf.mtype == 403) {
        fprintf(stderr, "failed: %ld\n", msgbuf.mtype);
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    else {
        fprintf(stderr, "unexpected type: %ld\n", msgbuf.mtype);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    close(sockfd);
    exit(EXIT_FAILURE);
}