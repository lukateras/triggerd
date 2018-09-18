# triggerd

`triggerd` (and accompanying client, `trigger`) is a UDP based activation
mechanism.

When daemon receives a packet, it runs an arbitrary program from its ARGV using
`execvp(3)`.  While program keeps running, there is just one slot that can take
another packet. If that slot is occupied, immediately after program quits, it
will be started again.

Packet contents are not processed in any way. In other words, UDP is used for
signaling, not for data transfer.

Additional packets after the first one will be discarded.

`trigger` is just an executable that sends a UDP packet to the daemon. You can
also send packets from any other program, but do mind that it should fill the
whole queue (i.e. `SOCK_MIN_RCVBUF`). It's OK to send more, but not less. To be
safe, I recommend using `/proc/sys/net/core/rmem_default` value.

This is a very opinionated queue mechanism and should be used only when
appropriate. It has been designed for continuous `nixos-rebuild switch`.
