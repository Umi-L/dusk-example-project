//
//  mGBA logging functionality
//
//! \file tonc_mgba.c
//! \author Nick Sells
//! \date 20210221

#include <string.h>
#include "tonc_math.h"
#include "tonc_mgba.h"

//adapted from https://github.com/GValiente/butano/blob/8017ce68628a86d8eb26b5077b84346c3143b54e/butano/hw/src/bn_hw_log.cpp#L22
void mgba_log(const char* str, const u32 level) {
    REG_LOG_ENABLE = 0xC0DE;
    const u32 max_chars_per_line = 256; //not arbitrary. the register is just 256 chars wide
    u32 chars_left = strlen(str);

    while(chars_left) { //breaks the message into 256-char log entries
        u32 chars_to_write = min(chars_left, max_chars_per_line);

        memcpy(REG_LOG_STR, str, chars_to_write);
        REG_LOG_LEVEL = level; //every time this is written to, mgba creates a new log entry

        str += chars_to_write; //increments the POINTER to the string, took me forever to realize
        chars_left -= chars_to_write;
    }
}