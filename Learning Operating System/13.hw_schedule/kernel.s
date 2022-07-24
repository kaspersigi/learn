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

    mov ebx, message_1
    call kernel_routine_seg_sel:print

    ;以下开始安装为整个系统服务的调用门。特权级之间的控制转移必须使用门
    mov edi, salt_begin                         ;C-SALT表的起始位置
    mov ecx, salt_items                         ;C-SALT表的条目数量

    .b0:
    push ecx
    mov eax, [edi+256]                          ;该条目入口点的32位偏移地址
    mov bx, [edi+260]                           ;该条目入口点的段选择子
    mov cx, 1_11_0_1100_00000000B               ;特权级3的调用门(3以上的特权级才允许访问)，0个参数(因为用寄存器传递参数，而没有用栈)
    call kernel_routine_seg_sel:make_gate_descriptor
    call kernel_routine_seg_sel:set_up_gdt_descriptor
    or cx, 0000000000000_000B                   ;设置选择子rpl为0
    mov [edi+260], cx                           ;将返回的门描述符选择子回填
    add edi, salt_item_length                   ;指向下一个C-SALT条目
    pop ecx
    loop .b0

    ;对门进行测试
    mov ebx, message_2
    call far [salt_1+256]                       ;通过门显示信息(偏移量将被忽略)

    ;为内核任务创建任务控制块TCB
    mov ecx, 0x46
    call kernel_routine_seg_sel:allocate_memory
    call append_to_tcb_link                     ;将此TCB添加到TCB链中
    mov esi, ecx

    ;为内核任务的TSS分配内存空间
    mov ecx, 104                                ;为该任务的TSS分配内存
    call kernel_routine_seg_sel:allocate_memory
    mov [fs:esi+0x14], ecx                      ;在内核TCB中保存TSS基地址

    ;在内核任务(程序管理器)的TSS中设置必要的项目
    mov word [fs:ecx+96], 0                     ;没有LDT。处理器允许没有LDT的任务
    mov word [fs:ecx+102], 103                  ;没有I/O位图。0特权级事实上不需要，103是该TSS段的段界限值，表示不需要I/O映射基地址，即没有I/O许可位映射图
    mov word [fs:ecx+0], 0                      ;反向链=0
    mov dword [fs:ecx+28], 0                    ;登记CR3(PDBR)
    mov word [fs:ecx+100], 0                    ;T=0
                                                ;不需要0、1、2特权级堆栈。0特级不会向低特权级转移控制

    ;创建内核任务的TSS描述符，并安装到GDT中
    mov eax, ecx                                ;TSS的起始线性地址
    mov ebx, 103                                ;段长度（界限）
    mov ecx, 0x00008900                         ;TSS描述符，特权级0
    call kernel_routine_seg_sel:make_seg_descriptor
    call kernel_routine_seg_sel:set_up_gdt_descriptor
    mov word [fs:esi+0x18], cx                  ;登记TSS选择子到TCB
    ;0x04处为任务状态字，0x0000表示任务处于就绪态，0xffff表示任务处于运行态，0x3333表示任务处于结束状态
    mov word [fs:esi+0x04], 0xffff              ;任务的状态为“忙”

    ;任务寄存器TR中的内容是任务存在的标志，该内容也决定了当前任务是谁。
    ;下面的指令为当前正在执行的0特权级任务“程序管理器”后补手续（TSS）。
    ltr cx

    mov ebx, message_3
    call kernel_routine_seg_sel:print

    mov ax, cs                                  ;取CS段选择子
    and al, 0000_0011B                          ;取cpl
    or al, 0x30                                 ;0字符0x30，由于cpl只有0，1，2，3相当于加法
    mov [cpl], al
    mov ebx, message_0
    call kernel_routine_seg_sel:print

    ;创建用户任务TCB
    mov ecx, 0x46                               ;设计tcb大小为70字节
    call kernel_routine_seg_sel:allocate_memory ;为tcb分配内存
    mov word [fs:ecx+0x04], 0                   ;任务状态：就绪态
    call append_to_tcb_link                     ;将tcb添加到链表尾部

    ;一共两个参数，用户程序起始逻辑扇区号4B，新tcb线性基地址4B
    push dword app_lba_start                    ;用堆栈向过程load_relocate_program传递参数
    push ecx                                    ;压栈保存新tcb线性基地址
    ;过程调用压入eip 4B
    call load_relocate_program

    .do_switch:
    ;主动切换到其它任务，给它们运行的机会
    call kernel_routine_seg_sel:initiate_task_switch

    mov ebx, message_4
    call kernel_routine_seg_sel:print

    ;清理已经终止的任务，并回收它们占用的资源
    call kernel_routine_seg_sel:do_task_clean

    mov eax, [tcb_chain]
    .find_ready:
    cmp word [es:eax+0x04], 0x0000              ;还有处于就绪状态的任务？
    jz .do_switch                               ;有，继续执行任务切换
    mov eax, [es:eax]
    or eax, eax                                 ;还有用户任务吗？
    jnz .find_ready                             ;一直搜索到链表尾部

    ;已经没有可以切换的任务，停机
    hlt
