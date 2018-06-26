// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef SCHOOLHW_UTIL_H
#define SCHOOLHW_UTIL_H

#include "hwlib.hpp"

class text_window : public hwlib::glcd_oled, public hwlib::ostream {
private:
    constexpr static int8_t char_width = 9;
    constexpr static int8_t line_height = 10;
    constexpr static int8_t chars_on_term = 13;
    constexpr static int8_t tab_width = 2;
    constexpr static int8_t line_width = char_width * chars_on_term;

    hwlib::location loc;

    void newline();

    void putc(char c) override;

protected:
    hwlib::font_default_8x8 font;
    hwlib::buffering buffering;

public:
    text_window(hwlib::i2c_bus &bus, uint_fast8_t address, hwlib::buffering buffering);

    void flush() override;
};

#endif //SCHOOLHW_UTIL_H
