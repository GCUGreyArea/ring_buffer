#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>

#include <libProducerConsumer.h>

#define RB_SIZE 32


typedef struct st_container {
    char * string;
    int * read_cnt;
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
static const st_container_t * static_string_producer(char * value, int id) {

    // Because these are static they will persist after the function exectution
    // terminates! Current ID keeps track of how many times we have been called
    // and is used to index into the string store.
    static int current_id = 0;
    static int cnt = 0;

    // RB_SIZE string ogf 10 characters each!
    static char string_back[RB_SIZE][10];
    static st_container_t containers[RB_SIZE];

    // If things are still waiting and we don't have space
    // bail...
    if(cnt == RB_SIZE) {
        return NULL;
    }

    // If the strings have been consumed we can go back to the start
    if(current_id == RB_SIZE) {
        current_id = 0;
    }

    char * str = string_back[current_id];
    sprintf(str,"%s:%d", value,id);

    cnt++;

    // We pass in the address so that updates are reflected in this function!
    containers[current_id].read_cnt = &cnt;
    containers[current_id].string = str;
    
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
    int inc = 0;
    while (true)
    {
        ring_buffer_err_t er = rb_test(rb);
        if (er == RB_ERR_OK || er == RB_ERR_FULL)
        {
            uint64_t val = rb_get(rb);
            st_container_t *str = (st_container_t*)val;

            // Decrement the read count so the producer can move on.
            int v = --*(str->read_cnt);
            printf("received %s count %d\n", str->string, v);
        }
        else
        {
            printf("consummer sleeping (1): %d\n",inc++); 
            sleep(1);
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

    while (true)
    {
        for (int i = 1; i < RB_SIZE; i++)
        {
            ring_buffer_err_t er = rb_test(rb);
            if (er != RB_ERR_FULL)
            {
                goto start;
            retry:
                printf("retrying\n");

            start:

                string = static_string_producer("string",i);
                if(string) {
                    rb_add(rb, (uint64_t)string);

                }
                else {
                    sleep(0.5);
                    goto retry;
                }
            }
        }

        sleep(1);
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