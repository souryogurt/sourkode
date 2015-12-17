#include <KD/kd.h>
#include <KD/KHR_thread_storage.h>
#include "sk_thread_data.h"

struct KDThreadAttr {
    KDint detachstate;
    KDsize stacksize;
};

struct KDThread {
    KDint data;
};

struct KDThreadMutex {
    KDint locked;
};

struct KDThreadCond {
    KDint data;
};

struct KDThreadSem {
    KDuint value;
};

static KDThread main_thread;

#define UNUSED(x) (void)(x)

KD_API KDThreadAttr *KD_APIENTRY kdThreadAttrCreate (void)
{
    KDThreadAttr *result = (KDThreadAttr *) kdMalloc (sizeof (KDThreadAttr));
    if (result) {
        result->detachstate = KD_THREAD_CREATE_JOINABLE;
        result->stacksize = 0;
        return result;
    }
    kdSetError (KD_ENOMEM);
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdThreadAttrFree (KDThreadAttr *attr)
{
    kdFree (attr);
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadAttrSetDetachState (KDThreadAttr *attr,
        KDint detachstate)
{
    switch (detachstate) {
        case KD_THREAD_CREATE_JOINABLE:
        case KD_THREAD_CREATE_DETACHED:
            attr->detachstate = detachstate;
            break;
        default:
            kdSetError (KD_EINVAL);
            return -1;
    }
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadAttrSetStackSize (KDThreadAttr *attr,
        KDsize stacksize)
{
    attr->stacksize = stacksize;
    return 0;
}

KD_API KDThread *KD_APIENTRY kdThreadCreate (const KDThreadAttr *attr,
        void * (*start_routine) (void *), void *arg)
{
    UNUSED (attr);
    UNUSED (start_routine);
    UNUSED (arg);
    kdSetError (KD_ENOSYS);
    return KD_NULL;
}

KD_API KD_NORETURN void KD_APIENTRY kdThreadExit (void *retval)
{
    UNUSED (retval);
    kdExit (0);
}

KD_API KDint KD_APIENTRY kdThreadJoin (KDThread *thread, void **retval)
{
    UNUSED (thread);
    UNUSED (retval);
    kdSetError (KD_EDEADLK);
    return -1;
}

KD_API KDint KD_APIENTRY kdThreadDetach (KDThread *thread)
{
    UNUSED (thread);
    kdSetError (KD_EINVAL);
    return -1;
}

KD_API KDThread *KD_APIENTRY kdThreadSelf (void)
{
    return &main_thread;
}

#ifndef KD_NO_STATIC_DATA
KD_API KDint KD_APIENTRY kdThreadOnce (KDThreadOnce *once_control,
                                       void (*init_routine) (void))
{
    /* TODO: lock once_control */
    if (!once_control->impl) {
        once_control->impl = (void *)1;
        init_routine();
    }
    /* TODO: unlock once_control */
    return 0;
}
#endif /* ndef KD_NO_STATIC_DATA */

KD_API KDThreadMutex *KD_APIENTRY kdThreadMutexCreate (const void *mutexattr)
{
    KDThreadMutex *result = (KDThreadMutex *) kdMalloc (sizeof (KDThreadMutex));
    UNUSED (mutexattr);
    if (result) {
        result->locked = 0;
        return result;
    }
    kdSetError (KD_ENOMEM);
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdThreadMutexFree (KDThreadMutex *mutex)
{
    kdFree (mutex);
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadMutexLock (KDThreadMutex *mutex)
{
    if (mutex->locked) {
        /* TODO: show message "DEADLOCK" and die? */
    }
    mutex->locked = 1;
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadMutexUnlock (KDThreadMutex *mutex)
{
    mutex->locked = 0;
    return 0;
}

KD_API KDThreadCond *KD_APIENTRY kdThreadCondCreate (const void *attr)
{
    UNUSED (attr);
    kdSetError (KD_ENOSYS);
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdThreadCondFree (KDThreadCond *cond)
{
    UNUSED (cond);
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadCondSignal (KDThreadCond *cond)
{
    UNUSED (cond);
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadCondBroadcast (KDThreadCond *cond)
{
    UNUSED (cond);
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadCondWait (KDThreadCond *cond,
        KDThreadMutex *mutex)
{
    UNUSED (cond);
    UNUSED (mutex);
    return 0;
}

KD_API KDThreadSem *KD_APIENTRY kdThreadSemCreate (KDuint value)
{
    KDThreadSem *result = (KDThreadSem *) kdMalloc (sizeof (KDThreadSem));
    if (result) {
        result->value = value;
        return result;
    }
    kdSetError (KD_ENOSPC);
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdThreadSemFree (KDThreadSem *sem)
{
    kdFree (sem);
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadSemWait (KDThreadSem *sem)
{
    if (sem->value == 0) {
        /* TODO: show message "DEADLOCK" and die? */
    }
    sem->value -= 1;
    return 0;
}

KD_API KDint KD_APIENTRY kdThreadSemPost (KDThreadSem *sem)
{
    sem->value += 1;
    return 0;
}

KD_API void KD_APIENTRY skInitThreadData (KDThread *thread)
{
    KDThreadStorageKeyKHR current_key = kdMapThreadStorageKHR (SKCurrentThread);
    SKThreadData *data = (SKThreadData *) kdMalloc (sizeof (SKThreadData));
    data->error = 0;
    if (!thread) {
        /* It's main thread */
        kdSetThreadStorageKHR ( kdMapThreadStorageKHR (SKMainThread), data);
        thread = (KDThread *) kdMalloc (sizeof (KDThread));
        /* TODO: set internal implementation defined handles */
    }
    data->thread = thread;
    kdSetThreadStorageKHR (current_key, data);
}
