#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <execinfo.h>
#include <errno.h>

#include <libProducerConsumer.h>

#define RB_SIZE 32

volatile bool g_run_flag = true;

void int_handler(int value)
{
    printf("signal caught\n");
    switch (value)
    {
    case SIGINT:
        printf("sigint recieved, terminating\n");
        g_run_flag = false;
        break;

    default:
        break;
    }
}

// Container structure to allow synchronisation between the producer and
// consumer threads / processes.
typedef struct st_container
{
    char string[20]; // The string being transmited
    bool clear;      // clear flag
} st_container_t;

/**
 * @brief Generate a static string without and use one from a local memory from
 * a local store rathern that using malloced heap memory
 *
 * @param consumed flagg indicating that the previous strings have been consumed
 * @param value value to use as tghe first part of the string
 * @param id id to use as the next part
 * @return const char*
 */
static const st_container_t *static_string_producer(char *value, int id)
{
    // Because these are static they will persist after the function exectution
    // terminates! Current ID keeps track of how many times we have been called
    // and is used to index into the message store.
    static int current_id = 0;
    static st_container_t containers[RB_SIZE];
    static bool init = false;

    // This will ony run once
    if (!init)
    {
        for (size_t i = 0; i < RB_SIZE; i++)
        {
            containers[i].clear = true;
        }

        init = true;
    }

    // We want to rotate though the IDs so we use the same trick as the ring
    // buffer because we know it's a power of 2 size
    current_id &= (current_id & (RB_SIZE - 1));

    // we need to make sure that the slot is free before we lock
    int count = 0;
    while (!containers[current_id].clear && current_id != RB_SIZE)
    {
        count++;
        current_id &= (current_id & (RB_SIZE - 1));
        if (count == RB_SIZE)
        {
            // We have cycled trhrough all the slots, give the reader a chance
            // to catch up by sleeping whch yeilds control to other threads
            sleep(0.1);
            count = 0;
        }
    }

    __sync_bool_compare_and_swap (&containers[current_id].clear,true,false); // and mark this as to be read
    sprintf(containers[current_id].string, "%s:%d", value, id);
    return &containers[current_id++];
}

/**
 * @brief Called as the consumer thread
 *
 * @param ptr
 * @return void*
 */
void *run_consumer(void *ptr)
{
    ring_buffer_t *rb = (ring_buffer_t *)ptr;
    char local[30];
    char addr[17];

    while (g_run_flag)
    {
        ring_buffer_err_t er = rb_test(rb);
        if (er == RB_ERR_FULL || er == RB_ERR_OK)
        {
            uint64_t val = rb_get(rb);
            // Not sure why, possibly a race condition? ODD.
            if (val == 0)
            {
                printf("empty slot?\n");
                sleep(1);
                continue;
            }

            st_container_t *str = (st_container_t *)val;

            strcpy(local, str->string);
            sprintf(addr, "%p", str);

            // Because this will not experience contention due to code ordering,
            // this is OK. In the normal run of things however we would wat to
            // make this atomic or use a lock to guard against two threads
            // writing and reading simultaniously.
           __sync_bool_compare_and_swap(&str->clear,false,true);

            printf("string: %s, slot %s\n", local, addr);
        }
    }

    return ptr;
}

/**
 * @brief Called as the producer thread
 *
 * @param ptr
 * @return void*
 */
void *run_producer(void *ptr)
{
    ring_buffer_t *rb = (ring_buffer_t *)ptr;
    int i = 0;

    while (g_run_flag)
    {
        ring_buffer_err_t er = rb_test(rb);
        if (er == RB_ERR_OK || er == RB_ERR_NO_DATA)
        {
            rb_add(rb, (uint64_t)static_string_producer("string", i++));
            i &= (RB_SIZE - 1);
        }
        else
        {
            sleep(0.3);
        }
    }

    return ptr;
}

/**
 * @brief Run two simltanious process as producer and consumer
 *
 * @note For a better understanding of pthreads see
 * https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, const char **argv)
{
    ring_buffer_t rb;
    ring_buffer_err_t er = rb_init(&rb, RB_SIZE);
    if (er != RB_ERR_OK)
    {
        printf("Failed to initialise ring buffer: %d\n", er);
        abort();
    }

    // setup the signal handler
    signal(SIGINT, int_handler);

    pthread_t thread1;
    pthread_t thread2;

    int iret1 = pthread_create(&thread1, NULL, run_producer, (void *)&rb);
    int iret2 = pthread_create(&thread2, NULL, run_consumer, (void *)&rb);

    pthread_join(thread2, NULL);
    pthread_join(thread1, NULL);

    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);

    rb_teardown(&rb);

    return 0;
}