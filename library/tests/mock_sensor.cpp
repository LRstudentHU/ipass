// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "mock_sensor.hpp"

ipass::test::mock_sensor::mock_sensor() : gyro(), accel() {}

ipass::test::mock_sensor::mock_sensor(ipass::vector3<int16_t> &gyro, ipass::vector3<int16_t> &accel)
        : gyro(gyro), accel(accel) {}

ipass::vector3<int16_t> ipass::test::mock_sensor::get_gyro() {
    return gyro;
}

ipass::vector3<int16_t> ipass::test::mock_sensor::get_accel() {
    return accel;
}

void ipass::test::mock_sensor::set_gyro(const vector3<int16_t> &gyro) {
    this->gyro = gyro;
}

void ipass::test::mock_sensor::set_accel(const vector3<int16_t> &accel) {
    this->accel = accel;
}