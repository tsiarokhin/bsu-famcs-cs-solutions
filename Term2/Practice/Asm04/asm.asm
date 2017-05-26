.586
.model flat

public _power@8
public _longest_seq@8

.code

_power@8 proc
	mov		ecx, [esp+8]
	mov		eax, 1
_loop:
	imul	eax, [esp+4]
	loop _loop
	ret 8
_power@8 endp 

_longest_seq@8 proc
	mov		esi, [esp+4]
	mov		ah, [esi] ; prev char
	mov		cl, 1     ; cur length
	mov		bh, 0	  ; max index
	mov		ch, 0	  ; max length
	inc		esi
	mov		al, [esi] ; cur char
	mov		bl, 1     ; cur index
_loop:
	cmp		ah, al
	jne		_not_equal
	;if equal:
	inc		cl ; ++len
	jmp		_check_loop
_not_equal:
	cmp		cl, ch
	jg		_new_max
	jmp		_check_loop
_new_max:
	mov		ch, cl
	mov		bh, bl
	mov		cl, 1
	jmp		_check_loop
_check_loop:
	inc		bl
	mov		ah, [esi]
	inc		esi
	mov		al, [esi]
	cmp		al, 0
	jne		_loop
; after loop:
	xor		eax, eax
	mov		al, bh
	sub		al, ch
	
	mov		edx, [esp+8]
	mov		[edx], ch
	ret 8
_longest_seq@8 endp 

end
