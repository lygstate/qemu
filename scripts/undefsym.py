#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Static library and shared library compare utility
#
# Authors:
#  Yonggang Luo <luoyonggang@gmail.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, see <http://www.gnu.org/licenses/>.

import sys
import subprocess

# Before a shared module's DSO is produced, a static library is built for it
# and passed to this script.  The script generates -Wl,-u options to force
# the inclusion of symbol from libqemuutil.a if the shared modules need them,
# This is necessary because the modules may use functions not needed by the
# executable itself, which would cause the function to not be linked in.
# Then the DSO loading would fail because of the missing symbol.

def filter_lines_set(stdout, is_static = True):
    lines_set = set()
    for line in stdout.splitlines():
        tokens = line.split(b' ')
        if len(tokens) >= 1:
            if len(tokens) > 1:
                if is_static and tokens[1] == b'U':
                    continue
                if not is_static and tokens[1] != b'U':
                    continue
            new_line = b'-Wl,-u,' + tokens[0]
            if not new_line in lines_set:
                lines_set.add(new_line)
    return lines_set

def main(args):
    if len(args) <= 3:
        sys.exit(0)

    nm = args[1]
    staticlib = args[2]
    pc = subprocess.run([nm, "-P", "-g", staticlib], stdout=subprocess.PIPE)
    if pc.returncode != 0:
        sys.exit(-1)
    lines_set_left = filter_lines_set(pc.stdout)

    shared_modules = args[3:]
    pc = subprocess.run([nm, "-P", "-g"] + shared_modules, stdout=subprocess.PIPE)
    if pc.returncode != 0:
        sys.exit(-1)
    lines_set_right = filter_lines_set(pc.stdout, False)
    lines = []
    for line in sorted(list(lines_set_right)):
        if line in lines_set_left:
            lines.append(line)
    sys.stdout.write(b'\n'.join(lines).decode())

if __name__ == "__main__":
    main(sys.argv)
