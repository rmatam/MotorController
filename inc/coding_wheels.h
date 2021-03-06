/** @file */

#ifndef CODING_WHEELS_H
#define CODING_WHEELS_H

#include "hal.h"

/**
 * @brief Possible values for coding wheels orientation.
 */
typedef enum {
    DIRECT = 0U, /**< Direct orientation */
    INDIRECT = 1U /**< Indirect orientation */
} wheel_orientation_t;

/**
 * @brief Configuration structure for coding wheels.
 *
 * @remark The `orientation` parameters allow the user to specify which rotation direction
 * corresponds to a forward movement of the robot.
 */
typedef struct {
    int32_t initial_right_ticks; /**< Initial value of the right coding wheel counter */
    wheel_orientation_t right_wheel_orientation; /**< Orientation of the right coding wheel */
    int32_t initial_left_ticks; /**< Initial value of the left coding wheel counter */
    wheel_orientation_t left_wheel_orientation; /**< Orientation of the left coding wheel */
} coding_wheels_config_t;

/*
 * Number of ticks counted by the right coding wheel.
 */
extern volatile int32_t right_ticks;

/*
 * Number of ticks counted by the left coding wheel.
 */
extern volatile int32_t left_ticks;

/**
 * @brief Perform all the initializations required by the coding wheels.
 *
 * @param[in] config The initial configuration of the coding wheels driver.
 *            For common use, initial_left_ticks and initial_right_ticks should
 *            be set to 0.
 * @remark Behaviour is undefined for now if initial ticks aren't 0.
 */
extern void init_coding_wheels(coding_wheels_config_t config);

#endif /* CODING_WHEELS_H */
