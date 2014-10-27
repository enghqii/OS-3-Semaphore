/*
 * OS Assignment #3
 *
 * @file sem.h
 */

#ifndef __SEM_H__
#define __SEM_H__

#include <pthread.h>

typedef struct test_semaphore tsem_t;

tsem_t *tsem_new      (int      value);
void    tsem_free     (tsem_t  *sem);
void    tsem_wait     (tsem_t  *sem);
int     tsem_try_wait (tsem_t  *sem);
void    tsem_signal   (tsem_t  *sem);

#endif /* __SEM_H__ */
