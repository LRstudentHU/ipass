// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef  IN_TEST_SUITE

#include <hwlib.hpp>

#include "mpu6050.hpp"
#include "text_window.hpp"

int main() {
    // Kill the watchdog timer
    WDT->WDT_MR = WDT_MR_WDDIS;

    // Create the I2C bus
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);

    auto bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

    // Create a text window, which combines
    // a oled with hwlib::ostream
    text_window display(bus, 0x3c, hwlib::buffering::buffered);

    // Instantiate the sensor
    mpu6050 mpu(bus);

    // Correct the gyro of the sensor slightly
    ipass::gyro_corrected_motion_sensor sensor(mpu, {-6, -1, 0});

    /*
     * Optionally, the cached_motion_sensor decorator can be
     * used here to speed up program iterations if required.
     */
    // ipass::cached_motion_sensor sensor(mpu);

    // Initialize the hardware
    sensor.initialize();

    // Building block rules
    ipass::gyro_rule hand_tilted_backwards_y = {ipass::motion::y_less_then, -150};
    ipass::gyro_rule hand_tilted_forwards_y = {ipass::motion::y_greater_then, 150};
    ipass::accel_rule hand_flat = {ipass::motion::z_equal_to, 1};

    ipass::gyro_rule hand_tilted_left = {ipass::motion::x_less_then, -120};
    ipass::gyro_rule hand_tilted_right = {ipass::motion::x_greater_then, 120};

    // Invert the hand flat rule
    auto hand_not_flat = ipass::inverted_motion_rule(hand_flat);

    // Combine both rules for the motion
    auto hand_tilted_backwards = hand_tilted_backwards_y + hand_not_flat;
    auto hand_tilted_forwards = hand_tilted_forwards_y + hand_not_flat;

    // Register a handler for the motion rule
    sensor.when(hand_tilted_backwards, [](const auto &, const auto &) {
        hwlib::cout << "Hand tilted backwards" << hwlib::endl;
    });

    sensor.when(hand_tilted_forwards, [](const auto &, const auto &) {
        hwlib::cout << "Hand tilted forwards" << hwlib::endl;
    });

    sensor.when(hand_tilted_left, [](const auto &, const auto &) {
        hwlib::cout << "Hand tilted left" << hwlib::endl;
    });

    sensor.when(hand_tilted_right, [](const auto &, const auto &) {
        hwlib::cout << "Hand tilted right" << hwlib::endl;
    });

    uint_fast64_t start = 0;

    for (;;) {
        start = hwlib::now_us();

        display.clear(hwlib::buffering::buffered);

        // Run checks for all rules
        sensor.process_handlers();

        // Get data to display
        // @note: this is not the most efficient,
        // since this will fetch data from the chip again.
        // The data will be recent, but it will be slower than caching.
        const auto accel = sensor.get_accel();
        const auto gyro = sensor.get_gyro();

        // Display the accel and gyro info
        // on the oled display
        display << "A x:" << accel.x
                << ",y:" << accel.y
                << ",z:" << accel.z
                << "\n\n";

        display << "G x:" << gyro.x
                << "\n\ty:" << gyro.y
                << "\n\tz:" << gyro.z
                << '\n';

        display << "ms: " << ((hwlib::now_us() - start) / 1000);

        display.flush();

        // Also display on the console on the pc
        hwlib::cout << "G: " << gyro << "\nA: " << accel << hwlib::endl;
    }

    return 0;
}

#endif