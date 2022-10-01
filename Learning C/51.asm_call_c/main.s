.section .data
.align 4
buffer:
    .fill 48
    .ascii "\r\n"

.section .text
.align 4
.global _start
_start:
.code32
    # 显示处理器品牌信息
    movl $buffer, %edi
    movl $0x80000002, %eax
    cpuid
    movl %eax, 0x00(%edi)
    movl %ebx, 0x04(%edi)
    movl %ecx, 0x08(%edi)
    movl %edx, 0x0c(%edi)

    addl $0x10, %edi
    movl $0x80000003, %eax
    cpuid
    movl %eax, 0x00(%edi)
    movl %ebx, 0x04(%edi)
    movl %ecx, 0x08(%edi)
    movl %edx, 0x0c(%edi)

    addl $0x10, %edi
    movl $0x80000004, %eax
    cpuid
    movl %eax, 0x00(%edi)
    movl %ebx, 0x04(%edi)
    movl %ecx, 0x08(%edi)
    movl %edx, 0x0c(%edi)

    movl $4, %eax
    movl $1, %ebx
    movl $buffer, %ecx
    movl $50, %edx
    int $0x80

    call func

    movl $1, %eax
    movl $0, %ebx
    int $0x80
