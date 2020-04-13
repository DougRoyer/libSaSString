if HAVE_DOXYGEN
directory = $(top_srcdir)/Documentation/OutPut/man/man3/

doxyfile.stamp: public private
	echo Timestamp > doxyfile.stamp

public:
	$(DOXYGEN) Doxyfile-public
	echo Timestamp > doxyfile-public.stamp

private:
	$(DOXYGEN) Doxyfile-private
	echo Timestamp > doxyfile-private.stamp

CLEANFILES = doxyfile.stamp doxyfile-private.stamp doxyfile-public.stamp

all-local: doxyfile.stamp
clean-local:
	rm -rf $(top_srcdir)/Documentation/OutPutPrivate
	rm -rf $(top_srcdir)/Documentation/OutPutPublic
	rm -rf $(top_srcdir)/Documentation/Warnings*

#
endif

