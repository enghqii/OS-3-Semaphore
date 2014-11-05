/*
 * OS Assignment #3
 *
 * @file sem.c
 */

#include "sem.h"
#include <stdlib.h>

struct test_semaphore
{
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    int value;
};

tsem_t * tsem_new (int value) {

    tsem_t * ret = (tsem_t *) malloc(sizeof(tsem_t));

    if(ret == NULL) {
        return NULL;
    }else {
        ret->value = value;
        pthread_mutex_init(&(ret->mutex), NULL);
        pthread_cond_init(&(ret->cond), NULL);
    }
    return ret;
}

void tsem_free (tsem_t *sem) {
    free(sem);
}

void tsem_wait (tsem_t *sem) {

    pthread_mutex_lock(&(sem->mutex));
    sem->value--;

    if(sem->value < 0){
        // wait
        pthread_cond_wait(&(sem->cond), &(sem->mutex));
    }
    pthread_mutex_unlock(&(sem->mutex));
}

int tsem_try_wait (tsem_t *sem) {

    if(sem->value >= 1){
        sem->value--;
        return 0;
    }else{
        return 1;
    }
}

void tsem_signal (tsem_t *sem) {

    pthread_mutex_lock(&(sem->mutex));
    sem->value += 1;

    if(sem->value <= 0) {
        pthread_cond_signal(&(sem->cond));
    }
    pthread_mutex_unlock(&(sem->mutex));
}
