#include <KD/kd.h>
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4668 )
#pragma warning( disable: 4820 )
#pragma warning( disable: 4255 )
#pragma warning( disable: 4820 )
#endif /* _MSC_VER */
#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#ifdef _MSC_VER
#pragma warning( pop )
#pragma warning( disable: 4710 )
#endif /* _MSC_VER */
#define UNUSED(x) (void)(x)

static char *get_utf8 (LPCWSTR string)
{
    char *UTF8String = NULL;
    int UTF8StringLength = WideCharToMultiByte (CP_UTF8, WC_ERR_INVALID_CHARS,
                           string, -1, UTF8String, 0, NULL, NULL);
    UTF8String = (char *) kdMalloc (sizeof (char) * UTF8StringLength);
    WideCharToMultiByte (CP_UTF8, WC_ERR_INVALID_CHARS, string, -1, UTF8String,
                         UTF8StringLength, NULL, NULL);
    return UTF8String;
}

#if defined(KD_WINDOW_SUPPORTED)
int CALLBACK WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine, int nCmdShow)
{
    int argc = __argc;
    wchar_t **wargv = __wargv;
    UNUSED (hInstance);
    UNUSED (hPrevInstance);
    UNUSED (lpCmdLine);
    UNUSED (nCmdShow);
#else
int wmain (int argc, wchar_t *wargv[ ], wchar_t *envp[])
{
#endif
    int result = 0;
    char **argvu8 = (char **) kdMalloc (sizeof (char *) * argc);
    for (int i = 0; i < argc; i++) {
        argvu8[i] = get_utf8 (wargv[i]);
    }
    result = kdMain (argc, (const KDchar * const *)argvu8);
    for (int i = 0; i < argc; i++) {
        kdFree (argvu8[i]);
    }
    kdFree (argvu8);
    return result;
}
