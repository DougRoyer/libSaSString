INSTALL			= install -C -c

AM_CPPFLAGS		= \
			-DBUILDING_SAS_LIBRARY_STRING \
			-DUSE_ICONV \
			-I$(top_srcdir)/include \
			-I/usr/include/tirpc

LIBS			= \
			-L/usr/local/lib \
			-lSaSCommon \
			-licui18n \
			-licuuc \
			-licudata

lib_LTLIBRARIES		= libSaSString.la

libSaSString_la_LDFLAGS = -version-info 0:0:0

Locale =

libSaSString_la_SOURCES = \
			StringCharmap.cpp \
			StringLocale.cpp \
			StringLocaleLcAddress.cpp \
			StringLocaleLcCtype.cpp \
			StringLocaleLcCollate.cpp \
			StringLocaleLcIdentification.cpp \
			StringLocaleLcMeasurement.cpp \
			StringLocaleLcMessages.cpp \
			StringLocaleLcMonentary.cpp \
			StringLocaleLcName.cpp \
			StringLocaleLcNumeric.cpp \
			StringLocaleLcPaper.cpp \
			StringLocaleLcTelephone.cpp \
			StringLocaleLcTime.cpp
			StringIterator.cpp \
			msgCat2.cpp \
			msgcat.cpp \
			replaceText.cpp \
			StringCache.cpp \
			StringCat.cpp \
			StringCharset.cpp \
			StringChr.cpp \
			StringCmp.cpp \
			StringCompareOperator.cpp \
			String.cpp \
			StringCpy.cpp \
			StringCspn.cpp \
			StringDup.cpp \
			StringLen.cpp \
			StringNCpy.cpp \
			StringPbrk.cpp \
			StringReplace.cpp \
			StringSeg.cpp \
			StringSpn.cpp \
			StringStr.cpp \
			StringSub.cpp \
			StringTok.cpp \
			strlower.c \
			strsearch.cpp \
			strupper.c \
			ROString.cpp

clean-generic:
	$(RM) -f *.gcno
	$(RM) -rf .deps

