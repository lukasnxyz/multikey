#include "widgets.h"

AppIndicator *multikey;

GtkWidget *title;
GtkWidget *separator_menu_widget;
GtkWidget *sys_info_widget;
GtkWidget *local_ip_widget;
GtkWidget *keyboard_cleaning_widget;
GtkWidget *menu_quit_widget;

void quit_callback(GtkWidget *widget, gpointer data) {
    TODO("Check if keyboard is disabled and enable if so.");

    gtk_main_quit();
}

double get_memory() {
    FILE* mem_file = fopen("/proc/meminfo", "r");

    if (mem_file == NULL) {
        fprintf(stderr, "Failed to open /proc/meminfo\n");
        return 1;
    }

    unsigned long mem_free = 0;
    unsigned long mem_total = 0;
    unsigned long mem_used = 0;

    char line[128];
    while (fgets(line, sizeof(line), mem_file)) {
        if (sscanf(line, "MemTotal: %llu kB", &mem_total) == 1) {
            continue;
        } else if (sscanf(line, "MemAvailable: %llu kB", &mem_free) == 1) {
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
        perror("Failed to get storage usage");
        return -1;
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
    FILE *cpu_cmd = popen("sensors | grep \"CPU\" | awk '{ print $2 }'", "r"); /* fix this so that it's not dependent on another program */

    if (cpu_cmd == NULL) {
        fprintf(stderr, "Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output), cpu_cmd) != NULL);

    char *ret_output = output;
    fclose(cpu_cmd);

    return ret_output;
}

gboolean update_sys_info(gpointer data) {
    double memory = get_memory();
    char *cpu_temp = get_cpu_temp();
    double storage = get_storage();

    char label[30];
    size_t len = strlen(cpu_temp);

    if(cpu_temp[len - 1] == '\n')
        cpu_temp[len - 1] = '\0';

    sprintf(label, "  %s   %.2fGB   %.0fGB", cpu_temp, memory, storage); /* find awesome font alternative */
    gtk_menu_item_set_label(GTK_MENU_ITEM(sys_info_widget), label);

    return G_SOURCE_CONTINUE;
}

char *get_local_ip() {
    TODO("Get local ip address.");

    char *local_ip = "IP Address";

    return local_ip;
}

gboolean update_local_ip(gpointer data) {
    char label[26];
    sprintf(label, "%s", get_local_ip());
    gtk_menu_item_set_label(GTK_MENU_ITEM(local_ip_widget), label);

    return G_SOURCE_CONTINUE;
}

void on_keyboard_cleaning_mode_activated(GtkMenuItem *menu_item, gpointer data) {
    gboolean active = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item));
    char *keyboard;
    char cmd[80];
    int c;
    int i = -1;
    unsigned int size;

    FILE *keyboard_fp = fopen(share_dir("multikey_default.txt"), "r");
    if(keyboard_fp == NULL) {
        fprintf(stderr, "Failed to open file!\n");
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

    if(active) { /* disable keyboard on laptop */
        g_print("Keyboard cleaning mode activated\n");
        sprintf(cmd, "xinput set-int-prop \"%s\" \"Device Enabled\" 8 0", keyboard);
    } else { /* enable keyboard on laptop */
        g_print("Keyboard cleaning mode deactivated\n");
        sprintf(cmd, "xinput set-int-prop \"%s\" \"Device Enabled\" 8 1", keyboard);
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
