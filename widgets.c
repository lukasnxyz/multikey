#include "widgets.h"

AppIndicator *indicator;

GtkWidget *title;
GtkWidget *separatorMenuItem;
GtkWidget *sysInfoWidget;
GtkWidget *localIpWidget;
GtkWidget *keyboardCleaningMode;
GtkWidget *menuQuit;

void QuitCallback(GtkWidget *widget, gpointer data) {
    /*
     * check if keyboard is disabled and enable if so
     * */
    gtk_main_quit();
}

double GetMemory() {
    FILE* memFile = fopen("/proc/meminfo", "r");

    if (memFile == NULL) {
        fprintf(stderr, "Failed to open /proc/meminfo\n");
        return 1;
    }

    unsigned long mem_free = 0;
    unsigned long mem_total = 0;
    unsigned long mem_used = 0;

    char line[128];
    while (fgets(line, sizeof(line), memFile)) {
        if (sscanf(line, "MemTotal: %llu kB", &mem_total) == 1) {
            continue;
        } else if (sscanf(line, "MemAvailable: %llu kB", &mem_free) == 1) {
            continue;
        }
    }

    fclose(memFile);

    mem_used = mem_total - mem_free;

    double mem_used_g = (double)(mem_used) / (1024.0 * 1024.0);

    return mem_used_g;
}

double GetStorage() {
    const char *path = "/";

    struct statvfs stat;
    if (statvfs(path, &stat) != 0) {
        perror("Failed to get storage usage");
        return -1;
    }

    unsigned long long blockSize = stat.f_frsize;
    unsigned long long totalBlocks = stat.f_blocks;
    unsigned long long freeBlocks = stat.f_bfree;
    unsigned long long usedBlocks = totalBlocks - freeBlocks;

    double totalSizeGB = (double)(blockSize * totalBlocks) / (1024 * 1024 * 1024);
    double usedSizeGB = (double)(blockSize * usedBlocks) / (1024 * 1024 * 1024);

    return usedSizeGB;
}

char *GetCpuTemp() {
    char output[1025];
    FILE *cpuCommand = popen("sensors | grep \"CPU\" | awk '{ print $2 }'", "r"); /* fix this so that it's not dependent on another program */
    if (cpuCommand == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output), cpuCommand) != NULL)
        ;

    char *returnOutput = output;
    fclose(cpuCommand);

    return returnOutput;
}

gboolean UpdateSysInfo(gpointer data) {
    double memory = GetMemory();
    char *cpuTemp = GetCpuTemp();
    double storage = GetStorage();

    char label[30];
    size_t len = strlen(cpuTemp);

    if(cpuTemp[len - 1] == '\n')
        cpuTemp[len - 1] = '\0';

    sprintf(label, "  %s   %.2fGB   %.0fGB", cpuTemp, memory, storage); /* find awesome font alternative */
    gtk_menu_item_set_label(GTK_MENU_ITEM(sysInfoWidget), label);

    return G_SOURCE_CONTINUE;
}

char *getLocalIp() {
    char *localIp = "==Ip under development==";

    return localIp;
}

gboolean UpdateLocalIp(gpointer data) {
    char label[26];
    sprintf(label, "%s", getLocalIp());
    gtk_menu_item_set_label(GTK_MENU_ITEM(localIpWidget), label);

    return G_SOURCE_CONTINUE;
}

void OnKeyboardCleaningModeActivated(GtkMenuItem *menuitem, gpointer data) {
    gboolean active = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem));
    char *keyboard;
    char command[80];
    int c;
    int i = -1;
    unsigned int size;

    FILE *keyboardFile = fopen(shareDir("keyboard.txt"), "r");
    if(keyboardFile == NULL) {
        fprintf(stderr, "Failed to open file!\n");
    }

    fseek(keyboardFile , 0L , SEEK_END);
    size = ftell(keyboardFile);
    rewind(keyboardFile);

    keyboard = calloc(1, size+1);

    while(EOF != (c = fgetc(keyboardFile)) && ++i < size) {
        keyboard[i] = c;
    }

    if(keyboard[size - 1] == '\n')
        keyboard[size - 1] = '\0';

    if(active) { /* disable keyboard on laptop */
        g_print("Keyboard cleaning mode activated\n");
        sprintf(command, "xinput set-int-prop \"%s\" \"Device Enabled\" 8 0", keyboard);
    } else { /* enable keyboard on laptop */
        g_print("Keyboard cleaning mode deactivated\n");
        sprintf(command, "xinput set-int-prop \"%s\" \"Device Enabled\" 8 1", keyboard);
    }

    system(command);

    fclose(keyboardFile);
}

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

char *shareDir(char *item) {
    char *homePath = getenv("HOME");
    char *path = (char*)malloc(45 * sizeof(char));
    sprintf(path, "%s/.local/share/%s", homePath, item);

    return path;
}
