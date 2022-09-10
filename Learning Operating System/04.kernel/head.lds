OUTPUT_FORMAT("binary", "binary", "binary")
OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
    . = 0;
    .data ALIGN(0x10) : {*(.head) *(.data) *(.stack)}
    .text ALIGN(0x10) : {*(.text)}
}