         ;�ļ�˵�����û����� 
         ;�������ڣ�2020-10-30

;===============================================================================
SECTION header vstart=0

         program_length   dd program_end          ;�����ܳ���#0x00
         entry_point      dd start                ;������ڵ�#0x04
         salt_position    dd salt                 ;SALT����ʼƫ����#0x08
         salt_items       dd (header_end-salt)/256 ;SALT��Ŀ��#0x0C

;-------------------------------------------------------------------------------
         ;���ŵ�ַ������
         salt:                                     ;#0x28
         PrintString      db  '@PrintString'
                     times 256-($-PrintString) db 0
                     
         TerminateProgram db  '@TerminateProgram'
                     times 256-($-TerminateProgram) db 0
                     
         ReadDiskData     db  '@ReadDiskData'
                     times 256-($-ReadDiskData) db 0

         InitTaskSwitch   db  '@InitTaskSwitch'
                     times 256-($-InitTaskSwitch) db 0
                 
         malloc           db  '@malloc'
                     times 256-($-malloc) db 0
header_end:
  
;===============================================================================
SECTION data vfollows=header

         message_1        db  '[USER TASK]: ,,,,,,,,,,,,,,,,,,,,,,,',0x0d,0x0a,0

         reserved  times 4096*5 db 0                ;����һ���հ���������ʾ��ҳ
data_end:

;===============================================================================
      [bits 32]
;===============================================================================
SECTION code vfollows=data
start:
         ;�ڵ�ǰ�����ڵ������ַ�ռ�������ڴ�
         mov ecx,128                                ;�������128���ֽ�
         call far [malloc]
         mov ebx,ecx                                ;Ϊ�����ӡ�ַ���׼������

         ;�����ַ�����������ڴ���
         mov esi,message_1
         mov edi,ecx
         mov ecx,reserved-message_1
         cld
         repe movsb

.show:
         ;mov ebx,message_1
         call far [PrintString]
         jmp .show

code_end:

;-------------------------------------------------------------------------------
SECTION trail
;-------------------------------------------------------------------------------
program_end:
