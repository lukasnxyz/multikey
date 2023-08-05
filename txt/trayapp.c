#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>

AppIndicator *indicator;

void quit_callback(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void hello_world(GtkWidget *widget, gpointer data) {
    system("$TERMINAL");
}

int main(int argc, char** argv) {
    gtk_init(&argc, &argv);

    indicator = app_indicator_new("my-indicator", "logo.png", APP_INDICATOR_CATEGORY_APPLICATION_STATUS);

    app_indicator_set_label(indicator, "Hello", "");
    app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);

    GtkWidget *menu = gtk_menu_new();

    GtkWidget *menuItem = gtk_menu_item_new_with_label("Quit");
    g_signal_connect(menuItem, "activate", G_CALLBACK(quit_callback), NULL);

    GtkWidget *menuItem2 = gtk_menu_item_new_with_label("Hello!");
    g_signal_connect(menuItem2, "activate", G_CALLBACK(hello_world), NULL);


    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem2);
    gtk_widget_show_all(menu);


    app_indicator_set_menu(indicator, GTK_MENU(menu));

    gtk_main();

    g_object_unref(indicator);

    return 0;
}
