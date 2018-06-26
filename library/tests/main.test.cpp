// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "../vector3.hpp"
#include "../motion_sensor.hpp"
#include "mock_sensor.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/* Vector3 tests */
TEST_CASE("ipass::vector3 zero initialization") {
    ipass::vector3<int> vec;

    REQUIRE(vec == ipass::vector3<int>{0, 0, 0});
}

TEST_CASE("ipass::vector3 full initialization") {
    ipass::vector3<int> vec{3, 4, -5};

    REQUIRE(vec == ipass::vector3<int>{3, 4, -5});
}

TEST_CASE("ipass::vector3 length") {
    ipass::vector3<int> vec{2, 3, 4};

    REQUIRE(vec.length() == Approx(5.3851).epsilon(0.001));
}

TEST_CASE("ipass::vector3 distance") {
    ipass::vector3<int> v1{2, 3, 4};
    ipass::vector3<int> v2{3, 4, 5};

    REQUIRE(v1.distance(v2) == Approx(1.7320).epsilon(0.001));
    REQUIRE(v2.distance(v1) == Approx(1.7320).epsilon(0.001));
}

TEST_CASE("ipass::vector3 normalized") {
    ipass::vector3<int> vec{2, 3, 4};
    auto norm = vec.normalized();

    REQUIRE(norm.x == Approx(0.3713).epsilon(0.001));
    REQUIRE(norm.y == Approx(0.5570).epsilon(0.001));
    REQUIRE(norm.z == Approx(0.7427).epsilon(0.001));
}

TEST_CASE("ipass::vector3 scalar division") {
    ipass::vector3<int> vec(2, 4, 8);
    auto divided = vec / 2;

    REQUIRE(divided == ipass::vector3<int>{1, 2, 4});

    vec /= 2;
    REQUIRE(vec == ipass::vector3<int>{1, 2, 4});
}

TEST_CASE("ipass::vector3 division") {
    ipass::vector3<int> vec(2, 4, 8);
    auto divided = vec / ipass::vector3<int>(2, 4, 8);

    REQUIRE(divided == ipass::vector3<int>{1, 1, 1});

    vec /= ipass::vector3<int>(2, 4, 8);
    REQUIRE(vec == ipass::vector3<int>{1, 1, 1});
}

TEST_CASE("ipass::vector3 scalar multiplication") {
    ipass::vector3<int> vec(2, 4, 8);
    auto divided = vec * 2;

    REQUIRE(divided == ipass::vector3<int>{4, 8, 16});

    vec *= 2;
    REQUIRE(vec == ipass::vector3<int>{4, 8, 16});
}

TEST_CASE("ipass::vector3 multiplication") {
    ipass::vector3<int> vec(2, 4, 8);
    auto multiplicated = vec * ipass::vector3<int>(2, 4, 8);

    REQUIRE(multiplicated == ipass::vector3<int>{2 * 2, 4 * 4, 8 * 8});

    vec *= ipass::vector3<int>(2, 4, 8);
    REQUIRE(vec == ipass::vector3<int>{2 * 2, 4 * 4, 8 * 8});
}

TEST_CASE("ipass::vector3 plus") {
    ipass::vector3<int> vec(1, 1, 1);
    auto result = vec + ipass::vector3<int>{1, 1, 1};
    vec += ipass::vector3<int>{1, 1, 1};

    REQUIRE(result == ipass::vector3<int>{2, 2, 2});
    REQUIRE(vec == ipass::vector3<int>{2, 2, 2});
}

TEST_CASE("ipass::vector3 minus") {
    ipass::vector3<int> vec(1, 1, 1);
    auto result = vec - ipass::vector3<int>{1, 1, 1};
    vec -= ipass::vector3<int>{1, 1, 1};

    REQUIRE(result == ipass::vector3<int>{0, 0, 0});
    REQUIRE(vec == ipass::vector3<int>{0, 0, 0});
}

