    app_lba_start           equ 100             ;声明常数（用户程序起始逻辑扇区号）
    ;以下常量定义部分。内核的大部分内容都应当固定
    video_data_seg_sel      equ 0000000000001_000B  ;显卡数据段选择子#1
    gdt_data_seg_sel        equ 0000000000010_000B  ;GDT数据段选择子#2
    mem_data_seg_sel        equ 0000000000011_000B  ;内存数据段选择子#3
    kernel_text_seg_sel     equ 0000000000111_000B  ;内核代码段选择子#7
    kernel_routine_seg_sel  equ 0000000001000_000B  ;内核例程段选择子#8
    kernel_data_seg_sel     equ 0000000001001_000B  ;内核数据段选择子#9
    kernel_stack_seg_sel    equ 0000000001010_000B  ;内核堆栈段选择子#10
SECTION head vstart=0 align=16                  ;定义内核程序头部段
    program_length:     dd program_end          ;程序总长度
    ;段重定位表
    realloc_tbl_begin:
    text_segment:       dd section.text.start   ;代码段距程序首地址偏移地址
    routine_segment:    dd section.routine.start;例程段距程序首地址偏移地址
    data_segment:       dd section.data.start   ;数据段距程序首地址偏移地址
    stack_segment:      dd section.stack.start  ;栈段距程序首地址偏移地址
    realloc_tbl_end:
    code_entry:         dd start                ;代码段入口段内偏移地址
                        dw kernel_text_seg_sel

SECTION text vstart=0 align=16                  ;定义代码段
    bits 32
    start:                                      ;程序入口
    mov ax, kernel_stack_seg_sel                ;初始化内核堆栈段
    mov ss, ax
    mov esp, stack_pointer

    mov ax, kernel_data_seg_sel                 ;初始化内核数据段
    mov ds, ax

    mov ax, video_data_seg_sel                  ;初始化显卡数据段
    mov es, ax

    mov ax, gdt_data_seg_sel                    ;初始化GDT数据段
    mov gs, ax

    mov ax, mem_data_seg_sel                    ;初始化内存数据段
    mov fs, ax

    call kernel_routine_seg_sel:clear

    mov ebx, message
    call kernel_routine_seg_sel:show

    mov esi, app_lba_start                      ;用户程序位于逻辑100扇区
    call load_relocate_program

    mov gs, ax
    mov [pointer_backup], esp

    push ss

    mov ax, [gs:0x1c]
    mov edx, [gs:0x20]
    mov ss, ax
    mov esp, edx

    call far [gs:0x08]

    mov ax, kernel_data_seg_sel
    mov ds, ax
    mov ax, kernel_stack_seg_sel
    mov ss, ax
    mov esp, [pointer_backup],

    hlt
;-------------------------------------------------------------------------------
    load_relocate_program:                      ;加载并重定位用户程序
                                                ;输入：ESI=起始逻辑扇区号
                                                ;返回：AX=指向用户程序头部的选择子
        push ebx
        push ecx
        push edx
        push esi
        push edi
        push ds

        mov eax, esi                            ;读取程序头部数据到内核缓冲区
        mov ebx, kernel_buffer
        call kernel_routine_seg_sel:read_hard_disk_0

        ;以下判断整个程序有多大
        mov eax, [kernel_buffer]                ;用户程序大小
        mov ebx, eax                            ;备份用户程序大小
        and ebx, 0xfffffe00                     ;将低9位置0，使之成为512的倍数
        add ebx, 512                            ;将其补为512的倍数
        test eax, 0x000001ff                    ;程序的大小正好是512的倍数吗?
        cmovnz eax, ebx                         ;不是则使用凑整的结果

        mov ecx, eax                            ;实际需要申请的内存数量
        call kernel_routine_seg_sel:allocate_memory
        mov ebx, ecx                            ;ebx -> 申请到的内存首地址
        push ebx                                ;保存该首地址

        ;计算用户程序总扇区数
        xor edx, edx
        mov ecx, 512
        div ecx
        mov ecx, eax                            ;总扇区数

        mov ax, mem_data_seg_sel                ;切换到4G内存的数据段
        mov ds, ax

        mov eax, esi                            ;起始扇区号
        .b1:
        call kernel_routine_seg_sel:read_hard_disk_0
        inc eax
        loop .b1                                ;循环读，直到读完整个用户程序

        ;建立程序头部段描述符#11
        pop edi                                 ;恢复程序装载的首地址
        mov eax, edi                            ;程序头部起始线性地址
        mov ebx, [edi+0x04]                     ;段长度
        dec ebx                                 ;段界限
        mov ecx, 0x00409200                     ;字节粒度的数据段描述符
        call kernel_routine_seg_sel:make_seg_descriptor
        call kernel_routine_seg_sel:set_up_gdt_descriptor
        mov [edi+0x04], cx

        ;建立程序代码段描述符#12
        mov eax, edi
        add eax, [edi+0x0c]                     ;代码起始线性地址
        mov ebx, [edi+0x10]                     ;段长度
        dec ebx                                 ;段界限
        mov ecx, 0x00409800                     ;字节粒度的代码段描述符
        call kernel_routine_seg_sel:make_seg_descriptor
        call kernel_routine_seg_sel:set_up_gdt_descriptor
        mov [edi+0x0c], cx

        ;建立程序数据段描述符#13
        mov eax, edi
        add eax, [edi+0x14]                     ;数据段起始线性地址
        mov ebx, [edi+0x18]                     ;段长度
        dec ebx                                 ;段界限
        mov ecx, 0x00409200                     ;字节粒度的数据段描述符
        call kernel_routine_seg_sel:make_seg_descriptor
        call kernel_routine_seg_sel:set_up_gdt_descriptor
        mov [edi+0x14], cx

        ;建立程序数据段描述符#14
        mov eax, edi
        add eax, [edi+0x1c]                     ;堆栈段起始线性地址
        mov ebx, [edi+0x20]                     ;段长度
        dec ebx                                 ;段界限
        mov ecx, 0x00409200                     ;字节粒度的数据段描述符
        call kernel_routine_seg_sel:make_seg_descriptor
        call kernel_routine_seg_sel:set_up_gdt_descriptor
        mov [edi+0x1c], cx

        mov ax, [edi+0x04]                      ;从用户头部段中取出头部段选择子

        pop ds
        pop edi
        pop esi
        pop edx
        pop ecx
        pop ebx

        ret
