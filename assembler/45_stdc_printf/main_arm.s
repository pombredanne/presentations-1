# asmsyntax=as

# Program pro otestovani volani funkci ze standardni knihovny jazyka C
# - volani funkce 'printf'
# - varianta urcena pro klasickou 32bitovou architekturu ARM
#
# Autor: Pavel Tisnovsky



#-----------------------------------------------------------------------------
.section .data
hello_world_message:
        .asciz "Hello world!\n"         @ zprava, ktera se ma vytisknout na standardni vystup



#-----------------------------------------------------------------------------
.section .text
        .global main                    @ tento symbol ma byt dostupny i linkeru

main:
        stmfd sp!, {lr}                 @ ulozeni zvolenych registru na zasobnik

        ldr   r0, =hello_world_message  @ adresa zpravy, ktera se ma vytisknout
                                        @ (jde o jediny parametr predany funkci printf())

        bl    printf                    @ zavolani knihovni funkce printf()

        mov   r0, #42                   @ navratova hodnota (exit status)
        ldmfd sp!, {pc}                 @ obnova registru, ukonceni aplikace
                                        @ (rizeni se vrati na adresu ulozenou v LR)

