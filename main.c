/*
 * See LICENSE file for copyright and license details.
 * Author: Lukas Nitzsche
 * multikey
 */

#include <stdio.h>

#include "main.h"

int main(int argc, char **argv) {
    TODO("Upload to AUR.\n \
          Find better logo.\n \
          Add a clipboard drop down menu to show last thing in clipboard. Seperate Module\n \
          Parameter handeling for things like default keyboard in a seperate module(.c/.h)?\n \
          Auto start feature?\n \
          README.md ![Screenshot](https://lukasn.xyz/path/to/screenshot)\n \
          List of keyboards to activate and deactivate the 'binding mode' on.\n \
          Implement a settings window so that the user can choose what keys to bind on each keyboard.\n \
          Toggle dark mode.");

    gtk_init(&argc, &argv);

    /* dark mode */
    g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE, NULL);

    multikey = app_indicator_new("multikey", share_dir("multikey_logo.png"), APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
    app_indicator_set_label(multikey, "multikey", "");
    app_indicator_set_status(multikey, APP_INDICATOR_STATUS_ACTIVE);

    GtkWidget *menu = gtk_menu_new();

    /* title */
    title = gtk_menu_item_new_with_label("Multikey");
    gtk_widget_set_name(title, "multikey_title");
    gtk_widget_set_halign(title, GTK_ALIGN_START);
    gtk_widget_set_sensitive(title, FALSE);

    /* add seperator widget */
    separator_menu_widget = gtk_separator_menu_item_new();

    /* sys info widget */
    sys_info_widget = gtk_menu_item_new();
    gtk_widget_set_name(sys_info_widget, "sys_info_widget");
    gtk_widget_set_sensitive(sys_info_widget, TRUE);

    /* keyboard cleaning mode */
    keyboard_cleaning_widget = gtk_check_menu_item_new_with_label("Keyboard Cleaning");
    g_signal_connect(keyboard_cleaning_widget, "activate", G_CALLBACK(on_keyboard_cleaning_mode), NULL);

    /* quit widget */
    menu_quit_widget = gtk_menu_item_new_with_label("Quit");
    g_signal_connect(menu_quit_widget, "activate", G_CALLBACK(quit_callback), NULL);

    /* add widgets to menu */
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), title);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), separator_menu_widget);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), sys_info_widget);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), keyboard_cleaning_widget);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_quit_widget);

    /* gtk widget menu setup */
    app_indicator_set_menu(multikey, GTK_MENU(menu));
    gtk_widget_show_all(menu);

    /* updates */
    update_sys_info(NULL);
    g_timeout_add_seconds(1, (GSourceFunc)update_sys_info, NULL);

    gtk_main();

    g_object_unref(multikey);

    return 0;
}
