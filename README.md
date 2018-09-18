# triggerd

A UDP based activation mechanism.

When daemon receives a packet, it runs an arbitrary program from its ARGV using
`execvp(3)`.  While program keeps running, there is just one slot that can take
another packet. If that slot is occupied, immediately after program quits, it
will be started again.

Packet contents are not processed in any way. In other words, UDP is used for
signaling, not for data transfer.

Additional packets after the first one will be discarded.

Comes with `trigger`, a client that sends a UDP packet to the daemon. You can
also send packets from any other program, but do mind that packet size should
be equal to [`SOCK_MIN_RCVBUF`][SOCK_MIN_RCVBUF].

Together, `trigger` and `triggerd` form a multi-call binary: the former is just
a symlink to the latter. The reason is that most code (socket setup, address
creation, inferring `SOCK_MIN_RCVBUF`) are be shared between the two.

[SOCK_MIN_RCVBUF]: https://github.com/torvalds/linux/blob/v4.19-rc4/include/net/sock.h#L2185 

This is a very opinionated queue mechanism and should be used only when
appropriate. It has been designed for continuous deployment via `triggerd
nixos-rebuild switch`, where one can enqueue a rebuild just by sending a UDP
packet, while at the same rebuilding only once for any N of requests.
