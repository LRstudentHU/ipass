// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef SCHOOLHW_MPU6050_HPP
#define SCHOOLHW_MPU6050_HPP

#include "hwlib.hpp"
#include "../library/vector3.hpp"
#include "../library/motion_sensor.hpp"

class mpu6050 : public ipass::motion_sensor {
private:
    static constexpr uint8_t GYRO_CONFIG = 0x1B;
    static constexpr uint8_t ACCEL_CONFIG = 0x1C;
    static constexpr uint8_t ACCEL_XOUT_H = 0x3B;
    static constexpr uint8_t GYRO_XOUT_H = 0x43;
    static constexpr uint8_t PWR_MGMT_1 = 0x6B;

    hwlib::i2c_bus &bus;
    uint8_t address{};

    ipass::vector3<int16_t> get_sensor_data(uint8_t start);
public:
    explicit mpu6050(hwlib::i2c_bus &bus, uint8_t address = 0x68);

    void initialize() override;

    ipass::vector3<int16_t> get_accel() override;

    ipass::vector3<int16_t> get_gyro() override;
};


#endif //SCHOOLHW_MPU6050_HPP
