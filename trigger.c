#include "common.h"

gboolean trigger(GError **error) {
  TRIGGERD_SETUP(error);

  if (!setup)
    return FALSE;

  if (!g_socket_connect(socket, address, NULL, error))
    return FALSE;

  if (g_socket_send(socket, rcvbuf, rcvbuf_size, NULL, error) < 0)
    return FALSE;

  return TRUE;
}

gint main(const gint argc, const gchar *const *argv) {
  g_autoptr(GError) error;

  if (argc > 1) {
    g_printerr("Usage: %s\n", argv[0]);
    return TRIGGERD_EXIT_USAGE;
  }

  if (!trigger(&error)) {
    g_printerr("%s\n", error->message);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
