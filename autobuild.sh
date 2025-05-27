#!/bin/bash
set -eux

# A InitRAMfs /init .
# Copyright (C) 2025  Wdboyes13

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; **version 2 of the License only**.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, see
# <https://www.gnu.org/licenses/>.

if [ ! -d "$(pwd)/build" ]; then
    meson setup build --cross-file arm-linux.cross -Dprefix=$(pwd)/dist
fi
	
ninja -C build
ninja -C build install
exit 0
