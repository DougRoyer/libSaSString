#!/bin/sh

case `uname` in Darwin*) glibtoolize --copy ;;
  *) libtoolize --copy ;; esac

echo "aclocal"
aclocal

echo "autoheader"
autoheader

echo "automake -v --add-missing"
automake -v --add-missing  --no-force

echo "autoconf"
autoconf

#autoreconf --install

echo "To build debug, run: ./configure --enable-debug"
echo "To build test coverage, run: ./configure --enable-test-coverage"
exit 0
