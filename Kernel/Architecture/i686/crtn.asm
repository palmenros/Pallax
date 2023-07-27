/* Copyright (c) 2023, Pedro Palacios Almendros. */

/* GLOBAL CONSTRUCTORS */

.section .init
    /* GCC will put the contents of certend.o's .init section here. */
    popl %ebp
    ret

/* GLOBAL DESTRUCTORS */

.section .fini
    /* GCC will put the contents of certend.o's .fini section here. */
    popl %ebp
    ret