;-------------------------------------------------------------------------------
    load_relocate_program:                      ;加载并重定位用户程序
                                                ;输入:PUSH 逻辑扇区号
                                                ;    PUSH tcb基地址
                                                ;输出:无
        pushad                                  ;依次push eax,ecx,edx,ebx,esp(pushad前的值),ebp,esi,edi
        push ds
        push es

        mov ebp, esp                            ;为访问通过堆栈传递的参数做准备
        mov cx, mem_data_seg_sel
        mov es, cx
        mov esi,[ebp+11*4]                      ;从堆栈中取得tcb的基地址
                                                ;如果仅由bp、epb提供偏移量寻址，则默认段寄存器为ss

        ;以下申请创建LDT所需要的内存
        mov ecx, 160                            ;允许安装20个LDT描述符
                                                ;一个段描述符，64位，8字节
        call kernel_routine_seg_sel:allocate_memory
        mov [es:esi+0x0c], ecx                  ;登记LDT基地址到TCB中
        mov word [es:esi+0x0a], 0xffff          ;登记LDT初始的界限到TCB中

        ;以下开始加载用户程序
        mov ax, kernel_data_seg_sel
        mov ds, ax                              ;切换DS到内核数据段

        mov eax,[ebp+12*4]                      ;从堆栈中取出用户程序起始扇区号
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
        mov [es:esi+0x06], ecx                  ;登记程序加载基地址到tcb中

        mov ebx, ecx                            ;ebx -> 申请到的内存首地址

        ;计算用户程序总扇区数
        xor edx, edx
        mov ecx, 512
        div ecx
        mov ecx, eax                            ;总扇区数

        mov ax, mem_data_seg_sel                ;切换到4G内存的数据段
        mov ds, ax

        mov eax, [ebp+12*4]                     ;起始扇区号
        .b1:
        call kernel_routine_seg_sel:read_hard_disk_0
        inc eax
        loop .b1                                ;循环读，直到读完整个用户程序

        mov edi,[es:esi+0x06]                   ;获得程序加载基地址

        ;建立程序头部段描述符#0
        mov eax, edi                            ;程序头部起始线性地址
        mov ebx, [edi+0x04]                     ;段长度
        dec ebx                                 ;段界限
        mov ecx, 0x0040f200                     ;字节粒度的数据段描述符
        call kernel_routine_seg_sel:make_seg_descriptor

        ;安装头部段描述符到LDT中
        mov ebx, esi                            ;tcb的基地址
        call kernel_routine_seg_sel:fill_descriptor_in_ldt
        or cx, 0000000000000_011B               ;设置选择子rpl为3
        mov [es:esi+0x44], cx                   ;登记头部段选择子到tcb中
        mov [edi+0x04], cx                      ;回填段选择子到头部段中

        ;建立程序代码段描述符#1
        mov eax, edi
        add eax, [edi+0x0c]                     ;代码起始线性地址
        mov ebx, [edi+0x10]                     ;段长度
        dec ebx                                 ;段界限
        mov ecx, 0x0040f800                     ;字节粒度的代码段描述符
        call kernel_routine_seg_sel:make_seg_descriptor

        ;安装代码段描述符到LDT中
        mov ebx, esi                            ;tcb的基地址
        call kernel_routine_seg_sel:fill_descriptor_in_ldt
        or cx, 0000000000000_011B               ;设置选择子rpl为3
        mov [edi+0x0c], cx                      ;回填段选择子到代码段中

        ;建立程序数据段描述符#2
        mov eax, edi
        add eax, [edi+0x14]                     ;数据段起始线性地址
        mov ebx, [edi+0x18]                     ;段长度
        dec ebx                                 ;段界限
        mov ecx, 0x0040f200                     ;字节粒度的数据段描述符
        call kernel_routine_seg_sel:make_seg_descriptor

        ;安装数据段描述符到LDT中
        mov ebx, esi                            ;tcb的基地址
        call kernel_routine_seg_sel:fill_descriptor_in_ldt
        or cx, 0000000000000_011B               ;设置选择子rpl为3
        mov [edi+0x14], cx

        ;建立程序堆栈段描述符#3
        mov eax, edi
        add eax, [edi+0x1c]                     ;堆栈段起始线性地址
        mov ebx, [edi+0x20]                     ;段长度
        dec ebx                                 ;段界限
        mov ecx, 0x0040f200                     ;字节粒度的数据段描述符
        call kernel_routine_seg_sel:make_seg_descriptor

        ;安装堆栈段描述符到LDT中
        mov ebx, esi                            ;tcb的基地址
        call kernel_routine_seg_sel:fill_descriptor_in_ldt
        or cx, 0000000000000_011B               ;设置选择子rpl为3
        mov [edi+0x1c], cx

        ;重定位SALT
        mov ax, mem_data_seg_sel                ;这里和前一章不同，头部段描述符
        mov es, ax                              ;已安装，但还没有生效，故只能通过4GB段访问用户程序头部
        mov ax, kernel_data_seg_sel
        mov ds, ax

        cld

        mov ecx, [es:edi+0x24]                  ;U-SALT条目数(通过访问4GB段取得)
        add edi, 0x28                           ;U-SALT在4GB段内的偏移

        .b2:                                    ;外循环，依次便利用户程序的salt条目
        push ecx
        push edi

        mov ecx, salt_items                     ;内循环次数
        mov esi, salt_begin

        .b3:
        push esi
        push edi
        push ecx

        mov ecx, 64                             ;检索表中，每条目的比较次数
        repe cmpsd                              ;每次比较4字节
        jnz .b4
        mov eax, [esi]                          ;若匹配，edi恰好指向其后的地址数据
        mov [es:edi-256], eax                   ;将字符串改写成偏移地址
        mov ax, [esi+4]
        or ax, 0000000000000_011B               ;设置选择子rpl为3
        mov [es:edi-252], ax                    ;以及段选择子
        .b4:

        pop ecx
        pop edi
        pop esi
        add esi, salt_item_length
        loop .b3

        pop edi
        pop ecx
        add edi, 256
        loop .b2

        mov esi, [ebp+11*4]                     ;从堆栈中取得tcb的基地址

        ;创建0特权级堆栈
        mov ecx, 1024                           ;设置堆栈大小为1024B
        mov [es:esi+0x1a], ecx                  ;登记0特权级栈界限到TCB
        mov dword [es:esi+0x24], ecx            ;登记0特权级堆栈初始ESP到TCB
        call kernel_routine_seg_sel:allocate_memory
        mov [es:esi+0x1e], ecx                  ;登记0特权级堆栈基地址到TCB
        mov eax, ecx
        mov ebx, 1023                           ;段长度（界限）
        mov ecx, 0x00409200                     ;字节粒度，读写，特权级0
        call kernel_routine_seg_sel:make_seg_descriptor
        mov ebx, esi                            ;TCB的基地址
        call kernel_routine_seg_sel:fill_descriptor_in_ldt
        or cx, 0000000000000_000B               ;设置选择子rpl为0
        mov [es:esi+0x22], cx                   ;登记0特权级堆栈选择子到TCB

        ;创建1特权级堆栈
        mov ecx, 1024                           ;设置堆栈大小为1024B
        mov [es:esi+0x28], ecx                  ;登记1特权级栈界限到TCB
        mov dword [es:esi+0x32], ecx            ;登记1特权级堆栈初始ESP到TCB
        call kernel_routine_seg_sel:allocate_memory
        mov [es:esi+0x2c], ecx                  ;登记1特权级堆栈基地址到TCB
        mov eax, ecx
        mov ebx, 1023                           ;段长度（界限）
        mov ecx, 0x0040b200                     ;字节粒度，读写，特权级0
        call kernel_routine_seg_sel:make_seg_descriptor
        mov ebx, esi                            ;TCB的基地址
        call kernel_routine_seg_sel:fill_descriptor_in_ldt
        or cx, 0000000000000_001B               ;设置选择子rpl为1
        mov [es:esi+0x30], cx                   ;登记1特权级堆栈选择子到TCB

        ;创建2特权级堆栈
        mov ecx, 1024                           ;设置堆栈大小为1024B
        mov [es:esi+0x36], ecx                  ;登记2特权级栈界限到TCB
        mov dword [es:esi+0x40], ecx            ;登记2特权级堆栈初始ESP到TCB
        call kernel_routine_seg_sel:allocate_memory
        mov [es:esi+0x3a], ecx                  ;登记2特权级堆栈基地址到TCB
        mov eax, ecx
        mov ebx, 1023                           ;段长度（界限）
        mov ecx, 0x0040d200                     ;字节粒度，读写，特权级0
        call kernel_routine_seg_sel:make_seg_descriptor
        mov ebx, esi                            ;TCB的基地址
        call kernel_routine_seg_sel:fill_descriptor_in_ldt
        or cx, 0000000000000_010B               ;设置选择子rpl为2
        mov [es:esi+0x3e], cx                   ;登记2特权级堆栈选择子到TCB

        ;在GDT中登记LDT描述符
        mov eax, [es:esi+0x0c]                  ;LDT的起始线性地址
        movzx ebx, word [es:esi+0x0a]           ;LDT段界限
        mov ecx, 0x00008200                     ;LDT描述符，特权级0
        call kernel_routine_seg_sel:make_seg_descriptor
        call kernel_routine_seg_sel:set_up_gdt_descriptor
        mov [es:esi+0x10], cx                   ;登记LDT选择子到tcb中

        ;创建用户程序的TSS
        mov ecx, 104                            ;tss的基本尺寸
        mov [es:esi+0x12], cx
        dec word [es:esi+0x12]                  ;登记TSS界限值到TCB
        call kernel_routine_seg_sel:allocate_memory
        mov [es:esi+0x14], ecx                  ;登记TSS基地址到TCB

        ;登记基本的TSS表格内容
        ;其中最重要的是CS，EIP，IO许可位映射区，三个特权级堆栈，LDT段选择子
        mov word [es:ecx+0], 0                  ;反向链=0

        mov edx, [es:esi+0x24]                  ;登记0特权级堆栈初始ESP
        mov [es:ecx+4], edx                     ;到TSS中

        mov dx, [es:esi+0x22]                   ;登记0特权级堆栈段选择子
        mov [es:ecx+8], dx                      ;到TSS中

        mov edx, [es:esi+0x32]                  ;登记1特权级堆栈初始ESP
        mov [es:ecx+12], edx                    ;到TSS中

        mov dx, [es:esi+0x30]                   ;登记1特权级堆栈段选择子
        mov [es:ecx+16], dx                     ;到TSS中

        mov edx, [es:esi+0x40]                  ;登记2特权级堆栈初始ESP
        mov [es:ecx+20], edx                    ;到TSS中

        mov dx, [es:esi+0x3e]                   ;登记2特权级堆栈段选择子
        mov [es:ecx+24], dx                     ;到TSS中

        mov dx, [es:esi+0x10]                   ;登记任务的LDT选择子到tss中
        mov [es:ecx+96], dx

        mov dx, [es:esi+0x12]                   ;登记任务的I/O位图偏移
        mov [es:ecx+102], dx                    ;到TSS中

        mov word [es:ecx+100], 0                ;T=0

        mov dword [es:ecx+28], 0                ;登记CR3(PDBR)

        ;访问用户程序头部，获取数据填充TSS
        mov ebx, [ebp+11*4]                     ;从堆栈中取得TCB的基地址
        mov edi, [es:ebx+0x06]                  ;用户程序加载的基地址

        mov edx, [es:edi+0x08]                  ;登记程序入口点（EIP）
        mov [es:ecx+32], edx                    ;到TSS

        mov dx, [es:edi+0x0c]                   ;登记程序代码段（CS）选择子
        mov [es:ecx+76], dx                     ;到TSS中

        mov dx, [es:edi+0x1c]                   ;登记程序堆栈段（SS）选择子
        mov [es:ecx+80], dx                     ;到TSS中

        mov dx, [es:edi+0x04]                   ;登记程序数据段（DS）选择子
        mov word [es:ecx+84], dx                ;到TSS中。注意，它指向程序头部段

        mov word [es:ecx+72], 0                 ;TSS中的ES=0

        mov word [es:ecx+88], 0                 ;TSS中的FS=0

        mov word [es:ecx+92], 0                 ;TSS中的GS=0

        pushfd
        pop dword [es:ecx+36]                   ;EFLAGS

        ;在GDT中登记TSS描述符
        mov eax, [es:esi+0x14]                  ;TSS的起始线性地址
        movzx ebx, word [es:esi+0x12]           ;段长度（界限）
        mov ecx, 0x00008900                     ;TSS描述符，特权级0
        call kernel_routine_seg_sel:make_seg_descriptor
        call kernel_routine_seg_sel:set_up_gdt_descriptor
        mov [es:esi+0x18], cx                   ;登记TSS选择子到TCB

        pop es
        pop ds
        popad                                   ;以相反顺序弹栈，但是忽略esp
                                                ;依次出栈edi,esi,ebp,ebx,edx,ecx,eax
        ret 8                                   ;esp+8，丢弃两个压栈的数据
