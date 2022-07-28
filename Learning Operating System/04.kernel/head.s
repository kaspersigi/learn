.equ gdt_base_address,      0x00010000 # 常数，gdt的起始内存地址
.equ kernel_base_address,   0x00000000 # 常数，kernel加载内存起始地址
.equ kernel_start_sector,   0x00000004 # 常数，kernel起始逻辑扇区号

# 定义引导程序头部段
.section .head
.align 4
    program_length: .int    program_end # 程序总长度
    text_entry:     .short  _start      # 代码段入口段内偏移地址
    # 段重定位表
    realloc_tbl_begin:
    text_segment:   .int    .text  # 代码段距程序首地址偏移地址
    data_segment:   .int    .data  # 数据段距程序首地址偏移地址
    stack_segment:  .int    .stack # 栈段距程序首地址偏移地址
    realloc_tbl_end:

.section .text
.align 4
.global _start
_start:
.code16
    .asciz "section text"

.section .data
.align 4
    .asciz "section data"

.section .stack
.align 4
    .asciz "section stack"

.section .tail
.align 4
    program_end:
