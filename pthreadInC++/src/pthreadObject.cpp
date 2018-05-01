#include "pthreadObject.h"
#include <unistd.h>
pthreadObject::pthreadObject()
{
    //ctor
    isRun = true;
}

pthreadObject::~pthreadObject()
{
    //dtor
}

void pthreadObject::start()
{
    pthread_create(&thread,NULL,run,(void *)this);
}

void pthreadObject::cancel()
{
    isRun = false;
    pthread_cancel(thread);
}

void pthreadObject::join()
{
    void *status;
    int rc = pthread_join(thread, &status);
    if (rc)
    {
        printf("ERROR; return code from pthread_join() is %d\n", rc);
        exit(-1);
    }
    printf("Main: completed join with thread %ld having a status of %ld\n",thread,(long)status);
}

void* pthreadObject::run(void *threadarg)
{
    pthreadObject* ptr = (pthreadObject*)threadarg;
    while(1)
    {
        pthread_cleanup_push(release, threadarg);
        sleep(1);
        printf("thread %ld is running!\n",pthread_self());
        pthread_cleanup_pop(0);
        pthread_testcancel();
    }

    return NULL;
}
