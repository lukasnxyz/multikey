#ifndef _WIDGET_H
#define _WIDGET_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include <sys/statvfs.h>

#include <sys/types.h>
#include <ifaddrs.h>

#define TODO(NOTES) \
    do { \
        fprintf(stderr, "Function '%s' todo: %s\n", \
                __func__, NOTES); \
    } while(0); \

#define ERR(MESSAGE) \
    do { \
        fprintf(stderr, "Error (%s:%i): %s\n", \
                __func__, __LINE__, MESSAGE); \
        exit(EXIT_FAILURE); \
    } while(0); \

extern int keyboard_cleaning_mode;

extern AppIndicator *multikey;

extern GtkWidget *title;
extern GtkWidget *separator_menu_widget;
extern GtkWidget *sys_info_widget;
extern GtkWidget *keyboard_cleaning_widget;
extern GtkWidget *menu_quit_widget;

double get_storage(void);
char *get_cpu_temp(void);
char *get_local_ip(void);
char *get_default_keyboard(void);

void on_keyboard_cleaning_mode(GtkMenuItem *, gpointer);
void quit_callback(GtkWidget *, gpointer);

gboolean update_sys_info(gpointer);
gboolean update_local_ip(gpointer);

int num_lines(FILE *);
char *share_dir(char *);

#endif /* _WIDGET_H */