TEST_CASE("ipass::vector3 equality") {
    ipass::vector3<int> v1 = {1, 1, 1};
    ipass::vector3<int> v2 = {2, 2, 2};
    ipass::vector3<int> v3 = {1, 1, 1};

    REQUIRE(!(v1 == v2));
    REQUIRE(v1 == v3);
}

TEST_CASE("ipass::vector3 greater then comparisons") {
    ipass::vector3<int> v1 = {1, 1, 1};
    ipass::vector3<int> v2 = {2, 2, 2};
    ipass::vector3<int> v3 = {1, 1, 1};

    REQUIRE(!(v1 > v2));
    REQUIRE(!(v1 >= v2));

    REQUIRE(v2 > v1);
    REQUIRE(v2 >= v1);

    REQUIRE(!(v1 > v3));
    REQUIRE(v1 >= v3);
}

TEST_CASE("ipass::vector3 less then comparisons") {
    ipass::vector3<int> v1 = {1, 1, 1};
    ipass::vector3<int> v2 = {2, 2, 2};
    ipass::vector3<int> v3 = {1, 1, 1};

    REQUIRE(!(v2 < v1));
    REQUIRE(!(v2 <= v1));

    REQUIRE(v1 < v2);
    REQUIRE(v1 <= v2);

    REQUIRE(!(v3 < v1));
    REQUIRE(v3 <= v1);
}

TEST_CASE("ipass::vector3 data access") {
    ipass::vector3<int> v = {1, 2, 3};

    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
}

/* Motion sensor tests */
TEST_CASE("ipass::motion_sensor get gyro and accel") {
    ipass::vector3<int16_t> gyro = {9, -5, 2};
    ipass::vector3<int16_t> accel = {2, 3, 4};

    ipass::test::mock_sensor m(gyro, accel);

    REQUIRE(m.get_gyro() == gyro);
    REQUIRE(m.get_accel() == accel);
}

TEST_CASE("ipass::motion_sensor get gyro and accel x y z") {
    ipass::vector3<int16_t> gyro = {9, -5, 2};
    ipass::vector3<int16_t> accel = {2, 3, 4};

    ipass::test::mock_sensor m(gyro, accel);

    REQUIRE(m.get_gyro_x() == gyro.x);
    REQUIRE(m.get_gyro_y() == gyro.y);
    REQUIRE(m.get_gyro_z() == gyro.z);

    REQUIRE(m.get_accel_x() == accel.x);
    REQUIRE(m.get_accel_y() == accel.y);
    REQUIRE(m.get_accel_z() == accel.z);
}

TEST_CASE("ipass::cached_motion_sensor caches info") {
    ipass::vector3<int16_t> gyro = {0, 0, 0};
    ipass::vector3<int16_t> accel = {0, 0, 0};
    ipass::test::mock_sensor base(gyro, accel);

    auto m = ipass::cached_motion_sensor(base);

    SECTION("it uses cached information") {
        gyro = {1, 2, 3};
        accel = {3, 2, 1};

        base.set_gyro(gyro);
        base.set_accel(accel);

        REQUIRE(m.get_gyro() == ipass::vector3<int16_t>{0, 0, 0});
        REQUIRE(m.get_accel() == ipass::vector3<int16_t>{0, 0, 0});
    }

    SECTION("cached information can be refreshed") {
        gyro = {5, 6, 7};
        accel = {7, 6, 5};

        base.set_gyro(gyro);
        base.set_accel(accel);

        m.refresh();

        REQUIRE(m.get_gyro() == ipass::vector3<int16_t>{5, 6, 7});
        REQUIRE(m.get_accel() == ipass::vector3<int16_t>{7, 6, 5});
    }
}

TEST_CASE("ipass::gyro_corrected_motion_sensor adjusted gyro") {
    ipass::vector3<int16_t> gyro = {9, -5, 2};
    ipass::vector3<int16_t> accel = {2, 3, 4};
    ipass::vector3<int16_t> correction = {1, -1, 1};

    ipass::test::mock_sensor base(gyro, accel);
    auto m = ipass::gyro_corrected_motion_sensor(base, correction);

    REQUIRE(m.get_gyro() == gyro - correction);
    REQUIRE(m.get_accel() == accel);
}

