NAME := init.uns
EXEC := init
VERSION := 1.6

CC := aarch64-unknown-linux-gnu-gcc
STRIPPER := aarch64-unknown-linux-gnu-strip
CFLAGS := -static -fno-pie -O2 -Iinclude -Ihelpers
LDFLAGS := -static -no-pie

LIBDIR := lib
LDLIBS := -L$(LIBDIR) -lblkid -lkmod

HELPERS := helpers/fsld.c helpers/mods.c helpers/sysmnt.c
UNC_INC_SRCS := include/utillinux/switch_root.c
SRC := init.c $(HELPERS) $(UNC_INC_SRCS)

DIST := dist
UNS_OUT := $(DIST)/$(NAME)
OUT := $(DIST)/$(EXEC)
CLEAN_TARGS := $(UNS_OUT) $(OUT) $(ZIP_TARG) $(ZSTD_TARG)
ZIP := zip -9r
ZIP_TARG := init-src.zip
ZSTD := zstd -9
TAR := tar cvf
ZSTD_TARG := init-src.tar.zst
ARCH_TARGS := README include deps LICENSE LegalStuff lib \
                    arm-linux.cross meson.build autobuild.sh pkg.sh \
                    helpers init.c GPLv2

all: clean init git


$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) $(LDLIBS) -o $(UNS_OUT)

init: $(NAME)
	$(STRIPPER) -o $(OUT) $(UNS_OUT)

clean:
	rm -rf $(CLEAN_TARGS)

pkg: clean
	mkdir staging
	cp -r $(ARCH_TARGS) staging/

	$(ZIP) $(ZIP_TARG) staging/
	$(TAR) - staging/ | $(ZSTD) -c > $(ZSTD_TARG)
	rm -rf staging/

git:
	git add .
	git commit -m "Updated $(shell date)"
	git push origin main

.PHONY: all clean pkg git