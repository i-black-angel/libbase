lib_LTLIBRARIES = libbase.la

# library version
libbase_la_LDFLAGS=$(LTLDFLAGS)

######################################
# Cflags and Libs
# libbase_la_CXXFLAGS = $(LIBICONV_CFLAGS)
libbase_la_LIBADD = -lpthread

libbase_la_SOURCES =				\
thread.cpp					\
mutex.cpp					\
cond.cpp					\
attr.cpp					\
ConvertUTF.c					\
rwlock.cpp    

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
base.h    
