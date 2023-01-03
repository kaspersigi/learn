.equ SDA_PHY_ADDR, 0x00007e00 # 系统数据区的起始物理地址
.equ PDT_PHY_ADDR, 0x00009000 # 对应于页目录表物理地址
.equ PT_PHY_ADDR, 0x0000a000 # 对应于低端4MB的内核页表的物理地址
.equ IDT_PHY_ADDR, 0x0000b000 # 中断描述符表的物理地址
.equ LDR_PHY_ADDR, 0x0000c000 # 用于安装内核加载器的起始物理地址
.equ GDT_PHY_ADDR, 0x00010000 # 全局描述符表GDT的物理地址
.equ CORE_PHY_ADDR, 0x00020000 # 内核的起始物理地址
.equ COR_PDPT_ADDR, 0x00100000 # 从这个物理地址开始的1MB是内核的254个页目录指针表

.section .text
.align 4
.global _start
_start:
.code16
    # 保护模式下中断机制尚未建立，应禁止中断
    cli

    # 初始化堆栈段及堆栈段指针
    movw $0x07e0, %ax
    movw %ax, %ss
    movw $0x0200, %sp
    xorw %ax, %ax
    movw %ax, %ds

    # 计算GDT所在的逻辑段地址
    movw (.gdt_base), %ax # 低16位
    movw (.gdt_base+0x02), %dx # 高16位

    movw $16, %bx
    divw %bx
    pushw %ds
    movw %ax, %ds # 令DS指向该段以进行操作
    movw %dx, %bx # 段内起始偏移地址

    # 创建#0描述符，它是空描述符，这是处理器的要求
    movl $0x00, 0x00(%bx)
    movl $0x00, 0x04(%bx)

    # 创建#1描述符，保护模式下的代码段描述符
    movl $0x0000ffff, 0x08(%bx) # 4G
    movl $0x00cf9800, 0x0c(%bx)

    # 创建#2描述符，保护模式下的数据段描述符
    movl $0x0000ffff, 0x10(%bx) # 4G
    movl $0x00cf9200, 0x14(%bx)

    # 创建#3描述符，保护模式下的堆栈段描述符
    movl $0x80000fff, 0x18(%bx) # 4k
    movl $0x00409200, 0x1c(%bx)

    popw %ds

    # 初始化描述符表寄存器GDTR
    movw $31, (.gdt_size)
    lgdt (.gdt_size) # 描述符表的界限（总字节数减一）

    # 设置PE位
    movl %cr0, %eax
    orl $1, %eax
    movl %eax, %cr0

    # 代码段选择子 00000000000_01_000B
    ljmp $0B0000000000001000, $(.protected) # 加载代码段选择子(索引0x01)
.code32
    .protected:
    movw $0B0000000000010000, %cx # 加载数据段选择子(索引0x02)
    movw %cx, %ds
    movw $0B0000000000011000, %cx # 加载堆栈段选择子(索引0x03)
    movw %cx, %ss
    movl $0x1000, %esp

    movl $0x3ff << 2, %esi

    movl $PDT_PHY_ADDR, %ebx
    movl $PT_PHY_ADDR | 0x03, %eax
    movl %eax, (%ebx)
    movl $PDT_PHY_ADDR | 0x03, %eax
    movl %eax, (%ebx, %esi)

    movl $1024, %ecx
    movl $0x00, %esi
    movl $PT_PHY_ADDR, %ebx
.set_pt:
    movl %esi, %eax
    shll $12, %eax
    orl $0x03, %eax
    movl %eax, (%ebx, %esi, 4)
    incl %esi
    loop .set_pt

    # 令CR3寄存器指向页目录表
    movl $PDT_PHY_ADDR, %eax
    movl %eax, %cr3

    # 开启分页功能
    movl %cr0, %eax
    bts $31, %eax
    movl %eax, %cr0

    movl (0x3ffffc), %eax

    hlt
.gdt_size:
    .word 0x0000
.gdt_base:
    .long GDT_PHY_ADDR
.org 510
.boot_flag: .word 0xAA55
