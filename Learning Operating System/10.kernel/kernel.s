    ;以下常量定义部分。内核的大部分内容都应当固定
    video_data_seg_sel equ 0000000000100_000B   ;显卡数据段选择子
    kernel_text_seg_sel equ 0000000000111_000B  ;内核代码段选择子
    kernel_data_seg_sel equ 0000000001000_000B  ;内核数据段选择子
    kernel_stack_seg_sel equ 0000000001001_000B ;内核堆栈段选择子
SECTION head vstart=0 align=16                  ;定义用户程序头部段
    program_length:     dd program_end          ;程序总长度
    ;段重定位表
    realloc_tbl_begin:
    text_segment:       dd section.text.start   ;代码段距程序首地址偏移地址
    data_segment:       dd section.data.start   ;数据段距程序首地址偏移地址
    stack_segment:      dd section.stack.start  ;栈段距程序首地址偏移地址
    realloc_tbl_end:
    code_entry:         dd start                ;代码段入口段内偏移地址
                        dw kernel_text_seg_sel

SECTION text vstart=0 align=16                  ;定义代码段
    bits 32
    start:                                      ;程序入口
    mov ax, kernel_data_seg_sel                 ;初始化内核数据段#8
    mov ds, ax

    mov ax, video_data_seg_sel                  ;初始化显卡数据段#4
    mov es, ax

    mov ax, kernel_stack_seg_sel
    mov ss, ax
    mov esp, stack_pointer

    call clear

    mov ebx, message
    call show

    hlt
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
        ret
;-------------------------------------------------------------------------------
SECTION data vstart=0 align=16                  ;定义数据段
    message:            db 'kernel is running......', 0

SECTION stack vstart=0 align=16                 ;定义栈段
    times 2048          db 0
    stack_pointer:

SECTION tail align=16
    program_end: