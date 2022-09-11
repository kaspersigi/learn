OUTPUT_FORMAT("binary", "binary", "binary")
OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
    . = 0;
    .text ALIGN(0x10) : {*(.text)}
}