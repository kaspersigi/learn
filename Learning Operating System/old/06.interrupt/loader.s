    app_lba_start equ 100                       ;声明常数（用户程序起始逻辑扇区号）
                                                ;常数的声明不会占用汇编地址
SECTION mbr vstart=0x7c00 align=16              ;定义主引导扇区
    ;初始化堆栈段及堆栈段指针
    mov ax, 0
    mov ss, ax
    mov sp, ax

    ;计算用于加载用户程序的逻辑段地址
    ;准备将phy_base处存储的绝对地址，按实模式，将其拆分为段基址和偏移地址
    ;准备对双字中存储的20位地址做除法
    mov ax, [cs:phy_base]                       ;我们先取出其低16位于ax中
    mov dx, [cs:phy_base+0x02]                  ;再取出其高4位于dx中
    mov bx, 16
    div bx                                      ;将这20位地址除以16作为用户程序的逻辑段地址
    ;商在ax中，存储到ds中作为用户程序的逻辑段地址
    ;余数在dx中，作为用户程序的逻辑段偏移地址
    mov ds, ax                                  ;将phy_base的高16位作为数据段，将来从这里开始存放用户程序
    mov es, ax

    ;对过程调用read_hard_disk_0做好准备
    xor di, di                                  ;将di置0
    mov si, app_lba_start                       ;和过程调用约定将用户程序起始逻辑扇区号置于si中
    xor bx, bx                                  ;约定将读取的扇区加载到[ds:bx]即[ds:0x0000]中
    call read_hard_disk_0                       ;过程调用

    ;以下判断整个用户程序多大
    ;按照和用户程序约定的
    ;4个字节程序总长度
    ;2个字节代码段入口段内偏地址
    ;4个字节代码段距程序首地址偏移地址
    ;2个字节段重定位表项个数
    ;4个字节程序段距程序首地址偏移地址，一共表项个数个
    mov dx, [2]                                 ;取出用户程序大小的高16位
    mov ax, [0]                                 ;取出用户程序大小的低16位
    mov bx, 512                                 ;每个扇区512字节
    div bx                                      ;计算程序占几个扇区
                                                ;商在ax中，余数在dx中
    cmp dx, 0                                   ;判断是否除尽
    jnz @1
    dec ax                                      ;已读取一个扇区，扇区数减一

    @1:
    cmp ax, 0                                   ;全部扇区已加载
    jz direct

    ;读取剩余的扇区
    push ds                                     ;以下要用到并改变DS寄存器，压栈ds，保存状态
    mov cx, ax                                  ;循环次数（剩余扇区数）

    @2:
    mov ax, ds
    add ax, 0x20                                ;将后512B作为新的段地址，即读取到的用户程序，每512B一个段，防止用户程序大于64K，一个段塞不下的情况
    mov ds, ax

    xor bx, bx                                  ;每个段，偏移地址为0x0000
    inc si                                      ;下一个逻辑扇区
    call read_hard_disk_0                       ;继续载入一个指定扇区
    loop @2                                     ;循环读，直到读完整个用户程序

    pop ds                                      ;恢复数据段基址到用户程序头部段

    ;计算用户程序入口点代码段基址
    direct:
    ;按照和用户程序约定的
    ;4个字节程序总长度
    ;2个字节代码段入口段内偏地址
    ;4个字节代码段距程序首地址偏移地址
    ;2个字节段重定位表项个数
    ;4个字节程序段距程序首地址偏移地址，一共表项个数个
    mov dx, [0x08]                              ;读取用户程序代码段距程序首地址偏移地址的高16位
    mov ax, [0x06]                              ;读取用户程序代码段距程序首地址偏移地址的低16位
    call calc_segment_base
    mov [0x06], ax                              ;回填重定位后的入口点代码段基址

    ;开始处理段重定位表
    mov cx, [0x0a]                              ;需要重定位的表项个数
    mov bx, 0x0c                                ;重定位表基址

    realloc:                                    ;对用户程序进行重定位
    mov dx, [bx+0x02]                           ;取得第一个段重定位表项的高16位
    mov ax, [bx]                                ;取得第一个段重定位表项的低16位
    call calc_segment_base
    mov [bx], ax                                ;回填用户程序各段的基址
    add bx, 4                                   ;下一个重定位项
    loop realloc

    jmp far [0x04]                              ;转移到用户程序

;-------------------------------------------------------------------------------
    read_hard_disk_0:                           ;从磁盘中读取一个指定的逻辑扇区
                                                ;约定用户程序起始逻辑扇区号高16位存放在di中，低16位存放在si中
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
            jnz .waits                          ;不忙，且硬盘已准备好数据传输

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

        add ax, [cs:phy_base]                   ;加载用户程序后的用户程序代码段在当前段的段内偏移量的低16位，可能会有进位，有进位的话cf=1
        ;adc是带进位的加法
        adc dx, [cs:phy_base+0x02]              ;加载用户程序后的用户程序代码段在当前段的段内偏移量的高4位
        ;shr逻辑右移指令
        shr ax, 4
        ;ror循环右移指令
        ror dx, 4
        and dx, 0xf000
        or ax, dx                               ;ax中为逻辑段地址

        pop dx

        ret
;-------------------------------------------------------------------------------

    phy_base:           dd 0x8000               ;用户程序被加载的物理起始地址（绝对地址）
times 510-($-$$)        db 0
                        db 0x55, 0xaa