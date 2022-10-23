#pragma once

#include <gio/gio.h>
#include <gio/gnetworking.h>
#include <glib.h>

#define TRIGGERD_EXIT_USAGE 64

#define TRIGGERD_PORT 51161

guint16 triggerd_port(GError **error);

GSocketAddress *triggerd_socket_address_new(GError **error);

GSocket *triggerd_socket_new(GError **error);

gsize triggerd_socket_min_rcvbuf(GSocket *socket, GError **error);

gboolean triggerd_setup(GSocket **socket, GSocketAddress **address,
                        gchar **rcvbuf, gsize *rcvbuf_size, GError **error);

#define TRIGGERD_SETUP(error)                                                  \
  g_autoptr(GSocket) socket;                                                   \
  g_autoptr(GSocketAddress) address;                                           \
  g_autofree gchar *rcvbuf;                                                    \
  gsize rcvbuf_size;                                                           \
  gboolean setup =                                                             \
      triggerd_setup(&socket, &address, &rcvbuf, &rcvbuf_size, error);
