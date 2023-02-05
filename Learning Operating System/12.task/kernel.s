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
.equ UPPER_GDT_LINEAR, UPPER_LINEAR_START + GDT_PHY_ADDR # GDT的高端线性地址
.equ UPPER_IDT_LINEAR, UPPER_LINEAR_START + IDT_PHY_ADDR # IDT的高端线性地址
.equ UPPER_CORE_ADDR, UPPER_LINEAR_START + CORE_PHY_ADDR # kernel起始的高端线性地址
.equ CORE_CODE64_SEL, 0x20 # 内核代码段段选择子

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

    call set_int

    sti #开放硬件中断

    int $0x80

    movq $.halt, %rax
    movq $UPPER_CORE_ADDR, %rbx
    addq %rbx, %rax
    .halt:
    hlt
    jmpq *%rax
    # jmpq *.halt(%rip)

# 为32个异常创建通用处理过程的中断门
# 和保护模式下的中断向量表一样
# 0~21基本是异常
# 22~31保留，不允许使用
# 32~255自定义
set_int:
    leaq general_exception_handler(%rip), %rax
    call make_interrupt_gate
    xorq %r8, %r8

    .mount_idt_32:
    call mount_idt_entry
    inc %r8
    cmpq $31, %r8
    jle .mount_idt_32

    leaq general_interrupt_handler(%rip), %rax
    call make_interrupt_gate
    movq $32, %r8

    .mount_idt_255:
    call mount_idt_entry
    inc %r8
    cmpq $255, %r8
    jle .mount_idt_255

    movq $UPPER_IDT_LINEAR, %rax # 中断描述符表IDT的高端线性地址
    movq %rax, .idt_base(%rip)
    movw $(256 << 16 -1), %ax
    movw %ax, .idt_size(%rip)

    lidt .idt_size(%rip)
    call init_8259

    leaq general_8259ints_handler(%rip), %rax
    call make_interrupt_gate
    movq $0x20, %r8

    .mount_idt_8259:
    call mount_idt_entry
    inc %r8
    cmpq $0x2f, %r8
    jle .mount_idt_8259

    ret

general_exception_handler:
    movq $0, %rax
    iretq

general_interrupt_handler:
    movq $1, %rax
    iretq

# 通用的8259中断处理过程
general_8259ints_handler:
    pushq %rax

    movb $0x20, %al # 中断结束命令EOI
    outb %al, $0xa0 # 向从片发送
    outb %al, $0x20 # 向主片发送

    pop %rax
    iretq

#创建64位的中断门
#输入：RAX=例程的线性地址
#输出：RDI:RSI=中断门
make_interrupt_gate:
    movq %rax, %rdi
    shrq $32, %rdi # 得到门的高64位，在RDI中
    pushq %rax # 构造数据结构，并预置线性地址的位15~0
    movw $CORE_CODE64_SEL, 2(%rsp) # 预置段选择子部分
    movl %eax, 4(%rsp) # 预置线性地址的位31~16
    movw $0x8e00,4(%rsp) # 添加P=1，TYPE=64位中断门
    popq %rsi
    ret

# 创建64位的陷阱门
# 输入：RAX=例程的线性地址
# 输出：RDI:RSI=陷阱门
make_trap_gate:
    movq %rax, %rdi
    shrq $32, %rdi # 得到门的高64位，在RDI中
    pushq %rax # 构造数据结构，并预置线性地址的位15~0
    movw $CORE_CODE64_SEL, 2(%rsp) # 预置段选择子部分
    movl %eax, 4(%rsp) # 预置线性地址的位31~16
    movw $0x8f00,4(%rsp) # 添加P=1，TYPE=64位陷阱门
    popq %rsi
    ret

# 在中断描述符表IDT中安装门描述符
# R8=中断向量
# RDI:RSI=门描述符
mount_idt_entry:
    pushq %r8
    pushq %r9

    shl $4, %r8 # 中断号乘以16，得到表内偏移
    movq $UPPER_IDT_LINEAR, %r9 # 中断描述符表的高端线性地址
    movq %rsi, (%r9, %r8)
    movq %rdi, 8(%r9, %r8)
    popq %r9
    popq %r8
    ret

    # 初始化8259中断控制器，包括重新设置向量号
init_8259:
    pushq %rax

    movb $0x11, %al
    outb %al, $0x20 # ICW1：边沿触发/级联方式
    movb $0x20, %al
    outb %al, $0x21 # ICW2:起始中断向量（避开前31个异常的向量）
    movb $0x04, %al
    outb %al, $0x21 # ICW3:从片级联到IR2
    movb $0x01, %al
    outb %al, $0x21 # ICW4:非总线缓冲，全嵌套，正常EOI

    movb $0x11, %al
    outb %al, $0xa0 # ICW1：边沿触发/级联方式
    movb $0x28, %al
    outb %al, $0xa1 # ICW2:起始中断向量-->0x28
    movb $0x02, %al
    outb %al, $0xa1 # ICW3:从片识别标志，级联到主片IR2
    movb $0x01, %al
    outb %al, $0xa1 # ICW4:非总线缓冲，全嵌套，正常EOI

    popq %rax
    ret

.gdt_size:
    .word 0x0000
.gdt_base:
    .quad UPPER_GDT_LINEAR
.idt_size:
    .word 0x0000
.idt_base:
    .quad UPPER_IDT_LINEAR
