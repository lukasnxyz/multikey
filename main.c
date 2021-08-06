#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

#define EVENT_FILE "/dev/input/event3"

int main(int argc, char **argv) {
    struct input_event ev;
    bool con = true;
    int fd = open(EVENT_FILE, O_RDONLY);

    // char *map = "..1234567890-=..qwertyuiop[]\n.asdfghjkl;'~^\\zxcvbnm,./^.. .";
    // printf("%c", map[ev.code]);

    char command[10];
    strcpy(command, "st &");
    while(con) {
        read(fd, &ev, sizeof(ev));
        fflush(stdout);
        if(ev.value == 1) {
            if(ev.code == 41) {
            system(command);
            }
        }
    }
    close(fd);

    return 0;
}
