#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>

#include <libProducerConsumer.h>

#define RB_SIZE 32

void *run_consumer(void *ptr)
{
    printf("running consumer\n");
    ring_buffer_t *rb = (ring_buffer_t *)ptr;
    int inc = 0;
    while (true)
    {
        ring_buffer_err_t er = rb_test(rb);
        if (er == RB_ERR_OK || er == RB_ERR_FULL)
        {
            uint64_t val = rb_get(rb);
            char *str = (char *)val;
            printf("received %s\n", str);
            free(str);
        }
        else
        {
            printf("consummer sleeping (2): %d\n",inc++); 
            sleep(2);
        }

               
    }

    return ptr;
}

void *run_producer(void *ptr)
{
    printf("running producer\n");
    ring_buffer_t *rb = (ring_buffer_t *)ptr;
    char *string = NULL;

    while (true)
    {
        for (int i = 1; i < RB_SIZE; i++)
        {
            ring_buffer_err_t er = rb_test(rb);
            if (er != RB_ERR_FULL)
            {
                string = (char *)malloc(sizeof(char) * 35);
                sprintf(string, "str:%d", i);
                rb_add(rb, (uint64_t)string);
            }
        }

        sleep(1);
    }

    return ptr;
}

int main(int argc, const char **argv)
{
    ring_buffer_t rb;
    ring_buffer_err_t er = rb_init(&rb, RB_SIZE);
    if (er != RB_ERR_OK)
    {
        printf("Failed to initialise ring buffer: %d\n",er);
        abort();
    }

    pthread_t thread1;
    pthread_t thread2;

    int iret1 = pthread_create(&thread1, NULL, run_producer, (void *)&rb);
    int iret2 = pthread_create(&thread2, NULL, run_consumer, (void *)&rb);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);

    rb_teardown(&rb);

    return 0;
}