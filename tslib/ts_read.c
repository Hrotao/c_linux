#include <stdio.h>
#include <stdlib.h>
#include "tslib.h"

/*
struct tsdev *ts_open(const char *dev_name, int nonblock)
struct tsdev *ts_setup(const char *dev_name, int nonblock)
int ts_config(struct tsdev *ts)
int ts_read(struct tsdev *ts, struct ts_sample *samp, int nr)
int ts_read_mt(struct tsdev *ts, struct ts_sample_mt **samp, int max_slots, int nr)
arm-linux-gnueabihf-gcc -I /home/alientek/tslib-1.21/arm-tslib/include -L /home/alientek/linux/nfs/rootfs/usr/lib -lts  ts_read.c -o ts
*/

int main(int argc, char *argv)
{
    struct tsdev *ts = NULL;
    struct ts_sample samp;
    int pressure = 0;
    ts = ts_setup(NULL, 0);
    if (NULL == ts)
    {
        fprintf(stderr, "ts_setup error");
        exit(EXIT_FAILURE);
    }
    for (;;)
    {
        if (0 > ts_read(ts, &samp, 1))
        {
            fprintf(stderr, "ts_read error");
            ts_close(ts);
            exit(EXIT_FAILURE);
        }
        if (samp.pressure)
        {
            if (pressure)
                printf("移动(%d, %d)\n", samp.x, samp.y);
            else
                printf("按下(%d, %d)\n", samp.x, samp.y);
        }
        else
            printf("松开\n"); // 打印坐标
        pressure = samp.pressure;
    }
    ts_close(ts);
    exit(EXIT_SUCCESS);
}
