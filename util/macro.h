#ifndef UTIL_MACRO_H
#define UTIL_MACRO_H

#define MIN(a, b) \
        (((a) < (b)) ? (a) : (b))

#define MAX(a, b) \
        (((a) > (b)) ? (a) : (b))

#define ABS(a) \
        (((a) < 0) ? -(a) : (a))

/**
 * Make sure x is between low and high
 *
 * Example:
 * CLAMP(42, 2, 15) // => 15
 * CLAMP(2, 10, 42) // => 10
 * CLAMP(24, 5, 42) // => 24
 */
#define CLAMP(x, low, high) \
        (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

/**
 * Get the size of an static array
 *
 * Example:
 * struct foo bar[42];
 * ARR_SIZE(bar) // => 42
 */
#define ARR_SIZE(arr) \
        (sizeof(arr) / sizeof((arr)[0]))

#endif