;-------------------------------------------------------------------------------
    append_to_tcb_link:                         ;在tcb_chain上追加tcb
                                                ;输入：ecx是新tcb的线性基地址
        push eax
        push edx
        push ds
        push es

        mov ax, kernel_data_seg_sel             ;令DS指向内核数据段
        mov ds, ax
        mov ax, mem_data_seg_sel                ;令ES指向内存4GB数据段
        mov es, ax

        mov dword [es:ecx+0x00], 0              ;将新tcb的指针域清0，来指示这是最后一个tcb

        mov eax, [tcb_chain]                    ;取得第一个tcb的指针域
        or eax, eax                             ;链表为空？
        jz .no_tcb

        .search:
        mov edx, eax                            ;备份当前tcb的指针域
        mov eax, [es:edx+0x00]                  ;取得当前tcb的指针域的下一个tcb的指针域
        or eax, eax                             ;当前tcb的下一个tcb是否为空
        jnz .search                             ;不是则继续搜索

        mov [es:edx+0x00], ecx                  ;将新tcp挂载到链表末尾处
        jmp .ret

        .no_tcb:
        mov [tcb_chain], ecx                    ;若为空表，直接令链表头指针指向新tcb

        .ret:
        pop es
        pop ds
        pop edx
        pop eax
        ret
