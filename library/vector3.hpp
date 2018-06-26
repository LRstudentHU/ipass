// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef IPASS_VECTOR3_HPP
#define IPASS_VECTOR3_HPP

#include <cmath>
#include "hwlib-ostream.hpp"

namespace ipass {

    /**
     * \brief
     * 3-dimensional vector.
     *
     * \details
     * 3-dimensional vector supporting common operations, used within
     * the library for storing gyroscope and accelerometer data.
     * @tparam T
     */
    template<typename T>
    struct vector3 {
        union {
            struct {
                T x, y, z;
            };

            T data[3];
        };

        /**
         * \brief
         * 3 argument constructor.
         * \details
         * Construct the vector with the given arguments.
         * @param x
         * @param y
         * @param z
         */
        vector3(T x, T y, T z)
                : x(x), y(y), z(z) {}

        /**
         * \brief
         * 0 argument constructor.
         * \details
         * Construct the vector with all values initialized to 0.
         */
        vector3() : x(0), y(0), z(0) {}

        /* Generic operations */

        /**
         * \brief
         * The length of the vector.
         * \details
         * Calculate the length of the vector as a double.
         * @return
         */
        double length() const {
            return sqrt((x * x) + (y * y) + (z * z));
        }

        /**
         * \brief
         * The distance between two vectors.
         * \details
         * Calculate the distance between the given vector to
         * this vector as a double.
         * @param rhs
         * @return
         */
        double distance(const vector3 &rhs) const {
            auto dx = pow(rhs.x - x, 2);
            auto dy = pow(rhs.y - y, 2);
            auto dz = pow(rhs.z - z, 2);

            return sqrt(dx + dy + dz);
        }

        /**
         * \brief
         * Create a normalized vector.
         * \details
         * Create a normalized vector based on the current
         * vector.
         * @return
         */
        vector3<double> normalized() const {
            double len = length();

            vector3<double> result = {
                    double(x) / len,
                    double(y) / len,
                    double(z) / len
            };

            return result;
        }

        /* Division */

        /**
         * \brief
         * Divide this vector by another vector, yielding a new vector.
         * @param rhs
         * @return
         */
        vector3 operator/(const vector3 &rhs) const {
            return vector3{x / rhs.x, y / rhs.y, z / rhs.z};
        }

        /**
         * \brief
         * Divide this vector by an integer, yielding a new vector.
         * @param rhs
         * @return
         */
        vector3 operator/(const int rhs) const {
            return vector3{x / rhs, y / rhs, z / rhs};
        }

        /**
         * \brief
         * Divide this vector by a double, yielding a new vector.
         * @param rhs
         * @return
         */
        vector3 operator/(const double rhs) const {
            return vector3{x / rhs, y / rhs, z / rhs};
        }

        /**
         * \brief
         * Divide this vector by another vector in-place.
         * @param rhs
         * @return
         */
        vector3 &operator/=(const vector3 &rhs) {
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;

            return *this;
        }

        /**
         * \brief
         * Divide this vector by an integer in-place.
         * @param rhs
         * @return
         */
        vector3 &operator/=(const int rhs) {
            x /= rhs;
            y /= rhs;
            z /= rhs;

            return *this;
        }

        /**
         * \brief
         * Divide this vector by a double in-place.
         * @param rhs
         * @return
         */
        vector3 &operator/=(const double rhs) {
            x /= rhs;
            y /= rhs;
            z /= rhs;

            return *this;
        }

        /* Multiplication */

        /**
         * \brief
         * Multiply this vector by another vector, yielding a new vector.
         * @param rhs
         * @return
         */
        vector3 operator*(const vector3 &rhs) const {
            return vector3{x * rhs.x, y * rhs.y, z * rhs.z};
        }

        /**
         * \brief
         * Multiply this vector by an integer, yielding a new vector.
         * @param rhs
         * @return
         */
        vector3 operator*(const int rhs) const {
            return vector3{x * rhs, y * rhs, z * rhs};
        }

