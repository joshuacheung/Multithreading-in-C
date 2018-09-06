//increment.c
//

# include <getopt.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

void* threadFunc(void *myArgs);
void someWork();

int sum = 0;
pthread_mutex_t mutex;

struct threadArgs
{
  int data;
};

void* threadFunc(void *myArgs)
{

  struct threadArgs *args = (struct threadArgs*)myArgs;
  int data = args->data;
  data = 1000;
  for(int i = 0; i < data; i++) //calling somework 1000 times 
  {
    someWork();
  }
  return 0;
}

void someWork()
{
  pthread_mutex_lock(&mutex);

    sum++; //increment sum

  pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{
  int option;
  struct threadArgs numThreads;
  while ((option = getopt(argc, argv, "n:")) != -1) //user input -n flag
  {
    switch(option)
    {
      case 'n':
      {
        numThreads.data = atoll(argv[2]); //converting data types
      }
    }
  }

  // Init Mutex
  pthread_mutex_init(&mutex, NULL);

  // Set Arguments and creates numThreads amount of threads
  pthread_t *thisThread = malloc(numThreads.data *sizeof(pthread_t));

  for(int i = 0; i < numThreads.data; i++) //executes user input amount of times
  {
    pthread_create(&thisThread[i], NULL, threadFunc, &numThreads);
  }

  // Wait for thread to finish executing
  for(int i = 0; i < numThreads.data; i++)
  {
    pthread_join(thisThread[i], NULL);
  }
  // Destry Mutex
  printf("%d\n", sum);
  pthread_mutex_destroy(&mutex);

}
