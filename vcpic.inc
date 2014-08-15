; f/One32 32-bit DOS Extender
; vcpic.inc: VCPI client functions

check_vcpi:
	push es
	xor ax,ax
	mov es,ax
	mov ax,[es:67h*4+2]
	test ax,ax
	jnz .isvcpi
.novcpi:
	mov ax,1
	stc
	pop es
	ret
.isvcpi:
	mov ax,0de00h
	int 67h
	test ax,ax
	jnz .novcpi
	pop es
	xor ax,ax
	clc
	ret
