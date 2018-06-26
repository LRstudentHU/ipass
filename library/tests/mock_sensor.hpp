// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef IPASS_MOCK_SENSOR_HPP
#define IPASS_MOCK_SENSOR_HPP

#include "../motion_sensor.hpp"

namespace ipass::test {
    class mock_sensor : public motion_sensor {
    private:
        vector3<int16_t> gyro, accel;

    public:
        mock_sensor();

        mock_sensor(vector3<int16_t> &gyro, vector3<int16_t> &accel);

        void initialize() override { };

        vector3<int16_t> get_gyro() override;

        vector3<int16_t> get_accel() override;

        void set_gyro(const vector3<int16_t> &gyro);

        void set_accel(const vector3<int16_t> &accel);
    };
}

#endif //IPASS_MOCK_SENSOR_HPP
