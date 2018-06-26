// ==========================================================================
// Copyright (c) Lex Ruesink (lex.ruesink@student.hu.nl) 2018
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================



#ifndef IPASS_MOTION_SENSOR_HPP
#define IPASS_MOTION_SENSOR_HPP

#include "vector3.hpp"
#include "motion_rule.hpp"

/**
 * \mainpage
 * \author Lex Ruesink (lex.ruesink@student.hu.nl)
 * \version 1.0
 * \copyright boost license
 *
 * -------------------------------------------------------------------------
 *
 * This library is created for the ipass project of year 2017-2018.
 * With this library gyroscope and accelerometer data can be used
 * to detect motion and gestures in a simple, abstracted matter.
 *
 * The library offers a simple yet flexible api for using and
 * extending sensors, motions and library behaviour.
 *
 * The entire library is written in C++ OO fashion with C++ 14.
 * The library is dependent on hwlib (https://github.com/wovo/hwlib, © Wouter van Ooijen).
 *
 * GitHub: https://github.com/LRstudentHU/ipass
 */

/**
 * \page use Use
 * For usage examples of the library, please see the
 * demo on the github.
 *
 * The library is a layer between the presentation layer and the
 * hardware layer. The library user is responsible for providing
 * a hardware implementation for the sensor used.
 *
 * With the library, motions are detected using combinations of rules.
 * When a rule is detected, a registered function is called.
 * Usage of the rules/callback system is not required to gain from this library;
 * using the abstraction layer and interpreting the gyroscope/accelerometer can provide
 * value in itself.
 */

/**
 * \brief
 * ipass namespace
 * \details
 * The ipass namespace contains all library
 * related code for the ipass project.
 */
namespace ipass {

    /**
     * \brief
     * The motion handler combines a rule with an action.
     * \details
     * The motion handler class is used internally to combine
     * a (combined set of) rules with a callback function that should
     * be called on rule match.
     */
    class motion_handler {
        friend class motion_sensor;

    public:
        using func = void (*)(const vector3<int16_t> &, const vector3<int16_t> &);

    private:
        func function;
        motion_rule *rule;

    public:
        /**
         * \brief
         * 0 argument constructor.
         * \details
         * Construct the motion handler with all values initialized to 0.
         */
        motion_handler();

        /**
         * \brief
         * 2 argument constructor with all requried values.
         * \details
         * Construct the motion handler with the given rule
         * and function. The handler does not have ownership of
         * the given rule.
         * @param rule
         * @param function
         */
        motion_handler(motion_rule &rule, func function);

        /**
         * \brief
         * Check if this handler is free (empty).
         * @return
         */
        bool is_free() const;
    };

    /**
     * \brief
     * Motion sensor base class.
     * \details
     * The base class for all motion sensor implementations.
     * This class also contains the handlers that can be registered.
     */
    class motion_sensor {
    protected:
        /**
         * \brief
         * The maximum amount of handlers that can be
         * registered.
         */
        constexpr static int8_t handler_count = 8;

        /**
         * \brief
         * All motion handlers that are registered.
         * Check if a spot is empty with motion_handler::is_free().
         */
        motion_handler handlers[handler_count];

    public:
        /**
         * \brief
         * 0 argument constructor.
         */
        motion_sensor();

        /**
         * \brief
         * Add a rule to to the handlers list.
         * \details
         * Add a rule to to the handlers list.
         * If no empty spot is available for the handler, -1 is returned.
         * Otherwise the handler index is returned.
         * Use the remove_handler() function to remove a registered handler.
         * Call process_handlers() to process all registered
         * handlers.
         * @param rule
         * @return
         */
        int8_t when(motion_rule &rule, motion_handler::func);

        /**
         * \brief
         * Remove a registered index from the handlers list.
         * \details
         * Remove a registered index from the handlers list.
         * If the index is below 0 or above the maximum handler count,
         * this function will do nothing.
         * @param index
         */
        void remove_handler(int8_t index);

        /**
         * \brief
         * Initialize the sensor.
         * \details
         * Initializes the sensor.
         * Implementation is defined by the implementor since
         * initialization code varies wildly between different pieces
         * of hardware.
         */
        virtual void initialize() = 0;

        /**
         * \brief
         * Get accelerometer data from the sensor.
         * @return
         */
        virtual vector3<int16_t> get_accel() = 0;

        /**
         * \brief
         * Get the x axis of the accelerometer.
         * \details
         * Get the x axis of the accelerometer.
         * By default, this functions calls get_accel() and
         * takes the x parameter of the retrieved vector.
         *
         * This function is meant for when you only need
         * to get one parameter from the sensor; if you need
         * other parameters please get the entire vector
         * from get_accel().
         * @return
         */
        virtual int16_t get_accel_x();

        /**
         * \brief
         * Get the y axis of the accelerometer.
         * \details
         * Get the y axis of the accelerometer.
         * By default, this functions calls get_accel() and
         * takes the y parameter of the retrieved vector.
         *
         * This function is meant for when you only need
         * to get one parameter from the sensor; if you need
         * other parameters please get the entire vector
         * from get_accel().
         * @return
         */
        virtual int16_t get_accel_y();

