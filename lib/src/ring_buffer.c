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

#include "ring_buffer.h"

static bool power_of_two_number(uint16_t n)
{
    return (n != 0) && ((n & (n - 1)) == 0);
}

ring_buffer_err_t rb_init_default(ring_buffer_t *rb)
{
    return rb_init(rb, 36);
}

ring_buffer_err_t rb_init(ring_buffer_t *rb, uint16_t size)
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

    return RB_ERR_OK;
}

ring_buffer_err_t rb_add(ring_buffer_t *rb, uint64_t value)
{
    if (rb == NULL)
    {
        return RB_ERR_NULL_VALUE;
    }

    if (rb->items + 1 != rb->size)
    {
        rb->buffer[rb->write++] = value;

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
    else if (rb->items + 1 == rb->size)
    {
        return RB_ERR_FULL;
    }

    return RB_ERR_OK;
}

uint64_t rb_get(ring_buffer_t *rb)
{
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
    free(rb->buffer);
}