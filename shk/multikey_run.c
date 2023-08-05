#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>

#define EVCODE_DEPRESS 1
#define EVCODE_RELEASE 0
#define MAX 30

typedef struct {
    unsigned int keyNum;
    char inComm[256];
} Key;

#include "config.h"

void runKbd(int id) {
    char ef[19];
    snprintf(ef, sizeof(ef), "/dev/input/event%d", id);

    struct input_event ev;
    int fd = open(ef, O_RDONLY);

    while(1) {
        read(fd, &ev, sizeof(ev));
        if(ev.value == EVCODE_DEPRESS) {
            for(int j = 0; j <= (sizeof(keys) / sizeof(keys[0])); j++) {
                if(ev.code == keys[j].keyNum) {
                    system(keys[j].inComm);
                }
            }
        }
    }
    close(fd);
}

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }
    int number = atoi(argv[1]);

    runKbd(number);

    return 0;
}