;-------------------------------------------------------------------------------

SECTION routine vstart=0 align=16               ;定义例程段
;-------------------------------------------------------------------------------
    ;字符串显示例程
    print:                                      ;显示0终止的字符串并移动光标
                                                ;输入：DS:EBX=串地址
        push ecx
        .getc:
        mov cl, [ebx]
        or cl, cl
        jz .exit
        call put_char
        inc ebx
        jmp .getc

        .exit:
        pop ecx
        retf                                    ;段间返回
;-------------------------------------------------------------------------------
    put_char:                                   ;在当前光标处显示一个字符,并推进光标。仅用于段内调用
                                                ;输入：CL=字符ASCII码
        pushad

        ;以下取当前光标位置
        mov dx, 0x3d4
        mov al, 0x0e
        out dx, al
        inc dx                                  ;0x3d5
        in al, dx                               ;高字
        mov ah, al

        dec dx                                  ;0x3d4
        mov al, 0x0f
        out dx, al
        inc dx                                  ;0x3d5
        in al, dx                               ;低字
        mov bx, ax                              ;BX=代表光标位置的16位数

        cmp cl, 0x0d                            ;回车符？
        jnz .put_0a
        mov ax, bx
        mov bl, 80
        div bl
        mul bl
        mov bx, ax
        jmp .set_cursor

        .put_0a:
        cmp cl, 0x0a                            ;换行符？
        jnz .put_other
        add bx, 80
        jmp .roll_screen

        .put_other:                             ;正常显示字符
        push es
        mov eax, video_data_seg_sel             ;0xb8000段的选择子
        mov es, eax
        shl bx,1
        mov [es:bx], cl
        pop es

        ;以下将光标位置推进一个字符
        shr bx, 1
        inc bx

        .roll_screen:
        cmp bx, 2000                            ;光标超出屏幕？滚屏
        jl .set_cursor

        push bx                                 ;为了修改原书程序的逻辑问题，新增
        push ds
        push es
        mov eax, video_data_seg_sel
        mov ds, eax
        mov es, eax
        cld
        mov esi, 0xa0                           ;小心！32位模式下movsb/w/d
        mov edi, 0x00                           ;使用的是esi/edi/ecx
        mov ecx, 1920
        rep movsw
        mov bx, 3840                            ;清除屏幕最底一行
        mov ecx, 80                             ;32位程序应该使用ECX

        .cls:
        mov word[es:bx], 0x0720
        add bx, 2
        loop .cls

        pop es
        pop ds

        pop bx
        sub bx, 80

        .set_cursor:
        mov dx, 0x3d4
        mov al, 0x0e
        out dx, al
        inc dx                                  ;0x3d5
        mov al, bh
        out dx, al
        dec dx                                  ;0x3d4
        mov al, 0x0f
        out dx, al
        inc dx                                  ;0x3d5
        mov al, bl
        out dx, al

        popad
        ret
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
    make_gate_descriptor:                       ;构造门的描述符（调用门等）
                                                ;输入：EAX=门代码在段内偏移地址
                                                ;       BX=门代码所在段的选择子
                                                ;       CX=段类型及属性等（各属性位都在原始位置）
                                                ;返回：EDX:EAX=完整的描述符
        push ebx
        push ecx

        mov edx, eax
        and edx, 0xffff0000                     ;得到偏移地址高16位
        or dx, cx                               ;组装属性部分到EDX

        and eax, 0x0000ffff                     ;得到偏移地址低16位
        shl ebx, 16
        or eax, ebx                             ;组装段选择子部分

        pop ecx
        pop ebx
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
    fill_descriptor_in_ldt:                     ;在LDT内安装一个新的描述符
                                                ;输入：edx:eax=描述符
                                                ;     ebx=tcb基地址
                                                ;输出：cx=描述符的选择子
        push eax
        push edx
        push edi
        push ds

        mov cx, mem_data_seg_sel                ;令ds指向内存4GB数据段
        mov ds, cx

        mov edi, [ebx+0x0c]                     ;获得LDT基地址

        xor ecx, ecx
        mov cx, [ebx+0x0a]                      ;获得LDT界限
        inc cx                                  ;LDT的总字节数，即新描述符偏移地址

        mov [edi+ecx+0x00], eax
        mov [edi+ecx+0x04], edx                 ;安装描述符

        add cx, 8
        dec cx                                  ;得到新的LDT界限值

        mov [ebx+0x0a], cx                      ;更新LDT界限值到TCB

        mov ax, cx
        xor dx, dx
        mov cx, 8
        div cx

        mov cx, ax
        shl cx, 3                               ;左移3位，并且
        or cx, 0000_0000_0000_0100B             ;使TI位=1，指向LDT，最后使RPL=00

        pop ds
        pop edi
        pop edx
        pop eax

        retf
