#include "common.h"

guint16 triggerd_port(GError **error) {
  const gchar *port_str = g_getenv("TRIGGERD_PORT");

  if (!port_str)
    return TRIGGERD_PORT;

  guint64 port;

  if (!g_ascii_string_to_unsigned(port_str, 10, 1, G_MAXUINT16, &port, error))
    return 0;

  return (guint16)port;
}

GSocketAddress *triggerd_socket_address_new(GError **error) {
  guint16 port = triggerd_port(error);

  if (!port)
    return NULL;

  return G_SOCKET_ADDRESS(g_inet_socket_address_new(
      g_inet_address_new_loopback(G_SOCKET_FAMILY_IPV6), port));
}

GSocket *triggerd_socket_new(GError **error) {
  return g_socket_new(G_SOCKET_FAMILY_IPV6, G_SOCKET_TYPE_DATAGRAM,
                      G_SOCKET_PROTOCOL_UDP, error);
}

gsize triggerd_socket_min_rcvbuf(GSocket *socket, GError **error) {
  gint rcvbuf_size;

  if (!g_socket_set_option(socket, SOL_SOCKET, SO_RCVBUF, 1, error))
    return 0;

  if (!g_socket_get_option(socket, SOL_SOCKET, SO_RCVBUF, &rcvbuf_size, error))
    return 0;

  return (gsize)rcvbuf_size;
}

gboolean triggerd_setup(GSocket **socket, GSocketAddress **address,
                        gchar **rcvbuf, gsize *rcvbuf_size, GError **error) {
  *address = triggerd_socket_address_new(error);

  if (!*address)
    return FALSE;

  *socket = triggerd_socket_new(error);

  if (!*socket)
    return FALSE;

  *rcvbuf_size = triggerd_socket_min_rcvbuf(*socket, error);

  if (*rcvbuf_size < 0)
    return FALSE;

  *rcvbuf = g_malloc0(*rcvbuf_size);

  return TRUE;
}
