#!/bin/sh

head -c $(cat /proc/sys/net/core/rmem_default) /dev/zero > /dev/udp/localhost/50494
