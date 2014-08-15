; simple example for DESQview detection

format mz
entry cseg:start

segment cseg use16

include 'vcpic.inc'

start:
	mov ax,cs
	mov ds,ax
	mov es,ax

	call check_vcpi
	jnc @f
	mov dx,novcpi_msg
	jmp finish

@@:
	mov dx,vcpifound_msg

finish:
	mov ah,9
	int 21h
	mov ax,4c00h
	int 21h

novcpi_msg	  db 'No VCPI host found.',13,10,'$'
vcpifound_msg	  db 'VCPI host is running.',13,10,'$'


