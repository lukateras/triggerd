![trigger + triggerd](logo.svg)

Simplistic UDP-based scheduler with a single slot queue.

I hope that you find `trigger` + `triggerd` useful 💚💜

## Installation

- Arch Linux: [`triggerd`]() (AUR)
- macOS: [`yanalunaterra/triggerd`]() (Homebrew tap)

## Example

```sh
$ triggerd make &

$ trigger # Schedule a build
$ trigger # Schedule another build
          # (Make will be restarted upon completion)
$ trigger # Attempt to schedule yet another build
          # (has no effect if Make is still running)
```

## Overview

`triggerd` listens on IPv6 loopback UDP port 51161 (overridable by setting
`TRIGGERD_PORT` environment variable).

When `triggerd` receives a packet, it executes a program from its command-line
arguments. While this program keeps running, there is a single slot that can
take another packet. If the slot is taken by the time the program exits, it will
be immediately restarted. Once the slot is taken, additional received packets
have no effect until the program is restarted and the slot is emptied.

`trigger` sends a packet to `triggerd`.

For details, consult `trigger(1)` and `triggerd(8)` man pages.

## Attribution

Prototype sponsored by [Serokell][].

[Clone Rounded PE][] logo font by Lasko Džurovski from [Rosetta Type Foundry][].

On/off switch logo icon by [Tanya Nevskaya][].

Social preview background pattern by Steve Schoger from [Hero Patterns][],
licensed under [CC BY 4.0][].

[Serokell]: https://serokell.io
[Clone Rounded PE]: https://rosettatype.com/CloneRoundedPE
[Tanya Nevskaya]: https://unparalloser.com
[Rosetta Type Foundry]: https://rosettatype.com
[Hero Patterns]: https://heropatterns.com
[CC BY 4.0]: https://creativecommons.org/licenses/by/4.0/

---

`trigger` + `triggerd` were designed for continuous deployment on [NixOS][]:
`triggerd nixos-rebuild switch` rebuilds the system on request while
deduplicating consecutive rebuild requests; `trigger` requests a system
rebuild.

One caveat to be aware of: all users on a system typically have access to UDP.
Do not use `triggerd` with anything that can lead to privilege escalation. If
internal denial-of-service is a concern for you, set up a firewall policy that
limits `triggerd` port access to a trusted group.

[NixOS]: https://nixos.org
