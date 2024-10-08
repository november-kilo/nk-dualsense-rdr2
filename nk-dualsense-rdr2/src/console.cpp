﻿#include "console.h"

namespace {
    void open_file_stream(const char* filename, const char* mode, FILE* stream) {
        FILE* fp;

        if (const errno_t err = freopen_s(&fp, filename, mode, stream); err != 0) {
            std::cerr << "Failed to open " << filename << '\n';
        }
    }
}

void console::create_console(const bool for_real) {
    if (for_real && AllocConsole()) {
        open_file_stream("CONIN$", "r", stdin);
        open_file_stream("CONOUT$", "w", stdout);
        open_file_stream("CONOUT$", "w", stderr);
        write("console opened");
    }
}

void console::write(const std::string& text) {
    std::cout << "[nk-dualsense-rdr2] " << text << '\n';
}
