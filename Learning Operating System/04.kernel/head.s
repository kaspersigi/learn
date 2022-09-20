.equ gdt_base_address,      0x00010000 # 常数，gdt的起始内存地址
.equ kernel_base_address,   0x00000000 # 常数，kernel加载内存起始地址
.equ kernel_start_sector,   0x00000004 # 常数，kernel起始逻辑扇区号

# 定义引导程序头部段
.section ".data.head"
.align 4
    program_length: .int    program_end # 程序总长度
    text_entry:     .short  _start      # 代码段入口段内偏移地址
    # 段重定位表
    realloc_tbl_begin:
    data_segment:   .int    _data_start     # 数据段距程序首地址偏移地址
    stack_segment:  .int    _stack_start    # 栈段距程序首地址偏移地址
    text_segment:   .int    _start    # 代码段距程序首地址偏移地址
    realloc_tbl_end:

.section .text
.align 4
.global _start
_start:
.code16
    .asciz "section text"

.section .data
.align 4
_data_start:
    .asciz "section data"

.section ".data.stack"
.align 4
_stack_start:
    .asciz "section stack"

.section ".data.tail"
    .asciz "section tail"
    program_end:
