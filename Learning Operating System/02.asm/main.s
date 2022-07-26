.section .text
.align 4
.global _start
_start:
.code16
    movw $0xb800, %ax
    movw %ax, %ds
    movb $'a', %ds:(0x00)
    movb $0x07, %ds:(0x01)
    movb $'s', %ds:(0x02)
    movb $0x07, %ds:(0x03)
    movb $'m', %ds:(0x04)
    movb $0x07, %ds:(0x05)

    # 写2000个空格
    movw $0x06, %bx
    movw $2000, %cx
    .cls:
    movw $0x0720, %ds:(%bx)
    addw $2, %bx
    loop .cls

    hlt

.org 510
boot_flag: .word 0xAA55
