#ifndef PTHREADOBJECT_H
#define PTHREADOBJECT_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

class pthreadObject
{
public:
    pthreadObject();
    virtual ~pthreadObject();
    //启动该线程
    void start();
    //阻塞，等待这个线程工作完成
    void join();
    //对这个线程发出停止信号，线程在时机合适时停止运行
    void cancel();
    static void* run(void *threadarg);

protected:

private:
    bool isRuning()
    {
        return isRun;
    }

    static void release(void* threadarg)
    {
        pthreadObject* ptr = (pthreadObject*)threadarg;
        ptr->realRelease();
    }
    void realRelease()
    {
        printf("thread is releasing!\n");
    }
    pthread_t thread;
    bool isRun;
};

#endif // PTHREADOBJECT_H
