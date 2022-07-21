SECTION mbr vstart=0x7c00 align=16              ;定义主引导扇区
    start:
    ;使编译器按默认16位编译
    bits 16
    ;初始化堆栈段及堆栈段指针
    mov ax, 0
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

    ;创建#1描述符，保护模式下的数据段描述符（文本模式下的显示缓冲区）
    mov dword [bx+0x08], 0x80007fff             ;32k
    mov dword [bx+0x0c], 0x0040920b

    ;创建#2描述符，保护模式下的代码段描述符
    mov dword [bx+0x10], 0x7c0003ff             ;1k,MBR
    mov dword [bx+0x14], 0x00409800

    ;初始化描述符表寄存器GDTR
    mov word [cs: gdt_size], 23                 ;描述符表的界限（总字节数减一）
    lgdt [cs: gdt_size]

    in al, 0x92                                 ;南桥芯片内的端口
    or al, 0000_0010B
    out 0x92, al                                ;打开A20

    cli                                         ;保护模式下中断机制尚未建立，应禁止中断

    mov eax, cr0
    or eax, 1
    mov cr0, eax                                ;设置PE位

    ;代码段选择子 00000000000_10_000B
    jmp dword 00000000000_10_000B:print-start
                                                ;加载代码段选择子(索引0x02)

    ;使编译器按默认32位编译
    bits 32

    print:
    ;以下在屏幕上显示"Protect mode OK."
    mov cx, 00000000000_01_000B                 ;加载数据段选择子(索引0x01)
    mov ds, cx
    mov byte [0x00], 'P'
    mov byte [0x02], 'r'
    mov byte [0x04], 'o'
    mov byte [0x06], 't'
    mov byte [0x08], 'e'
    mov byte [0x0a], 'c'
    mov byte [0x0c], 't'
    mov byte [0x0e], ' '
    mov byte [0x10], 'm'
    mov byte [0x12], 'o'
    mov byte [0x14], 'd'
    mov byte [0x16], 'e'
    mov byte [0x18], ' '
    mov byte [0x1a], 'O'
    mov byte [0x1c], 'K'

    ;写2000个空格
    mov cx, 2000
    mov bx, 0x1e
    cls:
    mov word[bx], 0x0720
    add bx, 2
    loop cls

    gohalt:
    hlt                                         ;已经禁止中断，将不会被唤醒

    gdt_size:           dw 0x0000               ;
    gdt_base:           dd 0x8000               ;

times 510-($-$$)        db 0
                        db 0x55, 0xaa