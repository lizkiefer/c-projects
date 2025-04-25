#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 15
#define THREADCOUNT 5

int buffer[BUF_SIZE];
int num = 0;
int totalProduced = 0;
int totalConsumed = 0;
pthread_mutex_t mut;
pthread_cond_t cond;

void *producer(void *param);
void *consumer(void *param);

int main (int argc, char *argv[])
{
    printf("pthread_mutex_init\n");
    if(pthread_mutex_init(&mut, NULL) != 0)
    {
        perror("pthread_mutex_init");
        exit(1);
    }
    
    printf("pthread_cond_init\n");
    if(pthread_cond_init(&cond, NULL) != 0)
    {
        perror("pthread_cond_init");
        exit(1);
    }
    
    // Create producer threads
    pthread_t producers[THREADCOUNT];
    for (int i = 0; i < THREADCOUNT; i++)
    {
        printf("pthread_create producer %i\n", i);
        if (pthread_create(&producers[i], NULL, producer, NULL) != 0)
        {
            perror("pthread_create");
            exit (1);
        }
    }
    
    // Create consumer threads
    pthread_t consumers[THREADCOUNT];
    for (int i = 0; i < THREADCOUNT; i++)
    {
        printf("pthread_create consumer %i\n", i);
        if (pthread_create(&consumers[i], NULL, consumer, NULL) != 0)
        {
            perror("pthread_create");
            exit (1);
        }
    }
    
    /* wait a while and then exit */
    printf("Sleeping 30\n");
    sleep(30);
    printf("WE ARE DONE\n");
}

// producer
// Increments num, exits when total increments is 30
void *producer(void *param)
{
    int i=0;
    while(totalProduced < 30)
    {
        pthread_mutex_lock(&mut);
        if (num > BUF_SIZE) 
        {
            exit(1);
        }
        while (num == BUF_SIZE)	
        {
            // Wait for another thread to signal to wake
            pthread_cond_wait (&cond, &mut);
        }
        buffer[num] = i;
        num++;
        totalProduced++;
        printf("Producer %li num %i, total produced %i\n", pthread_self(), num, totalProduced);
        pthread_mutex_unlock (&mut);
        pthread_cond_signal (&cond);
        sleep(1);
    }
    
    printf("Consumer %li Exiting\n", pthread_self());
}

// consumer
// Decrements num, exits when total decrements is 30
void *consumer(void *param)
{
    int i=0;
    while (totalConsumed < 30) {
        pthread_mutex_lock(&mut);
        if (num < 0)
        {
            exit(1);
        }
        while (num == 0)
        {
            pthread_cond_wait (&cond, &mut);
        }
        i = buffer[num];
        num--;
        totalConsumed++;
        printf("Consumer %li num %i, total consumed %i\n", pthread_self(), num, totalConsumed);
        pthread_mutex_unlock (&mut);
        pthread_cond_signal (&cond);
        sleep(3);
    }
    
    printf("Consumer %li Exiting\n", pthread_self());
}
