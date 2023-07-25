#include <benchmark/benchmark.h>
#include <libProducerConsumer.h>

#include <libProducerConsumer.h>

static void BM_AddGetBuffer(benchmark::State &state) {
    ring_buffer_t rb;
    ring_buffer_err_t er = rb_init(&rb,256);
    if(er != RB_ERR_OK) {
        printf("failed to create ring buffer\n");
        abort();
    }

    for (auto _ : state) {
        for(int i=0; i<256; i++) {
            rb_add(&rb,i);
        }

        for(int i=0; i < 256; i++) {
            rb_get(&rb);
        }
    }

    rb_teardown(&rb);
}

// Register the function as a benchmark
BENCHMARK(BM_AddGetBuffer);

// Run the benchmark
BENCHMARK_MAIN();

/**
 * @}
 * @}
 *
 */