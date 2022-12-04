//
//  mGBA logging functionality
//
//! \file tonc_mgba.c
//! \author Nick Sells
//! \date 20210221

#include <string.h>
#include "tonc_math.h"
#include "tonc_mgba.h"
#include "std_utils.h"

#include <stdlib.h>

//adapted from https://github.com/GValiente/butano/blob/8017ce68628a86d8eb26b5077b84346c3143b54e/butano/hw/src/bn_hw_log.cpp#L22
void mgba_log(const char* str) {
    REG_LOG_ENABLE = 0xC0DE;
    const u32 max_chars_per_line = 256; //not arbitrary. the register is just 256 chars wide
    u32 chars_left = strlen(str);

    while(chars_left) { //breaks the message into 256-char log entries
        u32 chars_to_write = min(chars_left, max_chars_per_line);

        memcpy(REG_LOG_STR, str, chars_to_write);
        REG_LOG_LEVEL = LOG_INFO; //every time this is written to, mgba creates a new log entry

        str += chars_to_write; //increments the POINTER to the string, took me forever to realize
        chars_left -= chars_to_write;
    }
}

void mgba_log_type(const char* str, const u32 level) {
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

void mgba_log_int(int num) {

    char string[15];
    itoa_simple(string, num);

    const char* str = string;

    REG_LOG_ENABLE = 0xC0DE;
    const u32 max_chars_per_line = 256; //not arbitrary. the register is just 256 chars wide
    u32 chars_left = strlen(str);

    while(chars_left) { //breaks the message into 256-char log entries
        u32 chars_to_write = min(chars_left, max_chars_per_line);

        memcpy(REG_LOG_STR, str, chars_to_write);
        REG_LOG_LEVEL = LOG_INFO; //every time this is written to, mgba creates a new log entry

        str += chars_to_write; //increments the POINTER to the string, took me forever to realize
        chars_left -= chars_to_write;
    }
}

void mgba_log_int_with_prefix(const char* prefix, int num) {


    char result[50] = "";

    char string[15];
    itoa_simple(string, num);

    strcat(result, prefix);
    strcat(result, string);

    char* str = result;

    REG_LOG_ENABLE = 0xC0DE;
    const u32 max_chars_per_line = 256; //not arbitrary. the register is just 256 chars wide
    u32 chars_left = strlen(str);

    while(chars_left) { //breaks the message into 256-char log entries
        u32 chars_to_write = min(chars_left, max_chars_per_line);

        memcpy(REG_LOG_STR, str, chars_to_write);
        REG_LOG_LEVEL = LOG_INFO; //every time this is written to, mgba creates a new log entry

        str += chars_to_write; //increments the POINTER to the string, took me forever to realize
        chars_left -= chars_to_write;
    }
}

void mgba_log_int_type(int num, const u32 level) {

    char string[15];
    itoa_simple(string, num);

    const char* str = string;

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