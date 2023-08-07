#include "widgets.h"

int keyboard_cleaning_mode = 0;

AppIndicator *multikey;

GtkWidget *title;
GtkWidget *separator_menu_widget;
GtkWidget *sys_info_widget;
GtkWidget *keyboard_cleaning_widget;
GtkWidget *menu_quit_widget;

void quit_callback(GtkWidget *widget, gpointer data) {
    if(keyboard_cleaning_mode) {
        on_keyboard_cleaning_mode(NULL, NULL);
    }

    gtk_main_quit();
}

double get_memory() {
    FILE* mem_file = fopen("/proc/meminfo", "r");

    if (mem_file == NULL) {
        ERR("Failed to open memory file!");
    }

    unsigned long mem_free = 0;
    unsigned long mem_total = 0;
    unsigned long mem_used = 0;

    char line[128];
    while (fgets(line, sizeof(line), mem_file)) {
        if (sscanf(line, "MemTotal: %lu kB", &mem_total) == 1) {
            continue;
        } else if (sscanf(line, "MemAvailable: %lu kB", &mem_free) == 1) {
            continue;
        }
    }

    fclose(mem_file);

    mem_used = mem_total - mem_free;

    double mem_used_g = (double)(mem_used) / (1024.0 * 1024.0);

    return mem_used_g;
}

double get_storage() {
    const char *path = "/";

    struct statvfs stat;
    if (statvfs(path, &stat) != 0) {
        ERR("Filed to retreive storage usage!");
    }

    unsigned long long block_size = stat.f_frsize;
    unsigned long long total_blocks = stat.f_blocks;
    unsigned long long free_blocks = stat.f_bfree;
    unsigned long long used_blocks = total_blocks - free_blocks;

    double used_size_gb = (double)(block_size * used_blocks) / (1024 * 1024 * 1024);

    return used_size_gb;
}

char *get_cpu_temp() {
    TODO("Find a way to get cpu temp directly from system not using\n \
          an external command. (Reduces portability)");

    char output[1025];
    FILE *cpu_cmd = popen("sensors | grep \"CPU\" | awk '{ print $2 }'", "r");

    if (cpu_cmd == NULL) {
        ERR("Failed to run command!");
    }

    while (fgets(output, sizeof(output), cpu_cmd) != NULL);

    char *ret_output = output;
    fclose(cpu_cmd);

    return ret_output;
}

gboolean update_sys_info(gpointer data) {
    TODO("Find alternative to printing awesome font directly.");

    double memory = get_memory();
    char *cpu_temp = get_cpu_temp();
    double storage = get_storage();

    char label[30];
    size_t len = strlen(cpu_temp);

    if(cpu_temp[len - 1] == '\n')
        cpu_temp[len - 1] = '\0';

    sprintf(label, "  %s   %.2fGB   %.0fGB", cpu_temp, memory, storage);
    gtk_menu_item_set_label(GTK_MENU_ITEM(sys_info_widget), label);

    return G_SOURCE_CONTINUE;
}

void on_keyboard_cleaning_mode(GtkMenuItem *menu_item, gpointer data) {
    gboolean active = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item));
    char *keyboard;
    char cmd[80];
    int c;
    int i = -1;
    unsigned int size;

    FILE *keyboard_fp = fopen(share_dir("multikey_default.txt"), "r");
    if(keyboard_fp == NULL) {
        ERR("Failed to open file!");
    }

    fseek(keyboard_fp , 0L , SEEK_END);
    size = ftell(keyboard_fp);
    rewind(keyboard_fp);

    keyboard = calloc(1, size+1);

    while(EOF != (c = fgetc(keyboard_fp)) && ++i < size) {
        keyboard[i] = c;
    }

    if(keyboard[size - 1] == '\n')
        keyboard[size - 1] = '\0';

    if(active) {
        g_print("Keyboard cleaning mode activated\n");
        sprintf(cmd, "xinput set-int-prop \"%s\" \"Device Enabled\" 8 0", keyboard);
        keyboard_cleaning_mode = 1; /* keyboard is disabled */
    } else { /* enable keyboard on laptop */
        g_print("Keyboard cleaning mode deactivated\n");
        sprintf(cmd, "xinput set-int-prop \"%s\" \"Device Enabled\" 8 1", keyboard);
        keyboard = 0;
    }

    system(cmd);

    fclose(keyboard_fp);
}

char *get_default_keyboard(void) {
    TODO("Get default keyboard from file and return as string.");

    char *default_keyboard = "";

    return default_keyboard;
}

int num_lines(FILE *fp) {
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

char *share_dir(char *item) {
    char *path = (char*)malloc(45 * sizeof(char));
    sprintf(path, "/usr/share/multikey/%s", item);

    return path;
}
