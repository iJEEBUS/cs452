#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#define TRUE 1
#define FALSE 0

using namespace std;

void *retrieve_file(void *arg);

int serving = TRUE;

int main()
{
  pthread_t thread;
  void *thread_result;
  int status;

  string file;

  // infinite loop that will exit when ^C is passed.
  while(serving)
  {
    cout << "filename to access: ";
    getline(cin, file);
    
    // create and start the thread to search for the filename
    // entered by the user
    if ((status = pthread_create(&thread, NULL, retrieve_file, &file)) != 0) 
    {
      fprintf(stderr, "thread creation error %d: %s\n", status, strerror(status));
      exit(1);
    }

    // wait for the thread to terminate and then
    // get its return value
    if ((status = pthread_join(thread, &thread_result)) != 0)
    {
      fprintf(stderr, "join error %d: %s\n", status, strerror(status));
      exit(1);
    }
  }

  return 0;
}

void *retrieve_file(void *arg)
{
  string *filename = (string *)arg;

  // there is an 80% chance to sleep for 1 second,
  // 20% chance to sleep for 7-10 seconds
  int time_key = (rand() % 10) + 1;
  if (time_key <= 8)
  {
    sleep(1);
  } else {
    int time_to_sleep = (rand() % 3) + 7;	    
    sleep(time_to_sleep);
  } 
  cout << "File accessed: " << *filename << endl;
  return NULL;
}

