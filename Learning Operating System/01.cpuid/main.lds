OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
    . = 0x08048000;
    .text ALIGN(0x1000): {*(.text)}
    .data ALIGN(0x1000): {*(.data)}
}