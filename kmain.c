#include "fb_driver.h"
#include "serial_driver.h"

int main(void) {
    char msg[] = "hello world!\n";
    fb_write(msg, sizeof(msg) - 1);
    serial_write(msg, sizeof(msg) - 1);
    return 0;
}
