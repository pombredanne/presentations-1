# asmsyntax=as

# Aplikace pro precteni dat ze standardniho vstupu
# naprogramovana v assembleru GNU as - priklad pro AArch64
#
# Autor: Pavel Tisnovsky



# Linux kernel system call table
sys_exit   = 93
sys_read   = 63
sys_write  = 64


# List of syscalls for AArch64:
# https://github.com/torvalds/linux/blob/master/include/uapi/asm-generic/unistd.h



# Dalsi konstanty pouzite v programu - standardni streamy
std_input  = 0
std_output = 1



#-----------------------------------------------------------------------------
.section .data

message1:
        .ascii "Enter your name: "         // string, ktery NENI ukoncen nulou
        message1len = . - message1         // delka prvni zpravy

message2:
        .ascii "Hello "                    // string, ktery NENI ukoncen nulou
        message2len = . - message2         // delka druhe zpravy



#-----------------------------------------------------------------------------
.section .bss
        .lcomm input,  50                  // rezervace 50 bajtu pro vstup



#-----------------------------------------------------------------------------
.section .text
        .global _start                     // tento symbol ma byt dostupny i z linkeru

_start:
        // tisk prvni zpravy (vyzvy)
        mov   x8, #sys_write               // cislo syscallu pro funkci "write"
        mov   x0, #std_output              // standardni vystup
        ldr   x1, =message1                // adresa retezce, ktery se ma vytisknout
        mov   x2, #message1len             // pocet znaku, ktere se maji vytisknout
        svc   0                            // volani Linuxoveho kernelu

        // precteni vstupu od uzivatele
        mov   x8, #sys_read                // cislo syscallu pro funkci "read"
        mov   x0, #std_input               // standardni vstup
        ldr   x1, =input                   // adresa bufferu
        mov   x2, #50                      // maximalni delka zpravy
        svc   0                            // volani Linuxoveho kernelu

        // tisk druhe zpravy (zacatek odpovedi)
        mov   x8, #sys_write               // cislo syscallu pro funkci "write"
        mov   x0, #std_output              // standardni vystup
        ldr   x1, =message2                // adresa retezce, ktery se ma vytisknout
        mov   x2, #message2len             // pocet znaku, ktere se maji vytisknout
        svc   0                            // volani Linuxoveho kernelu

        // tisk vstupu od uzivatele
        mov   x8, #sys_write               // cislo syscallu pro funkci "write"
        mov   x0, #std_output              // standardni vystup
        ldr   x1, =input                   // adresa bufferu
        mov   x2, #50                      // delka (max delka)
        svc   0                            // volani Linuxoveho kernelu

        mov   x8, #sys_exit                // cislo sycallu pro funkci "exit"
        mov   x0, #0                       // exit code = 0
        svc   0                            // volani Linuxoveho kernelu

