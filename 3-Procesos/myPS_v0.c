#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int pid = getpid();
    char buf[80];
    fork();
    if (pid == getpid()) {
        sprintf(buf,"El pid del padre es %d\n", pid);
    }
    else {
        sprintf(buf,"El pid del hijo es %d\n", getpid());
        write(1,buf,strlen(buf));
        sprintf(buf,"El parametro es %s\n", argv[1]);
    }
    write(1,buf,strlen(buf));
    
    while (1) {
        
    }
}
