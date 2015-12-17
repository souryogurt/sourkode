#include <KD/kd.h>
#include <stdlib.h>

KD_API void *KD_APIENTRY kdMalloc (KDsize size)
{
    return malloc (size);
}

KD_API void KD_APIENTRY kdFree (void *ptr)
{
    free (ptr);
}

KD_API void *KD_APIENTRY kdRealloc (void *ptr, KDsize size)
{
    return realloc (ptr, size);
}
