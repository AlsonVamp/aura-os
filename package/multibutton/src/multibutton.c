/*
 *  Button events handler
 *
 *  leds use oneshot trigger from /lib/modules/[your kernel release]/kernel/drivers/leds/trigger 
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


void blink_led() {
    int fd;
    char d = '1';
    fd = open("/sys/class/leds/aura:led1/shot", O_WRONLY);
    if(fd == -1){
        printf("Led trigger unavailable\n");
    } else {
        write (fd, &d, 1);
        close(fd);
    }
}

void short_press_handle()
{
    blink_led();
    printf("Short press\n");
}

void long_press_handle()
{
    blink_led();
    system("shutdown -P now");
}

int main()
{

    const char *dev = "/dev/input/multibutton";
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
