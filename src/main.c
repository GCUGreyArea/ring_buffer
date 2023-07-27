#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include <libProducerConsumer.h>

#define RB_SIZE 32

// Container structure to allow synchronisation between the producer and
// consumer threads / processes.
typedef struct st_container
{
    char string[15]; // The string being transmited
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
    while (containers[current_id].clear == false && current_id != RB_SIZE)
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

    containers[current_id].clear = false; // and mark this as to be read
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
    printf("running consumer\n");
    ring_buffer_t *rb = (ring_buffer_t *)ptr;
    char local[30];
    char addr[17];

    while (true)
    {

        ring_buffer_err_t er = rb_test(rb);
        if (er == RB_ERR_OK || er == RB_ERR_FULL)
        {
            uint64_t val = rb_get(rb);
            if(val == 0) {
                printf("empty slot?\n");
                continue;
            }

            st_container_t *str = (st_container_t *)val;

            strcpy(local, str->string);
            sprintf(addr, "%p", str);

            // Decrement the read count so the producer can move on.
            str->clear = true;

            printf("string: %s, slot %s\n", local, addr);
        }
        else
        {
            sleep(0.1);
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
    printf("running producer\n");
    ring_buffer_t *rb = (ring_buffer_t *)ptr;
    const st_container_t *string = NULL;

    int i = 0;
    while (true)
    {
        ring_buffer_err_t er = rb_test(rb);
        if (er != RB_ERR_FULL)
        {

            string = static_string_producer("string", i++);
            if (string)
            {
                rb_add(rb, (uint64_t)string);
                i &= (RB_SIZE - 1);
            }
            else
            {
                // This will happen if there are no more free slots
                // This will yeaild the thread and allow the consuner to unlock resources
                sleep(1);
            }
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