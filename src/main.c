#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>

#include <libProducerConsumer.h>

#define RB_SIZE 32


typedef struct st_container {
    char * string;
    bool clear;
    pthread_mutex_t* lock;
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
    int current_id = 0;

    // RB_SIZE string ogf 10 characters each!
    static char strings[RB_SIZE][30];
    static st_container_t containers[RB_SIZE];
    static pthread_mutex_t lock;

    while(!containers[current_id++].clear && current_id != RB_SIZE) {
        printf("testing %d\n",current_id);
    }

    if(current_id == RB_SIZE){
        return NULL;
    }

    pthread_mutex_lock(&lock);
    char * str = strings[current_id];
    containers[current_id].string = str;
    containers[current_id].lock = &lock;
    containers[current_id].clear = true;


    
    sprintf(str,"%s:%d", value,id);

    // reset the flag
    containers[current_id].clear = false;
    st_container_t * ret =  &containers[current_id++];

    pthread_mutex_unlock(&lock);
    
    return ret;
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
        
            pthread_mutex_lock(str->lock);

            // Decrement the read count so the producer can move on.
            str->clear = true;

            pthread_mutex_unlock(str->lock);
            printf("received %s\n", str->string);
        }
        else
        {
            printf("consummer sleeping (1): %d\n",inc++); 
            sleep(2);
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
                
                string = static_string_producer("string",i);
                if(string) {
                    rb_add(rb, (uint64_t)string);
                }
                else {
                    // This will happen if there are no more free slots
                    // This will yeaild the thread and allow the consuner to unlock resources
                    sleep(0.5);
                }

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