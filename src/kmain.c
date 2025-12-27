#include "myio.h"

int main(void) {
    char msg[] = "hello world!\n";
    myprintf(msg, sizeof(msg) - 1);
    mylog(MYIO_LOG_INFO, "foo\n", 4);
    mylog(MYIO_LOG_DEBUG, "bar\n", 4);
    mylog(MYIO_LOG_ERROR, "baz\n", 4);
    return 0;
}
