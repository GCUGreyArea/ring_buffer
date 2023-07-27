# ring buffer

## Dependencies

1. [Google test](https://github.com/google/googletest) framework.
2. [Google benchmark](https://github.com/google/benchmark) framework

These can be installed in Linux by running sudo `sudo apt install libgtest-dev`
and `sudo apt install libbenchmark-dev` respectively. On MacOS the commands are
`brew install googletest` and `brew install google-benchmark`.

Or they can be built from source

## Building the project

The project has been designed and tested on MacOS but should build and function
correctly on Linux. If you are running Windows 10 or 11 please build this
project in WSL2 using the latest Ubuntu distro.

```bash
$ git clone https://github.com/GCUGreyArea/ring_buffer.git
$ cd ring_buffer
$ make test benchmark project
$ ./build/producer_consumer
```

## Updating the project

If you already have the code

```bash
$ cd ring_buffer
$ git pull
$ make clean test benchmark project
$ ./build/produce_consumer
```

## Building and running unit tests and benchmarks

Unit tests and benchmarks are built in the standard build. Test are provided in
the `test` directory and benchmarks in the `benchmark` directory. These can
either be run from the command line or through the makefile.

```bash
$ ./test/build/test_producer_consumer

OR

$ make test
```

```bash
$ ./benchmark/build/benchmark_producer_consumer

OR

make benchmark
```

## Optional code documentation

Optional code documentation is also available through
[Doxygen](https://doxygen.nl/manual/starting.html). Both `Doxygen` and
`graphviz` need to be installed.

Doxygen can be [installed from source](https://doxygen.nl/manual/install.html)
on either MacOS or Linux.

On Linux run `sudo apt-get install doxygen graphviz` On MacOS run `brew install
doxygen` and `brew install graphviz`


```bash
$ make docs
```

The resulting HTML pages will be available in `docs/output/html`

## ring buffer API

```c
ring_buffer_err_t rb_init_default(ring_buffer_t *rb);
ring_buffer_err_t rb_init(ring_buffer_t *rb, uint16_t size);
ring_buffer_err_t rb_add(ring_buffer_t *rb,uint64_t value);
ring_buffer_err_t rb_test(ring_buffer_t *rb);
uint64_t rb_get(ring_buffer_t *rb);
void rb_teardown(ring_buffer_t *rb);
```

### Using a buffer

Memory for the structure is not assigned by the module, but the internals are.
The use pattern for a buffer is

```c
    // Create and initialise the buffer
    ring_buffer_t rb;
    ring_buffer_err_t er = rb_init(&rb, RB_SIZE);
    if (er != RB_ERR_OK)
    {
        printf("Failed to initialise ring buffer: %d\n",er);
        abort();
    }

    // Use the buffer 
    // ...

    // Then teardown the buffer
    rb_teardown(&rb);
```

The only errors that `rb_init` can realistically generate are
`RB_ERR_NULL_VALUE` meaning a NULL value was passed in for initialisation, and
`RB_ERR_INVALID_SIZE` meaning that trhe size requested was not a [power of 2
number](https://en.wikipedia.org/wiki/Power_of_two). Power of two numbers are
used due to the ease with which the end points in the array can be calculated
using bit wise arithmatic and teh indicies wraped efficiently.


### Static buffer API

You cabn also create a static ring buffer (one that is alocated from the stack rather than the heap) by using the macro

```c
#define STATIC_BUFFER(size, name) \
    const size_t s = pow(2, ceil(log(size)/log(2))); \
    uint64_t ar[s]; \
    ring_buffer_t name = {ar,0,0,s,0,true}
```

Please note carfully that no attempt is made to insure there are enough stack resources to satisfy the the variable declaraation. It is left entirely to the used to not ask for more resources than exists. 

Also note that a stack created buffer guards against having `rb_teardown` called on it by seting a flag that it can test during teardown.

## Testing the capacity of the buff

The capacity of the buffer can be tested for by calling `rb_test` which will return one of three values

1. `RB_ERR_NO_DATA`: There is no data in the buffer waiting to be read
2. `RB_ERR_FULL`: The buffer is full
2. `RB_ERR_OK`: The buffer has data and capacity 

### Adding values to the buffer 

The ring buffer is a thread safe object. You cannot write past the tail of the
buffer as the algorithm gurentees that a call to `rb_add` will return
`RB_ERR_FULL` once the buffer is at capacity. The capacity, due to the way
wrapping is calculated, is always `SIZE-1`. Calls to `rb_add` should test the
return value to insure that the item has been added to the buffer if this is
important. Alternatively the capcaity can be tested rior to an add or get call
by calling `rb_test`.

### Getting values from the buffer

Getting values from the buffer is done via `rb_get`, which will return the value
at the location, ort `0` if no values are availible. Note that this excludes the
idea of an `NULL` values having significance. Alternatively the capcaity can be
tested rior to an add or get call by calling `rb_test`.


## performace stats 

Performance stats where gathered on WSL2 using this implementtion
(producer_consumer) threaded program run with `perf record`. System calls have
been removed from the output for ease of reading.

```text 
# Overhead  Command          Shared Object            Symbol                                                                                                                                                       
# ........  ...............  .......................  ............................
#
    19.57%  producer_consum  libproducer_consumer.so  [.] rb_test
    10.80%  producer_consum  producer_consumer        [.] run_consumer
     2.78%  producer_consum  producer_consumer        [.] run_producer
     1.04%  producer_consum  libproducer_consumer.so  [.] rb_add
     0.99%  producer_consum  libproducer_consumer.so  [.] rb_get
```

Full stats can be viewed at [docs/perf/perf.md](docs/perf/perf.md)


## License 

This software is licensed under the `GNU GENERAL PUBLIC LICENSE` version 3.

Please read the [license](LICENSE.TXT) before using this software or integrating
it into your project
