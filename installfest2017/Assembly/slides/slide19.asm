; asmsyntax=nasm

; varianta pro i386, syntaxe Intel (i NASM)

; Linux kernel system call table
sys_exit equ 1

;-----------------------------------------------------------------------------
section .data

;-----------------------------------------------------------------------------
section .bss

;-----------------------------------------------------------------------------
section .text
        global _start           ; tento symbol ma byt dostupny i linkeru

_start:
        mov   eax,sys_exit      ; cislo sycallu pro funkci "exit"
        mov   ebx,0             ; exit code = 0
        int   80h               ; volani Linuxoveho kernelu

