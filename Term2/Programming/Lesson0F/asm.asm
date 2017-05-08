.686
.model flat
.stack

public _rootsCount@12

.code

_countD proc
	mov		ebx, 4
	imul	ebx, dword ptr [esp + 8] 
	imul	ebx, dword ptr [esp + 16]  
	neg		ebx
	mov		eax, dword ptr [esp + 12]
	imul	eax, dword ptr [esp + 12]
	add		eax, ebx
	ret
_countD endp

_rootsCount@12 proc
	call	_countD
	mov		edx, eax

	cmp		edx, 0
	jz		zero
	jl		less

	;greater (by default)
	mov		eax, 2
	jmp		the_end
	zero:
		mov		eax, 1
		jmp		the_end
	less:
		mov		eax, 0
	the_end:
	ret 12 
_rootsCount@12 endp

end