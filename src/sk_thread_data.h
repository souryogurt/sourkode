#ifndef SK_THREAD_DATA_H
#define SK_THREAD_DATA_H
#include <KD/kd.h>
#define SKCurrentThread "SKCurrentThreadDataID"
#define SKMainThread "SKMainThreadDataID"
typedef struct SKThreadData {
    KDint error;
    KDThread *thread;
} SKThreadData;

#ifdef __cplusplus
extern "C" {
#endif

KD_API void KD_APIENTRY skInitThreadData (KDThread *thread);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: SK_THREAD_DATA_H */
