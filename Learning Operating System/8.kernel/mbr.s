    kernel_base_address equ 0x00018000          ;常数，内核加载的起始内存地址
    kernel_start_sector equ 0x00000001          ;常数，内核的起始逻辑扇区号
                                                ;LBA逻辑区块从0开始
SECTION mbr vstart=0x7c00 align=16              ;定义主引导扇区
    start:
    ;使编译器按默认16位编译
    bits 16
    ;初始化堆栈段及堆栈段指针
    mov ax, 0x07e0
    mov ss, ax
    mov sp, 0x0200

    ;计算GDT所在的逻辑段地址
    mov ax, [cs:gdt_base]                       ;低16位
    mov dx, [cs:gdt_base+0x02]                  ;高16位

    mov bx, 16
    div bx
    mov ds, ax                                  ;令DS指向该段以进行操作
    mov bx, dx                                  ;段内起始偏移地址

    ;创建0#描述符，它是空描述符，这是处理器的要求
    mov dword [bx+0x00], 0x00
    mov dword [bx+0x04], 0x00

    ;创建#1描述符，保护模式下的代码段描述符
    mov dword [bx+0x08], 0x7c0001ff             ;512B, MBR代码段
    mov dword [bx+0x0c], 0x00409800

    ;创建#2描述符，保护模式下的栈段描述符
    mov dword [bx+0x10], 0x7e0001ff             ;512B, MBR栈段
    mov dword [bx+0x14], 0x00409200

    ;创建#3描述符，保护模式下的数据段描述符
    mov dword [bx+0x18], 0x7c0001ff             ;512B, MBR数据段
    mov dword [bx+0x1c], 0x00409200

    ;创建#4描述符，保护模式下的数据段描述符
    mov dword [bx+0x20], 0x80007fff             ;32K, 显存数据段
    mov dword [bx+0x24], 0x0040920b

    ;创建#5描述符，保护模式下的数据段描述符
    mov dword [bx+0x28], 0x8000ffff             ;64K, GDT数据段
    mov dword [bx+0x2c], 0x00409200

    ;创建#6描述符，保护模式下的数据段描述符
    mov dword [bx+0x30], 0x8000ffff             ;64K, 装载kernel用数据段
    mov dword [bx+0x34], 0x00409201

    ;初始化描述符表寄存器GDTR
    mov word [cs: gdt_size], 55                 ;描述符表的界限（总字节数减一）
    lgdt [cs: gdt_size]

    in al, 0x92                                 ;南桥芯片内的端口
    or al, 0000_0010B
    out 0x92, al                                ;打开A20

    cli                                         ;保护模式下中断机制尚未建立，应禁止中断

    mov eax, cr0
    or eax, 1
    mov cr0, eax                                ;设置PE位

    jmp dword 0000000000001_000B:protected-start;加载代码段选择子#1

    ;使编译器按默认32位编译
    bits 32
    protected:
    mov ax, 0000000000010_000B                  ;初始化MBR栈段#2
    mov ss, ax
    mov esp, 0x0200

    mov ax, 0000000000011_000B                  ;初始化MBR数据段#3
    mov fs, ax

    ; mov ax, 0000000000100_000B                  ;初始化显存数据段#4
    ; mov es, ax

    mov ax, 0000000000101_000B                  ;初始化GDT数据段#5
    mov gs, ax

    mov ax, 0000000000110_000B                  ;初始化加载kernel的数据段#6
    mov ds, ax

    ; call clear

    ; mov ebx, message-start
    ; call show

    ;以下加载系统核心程序
    mov eax, kernel_start_sector
    xor ebx, ebx
    call read_hard_disk_0                       ;以下读取程序的起始部分（一个扇区）

    ;以下判断整个程序有多大
    mov eax, [0x0000]                           ;核心程序尺寸
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
    ;建立核心代码段描述符#7
    mov eax, [0x04]                             ;核心代码段起始汇编地址
    mov ebx, [0x08]                             ;核心数据段起始汇编地址
    sub ebx, eax
    dec ebx                                     ;核心代码段界限
    add eax, edi                                ;核心代码段基地址
    mov ecx, 0x00409800                         ;字节粒度的代码段描述符
    call make_gdt_descriptor
    mov [gs:0x38], eax
    mov [gs:0x3c], edx

    ;建立核心数据段描述符#8
    mov eax, [0x08]                             ;核心数据段起始汇编地址
    mov ebx, [0x0c]                             ;核心堆栈段起始汇编地址
    sub ebx, eax
    dec ebx                                     ;核心数据段界限
    add eax, edi                                ;核心数据段基地址
    mov ecx, 0x00409200                         ;字节粒度的数据段描述符
    call make_gdt_descriptor
    mov [gs:0x40],eax
    mov [gs:0x44],edx

    ;建立核心堆栈段描述符#9
    mov eax, [0x0c]                             ;核心堆栈段起始汇编地址
    mov ebx, [0x00]                             ;程序总长度
    sub ebx, eax
    dec ebx                                     ;核心堆栈段界限
    add eax, edi                                ;核心堆栈段基地址
    mov ecx, 0x00409200                         ;字节粒度的堆栈段描述符
    call make_gdt_descriptor
    mov [gs:0x48],eax
    mov [gs:0x4c],edx

    mov word [fs:gdt_size-start], 79            ;描述符表的界限
    lgdt [fs:pgdt-start]
    jmp far [0x10]

    hlt
;-------------------------------------------------------------------------------
    ;将屏幕清空
    ; clear:
    ;    mov al, 80
    ;    mov bl, 24
    ;    mul bl
    ;    xor ecx, ecx
    ;    mov cx, ax
    ;    xor ax, ax
    ;    xor ebx, ebx
    ;    show_null:
    ;    mov [es:ebx*2], ax
    ;    inc ebx
    ;    loop show_null
    ;    ret
;-------------------------------------------------------------------------------
    ;显示welcome信息
    ; show:
    ;    mov ecx, 512
    ;    xor esi, esi

    ;    print:
    ;    mov dl, [fs:ebx+esi]
    ;    cmp dl, 0
    ;    jz print_end
    ;    mov [es:esi*2], dl
    ;    mov byte [es:esi*2+1], 0x07
    ;    inc esi
    ;    loop print
    ;    print_end:
    ;    ret
;-------------------------------------------------------------------------------
    read_hard_disk_0:                           ;从硬盘读取一个逻辑扇区
                                                ;EAX=逻辑扇区号
                                                ;DS:EBX=目标缓冲区地址
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
        mov [ebx], ax
        add ebx, 2
        loop .readw

        pop edx
        pop ecx
        pop eax

        ret
;-------------------------------------------------------------------------------
    make_gdt_descriptor:                        ;构造描述符
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
    ; message:            db 'booting......', 0
    pgdt:
    gdt_size:           dw 0x0000               ;
    gdt_base:           dd 0x8000               ;
times 510-($-$$)        db 0
                        db 0x55, 0xaa
