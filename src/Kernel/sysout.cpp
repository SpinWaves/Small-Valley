// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "sysout.h"

void log::report(log_type type, std::string message, ...)
{
    char* buffer = (char*)std::malloc(message.length() + 1024);
    va_list args;
    va_start(args, message);
    vsprintf(buffer, std::move(message).c_str(), args);
    va_end(args);

    switch(type)
    {
        case log_type::message:     std::cout << "\033[1;34m[log message]     " << buffer << "\033[1;39m" << '\n'; break;
        case log_type::warning:     std::cout << "\033[1;35m[log warning]     " << buffer << "\033[1;39m" << '\n'; break;
        case log_type::error:       std::cout << "\033[1;31m[log error]       " << buffer << "\033[1;39m" << '\n'; break;
        case log_type::fatal_error: std::cout << "\033[1;31m[log fatal error] " << buffer << "\033[1;39m" << '\n'; break;

        default: break;
    }

    std::free(buffer);

    if(type == log_type::fatal_error)
    {
        std::set_terminate(TERMINATE);
        std::terminate();
    }
}

void log::TERMINATE() noexcept
{
    std::cout << "\033[1;31mFATAL ERROR: emergency abortion program \033[1;49m" << std::endl;
    abort();
}
