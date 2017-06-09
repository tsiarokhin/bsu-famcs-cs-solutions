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
    szPrompt    db  "Enter x: ", 0
	szEndLine   db  13, 10, 0
	szOutput    db  "0.5^x =  ", 0
	szGoodBye   db  "Press ENTER to continue...", 13, 10, 0

	a			real8 0.5
	odin		dw	1
    buf         db  100 dup(?)
    x           real8 ?
	res			real8 ?
	
.code

MainProc	proc

    invoke  StdOut, addr szPrompt
    invoke  StdIn, addr buf, 100
    invoke  StrToFloat, addr buf, addr x

	finit
	fld		x
	fld		a
	fyl2x					;st0 = z = x*log[2, 0.5]
	fld		st(0)			;st0 = z    st1 = z

	frndint					;st0 = round(z)			st1 = z
    fxch	st(1)			;st0 = z				st1 = round(z)
    fsub	st(0), st(1)	;st0=z-round(z)			st1=round(z)
    f2xm1					;st0=2^(z-round(z))-1   st1=round(z)
    fiadd	odin			;st0=2^(z-round(z))     st1=round(z)
    fscale					;st0=(2^(z-round(z)))*(2^round(z)) = 2^(z)

	fst		res

	invoke  FloatToStr,  res, addr buf
	invoke  StdOut, addr szOutput
    invoke  StdOut, addr buf
    invoke  StdOut, addr szEndLine

	invoke  StdOut, addr szGoodBye
    invoke  StdIn, addr buf, 100
    invoke  ExitProcess, 0
MainProc    endp

end MainProc
