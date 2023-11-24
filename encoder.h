#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include <stdio.h>

/**
 * @brief Representation of possible states for the 2-bit encoder.
 * LOCKED = 90 degrees (bollard arm perpendicular to ground)
 * UNLOCKED = 0 degrees (bollard arm parallel to ground)
 * TRANSIT = 0-90 degrees (bollard arm between locked and unlocked position)
 * OVEREXTENDED = 90-180 degrees (bollard arm is extended past the locked position)
 */
typedef uint8_t encoder_state_t;
enum
{
  ENCODER_LOCKED,
  ENCODER_TRANSIT,
  ENCODER_OVEREXTENDED,
  ENCODER_UNLOCKED,
  ENCODER_ERROR
};

/**
 * @brief Enables the encoder. N.B. reading encoder value instantly after enabling it results in incorrect readings.
 */
void encoder_enable(void);

/**
 * @brief Disables the encoder.
 */
void encoder_disable(void);

/**
 * @brief Reads the encoder bits and converts then into an encoder state representing the 4 possible positions.
 *
 * @return Current position according to the encoder.
 */
encoder_state_t encoder_read(void);

/**
 * @brief Enables the encoder, performs a reading, disables the encoder and returns the result.
 */
encoder_state_t encoder_poll(void);

/**
 * @brief Return string corresponding to encoder value.
 * @param val The encoder value
 * @param str The array to stroe the str inside of.
 */
void encoder_to_string(encoder_state_t val, char * str);
#endif
