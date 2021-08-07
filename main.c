#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <linux/input-event-codes.h>

#define EVENT_FILE "/dev/input/event3"
#define EVCODE_DEPRESS 1
#define EVCODE_RELEASE 0

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
        //if(ev.value == evcodeRelease)
         //   printf("%i\n", ev.code);
        if(ev.value == 1) {
            if(ev.code == KEY_GRAVE) {
                system(command);
            }
        }
    }
    close(fd);

    return 0;
}