        /**
         * \brief
         * Get the z axis of the accelerometer.
         * \details
         * Get the z axis of the accelerometer.
         * By default, this functions calls get_accel() and
         * takes the z parameter of the retrieved vector.
         *
         * This function is meant for when you only need
         * to get one parameter from the sensor; if you need
         * other parameters please get the entire vector
         * from get_accel().
         * @return
         */
        virtual int16_t get_accel_z();

        /**
         * \brief
         * Get gyroscope data from the sensor.
         * @return
         */
        virtual vector3<int16_t> get_gyro() = 0;

        /**
        * \brief
        * Get the x axis of the gyroscope.
        * \details
        * Get the x axis of the gyroscope.
        * By default, this functions calls get_gyro() and
        * takes the x parameter of the retrieved vector.
        *
        * This function is meant for when you only need
        * to get one parameter from the sensor; if you need
        * other parameters please get the entire vector
        * from get_gyro().
        * @return
        */
        virtual int16_t get_gyro_x();

        /**
        * \brief
        * Get the y axis of the gyroscope.
        * \details
        * Get the y axis of the gyroscope.
        * By default, this functions calls get_gyro() and
        * takes the y parameter of the retrieved vector.
        *
        * This function is meant for when you only need
        * to get one parameter from the sensor; if you need
        * other parameters please get the entire vector
        * from get_gyro().
        * @return
        */
        virtual int16_t get_gyro_y();

        /**
        * \brief
        * Get the z axis of the gyroscope.
        * \details
        * Get the z axis of the gyroscope.
        * By default, this functions calls get_gyro() and
        * takes the z parameter of the retrieved vector.
        *
        * This function is meant for when you only need
        * to get one parameter from the sensor; if you need
        * other parameters please get the entire vector
        * from get_gyro().
        * @return
        */
        virtual int16_t get_gyro_z();

        /**
         * \brief
         * Process all registered motion handlers.
         */
        virtual void process_handlers();
    };

    /**
     * \brief
     * Motion sensor decorator that caches gyroscope and accelerometer data until refresh.
     * \details
     * Depending on the hardware, implementation and application complexity
     * the hidden cost of fetching the most recent data from the sensor may become
     * too expensive. This decorator caching the data, but the datamust be manually
     * refreshed using refresh().
     */
    class cached_motion_sensor : public motion_sensor {
    protected:
        vector3<int16_t> gyro, accel;
        motion_sensor &slave;

    public:
        /**
        * Decorator constructor.
        *
        * @param slave
        */
        explicit cached_motion_sensor(motion_sensor &slave);

        /**
         * Override to adhere to the motion_sensor
         * base class requirements, will call motion_sensor::initialize()
         * on the slave.
         */
        void initialize() override;

        /**
         * Get accel data, will return
         * the cached data.
         * @return
         */
        vector3<int16_t> get_accel() override;

        /**
         * Get gyro data, will return
         * the cached data.
         * @return
         */
        vector3<int16_t> get_gyro() override;

        /**
         * Refresh the gyroscope and accelerometer
         * data from the implementation.
         */
        void refresh();
    };

    /**
     * \brief
     * Base class for a motion corrected sensor decorator.
     */
    class corrected_motion_sensor : public motion_sensor {
    protected:
        motion_sensor &slave;
        vector3<int16_t> correction;

    public:
        /**
         * Constructor for the motion corrected
         * sensor decorator.
         *
         * @param slave
         * @param correction
         */
        corrected_motion_sensor(motion_sensor &slave, vector3<int16_t> correction);

        /**
         * Override to adhere to the motion_sensor
         * base class requirements, will call motion_sensor::initialize()
         * on the slave.
         */
        void initialize() override;
    };

    /**
     * \brief
     * Apply a correction to the gyroscope data.
     */
    class gyro_corrected_motion_sensor : public corrected_motion_sensor {
    public:
        /**
         * Decorator constructor.
         *
         * @param slave
         * @param correction
         */
        gyro_corrected_motion_sensor(motion_sensor &slave, const vector3<int16_t> &correction);

        /**
         * Get accel implementation, will simply
         * pass accel data from the slave.
         * @return
         */
        vector3<int16_t> get_accel() override;

        /**
         * Get gyro implementation, will
         * apply correction the data.
         * @return
         */
        vector3<int16_t> get_gyro() override;
    };

    /**
     * \brief
     * Apply a correction to the accelerometer data.
     */
    class accel_corrected_motion_sensor : public corrected_motion_sensor {
    public:
        /**
         * Decorator constructor.
         *
         * @param slave
         * @param correction
         */
        accel_corrected_motion_sensor(motion_sensor &slave, const vector3<int16_t> &correction);

        /**
          * Get accel implementation, will
          * apply correction the data.
          * @return
          */
        vector3<int16_t> get_accel() override;

        /**
        * Get gyro implementation, will simply
        * pass gyro data from the slave.
        * @return
        */
        vector3<int16_t> get_gyro() override;
    };
}

#endif //IPASS_MOTION_SENSOR_HPP
