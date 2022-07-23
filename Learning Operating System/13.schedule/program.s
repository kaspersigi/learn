SECTION head vstart=0 align=16                  ;定义用户程序头部段
    program_length:     dd program_end          ;程序总长度(0x00
    head_length:        dd head_end             ;程序头部段长度->回填头部段选择子(0x04

    text_entry:         dd start                ;代码段入口段内偏移地址(0x08
    text_segment:       dd section.text.start   ;代码段距程序首地址偏移地址(0x0c
    text_length:        dd text_end             ;程序代码段长度(0x10

    data_segment:       dd section.data.start   ;数据段距程序首地址偏移地址(0x14
    data_length:        dd data_end             ;程序代码段长度(0x18

    stack_segment       dd section.stack.start  ;堆栈段距程序首地址偏移地址(0x1c
    stack_length        dd stack_end            ;程序堆栈段长度(0x20
;-------------------------------------------------------------------------------
    salt_length:            dd (salt_end-salt_begin)/256
                                                ;(0x24
    ;符号地址检索表
    salt_begin:                                 ;(0x28
    print:                  db '@print'         ;(0x28
    times 256-($-print)     db 0
    init_task_switch:       db '@init_task_switch'  ;(0x128
    times 256-($-init_task_switch)  db 0
    salt_end:
;-------------------------------------------------------------------------------
    head_end:

SECTION text vstart=0 align=16                  ;定义引导程序代码段
    bits 32
    start:
    mov ax, [gs:0x14]
    mov ds, ax

    mov ebx, message1
    call far [gs:print]

    ;显示处理器品牌信息
    mov eax, 0x80000002
    cpuid
    mov [cpu_brand+0x00], eax
    mov [cpu_brand+0x04], ebx
    mov [cpu_brand+0x08], ecx
    mov [cpu_brand+0x0c], edx

    mov eax,0x80000003
    cpuid
    mov [cpu_brand+0x10], eax
    mov [cpu_brand+0x14], ebx
    mov [cpu_brand+0x18], ecx
    mov [cpu_brand+0x1c], edx

    mov eax,0x80000004
    cpuid
    mov [cpu_brand+0x20], eax
    mov [cpu_brand+0x24], ebx
    mov [cpu_brand+0x28], ecx
    mov [cpu_brand+0x2c], edx

    mov ebx, cpu_brand
    call far [gs:print]

    mov ebx, crlf
    call far [gs:print]

    mov ebx, message2
    call far [gs:print]

    call far [gs:init_task_switch]
    text_end:

SECTION data vstart=0 align=16                  ;定义用户程序数据段
    message1:           db 'program is running......', 0x0d, 0x0a, 0
    message2:           db 'program is over......', 0x0d, 0x0a, 0
    crlf:               db 0x0d, 0x0a, 0
    cpu_brand: times 52 db 0
    data_end:

SECTION stack vstart=0 align=16                 ;定义用户程序堆栈段
    times 1024          db 0

    stack_end:

SECTION tail align=16
    program_end: