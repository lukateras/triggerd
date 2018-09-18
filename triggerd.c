#include <gio/gio.h>
#include <gio/gnetworking.h>
#include <glib.h>

#include <errno.h>
#include <sys/wait.h>

#define DEFAULT_PORT 51161

#define fail(s, err) g_error("%s: %s: %s", __func__, s, g_strerror(err))
#define fail_if(expr)                                                          \
  if (expr)                                                                    \
    fail(#expr, errno);

int main(gint argc, char **argv) {
  if (argc < 2) {
    g_message("Usage: %s <command>", *argv);
    return EXIT_FAILURE;
  }

  argv++;

  g_autoptr(GSocket) sock =
      g_socket_new(G_SOCKET_FAMILY_IPV6, G_SOCKET_TYPE_DATAGRAM,
                   G_SOCKET_PROTOCOL_UDP, NULL);

  if (sock == NULL)
    fail("g_socket_new", errno);

  gint sock_min_rcvbuf;

  fail_if(g_socket_set_option(sock, SOL_SOCKET, SO_RCVBUF, 0, NULL) == FALSE);
  fail_if(g_socket_get_option(sock, SOL_SOCKET, SO_RCVBUF, &sock_min_rcvbuf,
                              NULL) == FALSE);

  g_autoptr(GSocketAddress) addr = G_SOCKET_ADDRESS(g_inet_socket_address_new(
      g_inet_address_new_loopback(G_SOCKET_FAMILY_IPV6), DEFAULT_PORT));

  fail_if(g_socket_bind(sock, addr, TRUE, NULL) == FALSE);

  gchar ack[sock_min_rcvbuf];

  for (;;) {
    g_socket_receive(sock, ack, sock_min_rcvbuf, NULL, NULL);

    pid_t cpid = fork();

    if (cpid < 0)
      fail("fork", errno);

    else if (cpid == 0) {
      fail_if(execvp(*argv, argv));
    }

    else
      fail_if(waitpid(cpid, NULL, 0) != cpid);
  }
}
