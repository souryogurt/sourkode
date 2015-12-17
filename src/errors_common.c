#include <KD/kd.h>
#include <KD/KHR_thread_storage.h>
#include "sk_thread_data.h"

KD_API KDint KD_APIENTRY kdGetError (void)
{
    KDThreadStorageKeyKHR key = kdMapThreadStorageKHR (SKCurrentThread);
    SKThreadData *data = (SKThreadData *) kdGetThreadStorageKHR (key);
    return data->error;
}

KD_API void KD_APIENTRY kdSetError (KDint error)
{
    KDThreadStorageKeyKHR key = kdMapThreadStorageKHR (SKCurrentThread);
    SKThreadData *data = (SKThreadData *) kdGetThreadStorageKHR (key);
    data->error = error;
}
