#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_OF_THREADS 6
#define ARRAY_SIZE 10000

int TOTAL = 0;

pthread_mutex_t the_mutex;

int global_array[ARRAY_SIZE] = {0};
int k;

void global_array_initializer () {
	//extern int global_array; 
  //declaring external array
	for (k = 1; k <= ARRAY_SIZE; k++) 
  {
		global_array[k-1] = k%257;
	}
	
}

void *print_total(void *threadid)
{  
  int tid;
  tid = (int)threadid;
  
  for(int i = (tid-1)*2000; i < tid*(2000-1); i++)
    {
      pthread_mutex_lock(&the_mutex);
      TOTAL += global_array[i];
      pthread_mutex_unlock(&the_mutex);
    }
  pthread_exit(NULL);
}

int main(void) 
{ 
  //initialize
  int i,j, status;
  pthread_t threads[NUM_OF_THREADS];
  
  //Fills array with values of 0 through 256
  global_array_initializer();

  for(int j = 1; j < NUM_OF_THREADS; j++)
  {
    pthread_create(&threads[j], NULL, print_total, (void*)j);
    
  }

  for(int i = 1; i < NUM_OF_THREADS; i++)
  {
    pthread_join(threads[i], NULL);
  }

  printf("Total: %d\n", TOTAL);
}
