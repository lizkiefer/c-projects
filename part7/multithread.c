/*
*multithread.c / Complex Synchronization
*
*Liz Kiefer / CS5600 / Northeastern University
*Fall 2024 / Oct 17, 2024
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
 
static int globalArray[120];
 
void *workerA(void *data)
{
    char *name = (char*)data;
 
    for (int i = 0; i < 120; i++)
    {
        usleep(50000);
        globalArray[i] = i % 3;
    }
 
    printf("Thread %s done!\n", name);
    return NULL;
}
 
void *workerB(void *data)
{
    char *name = (char*)data;
 
    for (int i = 0; i < 120; i++)
    {
        usleep(50000);
        printf("globalArray value at %i: %i\n", i, globalArray[i]);
    }
 
    printf("Thread %s done!\n", name);
    return NULL;
}
 
int main(void)
{
    pthread_t th1, th2;
    pthread_create(&th1, NULL, workerA, "X");
    pthread_create(&th2, NULL, workerB, "Y");
    sleep(1);
    printf("====> Cancelling Thread %li!!\n", th1);
    pthread_cancel(th2);
    usleep(100000);
    printf("====> Cancelling Thread %li!\n", th2);
    pthread_cancel(th1);
    printf("exiting from main program\n");
    return 0;
}