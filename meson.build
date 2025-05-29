project('initramfs-init', 'c', version: '1.5.0', license: 'GPL-2.0')

cc = meson.get_compiler('c')

inc_dirs = include_directories('include', 'helpers')
libdir = meson.project_source_root() / 'lib'

helpers = files(
    'helpers/fsld.c',
    'helpers/mods.c',
    'helpers/sysmnt.c'
)

unc_inc_srcs = files('include/utillinux/switch_root.c')

# Grab source files
srcs = files('init.c') + helpers + unc_inc_srcs

# Define external libraries
deps = [
  cc.find_library('blkid', required: true, dirs: libdir),
  cc.find_library('kmod', required: true, dirs: libdir),
  cc.find_library('pthread', required: true, dirs: libdir),
]

# Build target
exe = executable(
  'init.uns',
  srcs,
  include_directories: inc_dirs,
  c_args: ['-static', '-fno-pie', '-O2'],
  link_args: ['-static', '-no-pie'],
  dependencies: deps,
  install: false
)