;-------------------------------------------------------------------------------
    initiate_task_switch:                       ;主动发起任务切换
        pushad
        push ds
        push es

        mov eax, kernel_data_seg_sel
        mov es,eax

        mov eax, mem_data_seg_sel
        mov ds, eax

        mov eax, [es:tcb_chain]

        ;搜索状态为忙（当前任务）的节点
        .b0:
        cmp word [eax+0x04], 0xffff
        cmove esi, eax                          ;找到忙的节点，ESI=节点的线性地址
        jz .b1
        mov eax, [eax]
        jmp .b0

        ;从当前节点继续搜索就绪任务的节点
        .b1:
        mov ebx, [eax]
        or ebx, ebx
        jz .b2                                  ;到链表尾部也未发现就绪节点，从头找
        cmp word [ebx+0x04], 0x0000
        cmove edi, ebx                          ;已找到就绪节点，EDI=节点的线性地址
        jz .b3
        mov eax, ebx
        jmp .b1

        .b2:
        mov ebx, [es:tcb_chain]                 ;EBX=链表首节点线性地址
        .b20:
        cmp word [ebx+0x04], 0x0000
        cmove edi, ebx                          ;已找到就绪节点，EDI=节点的线性地址
        jz .b3
        mov ebx, [ebx]
        or ebx, ebx
        jz .return                              ;链表中已经不存在空闲任务，返回
        jmp .b20

        ;就绪任务的节点已经找到，准备切换到该任务
        .b3:
        not word [esi+0x04]                     ;将忙状态的节点改为就绪状态的节点
        not word [edi+0x04]                     ;将就绪状态的节点改为忙状态的节点
        jmp far [edi+0x14]                      ;通过jmp far进行硬件任务切换
                                                ;取得内存中的6个字节，现在低4字节是tss基地址（其实是什么无所谓，不做要求），高2字节是tss段选择子。cpu识别到选择子是tss段选择子后，忽略基地址，并执行任务切换

        .return:                                ;切换任务后从这里继续执行
        pop es
        pop ds
        popad

        retf
