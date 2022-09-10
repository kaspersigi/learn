.equ head_base_address, 0x00090000 # 常数，引导程序的起始内存地址
.equ head_start_sector, 0x00000001 # 常数，引导程序的起始逻辑扇区号
.equ head_sector_size,  0x00000004 # 常数，引导程序的总扇区个数

.section .text
.align 16
.global _start
_start:
.code16
    start:
    # 初始化堆栈段及堆栈段指针
    movw $0x07e0, %ax
    movw %ax, %ss
    movw $0x0200, %sp

    # 计算20位地址的段地址
    # 约定需要计算的地址，高4位存放在DX中，低16位存放在AX中
    movw %cs:(loading_address), %ax
    movw %cs:(loading_address+0x02), %dx

    movw $16, %bx
    divw %bx
    # 令DS、ES指向loading_address为起始的段
    movw %ax, %ds
    movw %ax, %es
    movw %dx, %bx # 段内偏移

    call load

    hlt

load:
    pushw %ax
    pushw %bx
    pushw %cx
    pushw %dx

    # 读磁盘
    # INT 13H AH=2
    # AL=扇区
    # CH,CL=磁道号，扇区号
    # DH:DL=磁头号，驱动器号
    # ES:BX=数据缓冲区地址
    movb $0x02, %ah
    movb %cs:(loading_size), %al
    movw $0x0001, %cx
    movw $0x0080, %dx
    movw $0x0000, %bx
    int $0x13

    popw %dx
    popw %cx
    popw %bx
    popw %ax

    ret

    # 扩展读
    # INT 13H AH=42H
    # 检验拓展功能是否存在
    /*
    movb $0x42, %ah
    movw $0x55aa, %bx
    movb $0x80, %dh
    int $0x13
    int13_diskette: unsupported AH=42
    */

    loading_address: .int   head_base_address
    loading_sector:  .short head_start_sector
    loading_size:    .short head_sector_size

.org 510
boot_flag: .word 0xAA55
