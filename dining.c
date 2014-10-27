/*
 * OS Assignment #3
 *
 * @file dininig.c
 */

#include "sem.h"
#include <stdio.h>
#include <unistd.h>

static tsem_t *chopstick[5];
static tsem_t *printing;

static void
update_status (int i,
	       int eating)
{
  static int status[5] = { 0, };
  int idx;

  status[i] = eating;

  tsem_wait (printing);
  for (idx = 0; idx < 5; idx++)
    fprintf (stdout, "%3s     ", status[idx] ? "EAT" : "...");
  fprintf (stdout, "\n");
  tsem_signal (printing);
}

void *
thread_func (void *arg)
{
  int i = (int) (long) arg;

  do
    {
      tsem_wait (chopstick[i]);

      /* deadlock! */
      tsem_wait (chopstick[(i + 1) % 5]);

      update_status (i, 1);
      tsem_signal (chopstick[i]);
      tsem_signal (chopstick[(i + 1) % 5]);
      update_status (i, 0);
    }
  while (1);
  
  return NULL;
}

int
main (int    argc,
      char **argv)
{
  int i;

  for (i = 0; i < 5; i++)
    chopstick[i] = tsem_new (1);
  printing = tsem_new (1);

  for (i = 0; i < 5; i++)
    {
      pthread_t tid;

      pthread_create (&tid, NULL, thread_func, (void *) (long) i);
    }

  /* endless thinking and eating... */
  while (1)
    usleep (10000000);
  
  return 0;
}