;-------------------------------------------------------------------------------
    terminate_current_task:                     ;终止当前任务
                                                ;注意，执行此例程时，当前任务仍在运中。此例程其实也是当前任务的一部分
        mov eax, kernel_data_seg_sel
        mov es,eax

        mov eax, mem_data_seg_sel
        mov ds, eax

        mov eax, [es:tcb_chain]
                                                ;EAX=首节点的线性地址
        ;搜索状态为忙（当前任务）的节点
        .s0:
        cmp word [eax+0x04], 0xffff
        jz .s1                                  ;找到忙的节点，EAX=节点的线性地址
        mov eax, [eax]
        jmp .s0

        ;将状态为忙的节点改成终止状态
        .s1:
        mov word [eax+0x04], 0x3333

        ;搜索就绪状态的任务
        mov ebx, [es:tcb_chain]                 ;EBX=链表首节点线性地址
        .s2:
        cmp word [ebx+0x04], 0x0000
        jz .s3                                  ;已找到就绪节点，EBX=节点的线性地址
        mov ebx, [ebx]
        jmp .s2

        ;就绪任务的节点已经找到，准备切换到该任务
        .s3:
        not word [ebx+0x04]                     ;将就绪状态的节点改为忙状态的节点
        jmp far [ebx+0x14]                      ;任务切换
