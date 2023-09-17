#include <libxfce4panel/libxfce4panel.h>
#include <gtk/gtk.h>

static void construct(XfcePanelPlugin *plugin);

const char * format = "%s%s%s";
const char * blackHeart = "<span foreground='black' size='14336'>&#x2764;</span>";
const char * redHeart = "<span foreground='red' size='14336'>&#x2764;</span>";

const char * getHeart(int heartOn)
{
    return heartOn ? redHeart : blackHeart;
}

static void clock_update(GtkLabel *clock)
{
    int hour = g_date_time_get_hour(g_date_time_new_now_local());
    int count = 0;

    if (hour <= 7) {
        count = 0;
    } else {
        switch (hour) {
            case 23: count = 1; break;
            case 22: count = 2; break;
            default: count = 3; break;
        }
    }

    gchar *text = g_strdup_printf(format, getHeart(count == 3), getHeart(count >=2), getHeart(count >= 1));
    gtk_label_set_markup(clock, text);
    g_free(text);
}

static gboolean clock_update_interval(GtkLabel *clock)
{
    clock_update(clock);
    return TRUE;
}

static void construct(XfcePanelPlugin *plugin)
{
    GtkWidget *clock = gtk_label_new(NULL);
    gtk_container_add(GTK_CONTAINER(plugin), clock);
    gtk_widget_show(clock);

    clock_update(GTK_LABEL(clock));

    g_timeout_add_seconds(5, G_SOURCE_FUNC(clock_update_interval), clock);
}

XFCE_PANEL_PLUGIN_REGISTER(construct);
