PLUGIN_NAME = myclock
LIBDIR = /usr/lib/xfce4/panel/plugins
PLUGDIR = /usr/share/xfce4/panel/plugins
CC = gcc
CFLAGS = -I/usr/include/xfce4/libxfce4panel-2.0 `pkg-config --cflags gtk+-3.0` -fPIC
LDFLAGS = `pkg-config --libs gtk+-3.0`

all:
	$(CC) $(CFLAGS) -shared -o lib$(PLUGIN_NAME).so $(PLUGIN_NAME).c $(LDFLAGS)

install:
	install lib$(PLUGIN_NAME).so $(LIBDIR) & install myclock.desktop $(PLUGDIR)
