// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef IPASS_MOTION_RULE_HPP
#define IPASS_MOTION_RULE_HPP

#include <cstdint>
#include "vector3.hpp"

namespace ipass {

    /**
     * \brief
     * Basic motion conditions.
     * \details
     * All basic motion conditions that can
     * be used to define motion by combining rules.
     */
    enum motion {
        none,

        x_greater_then,
        x_equal_to,
        x_less_then,

        y_greater_then,
        y_equal_to,
        y_less_then,

        z_greater_then,
        z_equal_to,
        z_less_then,
    };

    class combined_motion_rule;

    /**
     * \brief
     * Base class for a rule.
     */
    class motion_rule {
    protected:
        motion gesture;
        int16_t val;

        motion_rule();

        motion_rule(motion gesture, int16_t val);

        virtual bool match_against(const vector3<int16_t> &data) const;

    public:

        /**
         * \brief
         * Match the rule against the given data.
         * @param gyro
         * @param accel
         * @return
         */
        virtual bool match_against(const vector3<int16_t> &gyro, const vector3<int16_t> &accel) const = 0;
    };

    /**
     * \brief
     * Combination of two or more rules.
     * \details
     * Adding two rules together will result in
     * a combined motion rule, which can be used to
     * make more complicated conditions.
     */
    class combined_motion_rule : public motion_rule {
    private:
        motion_rule &first;
        motion_rule &second;

    public:
        /**
         * \brief
         * Constructor for the combined motion rule.
         * @param first
         * @param second
         */
        combined_motion_rule(motion_rule &first, motion_rule &second);

        /**
         * \brief
         * Will match the given data against both rules.
         * @param gyro
         * @param accel
         * @return
         */
        bool match_against(const vector3<int16_t> &gyro, const vector3<int16_t> &accel) const override;
    };

    /**
     * \brief
     * Add two rules together.
     * \details
     * The parameters for this function are non-const
     * intentionally; making them const would allow for const references
     * (temporaries) being passed to the function, which won't work because
     * a combined_motion_rule is constructed from motion_rule references (since
     * the motion_rule base class is abstract).
     * @param rhs
     * @return
     */
    static combined_motion_rule operator+(motion_rule &lhs, motion_rule &rhs)  {
        return ipass::combined_motion_rule{lhs, rhs};
    }

    /**
     * \brief
     * A motion rule that will apply to the gyroscope.
     */
    class gyro_rule : public motion_rule {
    public:
        /**
         * \brief
         * Constructor with the gesture and the value to match against.
         * @param gesture
         * @param val
         */
        gyro_rule(motion gesture, int16_t val);

        /**
         * \brief
         * Will match the given data against the rule.
         * @param gyro
         * @param accel
         * @return
         */
        bool match_against(const vector3<int16_t> &gyro, const vector3<int16_t> &accel) const override;
    };

    /**
     * \brief
     * A motion rule that will apply to the accelerometer.
     */
    class accel_rule : public motion_rule {
    public:
        /**
         * \brief
         * Constructor with the gesture and the value to match against.
         * @param gesture
         * @param val
         */
        accel_rule(motion gesture, int16_t val);

        /**
         * \brief
         * Will match the given data against the rule.
         * @param gyro
         * @param accel
         * @return
         */
        bool match_against(const vector3<int16_t> &gyro, const vector3<int16_t> &accel) const override;
    };

    /**
     * \brief
     * Motion rule invertion decorator.
     * \details
     * This decorator will invert a rule to provide greater
     * flexibility in combining rules.
     */
    class inverted_motion_rule : public motion_rule {
    private:
        const motion_rule &slave;

    public:
        /**
         * \brief
         * Constructor with the rule to invert.
         * @param slave
         */
        explicit inverted_motion_rule(const motion_rule &slave);

        /**
         * Will match against the inverse of the rule.
         * @param gyro
         * @param accel
         * @return
         */
        bool match_against(const vector3<int16_t> &gyro, const vector3<int16_t> &accel) const override;
    };
}

#endif //IPASS_MOTION_RULE_HPP
