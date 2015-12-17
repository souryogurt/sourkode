#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4668 )
#pragma warning( disable: 4820 )
#pragma warning( disable: 4255 )
#pragma warning( disable: 4820 )
#endif /* _MSC_VER */
#include <KD/kd.h>
#include <windows.h>
#ifdef _MSC_VER
#pragma warning( pop )
#pragma warning( disable: 4710 )
#endif /* _MSC_VER */

#ifdef  _UNICODE
/** Convert UTF16 string to UTF8 string
 * @param utf16_string UTF16 string terminated by 0
 * @returns new UTF8 string, KD_NULL otherwise
 */
static KDchar *get_utf8 (const wchar_t *const utf16_string)
{
    KDchar *result = KD_NULL;
    if (utf16_string) {
        int result_length = WideCharToMultiByte (CP_UTF8, WC_ERR_INVALID_CHARS,
                            (LPCWCH)utf16_string, -1, result, 0, 0, 0);
        result = (KDchar *) kdMalloc (sizeof (KDchar) * result_length);
        if (result) {
            WideCharToMultiByte (CP_UTF8, WC_ERR_INVALID_CHARS, (LPCWCH)utf16_string, -1,
                                 result,
                                 result_length, 0, 0);
        }
    }
    return result;
}

/** Convert array of UTF16 strings to array of UTF8 strings
 * @param strings Array of UTF16 strings
 * @param count Number of elements of array
 * @returns new array of UTF8 strings, KD_NULL otherwise
 */
static KDchar **get_utf8_array (const wchar_t *const *const strings, int count)
{
    KDchar **result = KD_NULL;
    if (strings && (count > 0)) {
        result = (KDchar **) kdMalloc (sizeof (KDchar *) * count);
        if (result) {
            int i = 0;
            while (i < count) {
                result[i] = get_utf8 (strings[i]);
                if (result[i] == KD_NULL) {
                    kdFree (result);
                    return KD_NULL;
                }
                i++;
            }
        }
    }
    return result;
}

/** Frees array of strings
 * @param strings Array of strings
 * @param count Number of elements of array
 */
static void free_utf8_array (KDchar **strings, int count)
{
    if (strings) {
        int i = 0;
        while (i < count) {
            kdFree (strings[i]);
            i++;
        }
        kdFree (strings);
    }
}
#endif

int main (int argc, char *argt[])
{
    int result = 1;
    KDchar **argv = KD_NULL;
#ifdef  _UNICODE
    argv = get_utf8_array ((wchar_t **)argt, argc);
#else
    argv = (KDChar **) argt;
#endif
    if (argv) {
        result = kdMain (argc, argv);
    }
#ifdef  _UNICODE
    free_utf8_array (argv, argc);
#endif
    return result;
}
