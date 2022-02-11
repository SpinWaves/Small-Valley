// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __SYS_OUT__
#define __SYS_OUT__

#include <iostream>
#include <string>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

enum class log_type 
{
    message,
    warning,
    error,
    fatal_error
};

class log
{
    public:
        log() = delete;

        static void report(log_type type, std::string message, ...);

        ~log() = delete;
    
    private:
        static void TERMINATE() noexcept;
};

#endif // __SYS_OUT__
