#pragma once

#define SHOULD_OPEN_CONSOLE 0

#include <iostream>
#include <iostream>
#include <windows.h>

#include "util.h"

namespace console {
    void create_console();
    void write(const std::string& text);
}
