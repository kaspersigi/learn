OUTPUT_FORMAT("binary", "binary", "binary")
OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
    . = 0;
    .data.head ALIGN(0x10) : {*(.text.head)}
    .text ALIGN(0x10) : {*(.text)}
    .data ALIGN(0x10) : {*(.data)}
    .data.stack ALIGN(0x10) : {*(.data.stack)}
    .data.tail ALIGN(0x10) : {*(.data.tail)}
}