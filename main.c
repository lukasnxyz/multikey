/*
 * See LICENSE file for copyright and license details.
 * MultiKey
 */

#include <stdio.h>

#include "widgets.h"

int main(int argc, char** argv) {
    gtk_init(&argc, &argv);

    indicator = app_indicator_new("my-indicator", shareDir("logo.png"), APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
    app_indicator_set_label(indicator, "MultiKey", "");
    app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);

    GtkWidget *menu = gtk_menu_new();

    /* title */
    title = gtk_menu_item_new_with_label("MultiKey");
    gtk_widget_set_name(title, "MultiKeyTitle");
    gtk_widget_set_halign(title, GTK_ALIGN_START);
    gtk_widget_set_sensitive(title, FALSE);

    /* add seperator widget */
    separatorMenuItem = gtk_separator_menu_item_new();

    /* sys info widget */
    sysInfoWidget = gtk_menu_item_new();
    gtk_widget_set_name(sysInfoWidget, "SysInfoWidget");
    gtk_widget_set_sensitive(sysInfoWidget, TRUE);

    /* show local ip address widget */
    localIpWidget = gtk_menu_item_new();
    gtk_widget_set_name(localIpWidget, "LocalIP");
    gtk_widget_set_sensitive(localIpWidget, TRUE);

    /* keyboard cleaning mode */
    keyboardCleaningMode = gtk_check_menu_item_new_with_label("Keyboard Cleaning");
    g_signal_connect(keyboardCleaningMode, "activate", G_CALLBACK(OnKeyboardCleaningModeActivated), NULL);

    /*
     * keyboards menuQuit
     * settings launch window
     */

    /* quit widget */
    menuQuit = gtk_menu_item_new_with_label("Quit");
    g_signal_connect(menuQuit, "activate", G_CALLBACK(QuitCallback), NULL);

    /* add widgets to menu */
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), title);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), separatorMenuItem);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), sysInfoWidget);
    /*gtk_menu_shell_append(GTK_MENU_SHELL(menu), localIpWidget);*/
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), keyboardCleaningMode);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuQuit);

    /* gtk widget menu setup */
    app_indicator_set_menu(indicator, GTK_MENU(menu));
    gtk_widget_show_all(menu);

    /* updates */
    UpdateSysInfo(NULL);
    g_timeout_add_seconds(1, (GSourceFunc)UpdateSysInfo, NULL);
    /*
    UpdateLocalIp(NULL);
    g_timeout_add_seconds(1, (GSourceFunc)UpdateLocalIp, NULL);
    */

    gtk_main();

    g_object_unref(indicator);

    return 0;
}
