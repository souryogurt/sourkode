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


int CALLBACK WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine, int nCmdShow)
{
    return kdMain (__argc, (const KDchar * const *)__argv);
}
