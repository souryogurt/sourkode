#include <KD/kd.h>
#include "sk_thread_data.h"
#include <stdlib.h>

int main (int argc, char *argv[])
{
    skInitThreadData (KD_NULL);
    return kdMain (argc, (const KDchar * const *)argv);
}

KD_API KD_NORETURN void KD_APIENTRY kdExit (KDint status)
{
    exit (status);
}
