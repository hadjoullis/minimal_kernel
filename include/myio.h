#ifndef INCLUDE_MYIO_H
#define INCLUDE_MYIO_H

#include "fb_driver.h"
#include "serial_driver.h"

enum MYIO_LOG_SEV {
    MYIO_LOG_INFO,
    MYIO_LOG_DEBUG,
    MYIO_LOG_ERROR,
};

void mylog(enum MYIO_LOG_SEV sev, char *fmt, ...);
void myprintf(char *fmt, ...);

#endif /* INCLUDE_MYIO_H */
