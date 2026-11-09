#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
    // Cast the parameter back to the struct type
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    // 1. Wait before obtaining the mutex (convert ms to microseconds)
    usleep(thread_func_args->wait_to_obtain_ms * 1000);

    // 2. Obtain the mutex (lock)
    pthread_mutex_lock(thread_func_args->mutex);

    // 3. Wait while holding the mutex
    usleep(thread_func_args->wait_to_release_ms * 1000);

    // 4. Release the mutex (unlock)
    pthread_mutex_unlock(thread_func_args->mutex);

    // Return the pointer as suggested by the original stub.
    // (Note: This might cause a small memory leak if the test doesn't free it, 
    // but it strictly follows the provided template).
    return thread_param; 
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    // 1. Allocate memory for the thread data
    struct thread_data* data = (struct thread_data*) malloc(sizeof(struct thread_data));
    
    // Check if malloc failed
    if (data == NULL) {
        ERROR_LOG("Failed to allocate memory for thread data");
        return false;
    }

    // 2. Setup the struct with the provided arguments
    data->mutex = mutex;
    data->wait_to_obtain_ms = wait_to_obtain_ms;
    data->wait_to_release_ms = wait_to_release_ms;

    // 3. Create the thread using threadfunc as the entry point
    int rc = pthread_create(thread, NULL, threadfunc, (void *)data);

    // Check if thread creation failed
    if (rc != 0) {
        ERROR_LOG("Failed to create thread");
        free(data); // Clean up if thread creation fails
        return false;
    }

    return true;
}
