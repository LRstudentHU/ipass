// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "motion_sensor.hpp"

ipass::motion_handler::motion_handler()
        : function(nullptr), rule(nullptr) {}

ipass::motion_handler::motion_handler(ipass::motion_rule &rule, ipass::motion_handler::func function)
        : function(function), rule(&rule) {}

bool ipass::motion_handler::is_free() const {
    return function == nullptr;
}

ipass::motion_sensor::motion_sensor() : handlers() {}

int8_t ipass::motion_sensor::when(motion_rule &rule, motion_handler::func function) {
    const int8_t size = sizeof(handlers) / sizeof(handlers[0]);

    for (int8_t i = 0; i < size; i++) {
        if (handlers[i].is_free()) {
            handlers[i] = motion_handler(rule, function);
            return i;
        }
    }

    return -1;
}

void ipass::motion_sensor::remove_handler(int8_t index) {
    if (index >= handler_count || index < 0) {
        return;
    }

    handlers[index] = motion_handler();
}

int16_t ipass::motion_sensor::get_accel_x() {
    return get_accel().x;
}

int16_t ipass::motion_sensor::get_accel_y() {
    return get_accel().y;
}

int16_t ipass::motion_sensor::get_accel_z() {
    return get_accel().z;
}

int16_t ipass::motion_sensor::get_gyro_x() {
    return get_gyro().x;
}

int16_t ipass::motion_sensor::get_gyro_y() {
    return get_gyro().y;
}

int16_t ipass::motion_sensor::get_gyro_z() {
    return get_gyro().z;
}

void ipass::motion_sensor::process_handlers() {
    vector3<int16_t> gyro = get_gyro();
    vector3<int16_t> accel = get_accel();

    for (const auto &handler : handlers) {
        /*
         * The handlers array is not sorted and can be
         * empty at random locations, so every item
         * has to be checked.
         */
        if (handler.is_free()) {
            continue;
        }

        if ((*handler.rule).match_against(gyro, accel)) {
            handler.function(gyro, accel);
        }
    }
}

ipass::cached_motion_sensor::cached_motion_sensor(ipass::motion_sensor &slave)
    : slave(slave) {}

void ipass::cached_motion_sensor::initialize() {
    slave.initialize();
}

ipass::vector3<int16_t> ipass::cached_motion_sensor::get_accel() {
    return accel;
}

ipass::vector3<int16_t> ipass::cached_motion_sensor::get_gyro() {
    return gyro;
}

void ipass::cached_motion_sensor::refresh() {
    gyro = slave.get_gyro();
    accel = slave.get_accel();
}

ipass::corrected_motion_sensor::corrected_motion_sensor(ipass::motion_sensor &slave, ipass::vector3<int16_t> correction)
        : slave(slave), correction(correction) {}

void ipass::corrected_motion_sensor::initialize() {
    slave.initialize();
}

ipass::gyro_corrected_motion_sensor::gyro_corrected_motion_sensor(ipass::motion_sensor &slave,
                                                                  const ipass::vector3<int16_t> &correction)
        : corrected_motion_sensor(slave, correction) {}

ipass::vector3<int16_t> ipass::gyro_corrected_motion_sensor::get_accel() {
    return slave.get_accel();
}

ipass::vector3<int16_t> ipass::gyro_corrected_motion_sensor::get_gyro() {
    auto base = slave.get_gyro();
    base -= correction;

    return base;
}

ipass::accel_corrected_motion_sensor::accel_corrected_motion_sensor(ipass::motion_sensor &slave,
                                                                    const ipass::vector3<int16_t> &correction)
        : corrected_motion_sensor(slave, correction) {}


ipass::vector3<int16_t> ipass::accel_corrected_motion_sensor::get_accel() {
    auto base = slave.get_accel();
    base -= correction;

    return base;
}

ipass::vector3<int16_t> ipass::accel_corrected_motion_sensor::get_gyro() {
    return slave.get_gyro();
}