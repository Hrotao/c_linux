#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>

static char gpio_path[100];

static int gpio_config(const char *attr, const char *val)
{
    char file_path[100];
    int len;
    int fd;
    sprintf(file_path, "%s/%s", gpio_path, attr);
    if (0 > (fd = open(file_path, O_WRONLY)))
    {
        perror("open error");
        return fd;
    }
    len = strlen(val);
    if (len != write(fd, val, len))
    {
        perror("write error");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

int main(int argc,char *argv[]){
    struct  pollfd pfd;
    char file_path[100];
    int ret;
    char val;
    if(2!=argc){
        fprintf(stderr, "usage:%s<gpio>\n",argv[0]);
        exit(-1);
    }
}