;-------------------------------------------------------------------------------

SECTION routine vstart=0 align=16               ;定义例程段
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
        retf
;-------------------------------------------------------------------------------
    ;显示string信息
    show:
        mov ecx, 512
        xor esi, esi

        print:
        mov dl, [ebx+esi]
        cmp dl, 0
        jz print_end
        mov [es:esi*2], dl
        mov byte [es:esi*2+1], 0x07
        inc esi
        loop print
        print_end:
        retf
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

        retf                                    ;段间返回
;-------------------------------------------------------------------------------
    allocate_memory:                            ;分配内存
                                                ;输入：ECX=希望分配的字节数
                                                ;输出：ECX=起始线性地址
        push eax
        push ebx
        mov eax, [ram_alloc]
        add eax, ecx                            ;下一次分配时的起始地址

        ;这里应当有检测可用内存数量的指令
        mov ecx, [ram_alloc]                    ;返回分配的起始地址

        mov ebx, eax                            ;备份分配的起始地址
        and ebx, 0xfffffffc                     ;准备进行4字节对齐
        add ebx, 4                              ;强制对齐
        test eax, 0x00000003                    ;下次分配的起始地址最好是4字节对齐
        cmovnz eax, ebx                         ;如果没有对齐，则强制对齐
        mov [ram_alloc], eax                    ;下次从该地址分配内存
                                                ;cmovcc指令可以避免控制转移
        pop ebx
        pop eax

        retf
;-------------------------------------------------------------------------------
    make_seg_descriptor:                        ;构造存储器和系统的段描述符
                                                ;输入：EAX=线性基地址
                                                ;      EBX=段界限
                                                ;      ECX=属性。各属性位都在原始
                                                ;          位置，无关的位清零
                                                ;返回：EDX:EAX=描述符
        mov edx, eax
        shl eax, 16
        or ax, bx                               ;描述符前32位(EAX)构造完毕

        and edx, 0xffff0000                     ;清除基地址中无关的位
        rol edx, 8
        bswap edx                               ;装配基址的31~24和23~16  (80486+)

        xor bx, bx
        or edx, ebx                             ;装配段界限的高4位

        or edx, ecx                             ;装配属性

        retf
;-------------------------------------------------------------------------------
    set_up_gdt_descriptor:                      ;在GDT内安装一个新的描述符
                                                ;输入：EDX:EAX=描述符
                                                ;输出：CX=描述符的选择子
        push eax
        push ebx
        push edx

        push ds

        mov ebx, kernel_data_seg_sel            ;切换到核心数据段
        mov ds, ebx

        sgdt [pgdt]                             ;在内存中存储GDTR的内容

        movzx ebx, word [pgdt]                  ;GDT界限
        inc bx                                  ;GDT总字节数，也是下一个描述符偏移
        add ebx, [pgdt+2]                       ;下一个描述符的线性地址

        mov [fs:ebx], eax
        mov [fs:ebx+4], edx

        add word [pgdt], 8                      ;增加一个描述符的大小

        lgdt [pgdt]                             ;对GDT的更改生效

        mov ax, [pgdt]                          ;得到GDT界限值
        xor dx, dx
        mov bx, 8
        div bx                                  ;除以8，去掉余数
        mov cx, ax
        shl cx, 3                               ;将索引号移到正确位置

        pop ds

        pop edx
        pop ebx
        pop eax

        retf
;-------------------------------------------------------------------------------

SECTION data vstart=0 align=16                  ;定义数据段
    message:            db 'kernel is running......', 0
    pgdt:
    gdt_size:           dw 0x0000
    gdt_base:           dd 0x00000000
    kernel_buffer: times 2048   db 0            ;kernel用的缓冲区
    ram_alloc:                  dd 0x00100000   ;下次分配内存时的起始地址
    pointer_backup:             dd 0            ;内核用来临时保存栈指针的位置

SECTION stack vstart=0 align=16                 ;定义堆栈段
    times 2048          db 0
    stack_pointer:

SECTION tail align=16
    program_end: