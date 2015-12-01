lib_LTLIBRARIES = libbase.la

# library version
libbase_la_LDFLAGS=$(LTLDFLAGS)

######################################
# Cflags and Libs
libbase_la_CPPFLAGS = -I$(top_srcdir)/include $(all_includes)
# libbase_la_CXXFLAGS = $(LIBICONV_CFLAGS)
libbase_la_LIBADD = -lpthread

libbase_la_SOURCES =				\
pthread/thread.cpp				\
pthread/cond.cpp				\
pthread/attr.cpp				\
pthread/rwlock.cpp				\
pthread/signalhandler.cpp			\
ConvertUTF.c					\
utils.cpp					\
netipc.cpp					\
dirs.cpp					\
process.cpp
