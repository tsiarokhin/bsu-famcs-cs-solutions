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

.const
    szGoodBye       db  "Press ENTER to continue...", 0
    szEndLine       db  13, 10, 0

.data
    _n      dd  10000
    _min    dq  0.0
    _max    dq  3.14		; 2*PI
    res     dq  0.0

.data?
    buf     db  300 dup(?)
    step    dq  ?
    x       dq  ?
    
.code
MainProc proc
    
    finit
    fld     _max
    fsub    _min
    fild     _n
    fdiv
    fst     x
    fstp    step
        
    mov ecx, _n
    _loop:
		fld x
		fcos
		fmul x
		fmul step
		fadd res
		fstp res
		fld x
		fadd step
		fstp x
	loop _loop
        
    invoke FloatToStr, res, addr buf
    invoke StdOut, addr buf
    invoke StdOut, addr szEndLine
    invoke StdOut, addr szGoodBye
    invoke StdIn, addr buf, 300
    invoke ExitProcess, 0
        
MainProc endp
end MainProc