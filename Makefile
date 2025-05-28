DOCS := \
	README LICENSE LegalStuff GPLv2

CONFS := \
	meson.build Makefile arm-linux.cross .gitignore

PKG_FILES := \
	deps helpers include lib init.c \
	$(CONFS) $(DOCS)

BUILD := build
DEST := $(shell pwd)/dist
CONFIG := arm-linux.cross

all: build git

setup:
	meson setup $(BUILD) --cross-file $(CONFIG) -Dprefix=$(DEST)

build:
	ninja -C $(BUILD)

install: build
	ninja -C $(BUILD) install

pkg: build
	mkdir staging/
	cp -r $(PKG_FILES) staging/
	zip -9r initsrc.zip staging/
	tar cvf - staging/ | zstd -9c > initsrc.tar.zst
	rm -rf staging

git: build
	git add .
	git commit -m "Updated $(shell date)"
	git push origin main

clean:
	rm -rf $(BUILD) $(DEST) initsrc.tar.* initsrc.zip

.PHONY: all setup build install pkg git clean