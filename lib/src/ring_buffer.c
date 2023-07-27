/**
 * @file ring_buffer.c
 * @author your name (barry.robinson@uk.ngc.com)
 * @brief Create a usable ring buffer
 * @note The ring buffer, because of the way the index for the next value is
 * calculated, can store a maximum of size-1 elements. The size of the ring
 * buffer must also be a power of two number so that it can use bit wize
 * arithmatic to calculate it's possition in the buffer and wrap the index to
 * accomodate the next value
 * @version 0.1
 * @date 2023-07-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "ring_buffer.h"

static bool power_of_two_number(size_t n)
{
    return (n != 0) && ((n & (n - 1)) == 0);
}

ring_buffer_err_t rb_init_default(ring_buffer_t *rb)
{
    return rb_init(rb, RING_BUFFER_SIZE);
}

size_t get_power_of_two(size_t n) {
    return pow(2, ceil(log(n)/log(2)));
}

ring_buffer_err_t rb_init(ring_buffer_t *rb, size_t size)
{
    if (rb == NULL)
    {
        return RB_ERR_NULL_VALUE;
    }

    if (!power_of_two_number(size))
    {
        return RB_ERR_INVALID_SIZE;
    }

    rb->buffer = malloc(sizeof(uint64_t) * size);
    if (rb->buffer == NULL)
    {
        fprintf(stderr, "memory allocation failure\n");
        abort();
    }

    rb->size = size;

    memset(rb->buffer, 0, sizeof(uint64_t) * rb->size);
    rb->read = 0;
    rb->write = 0;
    rb->items = 0;
    rb->stat = false;

    return RB_ERR_OK;
}

/**
 * @brief Add a value to the buffer 
 *
 * @note The bitwise opperations work to wrap the value of read and write (head
 * and tail) because of we are using power of two numbers. A power of two number
 * can translates to a binary representation that is exploitable through a trick
 * of bitwise aristhmatic because binary is base 2.   
 *
 * For instance 4 is 0100 and 3 (4-1) is 0011, which means that 0100 & 0011 will
 * always be 0, but no other combination will produce the same results (i.e 0010
 * (2) and 0011 (3) does not yeild 0 because 0010 & 0011 == 0010). 
 *
 * Because 2^n-1 a invers binary mask of 2^n (i.e. 4 is 0100 and 3 is
 * 0011) anding will always return greater than 0 until the number reaches 2^n,
 * at which point it will return 0.  
 *
 * 0011 
 * 0100
 * ----
 * 0000
 *
 * @param rb 
 * @param value 
 * @return ring_buffer_err_t 
 */
ring_buffer_err_t rb_add(ring_buffer_t *rb, uint64_t value)
{
    if (rb == NULL)
    {
        return RB_ERR_NULL_VALUE;
    }

    // Prevent the head wraapping back to the tail.
    if (rb->items + 1 != rb->size)
    {
        rb->buffer[rb->write++] = value;

        // Because this is a bitwise operator we can execute this in a single
        // instruction
        rb->write = (rb->write & (rb->size - 1));
        rb->items++;
        return RB_ERR_OK;
    }

    return RB_ERR_FULL;
}

ring_buffer_err_t rb_test(ring_buffer_t *rb)
{
    if (rb->items == 0)
    {
        return RB_ERR_NO_DATA;
    }
    else if (rb->items == rb->size-1)
    {
        return RB_ERR_FULL;
    }

    return RB_ERR_OK;
}

uint64_t rb_get(ring_buffer_t *rb)
{
    // Prevent the read function going past the head
    if (rb->items == 0)
    {
        return 0;
    }

    uint64_t val = rb->buffer[rb->read];
    rb->buffer[rb->read++] = 0;
    rb->items--;

    rb->read = (rb->read & (rb->size - 1));

    return val;
}

void rb_teardown(ring_buffer_t *rb)
{
    if(rb && !rb->stat) {
        free(rb->buffer);
    }
}
