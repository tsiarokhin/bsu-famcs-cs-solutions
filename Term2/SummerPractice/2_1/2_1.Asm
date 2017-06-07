.486
.model flat, stdcall                    
option casemap :none

include windows.inc     ; always first

include masm32.inc
include gdi32.inc
include user32.inc
include kernel32.inc

includelib masm32.lib
includelib gdi32.lib
includelib user32.lib
includelib kernel32.lib

.data
    szPrompt    db  "Enter matrix size: ", 0
	szEndLine   db  13, 10, 0
	szOutput    db  "Max element in negative columns: ", 0
	neg_count   db 0
	max_elem	db -128
	szGoodBye     	db  "Press ENTER to continue...", 13, 10, 0

.data?
    buf         db  100 dup(?)
    n           db ?
    matrix      db 10000 dup (?) 
    neg_columns db 100 dup (?)

.code

MainProc	proc

;;;;;;;;;;;;;;;;;;;;;;;;;;; input n
    invoke  StdOut, addr szPrompt
    invoke  StdIn, addr buf, 100
    invoke  atol, addr buf
    mov     n, al
;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;; reading matrix
	xor		ecx, ecx
_lines_loop:
	lea		ebx, matrix
	mov		eax, ecx
	mul		n
	add		ebx, eax
    call    readArray
    inc		ecx
	cmp		cl, n
	jne		_lines_loop
;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;; searching negative-only columns
	xor		ecx, ecx
_columns_loop:
	xor		edx, edx

	_lines_loop2:
		lea		ebx, matrix 	; |
		mov		eax, edx    	; |
		mul		n               ; | ebx = matrix + n*edx + ecx
		add		eax, ecx        ; |
		add		ebx, eax        ; |

		xor		eax, eax
		mov		al, byte ptr [ebx]
		cmp		al, 0
		
		jl		_less
		jmp		_has_positive
	_less:
		inc		edx
		cmp		dl, n
		jne		_lines_loop2

	lea		ebx, neg_columns
	add		bl, neg_count
	mov		byte ptr [ebx], cl
	inc		neg_count
	
_has_positive:
	inc		ecx
	cmp		cl, n
	jne		_columns_loop
;;;;;;;;;;;;;;;;;;;;;;;;;;; 

;;;;;;;;;;;;;;;;;;;;;;;;;;; searching max element in negative-only columns
	xor		ecx, ecx ; ch - col num
					 ; cl - loop var
_columns_loop2:
	xor		edx, edx

	lea		ebx, neg_columns   ;
	add		bl,	cl			   ; ch = neg_columns[cl]
	mov		ch, byte ptr [ebx] ;

	_lines_loop3:
		lea		ebx, matrix 	; |
		mov		eax, edx    	; |
		mul		n               ; | ebx = matrix + n*edx + ch
		add		al, ch          ; |
		add		ebx, eax        ; |

		xor		eax, eax
		mov		al, byte ptr [ebx]
		
		cmp		al, max_elem
		jle		_not_new_max		
		mov		max_elem, al
		
	_not_new_max:
		inc		edx
		cmp		dl, n
		jne		_lines_loop3

	
	inc		cl
	cmp		cl, neg_count
	jne		_columns_loop2
;;;;;;;;;;;;;;;;;;;;;;;;;;; 
	
	xor		eax, eax
	mov		al, max_elem
	neg		al
	neg		eax

	invoke  ltoa, eax, addr buf
	invoke  StdOut, addr szOutput
    invoke  StdOut, addr buf
    invoke  StdOut, addr szEndLine

	invoke  StdOut, addr szGoodBye
    invoke  StdIn, addr buf, 100
    invoke  ExitProcess, 0
MainProc    endp

readArray proc ; reads n bytes separated by ' ' into [ebx]. By Maxim Teryokhin
    pushad
    
    invoke  StdIn, addr buf, 100
	cld
	lea		edi, buf
    lea		esi, buf
	mov     byte ptr [esi+eax-2],' '   

    xor     edx, edx
    mov     dl, n
    
_loop:
	mov		ecx, 100
	mov		al, ' '  
    repne	scasb
	mov		byte ptr [edi-1], 0
	
	push	edx
	Invoke  atol, esi
	pop		edx

	mov     byte ptr [ebx], al
	inc		ebx
	mov     esi, edi
    
    dec     edx
    cmp     edx, 0
    jne     _loop
    
    popad
    ret

readArray endp

end MainProc

