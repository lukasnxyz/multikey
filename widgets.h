#ifndef _WIDGET_H
#define _WIDGET_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include <sys/statvfs.h>

#include <sys/types.h>
#include <ifaddrs.h>

#define TODO(notes) \
    do { \
        fprintf(stderr, "Function '%s' todo: %s\n", \
                __func__, notes); \
    } while(0); \

#define FILEMAX 30

typedef struct {
    int id;
    char name[FILEMAX];
} kbd;

extern AppIndicator *multikey;

extern GtkWidget *title;
extern GtkWidget *separator_menu_widget;
extern GtkWidget *sys_info_widget;
extern GtkWidget *local_ip_widget;
extern GtkWidget *keyboard_cleaning_widget;
extern GtkWidget *menu_quit_widget;

double get_storage(void);
char *get_cpu_temp(void);
char *get_local_ip(void);
char *get_default_keyboard(void);

void on_keyboard_cleaning_mode_activated(GtkMenuItem *, gpointer);
void quit_callback(GtkWidget *, gpointer);

gboolean update_sys_info(gpointer);
gboolean update_local_ip(gpointer);

int num_lines(FILE *);
char *share_dir(char *);

#endif /* _WIDGET_H */
