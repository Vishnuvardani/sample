//dinning philosopher problem

#include<stdio.h>
#include<semaphore.h>
#include <pthread.h>
#include<unistd.h>

sem_t chop[5];
sem_t mutex;
char status[6]={'-','-','-','-','-'}; //initally no state

void printstatus()
{
    int i;
    printf("\n");
    for(i=0;i<5;i++)
    {
        printf(" %c",status[i]);
    }
}

 void *philosopher(void *arg)
 {
     long int num =(long int)arg;
     //phil in hungry state
     status[num]='H';
     printstatus();
     //aquire left and right chop

     //lock the critical section
     sem_wait(&mutex);
     sem_wait(&chop[num]);
     Sleep(1);
     sem_wait(&chop[(num+1)%5]);

     //phil is eating state
     status[num]='E';
     printstatus();
     Sleep(1);

     //release chopstick
     sem_post(&chop[(num+1)%5]);
     sem_post(&chop[num]);

     //unlock the critical section
     sem_post(&mutex);

     //phil is thinking
     status[num]='T';
     printstatus();
     pthread_exit(NULL);
 }

 int main()
 {
     pthread_t phil[5]; //creating 5 philosopher
     long int i,j;
     //initalize semaphore
     for(i=0;i<5;i++)
     {
         sem_init(&chop[i],0,1); //add of sem var,not shared(0),inital value(1)
     }
     sem_init(&mutex,0,1);

     //printing heading of table
     printf("\n");
     for(i=0;i<5;i++)
    {
        printf("p[%ld]",i);
    }

     //create thread of philosopher
     for(i=0;i<5;i++)
     {
        pthread_create(&phil[i],NULL,philosopher,(void*)i);
     }

     //joining threads
     for(j=0;j<5;j++)
     {
        pthread_join(phil[j],NULL);
      }
 }
