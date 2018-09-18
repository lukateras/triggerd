#!/usr/bin/env bash

head -c "$(< /proc/sys/net/core/rmem_default)" /dev/zero > /dev/udp/localhost/51161
