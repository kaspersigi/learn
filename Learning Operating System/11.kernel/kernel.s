.section .text
.align 4
.global _start
_start:
.code64
    leaq _start(%rip), %rax
