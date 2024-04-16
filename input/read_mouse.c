#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int main(int argc, char *argv[])
{
    struct input_event in_ev;
    int x, y;
    int down;
    int valid;
    int fd = -1;
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <input-dev>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (0 > (fd = open(argv[1], O_RDONLY)))
    {
        perror("open error");
        exit(EXIT_FAILURE);
    }
    x = y = 0;
    down = 0;
    valid = 0;
    while (1)
    {
        if (sizeof(struct input_event) != read(fd, &in_ev, sizeof(struct input_event)))
        {
            perror("read error");
            exit(EXIT_FAILURE);
        }
        switch (in_ev.type)
        {
        case EV_KEY:
            if (in_ev.code == BTN_LEFT)
            {
                down = 1;
            }
            else if (in_ev.code == BTN_RIGHT)
            {
                down = 2;
            }
            break;
        case EV_REL:
            switch (in_ev.code)
            {
            case REL_X:
                x += in_ev.value;
                valid = 1;
                break;
            case REL_Y:
                y += in_ev.value;
                valid = 1;
                break;
            }
            break;
        case EV_SYN:
            if (SYN_REPORT == in_ev.code)
            {
                if (valid)
                {
                    printf("移动(%d, %d)\n", x, y);
                }
                if (down)
                {
                    if (down == 1)
                        printf("左击\n");
                    else
                        printf("右击\n");
                }
                down = 0;
                valid = 0;
            }
            break;
        }
    }
}