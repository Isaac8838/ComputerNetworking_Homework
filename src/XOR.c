#include <myhdr.h>
#include <mystructure.h>
#include <func.h>

void XOR(struct Msgbuf *msgbuf, char *id)
{
    int i;
    for (i = 0; i < strlen(msgbuf->context); i++) {
        msgbuf->context[i] = msgbuf->context[i] ^ id[i];
    }
    msgbuf->context[i] = '\0';
}