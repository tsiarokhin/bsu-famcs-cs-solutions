.686
.model flat
.stack

public _shortest_word@4
public _find@16

.code

_shortest_word@4 proc
	mov		edx, dword ptr [esp+4]
	xor		eax, eax
	xor		al, al ; shortest word pos
	mov		ah, 100 ; shortest word len
	xor		bl, bl ; current word pos
	xor		bh, bh ; current word len

cycle:
	mov		cl, byte ptr [edx]
	cmp		cl, ' '
	je		end_of_word
	jne		same_word

end_of_word:
	cmp		bh, ah
	jl		new_shortest
	jmp		new_word

new_shortest:
	mov		ah, bh
	mov		al, bl
	; jmp		new_word
	
new_word:
	inc		bl
	xor		bh, bh
	jmp		cycle_test

same_word:
	inc		bh
	; jmp cycle_test
	
cycle_test:
	inc		edx
	mov		cl, byte ptr [edx]
	cmp		cl, 0
	jne cycle

	xor ah, ah
	ret 4
_shortest_word@4 endp

_find@16 proc
	mov ebx,edi
	mov edx,esi
	cld
	mov ecx, [esp+12] ; len1
	mov edi, [esp+8] ; word
	mov al, [edi] ; first char of word
	mov edi, [esp+4] ; string
m_beg:
	repne scasb ; first symbol of word in str
	jecxz m_not ; not found
	push edi
	push ecx
	mov ecx, [esp+24]
	dec ecx
	mov esi, [esp+16]
	inc esi
	; compare word (from second symbol) with str
	repe cmpsb
	jz m_found ; word found
m_notfound:
	pop ecx
	pop edi
	jmp m_beg
m_not:
	mov eax, 0
	jmp m_end
m_found:
	pop ecx
	pop edi
	mov eax, 1
m_end:
	mov edi,ebx
	mov esi,edx
	ret 16
_find@16 endp

end