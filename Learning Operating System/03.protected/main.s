.section .text
.align 4
.global _start
_start:
.code16
    start:
    # 初始化堆栈段及堆栈段指针
    movw $0x07e0, %ax
    movw %ax, %ss
    movw $0x0200, %sp

    # 计算GDT所在的逻辑段地址
    movw %cs:(gdt_base), %ax # 低16位
    movw %cs:(gdt_base+0x02), %dx # 高16位

    movw $16, %bx
    divw %bx
    movw %ax, %ds # 令DS指向该段以进行操作
    movw %dx, %bx # 段内起始偏移地址

    # 创建0#描述符，它是空描述符，这是处理器的要求
    movl $0x00, 0x00(%bx)
    movl $0x00, 0x04(%bx)

    # 创建#1描述符，保护模式下的数据段描述符（文本模式下的显示缓冲区）
    movl $0x80007fff, 0x08(%bx) # 32k
    movl $0x0040920b, 0x0c(%bx)

    # 创建#2描述符，保护模式下的代码段描述符
    movl $0x7c0003ff, 0x10(%bx) # 1k,MBR
    movl $0x00409800, 0x14(%bx)

    # 初始化描述符表寄存器GDTR
    movw $23, %cs:(gdt_size)
    lgdt %cs:(gdt_size) # 描述符表的界限（总字节数减一）

    inb $0x92, %al # 南桥芯片内的端口
    orb $0B00000010, %al # 打开A20
    outb %al, $0x92 # 打开A20

    # 保护模式下中断机制尚未建立，应禁止中断
    cli

    # 设置PE位
    movl %cr0, %eax
    orl $1, %eax
    movl %eax, %cr0

    # 代码段选择子 00000000000_10_000B
    ljmp $0B0000000000010000, $(print-start) # 加载代码段选择子(索引0x02)
.code32
    print:
    movw $0B0000000000001000, %cx # 加载数据段选择子(索引0x01)
    movw %cx, %ds

    # 以下在屏幕上显示"Protect mode OK."
    movw $(buffer_end-buffer), %cx
    movw $(buffer-start), %bx

    # 保护模式下无法调用bios中断
    # .putc:
    # movb $0x0e, %ah
    # movb %cs:(%bx), %al
    # int $0x10
    # inc %bx
    # loop .putc

    hlt
buffer:
    .asciz "protected mode OK!"
buffer_end:
gdt_size:
    .word 0x0000
gdt_base:
    .word 0x8000
.org 510
boot_flag: .word 0xAA55
