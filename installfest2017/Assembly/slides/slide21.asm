# asmsyntax=as

# GNU AS pro architekturu AArch64.

# Linux kernel system call table
sys_exit=93

#-----------------------------------------------------------------------------
.section .data

#-----------------------------------------------------------------------------
.section .bss

#-----------------------------------------------------------------------------
.section .text
        .global _start          // tento symbol ma byt dostupny i z linkeru

_start:
        mov  x8, #sys_exit      // cislo sycallu pro funkci "exit"
        mov  x0, #0             // exit code = 0
        svc  0                  // volani Linuxoveho kernelu

