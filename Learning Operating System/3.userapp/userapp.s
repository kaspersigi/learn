SECTION head vstart=0 align=16                  ;定义用户程序头部段
    program_length:     dd program_end          ;程序总长度
    ;用户程序入口点
    code_entry:         dw start                ;代码段入口段内偏移地址--被重定位修改
                        dd section.text.start   ;代码段距程序首地址偏移地址
    realloc_tbl_len     dw (realloc_tbl_end-realloc_tbl_begin)/4
                                                ;段重定位表项个数
    ;段重定位表
    realloc_tbl_begin:
    text_segment:       dd section.text.start   ;代码段距程序首地址偏移地址--被重定位修改
    data_segment:       dd section.data.start   ;数据段距程序首地址偏移地址--被重定位修改
    stack_segment:      dd section.stack.start  ;数据段距程序首地址偏移地址--被重定位修改
    realloc_tbl_end:

SECTION text vstart=0 align=16                  ;定义代码段
    start:                                      ;程序入口
    mov cx, ss                                  ;保存loader ss
    mov dx, sp                                  ;保存loader sp

    ;初始执行时，DS和ES指向用户程序头部段
    mov ax, [stack_segment]
    mov ss, ax                                  ;初始化堆栈寄存器
    mov sp, stack_pointer                       ;初始化栈顶指针

    ;保存loader现场
    push cx
    push dx
    push es
    push si
    push ds
    push di

    mov ax, [data_segment]
    mov ds, ax                                  ;初始化数据段寄存器
                                                ;最后初始化ds，因为之前指向用户程序加载后的逻辑地址，修改后，将无法定位和访问用户程序

    mov ax, 0xb800
    mov es, ax

    mov di, message
    mov si, 0

    next:
        mov al, [di]
        cmp al, 0                               ;判断是否到达字符串末尾
        je exit
        mov byte [es:si], al
        mov byte [es:si+1], 0x07
        inc di
        add si, 2
        jmp next

    exit:
    pop di
    pop ds
    pop si
    pop es
    pop dx
    pop cx

    mov ss, cx
    mov sp, dx

    retf

SECTION data vstart=0 align=16                  ;定义数据段
    message:            db 'Hello World!', 0    ;0作为结束的标志

SECTION stack vstart=0 align=16                 ;定义栈段
    times 256 db 0
    stack_pointer:

SECTION tail align=16
    program_end: