lib_LTLIBRARIES = libbase.la

# library version
libbase_la_LDFLAGS=$(LTLDFLAGS)

######################################
# Cflags and Libs
# libbase_la_CXXFLAGS = $(LIBICONV_CFLAGS)
libbase_la_LIBADD = -lpthread

libbase_la_SOURCES =				\
pthread/thread.cpp				\
pthread/cond.cpp				\
pthread/attr.cpp				\
pthread/rwlock.cpp				\
ConvertUTF.c					\
utils.cpp					\
dirs.cpp

include_HEADERS =				\
thread.h					\
attr.h						\
rwlock.h					\
mutex.h						\
SimpleIni.h					\
timeutil.h					\
cond.h						\
define.h					\
ConvertUTF.h					\
utils.h						\
platform.h					\
base.h						\
datahandler.h					\
dirs.h
