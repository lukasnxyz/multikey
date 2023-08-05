#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

typedef struct {
    int id;
    char name[MAX];
} kbd;

int numLines(FILE *fp) {
    int lines = 0;
    char ch;

    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n')
        {
            lines++;
        }
    }

    return lines;
}

int main() {
    FILE *namesFp = fopen("txt/keyboards.txt", "r");
    FILE *idsFp = fopen("txt/ids.txt", "r");

    int lines = numLines(namesFp);
    rewind(namesFp);

    kbd list[lines];

    char nameTmp[MAX];
    char idTmp[MAX];

    int x = 0;
    while(fgets(nameTmp, sizeof(nameTmp), namesFp)) {
        for(int i = 0; i < MAX; i++) {
            list[x].name[i] = nameTmp[i];
        }
        x++;
    }

    for(int i = 0; i < lines; i++) {
        fscanf(idsFp, "%d", &list[i].id);
    }

    /* print out all keyboards and id's */
    for(int i = 0; i < lines; i++) {
        printf("%s - %d\n", list[i].name, list[i].id);
    }

    return 0;
}
