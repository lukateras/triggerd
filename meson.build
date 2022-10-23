project('triggerd', 'c', version: '1')

glib = dependency('glib-2.0')
gio = dependency('gio-2.0')

executable('trigger', ['common.c', 'trigger.c'], dependencies: [glib, gio], install: true)
install_man('trigger.1')

executable('triggerd', ['common.c', 'triggerd.c'], dependencies: [glib, gio], install: true)
install_man('triggerd.8')
