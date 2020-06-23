	.586
	.model flat, stdcall
	option casemap :none

	include \masm32\include\windows.inc
	include \masm32\include\user32.inc
	include \masm32\include\kernel32.inc
	include \masm32\include\masm32.inc

	includelib \masm32\lib\user32.lib
	includelib \masm32\lib\kernel32.lib
	includelib \masm32\lib\masm32.lib


	.data
		a DWORD 0
		b DWORD 0
		i DWORD 0
		t DWORD 0
		n DWORD 0
		_t_t_0 DWORD 0
		_t_t_1 DWORD 0
		_t_t_buffer BYTE 128 dup(0)
		_t_t_LF BYTE 13, 10, 0


	.code
_start:
	MOV eax, 0
	MOV a, eax
	MOV eax, 1
	MOV b, eax
	MOV eax, 1
	MOV i, eax
	invoke StdIn, ADDR _t_t_buffer, 127
	invoke StripLF, ADDR _t_t_buffer
	invoke atodw, ADDR _t_t_buffer
	MOV n, eax
	invoke dwtoa, a, ADDR _t_t_buffer
	invoke StdOut, ADDR _t_t_buffer
	invoke StdOut, ADDR _t_t_LF
	invoke dwtoa, b, ADDR _t_t_buffer
	invoke StdOut, ADDR _t_t_buffer
	invoke StdOut, ADDR _t_t_LF
@0:
	MOV eax, i
	CMP eax, n
	jl @1
	jmp @2
@1:
	MOV eax, b
	MOV t, eax
	MOV eax, a
	ADD eax, b
	MOV _t_t_0, eax
	MOV eax, _t_t_0
	MOV b, eax
	invoke dwtoa, b, ADDR _t_t_buffer
	invoke StdOut, ADDR _t_t_buffer
	invoke StdOut, ADDR _t_t_LF
	MOV eax, t
	MOV a, eax
	MOV eax, i
	ADD eax, 1
	MOV _t_t_1, eax
	MOV eax, _t_t_1
	MOV i, eax
	jmp @0
@2:
	invoke ExitProcess, 0
end _start