        /**
         * \brief
         * Multiply this vector by a double, yielding a new vector.
         * @param rhs
         * @return
         */
        vector3 operator*(const double rhs) const {
            return vector3{x * rhs, y * rhs, z * rhs};
        }

        /**
         * \brief
         * Multiply this vector by another vector in-place.
         * @param rhs
         * @return
         */
        vector3 &operator*=(const vector3 &rhs) {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;

            return *this;
        }

        /**
         * \brief
         * Multiply this vector by an integer in-place.
         * @param rhs
         * @return
         */
        vector3 &operator*=(const int rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;

            return *this;
        }

        /**
         * \brief
         * Multiply this vector by a double in-place.
         * @param rhs
         * @return
         */
        vector3 &operator*=(const double rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;

            return *this;
        }

        /* Subtraction */

        /**
         * \brief
         * Substract this vector by another vector, yielding a new vector.
         * @param rhs
         * @return
         */
        vector3 operator-(const vector3 &rhs) const {
            return vector3{x - rhs.x, y - rhs.y, z - rhs.z};
        }

        /**
         * \brief
         * Substract this vector by another vector in place.
         * @param rhs
         * @return
         */
        vector3 &operator-=(const vector3 &rhs) {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;

            return *this;
        }

        /* Addition */

        /**
         * \brief
         * Add this vector to another vector, yielding a new vector.
         * @param rhs
         * @return
         */
        vector3 operator+(const vector3 &rhs) const {
            return vector3{x + rhs.x, y + rhs.y, z + rhs.z};
        }

        /**
         * \brief
         * Add this vector to another vector in-place.
         * @param rhs
         * @return
         */
        vector3 &operator+=(const vector3 &rhs) {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;

            return *this;
        }

        /* Equality */

        /**
         * \brief
         * Check if two vectors are equal.
         * \details
         * Check if two vectors are equal by executing a member-wise compare.
         * @param rhs
         * @return
         */
        bool operator==(const vector3 &rhs) const {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }

        /**
         * \brief
         * Check if two vectors are not equal.
         * \details
         * Check if two vectors are not equal by executing a member-wise compare.
         * @param rhs
         * @return
         */
        bool operator!=(const vector3 &rhs) const {
            return !operator==(rhs);
        }

        /**
         * \brief
         * Check if the current vector is larger than the given vector.
         * @param rhs
         * @return
         */
        bool operator>(const vector3 &rhs) const {
            return rhs.x < x && rhs.y < y && rhs.z < z;
        }

        /**
         * \brief
         * Check if the current vector is larger than or equal to the given vector.
         * @param rhs
         * @return
         */
        bool operator>=(const vector3 &rhs) const {
            return operator==(rhs) || operator>(rhs);
        }

        /**
         * \brief
         * Check if the current vector is smaller than the given vector.
         * @param rhs
         * @return
         */
        bool operator<(const vector3 &rhs) const {
            return rhs.x > x && rhs.y > y && rhs.z > z;
        }

        /**
         * \brief
         * Check if the current vector is smaller than or equal to the given vector.
         * @param rhs
         * @return
         */
        bool operator<=(const vector3 &rhs) const {
            return operator==(rhs) || operator<(rhs);
        }

        /* Access */

        /**
         * \brief
         * Access the vector data with the [] operator.
         * @param index
         * @return
         */
        T &operator[](const int index) {
            return data[index];
        }
    };

    /**
     * \brief
     * Output the vector to given output stream.
     * @tparam T
     * @param ostream
     * @param vec
     * @return
     */
    template<typename T>
    hwlib::ostream &operator<<(hwlib::ostream &ostream, const vector3<T> &vec) {
        ostream << "x: " << vec.x
                << ", y: " << vec.y
                << ", z: " << vec.z;

        return ostream;
    }
}

#endif //IPASS_VECTOR3_HPP
