//
//  mGBA logging functionality
//
//! \file tonc_mgba.h
//! \author Nick Sells
//! \date 20210221

#pragma once
#ifndef TONC_MGBA_H
#define TONC_MGBA_H

#include "tonc_types.h"

#define REG_LOG_STR      (char*) 0x4FFF600
#define REG_LOG_LEVEL   *(vu16*) 0x4FFF700
#define REG_LOG_ENABLE  *(vu16*) 0x4FFF780

#define LOG_FATAL       0x100
#define LOG_ERR         0x101
#define LOG_WARN        0x102
#define LOG_INFO        0x103


void mgba_log(const char* str);

void mgba_log_type(const char* str, const u32 level);

void mgba_log_int(int num);

void mgba_log_int_type(int num, const u32 level);

void mgba_log_int_with_prefix(const char* prefix, int num);

#endif