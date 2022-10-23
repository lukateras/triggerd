#include "common.h"

gboolean triggerd(const gchar *const *argv, GError **error) {
  TRIGGERD_SETUP(error);

  if (!setup)
    return FALSE;

  if (!g_socket_bind(socket, address, FALSE, error))
    return FALSE;

  for (;;) {
    if (g_socket_receive(socket, rcvbuf, rcvbuf_size, NULL, error) < 0)
      return FALSE;

    g_autoptr(GSubprocess) subprocess =
        g_subprocess_newv(argv, G_SUBPROCESS_FLAGS_NONE, error);

    if (!subprocess)
      return FALSE;

    if (!g_subprocess_wait(subprocess, NULL, error))
      return FALSE;
  }
}

gint main(const gint argc, const gchar *const *argv) {
  g_autoptr(GError) error;

  if (argc < 2) {
    g_printerr("Usage: %s cmd ...\n", argv[0]);
    return TRIGGERD_EXIT_USAGE;
  }

  if (!triggerd(&argv[1], &error)) {
    g_printerr("%s\n", error->message);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
