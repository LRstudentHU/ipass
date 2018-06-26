// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "mpu6050.hpp"

mpu6050::mpu6050(hwlib::i2c_bus &bus, uint8_t address)
        : bus(bus), address(address) {}

void mpu6050::initialize() {
    uint8_t pwr[] = {PWR_MGMT_1, (uint8_t) 0};
    bus.write(address, pwr, 2);

    // gyro_config and accel_config addresses
    // are 1 apart, so we can write to both configs
    // in one write
    uint8_t config[] = {
        GYRO_CONFIG, uint8_t(0),
        ACCEL_CONFIG, uint8_t(0)
    };

    bus.write(address, config, 4);
}

ipass::vector3<int16_t> mpu6050::get_sensor_data(const uint8_t start) {
    uint8_t data[6] = {start};

    bus.write(address, data, 1);
    bus.read(address, data, 6);

    return {
        int16_t(((data[0] << 8) | data[1])), // x
        int16_t(((data[2] << 8) | data[3])), // y
        int16_t(((data[4] << 8) | data[5]))  // z
    };
}

ipass::vector3<int16_t> mpu6050::get_accel() {
    auto accel = get_sensor_data(ACCEL_XOUT_H);
    accel /= 16384;
    return accel;
}

ipass::vector3<int16_t> mpu6050::get_gyro() {
    auto gyro = get_sensor_data(GYRO_XOUT_H);
    gyro /= 131.0;
    return gyro;
}

