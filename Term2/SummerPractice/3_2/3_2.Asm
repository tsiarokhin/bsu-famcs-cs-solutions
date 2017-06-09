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
	szConst     db  "Const ln(2) = ", 0
	szCalc      db  "Calc  ln(2) = ", 0
	szGoodBye	db "Press ENTER to continue...", 13, 10, 0
	endl		db 13, 10, 0 

	dva			dw 2
	
	summ		dq 0.0
	temp		dq 1.0
	k			dq 0.0
	x			dq 1.0

	buff		db 300 dup(?)
	buf			db 300 dup(?)
	dwA			dd ?
	result		dd ?
	chisl		dq ?
	ans2		dq ?
	rec			dq ?

.code
	MainProc proc

	finit 
	fldln2
	fstp	ans2

	invoke FloatToStr, ans2, addr buff
	invoke  StdOut, addr szConst
	invoke StdOut, addr buff
	invoke StdOut, addr endl
	mov		ecx, 10600
m:
	fld1			;
	fadd	k		;
	fstp	k		;	k++
	fstp	rec		;

	fld		temp	;
	fmul	x		;
	fstp	temp	; temp *= x
	fstp	rec		;

	fld		temp	;
	fdiv	k		; result = temp/k
	fstp	result	;

	fld		summ	;
	mov		eax, ecx;
	cdq				;
	idiv	dva		;
	cmp		edx, 0	; (ecx%2 == 0)?(+result):(-result)
	jne		plp		;
	fadd	result	;
	jmp		lpl		;
plp:                ;
	fsub	result  ;
lpl:
	fstp	summ
	fstp	rec
	loop	m

	invoke FloatToStr, summ, addr buff
	invoke  StdOut, addr szCalc
	invoke StdOut, addr buff
	invoke StdOut, addr endl

	invoke StdOut, addr szGoodBye
	invoke StdIn, addr buff, 300
	invoke ExitProcess, 0

	MainProc endp

end MainProc