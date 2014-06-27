/**
 * mutex - simple mutex example
 * Original Author: alex Sayle <alexs@cse>
 * Modified:  Leclerc
 *
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// The number of thread that will be started
#define THREAD_COUNT 2 
// sleeping factor 
#define N 5


/*
 * argument given to the thread
 *
 */
struct thread_args {
  int ident ;                 // theads identity

  pthread_mutex_t *resA ;
  pthread_mutex_t *resB ;
  // add argument that you want to pass to threads
};

// type def for those who don't like writing struct all the time 
typedef struct thread_args  thread_args_t ;


// forward declaration of functions
void run_thread_one(thread_args_t *);
void run_thread_two(thread_args_t *);

/*
 *  Main code
 */
int main(int argc, char** argv)
{

  pthread_t        thread_one;
  pthread_t        thread_two;
       
  thread_args_t    args_one,args_two;     // thread arguments


  void *statusp  ;                         

   
  pthread_mutex_t resA_lock = PTHREAD_MUTEX_INITIALIZER ;
  pthread_mutex_t resB_lock = PTHREAD_MUTEX_INITIALIZER ;
    

  printf("deadlock program starting. \n");

  /* Set evil seed (initial seed) */
  srand( (unsigned)time( NULL ) );


  /*
   * start up threads
   */
  
  /* Set up argument for Thread one */
  args_one.ident = 1  ;
  args_one.resA = &resA_lock;
  args_one.resB = &resB_lock;
  
  // set any other argument you want to pass to the 
  // newly created thread


  pthread_create(&thread_one,
		 NULL,
		 (void *) run_thread_one,
		 (void *) &args_one) ;


  /* Set up argument for Thread two */
  args_two.ident = 2  ;
  args_two.resA = &resA_lock;
  args_two.resB = &resB_lock;
   
  // set any other argument you want to pass to the 
  // newly created thread


  pthread_create(&thread_two,
		 NULL,
		 (void *) run_thread_two,
		 (void *) &args_two) ;  



  /*
   * wait for 60 sec, if the threads aren't done in 60 seconds, then 
   * it must be a dead lock.
   */
  sleep(60);


  /*
   * cleaning up after threads
   */
  
#if 0
  /* just in case the thread returns, make sure we handle it */
  pthread_join(thread_one,&statusp);
  if( (int *) *statusp == (int *) PTHREAD_CANCELED ){
    printf("thread %d was canceld\n",args_one.ident);
  }else{
    printf("thread %d completed. it's return value isf %d\n",
	   args_one.ident,*(int *)statusp);
  }
    
  /* handle thrad two returning */
  pthread_join(thread_two,&statusp);
  if(PTHREAD_CANCELED == *statusp ){
    printf("thread %d was canceld\n",args_two.ident);
  }else{
    printf("thread %d completed. it's return value isf %d\n",
	   args_two.ident,*(int *)statusp);
  }
    
#endif 	


  /* and we're done */
  return(0);

} 


/**
 * this function is started as a new thread.
 *
 */
void run_thread_one(thread_args_t *args){
 
  /* say hello to the world. */
  printf("Hello world, I'm thread %d\n",args->ident);

  printf("thread %d about to get resource B \n",args->ident);

  pthread_mutex_lock(args->resB);
  /* mutual exclusion section */
  {

    printf("thread %d: I got resource B \n",args->ident);
    /* don't delete this */
    sleep(1);
    
    printf("thread %d about to get resource A \n",args->ident);
    pthread_mutex_lock(args->resA);
    
    printf("thread %d: I've both resouces :) \n",args->ident);
    
  }
  pthread_mutex_unlock(args->resB);
  pthread_mutex_unlock(args->resA);
  

}


void run_thread_two(thread_args_t *args){
 
  /* say hello to the world. */
  printf("Hello world, I'm thread %d\n",args->ident);

  printf("thread %d about to get resource B \n",args->ident);
  pthread_mutex_lock(args->resB);
  /* mutual exclusion section */
  {
    printf("thread %d: I got resource B \n",args->ident);
    /* don't delete this */
    sleep(1);
    
    printf("thread %d about to get resource A \n",args->ident);
    pthread_mutex_lock(args->resA);
    
    printf("thread %d: I've both resouces :) \n",args->ident);
    
  }
  pthread_mutex_unlock(args->resB);
  pthread_mutex_unlock(args->resA);
  
}
