/*
 * OS Assignment #3
 *
 * @file dininig.c
 */

#include "sem.h"
#include <stdio.h>
#include <unistd.h>

static tsem_t *room;
static tsem_t *printing;
static tsem_t *chopstick[5];

static void update_status (int i, int eating) {

    static int status[5] = { 0, };
    int idx;

    status[i] = eating;

    if(eating == 0) return;

    tsem_wait (printing);
    for (idx = 0; idx < 5; idx++) {
        fprintf(stdout, "%3s     ", status[idx] ? "EAT" : "...");
    }
    fprintf (stdout, "\n");
    tsem_signal (printing);

}

void * thread_func (void *arg) {

    int i = (int) (long) arg;

    do{
        /*
        int leftFork = i;
        int rightFork = (i - 1 + 5) % 5;

        int forkPickedUp;
        int otherFork;
        int pickedUp;

        if( leftFork > rightFork ){
            forkPickedUp = leftFork;
            otherFork = rightFork;
        } else {
            forkPickedUp = rightFork;
            otherFork = leftFork;
        }

        pickedUp = tsem_try_wait(chopstick[forkPickedUp]);

        if( pickedUp == 0 ){
            int pickedUpOther = tsem_try_wait(chopstick[otherFork]);

            if(pickedUpOther == 0){
                update_status (i, 1);
                tsem_signal(chopstick[otherFork]);
            }
            tsem_signal(chopstick[forkPickedUp]);
        }

        update_status(i, 0);
*/
        tsem_wait(room);
        tsem_wait(chopstick[i]);
        tsem_wait(chopstick[(i + 1) % 5]);

        update_status (i, 1);

        tsem_signal(chopstick[i]);
        tsem_signal(chopstick[(i + 1) % 5]);

        update_status (i, 0);

        tsem_signal(room);

    }
    while (1);
  
  return NULL;
}

int main (int argc, char **argv) {

    int i;

    room = tsem_new(4);

    for (i = 0; i < 5; i++) {
        chopstick[i] = tsem_new(1);
    }

    printing = tsem_new(1);

    for (i = 0; i < 5; i++) {
        pthread_t tid;
        pthread_create(&tid, NULL, thread_func, (void *) (long) i);
    }

    /* endless thinking and eating... */
    while (1) {
        usleep(10000000);
    }

    return 0;
}
