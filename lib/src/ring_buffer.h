#ifndef RING_BUFFER_H
#define RING_BUFFER_H


// #ifndef RING_BUFFER_SIZE
// #define RING_BUFFER_SIZE (4^2)
// #endif//RING_BUFFER_SIZE

#include <stdint.h>

typedef struct ring_buffer {
    uint64_t * buffer;
    uint16_t write;
    uint16_t read;
    uint16_t size;
    uint16_t items;
} ring_buffer_t;

typedef enum rung_buffer_err {
    RB_ERR_OK,
    RB_ERR_INVALID_SIZE,
    RB_ERR_NULL_VALUE,
    RB_ERR_FULL,
    RB_ERR_NO_DATA
} ring_buffer_err_t;

ring_buffer_err_t rb_init_default(ring_buffer_t *rb);
ring_buffer_err_t rb_init(ring_buffer_t *rb, uint16_t size);
ring_buffer_err_t rb_add(ring_buffer_t *rb,uint64_t value);
ring_buffer_err_t rb_test(ring_buffer_t *rb);
uint64_t rb_get(ring_buffer_t *rb);
void rb_teardown(ring_buffer_t *rb);

#endif//RING_BUFFER_H