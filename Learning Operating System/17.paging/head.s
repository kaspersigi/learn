    gdt_base_address    equ 0x00010000          ;常数，gdt的起始内存地址
    kernel_base_address equ 0x00000000          ;常数，kernel加载内存起始地址
    kernel_start_sector equ 0x00000004          ;常数，kernel起始逻辑扇区号
SECTION head vstart=0 align=16                  ;定义引导程序头部段
    program_length:     dd program_end          ;程序总长度
    text_entry:         dw start                ;代码段入口段内偏移地址
    ;段重定位表
    realloc_tbl_begin:
    text_segment:       dd section.text.start   ;代码段距程序首地址偏移地址
    data_segment:       dd section.data.start   ;数据段距程序首地址偏移地址
    stack_segment:      dd section.stack.start  ;栈段距程序首地址偏移地址
    realloc_tbl_end:

SECTION text vstart=0 align=16                  ;定义引导程序代码段
    bits 16
    start:
    ;计算GDT所在的逻辑段地址
    mov ax, [gdt_base]                          ;低16位
    mov dx, [gdt_base+0x02]                     ;高16位

    mov bx, 16
    div bx
    mov es, ax                                  ;令ES指向该段以进行操作
    mov bx, dx                                  ;段内起始偏移地址

    mov si, bx

    ;创建0#描述符，它是空描述符，这是处理器的要求
    mov dword [es:bx+0x00], 0x00
    mov dword [es:bx+0x04], 0x00

    ;创建#1描述符，保护模式下的数据段描述符
    mov dword [es:bx+0x08], 0x80007fff          ;32K, 显存数据段
    mov dword [es:bx+0x0c], 0x0040920b

    ;创建#2描述符，保护模式下的数据段描述符
    mov dword [es:bx+0x10], 0x0000ffff          ;64K, GDT数据段
    mov dword [es:bx+0x14], 0x00409201

    ;创建#3描述符，保护模式下的数据段描述符
    mov dword [es:bx+0x18], 0x0000ffff          ;4G, kernel用数据段
    mov dword [es:bx+0x1c], 0x00cf9200

    ;建立代码段描述符#4
    mov cx, cs                                  ;引导程序代码段基址
    mov bx, ds                                  ;引导程序数据段基址
    mov word [descriptor_3], 0x0040
    mov word [descriptor_2], 0x9800
    mov di, 0x0020
    call make_gdt_descriptor_16

    ;建立数据段描述符#5
    mov cx, ds                                  ;引导程序数据段基址
    mov bx, ss                                  ;引导程序堆栈段基址
    mov word [descriptor_3], 0x0040
    mov word [descriptor_2], 0x9200
    mov di, 0x0028
    call make_gdt_descriptor_16

    ;建立堆栈段描述符#6
    mov cx, ss                                  ;引导程序堆栈段基址
    mov ax, stack_pointer
    mov bx, 16
    div bx
    add ax, cx
    mov bx, ax                                  ;引导程序尾部基址
    mov word [descriptor_3], 0x0040
    mov word [descriptor_2], 0x9200
    mov di, 0x0030
    call make_gdt_descriptor_16

    mov word [gdt_size], 55                     ;描述符表的界限（总字节数减一）
    lgdt [gdt_size]

    in al, 0x92                                 ;南桥芯片内的端口
    or al, 0000_0010B
    out 0x92, al                                ;打开A20

    cli                                         ;保护模式下中断机制尚未建立，应禁止中断

    mov eax, cr0
    or eax, 1
    mov cr0, eax                                ;设置PE位

    jmp dword 0000000000100_000B:protected-start;加载代码段选择子#4
;-------------------------------------------------------------------------------
    make_gdt_descriptor_16:                     ;构造描述符
                                                ;约定段起点为cx，终点为bx
                                                ;新建段描述符在GDT中段基址为di
        sub bx, cx
        mov ax, bx
        mov dx, 0x0010
        mul dx
        dec ax                                  ;段界限

        mov word [descriptor_1], 0x0000
        mov [descriptor_0], ax

        mov ax, cx                              ;段基址
        mov dx, 16
        mul dx
        mov [descriptor_1], ax
        add [descriptor_2], dx

        mov bx, di

        mov ax, [descriptor_0]
        mov [es:bx+si+0x00], ax
        mov ax, [descriptor_1]
        mov [es:bx+si+0x02], ax
        mov ax, [descriptor_2]
        mov [es:bx+si+0x04], ax
        mov ax, [descriptor_3]
        mov [es:bx+si+0x06], ax

        ret
