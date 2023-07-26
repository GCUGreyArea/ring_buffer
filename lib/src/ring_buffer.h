#ifndef RING_BUFFER_H
#define RING_BUFFER_H


#ifndef RING_BUFFER_SIZE
#define RING_BUFFER_SIZE 8
#endif//RING_BUFFER_SIZE

#include <stdint.h>
#include <math.h>

typedef struct ring_buffer {
    uint64_t * buffer;  // The buffer 
    size_t write;       // Write point (head of the ring)
    size_t read;        // Read point (tail of the ring)
    size_t size;        // Size of the buffer
    size_t items;       // Items in the buffer
    bool stat;          // Statically or dynamically assigned
} ring_buffer_t;

#define STATIC_BUFFER(size, name) \
    const size_t s = pow(2, ceil(log(size)/log(2))); \
    uint64_t ar[s]; \
    ring_buffer_t name = {ar,0,0,s,0,true}

typedef enum rung_buffer_err {
    RB_ERR_OK,
    RB_ERR_INVALID_SIZE,
    RB_ERR_NULL_VALUE,
    RB_ERR_FULL,
    RB_ERR_NO_DATA
} ring_buffer_err_t;


size_t get_power_of_two(size_t n);

ring_buffer_err_t rb_init_default(ring_buffer_t *rb);
ring_buffer_err_t rb_init(ring_buffer_t *rb, size_t size);
ring_buffer_err_t rb_add(ring_buffer_t *rb,uint64_t value);
ring_buffer_err_t rb_test(ring_buffer_t *rb);
uint64_t rb_get(ring_buffer_t *rb);
void rb_teardown(ring_buffer_t *rb);

#endif//RING_BUFFER_H