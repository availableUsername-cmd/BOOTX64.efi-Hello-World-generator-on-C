ENTRY(EfiMain)

SECTIONS
{
    . = 0;

    .text :
    {
        *(.text)
    }

    .data :
    {
        *(.data)
    }

    .reloc :
    {
        *(.reloc)
    }
}