TEST_CASE("ipass::accel_corrected_motion_sensor adjusted accel") {
    ipass::vector3<int16_t> gyro = {9, -5, 2};
    ipass::vector3<int16_t> accel = {2, 3, 4};
    ipass::vector3<int16_t> correction = {1, -1, 1};

    ipass::test::mock_sensor base(gyro, accel);
    auto m = ipass::accel_corrected_motion_sensor(base, correction);

    REQUIRE(m.get_gyro() == gyro);
    REQUIRE(m.get_accel() == accel - correction);
}

/* Motion rule tests */
TEST_CASE("ipass::gyro_rule applies to gyro") {
    ipass::vector3<int16_t> gyro = {0, 0, 1};
    ipass::vector3<int16_t> accel = {0, 0, 1};

    ipass::test::mock_sensor m(gyro, accel);

    auto rule = ipass::gyro_rule(ipass::motion::z_greater_then, 0);
    static bool success = false;

    m.when(rule, [](const auto&, const auto&) {
        success = true;
    });

    m.process_handlers();

    REQUIRE(success);
}

TEST_CASE("ipass::accel_rule applies to accel") {
    ipass::vector3<int16_t> gyro = {0, 0, 1};
    ipass::vector3<int16_t> accel = {0, 0, 1};

    ipass::test::mock_sensor m(gyro, accel);

    auto rule = ipass::accel_rule(ipass::motion::z_greater_then, 0);
    static bool success = false;

    m.when(rule, [](const auto&, const auto&) {
        success = true;
    });

    m.process_handlers();

    REQUIRE(success);
}

TEST_CASE("ipass::motion::none always passes") {
    ipass::vector3<int16_t> gyro = {0, 0, 1};
    ipass::vector3<int16_t> accel = {0, 0, 1};

    ipass::test::mock_sensor m(gyro, accel);

    auto rule = ipass::accel_rule(ipass::motion::none, 1000);
    static bool success = false;

    m.when(rule, [](const auto&, const auto&) {
        success = true;
    });

    m.process_handlers();

    REQUIRE(success);
}

TEST_CASE("ipass::inverted_motion_rule does the inversion") {
    ipass::vector3<int16_t> gyro = {0, 0, -1};
    ipass::vector3<int16_t> accel = {0, 0, 1};

    ipass::test::mock_sensor m(gyro, accel);

    auto basic_rule = ipass::gyro_rule(ipass::motion::z_greater_then, 0);
    auto rule = ipass::inverted_motion_rule(basic_rule);

    static bool success = false;

    m.when(rule, [](const auto&, const auto&) {
        success = true;
    });

    m.process_handlers();

    REQUIRE(success);
}

TEST_CASE("ipass::motion_rule rules can be combined") {
    SECTION("should succeed") {
        ipass::vector3<int16_t> gyro = {0, 0, 1};
        ipass::vector3<int16_t> accel = {0, 0, 1};

        ipass::test::mock_sensor m(gyro, accel);

        auto gyro_rule = ipass::gyro_rule(ipass::motion::z_greater_then, 0);
        auto accel_rule = ipass::accel_rule(ipass::motion::z_greater_then, 0);

        auto rule = gyro_rule + accel_rule;

        static bool success = false;

        m.when(rule, [](const auto&, const auto&) {
            success = true;
        });

        m.process_handlers();

        REQUIRE(success);
    }

    SECTION("should fail") {
        ipass::vector3<int16_t> gyro = {0, 0, 0};
        ipass::vector3<int16_t> accel = {0, 0, 1};

        ipass::test::mock_sensor m(gyro, accel);

        auto gyro_rule = ipass::gyro_rule(ipass::motion::z_greater_then, 0);
        auto accel_rule = ipass::accel_rule(ipass::motion::z_greater_then, 0);

        auto rule = gyro_rule + accel_rule;

        static bool success = false;

        m.when(rule, [](const auto&, const auto&) {
            success = true;
        });

        m.process_handlers();

        REQUIRE_FALSE(success);
    }
}