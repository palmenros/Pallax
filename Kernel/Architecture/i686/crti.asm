/* Copyright (c) 2023, Pedro Palacios Almendros. */

/* GLOBAL CONSTRUCTORS */

.section .init

/* Export the global _init function to be called for calling global constructors */
.global _init
.type _init, @function

_init:
    push %ebp
    movl %esp, %ebp
    /* GCC will put the contents of crtbegin.o's .init section here */


/* GLOBAL DESTRUCTORS */

.section .fini

/* Export the global _fini function to be called for calling global destructors */
.global _fini
.type _fini, @function
_fini:
    push %ebp
    movl %esp, %ebp
    /* GCC will put the contents of crtbegin.o's .fini section here */
