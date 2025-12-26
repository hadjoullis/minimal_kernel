#include "fb_driver.h"
#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

#define FB_ROWS                 25
#define FB_COLUMNS              80

enum {
    FB_BLACK = 0,
    FB_BLUE,
    FB_GREEN,
    FB_CYAN,
    FB_RED,
    FB_MAGENTA,
    FB_BROWN,
    FB_LIGHT_GREY,
    FB_DARK_GREY,
    FB_LIGHT_BLUE,
    FB_LIGHT_GREEN,
    FB_LIGHT_CYAN,
    FB_LIGHT_RED,
    FB_LIGHT_BROWN,
    FB_WHITE,
} FB_COLOR;

/* The starting address of memory-mapped I/O */
char * const fb = (char *)0x000B8000;

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
static void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

/** fb_write_cell:
 *  Writes a character with the given foreground and background to cell i
 *  in the framebuffer.
 *
 *  @param i  The cell index in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
static void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    /* each cell uses two indices */
    i = 2 * i;
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

static void fb_clear(void) {
    for (unsigned int i = 0; i < FB_ROWS * FB_COLUMNS; i++) {
        fb_write_cell(2 * i, '\0', FB_BLACK, FB_BLACK);
    }
}

int write(char *buf, unsigned int len) {
    static unsigned short cursor = 0;
    for (unsigned int i = 0; i < len; i++) {
        fb_write_cell(cursor, buf[i], FB_BLACK, FB_LIGHT_GREY);
        fb_move_cursor(cursor++);
        if (cursor == FB_ROWS * FB_COLUMNS) {
            cursor = 0;
            // TODO: implemnt screen scrolling
            fb_clear();
        }
    }
    return 0;
}
