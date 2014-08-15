; simple example for DESQview detection

format mz
entry cseg:start

segment cseg use16

include 'dv.inc'
;include 'desqview.inc' removed due to changes in dv.inc
;dv.inc now includes desqview.inc 

start:
	mov ax,cs
	mov ds,ax
	mov es,ax

	call check_desqview	;check_desqview is not compatible with original DV_GET_VERSION
				;but is FAPI (f/One Extender) style function
				;the BX register contains DV version or 0
	jnc @f
	mov dx,nodv_msg
	jmp finish

@@:
	mov dx,dvfound_msg

finish:
	mov ah,9
	int 21h
	mov ax,4c00h
	int 21h

nodv_msg	db 'DESQview is not running.',13,10,'$'
dvfound_msg	db 'Running under DESQview :)',13,10,'$'


