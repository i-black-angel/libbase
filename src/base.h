#ifndef _BASE_H_
#define _BASE_H_

#include "define.h"
#include "attr.h"
#include "thread.h"
#ifdef __linux__
#include "rwlock.h"
#include "cond.h"
#endif /* __linux */
#include "mutex.h"
#include "SimpleIni.h"
#include "timeutil.h"
#include "dirs.h"
#include "utils.h"

#endif /* _BASE_H_ */
