SECTION mbr vstart=0x7c00 align=16              ;定义主引导扇区
    start:
    ;使编译器按默认16位编译
    bits 16
    ;初始化堆栈段及堆栈段指针
    xor ax, ax
    mov ss, ax
    mov sp, 0x8000

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
    mov dword [bx+0x08], 0x7c0001ff             ;512B,MBR
    mov dword [bx+0x0c], 0x00409800

    ;创建#2描述符，保护模式下的栈段描述符
    mov dword [bx+0x10], 0x7e0001ff             ;512B
    mov dword [bx+0x14], 0x00409200

    ;创建#3描述符，保护模式下的数据段描述符
    mov dword [bx+0x18], 0x80007fff             ;32K
    mov dword [bx+0x1c], 0x0040920b

    ;创建#4描述符，保护模式下的数据段描述符
    mov dword [bx+0x20], 0x80007fff             ;32K
    mov dword [bx+0x24], 0x0040920b

    ;创建#5描述符，保护模式下的数据段描述符
    mov dword [bx+0x28], 0x7c0001ff             ;512B
    mov dword [bx+0x2c], 0x00409200

    ;初始化描述符表寄存器GDTR
    mov word [cs: gdt_size], 47                 ;描述符表的界限（总字节数减一）
    lgdt [cs: gdt_size]

    in al, 0x92                                 ;南桥芯片内的端口
    or al, 0000_0010B
    out 0x92, al                                ;打开A20

    cli                                         ;保护模式下中断机制尚未建立，应禁止中断

    mov eax, cr0
    or eax, 1
    mov cr0, eax                                ;设置PE位

    jmp dword 0000000000001_000B:protected-start
                                                ;加载代码段选择子(索引0x01)

    ;使编译器按默认32位编译
    bits 32
    protected:
    mov ax, 0000000000010_000B
    mov ss, ax
    mov esp, 0x0200

    mov ax, 0000000000011_000B
    mov ds, ax

    mov ax, 0000000000100_000B
    mov es, ax

    mov ax, 0000000000101_000B
    mov fs, ax

    call clear

    mov dword ebx, welcome-start
    call show

    mov esi, string-start
    xor edx, edx
    call sizeof

    ;开始冒泡排序
    dec edx                                     ;冒泡排序外循环次数为个数减一
    mov ecx, edx
    step1:
    push ecx                                    ;32位操作尺寸下loop使用ecx
    xor bx, bx                                  ;32位操作尺寸下偏移量可以是16位，也可以是32位
    step2:
    mov ax, [fs:string+bx-start]
    cmp ah, al
    jge step3
    xchg al, ah
    mov [fs:string+bx-start], ax
    step3:
    inc bx
    loop step2                                  ;外循环

    pop ecx
    loop step1

    call clear
    mov dword ebx, string-start
    call show

    gohalt:
    hlt                                         ;已经禁止中断，将不会被唤醒

;-------------------------------------------------------------------------------
    ;将屏幕清空
    clear:
        mov al, 80
        mov bl, 24
        mul bl
        xor ecx, ecx
        mov cx, ax
        xor ax, ax
        xor ebx, ebx
        show_null:
        mov [es:ebx*2], ax
        inc ebx
        loop show_null
        ret
;-------------------------------------------------------------------------------
    ;显示welcome信息
    show:
        mov ecx, 512
        xor esi, esi

        print:
        mov dl, [fs:ebx+esi]
        cmp dl, 0
        jz print_end
        mov [esi*2], dl
        mov byte [esi*2+1], 0x07
        inc esi
        loop print
        print_end:
        ret
;-------------------------------------------------------------------------------
    sizeof:
        mov ecx, 512
        compute:
        mov al, [fs:esi]
        cmp al, 0
        jz sizeof_end
        inc edx
        inc esi
        loop compute
        sizeof_end:
        ret
;-------------------------------------------------------------------------------
    welcome:            db 'welcome to protected mode!', 0
    string:             db 's0ke4or92xap3fv8giuzjcy5l1m7hd6bnqtw.', 0

    gdt_size:           dw 0x0000               ;
    gdt_base:           dd 0x8000               ;

times 510-($-$$)        db 0
                        db 0x55, 0xaa