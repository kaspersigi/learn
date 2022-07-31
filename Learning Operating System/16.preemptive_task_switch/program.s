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
    salt_length:                            dd (salt_end-salt_begin)/256
                                                                    ;(0x24
    ;符号地址检索表
    salt_begin:                                                     ;(0x28
    print:                                  db '@print'             ;(0x28
    times 256-($-print)                     db 0
    init_task_switch:                       db '@init_task_switch'  ;(0x128
    times 256-($-init_task_switch)          db 0
    terminate_current_task:                 db '@terminate_current_task'    ;(0x228
    times 256-($-terminate_current_task)    db 0
    salt_end:
;-------------------------------------------------------------------------------
    head_end:

SECTION text vstart=0 align=16                  ;定义引导程序代码段
    bits 32
    start:
    mov ax, ds
    mov gs, ax
    mov ax, [0x14]
    mov ds, ax

    mov ebx, message_1
    call far [gs:print]

    mov ax, cs                                  ;取CS段选择子
    and al, 0000_0011B                          ;取cpl
    or al, 0x30                                 ;0字符0x30，由于cpl只有0，1，2，3相当于加法
    mov [cpl], al
    mov ebx, message_0
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

    mov ebx, message_5
    call far [gs:print]

    mov ebx, crlf
    call far [gs:print]

    mov ebx, message_2
    call far [gs:print]

    ; call far [gs:init_task_switch]

    ; mov ebx, message_3
    ; call far [gs:print]

    ; mov ebx, message_4
    ; call far [gs:print]
    ; call far [gs:terminate_current_task]

    .do_print:
    mov ebx, message_6
    call far [gs:print]
    jmp .do_print

    call far [gs:terminate_current_task]        ;退出，并将控制权返回到核心
    text_end:

SECTION data vstart=0 align=16                  ;定义用户程序数据段
    message_0:          db '[User Task]: I am run at CPL=',
    cpl:                db 0
                        db '.....', 0x0d, 0x0a, 0
    message_1:          db '[User Task]: program task is running......', 0x0d, 0x0a, 0
    message_2:          db '[User Task]: program task is switching......', 0x0d, 0x0a, 0
    message_3:          db '[User Task]: program task is running again......', 0x0d, 0x0a, 0
    message_4:          db '[User Task]: program task is exiting......', 0x0d, 0x0a, 0
    message_5:          db '[User Task]: '
    cpu_brand: times 48 db 0
    crlf:               db 0x0d, 0x0a, 0
    message_6:          db '[User Task]: ,,,,,,,,,,,,,,,,,,,,,,,',0x0d,0x0a,0
    data_end:

SECTION stack vstart=0 align=16                 ;定义用户程序堆栈段
    times 1024          db 0

    stack_end:

SECTION tail align=16
    program_end: