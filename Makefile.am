AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = lib  include Utilities
DOC_SUBDIR = Documentation

dist_doc_DATA=README

README.md : README.nroff
	groff -Tascii README.nroff | col > README.md

README.html : README.nroff
	groff -Thtml README.nroff | col > README.html

