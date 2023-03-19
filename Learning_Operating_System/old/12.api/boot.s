    head_base_address equ 0x00090000            ;常数，引导程序的起始内存地址
    head_start_sector equ 0x00000001            ;常数，引导程序的起始逻辑扇区号
    head_sector_size  equ 0x00000004            ;常数，引导程序的总扇区个数

SECTION mbr vstart=0x7c00 align=16              ;定义主引导扇区
    start:
    ;使编译器按默认16位编译
    bits 16
    ;初始化堆栈段及堆栈段指针
    mov ax, 0x07e0
    mov ss, ax
    mov sp, 0x0200

    mov ax, [cs:loading_address]                ;低16位
    mov dx, [cs:loading_address+0x02]           ;高16位

    mov bx, 16
    div bx
    mov ds, ax                                  ;令DS指向该段以进行操作
    mov bx, dx                                  ;段内起始偏移地址

    ;对过程调用read_hard_disk_0做好准备
    xor di, di                                  ;将di置0
    mov si, [cs:loading_sector]                 ;和过程调用约定将用户程序起始逻辑扇区号置于si中
    xor bx, bx                                  ;约定将读取的扇区加载到[ds:bx]即[ds:0x0000]中
    mov cx, [cs:loading_size]

    loading:
    call read_hard_disk_0                       ;过程调用
    add bx, 512
    inc si
    loop loading

    ;开始处理段重定位表
    mov cx, 0x03                                ;需要重定位的表项个数
    mov bx, 0x06                                ;重定位表基址

    realloc:                                    ;对用户程序进行重定位
    mov dx, [bx+0x02]                           ;取得第一个段重定位表项的高16位
    mov ax, [bx]                                ;取得第一个段重定位表项的低16位
    call calc_segment_base
    mov [bx], ax                                ;回填用户程序各段的基址
    add bx, 4                                   ;下一个重定位项
    loop realloc

    jmp road1
;-------------------------------------------------------------------------------
    road1:
    mov ax, [0x0e]
    mov ss, ax
    mov sp, 1024

    mov ax, ds
    mov es, ax

    mov ax, [0x0a]
    mov ds, ax

    jmp far [es:0x04]
    hlt
;-------------------------------------------------------------------------------
    road2:
    mov ax, [0x0e]
    mov ss, ax
    mov sp, 1024

    mov es, [0x06]
    mov bx, [0x04]

    mov ax, [0x0a]
    mov ds, ax

    push es
    push bx
    retf
    hlt                                         ;处理器暂停
;-------------------------------------------------------------------------------
    read_hard_disk_0:                           ;从磁盘中读取一个指定的逻辑扇区
                                                ;约定将读取的扇区加载到[ds:bx]即[ds:0x0000]中
        ;保存环境，将可能用到的寄存器压栈
        push ax
        push bx
        push cx
        push dx

        mov dx, 0x1f2
        mov al, 1
        out dx, al                              ;读取的扇区数

        inc dx                                  ;0x1f3
        mov ax, si
        out dx, al                              ;LBA地址7~0

        inc dx                                  ;0x1f4
        mov al, ah
        out dx, al                              ;LBA地址15~8

        inc dx                                  ;0x1f5
        mov ax, di
        out dx, al                              ;LBA地址23~16

        inc dx                                  ;0x1f6
        mov al, 0xe0                            ;LBA28模式，主盘
        or al, ah                               ;LBA地址27~24
        out dx, al

        inc dx                                  ;0x1f7
        mov al, 0x20                            ;读命令
        out dx, al

        .waits:
        in al, dx
        and al, 0x88
        cmp al, 0x08
        jnz .waits                              ;不忙，且硬盘已准备好数据传输

        mov cx, 256                             ;总共要读取的字数
        mov dx, 0x1f0

        .readw:
        in ax, dx
        mov [bx], ax
        add bx, 2
        loop .readw

        ;恢复环境
        pop dx
        pop cx
        pop bx
        pop ax

        ret                                     ;从过程调用中返回
;-------------------------------------------------------------------------------
    calc_segment_base:                          ;计算20位地址的段地址
                                                ;约定需要计算的地址，高4位存放在DX中，低16位存放在AX中
        push dx;

        add ax, [cs:loading_address]            ;加载用户程序后的用户程序代码段在当前段的段内偏移量的低16位，可能会有进位，有进位的话cf=1
        ;adc是带进位的加法
        adc dx, [cs:loading_address+0x02]       ;加载用户程序后的用户程序代码段在当前段的段内偏移量的高4位
        ;shr逻辑右移指令
        shr ax, 4
        ;ror循环右移指令
        ror dx, 4
        and dx, 0xf000
        or ax, dx                               ;ax中为逻辑段地址

        pop dx

        ret
;-------------------------------------------------------------------------------
    loading_address:    dd head_base_address
    loading_sector:     dw head_start_sector
    loading_size:       dw head_sector_size
times 510-($-$$)        db 0
                        db 0x55, 0xaa