;-------------------------------------------------------------------------------
    do_task_clean:                              ;清理已经终止的任务并回收资源

        ;搜索TCB链表，找到状态为终止的节点
        ;将节点从链表中拆除
        ;回收任务占用的各种资源（可以从它的TCB中找到）

        retf
;-------------------------------------------------------------------------------

SECTION data vstart=0 align=16                  ;定义数据段
    message_0:          db '[Kernel Task]: I am run at CPL=',
    cpl:                db 0
                        db '.....', 0x0d, 0x0a, 0
    message_1:          db '[Kernel]: Kernel is running......', 0x0d, 0x0a, 0
    message_2:          db '[Kernel]: Testing call gate......', 0x0d, 0x0a, 0
    message_3:          db '[Kernel Task]: Kernel task is running......', 0x0d, 0x0a, 0
    message_4:          db '[Kernel Task]: return kernel task......', 0x0d, 0x0a, 0

    pgdt:
    gdt_size:           dw 0x0000
    gdt_base:           dd 0x00000000
    kernel_buffer: times 2048   db 0            ;kernel用的缓冲区
    ram_alloc:                  dd 0x00100000   ;下次分配内存时的起始地址
    pointer_backup:             dd 0            ;内核用来临时保存栈指针的位置
    ;TCB chain
    tcb_chain:                  dd 0            ;tcb_chain的头指针
                                                ;整个tcb_chain存放在4G内存空间的段中
    ;符号地址检索表
    salt_begin:
    salt_1:                     db "@print"
    times 256-($-salt_1)        db 0
                                dd print
                                dw kernel_routine_seg_sel

    salt_2:                     db "@init_task_switch"
    times 256-($-salt_2)        db 0
                                dd initiate_task_switch
                                dw kernel_routine_seg_sel

    salt_3:                     db "@terminate_current_task"
    times 256-($-salt_3)        db 0
                                dd terminate_current_task
                                dw kernel_routine_seg_sel

    salt_end:
    salt_length                 equ salt_end-salt_begin
    salt_items                  equ 3
    salt_item_length            equ salt_length/salt_items

SECTION stack vstart=0 align=16                 ;定义堆栈段
    times 2048          db 0
    stack_pointer:

SECTION tail align=16
    program_end: