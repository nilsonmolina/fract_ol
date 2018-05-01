# 42 Project: `fract_ol`

## Objective
*Now that you took over your first graphical library: the miniLibX, it’s time for you to light all the pixels of your screen at the same time! This new project will be the opporunity for you to hone your miniLibX skills, to make you discover/use the mathematical notion of complex numbers and to take a peek at the concept of optimization in computer graphics.*

## Multi-Threading in C using `pthreads`
Fract_ol will require a lot of computational processing, so it would be very useful to utilize multiple threads to improve overall performance. `Pthreads` are a simple and effective way of creating a multi-threaded application.  Multi-threaded applications allow two or more tasks to be executed concurrently (ie: at the same time). Below are 4 steps to creating a basic multi-threaded program:

1. **Define thread reference variables**  
The variable type `pthread_t` is a means of referencing threads. There needs to be a pthread_t variable in existence for every thread being created. Something like `pthread_t thread0;` will do the trick.
1. **Create an entry point for the thread**  
When creating a thread using pthreads, you need to point it to a function for it to start execution. The function must return void * and take a single void * argument. For example, if you want the function to take an integer argument, you will need to pass the address of the integer and dereference it later. This may sound complicated but, as is shown below, it’s pretty simple. An example function signature would be `void *my_entry_function(void *param);`
1. **Create the thread**  
Once the pthread_t variable has been defined and the entry point function created, we can create the thread using `pthread_create`. This method takes four arguments: a pointer to the pthread_t variable, any extra attributes (don’t worry about this for now – just set it to NULL), a pointer to the function to call (ie: the name of the entry point) and the pointer being passed as the argument to the function. Now there’s a lot of pointers in that call, but don’t stress – it’s not as tricky as it sounds. This call will look something like `pthread_create(&thread0, NULL, my_entry_function, &parameter);`

1. **Join everything back up**  
When the newly-created thread has finished doing it’s bits, we need to join everything back up. This is done by the `pthread_join` function which takes two parameters: the pthread_t variable used when pthread_create was called (not a pointer this time) and a pointer to the return value pointer (don’t worry about this for now – just set it to NULL). This call will look something like `pthread_join(thread0, NULL)`;

**_Note:_** *When compiling the program, you will also need to add `-lpthread` to the compile command.*

**Basic Example:**
```c
#include<pthread.h>
#include<stdio.h>
// a simple pthread example 
// compile with -lpthreads

// create the function to be executed as a thread
void *thread(void *ptr)
{
    int type = (int) ptr;
    fprintf(stderr,"Thread - %d\n",type);
    return  ptr;
}

int main(int argc, char **argv)
{
    // create the thread objs
    pthread_t thread1, thread2;
    int thr = 1;
    int thr2 = 2;
    // start the threads
    pthread_create(&thread1, NULL, *thread, (void *) thr);
    pthread_create(&thread2, NULL, *thread, (void *) thr2);
    // wait for threads to finish
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    return 0;
}
```

References:  
- http://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/  
- https://gist.github.com/ankurs/179778