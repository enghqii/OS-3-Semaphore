/*
 * OS Assignment #3
 *
 * @file test.c
 */

#include "sem.h"
#include <stdio.h>
#include <unistd.h>

#define THREAD_MAX 10

static tsem_t *start_sem[THREAD_MAX];
static tsem_t *finish_sem[THREAD_MAX];

void *
thread_func (void *arg)
{
  int idx = (int) (long) arg;

  tsem_signal (start_sem[idx]);

  fprintf (stdout, "thread[%d] entered...\n", idx);
  usleep (1000000);
  fprintf (stdout, "thread[%d] leaved...\n", idx);

  tsem_signal (finish_sem[idx]);
  
  return NULL;
}

int
main (int    argc,
      char **argv)
{
  int idx;

  for (idx = 0; idx < THREAD_MAX; idx++)
    {
      pthread_t tid;

      start_sem[idx] = tsem_new (0);
      finish_sem[idx] = tsem_new (0);
      pthread_create (&tid, NULL, thread_func, (void *) (long) idx);
      tsem_wait (start_sem[idx]);
    }

  for (idx = 0; idx < THREAD_MAX; idx++)
    {
      tsem_wait (finish_sem[idx]);
      tsem_free (finish_sem[idx]);
      tsem_free (start_sem[idx]);
    }

  return 0;
}
