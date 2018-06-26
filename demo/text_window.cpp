// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "text_window.hpp"

text_window::text_window(hwlib::i2c_bus &bus, const uint_fast8_t address, const hwlib::buffering buffering = hwlib::buffering::unbuffered)
        : glcd_oled(bus, address), loc(1,1), buffering(buffering) {}

void text_window::newline() {
    loc.x = 1;
    loc.y += line_height;
}

void text_window::putc(char c) {
    if (c == '\n') {
        newline();
        return;
    }

    if (c == '\t') {
        loc.x += tab_width * char_width;
        return;
    }

    if (loc.x + char_width > line_width + 1) {
        newline();
    }

    write(loc, font[c], buffering);
    loc.x += char_width;
}

void text_window::flush() {
    loc = {1,1};
    glcd_oled::flush();
}