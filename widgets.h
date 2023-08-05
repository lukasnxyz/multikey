#ifndef _WIDGET_H
#define _WIDGET_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include <sys/statvfs.h>

#include <sys/types.h>
#include <ifaddrs.h>

#define FILEMAX 30

typedef struct {
    int id;
    char name[FILEMAX];
} kbd;

extern AppIndicator *indicator;

extern GtkWidget *title;
extern GtkWidget *separatorMenuItem;
extern GtkWidget *sysInfoWidget;
extern GtkWidget *localIpWidget;
extern GtkWidget *keyboardCleaningMode;
extern GtkWidget *menuQuit;

void QuitCallback(GtkWidget *, gpointer);
double GetStorage(void);
char *GetCpuTemp(void);
gboolean UpdateSysInfo(gpointer);
char *getLocalIp(void);
gboolean UpdateLocalIp(gpointer);
void OnKeyboardCleaningModeActivated(GtkMenuItem *, gpointer);

int numLines(FILE *);
char *shareDir(char *);

#endif /* _WIDGET_H */
