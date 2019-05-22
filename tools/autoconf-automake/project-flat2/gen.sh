#!/bin/bash
aclocal
autoheader
autoconf
automake --add-missing --include-deps --foreign
