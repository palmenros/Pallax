/* Set the bootstrap assembly label _start as the entry point */
ENTRY(_start)

/* Define the sections of the output image */
SECTIONS
{

    /* TODO: Better document the memory map */

    /* We will load the Kernel at 1 MiB */
    . = 1M;

    /*
       The multiboot header must be within the first 8 KiB of the image, so we
       will put it first along the .text section
    */
    .text BLOCK(4K) : ALIGN(4K) /* Align the block to a page boundary */
    {
        *(.multiboot)
        *(.text)
    }

    /* Read-only data (constants) */
    .rodata BLOCK(4K) : ALIGN(4K) /* Align the block to a page boundary */
    {
        *(.rodata)
    }

    /* Read-write initialized data */
    .data BLOCK(4K) : ALIGN(4K) /* Align the block to a page boundary */
    {
        *(.data)
    }

    /* Unitialized read-write data and stack */
    .bss BLOCK(4K) : ALIGN(4K)  /* Align the block to a page boundary */
    {
		*(COMMON)
		*(.bss)
    }

    /* FIXME: Add more sections here if needed */
}