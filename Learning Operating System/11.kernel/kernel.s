.equ SDA_PHY_ADDR, 0x00007e00 # 系统数据区的起始物理地址
.equ PML5_PHY_ADDR, 0x00009000 # 内核5级头表物理地址
.equ PML4_PHY_ADDR, 0x0000a000 # 内核4级头表物理地址
.equ PDPT_PHY_ADDR, 0x0000b000 # 对应于低端2MB的内核页目录指针表物理地址
.equ PDT_PHY_ADDR, 0x0000c000 # 对应于低端2MB的页目录表物理地址
.equ PT_PHY_ADDR, 0x0000d000 # 对应于低端2MB的内核页表的物理地址
.equ IDT_PHY_ADDR, 0x0000e000 # 中断描述符表的物理地址
.equ LDR_PHY_ADDR, 0x0000f000 # 用于安装内核加载器的起始物理地址
.equ GDT_PHY_ADDR, 0x00010000 # 全局描述符表GDT的物理地址
.equ CORE_PHY_ADDR, 0x00020000 # 内核的起始物理地址
.equ COR_PDPT_ADDR, 0x00100000 # 从这个物理地址开始的1MB是内核的254个页目录指针表
.equ UPPER_LINEAR_START, 0xffff800000000000 # 虚拟内存的高端起始于线性地址0xffff800000000000
.equ UPPER_GDT_LINEAR, UPPER_LINEAR_START + GDT_PHY_ADDR #GDT的高端线性地址
.equ UPPER_IDT_LINEAR, UPPER_LINEAR_START + IDT_PHY_ADDR #IDT的高端线性地址

.section .text
.align 4
.global _start
_start:
.code64
    movl $0x28, %eax
    movl %eax, %ds
    movl $0x30, %eax
    movl %eax, %ss
    movq $0xffff800000200000, %rsp

    sgdt .gdt_size(%rip)
    movq $UPPER_GDT_LINEAR, %rax
    movq %rax, .gdt_base(%rip)
    lgdt .gdt_size(%rip)

    leaq .upper(%rip), %rax
    movq $UPPER_LINEAR_START, %rbx
    addq %rbx, %rax
    jmpq *%rax
    .upper:

    leaq general_interrupt_handler(%rip), %rax
    movq %rax, %rbx
    shrq $32, %rbx #右移32位，得到门的高64位
    pushq %rax
    movw $0x20, 2(%rsp)
    movl %eax, 4(%rsp)
    movw $0x8e00,4(%rsp) #中断门
    popq %rax

    leaq general_exception_handler(%rip), %rax
    movq %rax, %rbx
    shrq $32, %rbx #右移32位，得到门的高64位
    pushq %rax
    movw $0x20, 2(%rsp)
    movl %eax, 4(%rsp)
    movw $0x8f00,4(%rsp) #陷阱门
    popq %rax

    hlt
general_interrupt_handler:
    iretq
general_exception_handler:
    iretq

.gdt_size:
    .word 0x0000
.gdt_base:
    .quad UPPER_GDT_LINEAR
