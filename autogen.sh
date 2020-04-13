#!/bin/sh

case `uname` in Darwin*) glibtoolize --copy ;;
  *) libtoolize --copy ;; esac

echo "aclocal"
aclocal

echo "autoheader"
autoheader

echo "There are over 5,500 test directories, this takes a while ..."
echo "automake -v --add-missing"
automake -v --add-missing  --no-force

echo "autoconf"
autoconf

#autoreconf --install

echo "To build debug, run: ./configure --enable-debug"
exit 0
