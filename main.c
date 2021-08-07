#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>

#define EVENT_FILE "/dev/input/event3"
#define EVCODE_DEPRESS 1
#define EVCODE_RELEASE 0

/*
 * create struct to take in key and command
 * and create function to read struct and run through if statment in while loop
 * create config.def.h and custom rc file in config folder later
 * */

int main(int argc, char **argv) {
    struct input_event ev;
    int fd = open(EVENT_FILE, O_RDONLY);

    char command[30];
    strcpy(command, "amixer -q sset Master 3%-");
    while(1) {
        read(fd, &ev, sizeof(ev));
        fflush(stdout);
        if(ev.value == EVCODE_DEPRESS) {
            if(ev.code == KEY_VOLUMEDOWN) {
                system(command);
            }
        }
    }
    close(fd);

    return 0;
}
