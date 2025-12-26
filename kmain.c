#include "fb_driver.h"

int main(void) {
    char msg[] = "hello world!";
    write(msg, sizeof(msg) - 1);
    return 0;
}
