.686
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
	szRoot				db	"Root: ", 0
	szEndl				db	13, 10, 0
    szEnterA            db  "a: ", 0
    szEnterB            db  "b: ", 0
	szEnterC            db  "c: ", 0
    buf                 db  300 dup(' ')
    fa                  dq  ?
    fb                  dq  ?
	fc					dq	?
	cura				dq	?
	curb				dq	?
	mid					dq  ?
	val					dq	?
	vala				dq  ?
	valb				dq  ?
	part1				dq	?
	dva					dw	2
    step                dq  0.001
	szGoodBye	db "Press ENTER to continue...", 13, 10, 0
.code

MainProc	proc
	invoke  StdOut, addr szEnterA
	invoke  StdIn, addr buf, 300
	invoke  StrToFloat, addr buf, addr fa
	invoke  StdOut, addr szEnterB
	invoke  StdIn, addr buf, 300
	invoke  StrToFloat, addr buf, addr fb
	invoke  StdOut, addr szEnterC
	invoke  StdIn, addr buf, 300
	invoke  StrToFloat, addr buf, addr fc
	fld     fb
	fld     fa
	fchs
	cycle:
		fst		cura
		fadd    step
		fst		curb
		fcomi	st(0), st(1)
		jae		cycle_end
		fld		cura
		call	func
		fstp	vala
		fld		curb
		call	func
		fmul	vala
		fldz
		fcomip	st(0), st(1)
		fstp	vala
		jb		cycle
		fld		curb
		fld		cura
		call	findRootOnSegment			
		jmp cycle
	cycle_end:
	fstp	cura
	fstp	curb
	invoke  StdOut, addr szGoodBye
	invoke  StdIn, addr buf, 300
	invoke  ExitProcess, 0
MainProc    endp

findRootOnSegment  proc
	mov		ecx, 1000
	binary_cycle:
		fstp	cura
		fstp	curb
		fld		cura
		fadd	curb
		fidiv	dva
		fst		mid
		call	func
		fld		cura
		call	func
		fstp	vala
		fmul	vala
		fldz
		fcomip	st(0), st(1)
		fstp	vala
		fld		mid
		jb		right
		fstp	curb
		jmp		binary_cycle_end
		right:
		fstp	cura
		binary_cycle_end:
		fld		curb
		fld		cura
		loop binary_cycle
	fstp	cura
	fstp	curb
	invoke	FloatToStr, cura, addr buf
	invoke	StdOut, addr szRoot
	invoke	StdOut, addr buf
	invoke	StdOut, addr szEndl
    ret
findRootOnSegment  endp

func		proc
	fst		val    
	fmul	val
	fmul	fa
	fstp	part1
	fld		val
	fsub	fb
	fstp	val
	fld		fb
	fdiv	val
	fadd	part1
	fadd	fc
	ret
func		endp


end MainProc