; f/One32 32-bit DOS Extender (c) ACP 2014
; desqview.inc: handles DESQview detection

macro CHECK4DV {
      cmp [in_dv],1
      jz @f
      stc
      ret
@@:
}

check_desqview:
	mov ax,2b01h
	mov cx,4445h	;'DE': don't put 'DE' in FASM becouse it will treat is as word and change byte order
	mov dx,5351h	;'SQ'
	int 21h
	cmp al,0ffh
	jne @f
	xor bx,bx
	mov ax,1
	stc
	ret
@@:
	mov [desqview_ver],bx
	inc [in_dv]
	xor ax,ax
	clc
	ret

dv_pause:
	CHECK4DV
	mov ax,1000h
	int 15h
	clc
	ret

dv_begin_critical_section:
	CHECK4DV
	mov ax,101bh
	int 15h
	clc
	ret

dv_end_critical_section:
	CHECK4DV
	mov ax,101ch
	int 15h
	clc
	ret


