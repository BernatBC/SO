#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void error_y_exit(char *msg, int exit_status) {
    perror(msg);
    exit(exit_status);
}

void muta_a_PS(char *username) {
    execlp("ps", "ps", "-u", username, (char*)NULL);
    error_y_exit("Ha fallado la mutacion al ps", 1);
}

int main(int argc, char *argv[]) {
    int pid = getpid();
    char buf[80];
    fork();
    if (pid == getpid()) {
        sprintf(buf,"El pid del padre es %d\n", pid);
        write(1,buf,strlen(buf));
    }
    else {
        sprintf(buf,"El pid del hijo es %d\n", getpid());
        write(1,buf,strlen(buf));
        sprintf(buf,"El parametro es %s\n", argv[1]);
        write(1,buf,strlen(buf));
        muta_a_PS(argv[1]);
    }
    while (1) {
        
    }
}
