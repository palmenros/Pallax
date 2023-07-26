/* Declare constants to be use later inside the Multiboot header */

.set MAGIC,     0x1BADB002  /* Multiboot magic constant that lets the bootloader recognize a multiboot binary */

/* Flags */
.set ALIGN,     1<<0        /* The bootloader should align loaded modules on page boundaries */
.set MEMINFO,   1<<1        /* The bootloader should provide a memory map with Main Memory information */

/* Flags that we will use */
.set FLAGS,     ALIGN | MEMINFO

/* Checksum for the full multiboot header. The full multiboot header must sum to 0 */
.set CHECKSUM, -(MAGIC + FLAGS)

/*
    MULTIBOOT HEADER
    This section will contain the Multiboot header as documented in the standard.
*/
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/*
    BOOTSTRAP STACK
    We will allocate space in the .bss section for a boostrap stack to use before processes have been created.
    This space will be reserved in the executable, and the bootloader will not write the multiboot structure
    into it.
*/
.section .bss
.align 16       /* Align the stack to 16 bytes */
stack_bottom:
    .skip 16 * 1024 * 1024      /* The stack will be 16 Kib */
stack_top:

/*
    ENTRY POINT
    We will now define the entry point that the bootloader will call after loading us into memory.
*/
.section .text
.global _start      /* Export the _start symbol which will be our entry point */

_start:
    /* Set up the stack to the reserved space */
    mov $stack_top, %esp

    /* TODO: Enable paging. */
    /* TODO: Load GDT and interrupts. */
    /* TODO: Call C++ global constructors. */
    /* TODO: Pass the multiboot structure to the kernel_main function */

    /* Call the C/C++ kernel_main function */
    call kernel_main

    /* If the kernel_main function returns (which shouldn't happen), disable interrupts
       and put the CPU into an infinite loop
    */
    cli
loop:
    hlt
    jmp loop
