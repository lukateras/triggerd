project('triggerd', 'c')

glib = dependency('glib-2.0')
gio = dependency('gio-2.0')

executable('trigger', 'trigger.c', dependencies: [glib, gio], install: true)
executable('triggerd', 'triggerd.c', dependencies: [glib, gio], install: true)
