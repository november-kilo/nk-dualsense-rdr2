#pragma once

#include <iostream>
#include <windows.h>

#include "util.h"

namespace console {
    void create_console(bool for_real = false);
    void write(const std::string& text);
}
