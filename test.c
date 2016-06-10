#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void *print_message_function(void *ptr);


int main()
{
    pthread_t thread1, thread2;
    const char* message1 = "Thread1";
    const char* message2 = "Thread2";
    int iret1, iret2;

    // create independent threads each of which will execute function

    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*)message1);
    if (iret1)
    {
        fprintf(stderr, "Error pthread_create() return code: %d\n", iret1);
        exit(EXIT_FAILURE);
    }

    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*)message2);
    if (iret2)
    {
        fprintf(stderr, "Error pthread_create() return code: %d\n", iret2);
        exit(EXIT_FAILURE);
    }

    printf("pthread_create() for thread1 returns: %d\n", iret1);
    printf("pthread_create() for thread1 returns: %d\n", iret2);

    // wait till threads are complete before main continues. Unless we
    // wait we run the risk of exiting which will terminate process and threads

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(EXIT_SUCCESS);
}

void *print_message_function(void *ptr)
{
    char* message;
    message = (char*)ptr;
    sleep(1);
    printf("%s\n", message);
    return message;
}