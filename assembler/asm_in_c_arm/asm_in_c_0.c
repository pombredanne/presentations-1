#include <stdio.h>

int main()
{
    __asm__ __volatile__(
        "nop   \n\t"
        " nop   \n\t"
        "  nop   \n\t"
        "    nop   \n\t"
        "    nop  @ komentar \n\t"
        : /* zadne vystupni registry */
        : /* zadne vstupni operandy */
        : /* zadne registry pouzivane uvnitr kodu */
    );

    return 0;
}

