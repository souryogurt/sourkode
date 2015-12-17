#include <KD/KHR_thread_storage.h>

#ifndef KHR_THREAD_STORAGE_SIZE
#define KHR_THREAD_STORAGE_SIZE 1024
#endif

typedef struct TLSItem {
    const void *id;
    void *data;
} TLSItem;

static TLSItem thread_storage_items[KHR_THREAD_STORAGE_SIZE] = {KD_NULL};

KD_API KDThreadStorageKeyKHR KD_APIENTRY kdMapThreadStorageKHR (const void *id)
{
    KDThreadStorageKeyKHR key;
    for (key = 1; key < KHR_THREAD_STORAGE_SIZE; key++) {
        if (thread_storage_items[key].id == id) {
            return key;
        } else if (thread_storage_items[key].id == KD_NULL) {
            thread_storage_items[key].id = id;
            return key;
        }
    }
    kdSetError (KD_ENOMEM);
    return 0;
}

KD_API KDint KD_APIENTRY kdSetThreadStorageKHR (KDThreadStorageKeyKHR key,
        void  *data)
{
    thread_storage_items[key].data = data;
    return 0;
}

KD_API void *KD_APIENTRY kdGetThreadStorageKHR (KDThreadStorageKeyKHR key)
{
    return thread_storage_items[key].data;
}