;-------------------------------------------------------------------------------
    protected:
    bits 32
    mov cx, 0000000000101_000B                  ;加载数据段选择子(索引0x05)
    mov ds, cx

    mov cx, 0000000000110_000B                  ;加载堆栈段选择子(索引0x06)
    mov ss, cx

    mov cx, 0000000000001_000B                  ;加载显存数据段选择子(索引0x01)
    mov es, cx

    mov cx, 0000000000010_000B                  ;加载GDT数据段选择子(索引0x02)
    mov gs, cx

    mov cx, 0000000000011_000B                  ;加载kernel加载数据段选择子(索引0x03)
    mov fs, cx

    ;以下加载kernel
    mov eax, kernel_start_sector
    xor ebx, ebx
    call read_hard_disk_0                       ;以下读取kernel的起始部分（一个扇区）

    ;以下判断整个程序有多大
    mov eax, [fs:0x0000]                        ;核心程序尺寸
    xor edx, edx
    mov ecx, 512                                ;512字节每扇区
    div ecx

    or edx, edx
    jnz @1                                      ;未除尽，因此结果比实际扇区数少1
    dec eax                                     ;已经读了一个扇区，扇区总数减1
    @1:
    or eax, eax                                 ;考虑实际长度≤512个字节的情况
    jz setup                                    ;EAX=0 ?

    ;读取剩余的扇区
    mov ecx, eax                                ;32位模式下的LOOP使用ECX
    mov eax, kernel_start_sector
    inc eax                                     ;从下一个逻辑扇区接着读
    @2:
    call read_hard_disk_0
    inc eax
    loop @2                                     ;循环读，直到读完整个内核

    setup:
    mov edi, kernel_base_address
    ;建立kernel代码段描述符#7
    mov eax, [fs:0x04]                          ;kernel代码段起始汇编地址
    mov ebx, [fs:0x08]                          ;kernel例程段起始汇编地址
    sub ebx, eax
    dec ebx                                     ;kernel代码段界限
    add eax, edi                                ;kernel代码段基地址
    mov ecx, 0x00409800                         ;字节粒度的代码段描述符
    call make_gdt_descriptor_32
    mov [gs:0x38], eax
    mov [gs:0x3c], edx

    ;建立kernel例程段描述符#8
    mov eax, [fs:0x08]                          ;kernel例程段起始汇编地址
    mov ebx, [fs:0x0c]                          ;kernel数据段起始汇编地址
    sub ebx, eax
    dec ebx                                     ;kernel例程段界限
    add eax, edi                                ;kernel例程段基地址
    mov ecx, 0x00409800                         ;字节粒度的代码段描述符
    call make_gdt_descriptor_32
    mov [gs:0x40], eax
    mov [gs:0x44], edx

    ;建立kernel数据段描述符#9
    mov eax, [fs:0x0c]                          ;kernel数据段起始汇编地址
    mov ebx, [fs:0x10]                          ;kernel堆栈段起始汇编地址
    sub ebx, eax
    dec ebx                                     ;kernel数据段界限
    add eax, edi                                ;kernel数据段基地址
    mov ecx, 0x00409200                         ;字节粒度的数据段描述符
    call make_gdt_descriptor_32
    mov [gs:0x48], eax
    mov [gs:0x4c], edx

    ;建立kernel堆栈段描述符#10
    mov eax, [fs:0x10]                          ;kernel堆栈段起始汇编地址
    mov ebx, [fs:0x00]                          ;程序总长度
    sub ebx, eax
    dec ebx                                     ;kernel数据段界限
    add eax, edi                                ;kernel数据段基地址
    mov ecx, 0x00409200                         ;字节粒度的数据段描述符
    call make_gdt_descriptor_32
    mov [gs:0x50], eax
    mov [gs:0x54], edx

    mov word [gdt_size], 87                     ;描述符表的界限
    lgdt [pgdt]
    jmp far [fs:0x14]

    hlt
;-------------------------------------------------------------------------------
    read_hard_disk_0:                           ;从硬盘读取一个逻辑扇区
                                                ;EAX=逻辑扇区号
                                                ;FS:EBX=目标缓冲区地址
                                                ;返回：EBX=EBX+512
        push eax
        push ecx
        push edx

        push eax

        mov dx, 0x1f2
        mov al, 1
        out dx, al                              ;读取的扇区数

        inc dx                                  ;0x1f3
        pop eax
        out dx, al                              ;LBA地址7~0

        inc dx                                  ;0x1f4
        mov cl, 8
        shr eax, cl
        out dx, al                              ;LBA地址15~8

        inc dx                                  ;0x1f5
        shr eax, cl
        out dx, al                              ;LBA地址23~16

        inc dx                                  ;0x1f6
        shr eax, cl
        or al, 0xe0                             ;第一硬盘  LBA地址27~24
        out dx, al

        inc dx                                  ;0x1f7
        mov al, 0x20                            ;读命令
        out dx, al

        .waits:
        in al, dx
        and al, 0x88
        cmp al, 0x08
        jnz .waits                              ;不忙，且硬盘已准备好数据传输

        mov ecx, 256                            ;总共要读取的字数
        mov dx, 0x1f0

        .readw:
        in ax, dx
        mov [fs:ebx], ax
        add ebx, 2
        loop .readw

        pop edx
        pop ecx
        pop eax

        ret
;-------------------------------------------------------------------------------
    make_gdt_descriptor_32:                     ;构造描述符
                                                ;输入：EAX=线性基地址
                                                ;      EBX=段界限
                                                ;      ECX=属性（各属性位都在原始
                                                ;      位置，其它没用到的位置0）
                                                ;返回：EDX:EAX=完整的描述符
        mov edx, eax
        shl eax, 16
        or ax, bx                               ;描述符前32位(EAX)构造完毕

        and edx, 0xffff0000                     ;清除基地址中无关的位
        rol edx, 8
        bswap edx                               ;装配基址的31~24和23~16  (80486+)

        xor bx, bx
        or edx, ebx                             ;装配段界限的高4位

        or edx, ecx                             ;装配属性
        ret
;-------------------------------------------------------------------------------
SECTION data vstart=0 align=16                  ;定义引导程序数据段
    descriptor:
    descriptor_0:       dw 0x0000
    descriptor_1:       dw 0x0000
    descriptor_2:       dw 0x0000
    descriptor_3:       dw 0x0000
    pgdt:
    gdt_size:           dw 0x0000
    gdt_base:           dd 0x00010000

SECTION stack vstart=0 align=16                 ;定义引导程序堆栈段
    times 1024          db 0
    stack_pointer:

SECTION tail align=16
    program_end: