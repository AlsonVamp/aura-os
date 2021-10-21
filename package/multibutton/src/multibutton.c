/*
 *  Button events handler
 *
 *  Copyright (C) 2021 Aleksandr Nazarov
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

// List input devices: cat /proc/bus/input/devices
#define MAX_SHORT_PRESS_TIME 1
#define LONG_PRESS_DELAY 4

void short_press_handle()
{
    printf("Short press\n");
}

void long_press_handle()
{
    system("shutdown -P now");
}

int main()
{

    const char *dev = "/dev/input/event0";
    int fd, rd, i;
    int prev_value = 0;
    int action_done = 0;
    time_t pressed_time = time(NULL);
    struct input_event ev[64];

    fd = open(dev, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "Cannot open %s\n", dev);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        rd = read(fd, ev, sizeof(struct input_event) * 64);

        if (rd < (int)sizeof(struct input_event))
        {
            perror("\nSystem button failure");
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < rd / sizeof(struct input_event); i++)
        {

            if (ev[i].type == EV_KEY || ev[i].type == EV_PWR)
            {
                //printf ("time: %ld, code %d, type: %u, value: %d\n", ev[i].time.tv_sec, ev[i].code, ev[i].type ,ev[i].value);
                
                if (ev[i].value && !prev_value)
                {
                    pressed_time = time(NULL);
                }

                prev_value = ev[i].value;

                if (!ev[i].value && ev[i].time.tv_sec - pressed_time <= MAX_SHORT_PRESS_TIME)
                {
                    short_press_handle();
                }

                if (ev[i].time.tv_sec - pressed_time >= LONG_PRESS_DELAY && !action_done)
                {
                    long_press_handle();
                    action_done = 1;
                }
                if (!ev[i].value)
                    action_done = 0;
            }
        }
    }
}
