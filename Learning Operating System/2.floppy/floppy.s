mov ax, 0xb800
mov ds, ax
mov byte [0x00], 'a'
mov byte [0x01], 0x07
mov byte [0x02], 's'
mov byte [0x03], 0x07
mov byte [0x04], 'm'
mov byte [0x05], 0x07
mov byte [0x06], ' '
mov byte [0x07], 0x07
jmp $
times 510-($-$$) db 0
db 0x55, 0xaa