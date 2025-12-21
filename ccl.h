// C Color Library (ccl.h)
// with love by czjstmax <jstmaxlol@disroot.org>
// versionless header

#pragma once

#ifndef CCL_H
#define CCL_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

// Utility characters
static const char *BLOCK   = "█";
static const char *TLANGLE = "┌";
static const char *BRANGLE = "┘";
static const char *TRANGLE = "┐";
static const char *BLANGLE = "└";
static const char *HORL    = "─";
static const char *VERL    = "│";

struct ccl_api {
    void (*fg)(const char*);
    void (*bg)(const char*);
    int (*fg_ansi)(const char*);
    void (*printf)(const char*, const char*, ...);
    void (*reset)();
    int (*style)(const char*);
};

static inline void ccl_fg(const char *restrict hex);
static inline void ccl_bg(const char *restrict hex);
static inline int  ccl_fg_ansi(const char *restrict col);
static inline void ccl_reset(void);
static inline int  ccl_style(const char *style);
static inline void ccl_printf(const char *restrict hex, const char *fmt, ...);

static inline int ccl_hexval(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static inline int ccl_hexbyte(const char *s) {
    int hi = ccl_hexval(s[0]);
    int lo = ccl_hexval(s[1]);
    if (hi < 0 || lo < 0) return -1;
    return (hi << 4) | lo; // (hi * 16) + lo
}

// Truecolor foreground from HEX value
static inline void ccl_fg(const char *restrict hex) {
    if (hex[0] == '#') hex++;

    int r = ccl_hexbyte(hex);
    int g = ccl_hexbyte(hex + 2);
    int b = ccl_hexbyte(hex + 4);
    if (r < 0 || g < 0 || b < 0) return;

    printf("\x1b[38;2;%d;%d;%dm", r, g, b);
}

// Truecolor background from HEX value
static inline void ccl_bg(const char *restrict hex) {
    if (hex[0] == '#') hex++;

    int r = ccl_hexbyte(hex);
    int g = ccl_hexbyte(hex + 2);
    int b = ccl_hexbyte(hex + 4);
    if (r < 0 || g < 0 || b < 0) return;

    printf("\x1b[48;2;%d;%d;%dm", r, g, b);
}
 
static inline int ccl_fg_ansi(const char *restrict col) {
    const char *COLOR = col;

    const char *BLACK   = "\x1b[30m";
    const char *RED     = "\x1b[31m";
    const char *GREEN   = "\x1b[32m";
    const char *YELLOW  = "\x1b[33m";
    const char *BLUE    = "\x1b[34m";
    const char *MAGENTA = "\x1b[35m";
    const char *CYAN    = "\x1b[36m";
    const char *WHITE   = "\x1b[37m";
 
    if (strcmp(COLOR, "black") == 0) {
        printf("%s", BLACK);
        return 0;
    } else if (strcmp(COLOR, "red") == 0) {
        printf("%s", RED);
        return 0;
    } else if (strcmp(COLOR, "green") == 0) {
        printf("%s", GREEN);
        return 0;
    } else if (strcmp(COLOR, "yellow") == 0) {
        printf("%s", YELLOW);
        return 0;
    } else if (strcmp(COLOR, "blue") == 0) {
        printf("%s", BLUE);
        return 0;
    } else if (strcmp(COLOR, "magenta") == 0) {
        printf("%s", MAGENTA);
        return 0;
    } else if (strcmp(COLOR, "cyan") == 0) {
        printf("%s", CYAN);
        return 0;
    } else if (strcmp(COLOR, "white") == 0) {
        printf("%s", WHITE);
        return 0;
    } else return 1;
}

// ccl.printf -> Colors formatted output, truecolor only
// (TODO: Add support for 256 colors mode and standard ANSI colors)
// Usage: ccl.printf("f4f4f4", "Hello, World!", ...);
static inline void ccl_printf(const char *restrict hex, const char *fmt, ...) {
    va_list ap;
    ccl_fg(hex);

    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);

    ccl_reset();
}

// Resets *everything*
static inline void ccl_reset() {
    const char *RESET = "\x1b[0m";
    printf("%s", RESET);
}

// Styles output
static inline int ccl_style(const char *style) {
    const char *BOLD            = "\x1b[1m";
    const char *DIM             = "\x1b[2m";
    const char *ITALIC          = "\x1b[3m";
    const char *UNDERLINE       = "\x1b[4m";
    const char *REVERSE         = "\x1b[7m";
    const char *STRIKETHROUGH   = "\x1b[9m";

    if (strcmp(style, "bold") == 0) {
        printf("%s", BOLD);
        return 0;
    } else if (strcmp(style, "dim") == 0) {
        printf("%s", DIM);
        return 0;
    } else if (strcmp(style, "italic") == 0) {
        printf("%s", ITALIC);
        return 0;
    } else if (strcmp(style, "underline") == 0) {
        printf("%s", UNDERLINE);
        return 0;
    } else if (strcmp(style, "reverse") == 0) {
        printf("%s", REVERSE);
        return 0;
    } else if (strcmp(style, "strikethrough") == 0) {
        printf("%s", STRIKETHROUGH);
        return 0;
    } else return 1;
}

static struct ccl_api ccl = {
    .fg         = ccl_fg,
    .bg         = ccl_bg,
    .fg_ansi    = ccl_fg_ansi,
    .printf     = ccl_printf,
    .reset      = ccl_reset,
    .style      = ccl_style
};

#endif
