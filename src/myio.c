#include "myio.h"

/* use compiler builtins since we do not link with glibc */
#define va_list       __builtin_va_list
#define va_start(v,l) __builtin_va_start(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define unreachable() __builtin_unreachable()

enum MYIO_DEV {
    MYIO_FB,    /* framebuffer */
    MYIO_SR,    /* serial      */
};

/** mywrite:
 *  Imitates simple printf-like behavior, by printing to the
 *  specified device.
 *
 *  @param  dev The MYIO_DEV dev to write to
 *  @param  fmt The format to follow
 *  @param  ap  The first argument of a va_list, needs to be
 *              initialized properly, and cleaned up after
 *  @return 0 if write was successful
 *          1 if write was not successful
 */
static int mywrite(enum MYIO_DEV dev, char *fmt, va_list ap) {
    int (*write)(char *, unsigned int);
    switch (dev) {
    case MYIO_FB: write = fb_write; break;
    case MYIO_SR: write = serial_write; break;
    default:
        return 1;
    }
    char *p, *sval;
    int ival;
    double dval;

    for (p = fmt; *p; p++) {
        if (*p != '%') {
            write(p, 1);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                // TODO: implement atoi
                (void)ival;
                break;
            case 'f':
                dval = va_arg(ap, double);
                // TODO: implement atof
                (void)dval;
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    write(sval, 1);
                break;
            default:
                write(p, 1);
                break;
        }
    }
    return 0;
}

void mylog(enum MYIO_LOG_SEV sev, char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    switch (sev) {
    case MYIO_LOG_INFO:  mywrite(MYIO_SR, "INFO: ", 0); break;
    case MYIO_LOG_DEBUG: mywrite(MYIO_SR, "DEBUG: ", 0); break;
    case MYIO_LOG_ERROR: mywrite(MYIO_SR, "ERROR: ", 0); break;
    default:
        unreachable();
    }
    mywrite(MYIO_SR, fmt, ap);
    va_end(ap);
}

void myprintf(char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    mywrite(MYIO_FB, fmt, ap);
    va_end(ap);
}
