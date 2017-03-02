/*
 * Vystupni operand ma byt v registru ECX
 */
#include <stdio.h>

unsigned long long result;

int main()
{
    __asm__ __volatile__(
        "mov    $42, %%rbx;   \n\t"
        "mov    %%rbx, %0;    \n\t"
        : "=c" (result)  /* vystupni operand */
        :                /* zadne vstupni operandy */
        : "%rbx"         /* registry pouzivane uvnitr kodu */
    );

    printf("%Ld\n", result);

    return 0;
}

