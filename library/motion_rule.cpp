// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "motion_rule.hpp"

ipass::motion_rule::motion_rule()
        : gesture(motion::none), val(0) {}

ipass::motion_rule::motion_rule(ipass::motion gesture, int16_t val)
        : gesture(gesture), val(val) {}

bool ipass::motion_rule::match_against(const vector3<int16_t> &data) const {
    switch (gesture) {
        case motion::none:
            return true;
            break;

            // x
        case motion::x_greater_then:
            if (data.x > val) return true;
            break;

        case motion::x_equal_to:
            if (data.x == val) return true;
            break;

        case motion::x_less_then:
            if (data.x < val) return true;
            break;

            // y
        case motion::y_greater_then:
            if (data.y > val) return true;
            break;

        case motion::y_equal_to:
            if (data.y == val) return true;
            break;

        case motion::y_less_then:
            if (data.y < val) return true;
            break;

            // z
        case motion::z_greater_then:
            if (data.z > val) return true;
            break;

        case motion::z_equal_to:
            if (data.z == val) return true;
            break;

        case motion::z_less_then:
            if (data.z < val) return true;
            break;
    }

    return false;
}

ipass::combined_motion_rule::combined_motion_rule(ipass::motion_rule &first, ipass::motion_rule &second)
        : first(first), second(second) {}

bool ipass::combined_motion_rule::match_against(const vector3<int16_t> &gyro, const vector3<int16_t> &accel) const {
    return first.match_against(gyro, accel)
           && second.match_against(gyro, accel);
}

ipass::gyro_rule::gyro_rule(ipass::motion gesture, int16_t val)
        : motion_rule(gesture, val) {}

bool ipass::gyro_rule::match_against(const vector3<int16_t> &gyro, const vector3<int16_t> &accel) const {
    return motion_rule::match_against(gyro);
}

ipass::accel_rule::accel_rule(ipass::motion gesture, int16_t val)
        : motion_rule(gesture, val) {}

bool ipass::accel_rule::match_against(const vector3<int16_t> &gyro, const vector3<int16_t> &accel) const {
    return motion_rule::match_against(accel);
}

ipass::inverted_motion_rule::inverted_motion_rule(const ipass::motion_rule &slave)
        : motion_rule(motion::none, 0), slave(slave) {}

bool ipass::inverted_motion_rule::match_against(const vector3<int16_t> &gyro, const vector3<int16_t> &accel) const {
    return !slave.match_against(gyro, accel);
}
