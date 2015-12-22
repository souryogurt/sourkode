/* Sample KD/kdplatform.h for OpenKODE Core 1.0.3  */
#ifndef __kdplatform_h_
#define __kdplatform_h_

#define KD_API
#define KD_APIENTRY

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)
/*
 * Using <stdint.h>
 */
#include <stdint.h>
typedef int32_t                 KDint32;
typedef uint32_t                KDuint32;
typedef int64_t                 KDint64;
typedef uint64_t                KDuint64;
#elif defined(__VMS ) || defined(__sgi)
/*
 * Using <inttypes.h>
 */
#include <inttypes.h>
typedef int32_t                 KDint32;
typedef uint32_t                KDuint32;
typedef int64_t                 KDint64;
typedef uint64_t                KDuint64;
#elif defined(_WIN32) && !defined(__SCITECH_SNAP__)
/*
 * Win32
 */
typedef __int32                 KDint32;
typedef unsigned __int32        KDuint32;
typedef __int64                 KDint64;
typedef unsigned __int64        KDuint64;
#elif defined(__sun__) || defined(__digital__)
/*
 * Sun or Digital
 */
typedef int                     KDint32;
typedef unsigned int            KDuint32;
#if defined(__arch64__) || defined(_LP64)
typedef long int                KDint64;
typedef unsigned long int       KDuint64;
#else
typedef long long int           KDint64;
typedef unsigned long long int  KDuint64;
#endif /* __arch64__ */
#else
/*
 * Generic fallback
 */
#include <stdint.h>
typedef int32_t                 KDint32;
typedef uint32_t                KDuint32;
typedef int64_t                 KDint64;
typedef uint64_t                KDuint64;
#endif

/*
 * Types that are (so far) the same on all platforms
 */
typedef signed   short int KDint16;
typedef unsigned short int KDuint16;

/*
 * Types that differ between LLP64 and LP64 architectures - in LLP64,
 * pointers are 64 bits, but 'long' is still 32 bits. Win64 appears
 * to be the only LLP64 architecture in current use.
 */
#ifdef _WIN64
typedef unsigned long long int KDuintptr;
typedef unsigned long long int KDsize;
typedef signed   long long int KDssize;
#else
typedef unsigned long int KDuintptr;
typedef unsigned long int KDsize;
typedef signed   long int KDssize;
#endif

#define KDINT_MIN (-0x7fffffff-1)
#define KDINT_MAX 0x7fffffff
#define KDUINT_MAX 0xffffffffU
#define KDINT64_MIN (-0x7fffffffffffffffLL-1)
#define KDINT64_MAX 0x7fffffffffffffffLL
#define KDUINT64_MAX 0xffffffffffffffffULL
#define KDSSIZE_MIN (-0x7fffffff-1)
#define KDSSIZE_MAX 0x7fffffff
#define KDSIZE_MAX 0xffffffffU
#define KDUINTPTR_MAX 0xffffffffU
#define KD_NORETURN
#define KD_INFINITY (1.0F/0.0F)
#ifdef KD_NDEBUG
#define kdAssert(c)
#else
#define kdAssert(c) ((void)( (c) ? 0 : (kdHandleAssertion(#c, __FILE__, __LINE__), 0)))
#endif

#endif /* __kdplatform_h_ */
