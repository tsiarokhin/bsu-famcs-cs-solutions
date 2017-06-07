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
    szPrompt    db  "Enter line of words: ", 0
	szEndLine   db  13, 10, 0
	szOutput    db  "Word with max number of unique symbols: ", 0
	szGoodBye   db  "Press ENTER to continue...", 13, 10, 0

	word_count  db  0
	max_chars   db  0
	max_word    db  0

.data?
    buf         db  100 dup(?)
	words       db  100 dup(?)
	word_starts db	100 dup(?)
	word_unique db	100 dup(?)
	letters     db	256 dup(?)
.code

MainProc	proc

;;;;;;;;;;;;;;;;;;;;;;;;;;; input words
    invoke  StdOut, addr szPrompt
	call readWords    
;;;;;;;;;;;;;;;;;;;;;;;;;;;

	xor		ecx, ecx
_words_loop:
	push	ecx
	call	countUnique@4
	inc		ecx
	cmp		cl, word_count
	jl		_words_loop

	lea		ebx, word_unique
	xor		ecx, ecx
	mov		cl, word_count
	dec		ecx
_words_loop_dec:
	mov		al, byte ptr [ebx+ecx]
	cmp		al, max_chars
	jle		_not_new_max
	mov		max_chars, al
	mov		max_word, cl
_not_new_max:
	dec		ecx
	cmp		ecx, 0
	jge		_words_loop_dec



	lea		ebx, word_starts   ;
	add		bl, max_word       ;
	mov		al, byte ptr [ebx] ; ebx = words + word_starts[max_word]
	lea		ebx, words         ;
	add		bl, al             ;

	invoke  StdOut, addr szOutput
    invoke  StdOut, ebx
    invoke  StdOut, addr szEndLine

	invoke  StdOut, addr szGoodBye
    invoke  StdIn, addr buf, 100
    invoke  ExitProcess, 0
MainProc    endp

readWords proc 
    pushad
    
    invoke  StdIn, addr words, 100
	mov		ecx, eax
	cld
	lea		edi, words
    lea		esi, words
	mov     byte ptr [esi+eax-2],' '   

    xor     edx, edx
    
_loop:
	
	mov		al, ' '  
    repne	scasb
	jecxz	not_found

	mov		byte ptr [edi-1], 0
	
	lea		ebx, word_starts
	add		bl, word_count
	
	lea		eax, words
	neg		eax
	add		eax, esi
	mov		byte ptr [ebx], al

	inc		word_count

	mov     esi, edi
    
    jmp     _loop

not_found:
    popad
    ret

readWords endp

countUnique@4 proc 	
    pushad

	xor		ecx, ecx
	lea		edx, letters
_zero_array:
	mov		byte ptr [edx + ecx], 0
	inc		ecx
	cmp		ecx, 256
	jl		_zero_array


	lea		ebx, word_starts   ;
	add		ebx, [esp+36]      ;
	mov		al, byte ptr [ebx] ; ebx = words + word_starts[arg1]
	lea		ebx, words         ;
	add		bl, al             ;

	xor		eax, eax
	xor		ecx, ecx
_letter_loop:
	mov		al, byte ptr [ebx + ecx]
	cmp		al, 0
	je		_word_end
	mov		byte ptr [edx + eax], 1
	inc		ecx
	jmp _letter_loop

_word_end:

	xor		eax, eax
	xor		ecx, ecx
_count_array:
	mov		ah, byte ptr [edx + ecx]
	cmp		ah, 0
	je		_next_letter
	inc		al
_next_letter:
	inc		ecx
	cmp		ecx, 256
	jl		_count_array

	lea		ebx, word_unique
	add		ebx, [esp+36]
	mov		byte ptr [ebx], al

    popad
    ret 4

countUnique@4 endp



end MainProc
